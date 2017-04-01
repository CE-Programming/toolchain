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
#include <libs/graphx.h>

#define color gfx_RGBTo1555(34, 55, 89)

/* Put function prototypes here */

/* Put all your code here */
void main(void) {
    uint8_t i = 0;
	
    /* Initialize the 8bpp graphics */
    gfx_Begin( gfx_8bpp );
	
    /* For i in 0..255 */
    do {
        
        /* Fade out to black */
        gfx_palette[0] = gfx_Darken(color, i);
        /* Fade in from black */
        gfx_palette[1] = gfx_Darken(color, ~i);
        /* Fade in from white */
        gfx_palette[3] = gfx_Lighten(color, ~i);
        /* Fade out to white */
        gfx_palette[2] = gfx_Lighten(color, i);
        
        /* Fade out to black */
        gfx_SetColor(0);
        gfx_FillRectangle_NoClip(0,0,160,120);
        /* Fade in from black */
        gfx_SetColor(1);
        gfx_FillRectangle_NoClip(160,0,160,120);
        /* Fade in from white */
        gfx_SetColor(2);
        gfx_FillRectangle_NoClip(0,120,160,120);
        /* Fade out to white */
        gfx_SetColor(3);
        gfx_FillRectangle_NoClip(160,120,160,120);

        /* Wait for a keypress at the start of each quarter of the fade */
        if (!(i & 0x3f)) {
            while(!os_GetCSC());
        }
        
    /* Loop until i is 0 again because of 8 bit range */
    } while(++i);
	
    /* Wait for a keypress */
    while(!os_GetCSC());
	
    /* Usual cleanup */
    gfx_End();
    prgm_CleanUp();
}
