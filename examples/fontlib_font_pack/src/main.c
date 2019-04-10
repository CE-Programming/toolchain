#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <fileioc.h>
#include <fontlibc.h>

/* Main Function */
void main(void) {
    char *title = " FONTLIBC ";
    char *font_pack_name = "HELVE";
    fontlib_font_t *font_pack;
    gfx_Begin();
    /* Erase the screen to black */
    gfx_FillScreen(gfx_black);
    fontlib_SetWindowFullScreen();
    fontlib_SetCursorPosition(1, 1);
    fontlib_SetColors(0xC0, 0x20);
    fontlib_SetTransparency(true);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    
    /* Set a font to use. */
    font_pack = fontlib_GetFontByIndex(font_pack_name, 4);
    
    if (font_pack) {
        fontlib_SetFont(font_pack, 0);
        fontlib_DrawString("Hello, world! A much longer test string!");
    }
    

    /* Pause */
    while (!os_GetCSC());

    /* Finish the graphics */
    gfx_End();
}
