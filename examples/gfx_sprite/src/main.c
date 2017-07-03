#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

/* Include the sprite data */
#include "gfx/logo_gfx.h"

void main(void) {
    /* Initialize the 8bpp graphics */
    gfx_Begin();
    
    /* Set up the palette for our sprites */
    gfx_SetPalette(logo_gfx_pal, sizeof logo_gfx_pal, 0);
    
    /* Fill the screen with color index 0 */
    gfx_FillScreen(0);

    /* Draw a bunch of different styled sprites on the screen */
    gfx_Sprite(ubuntu, 0, 0);
    gfx_Sprite_NoClip(ubuntu, 32, 32);
    gfx_TransparentSprite(ubuntu, 64, 64);
    gfx_TransparentSprite_NoClip(ubuntu, 96, 96);
    gfx_ScaledSprite_NoClip(ubuntu, 128, 128, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(ubuntu, 128, 0, 3, 3);
    
    /* Wait for a key to be pressed */
    while (!os_GetCSC());
    
    /* Close the graphics */
    gfx_End();
}

