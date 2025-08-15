#include "storage.h"
#include <string.h>

/* BIOS sector helpers are implemented inline for simplicity. This code is demo-only. */

/* Minimal BIOS read wrapper (reads one sector into buf) */
static void bios_read_sector(void* buf, unsigned char track, unsigned char head, unsigned char sector){
    unsigned short off = 0x9000;
    unsigned char* dst = (unsigned char*)(0x0000 * 16 + off);
    /* Attempt to call int 0x13 via inline asm that expects ES:BX pointing to buffer;
       For portability in this demo, we'll do a best-effort that works in QEMU/real-mode. */
    /* Copy buffer into the low memory area first (this is a placeholder operation in a demo environment). */
    unsigned char* b = (unsigned char*)buf;
    for(int i=0;i<512;i++) dst[i] = b[i];
    asm volatile(
        "push %%es\n\t"
        "mov %0, %%bx\n\t"
        "mov $0x00, %%dl\n\t"
        "mov $0x02, %%ah\n\t"
        "mov $1, %%al\n\t"
        "mov %1, %%ch\n\t"
        "mov %2, %%cl\n\t"
        "mov %3, %%dh\n\t"
        "mov $0x0000, %%ax\n\t"
        "mov %%ax, %%es\n\t"
        "int $0x13\n\t"
        "pop %%es\n\t"
        :
        : "r"(off), "r"(track), "r"(sector), "r"(head)
        : "ax","bx","cx","dx","es"
    );
    for(int i=0;i<512;i++) b[i] = dst[i];
}

static int bios_write_sector(void* buf, unsigned char track, unsigned char head, unsigned char sector){
    unsigned short off = 0x9000;
    unsigned char* dst = (unsigned char*)(0x0000 * 16 + off);
    unsigned char* b = (unsigned char*)buf;
    for(int i=0;i<512;i++) dst[i] = b[i];
    int status;
    asm volatile(
        "push %%es\n\t"
        "mov %1, %%bx\n\t"
        "mov $0x00, %%dl\n\t"
        "mov $0x03, %%ah\n\t"
        "mov $1, %%al\n\t"
        "mov %2, %%ch\n\t"
        "mov %3, %%cl\n\t"
        "mov %4, %%dh\n\t"
        "mov $0x0000, %%ax\n\t"
        "mov %%ax, %%es\n\t"
        "int $0x13\n\t"
        "jc 1f\n\t"
        "mov $0, %0\n\t"
        "jmp 2f\n\t"
        "1:\n\t"
        "mov $1, %0\n\t"
        "2:\n\t"
        "pop %%es\n\t"
        : "=r"(status)
        : "r"(off), "r"(track), "r"(sector), "r"(head)
        : "ax","bx","cx","dx","es"
    );
    return status;
}

int storage_read_config(BUNCFG* cfg){
    unsigned char buf[512];
    for(int i=0;i<512;i++) buf[i]=0;
    bios_read_sector(buf, 79, 1, 18);
    if(buf[0]=='B' && buf[1]=='U' && buf[2]=='N' && buf[3]=='C' && buf[4]=='F' && buf[5]=='G'){
        memcpy(cfg, buf, sizeof(BUNCFG));
        return 0;
    }
    return -1;
}

int storage_write_config(const BUNCFG* cfg){
    unsigned char buf[512];
    for(int i=0;i<512;i++) buf[i]=0;
    memcpy(buf, cfg, sizeof(BUNCFG));
    return bios_write_sector(buf, 79, 1, 18);
}
