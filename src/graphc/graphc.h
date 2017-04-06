#warning The graphc library is deprecated! The graphx library should be used instead.
#warning The graphc library is deprecated! The graphx library should be used instead.
#warning The graphc library is deprecated! The graphx library should be used instead.
#warning The graphc library is deprecated! The graphx library should be used instead.
#warning The graphc library is deprecated! The graphx library should be used instead.
#warning The graphc library is deprecated! The graphx library should be used instead.

/**
 * @file
 * @authors Matt "MateoConLechuga" Waltz
 * @authors Jacob "jacobly" Young
 * @brief Deprecated graphics operations and routines
 */

#ifndef H_GRAPHC
#define H_GRAPHC
#include <stdint.h>
#include <stdbool.h>
void gc_InitGraph(void);
void gc_CloseGraph(void);
uint16_t gc_paletteArray[256] _At 0xE30200;
uint16_t (*gc_vramArray)[240][320] _At 0xD40000;
#define gc_RandInt(min, max) ((unsigned)rand() % ((max) - (min) + 1) + (min))
#define gc_CheckRectangleHotspot(master_x, master_y, master_width, master_height, test_x, test_y, test_width, test_height) \
	  (test_x < master_x + master_width && \
	   test_x + test_width > master_x && \
	   test_y < master_y + master_height && \
	   test_y + test_height > master_y)
typedef struct gc_region {
	int24_t x_left, y_top, x_right, y_bottom;
} gc_region_t;
typedef struct gc_tilemap {
	uint8_t *map;
	uint8_t **tiles;
	uint8_t tile_height;
	uint8_t tile_width;
	uint8_t draw_height;
	uint8_t draw_width;
	uint8_t type_width;
	uint8_t type_height;
	uint8_t height;
	uint8_t width;
	uint8_t y_loc;
	uint24_t x_loc;
} gc_tilemap_t;
typedef enum gc_tilemap_type {
	gc_tile_2_pixel = 1,
	gc_tile_4_pixel,
	gc_tile_8_pixel,
	gc_tile_16_pixel,
	gc_tile_32_pixel,
	gc_tile_64_pixel,
	gc_tile_128_pixel,
} gc_tilemap_type_t;
#define gc_NoClipPixelPtr(x, y)           ((uint8_t*)(gc_drawingBuffer + (uint16_t)x + ((uint8_t)y)*320))
#define gc_NoClipSetPixel(x, y, c)        (*(gc_NoClipPixelPtr(x,y)) = c)
#define gc_NoClipGetPixel(x, y)           (*(gc_NoClipPixelPtr(x,y)))
#define gc_RGBTo1555(r,g,b)               ((unsigned short)(((unsigned char)(r) >> 3) << 10) | (((unsigned char)(g) >> 3) << 5) | ((unsigned char)(b) >> 3))
#define gc_FontHeight()                   8
#define gc_drawingBuffer                  (*(uint8_t**)(0xE30014))
#define gc_lcdWidth                       320
#define gc_lcdHeight                      240
void gc_ClipDrawBGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gc_NoClipDrawBGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gc_ClipDrawFGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
void gc_NoClipDrawFGTilemap(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
uint8_t *gc_TilePtr(gc_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);
uint8_t *gc_TilePtrMapped(gc_tilemap_t *tilemap, uint8_t x_offset, uint8_t y_offset);
void gc_LZDecompress(uint8_t *in, uint8_t *out, unsigned in_size);
uint8_t gc_SetColorIndex(uint8_t index);
void gc_SetDefaultPalette(void);
void gc_SetPalette(uint16_t *palette, uint16_t paletteSize);
void gc_FillScrn(uint8_t color);
uint16_t gc_GetColor(uint8_t index);
void gc_SetColor(uint8_t index, uint16_t color);
void gc_ClipSetPixel(int24_t x, int24_t y);
uint8_t gc_ClipGetPixel(int24_t x, int24_t y);
void gc_NoClipLine(uint16_t x0, uint8_t y0, uint16_t x1, uint8_t y1);
void gc_NoClipRectangle(uint16_t x, uint8_t y, uint16_t width, uint8_t height);
void gc_NoClipRectangleOutline(uint16_t x, uint8_t y, uint16_t width, uint8_t height);
void gc_NoClipHorizLine(uint16_t x, uint8_t y, uint16_t length);
void gc_NoClipVertLine(uint16_t x, uint8_t y, uint8_t length);
void gc_NoClipCircle(uint16_t x, uint8_t y, unsigned radius);
void gc_ClipCircle(int x, int y, unsigned radius);
void gc_ClipCircleOutline(int x, int y, unsigned radius);
void gc_DrawBuffer(void);
void gc_DrawScreen(void);
void gc_SwapDraw(void);
uint8_t gc_DrawState(void);
void gc_PrintChar(const char c);
void gc_PrintInt(int n, uint8_t length);
void gc_PrintUnsignedInt(unsigned int n, uint8_t length);
void gc_PrintString(const char *string);
void gc_PrintStringXY(const char *string, uint16_t x, uint8_t y);
uint16_t gc_TextX(void);
uint8_t gc_TextY(void);
void gc_SetTextXY(uint16_t x, uint8_t y);
uint16_t gc_SetTextColor(uint16_t color);
uint8_t gc_SetTransparentColor(uint8_t color);
void gc_NoClipDrawSprite(uint8_t *data, uint16_t x, uint8_t y, uint8_t width, uint8_t height);
void gc_NoClipDrawTransparentSprite(uint8_t *data, uint16_t x, uint8_t y, uint8_t width, uint8_t height);
uint8_t *gc_NoClipGetSprite(uint8_t *spriteBuffer, uint16_t x, uint8_t y, uint8_t width, uint8_t height);
void gc_SetCustomFontData(uint8_t *fontdata);
void gc_SetCustomFontSpacing(uint8_t *fontspacing);
void gc_SetFontMonospace(uint8_t monospace);
uint24_t gc_StringWidth(const char *string);
uint24_t gc_CharWidth(const char c);
void gc_ClipDrawSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height);
void gc_ClipDrawTransparentSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height);
#define gc_ClipGetSprite gc_NoClipGetSprite
void gc_SetClipWindow(int24_t xmin, int24_t ymin, int24_t xmax, int24_t ymax);
bool gc_ClipRegion(gc_region_t *region);
void gc_ShiftWindowDown(uint24_t pixels);
void gc_ShiftWindowUp(uint24_t pixels);
void gc_ShiftWindowLeft(uint24_t pixels);
void gc_ShiftWindowRight(uint24_t pixels);
void gc_ClipRectangle(int24_t x, int24_t y, uint24_t width, uint24_t height);
void gc_ClipRectangleOutline(int24_t x, int24_t y, uint24_t width, uint24_t height);
void gc_ClipHorizLine(int24_t x, int24_t y, uint24_t length);
void gc_ClipVertLine(int24_t x, int24_t y, uint24_t length);
bool gc_ClipLine(int24_t x0, int24_t y0, int24_t x1, int24_t y1);
void gc_NoClipDrawScaledSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height, uint8_t width_scale, uint8_t height_scale);
void gc_NoClipDrawScaledTransparentSprite(uint8_t *data, int24_t x, int24_t y, uint8_t width, uint8_t height, uint8_t width_scale, uint8_t height_scale);
#endif
