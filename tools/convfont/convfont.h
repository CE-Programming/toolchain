#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum {
    output_unspecified = 0,
    output_fontpack,
    output_c_array,
    output_asm_array,
    output_binary_blob,
} output_formats_t;

typedef enum {
    bad_infile = 1,
    bad_outfile,
    invalid_fnt,
    bad_options,
    malloc_failed,
    internal_error,
} error_codes_t;
/*
typedef struct
{
int16_t dfVersion;
int32_t dfSize;
uint8_t dfCopyright[60];
int16_t dfType;
int16_t dfPoints;
int16_t dfVertRes;
int16_t dfHorizRes;
int16_t dfAscent;
int16_t dfInternalLeading;
int16_t dfExternalLeading;
uint8_t dfItalic;
uint8_t dfUnderline;
uint8_t dfStrikeOut;
int16_t dfWeight;
uint8_t dfCharSet;
int16_t dfPixWidth;
int16_t dfPixHeight;
uint8_t dfPitchAndFamily;
int16_t dfAvgWidth;
int16_t dfMaxWidth;
uint8_t dfFirstChar;
uint8_t dfLastChar;
uint8_t dfDefaultChar;
uint8_t dfBreakChar;
int16_t dfWidthBytes;
int32_t dfDevice;
int32_t dfFace;
/* Should be zero * /
int32_t dfBitsPointer;
int32_t dfBitsOffset;
uint8_t dfReserved;
} fnt_header_20_t;

typedef struct
{
int16_t dfVersion;
int32_t dfSize;
uint8_t dfCopyright[60];
int16_t dfType;
int16_t dfPoints;
int16_t dfVertRes;
int16_t dfHorizRes;
int16_t dfAscent;
int16_t dfInternalLeading;
int16_t dfExternalLeading;
uint8_t dfItalic;
uint8_t dfUnderline;
uint8_t dfStrikeOut;
int16_t dfWeight;
uint8_t dfCharSet;
int16_t dfPixWidth;
int16_t dfPixHeight;
uint8_t dfPitchAndFamily;
int16_t dfAvgWidth;
int16_t dfMaxWidth;
uint8_t dfFirstChar;
uint8_t dfLastChar;
uint8_t dfDefaultChar;
uint8_t dfBreakChar;
int16_t dfWidthBytes;
int32_t dfDevice;
int32_t dfFace;
/* Should be zero * /
int32_t dfBitsPointer;
int32_t dfBitsOffset;
uint8_t dfReserved;
/* Start of 3.0 new stuff * /
int32_t dfFlags;
int16_t dfAspace;
int16_t dfBspace;
int16_t dfCspace;
int16_t dfColorPointer;
int32_t dfReserved1;
/* I have no idea what these are about. * /
int16_t garbage1;
int16_t garbage2;
int16_t garbage3;
int16_t garbage4;
int16_t garbage5;
int16_t garbage6;
int16_t garbage7;
} fnt_header_30_t;

typedef union
{
fnt_header_20_t fnt_20;
fnt_header_30_t fnt_30;
} fnt_header_t;*/

/* This definition just adds some typing to otherwise opaque chunks of data. */
typedef struct {
    int length;
    uint8_t bytes[1];
} fontlib_bitmap_t;

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
    uint8_t *widths_table;
    /* Offset to a table of offsets to glyph bitmaps.
    * These offsets are only 16-bits each to save some space. */
    fontlib_bitmap_t **bitmaps;
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

/*uint8_t get_cols(uint8_t width)
{
return ((width - 1) >> 3) + 1;
}*/

/* This macro provides a less ugly means of computing the number of bytes per
 * row for a glyph. */
#define byte_columns(width) ((((width) - 1) >> 3) + 1)

void throw_error(int code, char *string);
