/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Shared libraries */
#include <lib/ce/graphx.h>
#include "gfx/logo_gfx.h"

/* Put function prototypes here */

/* Put all your code here */
void main(void) {
	/* Decalre some variables */
	gfx_TempSprite( sprite_buffer, 32, 32 );

	/* Initialize the 8bpp graphics */
	gfx_Begin( gfx_8bpp );
	
	/* Normally we would set up the palette here, but convpng matched the image to the closest standard palette values */
	//gfx_SetPalette( logo_gfx_pal, sizeof(logo_gfx_pal), 0);
	
	/* Draw a sprite randomly on the screen without clipping */
	gfx_Sprite_NoClip( ubuntu, 10, 10 );
	gfx_Sprite_NoClip( gfx_FlipSpriteX(ubuntu, sprite_buffer), 10 + 32, 10 + 32 );
	gfx_Sprite_NoClip( gfx_FlipSpriteY(ubuntu, sprite_buffer), 10 + 32 + 32, 10 + 32 + 32);
	gfx_Sprite_NoClip( gfx_RotateSpriteC(ubuntu, sprite_buffer), 10 + 32 + 32 + 32, 10 + 32 + 32 + 32);
	gfx_Sprite_NoClip( gfx_RotateSpriteCC(ubuntu, sprite_buffer), 10 + 32 + 32 + 32 + 32, 10 + 32 + 32 + 32 + 32);
	gfx_Sprite_NoClip( gfx_RotateSpriteHalf(ubuntu, sprite_buffer), 10 + 32 + 32 + 32 + 32 + 32, 10 + 32 + 32 + 32 + 32 + 32);
	
	/* Wait for a key to be pressed */
	while( !os_GetCSC() );
	
	/* Close the graphics and return to the OS */
	gfx_End();
	prgm_CleanUp();
}
