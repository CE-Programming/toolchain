#include "fonts/fonts.h"

#include <graphx.h>
#include <fontlibc.h>
#include <keypadc.h>
#include <textioc.h>

void setup_fontlib_textio(void);
void switch_keymaps(uint24_t *ids);
void display_keymap_indicator(uint24_t *ids);

void main(void) {

	/* Pointer to the Input Data Structure (IDS) that will
	   hold the input data. */
	uint24_t *ids;

	sk_key_t key = 0;

	/* Setup the graphics */
	gfx_Begin();

	/* Setup TextIOC to use FontLibC. */
	setup_fontlib_textio();

	/* Setup our custom FontLibC font. */
	fontlib_SetFont(test_font, 0);
	fontlib_SetColors(0x00, 0xFF);

	/* Create a new IDS that will hold 10 characters and will
	   use TextIOC's uppercase and lowercase letter keymaps as well
	   its numerical keymap. */
	textio_CreateAlphaNumericalIDS(ids, 10, 50, 50, 50);

	/* Return if a memory error occurred. */
	if (ids == NULL)
		goto ERROR;

	/* Draw a box around the input field so it can be more easily seen. */
	gfx_SetColor(0x00);
	gfx_Rectangle_NoClip(48, 48, 54, 18);

	/* Set the cursor color. */
	textio_SetCursorColor(ids, 0x00);

	/* Setting the cursor's height to the height of the current font ensures
	   that the cursor will be tall enough. */
	textio_SetCursorDimensions(ids, 1, fontlib_GetCurrentFontHeight());

	/* Set the cursor y-position. */
	textio_SetCursorY(ids, textio_GetIDSY(ids));

	/* Get input until the user presses [enter]. */
	do {
		key = textio_Input(ids);

		/* Switch keymaps if the user presses [alpha]. */
		if (key == sk_Alpha)
			switch_keymaps(ids);

	} while (key != sk_Enter);

	/* Delete the IDS. It is very important to call this function
	   when you are through with an IDS. */
	textio_DeleteIDS(ids);

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

void switch_keymaps(uint24_t *ids) {

	uint8_t curr_keymap_num;

	/* Get the current keymap number */
	curr_keymap_num = textio_GetCurrKeymapNum(ids);

	/* Go to the next keymap */
	if (curr_keymap_num < textio_GetNumKeymaps(ids)) {
		curr_keymap_num++;
	} else {
		/* The number of the first IDS keymap is 0. */
		curr_keymap_num = 0;
	};

	textio_SetCurrKeymapNum(ids, curr_keymap_num);
	display_keymap_indicator(ids);

	return;
}

void display_keymap_indicator(uint24_t *ids) {

	uint24_t cursor_x;
	uint8_t cursor_y;
	char indicator;

	/* Get current cursor x-position. */
	cursor_x = textio_GetCurrCursorX();

	/* Get the cursor's y-position. */
	cursor_y = textio_GetIDSY(ids);

	/* Get the character that acts as the current keymap's indicator. */
	indicator = textio_GetCurrKeymapIndicator(ids);

	/* Draw the indicator. */
	gfx_SetColor(0x00);
	gfx_FillRectangle_NoClip(cursor_x, cursor_y, fontlib_GetGlyphWidth(indicator) + 4, fontlib_GetCurrentFontHeight());

	fontlib_SetColors(0xFF, 0x00);
	fontlib_SetCursorPosition(cursor_x + 2, cursor_y + 1);
	fontlib_DrawGlyph(indicator);

	/* Set the global color index to the cursor background color. */
	gfx_SetColor(textio_GetCursorBGColor());

	/* Erase a small amount of overdraw caused by the font height. */
	gfx_Rectangle_NoClip(cursor_x + 1, cursor_y + fontlib_GetCurrentFontHeight(), fontlib_GetGlyphWidth(indicator) + 3, 1);

	/* Pause */
	delay(200);

	/* Erase the indicator. */
	gfx_FillRectangle_NoClip(cursor_x, cursor_y, fontlib_GetGlyphWidth(indicator) + 4, fontlib_GetCurrentFontHeight());

	/* Reset the font colors. */
	fontlib_SetColors(0x00, 0xFF);

	return;
}