#include "fonts/fonts.h"

#include <graphx.h>
#include <fontlibc.h>
#include <textioc.h>

void main(void) {

	char text[] = {"\tThis line starts with a tab.\n\nA demonstration of multiple newline breaks.\n\n\tWhen did indenting paragraphs become a common standard? Did it start with Gutenburg or did someone else invent it in the following centuries after the printing press's invention?\n\t\tDouble tabbing also helps set your text further away from the left margin. Tabs in your text while printing centered, however, makes it look off-centered."};

	/* Start the graphics */
	gfx_Begin();

	/* Load the font */
	fontlib_SetFont(test_font, 0);
	fontlib_SetLineSpacing(2, 2);

	/* Set the text window dimensions*/
	fontlib_SetWindow(5, 0, 310, 240);
	fontlib_SetColors(0x00, 0xFF);
	fontlib_HomeUp();

	/* Set print format to left-margin flush */
	textio_SetPrintFormat(TEXTIOC_PRINT_LEFT_MARGIN_FLUSH);

	/* Set the number of spaces that make up the tab */
	textio_SetTabSize(5);

	/* Print the text */
	textio_PrintText(text, 5);

	/* Outline the window so we can see it */
	gfx_SetColor(224);
	gfx_Rectangle_NoClip(5, 0, 310, 240);

	/* Wait for keypress */
	while (!os_GetCSC());

	/* Close the graphics */
	gfx_End();
	exit(0);
}