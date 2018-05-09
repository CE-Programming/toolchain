#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

/* This tutorial is meant to be played around with to get a feeling for how blitting works */
void main(void) {
    uint8_t c;

    /* Initialize the 8bpp graphics, screen cleared to white */
    gfx_Begin();

    /* Draw to buffer instead of directly to screen */
    gfx_SetDrawBuffer(); // This is the same as gfx_SetDraw(gfx_buffer)

    /* Draw a gradient (to the buffer) */
    for (c = 0; c < 8; c++) {
        gfx_SetColor(c);
        gfx_FillRectangle_NoClip(c * (LCD_WIDTH / 8), 0, LCD_WIDTH / 8, LCD_HEIGHT);
    }

    /* Wait for a key */
    while (!os_GetCSC());

    /* Copy parts of the buffer to the screen */
    gfx_BlitLines(gfx_buffer, LCD_HEIGHT - 32, 32);
    gfx_BlitRectangle(gfx_buffer, LCD_WIDTH / 4, LCD_HEIGHT / 4, LCD_WIDTH / 2, LCD_HEIGHT / 2);

    /* Wait for a key */
    while (!os_GetCSC());

    /* Copy the full buffer to the screen */
    gfx_BlitBuffer(); // This is the same as gfx_Blit(gfx_buffer)

    /* Wait for a key */
    while (!os_GetCSC());

    /* Close the graphics */
    gfx_End();
}
