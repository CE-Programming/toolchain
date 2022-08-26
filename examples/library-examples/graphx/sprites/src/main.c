#include <ti/getcsc.h>
#include <graphx.h>

/* Include the converted graphics file */
#include "gfx/gfx.h"

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette for sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    /* These were set in the image conversion file */
    gfx_SetTransparentColor(0);
    gfx_FillScreen(1);

    /* Draw a normal sprite */
    gfx_Sprite_NoClip(oiram, 130, 110);

    /* A transparent sprite allows the background to show */
    gfx_TransparentSprite_NoClip(oiram, 190, 110);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
