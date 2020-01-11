#include <tice.h>
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
        gfx_FillRectangle_NoClip(c * (LCD_WIDTH / 8), 0, LCD_WIDTH / 8, LCD_HEIGHT);
    }

    /* Waits for a key */
    while (!os_GetCSC());

    /* Copy part of the drawn gradient to the visible screen */
    gfx_CopyRectangle(gfx_buffer, gfx_screen, LCD_WIDTH / 4, LCD_HEIGHT / 4, LCD_WIDTH / 4, LCD_HEIGHT / 4, LCD_WIDTH / 2, LCD_HEIGHT / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* This is the same as gfx_SetDraw(gfx_screen) */
    gfx_SetDrawScreen();

    /* Draw a gradient (to the screen) */
    for (c = 16; c < 24; c++)
    {
        gfx_SetColor(c);
        gfx_FillRectangle_NoClip((c - 16) * (LCD_WIDTH / 8), 0, LCD_WIDTH / 8, LCD_HEIGHT);
    }

    /* Copy part of the drawn gradient to the offscreen buffer */
    gfx_CopyRectangle(gfx_screen, gfx_buffer, LCD_WIDTH / 4, LCD_HEIGHT / 4, LCD_WIDTH / 4, LCD_HEIGHT / 4, LCD_WIDTH / 2, LCD_HEIGHT / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Copy the offscreen buffer to the visible screen */
    /* Same as gfx_BlitBuffer() */
    gfx_CopyRectangle(gfx_buffer, gfx_screen, 0, 0, 0, 0, LCD_WIDTH, LCD_HEIGHT);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
