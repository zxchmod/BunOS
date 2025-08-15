#include "input.h"
static unsigned char raw_read(){
    unsigned char al;
    asm volatile("xor %%ah, %%ah; int $0x16; mov %%al, %0" : "=r"(al) :: "ax");
    return al;
}

char key_read(){
    unsigned char a = raw_read();
    if(a == 0 || a == 0xE0){
        unsigned char b;
        asm volatile("xor %%ah, %%ah; int $0x16; mov %%al, %0" : "=r"(b) :: "ax");
        return (char)b;
    }
    return (char)a;
}

int key_is_arrow_left(char k){ return (unsigned char)k == 0x4B; }
int key_is_arrow_right(char k){ return (unsigned char)k == 0x4D; }
int key_is_arrow_up(char k){ return (unsigned char)k == 0x48; }
int key_is_arrow_down(char k){ return (unsigned char)k == 0x50; }
int key_is_enter(char k){ return k == '\r' || k == '\n'; }
int key_is_escape(char k){ return (unsigned char)k == 27; }
