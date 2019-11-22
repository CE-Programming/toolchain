#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <keypadc.h>

/* Include the sprite data */
#include "gfx/logo_gfx.h"

/* Function for drawing the main sprite */
void draw_sprite(int x, int y) {
    /* Fill the screen with color index 0 */
    /* Note that this is a super inefficient way to */
    /* redraw, but it demonstrates a simple way of clearing past data */
    gfx_FillScreen(0);

    /* Draw a bunch of different styled sprites on the screen */
    gfx_Sprite(ubuntu, x, y);

    /* Copy the buffer to the screen */
    gfx_BlitBuffer(); // This is the same as gfx_Blit(gfx_buffer)
}

void main(void) {
    bool right;
    bool left;
    bool up;
    bool down;
    kb_key_t arrows;

    /* Coordinates used for the sprite */
    int x, y;

    /* Initialize the 8bpp graphics */
    gfx_Begin();

    /* Set up the palette for our sprites */
    gfx_SetPalette(logo_gfx_pal, sizeof_logo_gfx_pal, 0);

    /* Start at 0, 0 */
    x = 0;
    y = 0;

    gfx_SetDrawBuffer();

    draw_sprite(x, y);

    do {
        /* Scan the keypad to update kb_Data */
        kb_Scan();

        /* Get the arrow key statuses */
        arrows = kb_Data[7];

        /* Convert the data to booleans so we can read them easier */
        right = arrows & kb_Right;
        left  = arrows & kb_Left;
        down  = arrows & kb_Down;
        up    = arrows & kb_Up;

        /* If any arrows are pressed, do this */
        if (arrows) {
            /* Do different directions depending on the keypress */
            if (right) {
                x++;
            }
            if (left) {
                x--;
            }
            if (down) {
                y++;
            }
            if (up) {
                y--;
            }
            draw_sprite(x, y);
        }
    } while (kb_Data[6] != kb_Clear);

    /* Close the graphics */
    gfx_End();
}
