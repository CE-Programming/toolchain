#include <graphx.h>
#include <textioc.h>
#include <debug.h>

void setup_gfx_textio(void);

void main(void) {

	char text[] = {"\tThis line starts with a tab. The text window dimensions are 140 pixels wide by 240 pixels tall. The initial text position is (0, 0). When the text reaches the bottom of the text window, any text that will not fit will be truncated."};

	/* Start the graphics. */
	gfx_Begin();

	/* Setup source library. */
	setup_gfx_textio();

	/* Preliminary configuration. */
	textio_SetFontHeight(8);
	textio_SetLineSpacing(1, 1);

	/* Set the text window dimensions. */
	textio_SetTextWindow(0, 0, 140, 240);

	/* Set print format to left-margin flush. */
	textio_SetPrintFormat(TEXTIOC_PRINT_LEFT_MARGIN_FLUSH);

	/* Set the number of spaces that make up the tab. */
	textio_SetTabSize(5);

	/* Print the text. */
	textio_PrintText(text, 5);

	/* Print the second window's text. */
	gfx_PrintStringXY("This line is printed", 160, 5);
	gfx_PrintStringXY("without using the", 160, 15);
	gfx_PrintStringXY("TextIOC library. It is", 160, 25);
	gfx_PrintStringXY("a demonstration of", 160, 35);
	gfx_PrintStringXY(" being able to use the", 160, 45);
	gfx_PrintStringXY("source library's", 160, 55);
	gfx_PrintStringXY("functions", 160, 65);
	gfx_PrintStringXY("independantly of", 160, 75);
	gfx_PrintStringXY("TextIOC while a", 160, 85);
	gfx_PrintStringXY("TextIOC text window", 160, 95);
	gfx_PrintStringXY("is active.", 160, 105);

	/* Outline each window. */
	gfx_SetColor(224);
	gfx_Rectangle_NoClip(0, 0, 140, 240);
	gfx_Rectangle_NoClip(160, 0, 150, 240);

	/* Wait for keypress. */
	while (!os_GetCSC());

	/* Close the graphics. */
	gfx_End();
	exit(0);
}

void setup_gfx_textio(void) {

	/* Setup the GraphX wrapper. */
	textio_library_routines_t routines = TEXTIO_GRAPHX_ROUTINES;

	/* Pass the wrapper pointers to TextIOC. */
	textio_SetLibraryRoutines(&routines);
	return;
}