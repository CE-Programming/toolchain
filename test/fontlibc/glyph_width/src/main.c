#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/sprintf.h>
#include <stdio.h>
#include <stdint.h>
#include <graphx.h>
#include <fontlibc.h>

#include "fonts/fonts.h"

#include "truth.h"

#define C(expr) if (!(expr)) { return __LINE__; }

int run_tests(void) {

    /* 256 glyph test */
    fontlib_SetFont(test_font, 0);
    C(fontlib_GetFirstGlyph() == 0);
    C(fontlib_GetTotalGlyphs() == 256);
    C(fontlib_GetTotalGlyphs() == 256);
    for (unsigned i = 0; i <= 255; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == truth_width[i - 0]);
    }

    /* 255 glyph test */
    test_font->first_glyph = 1;
    test_font->total_glyphs = 255;
    fontlib_SetFont(test_font, 0);
    C(fontlib_GetFirstGlyph() == 1);
    C(fontlib_GetTotalGlyphs() == 255);
    C(fontlib_GetGlyphWidth(0) == 0);
    for (unsigned i = 1; i <= 255; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == truth_width[i - 1]);
    }

    /* 128 glyph test */
    test_font->first_glyph = 0;
    test_font->total_glyphs = 128;
    fontlib_SetFont(test_font, 0);
    C(fontlib_GetFirstGlyph() == 0);
    C(fontlib_GetTotalGlyphs() == 128);
    for (unsigned i = 0; i <= 127; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == truth_width[i - 0]);
    }
    for (unsigned i = 128; i <= 255; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == 0);
    }

    /* 64 glyph test */
    test_font->first_glyph = 32;
    test_font->total_glyphs = 64;
    fontlib_SetFont(test_font, 0);
    C(fontlib_GetFirstGlyph() == 32);
    C(fontlib_GetTotalGlyphs() == 64);
    for (unsigned i = 0; i <= 31; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == 0);
    }
    for (unsigned i = 32; i <= 95; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == truth_width[i - 32]);
    }
    for (unsigned i = 96; i <= 255; i++) {
        uint8_t width = fontlib_GetGlyphWidth((uint8_t)i);
        C(width == 0);
    }

    return 0;
}

int main(void) {
    gfx_Begin();
    int failed_test = run_tests();
    gfx_End();

    os_ClrHome();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
