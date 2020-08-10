#include "vargfx.h"
#include <fileioc.h>

#define vargfx_HEADER_SIZE 6

unsigned char *vargfx_appvar[2] =
{
    (unsigned char*)6,
    (unsigned char*)518,
};

unsigned char *image_tiles_compressed[12] =
{
    (unsigned char*)0,
    (unsigned char*)3904,
    (unsigned char*)8118,
    (unsigned char*)12446,
    (unsigned char*)15847,
    (unsigned char*)21285,
    (unsigned char*)26195,
    (unsigned char*)31061,
    (unsigned char*)36433,
    (unsigned char*)42094,
    (unsigned char*)46823,
    (unsigned char*)51076,
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

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)vargfx_appvar[0] + vargfx_HEADER_SIZE;
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
}

