#include "fonts/fonts.h"

#include <textioc.h>
#include <graphx.h>
#include <fontlibc.h>

#include <stdio.h>

void setup_fontlib_textio(void);

void main(void) {

	char text[] = {"\tThis line starts with a tab. The text window dimensions are 140 pixels wide by 240 pixels tall. The initial text position is (0, 0). When the text reaches the bottom of the text window, any text that will not fit will be truncated."};
	char text_two[] = {"This text is in a FontLib text window and printed without TextIOC functions. This demonstrates how the programmer can use any supporting library's functions seperately from TextIOC."};

	/* Start the graphics */
	gfx_Begin();

	/* Setup the custom font. */
	fontlib_SetFont(test_font, 0);

	/* Setup the source library. */
	setup_fontlib_textio();

	textio_SetFontHeight(fontlib_GetCurrentFontHeight());
	textio_SetLineSpacing(0, 0);

	/* Set the text window dimensions*/
	textio_SetTextWindow(0, 0, 140, 240);

	/* Set print format to left-margin flush */
	textio_SetPrintFormat(TEXTIOC_PRINT_LEFT_MARGIN_FLUSH);

	/* Set the number of spaces that make up the tab */
	textio_SetTabSize(5);

	/* Print the text in the TextIOC text window. */
	textio_PrintText(text, 0);

	/* Print the second text array in a FontLib text window. */
	fontlib_SetWindow(160, 0, 150, 240);
	fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
	fontlib_HomeUp();
	fontlib_DrawString(text_two);

	/* Outline the windows so we can see them. */
	gfx_SetColor(224);
	gfx_Rectangle_NoClip(0, 0, 140, 240);
	gfx_Rectangle_NoClip(160, 0, 150, 240);

	/* Wait for keypress */
	while (!os_GetCSC());

	/* Close the graphics */
	gfx_End();
	exit(0);
}

void setup_fontlib_textio(void) {


	/* Setup the FontLibC wrapper. */
	textio_library_routines_t routines = TEXTIO_FONTLIB_ROUTINES;

	/* Pass the wrapper pointers to TextIOC. */
	textio_SetLibraryRoutines(&routines);
	return;
}