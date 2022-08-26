#include <ti/getcsc.h>
#include <graphx.h>

/* Include the converted image data */
#include "gfx/gfx.h"

int main(void)
{
    uint8_t x = 0;

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();

    /* Rotate the sprite until a key is pressed */
    do
    {

        /* Draw a rotated transparent scaled spite */
        gfx_RotatedScaledTransparentSprite_NoClip(star, 120, 80, 256 - x, 128);

        /* Show the buffered screen */
        gfx_BlitBuffer();

        /* Clear the old drawn sprite */
        gfx_FillScreen(1);

        /* Change the rotation amount */
        x++;

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
