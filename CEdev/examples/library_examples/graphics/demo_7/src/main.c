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

/* Put function prototypes here */

/* Put all your code here */
void main(void) {
	unsigned x_offset = 0, y_offset = 0;
    
	/* Initialize the 8bpp graphics */
	gfx_Begin( gfx_8bpp );
	
	/* Set up the palette */
	gfx_SetColor( gfx_black );
	
	/* Draw to buffer to avoid tearing */
	gfx_SetDrawBuffer();
	
	/* Draw a line on the buffer */
	//gfx_FillScreen( gfx_black );
	gfx_Line(0,0,319,239);
	
	/* Wait for a key */
	while(!os_GetCSC()); 
	
	/* Swap the buffer with the screen */
	gfx_SwapDraw();
	
	/* Copy part of the screen to the offscreen buffer */
	gfx_Blit( gfx_buffer );
	//gfx_BlitLines( gfx_buffer, 0, 20 );
	//gfx_BlitArea( gfx_buffer, 0, 0, 160, 120 );
	
	/* This should cause half of the line to flicker, and the other half to stay steady */
	
	while(!os_GetCSC()) {
		gfx_SwapDraw();
	}
	
	//while(!os_GetCSC());
	
	/* Close the graphics and return to the OS */
	gfx_End();
	prgm_CleanUp();
}
