// convpng
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __logo_gfx__
#define __logo_gfx__
#include <stdint.h>

#define logo_gfx_transparent_color_index 0

#define ubuntu_width 31
#define ubuntu_height 30
#define ubuntu_size 545
extern uint8_t ubuntu_data[545];
#define ubuntu ((gfx_rletsprite_t*)ubuntu_data)
#define sizeof_logo_gfx_pal 394
extern uint16_t logo_gfx_pal[197];

#endif
