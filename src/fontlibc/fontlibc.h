/**
 * @file
 * @authors DrDnar
 * @brief Provides improved font support.
 * 
 * FontLib was designed under a "mechanism not policy" sort of philosophy.
 * Rather than attempt to provide as many fancy features as a programmer could
 * want, FontLib tries to provide fast, basic routines that can be used to build
 * the additional functionality you want.  For example, word-wrap is not
 * directly provided, but can be implemented using fontlib_SetAlternateStopCode
 * and fontlib_GetStringWidth.  FontLib hopes to provide enough performance to
 * be usable in games, while providing powerful enough basic features for fancy
 * GUIs and document editors.
 * 
 * To assist in text layout, FontLib provides for a text window, which
 * automatically confines text to appear in a specific rectangular area of the
 * screen.  This feature may be useful for dialogs and scrolling large blocks of
 * text. Use fontlib_SetWindow to set the current window bounds.  Use
 * fontlib_SetNewlineOptions to control how fontlib_DrawString behaves when it
 * reaches the right edge of the text window.
 *
 * Implementing centered text, right-aligned text, and word wrap require being
 * able to compute the width of a word or string of text.  The routine
 * fontlib_GetStringWidth provides this functionality.
 * 
 * If you call fontlib_SetAlternateStopCode(' '), GetStringWidth and DrawString
 * will stop drawing on spaces, giving you a chance to check if the next word
 * will fit on screen.  You can use fontlib_GetLastCharacterRead() to find out
 * where GetStringWidth or DrawString stopped, and, after handling the space,
 * then pass that address (plus one) again to GetStringWidth or DrawString to
 * resume processing at where it left off before.
 *
 * Embedded control codes are a popular way of managing style and formatting
 * information in string.  FontLibC only natively recognizes two types of 
 * control code: NULL (0) as a stop code and a user-specified alternate stop
 * code, and a user-specified newline code (defaults to 0x0A---ASCII LF and
 * standard Linux style).  However, you can add your own control codes with
 * fontlib_SetFirstPrintableCodePoint.  When any code point less than the
 * first printable code point is encountered, FontLib stops string processing
 * and returns to allow you to handle the control code yourself using
 * fontlib_GetLastCharacterRead.
 * 
 * Part of providing high-performance is not painting a single pixel more than
 * once.  To assist with this goal, FontLib provides for both transparent and
 * opaque text backgrounds.  Use fontlib_SetTransparency(true) if you need to
 * paint text over a background other than a solid color.  If you turn
 * transparency off, however, FontLib will paint both background and foreground
 * pixels for you, eliminating the time needed to erase those pixels before
 * painting over that area.
 *
 * Since a block of text may not always be the same size, FontLib provides
 * fontlib_ClearEOL for erasing the remainder of a line of text without needing
 * to pad it with spaces.   This action can also be performed automatically
 * after embedded newlines in text and on normal wrapping with
 * fontlib_SetNewlineOptions.
 *
 * Additional blank vertical space around text can improve readability in large
 * blocks of text.  fontlib_SetLineSpacing allows you to set this behavior.
 * Fonts may specify default additional spacing that is automatically applied
 * when calling fontlib_SetFont.  In GUIs and games where the benefits of
 * legibility are outweighed by more aggressive use of vertical space, you can
 * force the default spacing to zero after using fontlib_SetFont with
 * fontlib_SetLineSpacing.
 * 
 */

#ifndef H_FONTLIBC
#define H_FONTLIBC

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FONTLIB_ENABLE_AUTO_WRAP = 0x01,
    FONTLIB_AUTO_CLEAR_TO_EOL = 0x02,
    FONTLIB_PRECLEAR_NEWLINE = 0x04
} fontlib_newline_options_t;

typedef enum {
    /* clear = sans-serif font */
    FONTLIB_SERIF = 0x01,
    /* If both are set, then assume there's no difference between oblique
     * and italic styles. */
    FONTLIB_OBLIQUE = 0x02,
    FONTLIB_ITALIC = 0x04,
    /* Chances are you're not using this library for monospaced fonts.
     * But if you are, you'll still have to provide a widths table where
     * every byte is the same. */
    FONTLIB_MONOSPACED = 0x08
} fontlib_styles_t;

typedef struct {
    /* These are standard C-strings.  These pointers may be NULL. */
    char *font_family_name;
    char *font_author;
    /* NOTA BENE: TYPEFACES AND BITMAPPED FONTS CANNOT BE COPYRIGHTED UNDER U.S. LAW!
     * This field is therefore referred to as a pseudocopyright.  HOWEVER,
     * it IS is applicable in other jusrisdictions, such as Germany. */
    char *font_pseudocopyright;
    char *font_description;
    char *font_version;
    char *font_codepage;
} fontlib_metadata_t;

typedef struct {
    /* Must be zero */
    uint8_t fontVersion;
    /* Height in pixels */
    uint8_t height;
    /* Total number of glyphs provided. */
    uint8_t total_glyphs;
    /* Number of first glyph.  If you have no codepoints below 32, for
       example, you can omit the first 32 bitmaps. */
    uint8_t first_glyph;
    /* Offset/pointer to glyph widths table.
     * This is an OFFSET from the fontVersion member in data format.
     * However, it is 24-bits long because it becomes a real pointer upon loading. */
    void *widths_table;
    /* Offset to a table of offsets to glyph bitmaps.
     * These offsets are only 16-bits each to save some space. */
    void *bitmaps;
    /* Specifies how much to move the cursor left after each glyph.
       Total movement is width - overhang.  Intended for italics. */
    uint8_t italic_space_adjust;
    /* These suggest adding blank space above or below each line of text.
       This can increase legibility. */
    uint8_t space_above;
    uint8_t space_below;
    /* Specifies the boldness of the font. 
       0x40: light
       0x80: regular
       0x90: medium
       0xC0: bold*/
    uint8_t weight;
    /* Specifies the style of the font.  See enum font_styles */
    uint8_t style;
    /* For layout, allows aligning text of differing fonts vertically.
       These count pixels going down, i.e. 0 means the top of the glyph. */
    uint8_t cap_height;
    uint8_t x_height;
    uint8_t baseline_height;
} fontlib_font_t;

typedef struct {
    char header[8]; /* "FONTPACK" */
    /* Offset from first byte of header */
    fontlib_metadata_t *metadata;
    /* Frankly, if you have more than 127 fonts in a pack, you have a
       problem. */
    uint8_t fontCount;
    fontlib_font_t font_list[1];
} fontlib_font_pack_t;


/**
 * Sets the bounds of the window all text will appear in to be the full screen.
 * This is the default.
 */
void fontlib_SetWindowFullScreen(void);

/**
 * Sets the bounds of the window all text will appear in.
 * 
 * Clipping of partial glyphs is not supported.  If a glyph, either horizontally
 * or vertically, does not fit in the text window, it will not be printed at all.
 * Behavior is undefined if the text cursor is positioned outside of the current
 * text window.
 * 
 * Changing this does not automatically move the text cursor into the window.
 * @param x_min X coord base
 * @param y_min Y coord base
 * @param width Width
 * @param height Height
 */
void fontlib_SetWindow(unsigned int x_min, uint8_t y_min, unsigned int width, uint8_t height);

/**
 * Returns the starting column of the current text window
 * @return Window X
 */
unsigned int fontlib_GetWindowXMin(void);

/**
 * Returns the starting row of the current text window
 * @return Window Y
 */
uint8_t fontlib_GetWindowYMin(void);

/**
 * Returns the width of the current text window
 * @return Window width
 */
unsigned int fontlib_GetWindowWidth(void);

/**
 * Returns the height of the current text window
 * @return Window height
 */
uint8_t fontlib_GetWindowHeight(void);

/**
 * Sets the cursor position.
 *
 * Behavior is undefined if the cursor is set outside of the text window.
 * @param x X
 * @param y Y
 */
void fontlib_SetCursorPosition(unsigned int x, uint8_t y);

/**
 * Returns the cursor column.
 * @return Current cursor X
 */
unsigned int fontlib_GetCursorX(void);

/**
 * Returns the cursor row.
 * @return Current cursor Y
 */
uint8_t fontlib_GetCursorY(void);

/**
 * Adds the given (x,y) to the cursor position.
 * Behavior is undefined if the resulting cursor position is offscreen.
 * 
 * Useful for tabbing, for example.
 * @param x x-shift
 * @param y y-shift
 */
void fontlib_ShiftCursorPosition(int x, int y);

/**
 * Sets the current font
 * @param font_data Pointer to font data
 * @param flags Information about how to process the font (unused)
 * @return Returns false if the font seems invalid for any reason
 * WARNING: If false is returned, no valid font is currently loaded and trying
 * to print will print garbage!
 */
bool fontlib_SetFont(const fontlib_font_t *font_data, unsigned int flags);

/**
 * Sets the current foreground color FontLibC will use for drawing.
 * This is NOT the same as GraphX's current color!
 * @param color New color to use
 */
void fontlib_SetForegroundColor(uint8_t color);

/**
 * Sets the current background color FontLibC will use for drawing.
 * This is NOT the same as GraphX's current color!
 * @param color New color to use
 */
void fontlib_SetBackgroundColor(uint8_t color);

/**
 * Sets the current colors FontLibC will use for drawing.
 * These are NOT the same as GraphX's current colors!
 * @param forecolor New foreground color to use
 * @param backcolor New background color to use
 */
void fontlib_SetColors(uint8_t forecolor, uint8_t backcolor);

/**
 * Returns the current foreground color FontLibC will use for drawing.
 * This is NOT the same as GraphX's current color!
 * @return Current foreground color
 */
uint8_t fontlib_GetForegroundColor(void);

/**
 * Returns the current background color FontLibC will use for drawing.
 * This is NOT the same as GraphX's current color!
 * @return Current background color
 */
uint8_t fontlib_GetBackgroundColor(void);

/**
 * Controls whether FontLibC will use a transparent background for text drawing
 * instead of the currently configured background color.
 * This has nothing to do with GraphX's configured transparent color
 * @param transparency true to make background transparent, false to use background color
 */
void fontlib_SetTransparency(bool transparency);

/**
 * Returns whether FontLibC will use a transparent background for text drawing
 * instead of the currently configured background color.
 * This has nothing to do with GraphX's configured transparent color
 * @return true if background will be transparent, false if background color will be used
 */
bool fontlib_GetTransparency(void);

/**
 * Controls hows much black space will be added above and below each line of
 * text.  If transparency is set, then the padding will not be overwritten with
 * the background color, but padding will still be added.  Padding space is
 * added at the time each glyph is drawn.
 * @param space_above Blank space padding to add above
 * @param space_below Blank space padding to add below
 */
void fontlib_SetLineSpacing(uint8_t space_above, uint8_t space_below);

/**
 * Returns current padding space above.
 * @return Current padding space above
 */
uint8_t fontlib_GetSpaceAbove(void);

/**
 * Returns current padding space below
 * @return Current padding space below
 */
uint8_t fontlib_GetSpaceBelow(void);

/**
 * Sets current spacing adjustment for italic text.  This causes the cursor to
 * be moved back a certain number of pixels after every glyph is drawn.  This
 * is only useful if transparency mode is set.
 * NOTE: Italics is currently untested!  (I haven't designed an italic font yet.)
 * @param italic_spacing_adjustment Pixels to move cursor backward after each glyph
 */
void fontlib_SetItalicSpacingAdjustment(uint8_t italic_spacing_adjustment);

/**
 * Returns current spacing adjustment for italic text.
 * @return Current spacing adjustment for italic text
 */
uint8_t fontlib_GetItalicSpacingAdjustment(void);

/**
 * Returns the height of the current font, INCLUDING space above/below
 * @return Height in pixels
 */
uint8_t fontlib_GetCurrentFontHeight(void);

/**
 * Tests whether the current font has the given code point
 * @param code_point Code point to test
 * @return true if code_point is in current font, false if not
 */
bool fontlib_ValidateCodePoint(char code_point);

/**
 * Returns the total number of printable glyphs in the font.
 * This can return 256; no valid font has 0 printable glyphs.
 * @return Total number of printable glyphs
 */
size_t fontlib_GetTotalGlyphs(void);

/**
 * Returns the code point of the first printable glyph.
 * Note that the C SDK makes char SIGNED by default, so you probably want to
 * typecast this to unsigned char before attempting any math with it.
 * @return First print glyph code point
 */
char fontlib_GetFirstGlyph(void);

/**
 * Allows you to set the code point that is recognized as being a new line code.
 * You can set this to zero to prevent new line code processing.  Note that if
 * FONTLIB_ENABLE_AUTO_WRAP is enabled, then wrapping will still implicitly
 * case a newline.
 * 
 * This defaults to 0x0A (ASCII line feed/UNIX newline)
 * @param code_point New code point to use for newline
 */
void fontlib_SetNewlineCode(char code_point);

/**
 * Returns the code point that is currently recognized as being a newline.
 * If 0, newlines in strings will not be processed.
 * @return Current newline
 */
char fontlib_GetNewlineCode(void);

/**
 * Sets an alternate code point to recognize as a stop code.
 * 
 * For example, you can set this to space to make DrawString and GetStringWidth
 * stop processing when they reach a space.
 * 
 * Set this to 0 if you do not want to use the alternate stop code feature.
 * 
 * NULL (0) will still be recognized as a stop code regardless of value.
 * 
 * Defaults to 0.
 * @param code_point Additional code point to recognize as a stop code.
 */
void fontlib_SetAlternateStopCode(char code_point);

/**
 * Returns the current alternate stop code.
 * @return Current alternate stop code.
 */
char fontlib_GetAlternateStopCode(void);

/**
 * Sets the first code point considered printable.
 * 
 * All code points before this will be considered control codes.
 * Setting this to 0 (NULL) will NOT cause NULL to be ignored.
 * 
 * This defaults 0x10.
 * @param code_point First printable code point
 */
void fontlib_SetFirstPrintableCodePoint(char code_point);

/**
 * Returns the first code point considered printable.
 * @return Current first printable code point
 */
char fontlib_GetFirstPrintableCodePoint(void);

/**
 * Returns the width of the given glyph
 * @param codepoint Codepoint to test
 * @return Width of glyph, 0 if invalid codepoint
 */
uint8_t fontlib_GetGlyphWidth(char codepoint);

/**
 * Returns the width of a string printed in the current font.
 * 
 * Stops processing when it encounters ANY control code or a codepoint not in
 * the current font.
 * @param str Pointer to string
 * @return Width of string
 */
size_t fontlib_GetStringWidth(const char *str);

/**
 * Returns the width of a string printed in the current font.
 * 
 * Stops processing when it encounters ANY control code or a codepoint not in
 * the current font, or when max_characters have been processed.
 * @param str Pointer to string
 * @param max_characters Maximum number of characters to process
 * @return Width of string
 */
size_t fontlib_GetStringWidthL(const char *str, size_t max_characters);

/**
 * Gets the location of the last character processed by GetStringWidth or 
 * DrawString
 * @return Pointer to character
 */
char *fontlib_GetLastCharacterRead(void);

/**
 * Returns 0 if DrawStringL or GetStringWidthL returned because max_characters
 * were processed.  Returns a non-zero number otherwise.
 * @return Either zero, or a non-zero number depending on the reason DrawStringL
 * or GetStringWidthL returned.
 */
size_t fontlib_GetCharactersRemaining(void);

/**
 * Draws a glyph.  This can even draw code points less than the code point
 * specified with fontlib_SetFirstPrintableCodePoint().  It can even draw code
 * point 0.
 * 
 * Nota bene: Although this does update the cursor X/Y positions, it does NOT
 * process window bounds at all!  (Maybe this should be FIXME?  On the other
 * hand, users may want this specifically so they can handle all their own
 * layout without the text window settings getting in their way.)
 * @param glyph Codepoint
 */
void fontlib_DrawGlyph(uint8_t glyph);

/**
 * Draws a string.
 * 
 * This stops drawing upon reaching NULL.  It will also stop if it encounters
 * the character code specified with fontlib_SetAlternateStopCode().  Note that
 * the check for the alternate stop code always takes place before drawing a
 * glyph, so if you need to also display the stop code character, you must
 * directly call fontlib_DrawGlyph to force display the character and increment
 * past it.
 * 
 * This will return when it reaches the right edge of the text window if
 * FONTLIB_ENABLE_AUTO_WRAP is turned off.
 * 
 * Newline codes will print regardless of whether FONTLIB_ENABLE_AUTO_WRAP is
 * enabled.  To disable parsing newline codes, use fontlib_SetNewlineCode(0);
 * 
 * THIS IS NOT REENTRANT (though if you need that, you're probably not using C)
 * @param str Pointer to string
 */
void fontlib_DrawString(const char *str);

/**
 * Draws a string, up to a maximum number of characters.
 * 
 * This is intended to be used if you only want a portion of a string printed,
 * (Or if you hate null-terminated strings and want length-prefixed strings
 * instead.  You still can't use NULLs though.)
 * 
 * THIS IS NOT REENTRANT (though if you need that, you're probably not using C)
 * @param str Pointer to string
 * @param max_characters Maximum number of characters to attempt to print, may
 * return early if some other condition requires returning
 */
void fontlib_DrawStringL(const char *str, size_t max_characters);

/**
 * Erases everything from the cursor to the right side of the text window
 * (End-Of-Line).  This ignores the transparent background flag.
 */
void fontlib_ClearEOL(void);

/**
 * Erases the entire current text window.  This ignores the transparent
 * background flag.  If background transparency is important, check
 * fontlib_GetTransparency() before calling this routine.
 */
void fontlib_ClearWindow(void);

/**
 * Performs a newline.  Pays attention to newline flags.
 */
void fontlib_Newline(void);

/**
 * Sets options for controlling newline behavior
 * @param options Flags setting newline behavior:
 * FONTLIB_ENABLE_AUTO_WRAP: Enables automatic wrapping at the end of the line
 * (this is per-glyph, not word-wrap);
 * FONTLIB_AUTO_CLEAR_TO_EOL: Clears the remainder of the line of text;
 * FONTLIB_PRECLEAR_NEWLINE: Clears the NEXT line of text, don't combine this
 * with AUTO_CLEAR because that just wastes CPU cycles.
 */
void fontlib_SetNewlineOptions(uint8_t options);

/**
 * Gets the current newline behavior options.
 * @return Current newline behavior options
 */
uint8_t fontlib_GetNewlineOptions(void);


#ifdef __cplusplus
}
#endif

#endif
