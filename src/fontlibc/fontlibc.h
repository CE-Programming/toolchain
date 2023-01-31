/**
 * @file
 * @brief Provides improved font support.
 *
 * @author DrDnar
 */

#ifndef _FONTLIBC_H
#define _FONTLIBC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Options for controlling newline behavior
 * @see fontlib_SetNewlineOptions
 */
typedef enum {
    /**
     * Enables automatic wrapping at the end of the line.
     * @note This is per-glyph; word warp is neither implemented nor planned
     */
    FONTLIB_ENABLE_AUTO_WRAP = 0x01,
    /**
     * Upon any newline, clears the remainder of the line of text.
     * @note Useful for printing over previously printed text when transparency
     * is turned off, as this means each pixel in a line of text need only be
     * visited once.
     */
    FONTLIB_AUTO_CLEAR_TO_EOL = 0x02,
    /**
     * Clears the NEXT line of text
     * @note Don't combine this with AUTO_CLEAR because that just wastes CPU
     * cycles due to erasing/drawing each pixel twice.
     */
    FONTLIB_PRECLEAR_NEWLINE = 0x04,
    /**
     * Enables automatic scrolling when a newline would push the cursor past the
     * bottom of the text window.  The cursor is left at the bottom left.
     * @note If PRECLEAR is not set, then the bottom line of text will not be
     * erased.
     */
    FONTLIB_AUTO_SCROLL = 0x08
} fontlib_newline_options_t;

/**
 * Options for controlling how SetFont functions.
 * @see fontlib_SetFont
 */
typedef enum {
    /**
     * If set, then the space above/below metrics specified in the font will be
     * ignored and set to zero.  You can still manually set them later.
     */
    FONTLIB_IGNORE_LINE_SPACING = 0x01
} fontlib_load_options_t;

/**
 * Options for selecting a font by style
 * @see fontlib_GetFontByStyle
 */
typedef enum {
    /**
     * Clear = sans-serif font
     */
    FONTLIB_SERIF = 0x01,
    /**
     * Oblique is slanted like italic text, but with the cursive-like styling.
     */
    FONTLIB_OBLIQUE = 0x02,
    /**
     * If both italic and oblique are set, then assume there's no difference
     * between oblique and italic styles.
     */
    FONTLIB_ITALIC = 0x04,
    /**
     * Monospaced font
     * @note Chances are you're not using this library for monospaced fonts.
     * But if you are, you'll still have to provide a widths table where
     * every byte is the same.
     * @note This is not enforced; a variable-width font can claim to be
     * monospaced!
     */
    FONTLIB_MONOSPACED = 0x08
} fontlib_styles_t;

/**
 * Options for selecting a font by weight
 * @see fontlib_GetFontByStyle
 */
typedef enum {
    FONTLIB_THIN = 0x20,
    FONTLIB_EXTRA_LIGHT = 0x30,
    FONTLIB_LIGHT = 0x40,
    FONTLIB_SEMILIGHT = 0x60,
    FONTLIB_NORMAL = 0x80,
    FONTLIB_MEDIUM = 0x90,
    FONTLIB_SEMIBOLD = 0xA0,
    FONTLIB_BOLD = 0xC0,
    FONTLIB_EXTRA_BOLD = 0xE0,
    FONTLIB_BLACK = 0xF0
} fontlib_weights_t;

/**
 * Contains references to various metadata strings.
 * @note Any or all of these offsets may be NULL.
 * @note These should be short null-terminated C strings, but this is not
 * enforced.  Check for malformed metadata!
 * @see fontlib_font_pack_t
 */
typedef struct fontlib_metadata_t {
    /**
     * Size of this struct, basically functions as a version field.
     * This does NOT include the lengths of the strings!
     */
    int24_t length;
    /**
     * A short, human-readable typeface name, such as "Times"
     */
    int24_t font_family_name;
    /**
     * A SHORT string naming the typeface designer.
     */
    int24_t font_author;
    /**
     * A SHORT copyright claim.
     * Do not try to include a complete license in here!  Space is limited!
     * @note Typefaces and bitmapped fonts cannot be copyrighted under US law.
     * This field is therefore referred to as a pseudocopyright.  HOWEVER,
     * it IS is applicable in other jusrisdictions, such as Germany. */
    int24_t font_pseudocopyright;
    /**
     * A BRIEF description of the font.
     */
    int24_t font_description;
    /**
     * @note This is a STRING, so while this should be something like "1.0.0.0"
     * it could also be something like "1 June 2019" or even "Hahaha versioning
     * is overrated!"
     */
    int24_t font_version;
    /**
     * Suggested values: "ASCII" "TIOS" "ISO-8859-1" "Windows 1252"
     * "Calculator 1252"
     */
    int24_t font_code_page;
} fontlib_metadata_t;

/**
 * This is the actual font format.  Directly reading from this struct is the
 * only way to read a font's cap_height, x_height, and baseline_height metrics.
 *
 * For example:
 * @code{.cpp}
 *  unsigned char baseline;
 *  fontlib_font_t *my_font = fontlib_GetFontByStyle("FONTPACK", 12, 12,
 *      FONTLIB_NORMAL, FONTLIB_NORMAL, FONTLIB_SERIF, 0);
 *  if (!my_font || !fontlib_SetFont(my_font))
 *      return;
 *  baseline = my_font->baseline_height;
 * @endcode
 * @note The font's width table and bitmaps table should appear directly after
 * this struct.  The struct does not contain a member for the data because
 * it is probably not useful for C code to parse the width or bitmap data
 * directly.
 */
typedef struct fontlib_font_t {
    /**
     * Version ID
     * @note This must be zero or the font will be rejected as invalid.
     */
    uint8_t fontVersion;
    /**
     * Height in pixels not including space above/below
     */
    uint8_t height;
    /**
     * Total number of glyphs provided.
     * @note If this is zero, then 256 glyphs are provided, not zero!
     */
    uint8_t total_glyphs;
    /**
     * Number of first glyph.  If you have no codepoints below 32, for
     * example, you can omit the first 32 bitmaps.
     */
    uint8_t first_glyph;
    /**
     * Offset/pointer to glyph widths table.
     * This is an OFFSET from the fontVersion member
     * @note It is 24-bits long because it becomes a real pointer upon loading.
     */
    int24_t widths_table;
    /**
     * Offset to a table of offsets to glyph bitmaps.
     * @note Parsing the bitmaps yourself is probably not useful.
     * @note These offsets are only 16-bits each to save some space.
     */
    int24_t bitmaps;
    /**
     * Specifies how much to move the cursor left after each glyph.
     * Total movement is width - overhang.
     * @note Intended for italics.
     */
    uint8_t italic_space_adjust;
    /**
     * These suggest adding blank space above or below each line of text.
     * @note This can be overridden
     * @note This can increase legibility while saving space for always-blank
     * lines.
     */
    uint8_t space_above;
    uint8_t space_below;
    /**
     * Specifies the boldness of the font.
     * @see fontlib_weights_t
     */
    uint8_t weight;
    /**
     * Specifies the style of the font.
     * @see fontlib_styles_t
     */
    uint8_t style;
    /**
     * For layout, allows aligning text of differing fonts vertically.
     * These count pixels going down, i.e. 0 means the top of the glyph.
     */
    uint8_t cap_height;
    uint8_t x_height;
    uint8_t baseline_height;
} fontlib_font_t;

/**
 * This is the format of a font pack appvar.
 * Parsing this directly is the only way to get metadata other than the typeface
 * name.
 * @code{.cpp}
 *  FILE font_pack_file;
 *  fontlib_font_pack_t *font_pack;
 *  fontlib_metadata_t *metadata;
 *  char *var_name;
 *  char *font_author;
 *  uint8_t *search_pos = NULL;
 *  // Just randomly select the first font pack found
 *  if ((var_name = ti_Detect(&search_pos, "FONTPACK")) == NULL)
 *      return;
 *  // Get font pack header
 *  font_pack_file = ti_Open(var_name, "r");
 *  font_pack = ti_GetDataPtr(font_pack_file);
 *  // Is metadata present?
 *  if (!font->metadata)
 *      return;
 *  if (EOF == ti_Seek(font->metadata, SEEK_SET, font_pack_file))
 *      return;
 *  // Is metadata semi-valid?
 *  metadata = ti_GetDataPtr(font_pack_file);
 *  if (metadata->length < sizeof(fontlib_metadata_t))
 *      return;
 *  // Get font's author
 *  if (!metadata->font_author)
 *      return;
 *  if (EOF == ti_Seek(metadata->font_author, SEEK_SET, font_pack_file))
 *      return;
 *  font_author = ti_GetDataPtr(font_pack_file);
 *  ti_Close(font_pack_file);
 * @endcode
 */
typedef struct fontlib_font_pack_t {
    /**
     * Must be "FONTPACK"
     * @note This is NOT null-terminated!
     */
    char header[8]; /* "FONTPACK" */
    /**
     * Offset from first byte of header
     */
    int24_t metadata;
    /**
     * Number of fonts present.  Should be greater than zero. . . .
     * @note Frankly, if you have more than 127 fonts in a pack, you have a
     * problem.
     */
    uint8_t fontCount;
    /**
     * Array of offsets to each individual font.
     * @note Despite being declared as a single element, this will be fontCount
     * elements long.
     */
    int24_t font_list[1];
} fontlib_font_pack_t;


/**
 * Sets the bounds of the window all text will appear in to be the full screen.
 * This is the default.
 */
void fontlib_SetWindowFullScreen(void);

/**
 * Sets the bounds of the window all text will appear in.
 * @note Clipping of partial glyphs is not supported.  If a glyph, either
 * horizontally or vertically, does not fit in the text window, it will not be
 * printed at all.
 * @note Behavior is undefined if the text cursor is positioned outside of the
 * current text window.
 * @warning Changing this does not automatically move the text cursor into the
 * window.
 * @param[in] x_min X coord base
 * @param[in] y_min Y coord base
 * @param[in] width Width
 * @param[in] height Height
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
 * @param[in] x X
 * @param[in] y Y
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
 * @note  Useful for tabbing, for example.
 * @warning Behavior is undefined if the resulting cursor position is offscreen.
 * @param[in] x x-shift
 * @param[in] y y-shift
 */
void fontlib_ShiftCursorPosition(int x, int y);

/**
 * Moves the cursor to the upper left corner of the text window.
 */
void fontlib_HomeUp();

/**
 * Moves the cursor back to the start of the current line.
 */
void fontlib_Home();

/**
 * Sets the current font
 * @param[in] font_data Pointer to font data
 * @param[in] flags Information about how to process the font (unused)
 * @return Returns false if the font seems invalid for any reason
 * @warning If false is returned, no valid font is currently loaded and trying
 * to print will print garbage!
 */
bool fontlib_SetFont(const fontlib_font_t *font_data, fontlib_load_options_t flags);

/**
 * Sets the current foreground color FontLibC will use for drawing.
 * @note This is NOT the same as GraphX's current color!
 * @param color New color to use
 */
void fontlib_SetForegroundColor(uint8_t color);

/**
 * Sets the current background color FontLibC will use for drawing.
 * @note This is NOT the same as GraphX's current color!
 * @param[in] color New color to use
 */
void fontlib_SetBackgroundColor(uint8_t color);

/**
 * Sets the current colors FontLibC will use for drawing.
 * @note These are NOT the same as GraphX's current colors!
 * @param[in] forecolor New foreground color to use
 * @param[in] backcolor New background color to use
 */
void fontlib_SetColors(uint8_t forecolor, uint8_t backcolor);

/**
 * Returns the current foreground color FontLibC will use for drawing.
 * @note This is NOT the same as GraphX's current color!
 * @return Current foreground color
 */
uint8_t fontlib_GetForegroundColor(void);

/**
 * Returns the current background color FontLibC will use for drawing.
 * @note This is NOT the same as GraphX's current color!
 * @return Current background color
 */
uint8_t fontlib_GetBackgroundColor(void);

/**
 * Controls whether FontLibC will use a transparent background for text drawing
 * instead of the currently configured background color.
 * @note This has nothing to do with GraphX's configured transparent color
 * @param[in] transparency true to make background transparent, false to use background color
 */
void fontlib_SetTransparency(bool transparency);

/**
 * Returns whether FontLibC will use a transparent background for text drawing
 * instead of the currently configured background color.
 * @note This has nothing to do with GraphX's configured transparent color
 * @return true if background will be transparent, false if background color will be used
 */
bool fontlib_GetTransparency(void);

/**
 * Controls hows much black space will be added above and below each line of
 * text.  If transparency is set, then the padding will not be overwritten with
 * the background color, but padding will still be added.  Padding space is
 * added at the time each glyph is drawn.
 * @param[in] space_above Blank space padding to add above
 * @param[in] space_below Blank space padding to add below
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
 * be moved back a certain number of pixels after every glyph is drawn.
 * @note This is only useful if transparency mode is set.
 * @note Italics is currently untested!  (I haven't designed an italic font yet.)
 * @param[in] italic_spacing_adjustment Pixels to move cursor backward after each glyph
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
 * @param[in] code_point Code point to test
 * @return true if code_point is in current font, false if not
 */
bool fontlib_ValidateCodePoint(char code_point);

/**
 * Returns the total number of printable glyphs in the font.
 * @note This can return 256; no valid font has 0 printable glyphs.
 * @return Total number of printable glyphs
 */
size_t fontlib_GetTotalGlyphs(void);

/**
 * Returns the code point of the first printable glyph.
 * @note The C SDK makes char SIGNED by default, so you probably want to
 * typecast this to unsigned char before attempting any math with it.
 * @return First print glyph code point
 */
char fontlib_GetFirstGlyph(void);

/**
 * Allows you to set the code point that is recognized as being a new line code.
 * You can set this to zero to prevent new line code processing.
 * @note If FONTLIB_ENABLE_AUTO_WRAP is enabled, then wrapping will still
 * implicitly case a newline.
 * @note This defaults to 0x0A (ASCII line feed/UNIX newline)
 * @param[in] code_point New code point to use for newline
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
 * Set this to 0 if you do not want to use the alternate stop code feature.
 * Defaults to 0.
 * @note You can set this to space to make DrawString and GetStringWidth
 * stop processing when they reach a space.
 * @note NULL (0) will still be recognized as a stop code regardless of value.
 * @param[in] code_point Additional code point to recognize as a stop code.
 */
void fontlib_SetAlternateStopCode(char code_point);

/**
 * Returns the current alternate stop code.
 * @return Current alternate stop code.
 */
char fontlib_GetAlternateStopCode(void);

/**
 * Sets the first code point considered printable.
 * All code points before this will be considered control codes.
 * This defaults 0x10.
 * @note Setting this to 0 (NULL) will NOT cause NULL to be ignored.
 * @param[in] code_point First printable code point
 */
void fontlib_SetFirstPrintableCodePoint(char code_point);

/**
 * Returns the first code point considered printable.
 * @return Current first printable code point
 */
char fontlib_GetFirstPrintableCodePoint(void);

/**
 * Sets the code points DrawInt and DrawUInt will use for the minus symbol
 * and digits 0-9.
 * @param[in] minus Minus symbol code point, defaults to '-'
 * @param[in] zero Zero code point, defaults to '0'; '1'-'9' are assumed to follow
 */
void fontlib_SetDrawIntCodePoints(char minus, char zero);

/**
 * Returns the code point DrawInt and DrawUInt will use for a minus symbol
 * Defaults to '-'
 * @return '-' or whatever you set it to
 */
char fontlib_GetDrawIntMinus(void);

/**
 * Returns the code point DrawInt and DrawUInt will use for '0'; it assumes
 * '1'-'9' follow '0'
 * Defaults to '0'
 * @return '0' or whatever you set it to
 */
char fontlib_GetDrawIntZero(void);

/**
 * Returns the width of the given glyph
 * @param[in] codepoint Codepoint to test
 * @return Width of glyph, 0 if invalid codepoint
 */
uint8_t fontlib_GetGlyphWidth(char codepoint);

/**
 * Returns the width of a string printed in the current font.
 *
 * Stops processing when it encounters ANY control code or a codepoint not in
 * the current font.
 * @param[in] str Pointer to string
 * @return Width of string
 */
unsigned int fontlib_GetStringWidth(const char *str);

/**
 * Returns the width of a string printed in the current font.
 *
 * Stops processing when it encounters ANY control code or a codepoint not in
 * the current font, or when max_characters have been processed.
 * @param[in] str Pointer to string
 * @param[in] max_characters Maximum number of characters to process
 * @return Width of string
 */
unsigned int fontlib_GetStringWidthL(const char *str, size_t max_characters);

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
 * Draws a glyph.
 * @note This can even draw code points less than the code point specified with
 * fontlib_SetFirstPrintableCodePoint().  It can even draw code point 0.
 * @note Although this does update the cursor X/Y positions, it does NOT
 * process window bounds at all!  (Maybe this should be FIXME?  On the other
 * hand, users may want this specifically so they can handle all their own
 * layout without the text window settings getting in their way.)
 * @param[in] glyph Codepoint
 * @return The new X value of the cursor
 */
uint24_t fontlib_DrawGlyph(uint8_t glyph);

/**
 * Draws a string.
 *
 * This will return when it reaches the right edge of the text window if
 * FONTLIB_ENABLE_AUTO_WRAP is turned off.
 *
 * This stops drawing upon reaching NULL.  It will also stop if it encounters
 * the character code specified with fontlib_SetAlternateStopCode().
 * @note The check for the alternate stop code always takes place before drawing
 * a glyph, so if you need to also display the stop code character, you must
 * directly call fontlib_DrawGlyph to force display the character and increment
 * past it.
 * @note Newline codes will print regardless of whether FONTLIB_ENABLE_AUTO_WRAP
 * is enabled.  To disable parsing newline codes, use fontlib_SetNewlineCode(0);
 * @note THIS IS NOT REENTRANT (though if you need that, you're probably not
 * using C)
 * @param[in] str Pointer to string
 * @return The new X value of the cursor (probably not useful if a newline was
 * processed.)
 */
uint24_t fontlib_DrawString(const char *str);

/**
 * Draws a string, up to a maximum number of characters.
 *
 * @note This is intended to be used if you only want a portion of a string
 * printed. (Or if you hate null-terminated strings and want length-prefixed
 * strings instead.  It still won't print NULLs though.)
 *
 * @note THIS IS NOT REENTRANT (though if you need that, you're probably not using C)
 * @param str Pointer to string
 * @param[in] max_characters Maximum number of characters to attempt to print, may
 * return early if some other condition requires returning
 * @return The new X value of the cursor (probably not useful if a newline was
 * processed.)
 */
uint24_t fontlib_DrawStringL(const char *str, size_t max_characters);

/**
 * Prints a signed integer
 *
 * Outputs at the current cursor position. Padded with leading zeros if
 * necessary to satisfy the specified minimum length.
 * @param[in] n Integer to print
 * @param[in] length Minimum number of characters to print
 * @note This does not obey window bounds like DrawString/L
 * @note \c length must be between 1 and 8, inclusive
 */
void fontlib_DrawInt(int n, uint8_t length);

/**
 * Prints an unsigned integer
 *
 * Outputs at the current cursor position. Padded with leading zeros if
 * necessary to satisfy the specified minimum length.
 * @param[in] n Unsigned integer to print
 * @param[in] length Minimum number of characters to print
 * @note This does not obey window bounds like DrawString/L
 * @note \c length must be between 1 and 8, inclusive
 */
void fontlib_DrawUInt(unsigned int n, uint8_t length);

/**
 * Erases everything from the cursor to the right side of the text window
 * (End-Of-Line).  This ignores the transparent background flag.
 */
void fontlib_ClearEOL(void);

/**
 * Erases the entire current text window.
 * @note This ignores the transparent background flag.  If background
 * transparency is important, check fontlib_GetTransparency() before calling
 * this routine.
 */
void fontlib_ClearWindow(void);

/**
 * Performs a newline.  Pays attention to newline flags.
 * @return Returns true if the text window is full.  This only happens if
 * scrolling is disabled.
 */
bool fontlib_Newline(void);

/**
 * Sets options for controlling newline behavior
 * @param[in] options Flags setting newline behavior
 * @see fontlib_newline_options_t
 */
void fontlib_SetNewlineOptions(uint8_t options);

/**
 * Gets the current newline behavior options.
 * @return Current newline behavior options
 */
uint8_t fontlib_GetNewlineOptions(void);

/**
 * Scrolls the contents of the text window down one line, i.e. everything in
 * the window is copied UP one line, thus yielding the effect of scrolling down.
 * The current text cursor position is ignored.
 * @note The bottom line is not erased; you must erase or overwrite it yourself.
 */
void fontlib_ScrollWindowDown(void);

/**
 * Scrolls the contents of the text window up one line, i.e. everything in
 * the window is copied DOWN one line, thus yielding the effect of scrolling up.
 * The current text cursor position is ignored.
 * @note The bottom line is not erased; you must erase or overwrite it yourself.
 * @note This doesn't try to compute the location of the bottom line of text; it
 * just blindly copies rows of pixels, so make sure the window height is an
 * exact multiple of the font height.
 */
void fontlib_ScrollWindowUp(void);

/**
 * Gets the long name associated with a font pack.  Useful in a loop with
 * ti_Detect() when searching a typeface with a specific name.
 * @param[in] appvar_name Pointer to name of appvar
 * @return Direct pointer to font's name; or NULL if no such appvar exists, the
 * appvar isn't a font pack, or the font pack does not supply a name.
 * NOTA BENE: Any operation that can move variables around in memory can
 * invalidate this pointer!
 */
char *fontlib_GetFontPackName(const char *appvar_name);

/**
 * Gets a pointer to a font, suitable for passing to SetFont(), given a font
 * pack's address.  Useful if you know caching the font pack's address is safe.
 * @see ti_GetDataPtr()
 * @param[in] font_pack Pointer to font pack
 * @param[in] index Index into font table of font pack
 * @return Direct pointer to font, or NULL if the index is invalid.
 */
fontlib_font_t *fontlib_GetFontByIndexRaw(const fontlib_font_pack_t *font_pack, uint8_t index);

/**
 * Gets a pointer to a font, suitable for passing to SetFont(), given a font
 * pack's appvar's name.  Recommended to use after any file write, create,
 * delete, or un/archive, as all those operations could invalidate the cached
 * data pointers to the currently loaded font.
 * @param[in] font_pack_name Pointer to font pack appvar's name
 * @param[in] index Index into font table of font pack
 * @return Direct pointer to font, or NULL if the index is invalid.
 */
fontlib_font_t *fontlib_GetFontByIndex(const char *font_pack_name, uint8_t index);

/**
 * Gets a pointer to a font, suitable for passing to SetFont(), given a font
 * pack's address and a set of font properties.  Useful if you know caching the
 * font pack's address is safe.
 * @see ti_GetDataPtr()
 * @param[in] font_pack Pointer to font pack
 * @param[in] size_min Minimum heigh, in pixels, to accept.  Space above and
 * space below metrics are not considered.
 * @param[in] size_max Maximum height
 * @param[in] weight_min Minimum weight to accept.  0 may be used.
 * @param[in] weight_max Maximum weight to accept.  0xFF may be used.
 * @param[in] style_bits_set Mask of style bits you want set.  For example,
 * FONTLIB_SERIF | FONTLIB_MONOSPACE to look for a monospaced serifed font.
 * @param[in] style_bits_reset Style bits you want RESET.  For example, pass
 * FONTLIB_MONOSPACE to REJECT monospaced fonts.
 * @return Direct pointer to font, or NULL if no matching font is found
 */
 fontlib_font_t *fontlib_GetFontByStyleRaw(const fontlib_font_pack_t *font_pack, uint8_t size_min, uint8_t size_max, uint8_t weight_min, uint8_t weight_max, uint8_t style_bits_set, uint8_t style_bits_reset);

/**
 * Gets a pointer to a font, suitable for passing to SetFont(), given a font
 * pack's appvar's name and a set of font properties.  Recommended to use after
 * any file write, create, delete, or un/archive, as all those operations could
 * invalidate the cached data pointers to the currently loaded font.
 * @param[in] font_pack_name Pointer to font pack appvar's name
 * @param[in] size_min Minimum heigh, in pixels, to accept.  Space above and
 * space below metrics are not considered.
 * @param[in] size_max Maximum height
 * @param[in] weight_min Minimum weight to accept.  0 may be used.
 * @param[in] weight_max Maximum weight to accept.  0xFF may be used.
 * @param[in] style_bits_set Mask of style bits you want set.  For example,
 * FONTLIB_SERIF | FONTLIB_MONOSPACE to look for a monospaced serifed font.
 * @param[in] style_bits_reset Style bits you want RESET.  For example, pass
 * FONTLIB_MONOSPACE to REJECT monospaced fonts.
 * @return Direct pointer to font, or NULL if no matching font is found
 */
fontlib_font_t *fontlib_GetFontByStyle(const char *font_pack_name, uint8_t size_min, uint8_t size_max, uint8_t weight_min, uint8_t weight_max, uint8_t style_bits_set, uint8_t style_bits_reset);


#ifdef __cplusplus
}
#endif

#endif
