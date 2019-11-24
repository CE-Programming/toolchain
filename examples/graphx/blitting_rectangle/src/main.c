#include <tice.h>
#include <graphx.h>

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    /* Fill the screen */
    gfx_FillScreen(0);

    /* Draw to the offscreen buffer */
    gfx_SetDrawBuffer();

    /* Fill the buffer */
    gfx_FillScreen(255);

    /* Draw a rectangle outline */
    gfx_SetColor(224);
    gfx_Rectangle(30, 20, 40, 50);

    /* Copy the drawn rectangle */
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 30, 20, 80, 20, 40, 50);

    /* Copy the drawn rectangles to the visible screen */
    gfx_CopyRectangle(gfx_buffer, gfx_screen, 30, 20, 30, 20, 90, 50);

    /* Copy the drawn rectangles on the visible screen to the buffer */
    gfx_CopyRectangle(gfx_screen, gfx_buffer, 30, 20, 30, 110, 90, 50);

    /* Wait for key input */
    while (!os_GetCSC());

    /* Copy the whole buffer to the visible screen */
    gfx_BlitBuffer();

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
