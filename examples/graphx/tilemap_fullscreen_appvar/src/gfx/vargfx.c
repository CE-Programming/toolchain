#include "vargfx.h"
#include <fileioc.h>

unsigned char *vargfx_appvar[2] =
{
    (unsigned char*)0,
    (unsigned char*)512,
};

unsigned char *image_tiles_compressed[12] =
{
    (unsigned char*)0,
    (unsigned char*)3911,
    (unsigned char*)8107,
    (unsigned char*)12473,
    (unsigned char*)15886,
    (unsigned char*)21280,
    (unsigned char*)26147,
    (unsigned char*)30900,
    (unsigned char*)36284,
    (unsigned char*)41930,
    (unsigned char*)46626,
    (unsigned char*)50876,
};

unsigned char vargfx_init(void)
{
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("vargfx", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)vargfx_appvar[0];
    for (i = 0; i < 2; i++)
    {
        vargfx_appvar[i] += data;
    }

    ti_CloseAll();

    data = (unsigned int)vargfx_appvar[1] - (unsigned int)image_tiles_compressed[0];
    for (i = 0; i < image_tiles_num; i++)
    {
        image_tiles_compressed[i] += data;
    }

    return 1;
};

