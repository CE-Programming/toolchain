#include "fonts.h"

static unsigned char test_font_data[] =
{
    #include "testfont.inc"
};

fontlib_font_t *test_font = (fontlib_font_t *)test_font_data;
