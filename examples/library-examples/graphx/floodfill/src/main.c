#include <math.h>
#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
    int pts[10];
    int i;

    int rx = 100;
    int ry = 100;
    int cx = GFX_LCD_WIDTH / 2;
    int cy = GFX_LCD_HEIGHT / 2;

    /* Build the coordinates of the polygon */
    double theta = -M_PI / 2;
    double dtheta = 4 * M_PI / 5;
    for (i = 0; i < 10; i += 2)
    {
        pts[i+0] = (int)(cx + rx * cos(theta)),
        pts[i+1] = (int)(cy + ry * sin(theta));
        theta += dtheta;
    }

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the outline color */
    gfx_SetColor(0);

    /* Draw a polygon */
    gfx_Polygon(pts, 5);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Flood fill the inside of the polygon */
    gfx_FloodFill(GFX_LCD_WIDTH / 2, GFX_LCD_HEIGHT / 2, 229);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Flood fill the outside of the polygon */
    gfx_FloodFill(0, 0, 9);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
