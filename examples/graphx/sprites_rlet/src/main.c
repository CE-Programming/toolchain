#include <ti/getcsc.h>
#include <limits.h>
#include <graphx.h>

/* Include the converted graphics file */
#include "gfx/gfx.h"

#define w ubuntu_width
#define h ubuntu_height

#define xmin ((GFX_LCD_WIDTH-w*6)/2)
#define ymin ((GFX_LCD_HEIGHT-h*6)/2)
#define xmax (xmin+w*6)
#define ymax (ymin+h*6)

#define xmin2 (xmin+w*7/2+4)
#define ymin2 (ymin+h*2+4)
#define xmax2 (xmin2+w-8)
#define ymax2 (ymin2+h-8)

/* For testing conversions */
gfx_UninitedSprite(ubuntu_normal, w, h);
gfx_UninitedRLETSprite(ubuntu_uninited, (w + 1) * h);

int main(void)
{
    /* For testing conversions */
    gfx_rletsprite_t *ubuntu_malloc;

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette for the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_palette[255] = gfx_RGBTo1555(192, 192, 192);

    /* Set a centered 192*192 clip region, bordered by gray and filled with color index 0 */
    gfx_FillScreen(255);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(xmin, ymin, xmax - xmin, ymax - ymin);
    gfx_SetClipRegion(xmin, ymin, xmax, ymax);

    /* Test no clipping */
    gfx_RLETSprite_NoClip(ubuntu, xmin + w * 3 / 2, ymin + h * 2);
    gfx_RLETSprite(ubuntu, xmin + w * 5 / 2, ymin + h * 2);

    /* Test top clipping */
    gfx_RLETSprite(ubuntu, xmin + w, ymin);
    gfx_RLETSprite(ubuntu, xmin + w * 2, ymin - h + 1);
    gfx_RLETSprite(ubuntu, xmin + w * 3, ymin - h);
    gfx_RLETSprite(ubuntu, xmin + w * 4, INT_MIN);

    /* Test bottom clipping */
    gfx_RLETSprite(ubuntu, xmin + w * 4, ymax - h);
    gfx_RLETSprite(ubuntu, xmin + w * 3, ymax - 1);
    gfx_RLETSprite(ubuntu, xmin + w * 2, ymax);
    gfx_RLETSprite(ubuntu, xmin + w, INT_MAX);

    /* Test right clipping */
    gfx_RLETSprite(ubuntu, xmax - w, ymin + h);
    gfx_RLETSprite(ubuntu, xmax - 1, ymin + h * 2);
    gfx_RLETSprite(ubuntu, xmax, ymin + h * 3);
    gfx_RLETSprite(ubuntu, INT_MAX, ymin + h * 4);

    /* Test left clipping */
    gfx_RLETSprite(ubuntu, xmin, ymin + h * 4);
    gfx_RLETSprite(ubuntu, xmin - w + 1, ymin + h * 3);
    gfx_RLETSprite(ubuntu, xmin - w, ymin + h * 2);
    gfx_RLETSprite(ubuntu, INT_MIN, ymin + h);

    /* Test corner clipping */
    gfx_RLETSprite(ubuntu, xmin - w + 1, ymin - h + 1);
    gfx_RLETSprite(ubuntu, xmax - 1, ymin - h + 1);
    gfx_RLETSprite(ubuntu, xmax - 1, ymax - 1);
    gfx_RLETSprite(ubuntu, xmin - w + 1, ymax - 1);

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
    gfx_TransparentSprite_NoClip(ubuntu_normal, xmin + w * 3 / 2, ymin + h * 3);
    gfx_ConvertToRLETSprite(ubuntu_normal, ubuntu_uninited);
    gfx_RLETSprite_NoClip(ubuntu_uninited, xmin + w * 5 / 2, ymin + h * 3);
    ubuntu_malloc = gfx_ConvertMallocRLETSprite(ubuntu_normal);
    gfx_RLETSprite_NoClip(ubuntu_malloc, xmin + w * 7 / 2, ymin + h * 3);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
