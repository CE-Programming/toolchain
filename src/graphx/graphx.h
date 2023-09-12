/**
 * @file
 *
 * The below example template shows the best graphx buffer usage pattern:
 * @code{.cpp}
 * // Standard #includes omitted
 *
 * bool partial_redraw;
 *
 * // Implement us!
 * void begin();
 * void end();
 * bool step();
 * void draw();
 *
 * void main() {
 *     begin(); // No rendering allowed!
 *     gfx_Begin();
 *     gfx_SetDrawBuffer(); // Draw to the buffer to avoid rendering artifacts
 *
 *     while (step()) { // No rendering allowed in step!
 *         if (partial_redraw) // Only redraw part of the previous frame?
 *             gfx_BlitScreen(); // Copy previous frame as a base for this frame
 *         draw(); // As little non-rendering logic as possible
 *         gfx_SwapDraw(); // Queue the buffered frame to be displayed
 *     }
 *
 *     gfx_End();
 *     end();
 * }
 * @endcode
 *
 * @authors Matt "MateoConLechuga" Waltz <br/>
 *          Jacob "jacobly" Young <br/>
 *          Zachary "Runer112" Wassall <br/>
 *          Patrick "tr1p1ea" Prendergast <br/>
 *          Peter "PT_" Tillema <br/>
 *          "grosged"
 */

#ifndef GRAPHX_H
#define GRAPHX_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sprite (image) type.
 *
 * Whether or not a sprite includes transparency is not explicitly encoded, and
 * is determined only by usage. If used with transparency, transparent pixels
 * are those with a certain color index, which can be set with
 * gfx_SetTransparentColor().
 *
 * @note
 * Displaying a gfx_rletsprite_t (which includes transparency) is significantly
 * faster than displaying a gfx_sprite_t with transparency, and should be
 * preferred. However, gfx_rletsprite_t does not support transformations, such
 * as flipping and rotation. Such transformations can be applied to a
 * gfx_sprite_t, which can then be converted to a gfx_rletsprite_t for faster
 * display using gfx_ConvertToNewRLETSprite() or gfx_ConvertToRLETSprite().
 *
 * @remarks
 * Create at compile-time with a tool like
 * <a href="https://github.com/mateoconlechuga/convimg" target="_blank">convimg</a>.
 * Create at runtime (with uninitialized data) with gfx_MallocSprite(),
 * gfx_UninitedSprite(), or gfx_TempSprite().
 */
typedef struct gfx_sprite_t {
    uint8_t width;   /**< Width of the image.  */
    uint8_t height;  /**< Height of the image. */
    uint8_t data[]; /**< Image data array.    */
} gfx_sprite_t;

/**
 * Sprite (image) type with RLE transparency.
 *
 * @attention
 * Displaying a gfx_rletsprite_t (which includes transparency) is significantly
 * faster than displaying a gfx_sprite_t with transparency, and should be
 * preferred. However, gfx_rletsprite_t does not support transformations, such
 * as flipping and rotation. Such transformations can be applied to a
 * gfx_sprite_t, which can then be converted to a gfx_rletsprite_t for faster
 * display using gfx_ConvertToNewRLETSprite() or gfx_ConvertToRLETSprite().
 *
 * @remarks
 * Create at compile-time with a tool like
 * <a href="https://github.com/mateoconlechuga/convimg" target="_blank">convimg</a>.
 */
typedef struct gfx_rletsprite_t {
    uint8_t width; /**< Width of the image. */
    uint8_t height; /**< Height of the image. */
    uint8_t data[]; /**< Image data array. */
} gfx_rletsprite_t;

/**
 * A structure for working with 2D points.
 */
typedef struct gfx_point_t {
    int x; /**< x point. */
    int y; /**< y point. */
} gfx_point_t;

/**
 * Defines a rectangular graphics region.
 *
 * @see gfx_GetClipRegion
 */
typedef struct gfx_region_t {
    int xmin; /**< Minimum x coordinate. */
    int ymin; /**< Minimum y coordinate. */
    int xmax; /**< Maximum x coordinate. */
    int ymax; /**< Maximum y coordinate. */
} gfx_region_t;

/**
 * Defines tilemap structure
 *
 * @see gfx_Tilemap
 */
typedef struct gfx_tilemap_t {
    uint8_t *map;            /**< Pointer to tilemap array. */
    gfx_sprite_t **tiles;    /**< Pointer to tileset sprites for the tilemap. */
    uint8_t tile_height;     /**< Individual tile height. */
    uint8_t tile_width;      /**< Individual tile width. */
    uint8_t draw_height;     /**< Number of tilemap rows to draw. */
    uint8_t draw_width;      /**< Number of tilemap columns to draw. */
    uint8_t type_width;      /**< Tile type height @see gfx_tilemap_type_t. */
    uint8_t type_height;     /**< Tile type width @see gfx_tilemap_type_t. */
    uint8_t height;          /**< Total number of rows in the tilemap. */
    uint8_t width;           /**< Total number of columns in the tilemap. */
    uint8_t y_loc;           /**< Y pixel location on the screen for the tilemap. */
    uint24_t x_loc;          /**< X pixel location on the screen for the tilemap. */
} gfx_tilemap_t;

/**
 * Stores operating modes of this library.
 * @see gfx_Begin.
 */
typedef enum {
    gfx_8bpp = 0x27 /**< Enable 8 bits per pixel mode. */
} gfx_mode_t;

/**
 * Used for defining tile types.
 *
 * @see gfx_tilemap_t.
 */
typedef enum {
    gfx_tile_no_pow2 = 0,     /**< Use when the tile width/height is not a power of 2. */
    gfx_tile_2_pixel,         /**< Use when the tile width/height is 2 pixels. */
    gfx_tile_4_pixel,         /**< Use when the tile width/height is 4 pixels. */
    gfx_tile_8_pixel,         /**< Use when the tile width/height is 8 pixels. */
    gfx_tile_16_pixel,        /**< Use when the tile width/height is 16 pixels. */
    gfx_tile_32_pixel,        /**< Use when the tile width/height is 32 pixels. */
    gfx_tile_64_pixel,        /**< Use when the tile width/height is 64 pixels. */
    gfx_tile_128_pixel        /**< Use when the tile width/height is 128 pixels. */
} gfx_tilemap_type_t;

/**
 * Different locations routines can be drawn to
 */
typedef enum {
    gfx_screen = 0, /**< Visible Screen. */
    gfx_buffer      /**< Non-visible Buffer. */
} gfx_location_t;

/**
 * Different available text modes.
 */
typedef enum {
    gfx_text_clip = 1, /**< Text routines will clip against the defined clip window. */
    gfx_text_noclip    /**< Default, text routines do not clip (much faster). */
} gfx_text_options_t;

/**
 * Direct LCD palette access via MMIO.
 *
 * The palette has 256 entries, each 2 bytes in size.
 */
#define gfx_palette \
((uint16_t*)0xE30200)

/**
 * Direct LCD VRAM access.
 *
 * Total of 153600 bytes in size.
 */
#define gfx_vram \
((uint8_t*)0xD40000)

/**
 * Number of pixels wide the screen is.
 */
#define GFX_LCD_WIDTH \
(320)

/**
 * Number of pixels high the screen is.
 */
#define GFX_LCD_HEIGHT \
(240)

/**
 * Direct LCD VRAM access of the current buffer.
 *
 * Total of 76800 bytes in size.
 */
#define gfx_vbuffer \
(**(uint8_t(**)[240][320])0xE30014)

/**
 * Makes graphics routines act on the non-visible buffer.
 */
#define gfx_SetDrawBuffer() \
gfx_SetDraw(gfx_buffer)

/**
 * Makes graphics routines act on the visible screen.
 */
#define gfx_SetDrawScreen() \
gfx_SetDraw(gfx_screen)

/**
 * Copies the contents of the screen to the buffer
 */
#define gfx_BlitScreen() \
gfx_Blit(gfx_screen)

/**
 * Copies the contents of the buffer to the screen
 */
#define gfx_BlitBuffer() \
gfx_Blit(gfx_buffer)

/**
 * Dynamically allocates memory for a sprite using \c malloc.
 *
 * \p width and \p height will be set in the sprite. Returns \c NULL upon
 * allocation failure.
 *
 * @note
 * If not used in a dynamic context and \p width and \p height are static,
 * consider statically allocating the sprite instead with gfx_UninitedSprite()
 * or gfx_TempSprite().
 *
 * @param[in] width Sprite width.
 * @param[in] height Sprite height.
 * @return A pointer to the allocated sprite, or NULL if the allocation failed.
 * @see gfx_AllocSprite
 */
#define gfx_MallocSprite(width, height) \
gfx_AllocSprite(width, height, malloc)

/**
 * Statically allocates uninitialized memory for a sprite.
 *
 * Declares a <tt>gfx_sprite_t *</tt> with the given \p name pointing to the
 * allocated memory. \p width and \p height will \b not be set in the sprite,
 * unlike gfx_TempSprite().
 *
 * @warning
 * If used outside of a function body, the memory will be allocated in the
 * global uninitialized data segment (BSS). If used inside a function body, the
 * memory will be allocated on the stack. If the sprite is sufficiently large,
 * usage inside a function body will overflow the stack, so it is recommended
 * that this normally be used outside of a function body.
 *
 * @param[in] name Name of declared <tt>gfx_sprite_t *</tt>.
 * @param[in] width Sprite width.
 * @param[in] height Sprite height.
 * @see gfx_MallocSprite()
 */
#define gfx_UninitedSprite(name, width, height) \
uint8_t name##_data[2 + (width) * (height)]; \
gfx_sprite_t *name = (gfx_sprite_t *)name##_data

/**
 * Statically allocates memory for a sprite.
 *
 * Declares a <tt>gfx_sprite_t *</tt> with the given \p name pointing to the
 * allocated memory. \p width and \p height will be set in the sprite, unlike
 * gfx_UninitedSprite().
 *
 * @attention
 * Due to \p width and \p height being set, the memory will be allocated in the
 * initialized data segment. If the compiled program is not compressed, then
 * this could be a serious source of bloat and gfx_UninitedSprite() should be
 * preferred.
 *
 * @param[in] name Name of declared <tt>gfx_sprite_t *</tt>.
 * @param[in] width Sprite width.
 * @param[in] height Sprite height.
 * @see gfx_MallocSprite()
 */
#define gfx_TempSprite(name, width, height) \
uint8_t name##_data[2 + (width) * (height)] = { (width), (height) }; \
gfx_sprite_t *name = (gfx_sprite_t *)name##_data

/**
 * Dynamically allocates memory for a sprite with RLE transparency.
 *
 * Allocates the memory with \p malloc_routine. Returns \c NULL upon allocation
 * failure.
 *
 * \p data_size is the maximum predicted/calculated size of the sprite data
 * (excluding the width and height bytes) that will be stored in the allocated
 * sprite.
 * Sprite data size could be up to <tt>(width + 1) * height * 3 / 2</tt>
 * bytes in the worst case, in which pixels horizontally alternate between
 * non-transparent and transparent and each row begins with a non-transparent
 * pixel. But if the average length of a horizontal transparent run is at least
 * 2, then the sprite data will be no larger than <tt>(width + 1) * height</tt>
 * bytes. The exact data size necessary is <tt>2 * hr + nont + rnont - ret</tt>
 * bytes, where:
 *
 * <tt>hr</tt>: Number of horizontal transparent runs.
 *
 * <tt>nont</tt>: Number of non-transparent runs.
 *
 * <tt>rnont</tt>: Number of rows beginning with a non-transparent pixel.
 *
 * <tt>rbnont</tt>: Number of rows beginning with a non-transparent pixel.
 *
 * <tt>ret</tt>: Number of rows ending with a transparent pixel.
 *
 * @note
 * If not used in a dynamic context and \p data_size is static, consider
 * statically allocating the sprite instead with gfx_UninitedRLETSprite() or
 * gfx_TempRLETSprite().
 *
 * @remarks
 * If using \c malloc as the \p malloc_routine, gfx_MallocRLETSprite() can be
 * used as a shortcut.
 *
 * @param[in] data_size (Maximum) sprite data size.
 * @param[in] malloc_routine Malloc implementation to use.
 * @return A pointer to the allocated sprite, or NULL if the allocation failed..
 */
#define gfx_AllocRLETSprite(data_size, malloc_routine) \
((gfx_rletsprite_t *)(malloc_routine)(data_size))

/**
 * Dynamically allocates memory for a sprite with RLE transparency using \c
 * malloc.
 *
 * \p data_size is the size to allocate for sprite data; see
 * gfx_AllocRLETSprite() for information. Returns \c NULL upon allocation
 * failure.
 *
 * @note
 * If not used in a dynamic context and \p data_size is static, consider
 * statically allocating the sprite instead with gfx_UninitedRLETSprite() or
 * gfx_TempRLETSprite().
 *
 * @param[in] data_size (Maximum) sprite data size.
 * @return A pointer to the allocated sprite, or NULL if the allocation failed.
 * @see gfx_AllocRLETSprite()
 */
#define gfx_MallocRLETSprite(data_size) \
gfx_AllocRLETSprite(data_size, malloc)

/**
 * Statically allocates uninitialized memory for a sprite with RLE transparency.
 *
 * Declares a <tt>gfx_rletsprite_t *</tt> with the given \p name pointing to
 * the allocated memory. \p data_size is the size to allocate for sprite data;
 * see gfx_AllocRLETSprite() for information.
 *
 * @warning
 * If used outside of a function body, the memory will be allocated in the
 * global uninitialized data segment (BSS). If used inside a function body, the
 * memory will be allocated on the stack. If the sprite is sufficiently large,
 * usage inside a function body will overflow the stack, so it is recommended
 * that this normally be used outside of a function body.
 *
 * @param[in] name Name of declared <tt>gfx_rletsprite_t *</tt>.
 * @param[in] data_size (Maximum) sprite data size.
 * @see gfx_MallocRLETSprite()
 */
#define gfx_UninitedRLETSprite(name, data_size) \
uint8_t name##_data[2 + (data_size)]; \
gfx_rletsprite_t *name = (gfx_rletsprite_t *)name##_data

/**
 * Sets a particular tile's sprite tileset index.
 * This function bases position on the pixel offset from the top-left of the tilemap.
 *
 * @param tilemap Pointer to initialized tilemap structure.
 * @param x_offset Offset in pixels from the left of the tilemap.
 * @param y_offset Offset in pixels from the top of the tilemap.
 * @param value Sprite index in tileset.
 */
#define gfx_SetTile(tilemap, x_offset, y_offset, value) \
(*(gfx_TilePtr((tilemap), (x_offset), (y_offset))) = (uint8_t)(value))

/**
 * Gets a particular tile's sprite tileset index.
 * This function bases position on the pixel offset from the top-left of the tilemap.
 *
 * @param[in] tilemap Pointer to an initialized tilemap structure.
 * @param[in] x_offset Offset in pixels from the left of the tilemap.
 * @param[in] y_offset Offset in pixels from the top of the tilemap.
 */
#define gfx_GetTile(tilemap, x_offset, y_offset) \
(*(gfx_TilePtr((tilemap), (x_offset), (y_offset))))

/**
 * Sets a particular tile's sprite tileset index.
 * This function uses the corrdinates from the tilemap array.
 *
 * @param[in] tilemap Pointer to initialized tilemap structure.
 * @param[in] col Column of tile in tilemap.
 * @param[in] row Row of tile in tilemap.
 * @param[in] value Sprite index in tileset.
 */
#define gfx_SetTileMapped(tilemap, col, row, value) \
(*(gfx_TilePtrMapped((tilemap), (col), (row))) = (uint8_t)(value))

/**
 * Gets a particular tile's sprite tileset index.
 * This function uses the corrdinates from the tilemap array.
 *
 * @param[in] tilemap Pointer to an initialized tilemap structure.
 * @param[in] col Column of tile in tilemap.
 * @param[in] row Row of tile in tilemap.
 */
#define gfx_GetTileMapped(tilemap, col, row) \
(*(gfx_TilePtrMapped((tilemap), (col), (row))))

/**
 * Draws an unclipped circle outline.
 *
 * Performs faster than using gfx_Circle, but can cause corruption if used outside the bounds of the screen.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] radius The radius of the circle.
 */
#define gfx_Circle_NoClip(x, y, radius) \
gfx_Circle((x), (y), (radius))

/**
 * Grabs the background behind an unclipped sprite.
 *
 * This is useful for partial redraw.
 * @param[out] sprite_buffer Buffer used to store grabbed sprite.
 * @param[in] x X coordinate to grab sprite.
 * @param[in] y Y coordinate to grab sprite.
 * @returns A pointer to sprite_buffer.
 * @note \p sprite_buffer must be pointing to a large enough buffer to hold
 *       (width * height + 2) number of bytes.
 */
#define gfx_GetSprite_NoClip(sprite_buffer, x, y) \
gfx_GetSprite((sprite_buffer), (x), (y))

/**
 * Helper macro to only perform rotation using
 * gfx_RotatedScaledTransparentSprite_NoClip.
 *
 * @param[in] sprite Input sprite to rotate/scale.
 * @param[in] x X coordinate position.
 * @param[in] y Y coordinate position.
 * @param[in] angle 256 position angular integer.
 * @see gfx_RotatedScaledTransparentSprite_NoClip.
 */
#define gfx_RotatedTransparentSprite_NoClip(sprite, x, y, angle) \
gfx_RotatedScaledTransparentSprite_NoClip(sprite, x, y, angle, 64)

/**
 * Helper macro to only perform rotation using
 * gfx_RotatedScaledSprite_NoClip.
 *
 * @param[in] sprite Input sprite to rotate/scale.
 * @param[in] x X coordinate position.
 * @param[in] y Y coordinate position.
 * @param[in] angle 256 position angular integer.
 * @see gfx_RotatedScaledTransparentSprite_NoClip.
 */
#define gfx_RotatedSprite_NoClip(sprite, x, y, angle) \
gfx_RotatedScaledSprite_NoClip(sprite, x, y, angle, 64)

/**
 * Helper macro to only perform rotation using gfx_RotateScaleSprite.
 *
 * @param[in] sprite_in Input sprite to rotate.
 * @param[out] sprite_out Pointer to where rotated sprite will be stored.
 * @param[in] angle 256 position angular integer.
 * @returns A pointer to \p sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 * @see gfx_RotateScaleSprite.
 */
#define gfx_RotateSprite(sprite_in, sprite_out, angle) \
gfx_RotateScaleSprite(sprite_in, sprite_out, angle, 64)

/**
 * Converts a sprite with normal transparency to a sprite with RLE transparency,
 * allocating the exact amount of necessary space for the converted sprite using
 * \c malloc.
 *
 * Width and height will be set in the converted sprite. Returns \c NULL upon
 * allocation failure.
 *
 * The transparent color index in the input sprite is controlled by
 * gfx_SetTransparentColor().
 *
 * @remarks
 * A gfx_sprite_t can be converted into an appropriately large,
 * already-allocated gfx_rletsprite_t using gfx_ConvertToRLETSprite().
 *
 * @param[in] sprite_in Input sprite with normal transparency.
 * @returns A newly allocated converted sprite with RLE transparency.
 * @see gfx_ConvertFromRLETSprite.
 */
#define gfx_ConvertMallocRLETSprite(sprite_in) \
gfx_ConvertToNewRLETSprite(sprite_in, malloc)

/**
 * Converts an RGB value to a palette color.
 *
 * @param[in] r Red value (0-255).
 * @param[in] g Green value (0-255).
 * @param[in] b Blue value (0-255).
 * @note Conversion is not 100% perfect, but is good enough in most cases.
 */
#define gfx_RGBTo1555(r,g,b) \
((uint16_t)(((((r) & 255) >> 3) << 10) | ((((g) & 255) >> 3) << 5) | (((b) & 255) >> 3)))

/**
 * Tests if a rectangular area intersects/collides with another rectangular area.
 * @param[in] x0 Rectangle 0 X coordinate
 * @param[in] y0 Rectangle 0 Y coordinate
 * @param[in] w0 Rectangle 0 width
 * @param[in] h0 Rectangle 0 height
 * @param[in] x1 Rectangle 1 X coordinate
 * @param[in] y1 Rectangle 1 Y coordinate
 * @param[in] w1 Rectangle 1 width
 * @param[in] h1 Rectangle 1 height
 * @returns true if the rectangles are intersecting.
 */
#define gfx_CheckRectangleHotspot(x0, y0, w0, h0, x1, y1, w1, h1) \
(((x1) < ((x0) + (w0))) && \
(((x1) + (w1)) > (x0)) && \
((y1) < ((y0) + (h0))) && \
(((y1) + (h1)) > (y0)))

/* byte 0 of compressed data is always literal - is the width */
#define gfx_GetZX7SpriteWidth(zx7_sprite)                     \
    __extension__({                                           \
        const uint8_t *_Data = (const uint8_t *)(zx7_sprite); \
        _Data[0];                                             \
    })

/* byte 1 of compressed data is flag. If bit 7 set, copy byte 0, else byte 2 */
#define gfx_GetZX7SpriteHeight(zx7_sprite)                    \
    __extension__({                                           \
        const uint8_t *_Data = (const uint8_t *)(zx7_sprite); \
        _Data[_Data[1] & 0x80 ? 0 : 2];                       \
    })

/**
 * Calculates the amount of memory that a zx7-compressed
 * sprite would use when decompressed.
 *
 * Sprite size is calculated as 2 + (width * height).
 *
 * ZX7 data always starts with a literal, which is the sprite's width. The next
 * byte contains flags, which indicates if the following bytes are literals or
 * codewords. If bit 7 of that is zero, the byte immediately after it is a
 * literal and can be read in as sprite height. Otherwise, the bits that follows
 * indicates a codeword, making sprite height the same as width.
 *
 * @param[in] zx7_sprite ZX7-compressed sprite
 * @return Size, in bytes, of decompressed sprite
*/
#define gfx_GetZX7SpriteSize(zx7_sprite)                                      \
    __extension__({                                                           \
        const void *_Sprite = (const void *)(zx7_sprite);                     \
        2 + gfx_GetZX7SpriteWidth(_Sprite) * gfx_GetZX7SpriteHeight(_Sprite); \
    })

/**
 * Initializes the `graphx` library context.
 *
 * This function should be called before any other `graphx` library routines.
 */
void gfx_Begin();

/**
 * Ends the `graphx` library context.
 *
 * Restores the LCD to 16bpp and clears the screen.
 * 16bpp is used by the OS, so if you don't call this, the screen will look
 * weird and won't work right.
 */
void gfx_End(void);

/**
 * Dynamically allocates memory for a sprite.
 *
 * Allocates the memory with \p malloc_routine. \p width and \p height will be
 * set in the allocated sprite. Returns \c NULL upon allocation failure.
 *
 * @note
 * If not used in a dynamic context and \p width and \p height are static,
 * consider statically allocating the sprite instead with gfx_UninitedSprite()
 * or gfx_TempSprite().
 *
 * @remarks
 * If using \c malloc as the \p malloc_routine, gfx_MallocSprite() can be used
 * as a shortcut.
 *
 * @param[in] width Sprite width.
 * @param[in] height Sprite height.
 * @param[in] malloc_routine Malloc implementation to use.
 * @return A pointer to the allocated sprite.
 */
gfx_sprite_t *gfx_AllocSprite(uint8_t width,
                              uint8_t height,
                              void *(*malloc_routine)(size_t));

/**
 * Draws a tilemap.
 *
 * @param[in] tilemap Pointer to initialized tilemap structure.
 * @param[in] x_offset Offset in pixels from the left of the tilemap.
 * @param[in] y_offset Offset in pixels from the top of the tilemap.
 * @see gfx_tilemap_t.
 */
void gfx_Tilemap(const gfx_tilemap_t *tilemap,
                 uint24_t x_offset,
                 uint24_t y_offset);

/**
 * Draws an unclipped tilemap.
 *
 * @param[in] tilemap Pointer to initialized tilemap structure.
 * @param[in] x_offset Offset in pixels from the left of the tilemap.
 * @param[in] y_offset Offset in pixels from the top of the tilemap.
 * @see gfx_tilemap_t.
 */
void gfx_Tilemap_NoClip(const gfx_tilemap_t *tilemap,
                            uint24_t x_offset,
                            uint24_t y_offset);

/**
 * Draws a transparent tilemap.
 *
 * @param[in] tilemap Pointer to initialized tilemap structure.
 * @param[in] x_offset Offset in pixels from the left of the tilemap.
 * @param[in] y_offset Offset in pixels from the top of the tilemap.
 * @see gfx_tilemap_t.
 */
void gfx_TransparentTilemap(const gfx_tilemap_t *tilemap,
                            uint24_t x_offset,
                            uint24_t y_offset);

/**
 * Draws an unclipped transparent tilemap.
 *
 * @param[in] tilemap Pointer to initialized tilemap structure.
 * @param[in] x_offset Offset in pixels from the left of the tilemap.
 * @param[in] y_offset Offset in pixels from the top of the tilemap.
 * @see gfx_tilemap_t.
 */
void gfx_TransparentTilemap_NoClip(const gfx_tilemap_t *tilemap,
                                   uint24_t x_offset,
                                   uint24_t y_offset);

/**
 * Gets a pointer to a particular sprite tileset index.
 * This function bases position on the pixel offset from the top-left of the tilemap.
 *
 * @param[in] tilemap Pointer to initialized tilemap structure.
 * @param[in] x_offset Offset in pixels from the left of the tilemap.
 * @param[in] y_offset Offset in pixels from the top of the tilemap.
 */
uint8_t *gfx_TilePtr(const gfx_tilemap_t *tilemap,
                     uint24_t x_offset,
                     uint24_t y_offset);

/**
 * Gets a pointer to a particular sprite tileset index.
 * This function uses the corrdinates from the tilemap array.
 *
 * @param[in] tilemap Pointer to an initialized tilemap structure.
 * @param[in] col Column of tile in tilemap.
 * @param[in] row Row of tile in tilemap.
 */
uint8_t *gfx_TilePtrMapped(const gfx_tilemap_t *tilemap,
                           uint8_t col,
                           uint8_t row);

/**
 * Sets the color index that drawing routines will use
 *
 * This applies to lines, rectangles, circles, etc.
 * @param[in] index Color index to set.
 * @returns Previous set color index.
 */
uint8_t gfx_SetColor(uint8_t index);

/**
 * Sets the transparent index that drawing routines will use
 *
 * This currently applies to transparent sprites, both scaled and unscaled
 * @param[in] index Transparent color index to set.
 * @returns The previous transparent color index.
 */
uint8_t gfx_SetTransparentColor(uint8_t index);

/**
 * Sets up the default palette for the given mode
 *
 * @param[in] mode Palette to use.
 */
void gfx_SetDefaultPalette(gfx_mode_t mode);

/**
 * Sets entries in the palette
 *
 * @param[in] palette Pointer to palette to set.
 * @param[in] size Size of palette in bytes.
 * @param[in] offset Palette index to insert at.
 */
void gfx_SetPalette(const void *palette,
                    uint24_t size,
                    uint8_t offset);

/**
 * Fills the screen with a given palette index.
 *
 * @param[in] index Pallete index to fill with.
 */
void gfx_FillScreen(uint8_t index);

/**
 * Implements a faster version of gfx_FillScreen(0).
 *
 * @see gfx_FillScreen.
 */
void gfx_ZeroScreen(void);

/**
 * Sets a pixel to the global color index.
 *
 * @note Pixels are only clipped within the screen boundaries, not the clip region.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @see gfx_SetColor
 */
void gfx_SetPixel(uint24_t x, uint8_t y);

/**
 * Gets a pixel's color index.
 *
 * @note Pixels are only clipped within the screen boundaries, not the clip region.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
uint8_t gfx_GetPixel(uint24_t x, uint8_t y);

/**
 * Draws a line.
 *
 * @param[in] x0 First X coordinate.
 * @param[in] y0 First Y coordinate.
 * @param[in] x1 Second X coordinate.
 * @param[in] y1 Second Y coordinate.
 */
void gfx_Line(int x0,
              int y0,
              int x1,
              int y1);

/**
 * Draws an unclipped line.
 *
 * @param[in] x0 First X coordinate.
 * @param[in] y0 First Y coordinate.
 * @param[in] x1 Second X coordinate.
 * @param[in] y1 Second Y coordinate.
 */
void gfx_Line_NoClip(uint24_t x0,
                     uint8_t y0,
                     uint24_t x1,
                     uint8_t y1);

/**
 * Draws a horizontal line.
 *
 * This routine is faster than gfx_Line for horizontal lines.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] length Length of line.
 */
void gfx_HorizLine(int x,
                   int y,
                   int length);

/**
 * Draws an unclipped horizontal line.
 *
 * This routine is faster than gfx_Line_NoClip for horizontal lines.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] length Length of line.
 */
void gfx_HorizLine_NoClip(uint24_t x,
                          uint8_t y,
                          uint24_t length);

/**
 * Draws a vertical line
 *
 * This routine is faster than gfx_Line for vertical lines.
 * @param[in] x X coordinate
 * @param[in] y Y coordinate
 * @param[in] length Length of line
 */
void gfx_VertLine(int x,
                  int y,
                  int length);

/**
 * Draws an unclipped vertical line.
 *
 * This routine is faster than gfx_Line_NoClip for vertical lines.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] length Length of line.
 */
void gfx_VertLine_NoClip(uint24_t x,
                         uint8_t y,
                         uint24_t length);

/**
 * Draws a rectangle outline.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] width Width of rectangle.
 * @param[in] height Height of rectangle.
 */
void gfx_Rectangle(int x,
                   int y,
                   int width,
                   int height);

/**
 * Draws an unclipped rectangle outline.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] width Width of rectangle.
 * @param[in] height Height of rectangle.
 */
void gfx_Rectangle_NoClip(uint24_t x,
                          uint8_t y,
                          uint24_t width,
                          uint8_t height);

/**
 * Draws a filled rectangle.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] width Width of rectangle.
 * @param[in] height Height of rectangle.
 */
void gfx_FillRectangle(int x,
                       int y,
                       int width,
                       int height);

/**
 * Draws an unclipped filled rectangle
 *
 * @param[in] x X coordinate
 * @param[in] y Y coordinate
 * @param[in] width Width of rectangle
 * @param[in] height Height of rectangle
 */
void gfx_FillRectangle_NoClip(uint24_t x,
                              uint8_t y,
                              uint24_t width,
                              uint8_t height);

/**
 * Draws a circle outline.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] radius The radius of the circle.
 */
void gfx_Circle(int x,
                int y,
                uint24_t radius);

/**
 * Draws a filled circle.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] radius The radius of the circle.
 */
void gfx_FillCircle(int x,
                    int y,
                    uint24_t radius);

/**
 * Draws an unclipped filled circle.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] radius The radius of the circle.
 */
void gfx_FillCircle_NoClip(uint24_t x,
                           uint8_t y,
                           uint24_t radius);

/**
 * Draws an unclipped filled ellipse.
 *
 * @param[in] x X coordinate of the center.
 * @param[in] y Y coordinate of the center.
 * @param[in] a The horizontal radius of the ellipse (current maximum is 128).
 * @param[in] b The vertical radius of the ellipse (current maximum is 128).
 */
void gfx_FillEllipse_NoClip(uint24_t x, uint24_t y, uint8_t a, uint8_t b);

/**
 * Draws a filled ellipse.
 *
 * @param[in] x X coordinate of the center.
 * @param[in] y Y coordinate of the center.
 * @param[in] a The horizontal radius of the ellipse (current maximum is 128).
 * @param[in] b The vertical radius of the ellipse (current maximum is 128).
 */
void gfx_FillEllipse(int24_t x, int24_t y, uint24_t a, uint24_t b);

/**
 * Draws an unclipped ellipse.
 *
 * @param[in] x X coordinate of the center.
 * @param[in] y Y coordinate of the center.
 * @param[in] a The horizontal radius of the ellipse (current maximum is 128).
 * @param[in] b The vertical radius of the ellipse (current maximum is 128).
 */
void gfx_Ellipse_NoClip(uint24_t x, uint24_t y, uint8_t a, uint8_t b);

/**
 * Draws an ellipse.
 *
 * @param[in] x X coordinate of the center.
 * @param[in] y Y coordinate of the center.
 * @param[in] a The horizontal radius of the ellipse (current maximum is 128).
 * @param[in] b The vertical radius of the ellipse (current maximum is 128).
 */
void gfx_Ellipse(int24_t x, int24_t y, uint24_t a, uint24_t b);

/**
 * Draws a clipped polygon outline.
 *
 * @code{.cpp}
 * int points[6] = {
 *                    160,  1,  // (x0, y0)
 *                    1,  238,  // (x1, y1)
 *                    318,238,  // (x2, y2)
 *                  };
 * num_points = 3;
 * gfx_Polygon(points, num_points);
 * @endcode
 * @param[in] points Pointer to x and y pairs.
 * @param[in] num_points Number of x and y pairs.
 */
void gfx_Polygon(const int *points, unsigned num_points);

/**
 * Draws an unclipped polygon outline
 *
 * @code{.cpp}
 * int points[6] = {
 *                    160,  1,  // (x0, y0)
 *                    1,  238,  // (x1, y1)
 *                    318,238,  // (x2, y2)
 *                  };
 * num_points = 3;
 * gfx_Polygon_NoClip(points, num_points)
 *
 * @endcode
 * @param[in] points Pointer to x and y pairs
 * @param[in] num_points Number of x and y pairs
 */
void gfx_Polygon_NoClip(const int *points, unsigned num_points);

/**
 * Draws a clipped filled triangle.
 *
 * @param[in] x0 First X coordinate.
 * @param[in] y0 First Y coordinate.
 * @param[in] x1 Second X coordinate.
 * @param[in] y1 Second Y coordinate.
 * @param[in] x2 Third X coordinate.
 * @param[in] y2 Third Y coordinate.
 */
void gfx_FillTriangle(int x0,
                      int y0,
                      int x1,
                      int y1,
                      int x2,
                      int y2);

/**
 * Draws a unclipped filled triangle.
 *
 * @param[in] x0 First X coordinate.
 * @param[in] y0 First Y coordinate.
 * @param[in] x1 Second X coordinate.
 * @param[in] y1 Second Y coordinate.
 * @param[in] x2 Third X coordinate.
 * @param[in] y2 Third Y coordinate.
 */
void gfx_FillTriangle_NoClip(int x0,
                             int y0,
                             int x1,
                             int y1,
                             int x2,
                             int y2);

/**
 * Forces all graphics routines draw location.
 *
 * @param[in] location Location routines should draw to.
 * @see gfx_location_t.
 */
void gfx_SetDraw(uint8_t location);

/**
 * Gets the current drawing buffer.
 *
 * @returns Location type enumeration.
 * @see gfx_location_t.
 */
uint8_t gfx_GetDraw(void);

/**
 * Swaps the roles of the screen and drawing buffers.
 *
 * Does not wait for the old screen buffer to finish being displayed. Instead,
 * the next invocation of a graphx drawing function will block, (pause program
 * execution) waiting for this event. To block and wait explicitly, use gfx_Wait().
 *
 * The LCD driver maintains its own screen buffer pointer for the duration of a
 * refresh. The swap performed by this function will only be picked up at a
 * point between refreshes.
 *
 * @remarks
 * In practice, this function should be invoked immediately after finishing
 * drawing a frame to the drawing buffer, and invocation of the first graphx
 * drawing function for the next frame should be scheduled as late as possible
 * relative to non-drawing logic. Non-drawing logic can execute during time when
 * a drawing function may otherwise block.
 */
void gfx_SwapDraw(void);

/**
 * Waits for the screen buffer to finish being displayed after gfx_SwapDraw().
 *
 * @remarks
 * In practice, this function should not need to be invoked by user code. It
 * should be invoked by custom drawing functions (as late as reasonably
 * possible) before writing to the drawing buffer, gfx_vbuffer.
 */
void gfx_Wait(void);

/**
 * Copies the input buffer to the opposite buffer.
 *
 * No clipping is performed as it is a copy not a draw.
 * @param[in] src drawing location to copy from.
 */
void gfx_Blit(gfx_location_t src);

/**
 * Copies lines from the input buffer to the opposite buffer.
 *
 * No clipping is performed as it is a copy not a draw.
 * @param[in] src drawing location to copy from.
 * @param[in] y_loc Y Location to begin copying at.
 * @param[in] num_lines Number of lines to copy.
 * @see gfx_location_t.
 */
void gfx_BlitLines(gfx_location_t src,
                   uint8_t y_loc,
                   uint8_t num_lines);

/**
 * Transfers a rectangle from the source graphics buffer to the opposite
 * buffer.
 *
 * No clipping is performed as it is a copy not a draw.
 * @param[in] src drawing location to copy from.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] width Width of rectangle.
 * @param[in] height Height of rectangle.
 * @see gfx_location_t.
 */
void gfx_BlitRectangle(gfx_location_t src,
                       uint24_t x,
                       uint8_t y,
                       uint24_t width,
                       uint24_t height);

/**
 * Copies a rectangular region between graphics buffers or to the same graphics buffer.
 * The behavior is undefined when the rectangles overlap.
 * No clipping is performed as it is a copy not a draw.
 * @param[in] src Graphics buffer to copy from.i
 * @param[in] dst Graphics buffer to copy to.
 * @param[in] src_x X coordinate on src.
 * @param[in] src_y Y coordinate on src.
 * @param[in] dst_x X coordinate on dst.
 * @param[in] dst_y Y coordinate on dst.
 * @param[in] width Width of rectangle.
 * @param[in] height Height of rectangle.
 * @see gfx_location_t
 */
void gfx_CopyRectangle(gfx_location_t src,
                       gfx_location_t dst,
                       uint24_t src_x,
                       uint8_t src_y,
                       uint24_t dst_x,
                       uint8_t dst_y,
                       uint24_t width,
                       uint8_t height);

/**
 * Sets the scaling for text. Scaling is performed by multiplying the
 * width / height of the currently loaded text by the supplied scaling factors.
 *
 * Values in the range from 1-5 are preferred.
 * @param[in] width_scale Text width scaling
 * @param[in] height_scale Text height scaling
 */
void gfx_SetTextScale(uint8_t width_scale, uint8_t height_scale);

/**
 * Prints a single character.
 *
 * Outputs a character at the current cursor position.
 * @param[in] c Character to print
 * @note By default, no text clipping is performed. See gfx_SetTextConfig.
 */
void gfx_PrintChar(const char c);

/**
 * Prints a signed integer.
 *
 * Outputs at the current cursor position. Pads the integer with leading zeros if
 * necessary to satisfy the specified minimum length.
 * For example, gfx_PrintInt(5,3) prints "005".
 *
 * @param[in] n Integer to print.
 * @param[in] length Minimum number of characters to print.
 * @note By default, no text clipping is performed. See gfx_SetTextConfig.
 * @note \p length must be between 1 and 8, inclusive
 */
void gfx_PrintInt(int n, uint8_t length);

/**
 * Prints an unsigned integer.
 *
 * Outputs at the current cursor position. Pads the integer with leading zeros if
 * necessary to satisfy the specified minimum length.
 * For example, gfx_PrintUInt(5,3) prints "005".
 *
 * @param[in] n Unsigned integer to print.
 * @param[in] length Minimum number of characters to print.
 * @note By default, no text clipping is performed. See gfx_SetTextConfig.
 * @note \p length must be between 1 and 8, inclusive
 */
void gfx_PrintUInt(unsigned int n, uint8_t length);

/**
 * Prints a string.
 *
 * Outputs a string at the current cursor position.
 * @param[in] string Pointer to string to print.
 * @note By default, no text clipping is performed. See gfx_SetTextConfig.
 */
void gfx_PrintString(const char *string);

/**
 * Prints a string at a specific location.
 *
 * Outputs a string at the supplied coordinates.
 * This has the same effect as calling
 * gfx_SetTextXY(x,y);
 * then
 * gfx_PrintString();
 * @param[in] string Pointer to string to print.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @note By default, no text clipping is performed. See gfx_SetTextConfig.
 */
void gfx_PrintStringXY(const char *string, int x, int y);

/**
 * @returns The current text cursor X position.
 */
int gfx_GetTextX(void);

/**
 * @returns The current text cursor Y position.
 */
int gfx_GetTextY(void);

/**
 * Sets the text cursor X and Y positions.
 *
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_SetTextXY(int x, int y);

/**
 * Sets the configuration for the text routines.
 *
 * @param[in] config Set the options for the text mode.
 * @see gfx_text_options_t
 * @note Scaled text does not clip
 */
void gfx_SetTextConfig(uint8_t config);

/**
 * Sets the text foreground color.
 *
 * @param[in] color Palette index to set.
 * @returns Previous text foreground palette index.
 * @note Default text foreground palette index: 0.
 * @note Default text background palette index is 255, so if you don't change it and try to draw with color 255, nothing will happen.
 * You can change this with gfx_SetTextTransparentColor(color).
 */
uint8_t gfx_SetTextFGColor(uint8_t color);

/**
 * Sets the text background (highlight) color.
 *
 * @param[in] color Palette index to set.
 * @returns Previous text background palette index.
 * @note Default text background palette index: 255. (default transparent color)
 */
uint8_t gfx_SetTextBGColor(uint8_t color);

/**
 * Sets the text transparency color.
 *
 * @param[in] color Palette index to set.
 * @returns Previous text transparency palette index.
 * @note Default text transparency palette index: 255.
 */
uint8_t gfx_SetTextTransparentColor(uint8_t color);

/**
 * Draws a sprite.
 *
 * @param[in] sprite Pointer to an initialized sprite structure.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_Sprite(const gfx_sprite_t *sprite, int x, int y);

/**
 * Draws an unclipped sprite.
 *
 * @param[in] sprite Pointer to an initialized sprite structure.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_Sprite_NoClip(const gfx_sprite_t *sprite, uint24_t x, uint8_t y);

/**
 * Draws a transparent sprite.
 *
 * @param[in] sprite Pointer to an initialized sprite structure.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_TransparentSprite(const gfx_sprite_t *sprite, int x, int y);

/**
 * Draws an unclipped transparent sprite.
 *
 * @param[in] sprite Pointer to an initialized sprite structure.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_TransparentSprite_NoClip(const gfx_sprite_t *sprite, uint24_t x, uint8_t y);

/**
 * Grabs the background behind a sprite.
 *
 * This is useful for partial redraw.
 * @param[out] sprite_buffer Buffer used to store grabbed sprite.
 * @param[in] x X coordinate to grab sprite.
 * @param[in] y Y coordinate to grab sprite.
 * @returns A pointer to sprite_buffer.
 * @note \p sprite_buffer must be pointing to a large enough buffer to hold
 *       (width * height + 2) number of bytes.
 */
gfx_sprite_t *gfx_GetSprite(gfx_sprite_t *sprite_buffer, int x, int y);

/**
 * Scales an unclipped sprite.
 *
 * Scaling factors must be greater than or equal to 1, and an integer factor.
 * Sprites are scaled by multiplying the dimensions by the respective factors.
 *
 * @param[in] sprite Pointer to an initialized sprite structure.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] width_scale Width scaling factor.
 * @param[in] height_scale Height scaling factor.
 * @note Usable with gfx_GetSprite in order to create clipped versions.
 */
void gfx_ScaledSprite_NoClip(const gfx_sprite_t *sprite,
                             uint24_t x,
                             uint8_t y,
                             uint8_t width_scale,
                             uint8_t height_scale);

/**
 * Scales an unclipped transparent sprite.
 *
 * Scaling factors must be greater than or equal to 1, and an integer factor.
 * Sprites are scaled by multiplying the dimensions by the respective factors.
 *
 * @param[in] sprite Pointer to an initialized sprite structure.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 * @param[in] width_scale Width scaling factor.
 * @param[in] height_scale Height scaling factor.
 * @note Usable with gfx_GetSprite in order to create clipped versions.
 */
void gfx_ScaledTransparentSprite_NoClip(const gfx_sprite_t *sprite,
                                        uint24_t x,
                                        uint8_t y,
                                        uint8_t width_scale,
                                        uint8_t height_scale);

/**
 * Fixed Rotation with scaling factor for sprites.
 *
 * @note A scale factor of 64 represents 100% scaling.
 * @warning This routine only accepts square input sprites.
 * @param[in] sprite Input sprite to rotate/scale.
 * @param[in] x X coordinate position.
 * @param[in] y Y coordinate position.
 * @param[in] angle 256 position angular integer.
 * @param[in] scale Scaling factor; range is about 1% to 400% scale.
 * @returns The size of the sprite after scaling.
 *          This can be used for centering purposes.
 */
uint8_t gfx_RotatedScaledTransparentSprite_NoClip(const gfx_sprite_t *sprite,
                                                  uint24_t x,
                                                  uint8_t y,
                                                  uint8_t angle,
                                                  uint8_t scale);

/**
 * Fixed Rotation with scaling fator for sprites without transparency.
 *
 * @note A scale factor of 64 represents 100% scaling.
 * @warning This routine only accepts square input sprites.
 * @param[in] sprite Input sprite to rotate/scale.
 * @param[in] x X coordinate position.
 * @param[in] y Y coordinate position.
 * @param[in] angle 256 position angular integer.
 * @param[in] scale Scaling factor; range is about 1% to 400% scale.
 *        64 represents 100% scaling.
 * @returns The size of the sprite after scaling.
 *          This can be used for centering purposes.
 */
uint8_t gfx_RotatedScaledSprite_NoClip(const gfx_sprite_t *sprite,
                                       uint24_t x,
                                       uint8_t y,
                                       uint8_t angle,
                                       uint8_t scale);

/**
 * Flips a sprite along the X axis.
 *
 * @param[in] sprite_in Input sprite to flip.
 * @param[out] sprite_out Pointer to where flipped sprite will be stored.
 * @returns A pointer to sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_FlipSpriteX(const gfx_sprite_t *sprite_in,
                              gfx_sprite_t *sprite_out);

/**
 * Flips a sprite along the Y axis.
 *
 * @param[in] sprite_in Input sprite to flip.
 * @param[out] sprite_out Pointer to where flipped sprite will be stored.
 * @returns A pointer to sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_FlipSpriteY(const gfx_sprite_t *sprite_in,
                              gfx_sprite_t *sprite_out);

/**
 * Rotates a sprite 90 degrees clockwise.
 *
 * @param[in] sprite_in Input sprite to rotate.
 * @param[out] sprite_out Pointer to where rotated sprite will be stored.
 * @returns A pointer to sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_RotateSpriteC(const gfx_sprite_t *sprite_in,
                                gfx_sprite_t *sprite_out);

/**
 * Rotates a sprite 90 degrees counter clockwise.
 *
 * @param[in] sprite_in Input sprite to rotate.
 * @param[out] sprite_out Pointer to where rotated sprite will be stored.
 * @returns A pointer to sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_RotateSpriteCC(const gfx_sprite_t *sprite_in,
                                 gfx_sprite_t *sprite_out);

/**
 * Rotates a sprite 180 degrees.
 *
 * @param[in] sprite_in Input sprite to rotate.
 * @param[out] sprite_out Pointer to where rotated sprite will be stored.
 * @returns A pointer to sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_RotateSpriteHalf(const gfx_sprite_t *sprite_in,
                                   gfx_sprite_t *sprite_out);

/**
 * Resizes a sprite to new dimensions.
 *
 * Place new image dimensions in sprite_out;
 * i.e. sprite_out->width = 80; sprite_out->height = 20.
 * @param[in] sprite_in Input sprite to scale.
 * @param[out] sprite_out Pointer to where scaled sprite will be stored.
 * @returns A pointer to \p sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_ScaleSprite(const gfx_sprite_t *sprite_in,
                              gfx_sprite_t *sprite_out);

/**
 * Fixed Rotation with scaling factor for sprites.
 *
 * The output sprite is updated with the dimensions required for the
 * implemented scaling factor. You must make sure that \p sprite_out
 * has enough memory to store the needed output sprite. This can be
 * found with the following formula:
 *   size = (max_scale / 64) * width * height + 2;
 *
 * @note A scale factor of 64 represents 100% scaling.
 * @warning This routine only accepts square input sprites.
 * @param[in] sprite_in Input sprite to rotate/scale.
 * @param[out] sprite_out Pointer to where rotated/scaled sprite will be stored.
 * @param[in] angle 256 position angular integer.
 * @param[in] scale Scaling factor; range is about 1% to 400% scale.
 * @returns A pointer to \p sprite_out.
 * @note sprite_in and sprite_out cannot be the same. Ensure sprite_out is allocated.
 */
gfx_sprite_t *gfx_RotateScaleSprite(const gfx_sprite_t *sprite_in,
                                    gfx_sprite_t *sprite_out,
                                    uint8_t angle,
                                    uint8_t scale);

/**
 * Creates a temporary character sprite.
 *
 * This may be useful for performing rotations and other.
 * operations on characters. The sprite returned is always 8x8 pixels.
 * @param[in] c Character to generate.
 * @returns A sprite of the character data.
 */
gfx_sprite_t *gfx_GetSpriteChar(char c);

/**
 * Sets the font's character data.
 *
 * Fonts can be created manually or and exported to a C-style format
 * using 8x8 Pixel ROM Font Editor:
 * (https://www.min.at/prinz/o/software/pixelfont/#download)
 *
 * @param[in] data Pointer to formatted 8x8 pixel font.
 * @returns Pointer to previous font data.
 * @note Format of font data is 8 bytes horizontally aligned.
 */
uint8_t *gfx_SetFontData(const uint8_t *data);

/**
 * Sets the font data for a specific character.
 *
 * @param[in] index Character index to modify.
 *              (if using default font, values range from 0-127,
 *               custom font can have indexes 0-255).
 * @param[in] data Pointer to formatted 8x8 pixel font.
 * @returns Pointer to current character data if \p data is NULL,
 *          otherwise a pointer to next character data.
 * @note Format of font data is 8 bytes horizontally aligned.
 * @see gfx_SetFontData.
 */
uint8_t *gfx_SetCharData(uint8_t index,
                         const uint8_t *data);

/**
 * Sets the font spacing for each character.
 * Format is an array of bytes, where each index in the array
 * corresponds to the character's numerical value.
 *
 * @param[in] spacing Pointer to array of character spacing.
 */
void gfx_SetFontSpacing(const uint8_t *spacing);

/**
 * Sets the height in pixels of each character.
 *
 * The default value is 8 pixels.
 * @param[in] height New font height in pixels.
 * @returns Previous height of font in pixels.
 */
uint8_t gfx_SetFontHeight(uint8_t height);

/**
 * Sets a monospaced font width.
 *
 * @param[in] spacing Distance between characters.
 * @note To disable monospaced font, set to 0.
 */
void gfx_SetMonospaceFont(uint8_t spacing);

/**
 * Gets the pixel width of the given string.
 *
 * @param[in] string Pointer to a string.
 * @note Takes into account monospacing flag.
 */
unsigned int gfx_GetStringWidth(const char *string);

/**
 * Gets the pixel width of the given character.
 *
 * @param[in] c Character to get width of.
 * @returns Width in pixels of character.
 * @note Takes into account monospacing flag.
 */
unsigned int gfx_GetCharWidth(const char c);

/**
 * Sets the dimensions of the drawing window for all clipped routines.
 *
 * @param[in] xmin Minimum x coordinate, inclusive (default 0).
 * @param[in] ymin Minimum y coordinate, inclusive (default 0).
 * @param[in] xmax Maximum x coordinate, exclusive (default 320).
 * @param[in] ymax Maximum y coordinate, exclusive (default 240).
 */
void gfx_SetClipRegion(int xmin, int ymin, int xmax, int ymax);

/**
 * Clips a region to fit within the drawing window using Cohen-Sutherland.
 *
 * @returns False if offscreen, true if onscreen.
 */
bool gfx_GetClipRegion(gfx_region_t *region);

/**
 * Shifts/Slides the drawing window down.
 *
 * @param[in] pixels Number of pixels to shift.
 * @note Remnant data after a shift is undefined.
 */
void gfx_ShiftDown(uint8_t pixels);

/**
 * Shifts/Slides the drawing window up.
 *
 * @param[in] pixels Number of pixels to shift.
 * @note Remnant data after a shift is undefined.
 */
void gfx_ShiftUp(uint8_t pixels);

/**
 * Shifts/Slides the drawing window left.
 *
 * @param[in] pixels Number of pixels to shift.
 * @note Remnant data after a shift is undefined.
 */
void gfx_ShiftLeft(uint24_t pixels);

/**
 * Shifts/Slides the drawing window right.
 *
 * @param[in] pixels Number of pixels to shift.
 * @note Remnant data after a shift is undefined.
 */
void gfx_ShiftRight(uint24_t pixels);

/**
 * Lightens a given 1555 color; useful for palette color conversions.
 *
 * @param[in] color Original color input in 1555 format.
 * @param[in] amount Amount to lighten by.
 * @returns Lightened color.
 * @note 0 returns full white, 255 returns original color.
 */
uint16_t gfx_Lighten(uint16_t color,
                     uint8_t amount);

/**
 * Darkens a given 1555 color; useful for palette color conversions.
 *
 * @param[in] color Original color input in 1555 format.
 * @param[in] amount Amount to darken by.
 * @returns Darkened color.
 * @note 0 returns full black, 255 returns original color.
 */
uint16_t gfx_Darken(uint16_t color,
                    uint8_t amount);

/**
 * Fills an area with a color.
 *
 * @param[in] x X coordinate to begin filling at.
 * @param[in] y Y coordinate to begin filling at.
 * @param[in] color New color to fill with.
 *
 * @note This routine performs clipping to stay within the window,
 *       but you must ensure it starts in the window.
 */
void gfx_FloodFill(uint24_t x,
                   uint8_t y,
                   uint8_t color);

/**
 * Draws a sprite with RLE transparency.
 *
 * @param[in] sprite sprite to draw.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_RLETSprite(const gfx_rletsprite_t *sprite,
                    int x,
                    int y);

/**
 * Draws an unclipped sprite with RLE transparency.
 *
 * @param[in] sprite Sprite to draw.
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
void gfx_RLETSprite_NoClip(const gfx_rletsprite_t *sprite,
                           uint24_t x,
                           uint8_t y);

/**
 * Converts a sprite with RLE transparency to a sprite with normal transparency.
 *
 * Width and height will be set in the converted sprite.
 *
 * The transparent color index in the converted sprite is controlled by
 * gfx_SetTransparentColor().
 *
 * @attention
 * The output sprite must have been allocated with a large enough
 * \c data field to hold the converted sprite data, which will be
 * <tt>width * height</tt> bytes large.
 *
 * @param[in] sprite_in Input sprite with RLE transparency.
 * @param[out] sprite_out Converted sprite with normal transparency.
 * @returns The converted sprite.
 * @see gfx_ConvertMallocRLETSprite.
 * @see gfx_ConvertToRLETSprite.
 */
gfx_sprite_t *gfx_ConvertFromRLETSprite(const gfx_rletsprite_t *sprite_in,
                                        gfx_sprite_t *sprite_out);

/**
 * Converts a sprite with normal transparency to a sprite with RLE transparency.
 *
 * Width and height will be set in the converted sprite.
 *
 * The transparent color index in the input sprite is controlled by
 * gfx_SetTransparentColor().
 *
 * @attention
 * The output sprite must have been allocated with a large enough data field to
 * hold the converted sprite data; see gfx_AllocRLETSprite() for information.
 *
 * @note
 * To avoid needing to predict the output size and risking either the
 * prediction being too high and wasting space, or being too low and corrupting
 * memory, gfx_ConvertMallocRLETSprite() can be used instead to allocate the
 * exact amount of necessary space for the converted sprite.
 *
 * @param[in] sprite_in Input sprite with normal transparency.
 * @param[out] sprite_out Converted sprite with RLE transparency.
 * @returns The converted sprite.
 * @see gfx_ConvertFromRLETSprite.
 */
gfx_rletsprite_t *gfx_ConvertToRLETSprite(const gfx_sprite_t *sprite_in,
                                          gfx_rletsprite_t *sprite_out);

/**
 * Converts a sprite with normal transparency to a sprite with RLE transparency,
 * allocating the exact amount of necessary space for the converted sprite.
 *
 * Allocates the memory with \p malloc_routine. Width and height will be set in
 * the converted sprite. Returns \c NULL upon allocation failure.
 *
 * The transparent color index in the input sprite is controlled by
 * gfx_SetTransparentColor().
 *
 * @remarks
 * If using \c malloc as the \p malloc_routine, gfx_ConvertMallocRLETSprite()
 * can be used as a shortcut.
 *
 * @remarks
 * A gfx_sprite_t can be converted into an appropriately large,
 * already-allocated gfx_rletsprite_t using gfx_ConvertToRLETSprite().
 *
 * @param[in] sprite_in Input sprite with normal transparency.
 * @param[in] malloc_routine Malloc implementation to use.
 * @returns A newly allocated converted sprite with RLE transparency.
 * @see gfx_ConvertFromRLETSprite.
 */
gfx_rletsprite_t *gfx_ConvertToNewRLETSprite(const gfx_sprite_t *sprite_in,
                                             void *(*malloc_routine)(size_t));

/* Compatibility defines (don't use please) */
/* @cond */
#define gfx_black       _Pragma("GCC warning \"'gfx_black' is not palette-safe, try to avoid it\"")  0x00
#define gfx_red         _Pragma("GCC warning \"'gfx_red' is not palette-safe, try to avoid it\"")    0xE0
#define gfx_orange      _Pragma("GCC warning \"'gfx_orange' is not palette-safe, try to avoid it\"") 0xE3
#define gfx_green       _Pragma("GCC warning \"'gfx_green' is not palette-safe, try to avoid it\"")  0x03
#define gfx_blue        _Pragma("GCC warning \"'gfx_blue' is not palette-safe, try to avoid it\"")   0x10
#define gfx_purple      _Pragma("GCC warning \"'gfx_purple' is not palette-safe, try to avoid it\"") 0x50
#define gfx_yellow      _Pragma("GCC warning \"'gfx_yellow' is not palette-safe, try to avoid it\"") 0xE7
#define gfx_pink        _Pragma("GCC warning \"'gfx_pink' is not palette-safe, try to avoid it\"")   0xF0
#define gfx_white       _Pragma("GCC warning \"'gfx_white' is not palette-safe, try to avoid it\"")  0xFF
#define gfx_image_t     _Pragma("GCC warning \"'gfx_image_t' is deprecated, use 'gfx_sprite_t' instead\"") gfx_sprite_t
#define gfx_BlitArea    _Pragma("GCC warning \"'gfx_BlitArea' is deprecated, use 'gfx_BlitRectangle' instead\"") gfx_BlitRectangle
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
