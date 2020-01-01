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
#include "fonts/fonts.h"

void printCentered(const char *string) {
    /* We're just using some simple math to find the center of the text window.
    Then we find the center of the text to be displayed and use math to make
    sure it ends up in the center of the window. */
    fontlib_SetCursorPosition(fontlib_GetWindowWidth() / 2 + fontlib_GetWindowXMin() - (fontlib_GetStringWidth(string) / 2), fontlib_GetCursorY());
    fontlib_DrawString(string);
}

/* Main Function */
void main(void) {
    char *title = " FONTLIBC ";
    gfx_Begin();
    /* Erase the screen to black */
    gfx_FillScreen(gfx_black);

    /* Set a font to use.  DrawString will display garbage if you don't give it a font! */
    fontlib_SetFont(test_font, 0);
    
    /* First, we'll display centered text in a window */
    /* Add some vertical padding around our text */
    fontlib_SetLineSpacing(2, 2);
    fontlib_SetWindow(25, 40, 150, 40);
    fontlib_SetCursorPosition(25, 42);
    /* Set some random (and ugly) colors */
    fontlib_SetColors(0xC0, 0x20);
    /* This is a crazy combination of settings that you probably don't want to use in any real program, but we're using
    it here for testing purposes. */
    fontlib_SetTransparency(true);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP | FONTLIB_AUTO_CLEAR_TO_EOL | FONTLIB_PRECLEAR_NEWLINE);
    /* It's not as generic as Hello, world! */
    fontlib_DrawString("The quick brown fox jumps over the lazy dog.");
    /* Let's just test fontlib_ShiftCursorPosition for funsies while we're here */
    fontlib_ShiftCursorPosition(2, 2);
    fontlib_DrawGlyph('X');
    fontlib_SetTransparency(false);
    fontlib_ShiftCursorPosition(-20, -5);
    fontlib_DrawGlyph('Y');
    

    /* Pause */
    while (!os_GetCSC());

    /* Now erase everything in the text window so you don't see that dumb filler text! */
    fontlib_ClearWindow();
    /* . . . and move cursor back to top of text window */
    /* Note that since printCentered takes care of setting X for us, we can just set it to 0 here */
    fontlib_SetCursorPosition(0, fontlib_GetWindowYMin());
    /* Disable pre-/post- line clearing */
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    /* Show transparency in action */
    fontlib_SetTransparency(true);
    printCentered("[A text window]\n");
    /* Now let's try some /different/ ugly colors! */
    fontlib_SetColors(gfx_pink, gfx_blue);
    fontlib_SetTransparency(false);
    printCentered(" Opaque text ");

    /* Now print some text in the exact center of the screen */
    fontlib_SetWindowFullScreen();
    fontlib_SetLineSpacing(0, 0);
    fontlib_SetCursorPosition(0, fontlib_GetWindowHeight() / 2 - fontlib_GetCurrentFontHeight() / 2);
    printCentered(title);

    /* Pause */
    while (!os_GetCSC());
    
    /* Test scrolling */
    fontlib_SetWindow(25, 40, 150, 40);
    fontlib_HomeUp();
    fontlib_SetLineSpacing(2, 2);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP | FONTLIB_AUTO_SCROLL);
    fontlib_Newline();
    fontlib_Newline();
    fontlib_DrawString("Scrolled!");
    fontlib_ClearEOL();
    
    /* Pause */
    while (!os_GetCSC());

    /* Finish the graphics */
    gfx_End();
}
