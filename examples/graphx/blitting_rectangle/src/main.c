#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
    uint8_t c;

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Draw to buffer instead of directly to screen */
    /* This is the same as gfx_SetDraw(gfx_buffer) */
    gfx_SetDrawBuffer();

    /* Draw a gradient (to the buffer) */
    for (c = 0; c < 8; c++)
    {
        gfx_SetColor(c);
        gfx_FillRectangle_NoClip(c * (gfx_lcdWidth / 8), 0, gfx_lcdWidth / 8, gfx_lcdHeight);
    }

    /* Waits for a key */
    while (!os_GetCSC());

    /* Copy part of the drawn gradient to the visible screen */
    gfx_CopyRectangle(gfx_buffer, gfx_screen, gfx_lcdWidth / 4, gfx_lcdHeight / 4, gfx_lcdWidth / 4, gfx_lcdHeight / 4, gfx_lcdWidth / 2, gfx_lcdHeight / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* This is the same as gfx_SetDraw(gfx_screen) */
    gfx_SetDrawScreen();

    /* Draw a gradient (to the screen) */
    for (c = 16; c < 24; c++)
    {
        gfx_SetColor(c);
        gfx_FillRectangle_NoClip((c - 16) * (gfx_lcdWidth / 8), 0, gfx_lcdWidth / 8, gfx_lcdHeight);
    }

    /* Copy part of the drawn gradient to the offscreen buffer */
    gfx_CopyRectangle(gfx_screen, gfx_buffer, gfx_lcdWidth / 4, gfx_lcdHeight / 4, gfx_lcdWidth / 4, gfx_lcdHeight / 4, gfx_lcdWidth / 2, gfx_lcdHeight / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Copy the offscreen buffer to the visible screen */
    /* Same as gfx_BlitBuffer() */
    gfx_CopyRectangle(gfx_buffer, gfx_screen, 0, 0, 0, 0, gfx_lcdWidth, gfx_lcdHeight);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
