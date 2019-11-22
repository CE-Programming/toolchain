#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <compression.h>
#include <graphx.h>

/* Include the graphics file */
#include "gfx/all_gfx.h"

/* Put all your code here */
void main(void) {
    /* Define our sprite */
    gfx_sprite_t *apple;

    /* Allocate space for the decompressed sprite */
    apple = gfx_MallocSprite(apple_width, apple_height); /* Same as: gfx_AllocSprite(apple_width, apple_height, malloc) */

    /* Decompress the sprite */
    zx7_Decompress(apple, apple_compressed);

    /* Initialize the 8bpp graphics */
    gfx_Begin();

    /* Set up the palette */
    gfx_SetPalette(all_gfx_pal, sizeof_all_gfx_pal, 0);
    gfx_FillScreen(0);

    /* Draw the decompressed sprite */
    gfx_Sprite(apple, (LCD_WIDTH - 220) / 2, (LCD_HEIGHT - 240) / 2);

    /* Wait for a key */
    while (!os_GetCSC());

    /* Please, don't forget to free the apple image memory :) */
    free(apple);

    gfx_End();
}
