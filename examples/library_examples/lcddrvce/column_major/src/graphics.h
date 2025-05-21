#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void graphics_Begin(void);
void graphics_End(void);

uint8_t graphics_SetColor(uint8_t index);

void graphics_SetPixel(uint24_t x, uint8_t y);

void graphics_FillScreen(uint8_t index);

void graphics_SetDraw(uint8_t location);
void graphics_Wait(void);
void graphics_SwapDraw(void);
void graphics_Line(int x0, int y0, int x1, int y1);

#ifdef __cplusplus
}
#endif

#endif /* GRAPHICS_H */
