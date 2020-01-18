// convpng
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __var_gfx__
#define __var_gfx__
#include <stdint.h>

#include <stdbool.h>

#define var_gfx_num 2

extern uint8_t *var_gfx[2];
#define tileset_compressed ((gfx_sprite_t*)var_gfx[0])
#define tileset_tiles_num 12
extern uint8_t *tileset_tiles_compressed[12];
#define tileset_tile_0_compressed ((gfx_sprite_t*)tileset_tiles_compressed[0])
#define tileset_tile_1_compressed ((gfx_sprite_t*)tileset_tiles_compressed[1])
#define tileset_tile_2_compressed ((gfx_sprite_t*)tileset_tiles_compressed[2])
#define tileset_tile_3_compressed ((gfx_sprite_t*)tileset_tiles_compressed[3])
#define tileset_tile_4_compressed ((gfx_sprite_t*)tileset_tiles_compressed[4])
#define tileset_tile_5_compressed ((gfx_sprite_t*)tileset_tiles_compressed[5])
#define tileset_tile_6_compressed ((gfx_sprite_t*)tileset_tiles_compressed[6])
#define tileset_tile_7_compressed ((gfx_sprite_t*)tileset_tiles_compressed[7])
#define tileset_tile_8_compressed ((gfx_sprite_t*)tileset_tiles_compressed[8])
#define tileset_tile_9_compressed ((gfx_sprite_t*)tileset_tiles_compressed[9])
#define tileset_tile_10_compressed ((gfx_sprite_t*)tileset_tiles_compressed[10])
#define tileset_tile_11_compressed ((gfx_sprite_t*)tileset_tiles_compressed[11])
#define sizeof_tiles_gfx_pal 512
#define tiles_gfx_pal ((uint16_t*)var_gfx[1])
bool var_gfx_init(void);

#endif
