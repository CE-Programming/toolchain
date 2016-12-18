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
    uint8_t i = 0;
	
    /* Initialize the 8bpp graphics */
    gfx_Begin( gfx_8bpp );
	
    do {
        /* Change palette entries 0 and 1 */
        gfx_palette[0] = gfx_Darken(gfx_RGBTo1555(255,255,255), i);
        gfx_palette[1] = gfx_Lighten(gfx_RGBTo1555(0,0,150), i);
        
        /* Draw using palette 0 entry */
        gfx_SetColor(0);
        gfx_FillRectangle_NoClip(0,0,160,120);
        gfx_FillRectangle_NoClip(160,120,160,120);
        
        /* Draw using palette 1 entry */
        gfx_SetColor(1);
        gfx_FillRectangle_NoClip(160,0,160,120);
        gfx_FillRectangle_NoClip(0,120,160,120);
        
    /* Loop until i is 0 again because of 8 bit range */
    } while(++i);
	
    /* Wait for key */
    while(!os_GetCSC());
	
    /* Usual cleanup */
    gfx_End();
    prgm_CleanUp();
}
