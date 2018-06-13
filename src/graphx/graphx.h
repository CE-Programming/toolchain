/**
 * @file
 * @authors Matt "MateoConLechuga" Waltz
 * @authors Jacob "jacobly" Young
 * @authors Zachary "Runer112" Wassall
 * @authors Patrick "tr1p1ea" Prendergast
 * @authors "grosged"
 * @brief Contains optimized graphics operations and routines
 */

#ifndef H_GRAPHX
#define H_GRAPHX

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sprite (image) type.
 *
 * Whether or not a sprite includes transparency is not explicitly encoded, and
 * is determined only by usage. If used with transparency, transparent pixels
 * are those with a certain color index, which can be set with
 * gfx_SetTransparentColor().
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
 * <a href="https://github.com/MattWaltz/convpng" target="_blank">convpng</a>.
 * Create at runtime (with uninitialized data) with gfx_MallocSprite(),
 * gfx_UninitedSprite(), or gfx_TempSprite().
 */
typedef struct {
    uint8_t width;   /**< Width of the image  */
    uint8_t height;  /**< Height of the image */
    uint8_t data[1]; /**< Image data array    */
} gfx_sprite_t;

/**
 * @brief Sprite (image) type with RLE transparency.
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
 * <a href="https://github.com/MattWaltz/convpng" target="_blank">convpng</a>.
 */
typedef struct {
    uint8_t width;   /**< Width of the image  */
    uint8_t height;  /**< Height of the image */
    uint8_t data[1]; /**< Image data array    */
} gfx_rletsprite_t;

/**
 * @brief A simple structure for working with 2D points
 */
typedef struct {
    int x; /**< x point  */
    int y; /**< y point  */
} gfx_point_t;

/**
 * @brief Stores operating modes of this library
 * @see gfx_Begin
 */
typedef enum {
    gfx_8bpp = 0x27 /**< Enable 8 bits per pixel mode */
} gfx_mode_t;

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
 * @param width sprite width
 * @param height sprite height
 * @param malloc_routine malloc implementation to use
 * @return pointer to the allocated sprite
 */
gfx_sprite_t *gfx_AllocSprite(uint8_t width, uint8_t height, void *(*malloc_routine)(size_t));

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
 * @param width sprite width
 * @param height sprite height
 * @return pointer to the allocated sprite
 * @see gfx_AllocSprite
 */
#define gfx_MallocSprite(width, height) \
gfx_AllocSprite(width, height, malloc)

/**
 * Statically allocates unitialized memory for a sprite.
 *
 * Declares a <tt>gfx_sprite_t *</tt> with the given \p name pointing to the
 * allocated memory. \p width and \p height will \b not be set in the sprite,
 * unlike gfx_TempSprite().
 *
 * @warning
 * If used outside of a function body, the memory will be allocated in the
 * global unitialized data segment (BSS). If used inside a function body, the
 * memory will be allocated on the stack. If the sprite is sufficiently large,
 * usage inside a function body will overflow the stack, so it is recommended
 * that this normally be used outside of a function body.
 *
 * @param name name of declared <tt>gfx_sprite_t *</tt>
 * @param width sprite width
 * @param height sprite height
 * @see gfx_MallocSprite
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
 * @param name name of declared <tt>gfx_sprite_t *</tt>
 * @param width sprite width
 * @param height sprite height
 * @see gfx_MallocSprite
 */
#define gfx_TempSprite(name, width, height) \
uint8_t name##_data[2 + (width) * (height)] = { (width), (height) }; \
gfx_sprite_t *name = (gfx_sprite_t *)name##_data

/**
 * Dynamically allocates memory for a sprite with RLE transpareny.
 *
 * Allocates the memory with \p malloc_routine. Returns \c NULL upon allocation
 * failure.
 *
 * \p data_size is the maximum predicted/calculated size of the sprite data
 * (excuding the width and height bytes) that will be stored in the allocated
 * sprite. Sprite data size could be up to <tt>(width + 1) * height * 3 / 2</tt>
 * bytes in the worst case, in which pixels horizontally alternate between
 * non-transparent and transparent and each row begins with a non-transparent
 * pixel. But if the average length of a horizontal transparent run is at least
 * 2, then the sprite data will be no larger than <tt>(width + 1) * height</tt>
 * bytes. The exact data size necessary is <tt>2 *
 * num_horizontal_transparent_runs + num_non_transparent_pixels +
 * num_rows_beginning_with_non_transparent_pixel -
 * num_rows_ending_with_transparent_pixel</tt> bytes.
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
 * @param data_size (maximum) sprite data size
 * @param malloc_routine malloc implementation to use
 * @return pointer to the allocated sprite
 */
#define gfx_AllocRLETSprite(data_size, malloc_routine) \
(gfx_rletsprite_t *)(malloc_routine)(data_size)

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
 * @param data_size (maximum) sprite data size
 * @return pointer to the allocated sprite
 * @see gfx_AllocRLETSprite
 */
#define gfx_MallocRLETSprite(data_size) \
gfx_AllocRLETSprite(data_size, malloc)

/**
 * Statically allocates unitialized memory for a sprite with RLE transparency.
 *
 * Declares a <tt>gfx_rletsprite_t *</tt> with the given \p name pointing to the
 * allocated memory. \p data_size is the size to allocate for sprite data; see
 * gfx_AllocRLETSprite() for information.
 *
 * @warning
 * If used outside of a function body, the memory will be allocated in the
 * global unitialized data segment (BSS). If used inside a function body, the
 * memory will be allocated on the stack. If the sprite is sufficiently large,
 * usage inside a function body will overflow the stack, so it is recommended
 * that this normally be used outside of a function body.
 *
 * @param name name of declared <tt>gfx_rletsprite_t *</tt>
 * @param data_size (maximum) sprite data size
 * @see gfx_MallocRLETSprite
 */
#define gfx_UninitedRLETSprite(name, data_size) \
uint8_t name##_data[2 + (data_size)]; \
gfx_rletsprite_t *name = (gfx_rletsprite_t *)name##_data

/**
 * Initializes the graphics library setup
 */
int gfx_Begin();

/**
 * Closes the graphics setup
 *
 * Restores the LCD to 16bpp prefered by the OS and clears the screen.
 */
void gfx_End(void);

/**
 * Used for accessing the lcd palette directly
 *
 * This consists of 256 entries, each 2 bytes in size for a total of 512 bytes
 */
#define gfx_palette \
((uint16_t*)0xE30200)

/**
 * Array of the LCD RAM
 *
 * Total of 153600 bytes in size
 * @see gfx_vbuffer
 */
#define gfx_vram \
((uint8_t*)0xD40000)

/**
 * Array of the current drawing buffer
 *
 * Total of 76800 bytes in size
 * @see gfx_vram
 */
#define gfx_vbuffer \
(**(uint8_t(**)[240][320])0xE30014)

/**
 * @brief Defines a rectangular graphics region
 *
 * @see gfx_GetClipRegion
 */
typedef struct {
    int xmin; /**< Minimum x coordinate */
    int ymin; /**< Minimum y coordinate */
    int xmax; /**< Maximum x coordinate */
    int ymax; /**< Maximum y coordinate */
} gfx_region_t;

/**
 * @brief Defines tilemap structure
 *
 * @see gfx_Tilemap
 */
typedef struct {
    uint8_t *map;            /**< Pointer to indexed map array */
    gfx_sprite_t **tiles;     /**< Pointer to tiles */
    uint8_t tile_height;     /**< Individual tile height */
    uint8_t tile_width;      /**< Individual tile width */
    uint8_t draw_height;     /**< Number of tiles per row to draw */
    uint8_t draw_width;      /**< Number of tile per column to draw */
    uint8_t type_width;      /**< Tile type height @see gfx_tilemap_type_t */
    uint8_t type_height;     /**< Tile type width @see gfx_tilemap_type_t */
    uint8_t height;          /**< Total number of rows in the tilemap */
    uint8_t width;           /**< Total number of columns in the tilemap */
    uint8_t y_loc;           /**< Y pixel location of tilemap */
    uint24_t x_loc;          /**< X pixel location to tilemap */
} gfx_tilemap_t;

/**
 * @brief Used for defining tile types
 *
 * @see gfx_tilemap_t
 */
typedef enum {
    gfx_tile_no_pow2 = 0,     /**< Set when using non powers of 2 */
    gfx_tile_2_pixel,         /**< Set when using 2 pixel tiles */
    gfx_tile_4_pixel,         /**< Set when using 4 pixel tiles */
    gfx_tile_8_pixel,         /**< Set when using 8 pixel tiles */
    gfx_tile_16_pixel,        /**< Set when using 16 pixel tiles */
    gfx_tile_32_pixel,        /**< Set when using 32 pixel tiles */
    gfx_tile_64_pixel,        /**< Set when using 64 pixel tiles */
    gfx_tile_128_pixel        /**< Set when using 128 pixel tiles */
} gfx_tilemap_type_t;

/**
 * Draws a tilemap given an initialized tilemap structure
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 * @see gfx_tilemap_t
 */
void gfx_Tilemap(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Draws an unclipped tilemap given an initialized tilemap structure
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 * @see gfx_tilemap_t
 */
void gfx_Tilemap_NoClip(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Draws a transparent tilemap given an initialized tilemap structure
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 * @see gfx_tilemap_t
 */
void gfx_TransparentTilemap(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Draws an unclipped transparent tilemap given an initialized tilemap structure
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 * @see gfx_tilemap_t
 */
void gfx_TransparentTilemap_NoClip(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Gets a pointer to a particular tile given an initialized tilemap structure and pixel offsets
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 */
uint8_t *gfx_TilePtr(gfx_tilemap_t *tilemap, uint24_t x_offset, uint24_t y_offset);

/**
 * Sets a particular tile's value given an initialized tilemap structure and pixel offsets
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 * @param value Value to set tile to
 */
#define gfx_SetTile(tilemap, x_offset, y_offset, value) \
(*(gfx_TilePtr((tilemap), (x_offset), (y_offset))) = (uint8_t)(value))

/**
 * Gets a particular tile's value given an initialized tilemap structure and pixel offsets
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param x_offset Offset in pixels from the left of the tilemap
 * @param y_offset Offset in pixels from the top of the tilemap
 */
#define gfx_GetTile(tilemap, x_offset, y_offset) \
(*(gfx_TilePtr((tilemap), (x_offset), (y_offset))))

/**
 * Gets a pointer to a particular tile given an initialized tilemap structure and mapped offsets
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param row Offset in bytes in the row
 * @param col Offset in bytes in the column
 */
uint8_t *gfx_TilePtrMapped(gfx_tilemap_t *tilemap, uint8_t row, uint8_t col);

/**
 * Sets a particular tile's value given an initialized tilemap structure and mapped offsets
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param row Offset in bytes in the row
 * @param col Offset in bytes in the column
 * @param value Value to set tile to
 */
#define gfx_SetTileMapped(tilemap, row, col, value) \
(*(gfx_TilePtrMapped((tilemap), (row), (col))) = (uint8_t)(value))

/**
 * Gets a particular tile's value given an initialized tilemap structure and mapped offsets
 *
 * @param tilemap Pointer to initialized tilemap structure
 * @param row Offset in bytes in the row
 * @param col Offset in bytes in the column
 */
#define gfx_GetTileMapped(tilemap, row, col) \
(*(gfx_TilePtrMapped((tilemap), (row), (col))))

/**
 * Sets the color index that drawing routines will use
 *
 * This applies to lines, rectangles, circles, etc
 * @param index Color index to set
 * @returns Previous set color index
 */
uint8_t gfx_SetColor(uint8_t index);

/**
 * Sets the transparent index that drawing routines will use
 *
 * This currently applies to transparent sprites, both scaled and unscaled
 * @param index Transparent color index to set
 * @returns The previous transparent color index
 */
uint8_t gfx_SetTransparentColor(uint8_t index);

/**
 * Sets up the default palette for the given mode
 *
 * @param mode Palette to use
 */
void gfx_SetDefaultPalette(gfx_mode_t mode);

/**
 * Sets entries in the palette
 *
 * @param palette Pointer to palette to use
 * @param size Size of palette to store
 * @param offset Offset in bytes to start at (Generally set to 0)
 */
void gfx_SetPalette(uint16_t *palette, uint24_t size, uint8_t offset);

/**
 * Fills the screen with a given palette index
 *
 * @param index Color index to fill with
 */
void gfx_FillScreen(uint8_t index);

/**
 * Implements a faster version of gfx_FillScreen(0)
 *
 * @see gfx_FillScreen
 */
void gfx_ZeroScreen(void);

/**
 * Sets a pixel to the global color index
 *
 * This is measured from the top left origin of the screen.
 * Pixels are only clipped within the screen boundaries
 * @param x X coordinate location
 * @param y Y coordinate location
 * @see gfx_SetColor
 */
void gfx_SetPixel(uint24_t x, uint8_t y);

/**
 * Gets a pixel's color index
 *
 * This is measured from the top left origin of the screen.
 * Pixels are only clipped within the screen boundaries
 * @param x X coordinate location
 * @param y Y coordinate location
 */
uint8_t gfx_GetPixel(uint24_t x, uint8_t y);

/**
 * Draws a line
 *
 * This is measured from the top left origin of the screen.
 * @param x0 First X coordinate
 * @param y0 First Y coordinate
 * @param x1 Second X coordinate
 * @param y1 Second Y coordinate
 */
void gfx_Line(int x0, int y0, int x1, int y1);

/**
 * Draws an unclipped line
 *
 * This is measured from the top left origin of the screen.
 * @param x0 First X coordinate
 * @param y0 First Y coordinate
 * @param x1 Second X coordinate
 * @param y1 Second Y coordinate
 */
void gfx_Line_NoClip(uint24_t x0, uint8_t y0, uint24_t x1, uint8_t y1);

/**
 * Clips the points in a window region
 *
 * This is measured from the top left origin of the screen.
 * @param x0 First X coordinate
 * @param y0 First Y coordinate
 * @param x1 Second X coordinate
 * @param y1 Second Y coordinate
 * @returns False if not within window, true otherwise
 */
bool gfx_CohenSutherlandClip(int *x0, int *y0, int *x1, int *y1);

/**
 * Draws a horizontal line
 *
 * This is measured from the top left origin of the screen.
 * Performs faster than using @c gfx_Line
 * @param x X coordinate
 * @param y Y coordinate
 * @param length Length of line
 */
void gfx_HorizLine(int x, int y, int length);

/**
 * Draws an unclipped horizontal line
 *
 * This is measured from the top left origin of the screen.
 * Performs faster than using @c gfx_Line
 * @param x X coordinate
 * @param y Y coordinate
 * @param length Length of line
 */
void gfx_HorizLine_NoClip(uint24_t x, uint8_t y, uint24_t length);

/**
 * Draws a vertical line
 *
 * This is measured from the top left origin of the screen.
 * Performs faster than using @c gfx_Line
 * @param x X coordinate
 * @param y Y coordinate
 * @param length Length of line
 */
void gfx_VertLine(int x, int y, int length);

/**
 * Draws an unclipped vertical line
 *
 * This is measured from the top left origin of the screen.
 * Performs faster than using @c gfx_Line
 * @param x X coordinate
 * @param y Y coordinate
 * @param length Length of line
 */
void gfx_VertLine_NoClip(uint24_t x, uint8_t y, uint24_t length);

/**
 * Draws a rectangle outline
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
void gfx_Rectangle(int x, int y, int width, int height);

/**
 * Draws an unclipped rectangle outline
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
void gfx_Rectangle_NoClip(uint24_t x, uint8_t y, uint24_t width, uint8_t height);

/**
 * Draws a filled rectangle
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
void gfx_FillRectangle(int x, int y, int width, int height);

/**
 * Draws an unclipped filled rectangle
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
void gfx_FillRectangle_NoClip(uint24_t x, uint8_t y, uint24_t width, uint8_t height);

/**
 * Draws a circle outline
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param radius The radius of the circle
 */
void gfx_Circle(int x, int y, unsigned radius);

/**
 * Draws a filled circle
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param radius The radius of the circle
 */
void gfx_FillCircle(int x, int y, unsigned radius);

/**
 * Draws an unclipped filled circle
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param radius The radius of the circle
 */
void gfx_FillCircle_NoClip(uint24_t x, uint8_t y, unsigned radius);

/**
 * Draws an unclipped circle outline
 *
 * This is measured from the top left origin of the screen.
 * @param x X coordinate
 * @param y Y coordinate
 * @param radius The radius of the circle
 */
#define gfx_Circle_NoClip(x, y, radius) \
gfx_Circle((x), (y), (radius))

/**
 * Draws a polygon outline
 *
 * Points are measured from the top left origin of the screen.
 * @code
 * int points[6] = {
 *                    160,  1,  // (x0, y0)
 *                    1,  238,  // (x1, y1)
 *                    318,238,  // (x2, y2)
 *                  };
 * num_points = 3;
 * gfx_Polygon(points, num_points)
 * @endcode
 * @param points Pointer to x and y pairs
 * @param num_points Number of x and y pairs
 */
void gfx_Polygon(int *points, unsigned num_points);

/**
 * Draws an unclipped polygon outline
 *
 * Points are measured from the top left origin of the screen.
 * @code
 * int points[6] = {
 *                    160,  1,  // (x0, y0)
 *                    1,  238,  // (x1, y1)
 *                    318,238,  // (x2, y2)
 *                  };
 * num_points = 3;
 * gfx_Polygon_NoClip(points, num_points)
 * @endcode
 * @param points Pointer to x and y pairs
 * @param num_points Number of x and y pairs
 */
void gfx_Polygon_NoClip(int *points, unsigned num_points);

/**
 * Draws a filled triangle
 *
 * Points are measured from the top left origin of the screen.
 * @param x0 First X coordinate
 * @param y0 First Y coordinate
 * @param x1 Second X coordinate
 * @param y1 Second Y coordinate
 * @param x2 Third X coordinate
 * @param y2 Third Y coordinate
 */
void gfx_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
void gfx_FillTriangle_NoClip(int x0, int y0, int x1, int y1, int x2, int y2);

/**
 * Forces all graphics routines draw location
 *
 * @param location Location routines should draw to
 * @see gfx_draw_location_t
 */
void gfx_SetDraw(uint8_t location);

/**
 * @brief Different locations routines can be drawn to
 */
typedef enum {
    gfx_screen = 0, /**< Draw to screen */
    gfx_buffer      /**< Draw to buffer */
} gfx_draw_location_t;

/**
 * Makes the subsequent GraphX drawing routines act on the buffer
 */
#define gfx_SetDrawBuffer() \
gfx_SetDraw(gfx_buffer)

/**
 * Makes the subsequent GraphX drawing routines act on the screen
 */
#define gfx_SetDrawScreen() \
gfx_SetDraw(gfx_screen)

/**
 * Gets current draw location
 *
 * @returns Location type enumeration
 * @see gfx_draw_location_t
 */
uint8_t gfx_GetDraw(void);

/**
 * Swaps the roles of the screen and drawing buffers.
 *
 * Does not wait for the old screen buffer to finish being displayed. Instead,
 * the next invocation of a graphx drawing function will block, waiting for this
 * event. To block and wait explicitly, use gfx_Wait().
 *
 * @remarks
 * In practice, this function should be invoked immediately after finishing
 * drawing a frame to the drawing buffer, and invocation of the first graphx
 * drawing function for the next frame should be scheduled as late as possible
 * relative to non-drawing logic. Non-drawing logic can execute during time when
 * a drawing function may otherwise block.
 *
 * The LCD driver maintains its own screen buffer pointer for the duration of a
 * refresh. The swap performed by this function will only be picked up at a
 * point between refreshes.
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
 * Copies the input buffer to the opposite buffer
 *
 * No clipping is performed; as it is a copy not a draw
 * @param location gfx_screen - copies screen to buffer
 * @param location gfx_buffer - copies buffer to screen
 */
void gfx_Blit(uint8_t location);

/**
 * Copies lines from the input buffer to the opposite buffer
 *
 * No clipping is performed; as it is a copy not a draw
 * @param location gfx_screen - copies screen to buffer
 * @param location gfx_buffer - copies buffer to screen
 * @param y_loc Y Location to begin copying at
 * @param num_lines Number of lines to copy
 */
void gfx_BlitLines(uint8_t location, uint8_t y_loc, uint8_t num_lines);

/**
 * Copies a rectangle from the input buffer to the opposite buffer
 *
 * No clipping is performed; as it is a copy not a draw
 * @param location gfx_screen - copies screen to buffer
 * @param location gfx_buffer - copies buffer to screen
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
void gfx_BlitRectangle(uint8_t location, uint24_t x, uint8_t y, uint24_t width, uint24_t height);

/**
 * Copies the screen to the buffer
 */
#define gfx_BlitScreen() \
gfx_Blit(gfx_screen)

/**
 * Copies the buffer to the screen
 */
#define gfx_BlitBuffer() \
gfx_Blit(gfx_buffer)

/**
 * Sets the scaling for text
 *
 * Values in the range from 1-5 are preferred.
 * @param width_scale Text width scaling
 * @param height_scale Text height scaling
 */
void gfx_SetTextScale(uint8_t width_scale, uint8_t height_scale);

/**
 * Prints a character
 *
 * Outputs a character at the current cursor position.
 * @param c Character to print
 * @note By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 */
void gfx_PrintChar(const char c);

/**
 * Prints a signed integer
 *
 * Outputs at the current cursor position.
 * @param n Integer to print
 * @param length Length of integer character display
 * @note By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 * @note Values range from -8388608 to 8388607
 * @note Length must be between 0-8
 */
void gfx_PrintInt(int n, uint8_t length);

/**
 * Prints an unsigned integer
 *
 * Outputs at the current cursor position.
 * @param n Unsigned integer to print
 * @param length Length of unsigned integer character display
 * @note By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 * @note Values range from 0-16777215
 * @note Length must be between 0-8
 */
void gfx_PrintUInt(unsigned int n, uint8_t length);

/**
 * Prints a string
 *
 * Outputs a string at the current cursor position.
 * @param string Pointer to string to print
 * @note By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 */
void gfx_PrintString(const char *string);

/**
 * Prints a string at coordinates
 *
 * Outputs a string at the supplied coordinates
 * Posistion is measured from top left origin of screen.
 * @param string Pointer to string to print
 * @param x X coordinate
 * @param y Y coordinate
 * @note By default, no text clipping is performed (configurable with gfx_SetTextConfig)
 */
void gfx_PrintStringXY(const char *string, int x, int y);

/**
 * @returns The current text cursor X position
 */
int gfx_GetTextX(void);

/**
 * @returns The current text cursor Y position
 */
int gfx_GetTextY(void);

/**
 * Sets the text cursor XY position
 *
 * @param x X coordinate
 * @param y Y coordinate
 */
void gfx_SetTextXY(int x, int y);

/**
 * Sets the configuration for the text routines
 *
 * @param config Set the options for the text mode
 * @see gfx_text_options_t
 * @note Scaled text does not clip
 */
void gfx_SetTextConfig(uint8_t config);

/**
 * @brief Different available text modes
 */
typedef enum {
    gfx_text_clip = 1, /**< Text routines will clip against the defined clip window */
    gfx_text_noclip    /**< Default, text routines do not clip (much faster) */
} gfx_text_options_t;

/**
 * Sets text foreground color
 *
 * @param color Color index to set
 * @returns Previous text foreground color index
 * @note Default text foreground color index: 0
 */
uint8_t gfx_SetTextFGColor(uint8_t color);

/**
 * Sets text background color
 *
 * @param color Color index to set
 * @returns Previous text background color index
 * @note Default text background color index: 255
 */
uint8_t gfx_SetTextBGColor(uint8_t color);

/**
 * Sets text transparency color
 *
 * @param color Color index to set
 * @returns Previous text transparency color index
 * @note Default text transparency color index: 255
 */
uint8_t gfx_SetTextTransparentColor(uint8_t color);

/**
 * Draws a sprite
 *
 * @param sprite Pointer to initialized sprite structure
 * @param x X coordinate
 * @param y Y coordinate
 */
void gfx_Sprite(gfx_sprite_t *sprite, int x, int y);

/**
 * Draws an unclipped sprite
 *
 * @param sprite Pointer to initialized sprite structure
 * @param x X coordinate
 * @param y Y coordinate
 */
void gfx_Sprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y);

/**
 * Draws a transparent sprite
 *
 * @param sprite Pointer to initialized sprite structure
 * @param x X coordinate
 * @param y Y coordinate
 */
void gfx_TransparentSprite(gfx_sprite_t *sprite, int x, int y);

/**
 * Draws an unclipped transparent sprite
 *
 * @param sprite Pointer to initialized sprite structure
 * @param x X coordinate
 * @param y Y coordinate
 */
void gfx_TransparentSprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y);

/**
 * Grabs the background behind a sprite
 *
 * This is useful for partial redraw.
 * @param sprite_buffer Buffer used to store grabbed sprite
 * @param x X coordinate to grab sprite
 * @param y Y coordinate to grab sprite
 * @returns A pointer to sprite_buffer
 * @note sprite_buffer must be pointing to a large enough buffer to hold width*height number of bytes
 */
gfx_sprite_t *gfx_GetSprite(gfx_sprite_t *sprite_buffer, int x, int y);

/**
 * Grabs the background behind an unclipped sprite
 *
 * This is useful for partial redraw.
 * @param sprite_buffer Buffer used to store grabbed sprite
 * @param x X coordinate to grab sprite
 * @param y Y coordinate to grab sprite
 * @returns A pointer to sprite_buffer
 * @note sprite_buffer must be pointing to a large enough buffer to hold width*height number of bytes
 */
#define gfx_GetSprite_NoClip(sprite_buffer, x, y) \
gfx_GetSprite((sprite_buffer), (x), (y))

/**
 * Scales an unclipped sprite
 *
 * Scaling factors must be greater than or equal to 1, and an integer factor
 * @param sprite Pointer to initialized sprite structure
 * @param x X coordinate
 * @param y Y coordinate
 * @param width_scale Width scaling factor
 * @param height_scale Height scaling factor
 * @note Useable with gfx_GetSprite in order to create clipped versions
 */
void gfx_ScaledSprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y, uint8_t width_scale, uint8_t height_scale);

/**
 * Scales an unclipped transparent sprite
 *
 * Scaling factors must be greater than or equal to 1, and an integer factor
 * @param sprite Pointer to initialized sprite structure
 * @param x X coordinate
 * @param y Y coordinate
 * @param width_scale Width scaling factor
 * @param height_scale Height scaling factor
 * @note Useable with gfx_GetSprite in order to create clipped versions
 */
void gfx_ScaledTransparentSprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y, uint8_t width_scale, uint8_t height_scale);

/**
 * Fixed Rotation with scaling fator for sprites
 *
 * @note A scale factor of 64 represents 100% scaling
 * @warning This routine only accepts square input sprites
 * @param sprite Input sprite to rotate/scale
 * @param x X coordinate position
 * @param x Y coordinate position
 * @param angle 256 position angular integer
 * @param scale Scaling factor; range is about 1% to 400% scale
 * @returns The size of the sprite after scaling. This can be used for centering purposes.
 * @returns A pointer to \p sprite_out
 */
uint8_t gfx_RotatedScaledTransparentSprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y, uint8_t angle, uint8_t scale);

/**
 * Helper macro to only perform rotation using gfx_RotatedScaledTransparentSprite_NoClip
 *
 * @param sprite_in Input sprite to rotate
 * @param sprite_out Pointer to where rotated sprite will be stored
 * @param angle 256 position angular integer
 * @see gfx_RotatedScaledTransparentSprite_NoClip
 */
#define gfx_RotatedTransparentSprite_NoClip(sprite, x, y, angle) gfx_RotatedScaledTransparentSprite_NoClip(sprite, x, y, angle, 64)

/**
 * Fixed Rotation with scaling fator for sprites without transparency
 *
 * @note A scale factor of 64 represents 100% scaling
 * @warning This routine only accepts square input sprites
 * @param sprite Input sprite to rotate/scale
 * @param x X coordinate position
 * @param x Y coordinate position
 * @param angle 256 position angular integer
 * @param scale Scaling factor; range is about 1% to 400% scale
 * @returns The size of the sprite after scaling. This can be used for centering purposes.
 * @returns A pointer to \p sprite_out
 */
uint8_t gfx_RotatedScaledSprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y, uint8_t angle, uint8_t scale);

/**
 * Helper macro to only perform rotation using gfx_RotatedScaledSprite_NoClip
 *
 * @param sprite_in Input sprite to rotate
 * @param sprite_out Pointer to where rotated sprite will be stored
 * @param angle 256 position angular integer
 * @see gfx_RotatedScaledTransparentSprite_NoClip
 */
#define gfx_RotatedSprite_NoClip(sprite, x, y, angle) gfx_RotatedScaledTransparentSprite_NoClip(sprite, x, y, angle, 64)

/**
 * Flips a sprite along the X axis
 *
 * @param sprite_in Input sprite to flip
 * @param sprite_out Pointer to where flipped sprite will be stored
 * @returns A pointer to sprite_out
 * @note sprite_in and sprite_out cannot be the same
 */
gfx_sprite_t *gfx_FlipSpriteX(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Flips a sprite along the Y axis
 *
 * @param sprite_in Input sprite to flip
 * @param sprite_out Pointer to where flipped sprite will be stored
 * @returns A pointer to sprite_out
 * @note sprite_in and sprite_out cannot be the same
 */
gfx_sprite_t *gfx_FlipSpriteY(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Rotates a sprite 90 degrees clockwise
 *
 * @param sprite_in Input sprite to rotate
 * @param sprite_out Pointer to where rotated sprite will be stored
 * @returns A pointer to sprite_out
 * @note sprite_in and sprite_out cannot be the same
 */
gfx_sprite_t *gfx_RotateSpriteC(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Rotates a sprite 90 degrees counter clockwise
 *
 * @param sprite_in Input sprite to rotate
 * @param sprite_out Pointer to where rotated sprite will be stored
 * @returns A pointer to sprite_out
 * @note sprite_in and sprite_out cannot be the same
 */
gfx_sprite_t *gfx_RotateSpriteCC(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Rotates a sprite 180 degrees
 *
 * @param sprite_in Input sprite to rotate
 * @param sprite_out Pointer to where rotated sprite will be stored
 * @returns A pointer to sprite_out
 */
gfx_sprite_t *gfx_RotateSpriteHalf(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Resizes a sprite to new dimensions
 *
 * Place new image dimensions in sprite_out; i.e. sprite_out->width = 80; sprite_out->height = 20.
 * @param sprite_in Input sprite to scale
 * @param sprite_out Pointer to where scaled sprite will be stored
 * @returns A pointer to \p sprite_out
 */
gfx_sprite_t *gfx_ScaleSprite(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Fixed Rotation with scaling factor for sprites
 *
 * The output sprite is updated with the dimensions required for the implemented scaling factor.
 * You must make sure that \p sprite_out has enough memory to store the needed output sprite. This can be
 * found with the following formula: size = (max_scale / 64) * width * height + 2;
 *
 * @note A scale factor of 64 represents 100% scaling
 * @warning This routine only accepts square input sprites
 * @param sprite_in Input sprite to rotate/scale
 * @param sprite_out Pointer to where rotated/scaled sprite will be stored
 * @param angle 256 position angular integer
 * @param scale Scaling factor; range is about 1% to 400% scale
 * @returns A pointer to \p sprite_out
 */
gfx_sprite_t *gfx_RotateScaleSprite(gfx_sprite_t *sprite_in, gfx_sprite_t *sprite_out, uint8_t angle, uint8_t scale);

/**
 * Helper macro to only perform rotation using gfx_RotateScaleSprite
 *
 * @param sprite_in Input sprite to rotate
 * @param sprite_out Pointer to where rotated sprite will be stored
 * @param angle 256 position angular integer
 * @returns A pointer to \p sprite_out
 * @see gfx_RotateScaleSprite
 */
#define gfx_RotateSprite(sprite_in, sprite_out, angle) gfx_RotateScaleSprite(sprite_in, sprite_out, angle, 64)

/**
 * Creates a temporary character sprite
 *
 * This may be useful for performing rotations and other
 * operations on characters. The sprite returned is always 8x8 pixels.
 * @param c Character to generate
 */
gfx_sprite_t *gfx_GetSpriteChar(char c);

/**
 * Sets the font's character data
 *
 * Fonts can be created manually or and exported to a C-style format using 8x8 Pixel ROM Font Editor.
 * (https://www.min.at/prinz/o/software/pixelfont/#download)
 *
 * @param data Pointer to formated 8x8 pixel font
 * @returns Pointer to previous font data
 * @note Format of font data is 8 bytes horizontally aligned.
 */
uint8_t *gfx_SetFontData(uint8_t *data);

/**
 * Sets the font data for a specific character
 *
 * @param index Character index to modify (if using default font, values range from 0-127, custom font can have indexes 0-255)
 * @param data Pointer to formated 8x8 pixel font
 * @returns Pointer to current character data if \p data is NULL, otherwise a pointer to next character data
 * @note Format of font data is 8 bytes horizontally aligned.
 * @see gfx_SetFontData
 */
uint8_t *gfx_SetCharData(uint8_t index, uint8_t *data);

/**
 * Sets the font spacing
 *
 * @param spacing Pointer to array of character spacing
 */
void gfx_SetFontSpacing(uint8_t *spacing);

/**
 * Sets the height in pixels of each character
 *
 * The default value is 8 pixels
 * @param height New font height in pixels
 * @returns Previous height of font in pixels
 */
uint8_t gfx_SetFontHeight(uint8_t height);

/**
 * Sets monospaced font
 *
 * @param spacing Distance between characters
 * @note To disable monospaced font, set to 0
 */
void gfx_SetMonospaceFont(uint8_t spacing);

/**
 * Gets the pixel width of the given string
 *
 * @param string Pointer to string
 * @note Takes into account monospacing flag
 */
unsigned int gfx_GetStringWidth(const char *string);

/**
 * Gets the pixel width of the given character
 *
 * @param c Character to get width of
 * @returns Width in pixels of character
 * @note Takes into account monospacing flag
 */
unsigned int gfx_GetCharWidth(const char c);

/**
 * Sets the clipping window
 *
 * This window is used across all clipped routines
 * @param xmin Minimum x coordinate
 * @param ymin Minimum y coordinate
 * @param xmax Maximum x coordinate
 * @param ymax Maximum y coordinate
 * @note This routine is exclusive
 */
void gfx_SetClipRegion(int xmin, int ymin, int xmax, int ymax);

/**
 * Clips a region to fit within the window
 *
 * @returns False if offscreen, true if onscreen
 */
bool gfx_GetClipRegion(gfx_region_t *region);

/**
 * Shifts the drawing window down
 *
 * @param pixels Number of pixels to shift
 * @note Data left over is undefined (Must be drawn over)
 */
void gfx_ShiftDown(uint8_t pixels);

/**
 * Shifts the drawing window up
 *
 * @param pixels Number of pixels to shift
 * @note Data left over is undefined (Must be drawn over)
 */
void gfx_ShiftUp(uint8_t pixels);

/**
 * Shifts the drawing window left
 *
 * @param pixels Number of pixels to shift
 * @note Data left over is undefined (Must be drawn over)
 */
void gfx_ShiftLeft(uint24_t pixels);

/**
 * Shifts the drawing window right
 *
 * @param pixels Number of pixels to shift
 * @note Data left over is undefined (Must be drawn over)
 */
void gfx_ShiftRight(uint24_t pixels);

/**
 * Lightens a given 1555 color; useful for palette color conversions.
 *
 * @param color Original color input in 1555 format
 * @param amount Amount to lighten by
 * @returns Lightened color
 * @note 0 returns full white, 255 returns original color
 */
uint16_t gfx_Lighten(uint16_t color, uint8_t amount);

/**
 * Darkens a given 1555 color; useful for palette color conversions.
 *
 * @param color Original color input in 1555 format
 * @param amount Amount to darken by
 * @returns Darkened color
 * @note 0 returns full black, 255 returns original color
 */
uint16_t gfx_Darken(uint16_t color, uint8_t amount);

/**
 * Fills an area with a color
 *
 * @param x X coordinate to begin filling at
 * @param y Y coordinate to begin filling at
 * @param color New color to fill with
 *
 * @note This routine performs clipping to stay within the window, but you must ensure it starts in the window.
 */
void gfx_FloodFill(unsigned int x, uint8_t y, uint8_t color);

/**
 * Draws a sprite with RLE transparency.
 *
 * @param sprite sprite to draw
 * @param x x-coordinate
 * @param y y-coordinate
 */
void gfx_RLETSprite(gfx_rletsprite_t *sprite, int x, int y);

/**
 * Draws an unclipped sprite with RLE transparency.
 *
 * @param sprite sprite to draw
 * @param x x-coordinate
 * @param y y-coordinate
 */
void gfx_RLETSprite_NoClip(gfx_rletsprite_t *sprite, uint24_t x, uint8_t y);

/**
 * Converts a sprite with RLE transpareny to a sprite with normal transparency.
 *
 * Width and height will be set in the converted sprite.
 *
 * The transparent color index in the converted sprite is controlled by
 * gfx_SetTransparentColor().
 *
 * @attention
 * The output sprite must have been allocated with a large enough \c data field
 * to hold the converted sprite data, which will be <tt>width * height</tt>
 * bytes large.
 *
 * @param[in] sprite_in input sprite with RLE transparency
 * @param[out] sprite_out converted sprite with normal transparency
 * @returns the converted sprite
 * @see gfx_ConvertMallocRLETSprite
 * @see gfx_ConvertToRLETSprite
 */
gfx_sprite_t *gfx_ConvertFromRLETSprite(gfx_rletsprite_t *sprite_in, gfx_sprite_t *sprite_out);

/**
 * Converts a sprite with normal transpareny to a sprite with RLE transparency.
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
 * To avoid needing to predict the output size and risking either the prediction
 * being too high and wasting space, or being too low and corrupting memory,
 * gfx_ConvertMallocRLETSprite() can be used instead to allocate the exact
 * amount of necessary space for the converted sprite.
 *
 * @param[in] sprite_in input sprite with normal transparency
 * @param[out] sprite_out converted sprite with RLE transparency
 * @returns the converted sprite
 * @see gfx_ConvertFromRLETSprite
 */
gfx_rletsprite_t *gfx_ConvertToRLETSprite(gfx_sprite_t *sprite_in, gfx_rletsprite_t *sprite_out);

/**
 * Converts a sprite with normal transpareny to a sprite with RLE transparency,
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
 * @param sprite_in input sprite with normal transparency
 * @param malloc_routine malloc implementation to use
 * @returns a newly allocated converted sprite with RLE transparency
 * @see gfx_ConvertFromRLETSprite
 */
gfx_rletsprite_t *gfx_ConvertToNewRLETSprite(gfx_sprite_t *sprite_in, void *(*malloc_routine)(size_t));

/**
 * Converts a sprite with normal transpareny to a sprite with RLE transparency,
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
 * @param sprite_in input sprite with normal transparency
 * @param malloc_routine malloc implementation to use
 * @returns a newly allocated converted sprite with RLE transparency
 * @see gfx_ConvertFromRLETSprite
 */
#define gfx_ConvertMallocRLETSprite(sprite_in) \
gfx_ConvertToNewRLETSprite(sprite_in, malloc)

/**
 * Converts an RGB value to a palette color
 *
 * Conversion is not 100% perfect, but is quite close
 */
#define gfx_RGBTo1555(r,g,b) \
((uint16_t)(((uint8_t)(r) >> 3) << 10) | \
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

/* Color definitions (try to avoid) */
#define gfx_black       0x00
#define gfx_red         0xE0
#define gfx_orange      0xE3
#define gfx_green       0x03
#define gfx_blue        0x10
#define gfx_purple      0x50
#define gfx_yellow      0xE7
#define gfx_pink        0xF0
#define gfx_white       0xFF

/* Compatability defines (don't use please) */
typedef gfx_sprite_t gfx_image_t;
#define gfx_BlitArea gfx_BlitRectangle
void gfx_LZDecompress(uint8_t *in, uint8_t *out, unsigned int in_size);

#define gfx_lcdWidth    (320)
#define gfx_lcdHeight   (240)

#ifdef __cplusplus
}
#endif

#endif
