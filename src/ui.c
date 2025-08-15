#include "gfx.h"
#include "input.h"
#include "locale.h"
#include "app.h"
#include "antivirus.h"
#include "storage.h"
#include "power.h"
#include <string.h>

static Language g_lang = LANG_EN;
static int g_wall = 1;
static int battery = 90;
static int focused = 0;

static int s_lang = 0;
static int s_wall = 1;
static int s_focus = 0;

void ui_init(){
    BUNCFG cfg;
    if(storage_read_config(&cfg) == 0){
        if(cfg.magic[0]=='B'){
            int lang = cfg.language;
            int wall = cfg.wallpaper;
            if(lang>=0 && lang<=4) g_lang = (Language)lang;
            if(wall>=0 && wall<=2) g_wall = wall;
        }
    }
    app_init_builtins();
    app_scan_bunapps();
}

static void itoa_small(int v, char* out){
    if(v>=100){ out[0]='1';out[1]='0';out[2]='0';out[3]='%';out[4]=0; return; }
    if(v>=10){ out[0] = '0' + (v/10); out[1] = '0' + (v%10); out[2]='%'; out[3]=0; return; }
    out[0] = '0' + v; out[1] = '%'; out[2]=0;
}

static void draw_wall(){
    if(g_wall==0) gfx_wallpaper_solid(0x12);
    else if(g_wall==1) gfx_wallpaper_gradient();
    else gfx_wallpaper_checker();
}

static void draw_topbar(const Locale* L){
    gfx_fillrect(0,0,WIDTH,24,0x12);
    gfx_text(8,8, L->os_name, 0x3F);
    gfx_text(110,8, L->by_author, 0x2F);
}

static void draw_footer(const Locale* L){
    gfx_text(6, HEIGHT-12, L->tip, 0x28);
}

static void draw_home(){
    const Locale* L = loc_get(g_lang);
    draw_wall(); draw_topbar(L);
    gfx_logo_bread(16,36);
    gfx_text(140,48, L->battery_title, 0x3F);
    gfx_battery(140,66, 120, 16, battery);
    char buf[5]; itoa_small(battery, buf); gfx_text(270,66, buf, 0x3F);
    gfx_text(140,90, L->device_title, 0x3F);
    gfx_text(140,102, L->device_name, 0x2F);

    const char* labels[5] = { loc_get(g_lang)->btn_battery, loc_get(g_lang)->btn_open_lid, loc_get(g_lang)->btn_sleep, loc_get(g_lang)->btn_apps, loc_get(g_lang)->btn_av };
    int bx=8, by=132, bw=58, bh=18, gap=8;
    for(int i=0;i<5;i++) gfx_button(bx + i*(bw+gap), by, bw, bh, labels[i], i==focused);
    draw_footer(L);
}

static void draw_settings(){
    const Locale* L = loc_get(g_lang);
    draw_wall(); draw_topbar(L);
    gfx_text(10,32, L->settings_title, 0x3F);

    gfx_text(16,56, L->settings_lang, 0x3F);
    const char* ln = (s_lang==0)? L->lang_en : (s_lang==1)? L->lang_uk : (s_lang==2)? L->lang_ko : (s_lang==3)? L->lang_ru : L->lang_he;
    gfx_button(160,52,120,18, ln, s_focus==0);

    gfx_text(16,86, L->settings_wall, 0x3F);
    const char* wn = (s_wall==0)? L->wall_solid : (s_wall==1)? L->wall_gradient : L->wall_checker;
    gfx_button(160,80,120,18, wn, s_focus==1);

    gfx_button(16,120,48,18,"<", s_focus==2);
}

static void apply_and_save_settings(){
    g_lang = (s_lang==0)? LANG_EN : (s_lang==1)? LANG_UK : (s_lang==2)? LANG_KO : (s_lang==3)? LANG_RU : LANG_HE;
    g_wall = s_wall;
    BUNCFG cfg;
    memset(&cfg,0,sizeof(cfg));
    cfg.magic[0]='B';cfg.magic[1]='U';cfg.magic[2]='N';cfg.magic[3]='C';cfg.magic[4]='F';cfg.magic[5]='G';
    cfg.version = 1;
    cfg.language = (unsigned char)s_lang;
    cfg.wallpaper = (unsigned char)s_wall;
    storage_write_config(&cfg);
}

static void home_action(){
    if(focused==0){ if(battery>0) battery -= 3; }
    else if(focused==1){ for(int i=0;i<3;i++){ gfx_fillrect(16,36,110,50,0x10); for(volatile int d=0; d<40000; ++d); gfx_logo_bread(16,36); for(volatile int d=0; d<40000; ++d); } }
    else if(focused==2){ gfx_clear(0x00); gfx_text(120,96, loc_get(g_lang)->sleeping, 0x2F); idle_loop(); }
    else if(focused==3){
        const Locale* L = loc_get(g_lang);
        gfx_clear(0x10);
        gfx_text(8,8, L->apps_title, 0x3F);
        int n = app_count();
        for(int i=0;i<n;i++){ const BApp* a=app_get(i); if(a) gfx_text(8,28+i*12, a->name, 0x2F); }
        gfx_text(8,28+n*12+8,"Press key: m/music, n/notes, f/files, any other to return",0x28);
        char k = key_read();
        if(k=='m') app_launch_by_id("music");
        else if(k=='n') app_launch_by_id("notes");
        else if(k=='f') app_launch_by_id("files");
    }
    else if(focused==4){ av_scan(); }
}

void ui_loop(){
    while(1){
        draw_home();
        char k = key_read();
        if(key_is_escape(k)){ gfx_clear(0x00); gfx_text(120,96, loc_get(g_lang)->halting, 0x2F); idle_loop(); }
        if(key_is_arrow_left(k)){ if(focused>0) focused--; }
        else if(key_is_arrow_right(k)){ if(focused<4) focused++; }
        else if(key_is_enter(k)){ home_action(); }
        else if(k=='s' || k=='S'){
            s_lang = (g_lang==LANG_EN)?0:(g_lang==LANG_UK)?1:(g_lang==LANG_KO)?2:(g_lang==LANG_RU)?3:4;
            s_wall = g_wall; s_focus = 0;
            int in = 1;
            while(in){
                draw_settings();
                char kk = key_read();
                if(key_is_escape(kk)){ in=0; break; }
                if(key_is_arrow_up(kk)){ if(s_focus>0) s_focus--; }
                else if(key_is_arrow_down(kk)){ if(s_focus<2) s_focus++; }
                else if(key_is_enter(kk)){
                    if(s_focus==0) s_lang = (s_lang+1)%5;
                    else if(s_focus==1) s_wall = (s_wall+1)%3;
                    else if(s_focus==2){ apply_and_save_settings(); in=0; }
                }
            }
        }
        for(volatile int t=0;t<60000;t++); static int ticks=0; ticks++; if(ticks%12==0 && battery>0) battery--;
    }
}
