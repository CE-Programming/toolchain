#include <ti/getcsc.h>
#include <graphx.h>

/* Include the converted image data */
#include "gfx/gfx.h"

int main(void)
{
    /* Initialize the 8bpp graphics */
    gfx_Begin();

    /* Set the palette for sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    /* These were set in the image conversion file */
    gfx_SetTransparentColor(0);
    gfx_FillScreen(1);

    /* Draw a normal scaled sprite */
    gfx_ScaledSprite_NoClip(oiram, 25, 15, 8, 8);

    /* A transparent sprite allows the background to show */
    gfx_ScaledTransparentSprite_NoClip(oiram, 175, 15, 8, 8);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
