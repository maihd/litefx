#pragma once

#include "lite_meta.h"
#include "lite_string.h"


typedef struct LiteImage LiteImage;
typedef struct LiteFont  LiteFont;
typedef struct LiteColor LiteColor;
typedef struct LiteRect  LiteRect;


struct alignas(4) LiteColor
{
    uint8_t b, g, r, a;
};


struct alignas(4) LiteRect
{
    int32_t x, y, width, height;
};


void        lite_renderer_init(void);
void        lite_renderer_deinit(void);

void        lite_renderer_update_rects(LiteRect* rects, int32_t count);
void        lite_renderer_set_clip_rect(LiteRect rect);
void        lite_renderer_get_size(int32_t* x, int32_t* y);

LiteImage*  lite_new_image(int32_t width, int32_t height);
void        lite_free_image(LiteImage* image);

LiteFont*   lite_load_font(LiteStringView filename, float size);
void        lite_free_font(LiteFont* font);
void        lite_set_font_tab_width(LiteFont* font, int32_t n);
int         lite_get_font_tab_width(LiteFont* font);
int         lite_get_font_width(LiteFont* font, LiteStringView text);
int         lite_get_font_height(LiteFont* font);

void        lite_draw_rect(LiteRect rect, LiteColor color);
void        lite_draw_image(LiteImage* image, LiteRect* sub, int32_t x, int32_t y, LiteColor color);
int         lite_draw_text(LiteFont* font, LiteStringView text, int32_t x, int32_t y, LiteColor color);

//! EOF

