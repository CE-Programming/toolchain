// convpng
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __logo_gfx__
#define __logo_gfx__
#include <stdint.h>

#define logo_gfx_transparent_color_index 0

#define ubuntu_width 32
#define ubuntu_height 32
#define ubuntu_size 1026
extern uint8_t ubuntu_data[1026];
#define ubuntu ((gfx_sprite_t*)ubuntu_data)
#define sizeof_logo_gfx_pal 378
extern uint16_t logo_gfx_pal[189];

#endif
