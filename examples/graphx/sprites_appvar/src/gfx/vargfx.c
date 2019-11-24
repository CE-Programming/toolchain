#include "vargfx.h"
#include <fileioc.h>

unsigned char *vargfx_appvar[3] =
{
    (unsigned char*)0,
    (unsigned char*)494,
    (unsigned char*)1520,
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
    for (i = 0; i < 3; i++)
    {
        vargfx_appvar[i] += data;
    }

    ti_CloseAll();

    return 1;
};

