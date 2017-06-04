// Converted using ConvPNG
#include <stdint.h>
#include "var_gfx.h"

#include <fileioc.h>
uint8_t *var_gfx[2] = {
 (uint8_t*)0,
 (uint8_t*)33024,
};

bool var_gfx_init(void) {
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("var_gfx", "r");
    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)var_gfx[0];
    for (i = 0; i < var_gfx_num; i++) {
        var_gfx[i] += data;
    }

    ti_CloseAll();

    data = (unsigned int)var_gfx[0] - (unsigned int)tileset_tiles_data[0];
    for (i = 0; i < tileset_tiles_num; i++) {
        tileset_tiles_data[i] += data;
    }

    return (bool)appvar;
}
