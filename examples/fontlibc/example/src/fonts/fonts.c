#include "fonts.h"

/* This contains the raw data for the font. */
static const unsigned char test_font_data[] =
{
	#include "testfont.inc"
};

/* However, C89 does not allow us to typecast a byte array into a
fontlib_font_t pointer directly, so we have to use a second statement to do it,
though helpfully we can at least do it in the global scope. */
const fontlib_font_t *test_font = (fontlib_font_t *)test_font_data;
