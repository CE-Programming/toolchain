#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/lcd.h>
#include "graphics.h"

extern uint8_t graphics_Color;

static uint8_t* get_draw_buffer(void) {
	return (uint8_t*)(void*)lcd_LpBase;
}

static void draw_line0(int x0, int y0, int x1, int y1) {
    int dX = x1 - x0;
    int dY = y1 - y0;
    int yI = 1;
    if (dY < 0) {
        yI = -1;
        dY = -dY;
    }
    int dD = 2 * dY - dX;
    const int dD_jump = 2 * (dY - dX);
    dY *= 2;
    int y = y0;
    for (int x = x0; x < x1; x++) {
        graphics_SetPixel(x, y);
        if (dD > 0) {
            y += yI;
            dD += dD_jump;
        } else {
            dD += dY;
        }
    }
}

static void draw_line1(int x0, int y0, int x1, int y1) {
    int dX = x1 - x0;
    int dY = y1 - y0;
    int xI = 1;
    if (dX < 0) {
        xI = -1;
        dX = -dX;
    }
    int dD = (2 * dX) - dY;
    const int dD_jump = 2 * (dX - dY);
    dX *= 2;
    int x = x0;
    for (int y = y0; y < y1; y++) {
        graphics_SetPixel(x, y);
        if (dD > 0) {
            x += xI;
            dD += dD_jump;
        } else {
            dD += dX;
        }
    }
}

void graphics_Line(int x0, int y0, int x1, int y1) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 > x1) {
            draw_line0(x1, y1, x0, y0);
        } else {
            draw_line0(x0, y0, x1, y1);
        }
    } else {
        if (y0 > y1) {
            draw_line1(x1, y1, x0, y0);
        } else {
            draw_line1(x0, y0, x1, y1);
        }
    }
}

void graphics_FillScreen(uint8_t index) {
	memset(get_draw_buffer(), index, LCD_WIDTH * LCD_HEIGHT);
}
