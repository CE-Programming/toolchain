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
#include <graphx.h>
 
/* Put function prototypes here */

/* Put all your code here */
void main(void) {
    int pts[10], i;

    int rx = 100;
    int ry = 100;
    int cx = LCD_WIDTH / 2;
    int cy = LCD_HEIGHT / 2;

    /* Build the corridinates of the polygon */
    double theta = -M_PI / 2;
    double dtheta = 4 * M_PI / 5;
    for (i = 0; i < 5*2; i+=2) {
        pts[i] = (int)(cx + rx * cos(theta)),
        pts[i+1] = (int)(cy + ry * sin(theta));
        theta += dtheta;
    }

    /* Initialize the 8bpp graphics */
    gfx_Begin( gfx_8bpp );
    
    /* Set up the palette */
    gfx_SetColor( gfx_black );
    
    /* Draw a polygon on the buffer */
    gfx_Polygon(pts, 5);

    /* Pause */
    while( !os_GetCSC() ); 

    /* Flood fill the rest of the screen */
    gfx_FloodFill(0, 0, 0);

    /* Pause */
    while( !os_GetCSC() ); 
    
    /* Close the graphics and return to the OS */
    gfx_End();
    prgm_CleanUp();
}
