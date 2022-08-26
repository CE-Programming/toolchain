#include <ti/getcsc.h>
#include <compression.h>
#include <graphx.h>

/* Include the converted graphics file */
#include "gfx/gfx.h"

/* Tilemap defines */
#define TILE_WIDTH          16
#define TILE_HEIGHT         16

#define TILEMAP_WIDTH       32
#define TILEMAP_HEIGHT      25

#define TILEMAP_DRAW_WIDTH  20
#define TILEMAP_DRAW_HEIGHT 14

#define Y_OFFSET            16
#define X_OFFSET            0

/* Include the external compressed tilemap data */
extern unsigned char tilemap_map_compressed[];

/* This is where the decompressed tilemap data is stored */
uint8_t tilemap_map[TILEMAP_WIDTH * TILEMAP_HEIGHT];

/* Holds the decompressed tile pointers */
gfx_sprite_t *tileset_tiles[128];

int main(void)
{
    uint8_t key;
    gfx_tilemap_t tilemap;
    gfx_sprite_t *tmp_ptr;
    unsigned int i;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;

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

    /* Decompress the compressed tileset tiles */
    for (i = 0; i < sizeof(tileset_tiles) / sizeof(gfx_sprite_t*); ++i)
    {
        tmp_ptr = gfx_MallocSprite(TILE_WIDTH, TILE_HEIGHT);
        zx7_Decompress(tmp_ptr, tileset_tiles_compressed[i]);
        tileset_tiles[i] = tmp_ptr;
    }

    /* Decompress the compressed tilemap */
    zx7_Decompress(tilemap_map, tilemap_map_compressed);

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetColor(0);
    gfx_SetTextFGColor(1);
    gfx_SetTextBGColor(0);

    /* Draw to buffer to avoid tearing */
    gfx_SetDrawBuffer();

    /* Set monospace font with width of 8 */
    gfx_SetMonospaceFont(8);

    /* Wait for the enter key to quit */
    do
    {
        uint8_t block_mapped;
        uint8_t block_ptr;

        /* Get the key */
        key = os_GetCSC();

        /* Draw tilemap and coords */
        gfx_Tilemap(&tilemap, x_offset, y_offset);
        gfx_FillRectangle(0, 0, 320, 16);
        gfx_PrintStringXY("x:", 64, 4);
        gfx_PrintInt(x_offset, 3);
        gfx_PrintString(" y:");
        gfx_PrintInt(y_offset, 3);
        gfx_PrintString(" block:");

        /* Or use gfx_GetTileMapped() and gfx_GetTile() */
        block_mapped = *gfx_TilePtrMapped(&tilemap, x_offset / TILE_WIDTH, y_offset / TILE_HEIGHT);
        block_ptr = *gfx_TilePtr(&tilemap, x_offset, y_offset);

        gfx_PrintUInt(block_mapped, 3);
        gfx_PrintString("/");
        gfx_PrintUInt(block_ptr, 3);

        /* Do something based on the keypress */
        switch (key)
        {
            case sk_Down:
                if (y_offset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
                {
                    y_offset += TILE_HEIGHT;
                }
                break;

            case sk_Left:
                if (x_offset)
                {
                    x_offset -= TILE_WIDTH;
                }
                break;

            case sk_Right:
                if (x_offset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
                {
                    x_offset += TILE_WIDTH;
                }
                break;

            case sk_Up:
                if (y_offset)
                {
                    y_offset -= TILE_HEIGHT;
                }
                break;

            default:
                break;
        }

        gfx_SwapDraw();

    } while (key != sk_Enter);

    /* End graphics drawing */
    gfx_End();

    return 0;
}
