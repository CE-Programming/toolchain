#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

/* Include the graphics */
#include "gfx/tiles_gfx.h"

/* Include the external map data */
extern uint8_t tilemap_map[];

/* Tilemap defines */
#define TILE_WIDTH          16
#define TILE_HEIGHT         16

#define TILEMAP_WIDTH       32
#define TILEMAP_HEIGHT      25

#define TILEMAP_DRAW_WIDTH  20
#define TILEMAP_DRAW_HEIGHT 14

#define Y_OFFSET            16
#define X_OFFSET            0

void main(void) {
    sk_key_t key;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;
    gfx_tilemap_t tilemap;

    /* Initialize the tilemap structure */
    tilemap.map         = tilemap_map;
    tilemap.tiles       = tileset_tiles;
    tilemap.type_width  = gfx_tile_16_pixel;
    tilemap.type_height = gfx_tile_16_pixel;
    tilemap.tile_height = TILE_HEIGHT;
    tilemap.tile_width  = TILE_WIDTH;
    tilemap.draw_height = TILEMAP_DRAW_HEIGHT;
    tilemap.draw_width  = TILEMAP_DRAW_WIDTH;
    tilemap.height      = TILEMAP_HEIGHT;
    tilemap.width       = TILEMAP_WIDTH;
    tilemap.y_loc       = Y_OFFSET;
    tilemap.x_loc       = X_OFFSET;
    
    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);
    
    /* Set up the palette */
    gfx_SetPalette(tiles_gfx_pal, sizeof(tiles_gfx_pal), 0);
    gfx_SetColor(gfx_white);
    
    /* Draw to buffer to avoid tearing */
    gfx_SetDrawBuffer();
    
    /* Set monospace font with width of 8 */
    gfx_SetMonospaceFont(8);

    /* Wait for the enter key to quit */
    while ((key = os_GetCSC()) != sk_Enter) {
    
        /* Draw tilemap and coords */
        gfx_Tilemap(&tilemap, x_offset, y_offset);
        gfx_FillRectangle(0, 0, 320, 16);
        gfx_PrintStringXY("x offset:", 48, 4);
        gfx_PrintUInt(x_offset, 4);
        gfx_PrintString(" y offset:");
        gfx_PrintUInt(y_offset, 4);
        
        /* Do something based on the keypress */
        switch (key) {
            case sk_Down:
                if (y_offset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
                    y_offset += TILE_HEIGHT;
                break;
            case sk_Left:
                if (x_offset)
                    x_offset -= TILE_WIDTH;
                break;
            case sk_Right:
                if (x_offset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
                    x_offset += TILE_WIDTH;
                break;
            case sk_Up:
                if (y_offset)
                    y_offset -= TILE_HEIGHT;
                break;
            default:
                break;
        }
        gfx_SwapDraw();
    }
    
    /* Close the graphics and return to the OS */
    gfx_End();
}
