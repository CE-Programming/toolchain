#include <ti/getcsc.h>
#include <compression.h>
#include <graphx.h>

/* Include the converted graphics file */
#include "gfx/gfx.h"

int main(void)
{
    /* Define our sprite */
    gfx_sprite_t *apple;

    /* Allocate space for the decompressed sprite */
    /* Same as gfx_AllocSprite() */
    apple = gfx_MallocSprite(apple_width, apple_height);

    /* Decompress the sprite */
    zx0_Decompress(apple, apple_compressed);

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set up the palette */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_FillScreen(0);

    /* Draw the decompressed sprite centered */
    gfx_Sprite(apple,
               (GFX_LCD_WIDTH - apple_width) / 2,
               (GFX_LCD_HEIGHT - apple_height) / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Free allocated sprite memory */
    free(apple);

    /* End graphics drawing */
    gfx_End();

    return 0;
}
