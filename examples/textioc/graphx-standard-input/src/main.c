#include <graphx.h>
#include <keypadc.h>
#include <textioc.h>

void setup_gfx_textio(void);
void switch_keymaps(uint24_t *ids);
void display_keymap_indicator(uint24_t *ids);

void main(void) {

	/* Pointer to the Input Data Structure (IDS) that will
	   hold the input data. */
	uint24_t *ids;
	sk_key_t key = 0;

	/* Start the graphics. */
	gfx_Begin();

	/* Setup TextIOC to use GraphX. */
	setup_gfx_textio();

	/* Create an IDS that will hold 10 characters and use
	   the uppercase and lowercase letter keymaps as well
	   as the numerical keymap. */
	textio_CreateAlphaNumericalIDS(ids, 10, 50, 51, 50);

	/* Return early if a memory error occurred. */
	if (ids == NULL)
		goto ERROR;

	/* Draw a box around the input field. */
	gfx_SetColor(0x00);
	gfx_Rectangle_NoClip(48, 48, 54, 13);

	/* Set the cursor configuration. */
	textio_SetCursorColor(ids, 0x00);
	textio_SetCursorDimensions(ids, 1, 9);
	textio_SetCursorY(ids, 50);

	do {
		key = textio_Input(ids);

		if (key == sk_Alpha)
			switch_keymaps(ids);

	} while (key != sk_Enter);

	/* Always delete any IDSes created before the program
	   exits. */
	textio_DeleteIDS(ids);

	ERROR:
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

void switch_keymaps(uint24_t *ids) {

	uint8_t curr_keymap_num;

	/* Get the current keymap number */
	curr_keymap_num = textio_GetCurrKeymapNum(ids);

	/* Go to the next keymap */
	if (curr_keymap_num < textio_GetNumKeymaps(ids)) {
		curr_keymap_num++;
	} else {
		/* The number of the first IDS keymap is 0 */
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

	/* Get current cursor x-position */
	cursor_x = textio_GetCurrCursorX();

	/* Get the cursor's y-position. */
	cursor_y = textio_GetCursorY(ids);

	/* Get the character that acts as the current keymap's indicator. */
	indicator = textio_GetCurrKeymapIndicator(ids);

	/* Draw the indicator. */
	gfx_SetColor(0x00);
	gfx_FillRectangle_NoClip(cursor_x, cursor_y, gfx_GetCharWidth(indicator) + 2, 9);

	gfx_SetTextBGColor(0x00);
	gfx_SetTextFGColor(0xFF);
	gfx_SetTextTransparentColor(0x00);
	gfx_SetTextXY(cursor_x + 1, cursor_y + 1);
	gfx_PrintChar(indicator);

	/* Pause */
	delay(200);

	/* Set the global color index to the cursor background color. */
	gfx_SetColor(textio_GetCursorBGColor());

	/* Erase the indicator. */
	gfx_FillRectangle_NoClip(cursor_x, cursor_y, gfx_GetCharWidth(indicator) + 4, 9);

	/* Reset the font colors */
	gfx_SetTextBGColor(0xFF);
	gfx_SetTextFGColor(0x00);
	gfx_SetTextTransparentColor(0xFF);

	return;
}