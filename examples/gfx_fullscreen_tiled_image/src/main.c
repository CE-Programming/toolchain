#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <decompress.h>
#include <graphx.h>
#include <debug.h>

/* Include the graphics */
#include "gfx/tiles_gfx.h"
#include "gfx/var_gfx.h"

/* Include the external map data */
extern uint8_t tilemap_map[];

#define TILE_WIDTH 80
#define TILE_HEIGHT 80

void main(void) {
    unsigned int i;
    unsigned int x, y;
    gfx_sprite_t *tile = gfx_MallocSprite(TILE_WIDTH, TILE_HEIGHT);

    /* Initialize the graphics */
    if (!var_gfx_init()) {
        return;
    }

    /* Start the graphics */
    gfx_Begin();
    x = y = i = 0;

    /* Draw offscreen */
    gfx_SetDrawBuffer();

    /* Decompress the tiles */
    for (; i < tileset_tiles_num; i++) {
        dzx7_Turbo(tileset_tiles_compressed[i], tile);
        gfx_Sprite_NoClip(tile, x, y);
        x += TILE_WIDTH;
        if (x >= LCD_WIDTH) {
            y += TILE_HEIGHT;
            x = 0;
        }
    }

    /* Copy to visible screen */
    gfx_SetPalette(tiles_gfx_pal, sizeof_tiles_gfx_pal, 0);
    gfx_BlitBuffer();

    /* Wait for a key */
    while (!os_GetCSC());

    /* Close the graphics and return to the OS */
    gfx_End();

    /* Free the earlier allocation */
    free(tile);
}
