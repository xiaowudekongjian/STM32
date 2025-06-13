#ifndef __FONT_H__
#define __FONT_H__

#include "main.h"

#define LINE(x)                ((x)*((sFONT*)ST7789V_GetFont())->height)
#define LINEY(x)               ((x)*((sFONT*)ST7789V_GetFont())->width)


typedef struct _tfont {
    const uint8_t *bitmap;
    uint8_t width;
    uint8_t height;
}sFONT;

extern sFONT Font8x16;
extern sFONT Font16x24;
extern sFONT Font24x32;

extern const uint8_t ASCII8x16_Table[];
extern const uint8_t ASCII16x24_Table[];
extern const uint8_t ASCII24x32_Table[];
#endif

