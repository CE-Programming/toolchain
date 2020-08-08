#include <graphx.h>
#include <keypadc.h>
#include <textioc.h>

void setup_gfx_textio(void);
void switch_keymaps(uint24_t *ids);
void display_keymap_indicator(uint24_t *ids);
void print_theta_char(void);

void main(void) {

	/* Pointer to the Input Data Structure (IDS) that will
	   hold the input data */
	uint24_t *ids;

	sk_key_t key = 0;
	char *name;

	/* Setup the graphics */
	gfx_Begin();

	/* Set GraphX as TextIOC's source library. */
	setup_gfx_textio();

	/* Create a new IDS that will hold 8 characters and will
	   use TextIOC's program_name letter keymaps as well its numerical keymap. */
	textio_CreatePrgmNameIDS(ids, 8, 50, 51, 80);

	/* Return if a memory error occured. */
	if (ids == NULL)
		goto ERROR;

	/* Set the codepoint that will stand for the theta character. */
	textio_SetThetaCodepoint(0x40);

	/* Give the pointer to the theta character drawing function to TextIOC. */
	textio_SetDrawThetaCharFunction(&print_theta_char);

	/* Draw a box around the input field so it can be more easily seen. */
	gfx_SetColor(0x00);
	gfx_Rectangle_NoClip(48, 48, 104, 13);

	/* Configure the cursor. */
	textio_SetCursorColor(ids, 0x00);
	textio_SetCursorDimensions(ids, 1, 9);
	textio_SetCursorY(ids, 50);

	/* Get input until the user presses [enter] */
	do {
		display_keymap_indicator(ids);

		key = textio_Input(ids);

		/* Switch keymaps if the user presses [alpha] */
		if (key == sk_Alpha)
			switch_keymaps(ids);

	} while (key != sk_Enter);

	/* Convert the program/appvar name into a TI-OS format. */
	name = textio_ConvertProgramAppvarName_TIOS(textio_GetDataBufferPtr(ids));

	/* Draw the converted name */
	gfx_SetTextXY(1, 1);
	gfx_PrintString("Converted name: ");
	gfx_PrintString(name);

	/* Delete the IDS. It is very important to call this function
	   when you are through with an IDS */
	textio_DeleteIDS(ids);

	/* Wait for keypress */
	while (!os_GetCSC());

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
	gfx_SetTextXY(150 - gfx_GetCharWidth(indicator), cursor_y + 1);

	if (indicator == textio_GetThetaCodepoint())
		print_theta_char();
	else
		gfx_PrintChar(indicator);

	/* Reset the font colors */
	gfx_SetTextBGColor(0xFF);
	gfx_SetTextFGColor(0x00);
	gfx_SetTextTransparentColor(0xFF);

	return;
}

void print_theta_char(void) {
	gfx_PrintChar('O');
	gfx_SetColor(gfx_GetPixel(gfx_GetTextX() - 3, gfx_GetTextY()));
	gfx_Line_NoClip(gfx_GetTextX() - 7, gfx_GetTextY() + 3, gfx_GetTextX() - 4, gfx_GetTextY() + 3);
}