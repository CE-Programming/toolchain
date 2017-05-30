// Converted using ConvPNG
#include <stdint.h>
#include "var_gfx.h"

#include <fileioc.h>
uint8_t *var_gfx[3] = {
 (uint8_t*)0,
 (uint8_t*)1026,
 (uint8_t*)2052,
};

bool var_gfx_init(void) {
    unsigned int i,s = (unsigned int)var_gfx[0];
    ti_var_t appvar;
    void *data;

    ti_CloseAll();

    appvar = ti_Open("var_gfx", "r");
    data = ti_GetDataPtr(appvar);
    for (i = 0; i < var_gfx_num; i++) {
        var_gfx[i] += (unsigned int)data - s;
    }

    ti_CloseAll();
    return (bool)appvar;
}
