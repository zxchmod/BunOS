#ifndef LOCALE_H
#define LOCALE_H

typedef enum { LANG_EN=0, LANG_UK=1, LANG_KO=2, LANG_RU=3, LANG_HE=4 } Language;

typedef struct {
    const char* os_name;
    const char* by_author;
    const char* tip;
    const char* btn_battery;
    const char* btn_open_lid;
    const char* btn_sleep;
    const char* btn_settings;
    const char* btn_apps;
    const char* btn_av;
    const char* battery_title;
    const char* device_title;
    const char* device_name;
    const char* sleeping;
    const char* halting;
    const char* settings_title;
    const char* settings_lang;
    const char* settings_wall;
    const char* lang_en;
    const char* lang_uk;
    const char* lang_ko;
    const char* lang_ru;
    const char* lang_he;
    const char* wall_solid;
    const char* wall_gradient;
    const char* wall_checker;
    const char* apps_title;
    const char* av_title;
    const char* av_scan;
    const char* av_clean;
    const char* av_ok;
    const char* av_threat;
} Locale;

const Locale* loc_get(Language lang);

#endif
