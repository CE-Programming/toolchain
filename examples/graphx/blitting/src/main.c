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
        gfx_FillRectangle_NoClip(c * (GFX_LCD_WIDTH / 8), 0, GFX_LCD_WIDTH / 8, GFX_LCD_HEIGHT);
    }

    /* Waits for a key */
    while (!os_GetCSC());

    /* Copy parts of the buffer to the screen */
    gfx_BlitLines(gfx_buffer, GFX_LCD_HEIGHT - 32, 32);
    gfx_BlitRectangle(gfx_buffer, GFX_LCD_WIDTH / 4, GFX_LCD_HEIGHT / 4, GFX_LCD_WIDTH / 2, GFX_LCD_HEIGHT / 2);

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
