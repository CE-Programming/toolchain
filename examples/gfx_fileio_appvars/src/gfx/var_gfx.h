// Converted using ConvPNG
// This file contains all the graphics sources for easier inclusion in a project
#ifndef __var_gfx__
#define __var_gfx__
#include <stdint.h>

#include <stdbool.h>

#define var_gfx_num 3

extern uint8_t *var_gfx[3];
#define ubuntu ((gfx_image_t*)var_gfx[0])
#define mint ((gfx_image_t*)var_gfx[1])

bool var_gfx_init(void);
#define sizeof_all_gfx_pal 512
#define all_gfx_pal ((uint16_t*)var_gfx[2])

#endif
