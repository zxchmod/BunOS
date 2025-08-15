#include "app.h"
#include "gfx.h"
#include "input.h"
#include <string.h>

#define MAX_APPS 12
static const BApp* registry[MAX_APPS];
static int reg_count = 0;

void app_register(const BApp* app){
    if(reg_count < MAX_APPS) registry[reg_count++] = app;
}
int app_count(){ return reg_count; }
const BApp* app_get(int idx){ if(idx<0||idx>=reg_count) return 0; return registry[idx]; }

int app_launch_by_id(const char* id){
    for(int i=0;i<reg_count;i++){
        if(strcmp(registry[i]->id, id)==0){
            if(registry[i]->entry) registry[i]->entry();
            return 1;
        }
    }
    return 0;
}

static void app_music(){ gfx_clear(0x10); gfx_text(16,20,"Music (demo)",0x3F); gfx_text(16,40,"Press any key to return",0x2F); key_read(); }
static void app_notes(){ gfx_clear(0x10); gfx_text(16,20,"Notes (demo)",0x3F); gfx_text(16,40,"Press any key to return",0x2F); key_read(); }
static void app_files(){ gfx_clear(0x10); gfx_text(16,20,"Files (demo)",0x3F); gfx_text(16,40,"Press any key to return",0x2F); key_read(); }

void app_init_builtins(){
    static const BApp a1 = { "music", "Music", app_music, 1 };
    static const BApp a2 = { "notes", "Notes", app_notes, 1 };
    static const BApp a3 = { "files", "Files", app_files, 1 };
    app_register(&a1); app_register(&a2); app_register(&a3);
}

/* microloader placeholder - in this demo it does nothing more than note potential external apps */
void app_scan_bunapps(){
    /* scanning omitted in demo build; QEMU-specific sector reads implemented in storage.c could be used */
    return;
}
