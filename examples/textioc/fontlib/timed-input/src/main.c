#include "fonts/fonts.h"

#include <graphx.h>
#include <fontlibc.h>
#include <keypadc.h>
#include <textioc.h>

void setup_fontlib_textio(void);
void print_timer(uint24_t *ids);
void display_keymap_indicator(uint24_t *ids);

void main(void) {

	/* Pointer to the Input Data Structure (IDS) that will
	   hold the input data. */
	uint24_t *ids;

	sk_key_t key = 0;

	/* Setup the graphics */
	gfx_Begin();

	/* Setup our custom FontLibC font */
	fontlib_SetFont(test_font, 0);
	fontlib_SetColors(0x00, 0xFF);

	/* Set FontLibC as TextIOC's source library. */
	setup_fontlib_textio();

	/* Create a new IDS that will hold 10 characters and will
	   use TextIOC's numerical keymap. */
	textio_CreateNumericalIDS(ids, 10, 50, 50, 80);

	/* Return if a memory error occurred. */
	if (ids == NULL)
		goto ERROR;

	/* Draw a box around the input field so it can be more easily seen. */
	gfx_SetColor(0x00);
	gfx_Rectangle_NoClip(48, 48, 104, 17);

	/* Set the cursor color. */
	textio_SetCursorColor(ids, 0x00);

	/* Setting the cursor's height to the height of the current font ensures
	   that the cursor will be tall enough. */
	textio_SetCursorDimensions(ids, 1, fontlib_GetCurrentFontHeight() - 1);

	/* Set the cursor y-position. */
	textio_SetCursorY(ids, textio_GetIDSY(ids));

	/* Set the amount time in which the user can enter input.
	   The amount is in seconds. */
	textio_SetIDSTimer(ids, 20);

	/* Get input until the user presses [enter] or until the timer expires. */
	do {
		display_keymap_indicator(ids);

		key = textio_TimedInput(ids);

		print_timer(ids);

	} while (key != sk_Enter && textio_GetIDSTimer(ids) > 0);

	/* Delete the IDS. It is very important to call this function
	   when you are through with an IDS */
	textio_DeleteIDS(ids);

	/* Wait for keypress */
	while (!os_GetCSC());

	ERROR:
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

void print_timer(uint24_t *ids) {

	uint24_t time;

	fontlib_SetCursorPosition(50, 30);
	fontlib_DrawString("Time left: ");

	/* Get IDS timer and print it. */
	time = textio_GetIDSTimer(ids);
	fontlib_DrawUInt(time, 2);

	return;
}

void display_keymap_indicator(uint24_t *ids) {

	uint8_t cursor_y;
	char indicator;

	/* Get the cursor's y-position. */
	cursor_y = textio_GetIDSY(ids);

	/* Get the character that acts as the current keymap's indicator. */
	indicator = textio_GetCurrKeymapIndicator(ids);

	/* Draw the indicator. */
	gfx_SetColor(0x00);
	gfx_FillRectangle_NoClip(151 - fontlib_GetGlyphWidth(indicator) - 4, cursor_y - 1, fontlib_GetGlyphWidth(indicator) + 4, fontlib_GetCurrentFontHeight() + 1);

	fontlib_SetColors(0xFF, 0x00);
	fontlib_SetCursorPosition(154 - fontlib_GetGlyphWidth(indicator) - 4, cursor_y);
	fontlib_DrawGlyph(indicator);

	/* Reset the font colors */
	fontlib_SetColors(0x00, 0xFF);

	return;
}