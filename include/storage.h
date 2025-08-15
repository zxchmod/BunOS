#ifndef STORAGE_H
#define STORAGE_H
typedef struct {
    char magic[6]; /* "BUNCFG" */
    unsigned char version;
    unsigned char language;
    unsigned char wallpaper;
    unsigned char reserved[8];
    unsigned int crc32;
} BUNCFG;

int storage_read_config(BUNCFG* cfg);
int storage_write_config(const BUNCFG* cfg);
#endif
