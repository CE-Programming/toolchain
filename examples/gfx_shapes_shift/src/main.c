#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

void main(void) {
    uint8_t y;
    uint24_t i;

    /* Triangle coordinates */
    int verts[6] = {
            160,  1,  /* (x0, y0) */
            1,  238,  /* (x1, y1) */
            318,238,  /* (x2, y2) */
    };

    /* Initialize the 8bpp graphics */
    gfx_Begin();
    gfx_SetColor(gfx_blue);

    /* Draw some circles to make sure they all look the same */
    y = 40;
    for (i = 2; i < 13; i++) {
        y += i;
        gfx_FillCircle_NoClip(80, y, i);
        y += i + 3;
    }
    y = 40;
    for (i = 2; i < 13; i++) {
        y += i;
        gfx_FillCircle(240, y, i);
        y += i + 3;
    }
    y = 40;
    for (i = 2; i < 13; i++) {
        y += i;
        gfx_Circle(160, y, i);
        y += i + 3;
    }

    /* Wait for any key */
    while (!os_GetCSC());

    gfx_FillScreen(gfx_white);
    gfx_SetColor(gfx_yellow);
    gfx_Rectangle(0, 0, 320, 240);

    /* Draw a blue triangle outline */
    gfx_SetColor(gfx_blue);
    gfx_Polygon(verts, 3);

    /* Draw a red circle outline */
    gfx_SetColor(gfx_red);
    gfx_Circle(160, 152, 80);

    /* Wait for any key */
    while (!os_GetCSC());

    /* Draw a filled yellow rectangle */
    gfx_SetColor(gfx_yellow);
    gfx_FillRectangle(0, 0, 320, 240);

    /* Draw a filled blue triangle */
    gfx_SetColor(gfx_blue);
    gfx_FillTriangle(verts[0], verts[1], verts[2], verts[3], verts[4], verts[5]);

    /* Draw a filled red circle */
    gfx_SetColor(gfx_red);
    gfx_FillCircle(160, 152, 80);

    /* Wait for any key */
    while (!os_GetCSC());

    /* Shift the screen around a bit */
    gfx_ShiftDown(20);
    gfx_ShiftDown(20);
    gfx_ShiftLeft(20);
    gfx_ShiftLeft(20);
    gfx_ShiftUp(20);
    gfx_ShiftRight(20);

    /* Wait for any key */
    while (!os_GetCSC());

    /* Close the graphics */
    gfx_End();
}
