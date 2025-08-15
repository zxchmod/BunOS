#ifndef GFX_H
#define GFX_H
#include <stdint.h>
#define WIDTH 320
#define HEIGHT 200

void gfx_set_mode13();
void gfx_clear(uint8_t color);
void gfx_putpixel(int x, int y, uint8_t color);
void gfx_fillrect(int x, int y, int w, int h, uint8_t color);
void gfx_drawrect(int x, int y, int w, int h, uint8_t color);
void gfx_text(int x, int y, const char* s, uint8_t color);

void gfx_logo_bread(int x, int y);
void gfx_battery(int x, int y, int w, int h, int level);
void gfx_button(int x, int y, int w, int h, const char* label, int focused);

void gfx_wallpaper_solid(uint8_t color);
void gfx_wallpaper_gradient();
void gfx_wallpaper_checker();
#endif
