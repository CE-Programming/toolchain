#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <graphx.h>

/* Include the sprite data */
#include "gfx/logo_gfx.h"

#define xmin 64
#define ymin 24
#define xmax 256
#define ymax 216

#define xmin2 180
#define ymin2 92
#define xmax2 204
#define ymax2 116

/* For testing conversions */
gfx_UninitedSprite(ubuntu_normal, 32, 32);
gfx_UninitedRLETSprite(ubuntu_uninited, 33 * 32);

void main(void) {
    /* For testing conversions */
    gfx_rletsprite_t *ubuntu_malloc;

    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);

    /* Set up the palette for our sprites */
    gfx_SetPalette(logo_gfx_pal, sizeof logo_gfx_pal, 0);
    gfx_palette[255] = gfx_RGBTo1555(192, 192, 192);

    /* Set a centered 192*192 clip region, bordered by gray and filled with color index 0 */
    gfx_FillScreen(255);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(xmin, ymin, xmax - xmin, ymax - ymin);
    gfx_SetClipRegion(xmin, ymin, xmax, ymax);

    /* Test no clipping */
    gfx_RLETSprite_NoClip(ubuntu, xmin + 48, ymin + 64);
    gfx_RLETSprite(ubuntu, xmin + 80, ymin + 64);

    /* Test top clipping */
    gfx_RLETSprite(ubuntu, xmin + 32, ymin);
    gfx_RLETSprite(ubuntu, xmin + 64, ymin - 31);
    gfx_RLETSprite(ubuntu, xmin + 96, ymin - 32);
    gfx_RLETSprite(ubuntu, xmin + 128, INT_MIN);

    /* Test bottom clipping */
    gfx_RLETSprite(ubuntu, xmin + 128, ymax - 32);
    gfx_RLETSprite(ubuntu, xmin + 96, ymax - 1);
    gfx_RLETSprite(ubuntu, xmin + 64, ymax);
    gfx_RLETSprite(ubuntu, xmin + 32, INT_MAX);

    /* Test right clipping */
    gfx_RLETSprite(ubuntu, xmax - 32, ymin + 32);
    gfx_RLETSprite(ubuntu, xmax - 1, ymin + 64);
    gfx_RLETSprite(ubuntu, xmax, ymin + 96);
    gfx_RLETSprite(ubuntu, INT_MAX, ymin + 128);

    /* Test left clipping */
    gfx_RLETSprite(ubuntu, xmin, ymin + 128);
    gfx_RLETSprite(ubuntu, xmin - 31, ymin + 96);
    gfx_RLETSprite(ubuntu, xmin - 32, ymin + 64);
    gfx_RLETSprite(ubuntu, INT_MIN, ymin + 32);

    /* Test corner clipping */
    gfx_RLETSprite(ubuntu, xmin - 31, ymin - 31);
    gfx_RLETSprite(ubuntu, xmax - 1, ymin - 31);
    gfx_RLETSprite(ubuntu, xmax - 1, ymax - 1);
    gfx_RLETSprite(ubuntu, xmin - 31, ymax - 1);

    /* Set a centered 16*16 clip region, bordered by gray and filled with color index 0 */
    gfx_SetColor(255);
    gfx_FillRectangle_NoClip(xmin2 - 4, ymin2 - 4, xmax2 - xmin2 + 8, ymax2 - ymin2 + 8);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(xmin2, ymin2, xmax2 - xmin2, ymax2 - ymin2);
    gfx_SetClipRegion(xmin2, ymin2, xmax2, ymax2);

    /* Test all-around clipping */
    gfx_RLETSprite(ubuntu, xmin2 - 4, ymin2 - 4);

    /* Test conversions */
    gfx_SetTransparentColor(0);
    gfx_ConvertFromRLETSprite(ubuntu, ubuntu_normal);
    gfx_TransparentSprite_NoClip(ubuntu_normal, xmin + 48, ymin + 96);
    gfx_ConvertToRLETSprite(ubuntu_normal, ubuntu_uninited);
    gfx_RLETSprite_NoClip(ubuntu_uninited, xmin + 80, ymin + 96);
    ubuntu_malloc = gfx_ConvertMallocRLETSprite(ubuntu_normal);
    gfx_RLETSprite_NoClip(ubuntu_malloc, xmin + 112, ymin + 96);

    /* Wait for a key to be pressed */
    while (!os_GetCSC());

    /* Close the graphics */
    gfx_End();
}
