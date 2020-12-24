#include "vargfx.h"
#include <fileioc.h>

#define vargfx_HEADER_SIZE 0

unsigned char *vargfx_appvar[2] =
{
    (unsigned char*)0,
    (unsigned char*)154,
};

unsigned char *tileset_tiles_data[128] =
{
    (unsigned char*)0,
    (unsigned char*)258,
    (unsigned char*)516,
    (unsigned char*)774,
    (unsigned char*)1032,
    (unsigned char*)1290,
    (unsigned char*)1548,
    (unsigned char*)1806,
    (unsigned char*)2064,
    (unsigned char*)2322,
    (unsigned char*)2580,
    (unsigned char*)2838,
    (unsigned char*)3096,
    (unsigned char*)3354,
    (unsigned char*)3612,
    (unsigned char*)3870,
    (unsigned char*)4128,
    (unsigned char*)4386,
    (unsigned char*)4644,
    (unsigned char*)4902,
    (unsigned char*)5160,
    (unsigned char*)5418,
    (unsigned char*)5676,
    (unsigned char*)5934,
    (unsigned char*)6192,
    (unsigned char*)6450,
    (unsigned char*)6708,
    (unsigned char*)6966,
    (unsigned char*)7224,
    (unsigned char*)7482,
    (unsigned char*)7740,
    (unsigned char*)7998,
    (unsigned char*)8256,
    (unsigned char*)8514,
    (unsigned char*)8772,
    (unsigned char*)9030,
    (unsigned char*)9288,
    (unsigned char*)9546,
    (unsigned char*)9804,
    (unsigned char*)10062,
    (unsigned char*)10320,
    (unsigned char*)10578,
    (unsigned char*)10836,
    (unsigned char*)11094,
    (unsigned char*)11352,
    (unsigned char*)11610,
    (unsigned char*)11868,
    (unsigned char*)12126,
    (unsigned char*)12384,
    (unsigned char*)12642,
    (unsigned char*)12900,
    (unsigned char*)13158,
    (unsigned char*)13416,
    (unsigned char*)13674,
    (unsigned char*)13932,
    (unsigned char*)14190,
    (unsigned char*)14448,
    (unsigned char*)14706,
    (unsigned char*)14964,
    (unsigned char*)15222,
    (unsigned char*)15480,
    (unsigned char*)15738,
    (unsigned char*)15996,
    (unsigned char*)16254,
    (unsigned char*)16512,
    (unsigned char*)16770,
    (unsigned char*)17028,
    (unsigned char*)17286,
    (unsigned char*)17544,
    (unsigned char*)17802,
    (unsigned char*)18060,
    (unsigned char*)18318,
    (unsigned char*)18576,
    (unsigned char*)18834,
    (unsigned char*)19092,
    (unsigned char*)19350,
    (unsigned char*)19608,
    (unsigned char*)19866,
    (unsigned char*)20124,
    (unsigned char*)20382,
    (unsigned char*)20640,
    (unsigned char*)20898,
    (unsigned char*)21156,
    (unsigned char*)21414,
    (unsigned char*)21672,
    (unsigned char*)21930,
    (unsigned char*)22188,
    (unsigned char*)22446,
    (unsigned char*)22704,
    (unsigned char*)22962,
    (unsigned char*)23220,
    (unsigned char*)23478,
    (unsigned char*)23736,
    (unsigned char*)23994,
    (unsigned char*)24252,
    (unsigned char*)24510,
    (unsigned char*)24768,
    (unsigned char*)25026,
    (unsigned char*)25284,
    (unsigned char*)25542,
    (unsigned char*)25800,
    (unsigned char*)26058,
    (unsigned char*)26316,
    (unsigned char*)26574,
    (unsigned char*)26832,
    (unsigned char*)27090,
    (unsigned char*)27348,
    (unsigned char*)27606,
    (unsigned char*)27864,
    (unsigned char*)28122,
    (unsigned char*)28380,
    (unsigned char*)28638,
    (unsigned char*)28896,
    (unsigned char*)29154,
    (unsigned char*)29412,
    (unsigned char*)29670,
    (unsigned char*)29928,
    (unsigned char*)30186,
    (unsigned char*)30444,
    (unsigned char*)30702,
    (unsigned char*)30960,
    (unsigned char*)31218,
    (unsigned char*)31476,
    (unsigned char*)31734,
    (unsigned char*)31992,
    (unsigned char*)32250,
    (unsigned char*)32508,
    (unsigned char*)32766,
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

    data = (unsigned int)vargfx_appvar[1] - (unsigned int)tileset_tiles_data[0];
    for (i = 0; i < tileset_tiles_num; i++)
    {
        tileset_tiles_data[i] += data;
    }

    return 1;
}

