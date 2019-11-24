#include <tice.h>
#include <graphx.h>
#include <fileioc.h>

/* Include the appvar sprite data */
#include "gfx/vargfx.h"

int main(void)
{
    /* This function is automatically created by convimg */
    /* Simply call it to load in graphics from the appvar */
    /* The common function name is <appvar name>_init */
    /* This function returns 1 on success or 0 if the appvar failed to load. */
    if (vargfx_init() == 0)
    {
        return 1;
    }

    /* Initialize the graphics */
    gfx_Begin();

    /* Set the palette for the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    /* Fill the screen */
    gfx_FillScreen(0);

    /* Draw the sprites directly from the appvar */
    gfx_Sprite(ubuntu, LCD_WIDTH / 2 - 16, LCD_HEIGHT / 2 - 16);
    gfx_Sprite(mint, LCD_WIDTH / 2 + 16, LCD_HEIGHT / 2 - 16);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
