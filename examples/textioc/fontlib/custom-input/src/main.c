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
	   hold the input data */
	uint24_t *ids;

	sk_key_t key = 0;

	/* Pointers to the custom keymaps. */
	char *keymap1, *keymap2;

	/* Setup the graphics */
	gfx_Begin();

	/* Setup our custom FontLibC font */
	fontlib_SetFont(test_font, 0);
	fontlib_SetColors(0x00, 0xFF);

	/* Set FontLibC as TextIOC's source library. */
	setup_fontlib_textio();

	/* Create an IDS that will hold 20 characters and use 2 keymaps. */
	ids = textio_CreateIDS(20, 50, 50, 88, 2);

	/* Return if a memory error occured. */
	if (ids == NULL)
		goto ERROR;

	/* Create two keymaps. */
	keymap1 = textio_CreateKeymap('A', "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0");
	keymap2 = textio_CreateKeymap('a', "\0\0\0\0\0\0\0\0\0\0\"wrmh\0\0?[vqlg\0\0:zupkfc\0 ytojeb\0\0xsnida\0\0\0\0\0\0\0\0");

	/* Set the two custom keymaps as the IDS keymaps. */
	textio_SetKeymaps(ids, 2, keymap1, keymap2);

	/* Determine which keymap that textio_Input should use first. */
	textio_SetCurrKeymapNum(ids, 0);

	/* Draw a box around the input field so it can be more easily seen. */
	gfx_SetColor(0x00);
	gfx_Rectangle_NoClip(48, 48, 104, 18);

	/* Set the cursor color. */
	textio_SetCursorColor(ids, 0x00);

	/* Setting the cursor's height to the height of the current font ensures
	   that the cursor will be tall enough. */
	textio_SetCursorDimensions(ids, 1, fontlib_GetCurrentFontHeight());

	/* Set cursor y-position. */
	textio_SetCursorY(ids, textio_GetIDSY(ids));

	/* Get input until the user presses [enter] */
	do {
		display_keymap_indicator(ids);

		key = textio_Input(ids);

		/* Switch keymaps if the user presses [alpha] */
		if (key == sk_Alpha)
			switch_keymaps(ids);

	} while (key != sk_Enter);

	/* Delete the IDS. It is very important to call this function
	   when you are through with an IDS */
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

	/* Go to the next keymap. */
	if (curr_keymap_num < textio_GetNumKeymaps(ids)) {
		curr_keymap_num++;
	} else {
		/* The number of the first IDS keymap is 0 */
		curr_keymap_num = 0;
	};

	textio_SetCurrKeymapNum(ids, curr_keymap_num);

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
	gfx_FillRectangle_NoClip(151 - fontlib_GetGlyphWidth(indicator) - 4, cursor_y - 1, fontlib_GetGlyphWidth(indicator) + 4, fontlib_GetCurrentFontHeight() + 2);

	fontlib_SetColors(0xFF, 0x00);
	fontlib_SetCursorPosition(154 - fontlib_GetGlyphWidth(indicator) - 4, cursor_y + 1);
	fontlib_DrawGlyph(indicator);

	/* Reset the font colors */
	fontlib_SetColors(0x00, 0xFF);

	return;
}