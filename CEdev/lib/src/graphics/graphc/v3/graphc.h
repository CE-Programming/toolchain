/**
 * @file    GRAPHC CE C Library
 * @version 3.0
 *
 * @section LICENSE
 *
 * Copyright (c) 2016
 * Matthew "MateoConLechuga" Waltz
 * Jacob "jacobly" Young
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 *
 * This library implements some fast graphical routines
 */

#ifndef H_GRAPHC
#define H_GRAPHC

#include <stdint.h>
#include <stdbool.h>

/**
 * Initializes the graphics setup.
 * This includes setting the LCD into 8bpp mode and
 * loading the default palette
 */
void gc_InitGraph(void);

/**
 * Closes the graphics setup.
 * Restores the LCD to 16bpp prefered by the OS
 * and clears the screen
 */
void gc_CloseGraph(void);

/**
 * Used for accessing the palette directly
 */
uint16_t gc_paletteArray[256] _At 0xE30200;

/**
 * Array of the LCD VRAM
 */
uint16_t (*gc_vramArray)[240][320] _At 0xD40000;

/**
 * Produces a random integer value
 */
#define gc_RandInt(min, max) ((unsigned)rand() % ((max) - (min) + 1) + (min))

/**
 * Checks if we are currently in a rectangular hotspot area
 */
#define gc_CheckRectangleHotspot(master_x, master_y, master_width, master_height, test_x, test_y, test_width, test_height) \
	  (test_x < master_x + master_width && \
	   test_x + test_width > master_x && \
	   test_y < master_y + master_height && \
	   test_y + test_height > master_y)
	   
/* Type for the clip region */
typedef struct gc_region {
	int24_t x_left, y_top, x_right, y_bottom;
} gc_region_t;

/* Type for tilemapping */
typedef struct gc_tilemap {
	uint8_t *map;             /* pointer to indexed map array */
	uint8_t **tiles;          /* pointer to tiles */
	uint8_t tile_height;      /* individual tile height */
	uint8_t tile_width;       /* individual tile width */
	uint8_t draw_height;      /* number of rows to draw in the tilemap */
	uint8_t draw_width;       /* number of cols to draw tilemap */
	uint8_t type_width;       /* 2^type_width = tile_width */
	uint8_t type_height;      /* 2^type_height = tile_height */
	uint8_t height;           /* total number of rows in the tilemap */
	uint8_t width;            /* total number of cols in the tilemap */
	uint8_t y_loc;            /* y pixel location to begin drawing at */
	uint24_t x_loc;           /* x pixel location to begin drawing at */
} gc_tilemap_t;

typedef enum gc_tilemap_type {
	gc_tile_2_pixel = 1,      /* Set when using 2 pixel tiles */
	gc_tile_4_pixel,          /* Set when using 4 pixel tiles */
	gc_tile_8_pixel,          /* Set when using 8 pixel tiles */
	gc_tile_16_pixel,         /* Set when using 16 pixel tiles */
	gc_tile_32_pixel,         /* Set when using 32 pixel tiles */
	gc_tile_64_pixel,         /* Set when using 64 pixel tiles */
	gc_tile_128_pixel,        /* Set when using 128 pixel tiles */
} gc_tilemap_type_t;

/**
 * Quickly set and get pixels.
 * No clipping is performed.
 */
#define gc_NoClipPixelPtr(x, y)           ((uint8_t*)(gc_drawingBuffer + (uint16_t)x + ((uint8_t)y)*320))
#define gc_NoClipSetPixel(x, y, c)        (*(gc_NoClipPixelPtr(x,y)) = c)
#define gc_NoClipGetPixel(x, y)           (*(gc_NoClipPixelPtr(x,y)))
#define gc_RGBTo1555(r,g,b)               ((unsigned short)(((unsigned char)(r) >> 3) << 10) | (((unsigned char)(g) >> 3) << 5) | ((unsigned char)(b) >> 3))
#define gc_FontHeight()                   8
#define gc_drawingBuffer                  (*(uint8_t**)(0xE30014))
#define gc_lcdWidth                       320
#define gc_lcdHeight                      240

/**
 * Draws a tilemap given an intialized tilemap structure
 *  x_offset : offset in pixels from the left of the tilemap
 *  y_offset : offset in pixels from the top of the tilemap
 */
void gc_ClipDrawBGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gc_NoClipDrawBGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Draws a transparent tilemap given an intialized tilemap structure
 *  x_offset : offset in pixels from the left of the tilemap
 *  y_offset : offset in pixels from the top of the tilemap
 */
void gc_ClipDrawFGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gc_NoClipDrawFGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Tile Setting/Getting -- These use absolute pixel offsets from the left and top
 */
uint8_t *gc_TilePtr(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Tile Setting/Getting -- These use mapped offsets from the tile map itself
 */
uint8_t *gc_TilePtrMapped(gc_tilemap_t *tilemap, uint8_t x_offset, uint8_t y_offset);

/**
 * Decompress a block of data using an LZ77 decoder
 *  in  : Compressed buffer
 *  out : Decompressed buffer; must be large enough to hold decompressed data
 *  insize : Number of input bytes
 */
void gc_LZDecompress(uint8_t *in, uint8_t *out, unsigned in_size);

/**
 * Sets the color index that drawing routines will use
 * This applies to lines, rectangles, etc
 * Returns the previous global color index
 */
uint8_t gc_SetColorIndex(uint8_t index);

/**
 * Sets up the default palette where high=low
 */
void gc_SetDefaultPalette(void);

/**
 * Sets up the palette; paletteSize is in bytes
 */
void gc_SetPalette(uint16_t *palette, uint16_t paletteSize);

/**
 * Fills the screen with the given palette index
 */
void gc_FillScrn(uint8_t color);

/**
 * Gets the 1555 color located at the given palette index.
 * Included for backwards compatibility  with v1.0
 * It is recomended you use the gc_paletteArray array instead
 */
uint16_t gc_GetColor(uint8_t index);

/**
 * Sets the 1555 color located at the given palette index.
 * Included for backwards compatibility  with v1.0
 * It is recomended you use the gc_paletteArray array instead
 */
void gc_SetColor(uint8_t index, uint16_t color);

/**
 * Sets the XY pixel measured from the top left origin of the screen to the
 * given palette index color. This routine performs clipping.
 */
void gc_ClipSetPixel(int24_t x, int24_t y);

/**
 * Gets the palette index color of the XY pixel measured from the top
 * left origin of the screen. This routine performs clipping.
 */
uint8_t gc_ClipGetPixel(int24_t x, int24_t y);

/**
 * Draws a line given the x,y,x,y coordinates measured from the top left origin.
 * No clipping is performed.
 */
void gc_NoClipLine(uint16_t x0, uint8_t y0, uint16_t x1, uint8_t y1);

/**
 * Draws a filled rectangle measured from the top left origin.
 * No clipping is performed.
 */
void gc_NoClipRectangle(uint16_t x, uint8_t y, uint16_t width, uint8_t height);

/**
 * Draws a rectangle outline measured from the top left origin.
 * No clipping is performed.
 */
void gc_NoClipRectangleOutline(uint16_t x, uint8_t y, uint16_t width, uint8_t height);

/**
 * Draws a fast horizontal line measured from the top left origin.
 * No clipping is performed.
 */
void gc_NoClipHorizLine(uint16_t x, uint8_t y, uint16_t length);

/**
 * Draws a fast vertical line measured from the top left origin.
 * No clipping is performed.
 */
void gc_NoClipVertLine(uint16_t x, uint8_t y, uint8_t length);

/**
 * Draws a filled circle measured from the top left origin.
 */
void gc_NoClipCircle(uint16_t x, uint8_t y, unsigned radius);
void gc_ClipCircle(int x, int y, unsigned radius);

/**
 * Draws circle outline measured from the top left origin.
 */
void gc_ClipCircleOutline(int x, int y, unsigned radius);

/**
 * Forces all graphics routines to write to the offscreen buffer
 */
void gc_DrawBuffer(void);

/**
 * Forces all graphics routines to write to the visible screen
 */
void gc_DrawScreen(void);

/**
 * Swaps the buffer with the visible screen and vice versa.
 * The current drawing location remains the same.
 */
void gc_SwapDraw(void);

/**
 * Returns 0 if graphics routines are currently drawing to visible screen
 * The current drawing location remains the same.
 */
uint8_t gc_DrawState(void);

/**
 * Outputs a character at the current cursor position
 * No text clipping is performed.
 */
void gc_PrintChar(const char c);

/**
 * Outputs a signed integer at the current cursor position.
 * No text clipping is performed.
 * Values range from: (-8388608-8388607)
 * length must be between 0-8
 */
void gc_PrintInt(int n, uint8_t length);

/**
 * Outputs an unsigned integer at the current cursor position.
 * No text clipping is performed.
 * Values range from: (0-16777215)
 * length must be between 0-8
 */
void gc_PrintUnsignedInt(unsigned int n, uint8_t length);

/**
 * Outputs a string at the current cursor position
 * No text clipping is performed.
 */
void gc_PrintString(const char *string);

/**
 * Outputs a string at the given XY coordinates measured from the top left origin.
 * The current cursor position is updated.
 * No text clipping is performed.
 */
void gc_PrintStringXY(const char *string, uint16_t x, uint8_t y);

/**
 * Returns the current text cursor X position
 */
uint16_t gc_TextX(void);

/**
 * Returns the current text cursor Y position
 */
uint8_t gc_TextY(void);

/**
 * Sets the text cursor XY position
 */
void gc_SetTextXY(uint16_t x, uint8_t y);

/**
 * Sets the current text color.
 * Low 8 bits represent the foreground color.
 * High 8 bits represent the background color.
 * Returns previous text color
 */
uint16_t gc_SetTextColor(uint16_t color);

/**
 * Sets the transparent color used in text and sprite functions
 * Default index transparency color is 0xFF
 * Returns the previous transparent color
 */
uint8_t gc_SetTransparentColor(uint8_t color);

/**
 * Draws a given sprite to the screen as fast as possible; no transparency, clipping, or anything of the sort.
 * Basically just a direct rectangular data dump onto vram.
 */
void gc_NoClipDrawSprite(uint8_t *data, uint16_t x, uint8_t y, uint8_t width, uint8_t height);

/**
 * Draws a given sprite to the screen using transparency set with gc_SetTransparentColor()
 * Not as fast as gc_NoClipDrawSprite(), but still performs pretty well.
 */
void gc_NoClipDrawTransparentSprite(uint8_t *data, uint16_t x, uint8_t y, uint8_t width, uint8_t height);

/**
 * Quickly grab the background behind a sprite (useful for transparency)
 * spriteBuffer must be pointing to a large enough buffer to hold width*height number of bytes
 * A pointer to spriteBuffer is also returned for ease of use.
 * spriteBuffer is updated with the screen coordinates given.
 */
uint8_t *gc_NoClipGetSprite(uint8_t *spriteBuffer, uint16_t x, uint8_t y, uint8_t width, uint8_t height);

/**
 * Set the font routines to use the provided font, formated 8x8
 */
void gc_SetCustomFontData(uint8_t *fontdata);

/**
 * Set the font routines to use the provided font spacing
 */
void gc_SetCustomFontSpacing(uint8_t *fontspacing);

/**
 * To disable monospaced font, gc_SetFontMonospace(0)
 * Otherwise, send the width int pixels you wish all characters to be
 */
void gc_SetFontMonospace(uint8_t monospace);

/**
 * Returns the width of the input sting
 * Takes into account monospacing flag
 */
uint24_t gc_StringWidth(const char *string);

/**
 * Returns the width of the character
 * Takes into account monospacing flag
 */
uint24_t gc_CharWidth(const char c);

/**
 * Draws a given sprite to the screen as fast as possible; no transparency.
 * Basically just a direct rectangular data dump onto vram.
 */
void gc_ClipDrawSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height);

/**
 * Draws a given sprite to the screen using transparency set with gc_SetTransparentColor()
 * Not as fast as gc_NoClipDrawSprite(), but still performs pretty well..
 */
void gc_ClipDrawTransparentSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height);

/**
 * Quickly grab the background behind a sprite (useful for transparency)
 * spriteBuffer must be pointing to a large enough buffer to hold width*height number of bytes
 * spriteBuffer is updated with the screen coordinates given.
 * A pointer to spriteBuffer is also returned for ease of use.
 * This routine is technically not clipped, but as long as you use one of the clipped drawing routines, it is fine
 */
#define gc_ClipGetSprite gc_NoClipGetSprite

/**
 * Sets the clipping window for clipped routines
 */
void gc_SetClipWindow(int24_t xmin, int24_t ymin, int24_t xmax, int24_t ymax);

/**
 * Clips an arbitrary region to fit within the defined bounds
 * Returns false if offscreen
 */
bool gc_ClipRegion(gc_region_t *region);

/**
 * Screen shifting routines that operate within the clipping window
 * Note that the data left over is undefined (Must be drawn over)
 */
void gc_ShiftWindowDown(uint24_t pixels);
void gc_ShiftWindowUp(uint24_t pixels);
void gc_ShiftWindowLeft(uint24_t pixels);
void gc_ShiftWindowRight(uint24_t pixels);

/**
 * Draws a filled rectangle measured from the top left origin.
 */
void gc_ClipRectangle(int24_t x, int24_t y, uint24_t width, uint24_t height);

/**
 * Draws a rectangle outline measured from the top left origin.
 */
void gc_ClipRectangleOutline(int24_t x, int24_t y, uint24_t width, uint24_t height);

/**
 * Draws a fast horizontal line measured from the top left origin.
 */
void gc_ClipHorizLine(int24_t x, int24_t y, uint24_t length);

/**
 * Draws a fast vertical line measured from the top left origin.
 */
void gc_ClipVertLine(int24_t x, int24_t y, uint24_t length);

/**
 * Fairly fast clipped line routine
 * Returns false if offscreen, true if drawn
 */
bool gc_ClipLine(int24_t x0, int24_t y0, int24_t x1, int24_t y1);

/**
 * Unclipped scaled sprite routines
 * Scaling factors must be greater than or equal to 1, and an integer factor
 */
void gc_NoClipDrawScaledSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height, uint8_t width_scale, uint8_t height_scale);
void gc_NoClipDrawScaledTransparentSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height, uint8_t width_scale, uint8_t height_scale);

#endif
