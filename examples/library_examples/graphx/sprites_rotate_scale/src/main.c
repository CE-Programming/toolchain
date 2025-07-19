#include <ti/getcsc.h>
#include <graphx.h>
#include <math.h>
#include <time.h>

/* Include the converted image data */
#include "gfx/gfx.h"

float cosine_interpolate(float t, float min_val, float max_val) {
    /* Interpolates between min_val and max_val on a cosine wave */
    /* t = 0 returns min_val */
    float amplitude = (min_val - max_val) / 2.0f;
    float offset = (min_val + max_val) / 2.0f;
    return amplitude * cosf(t) + offset;
}

int main(void)
{
    const int x_center = GFX_LCD_WIDTH / 2;
    const int y_center = GFX_LCD_HEIGHT / 2;

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();

    /* Record the start time */
    const clock_t start_time = clock();

    /* Rotate the sprite until a key is pressed */
    do {
        /* Get the elasped time in seconds */
        float time_elasped = (float)(clock() - start_time) / CLOCKS_PER_SEC;

        /* Complete one rotation every 5 seconds */
        uint8_t rotation = fmodf(time_elasped * 256.0f / 5.0f, 256.0f);

        /* Interpolates between 75% and 225% scale (64 = 100% scale) */
        uint8_t scale = (uint8_t)cosine_interpolate(time_elasped, 48, 144);

        /* The output size of the sprite can be calculated with this formula */
        uint8_t output_size = (scale * star_width) / 64;
        
        /* Calculate the x and y position to center the sprite */
        int x_pos = x_center - output_size / 2;
        int y_pos = y_center - output_size / 2;

        /* Draw a rotated transparent scaled spite */
        gfx_RotatedScaledTransparentSprite_NoClip(star, x_pos, y_pos, rotation, scale);

        /* Show the buffered screen */
        gfx_BlitBuffer();

        /* Clear the old drawn sprite */
        gfx_FillScreen(1);

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
