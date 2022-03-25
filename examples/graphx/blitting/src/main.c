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

    /* Copy parts of the buffer to the screen */
    gfx_BlitLines(gfx_buffer, gfx_lcdHeight - 32, 32);
    gfx_BlitRectangle(gfx_buffer, gfx_lcdWidth / 4, gfx_lcdHeight / 4, gfx_lcdWidth / 2, gfx_lcdHeight / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Copy the full buffer to the screen */
    /* This is the same as gfx_Blit(gfx_buffer) */
    gfx_BlitBuffer();

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
