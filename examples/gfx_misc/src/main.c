#include <tice.h>
#include <graphx.h>
#include <stdint.h>

/* Main function */
void main(void) {

    static const uint8_t char_data[8] = { 0xaa, 0x55, 0xff, 0x00, 0xaa, 0x55, 0xff, 0x00 };

    /* Start the graphics canvas */
    gfx_Begin();

    /* Fill the screen with black color */
    gfx_FillScreen(0);

    /* Draw to the offscreen buffer */
    gfx_SetDrawBuffer();

    /* Fill the buffer with white color */
    gfx_FillScreen(255);

    /* Draw a red rectangle outline */
    gfx_SetColor(224);
    gfx_Rectangle(30, 20, 40, 50);

    /* Copy the drawn rectangle */
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 30, 20, 80, 20, 40, 50);

    /* Copy the drawn rectangles to the visible screen */
    gfx_CopyRectangle(gfx_buffer, gfx_screen, 30, 20, 30, 20, 90, 50);

    /* Copy the drawn rectangles on the visible screen to the buffer */
    gfx_CopyRectangle(gfx_screen, gfx_buffer, 30, 20, 30, 110, 90, 50);

    /* Attempt to change a character */
    gfx_SetCharData('a', char_data);
    gfx_PrintStringXY("aaa", 0, 0);

    /* Wait for key input */
    while (!os_GetCSC());

    /* Copy the whole buffer to the visible screen */
    gfx_BlitBuffer();

    /* Wait for key input */
    while (!os_GetCSC());

    /* End the graphics canvas */
    gfx_End();
}

