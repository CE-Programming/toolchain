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

static const uint8_t test_font[] = {
	#include "testfont.inc"
};

void printCentered(char* string) {
    /* We're just using some simple math to find the center of the text window.
    Then we find the center of the text to be displayed and use math to make
    sure it ends up in the center of the window. */
    fontlib_SetCursorPosition(fontlib_GetWindowWidth() / 2 + fontlib_GetWindowXMin() - (fontlib_GetStringWidth(string) / 2), fontlib_GetCursorY());
    fontlib_DrawString(string);
}

/* Main Function */
void main(void) {
    char* title = " FONTLIBC ";
    gfx_Begin();
    /* Erase the screen to black */
    gfx_FillScreen(gfx_black);

    /* Disable pre-/post- line clearing */
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    /* Set a font to use.  DrawString will display garbage if you don't give it a font! */
    fontlib_SetFont(test_font, 0);

    /* First, we'll display centered text in a window */
    /* Add some vertical padding around our text */
    fontlib_SetLineSpacing(2, 2);
    fontlib_SetWindow(25, 40, 150, 40);
    fontlib_SetCursorPosition(25, 42);
    /* Set some random (and ugly) colors */
    fontlib_SetColors(0xC0, 0x20);
    fontlib_DrawString("The quick brown fox jumps over the lazy dog.");

    /* Pause */
    while (!os_GetCSC());

    /* Now erase everything in the text window so you don't see that dumb filler text! */
    fontlib_ClearWindow();
    /* . . . and move cursor back to top of text window */
    /* Note that since printCentered takes care of setting X for us, we can just set it to 0 here */
    fontlib_SetCursorPosition(0, fontlib_GetWindowYMin());
    /* Show transparency in action */
    fontlib_SetTransparency(true);
    printCentered("[A text window]\n");
    /* Now let's try some /different/ ugly colors! */
    fontlib_SetColors(0xF0, 0x10);
    fontlib_SetTransparency(false);
    printCentered(" Opaque text ");

    /* Now print some text in the exact center of the screen */
    fontlib_SetWindowFullScreen();
    fontlib_SetLineSpacing(0, 0);
    fontlib_SetCursorPosition(0, fontlib_GetWindowHeight() / 2 - fontlib_GetCurrentFontHeight() / 2);
    printCentered(title);

    /* Pause */
    while (!os_GetCSC());

    /* Finish the graphics */
    gfx_End();
}
