#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <debug.h>

#include "gfx/logo_gfx.h"

/* Defines used below */
#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT 32

/* Create some buffers used for storing the rotated and scaled sprites */
gfx_UninitedSprite(rotate_sprite, SPRITE_WIDTH, SPRITE_HEIGHT);
gfx_UninitedSprite(rotate_scale_sprite, SPRITE_WIDTH * 2, SPRITE_HEIGHT * 2);

void main(void) {
    uint8_t x;
    
    /* Start the graphics */
    gfx_Begin();
    
    /* Setup the palette used by the sprites*/
    gfx_SetPalette(logo_gfx_pal, sizeof logo_gfx_pal, 0);
    
    /* Loop for a bunch of times */
    for (x = 0; ++x;) {
        /* Rotate the sprite */
        gfx_RotateSprite(ubuntu, rotate_sprite, x);
        
        /* Rotate and scale the sprite */
        gfx_RotateScaleSprite(ubuntu, rotate_scale_sprite, 256 - x, 128);
        
        /* Draw the new images */
        gfx_Sprite_NoClip(rotate_scale_sprite, 0, 0);
        gfx_Sprite_NoClip(rotate_sprite, LCD_WIDTH/2, LCD_HEIGHT/2);
    }
    
    /* Wait for a key to be pressed */
    while (!os_GetCSC());
    
    /* Close the graphics */
    gfx_End();
}

