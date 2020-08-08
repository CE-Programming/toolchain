#include <graphx.h>
#include <keypadc.h>
#include <textioc.h>

void setup_gfx_textio(void);
void print_timer(uint24_t *ids);
void display_keymap_indicator(uint24_t *ids);

void main(void) {

	/* Pointer to the Input Data Structure (IDS) that will
	   hold the input data */
	uint24_t *ids;

	sk_key_t key = 0;

	/* Setup the graphics */
	gfx_Begin();

	/* Set the TextIOC source library to GraphX. */
	setup_gfx_textio();

	/* Create a new IDS that will hold 10 characters and will
	   use TextIOC's numerical keymap. */
	textio_CreateNumericalIDS(ids, 10, 50, 51, 80);

	/* Return if a memory error occured. */
	if (ids == NULL)
		goto ERROR;

	/* Draw a box around the input field so it can be more easily seen. */
	gfx_SetColor(0x00);
	gfx_Rectangle_NoClip(48, 48, 104, 13);

	/* Configure the cursor. */
	textio_SetCursorColor(ids, 0x00);
	textio_SetCursorDimensions(ids, 1, 9);
	textio_SetCursorY(ids, 50);

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

void setup_gfx_textio(void) {

	/* Setup the GraphX wrapper. */
	textio_library_routines_t routines = TEXTIO_GRAPHX_ROUTINES;

	/* Pass the wrapper pointers to TextIOC. */
	textio_SetLibraryRoutines(&routines);
	return;
}

void print_timer(uint24_t *ids) {

	uint24_t time;

	gfx_SetTextXY(50, 30);
	gfx_PrintString("Time left: ");

	/* Erase the previous time. */
	gfx_SetColor(0xFF);
	gfx_FillRectangle_NoClip(112, 30, 20, 9);

	/* Get IDS timer and print it. */
	time = textio_GetIDSTimer(ids);
	gfx_PrintUInt(time, 2);

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
	gfx_PrintChar(indicator);

	/* Reset the font colors */
	gfx_SetTextBGColor(0xFF);
	gfx_SetTextFGColor(0x00);
	gfx_SetTextTransparentColor(0xFF);

	return;
}