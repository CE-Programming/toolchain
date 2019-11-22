// convpng
#include <stdint.h>
#include "var_gfx.h"

#include <fileioc.h>
uint8_t *var_gfx[3] = {
 (uint8_t*)0,
 (uint8_t*)1026,
 (uint8_t*)2052,
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

    return (bool)appvar;
}
