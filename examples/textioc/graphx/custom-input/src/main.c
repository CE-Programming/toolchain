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

	/* Pointers to the custom keymaps. */
	char *keymap1, *keymap2;

	/* Setup the graphics. */
	gfx_Begin();

	/* Instruct TextIOC to use the GraphX library. */
	setup_gfx_textio();

	/* Create an IDS that will hold 20 characters and use 2 keymaps. */
	ids = textio_CreateIDS(20, 50, 51, 88, 2);

	/* Return if a memory error occurred. */
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
	gfx_Rectangle_NoClip(48, 48, 104, 13);

	/* Configure the cursor. */
	textio_SetCursorColor(ids, 0x00);
	textio_SetCursorDimensions(ids, 1, 9);
	textio_SetCursorY(ids, 50);

	/* Get input until the user presses [enter]. */
	do {
		display_keymap_indicator(ids);

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

void setup_gfx_textio(void) {

	/* Setup the GraphX wrapper. */
	textio_library_routines_t routines = TEXTIO_GRAPHX_ROUTINES;

	/* Pass the wrapper pointers to TextIOC. */
	textio_SetLibraryRoutines(&routines);
	return;
}

void switch_keymaps(uint24_t *ids) {

	uint8_t curr_keymap_num;

	/* Get the current keymap number. */
	curr_keymap_num = textio_GetCurrKeymapNum(ids);

	/* Go to the next keymap. */
	if (curr_keymap_num < textio_GetNumKeymaps(ids)) {
		curr_keymap_num++;
	} else {
		/* The number of the first IDS keymap is 0. */
		curr_keymap_num = 0;
	};

	textio_SetCurrKeymapNum(ids, curr_keymap_num);

	return;
}

void display_keymap_indicator(uint24_t *ids) {

	uint8_t cursor_y;
	char indicator;

	/* Get the cursor's y-position. */
	cursor_y = textio_GetCursorY(ids);

	/* Get the character that acts as the current keymap's indicator. */
	indicator = textio_GetCurrKeymapIndicator(ids);

	/* Draw the indicator. */
	gfx_SetColor(0x00);
	gfx_FillRectangle_NoClip(139, cursor_y - 1, 12, 11);

	gfx_SetTextBGColor(0x00);
	gfx_SetTextFGColor(0xFF);
	gfx_SetTextTransparentColor(0x00);
	gfx_SetTextXY(154 - gfx_GetCharWidth(indicator) - 4, cursor_y + 1);
	gfx_PrintChar(indicator);

	/* Reset the font colors. */
	gfx_SetTextBGColor(0xFF);
	gfx_SetTextFGColor(0x00);
	gfx_SetTextTransparentColor(0xFF);

	return;
}