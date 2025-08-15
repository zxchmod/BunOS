#include "gfx.h"
#include "input.h"
#include "locale.h"
#include "ui.h"

void kernel_main(){
    gfx_set_mode13();

    const char* SPLASH[] = {
        "   ______                 ",
        "  / ____/___ _____  ____ _",
        " / /   / __ `/ __ \\/ __ `/",
        "/ /___/ /_/ / / / / /_/ / ",
        "\\____/\\__,_/_/ /_/\\__,_/  ",
        NULL
    };

    gfx_wallpaper_gradient();
    int sy = 44;
    for(int i=0; SPLASH[i]; ++i) gfx_text(48, sy + i*10, SPLASH[i], 0x3F);
    gfx_text(120, sy + 70, "by NameSugar", 0x2F);
    gfx_text(28, sy + 90, "Press 'u' UK, 'k' KO, 'r' RU, 'h' HE, any other key EN", 0x28);

    char k = key_read();

    ui_init();
    ui_loop();
}
