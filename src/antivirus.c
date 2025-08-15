#include "antivirus.h"
#include "gfx.h"
#include "locale.h"
#include "app.h"
#include "input.h"
#include <string.h>

void av_scan(){
    const Locale* L = loc_get( LANG_EN );
    gfx_clear(0x10);
    gfx_text(16,18, L->av_scan, 0x3F);

    for(volatile int i=0;i<2000000;i++);

    int threat = 0;
    for(int i=0;i<app_count(); i++){
        const BApp* a = app_get(i);
        if(!a) continue;
        if(strstr(a->id, "bad") || (a->name && strstr(a->name, "BAD"))){
            threat = 1; break;
        }
    }

    if(threat) gfx_text(16,40, L->av_threat, 0x27);
    else gfx_text(16,40, L->av_clean, 0x2F);

    gfx_text(16,70, "Press any key to return", 0x28);
    key_read();
}
