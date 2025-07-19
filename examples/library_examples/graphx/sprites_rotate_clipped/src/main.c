#include <ti/getcsc.h>
#include <graphx.h>
#include <math.h>
#include <time.h>

/* Include the converted image data */
#include "gfx/gfx.h"

int main(void)
{
    /* Center of the screen */
    const int x_center = GFX_LCD_WIDTH / 2;
    const int y_center = GFX_LCD_HEIGHT / 2;

    /* Parameters for the clipping box */
    const int box_width  = 80;
    const int box_height = 80;
    const float box_pivot_radius = 20.0f;

    /* The positions of the 4 sprites on the screen */
    const int distance_from_center = 30;
    const int pos_left   = x_center - distance_from_center - (star_width  / 2);
    const int pos_right  = x_center + distance_from_center - (star_width  / 2);
    const int pos_top    = y_center - distance_from_center - (star_height / 2);
    const int pos_bottom = y_center + distance_from_center - (star_height / 2);

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();

    /* Record the start time */
    const clock_t start_time = clock();

    /* Rotate the sprites until a key is pressed */
    do {
        /* Get the elasped time in seconds */
        float time_elasped = (float)(clock() - start_time) / CLOCKS_PER_SEC;

        /* Calculate the clipping region */
        int x_offset = cosf(time_elasped) * box_pivot_radius;
        int y_offset = sinf(time_elasped) * box_pivot_radius;
        int box_left   = x_center - (box_width  / 2) + x_offset;
        int box_right  = x_center + (box_width  / 2) + x_offset;
        int box_top    = y_center - (box_height / 2) + y_offset;
        int box_bottom = y_center + (box_height / 2) + y_offset;
        gfx_SetClipRegion(box_left, box_top, box_right, box_bottom);

        /* Draw a rectangle to indicate the clipping region */
        gfx_SetColor(2);
        gfx_Rectangle_NoClip(box_left - 1, box_top - 1, box_width + 2, box_height + 2);

        /* Complete one rotation every 6 seconds */
        uint8_t sprite_angle = fmodf(time_elasped * 256.0f / 6.0f, 256.0f);

        /* Draws an unclipped rotated sprite */
        gfx_RotatedSprite_NoClip(star, pos_left, pos_bottom, sprite_angle);

        /* Draws a rotated sprite that is clipped to the rectangular box */
        gfx_RotatedSprite(star, pos_right, pos_bottom, sprite_angle);

        /* Draws an unclipped rotated sprite with transparency */
        gfx_RotatedTransparentSprite_NoClip(star, pos_right, pos_top, sprite_angle);

        /* Draws a rotated sprite with transparency that is clipped to the rectangular box */
        gfx_RotatedTransparentSprite(star, pos_left, pos_top, sprite_angle);

        /* Show the buffered screen */
        gfx_BlitBuffer();

        /* Clear the old drawn sprite */
        gfx_FillScreen(1);

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
