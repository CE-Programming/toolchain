#include <graphx.h>
#include <keypadc.h>
#include <textioc.h>

void setup_gfx_textio(void);
void switch_keymaps(uint24_t *ids);
void display_keymap_indicator(uint24_t *ids, uint8_t color);

void main(void) {

	/* Pointers to the Input Data Structures (IDS) that will
	   hold the input data. */
	uint24_t *ids_master, *ids_one, *ids_two;
	sk_key_t key = 0;
	uint8_t color;

	/* Setup the graphics */
	gfx_Begin();

	/* Set TextIOC to use GraphX. */
	setup_gfx_textio();

	/* Create two new IDS that will each hold 10 characters and will
	   use TextIOC's uppercase and lowercase keymaps. */
	textio_CreateAlphaIDS(ids_one, 10, 50, 51, 80);
	textio_CreateAlphaIDS(ids_two, 10, 50, 102, 80);

	/* Return if a memory error occurred. */
	if (ids_one == NULL || ids_two == NULL)
		goto ERROR;

	/* Configure each IDS's cursors. */
	textio_SetCursorColor(ids_one, 0x00);
	textio_SetCursorColor(ids_two, 0x00);
	textio_SetCursorDimensions(ids_one, 1, 9);
	textio_SetCursorDimensions(ids_two, 1, 9);
	textio_SetCursorY(ids_one, 50);
	textio_SetCursorY(ids_two, 101);

	/* Increase the cursor blink rate. */
	textio_SetCursorBlinkRate(10);

	/* Set the first active IDS. */
	ids_master = ids_one;
	textio_LockIDS(ids_two, true);

	/* Get input until the user presses [enter] */
	do {
		/* Draw boxes around the input fields and the keymap indicators
		   based on the IDS_Lock status for each IDS. */
		color = 0x00;
		if (textio_GetIDSLock(ids_one))
			color = 0xb5;
		gfx_SetColor(color);
		gfx_Rectangle_NoClip(48, 48, 104, 13);
		display_keymap_indicator(ids_one, color);

		color = 0x00;
		if (textio_GetIDSLock(ids_two))
			color = 0xb5;
		gfx_SetColor(color);
		gfx_Rectangle_NoClip(48, 99, 104, 13);
		display_keymap_indicator(ids_two, color);

		key = textio_Input(ids_master);

		/* Switch keymaps if the user presses [alpha] */
		if (key == sk_Alpha)
			switch_keymaps(ids_master);

		/* Switch input fields if requested. */
		if (key == sk_Up) {
			textio_LockIDS(ids_two, true);
			textio_LockIDS(ids_one, false);
			ids_master = ids_one;
		};

		if (key == sk_Down) {
			textio_LockIDS(ids_one, true);
			textio_LockIDS(ids_two, false);
			ids_master = ids_two;
		};

	} while (key != sk_Enter);

	/* Delete both IDSes. */
	textio_DeleteIDS(ids_one);
	textio_DeleteIDS(ids_two);

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

	return;
}

void display_keymap_indicator(uint24_t *ids, uint8_t color) {

	uint8_t cursor_y;
	char indicator;

	/* Get the cursor's y-position. */
	cursor_y = textio_GetCursorY(ids);

	/* Get the character that acts as the current keymap's indicator. */
	indicator = textio_GetCurrKeymapIndicator(ids);

	/* Draw the indicator. */
	gfx_FillRectangle_NoClip(139, cursor_y - 1, 12, 11);

	gfx_SetTextBGColor(color);
	gfx_SetTextFGColor(0xFF);
	gfx_SetTextTransparentColor(color);
	gfx_SetTextXY(154 - gfx_GetCharWidth(indicator) - 4, cursor_y + 1);
	gfx_PrintChar(indicator);

	/* Reset the font colors */
	gfx_SetTextBGColor(0xFF);
	gfx_SetTextFGColor(0x00);
	gfx_SetTextTransparentColor(0xFF);

	return;
}