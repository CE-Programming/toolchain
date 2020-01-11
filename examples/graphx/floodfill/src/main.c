#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

void main(void) {
    int pts[10], i;

    int rx = 100;
    int ry = 100;
    int cx = LCD_WIDTH / 2;
    int cy = LCD_HEIGHT / 2;

    /* Build the coordinates of the polygon */
    double theta = -M_PI / 2;
    double dtheta = 4 * M_PI / 5;
    for (i = 0; i < 10; i += 2) {
        pts[i+0] = (int)(cx + rx * cos(theta)),
        pts[i+1] = (int)(cy + ry * sin(theta));
        theta += dtheta;
    }

    /* Initialize the 8bpp graphics */
    gfx_Begin();

    /* Set up the palette */
    gfx_SetColor(gfx_black);

    /* Draw a polygon on the buffer */
    gfx_Polygon(pts, 5);

    /* Pause */
    while (!os_GetCSC()); 

    /* Flood fill the rest of the screen */
    gfx_FloodFill(0, 0, 0);

    /* Pause */
    while (!os_GetCSC()); 

    /* Close the graphics */
    gfx_End();
}
