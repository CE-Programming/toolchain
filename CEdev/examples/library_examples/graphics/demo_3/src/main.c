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

/* Place function prototypes here */

/* Put all your code here */
void main(void) {

	/* Triangle coordinates */
	int verts[6] = { 
			160,  1,  /* (x0, y0) */
			1,  238,  /* (x1, y1) */
			318,238,  /* (x2, y2) */
	};
    
	/* Initialize the 8bpp graphics */
	gfx_Begin( gfx_8bpp );

	/* Draw a yellow rectangle outline */
	gfx_SetColor( gfx_yellow );
	gfx_Rectangle( 0, 0, 320, 240 );
	
	/* Draw a blue triangle outline */
	gfx_SetColor( gfx_blue );
	gfx_Polygon( verts, 3 );
	
	/* Draw a red circle outline */
	gfx_SetColor( gfx_red );
	gfx_Circle( 160, 152, 80 );
	
	/* Wait for any key */
	while(!os_GetCSC());
	
	/* Draw a filled yellow rectangle */
	gfx_SetColor( gfx_yellow );
	gfx_FillRectangle( 0, 0, 320, 240 );
	
	/* Draw a filled blue triangle */
	gfx_SetColor( gfx_blue );
	gfx_FillTriangle( verts[0], verts[1], verts[2], verts[3], verts[4], verts[5] );
	
	/* Draw a filled red circle */
	gfx_SetColor( gfx_red );
	gfx_FillCircle( 160, 152, 80 );
	
	/* Wait for any key */
	while(!os_GetCSC());
	
	/* Shift the screen around a bit */
	gfx_ShiftDown(20);
	gfx_ShiftRight(20);
	gfx_ShiftLeft(20);
	gfx_ShiftDown(20);

	/* Wait for any key */
	while(!os_GetCSC());
	
	/* Close the graphics and return to the OS */
	gfx_End();
	prgm_CleanUp();
}
