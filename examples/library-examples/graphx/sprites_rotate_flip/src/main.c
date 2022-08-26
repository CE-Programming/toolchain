#include <ti/getcsc.h>
#include <graphx.h>

/* Include the converted image data */
#include "gfx/gfx.h"

/* Create a buffer the same size as the source sprite */
gfx_UninitedSprite(sprite_buffer, star_width, star_height);

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    /* Draw the sprites */
    gfx_TransparentSprite(gfx_FlipSpriteY(star, sprite_buffer), 136, 24);
    gfx_TransparentSprite(gfx_FlipSpriteX(star, sprite_buffer), 136, 168);
    gfx_TransparentSprite(gfx_RotateSpriteC(star, sprite_buffer), 64, 96);
    gfx_TransparentSprite(gfx_RotateSpriteCC(star, sprite_buffer), 208, 96);
    gfx_TransparentSprite(gfx_RotateSpriteHalf(star, sprite_buffer), 136, 96);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
