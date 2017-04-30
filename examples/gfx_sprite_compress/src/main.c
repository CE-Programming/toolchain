#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <decompress.h>
#include <graphx.h>

/* Include the graphics file */
#include "gfx/all_gfx.h"

/* Put all your code here */
void main(void) {
    /* Define our sprite */
    gfx_image_t *apple;
    
    /* This is just here so that the malloc function is compiled into the binary */
    malloc(0);
    
    /* Allocate space for the decompressed sprite */
    apple = gfx_MallocSprite(220, 240);
    
    /* Decompress the sprite */
    dzx7_Standard(apple_compressed, apple); // or dzx7_Turbo
    
    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);
    
    /* Set up the palette */
    gfx_SetPalette(all_gfx_pal, sizeof all_gfx_pal, 0);
    gfx_FillScreen(0);
    
    /* Draw the decompressed sprite */
    gfx_Sprite(apple, (320 - 220) / 2, (240 - 240) / 2);
    
    /* Wait for a key */
    while (!os_GetCSC());
    
    /* Please, don't forget to free the apple image memory :) */
    free(apple);
    
    gfx_End();
}

