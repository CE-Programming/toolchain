#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <fileioc.h>

/* Include the sprite data */
#include "gfx/all_gfx.h"
#include "gfx/var_gfx.h"

void main(void) {
    /* This function is automatically created by convpng */
    /* Simply call it to load in graphics from the appvar */
    /* The common function name is <appvar name>_init */
    var_gfx_init();
    
    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);
    
    /* Set up the palette for the sprite */
    gfx_SetPalette(all_gfx_pal, sizeof_all_gfx_pal, 0);
    
    /* Fill the screen with color index 0 */
    gfx_FillScreen(0);
    
    /* Draw the sprites directly from the appvar */
    gfx_Sprite(ubuntu, LCD_WIDTH/2 - 16, LCD_HEIGHT/2 - 16);
    gfx_Sprite(mint, LCD_WIDTH/2 + 16, LCD_HEIGHT/2 - 16);
    
    /* Wait for a key to be pressed */
    while (!os_GetCSC());
    
    /* Close the graphics */
    gfx_End();
}

