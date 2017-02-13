/**
 * @file    GRAPHX CE C Library
 * @version 4
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
 * For transparent routines; index 0 shall represent the transparent color
 * Text is the only exception, with the ability to specify the transparent index
 */

typedef struct gfx_image {
    uint8_t width;
    uint8_t height;
    uint8_t data[1];
} gfx_image_t;

/**
 * A simple structure for working with 2D points
 */
typedef struct gfx_point {
    int x,y;
} gfx_point_t;

/**
 * Allocates room on the heap for sprite data of given size
 * Takes a pointer to the routine used for malloc as well
 * Returns NULL upon failure to allocate space, otherwise a pointer to the sprite structure
 * Note that if you use the system malloc routine, it must be used elsewhere in your program
 * otherwise it will not be linked correctly
 */
gfx_image_t *gfx_AllocSprite(uint8_t width, uint8_t height, void *malloc_routine);
#define gfx_MallocSprite(width, height) gfx_AllocSprite(width, height, (void*)malloc)

/**
 * This routine should be used globally as it uses the BSS
 * Note that you will have to initialize the width and height of the sprite manually
 */
#define gfx_UninitedSprite(name, max_width, max_height) uint8_t name##_data[2 + (max_width) * (max_height)]; \
                                                        gfx_image_t *name = (gfx_image_t *)name##_data
                        
/**
 * This routine should be used for small sprites as it uses the stack
 */
#define gfx_TempSprite(name, width, height) uint8_t name##_data[2 + (width) * (height)] = { (width), (height) }; \
                                            gfx_image_t *name = (gfx_image_t *)name##_data

typedef enum gfx_mode {
    gfx_8bpp = 0x27
} gfx_mode_t;

/**
 * Initializes the graphics setup
 * Set LCD to 8bpp mode and loads the default palette
 */
int gfx_Begin(gfx_mode_t mode);

/**
 * Closes the graphics setup
 * Restores the LCD to 16bpp prefered by the OS and clears the screen
 */
void gfx_End(void);

/**
 * Used for accessing the palette directly
 * 256 bytes in size
 */
#define gfx_palette ((uint16_t*)0xE30200)

/**
 * Array of the LCD VRAM
 * 153600 bytes in size
 */
#define gfx_vram ((uint8_t*)0xD40000)

/**
 * Array of the current buffer
 * 76800 bytes in size
 */
#define gfx_vbuffer (**(uint8_t(**)[240][320])0xE30014)

/* Type for the clip region */
typedef struct gfx_region {
    int xmin, ymin, xmax, ymax;
} gfx_region_t;

/* Type for tilemap */
typedef struct gfx_tilemap {
    uint8_t *map;            /* pointer to indexed map array */
    gfx_image_t **tiles;     /* pointer to tiles */
    uint8_t tile_height;     /* individual tile height */
    uint8_t tile_width;      /* individual tile width */
    uint8_t draw_height;     /* number of rows to draw in the tilemap */
    uint8_t draw_width;      /* number of cols to draw tilemap */
    uint8_t type_width;      /* 2^type_width = tile_width (see enum gfx_tilemap_type) */
    uint8_t type_height;     /* 2^type_height = tile_height (see enum gfx_tilemap_type) */
    uint8_t height;          /* total number of rows in the tilemap */
    uint8_t width;           /* total number of cols in the tilemap */
    uint8_t y_loc;           /* y pixel location to begin drawing at */
    uint24_t x_loc;          /* x pixel location to begin drawing at */
} gfx_tilemap_t;

typedef enum gfx_tilemap_type {
    gfx_tile_no_pow2 = 0,     /* Set when using non powers of 2 */
    gfx_tile_2_pixel,         /* Set when using 2 pixel tiles */
    gfx_tile_4_pixel,         /* Set when using 4 pixel tiles */
    gfx_tile_8_pixel,         /* Set when using 8 pixel tiles */
    gfx_tile_16_pixel,        /* Set when using 16 pixel tiles */
    gfx_tile_32_pixel,        /* Set when using 32 pixel tiles */
    gfx_tile_64_pixel,        /* Set when using 64 pixel tiles */
    gfx_tile_128_pixel,       /* Set when using 128 pixel tiles */
} gfx_tilemap_type_t;

/**
 * Draws a tilemap given an initialized tilemap structure
 *  x_offset : offset in pixels from the of the tilemap
 *  y_offset : offset in pixels from the top of the tilemap
 */
void gfx_Tilemap(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gfx_Tilemap_NoClip(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Draws a transparent tilemap given an initialized tilemap structure
 *  x_offset : offset in pixels from the left left of the tilemap
 *  y_offset : offset in pixels from the top of the tilemap
 */
void gfx_TransparentTilemap(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gfx_TransparentTilemap_NoClip(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Tile Setting/Getting -- Uses absolute pixel offsets from the top left
 */
uint8_t *gfx_TilePtr(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
#define gfx_SetTile(a,b,c,d)    (*(gfx_TilePtr(a, b, c)) = (uint8_t)d)
#define gfx_GetTile(a,b,c)      (*(gfx_TilePtr(a, b, c)))

/**
 * Tile Setting/Getting -- Uses a mapped offsets from the tile map itself
 */
uint8_t *gfx_TilePtrMapped(gfx_tilemap_t *tilemap, uint8_t x_offset, uint8_t y_offset);
#define gfx_SetTileMapped(a,b,c,d)    (*(gfx_TilePtrMapped(a, b, c)) = (uint8_t)d)
#define gfx_GetTileMapped(a,b,c)      (*(gfx_TilePtrMapped(a, b, c)))

/**
 * Sets the color index that drawing routines will use
 * This applies to lines, rectangles, etc
 * Returns the previous global color index
 */
uint8_t gfx_SetColor(uint8_t index);

/**
 * Sets the tcolor index that drawing routines will use
 * This currently applies to transparent sprites, both scaled and unscaled
 * Returns the previous transparent color index
 */
uint8_t gfx_SetTransparentColor(uint8_t index);

/**
 * Sets up the default palette for the given mode
 */
void gfx_SetDefaultPalette(gfx_mode_t mode);

/**
 * Set entries 0-255 in the palette (index 0 is transparent for transparent routines)
 */
void gfx_SetPalette(uint16_t *palette, uint24_t size, uint8_t offset);

/**
 * Fills the screen with the given palette index
 */
void gfx_FillScreen(uint8_t index);

/**
 * Implements a faster version of gfx_FillScreen(0)
 */
void gfx_ZeroScreen(void);

/**
 * Sets the XY pixel measured from the top left origin of the screen to the
 * given palette index color. This routine performs clipping.
 */
void gfx_SetPixel(uint24_t x, uint8_t y);

/**
 * Gets the palette index color of the XY pixel measured from the top
 * left origin of the screen. This routine performs clipping.
 */
uint8_t gfx_GetPixel(uint24_t x, uint8_t y);

/**
 * Draws a line given the x,y,x,y coordinates measured from the top left origin.
 */
void gfx_Line(int x0, int y0, int x1, int y1);
void gfx_Line_NoClip(uint24_t x0, uint8_t y0, uint24_t x1, uint8_t y1);

/**
 * Clips the points in a line region
 * Returns false if offscreen
 */
bool gfx_CohenSutherlandClip(int *x0, int *y0, int *x1, int *y1);

/**
 * Draws a horizontal line measured from the top left origin.
 */
void gfx_HorizLine(int x, int y, int length);
void gfx_HorizLine_NoClip(uint24_t x, uint8_t y, uint24_t length);

/**
 * Draws a vertical line measured from the top left origin.
 */
void gfx_VertLine(int x, int y, int length);
void gfx_VertLine_NoClip(uint24_t x, uint8_t y, uint24_t length);

/**
 * Draws a rectangle measured from the top left origin.
 */
void gfx_Rectangle(int x, int y, int width, int height);
void gfx_Rectangle_NoClip(uint24_t x, uint8_t y, uint24_t width, uint8_t height);
void gfx_FillRectangle(int x, int y, int width, int height);
void gfx_FillRectangle_NoClip(uint24_t x, uint8_t y, uint24_t width, uint8_t height);

/**
 * Draws a filled circle measured from the top left origin.
 */
void gfx_Circle(int x, int y, unsigned radius);
void gfx_FillCircle(int x, int y, unsigned radius);
void gfx_FillCircle_NoClip(uint24_t x, uint8_t y, uint8_t radius);
#define gfx_Circle_NoClip gfx_Circle

/**
 * Draws a polygon outline
 * Example:
 * int points[6] = { 
 *                    160,  1,  (x0, y0)
 *                    1,  238,  (x1, y1)
 *                    318,238,  (x2, y2)
 *                  };
 * num_points = 3;
 */
void gfx_Polygon(int *points, unsigned num_points);
void gfx_Polygon_NoClip(int *points, unsigned num_points);

/**
 * Draws a filled triangle measured from the top left origin
 */
void gfx_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
void gfx_FillTriangle_NoClip(int x0, int y0, int x1, int y1, int x2, int y2);

/**
 * Forces all graphics routines to write to either the offscreen buffer or to the screen
 */
void gfx_SetDraw(uint8_t buffer);
#define gfx_screen 0
#define gfx_buffer 1
#define gfx_SetDrawBuffer() gfx_SetDraw(gfx_buffer)
#define gfx_SetDrawScreen() gfx_SetDraw(gfx_screen)

/**
 * Returns false if graphics routines are currently drawing to visible screen
 * The current drawing location remains the same.
 */
uint8_t gfx_GetDraw(void);

/**
 * Swaps the buffer with the visible screen and vice versa.
 * The current drawing location remains the same.
 */
void gfx_SwapDraw(void);

/**
 * Copies the input buffer to the opposite buffer (No clipping is performed; as it is a copy not a draw)
 * Arguments:
 *  gfx_screen: copies screen to buffer
 *  gfx_buffer: copies buffer to screen
 */
void gfx_Blit(uint8_t buffer);
void gfx_BlitLines(uint8_t buffer, uint8_t y_loc, uint8_t num_lines);
void gfx_BlitRectangle(uint8_t buffer, uint24_t x, uint8_t y, uint24_t width, uint24_t height);
#define gfx_BlitScreen() gfx_Blit(gfx_screen)
#define gfx_BlitBuffer() gfx_Blit(gfx_buffer)

/**
 * Scales text in integer steps. Values in the range from 1-5 are preferred.
 */
void gfx_SetTextScale(uint8_t width_scale, uint8_t height_scale);

/**
 * Outputs a character at the current cursor position
 * By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 */
void gfx_PrintChar(const char c);

/**
 * Outputs a signed integer at the current cursor position.
 * By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 * Values range from: (-8388608 - 8388607)
 * length must be between 0-8
 */
void gfx_PrintInt(int n, uint8_t length);

/**
 * Outputs an unsigned integer at the current cursor position.
 * By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 * Values range from: (0-16777215)
 * length must be between 0-8
 */
void gfx_PrintUInt(unsigned n, uint8_t length);

/**
 * Outputs a string at the current cursor position
 * By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 */
void gfx_PrintString(const char *string);

/**
 * Outputs a string at the given XY coordinates measured from the top left origin.
 * The current cursor position is updated.
 * By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 */
void gfx_PrintStringXY(const char *string, int x, int y);

/**
 * Returns the current text cursor X position
 */
int gfx_GetTextX(void);

/**
 * Returns the current text cursor Y position
 */
int gfx_GetTextY(void);

/**
 * Sets the text cursor XY position
 */
void gfx_SetTextXY(int x, int y);

/**
 * Sets the configuration for the text routines. The current options are:
 * GFX_TEXT_CLIP     - Default, text routines do not clip (much faster)
 * GFX_TEXT_NOCLIP   - Text routines will clip against the defined clip window
 *
 * Clipped text does not scale text
 */
void gfx_SetTextConfig(uint8_t config);
#define GFX_TEXT_CLIP   1
#define GFX_TEXT_NOCLIP 2

/**
 * Sets the text foreground (FG), background (BG), and transparent (TP) color indexes
 * Returns previous text color index
 * Defaults:
 *  FG = 0x00
 *  BG = 0xFF
 *  TP = 0xFF
 */
uint8_t gfx_SetTextFGColor(uint8_t color);
uint8_t gfx_SetTextBGColor(uint8_t color);
uint8_t gfx_SetTextTransparentColor(uint8_t color);

/**
 * Draws a given sprite to the screen
 */
void gfx_Sprite(gfx_image_t *data, int x, int y);
void gfx_Sprite_NoClip(gfx_image_t *data, uint24_t x, uint8_t y);

/**
 * Draws a given sprite to the screen using transparency
 */
void gfx_TransparentSprite(gfx_image_t *data, int x, int y);
void gfx_TransparentSprite_NoClip(gfx_image_t *data, uint24_t x, uint8_t y);

/**
 * Quickly grab the background behind a sprite (useful for transparency)
 * sprite_buffer must be pointing to a large enough buffer to hold width*height number of bytes
 * A pointer to sprite_buffer is also returned for ease of use.
 * sprite_buffer is updated with the screen coordinates given.
 */
gfx_image_t *gfx_GetSprite(gfx_image_t *sprite_buffer, int x, int y);
#define gfx_GetSprite_NoClip gfx_GetSprite

/**
 * Unclipped scaled sprite routines
 * Scaling factors must be greater than or equal to 1, and an integer factor
 * Useable with gfx_GetSprite in order to create clipped versions
 */
void gfx_ScaledSprite_NoClip(gfx_image_t *data, int x, int y, uint8_t width_scale, uint8_t height_scale);
void gfx_ScaledTransparentSprite_NoClip(gfx_image_t *data, int x, int y, uint8_t width_scale, uint8_t height_scale);

/**
 * Sprite flipping and rotating routines
 * sprite_in and sprite_out cannot be the same buffer (exception is a half rotation)
 * sprite_out must be the same size as sprite_in
 * Returns a pointer to sprite_out
 */
gfx_image_t *gfx_FlipSpriteX(gfx_image_t *sprite_in, gfx_image_t *sprite_out);
gfx_image_t *gfx_FlipSpriteY(gfx_image_t *sprite_in, gfx_image_t *sprite_out);
gfx_image_t *gfx_RotateSpriteC(gfx_image_t *sprite_in, gfx_image_t *sprite_out);
gfx_image_t *gfx_RotateSpriteCC(gfx_image_t *sprite_in, gfx_image_t *sprite_out);
gfx_image_t *gfx_RotateSpriteHalf(gfx_image_t *sprite_in, gfx_image_t *sprite_out);

/**
 * Creates a temporary sprite for the character c. This may be useful for performing rotations and other
 * operations on characters? The sprite returned is always 8x8 pixels.
 */
gfx_image_t *gfx_GetSpriteChar(char c);

/**
 * Set the font routines to use the provided font, formated 8x8
 */
void gfx_SetFontData(uint8_t *fontdata);

/**
 * Set the font routines to use the provided font spacing
 */
void gfx_SetFontSpacing(uint8_t *fontspacing);

/**
 * To disable monospaced font, gfx_SetFontMonospace(0)
 * Otherwise, send the width in pixels you wish all characters to be
 */
void gfx_SetMonospaceFont(uint8_t monospace);

/**
 * Returns the width of the input string
 * Takes into account monospacing flag
 */
unsigned int gfx_GetStringWidth(const char *string);

/**
 * Returns the width of the character
 * Takes into account monospacing flag
 */
unsigned int gfx_GetCharWidth(const char c);
#define gfx_GetCharHeight(c) 8
#define gfx_FontHeight()     8

/**
 * Sets the clipping window for clipped routines
 * This routine is exclusive
 */
void gfx_SetClipRegion(int xmin, int ymin, int xmax, int ymax);

/**
 * Clips an arbitrary region to fit within the defined bounds
 * Returns false if offscreen, true if onscreen
 */
bool gfx_GetClipRegion(gfx_region_t *region);

/**
 * Screen shifting routines that operate within the clipping window
 * Note that the data left over is undefined (Must be drawn over)
 */
void gfx_ShiftDown(uint8_t pixels);
void gfx_ShiftUp(uint8_t pixels);
void gfx_ShiftLeft(uint24_t pixels);
void gfx_ShiftRight(uint24_t pixels);

/**
 * Lightens a given 1555 color; useful for palette color conversions.
 * amt as 0 means full white, 255 returns original color, in between returns lightened color
 */
uint16_t gfx_Lighten(uint16_t color, uint8_t amt);

/**
 * Darkens a given 1555 color; useful for palette color conversions.
 * amt as 0 returns full black, 255 returns original color, in between returns darkened color
 */
uint16_t gfx_Darken(uint16_t color, uint8_t amt);

/**
 * Converts an RGB value to a palette color
 * Conversion is not 100% perfect, but is quite close
 */
#define gfx_RGBTo1555(r,g,b) ((uint16_t)(((uint8_t)(r) >> 3) << 10) | \
                             (((uint8_t)(g) >> 3) << 5) | \
                             ((uint8_t)(b) >> 3))

/**
 * Checks if we are currently in a rectangular hotspot area
 */
#define gfx_CheckRectangleHotspot(master_x, master_y, master_width, master_height, test_x, test_y, test_width, test_height) \
           (((test_x) < ((master_x) + (master_width))) && \
           (((test_x) + (test_width)) > (master_x)) && \
           ((test_y) < ((master_y) + (master_height))) && \
           (((test_y) + (test_height)) > (master_y)))

#define gfx_lcdWidth    (320)
#define gfx_lcdHeight   (240)

/**
 * Some simple color definitions using the standard palette
 */
#define gfx_black       0x00
#define gfx_red         0xE0
#define gfx_orange      0xE3
#define gfx_green       0x03
#define gfx_blue        0x10
#define gfx_purple      0x50
#define gfx_yellow      0xE7
#define gfx_pink        0xF0
#define gfx_white       0xFF

/**
 * Compatability defines (don't use please)
 */
#define gfx_BlitArea gfx_BlitRectangle
void gfx_LZDecompress(uint8_t *in, uint8_t *out, unsigned int in_size);

#endif
