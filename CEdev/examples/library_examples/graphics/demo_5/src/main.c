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
#include "gfx/all_gfx.h"

/* Put all your code here */
void main(void) {
	/* Define our sprite */
	gfx_image_t *apple;
	
	/* This is just here so that the malloc function is compiled into the binary */
	malloc(0);
	
	/* Allocate space for the decompressed sprite */
	apple = gfx_AllocSprite( 64, 64, malloc );
	
	/* Initialize the 8bpp graphics */
	gfx_Begin( gfx_8bpp );
	
	/* Set up the palette */
	gfx_SetPalette( all_gfx_pal, sizeof(all_gfx_pal), 0 );
	
	/* Looking at the output palette, this color is white */
	gfx_FillScreen( 0x00 );
	
	/* Decompress the sprite */
	gfx_LZDecompressSprite( apple_data_compressed, apple );
	
	/* Draw the decompressed sprite */
	gfx_Sprite( apple, (320 - 64) / 2, (240 - 64) / 2);

	/* Print some scaled text */
	gfx_SetTextScale( 5, 5 );
	gfx_SetTextFGColor( 0x01 );
	gfx_SetTextBGColor( 0x00 );
	gfx_PrintStringXY( "Apples!", 5, 5 );
	
	/* Wait for a key */
	while( !os_GetCSC() );
	
	/* Please, don't forget to free the apple image memory :) */
	free(apple);
	
	gfx_End();
	prgm_CleanUp();
}