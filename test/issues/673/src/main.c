#include <ti/getcsc.h>
#include <graphx.h>
#include <limits.h>

static const int test_params[][2] =
{
    { 0, 200 },
    { 50, 256 },
    { 100, 220 },
    { -1, 201 },
    { 100, 221 },
    { 150, INT_MAX },
    { -20, INT_MAX },
    { -40, 20 },
    { -40, 40 },
    { -40, 41 },
    { -40, 400 },
    { 320, 50 },
    { 319, 51 },
    { -1, 0 },
    { 0, 0 },
    { 319, 0 },
    { 320, 0 },
    { 50, -1 },
    { 100, INT_MIN },
};

static const int clip_regions[4][2] = {
    { 0, 320 },
    { 80, 220 },
    { 50, 101 },
    { 149, 319 },
};

int main(void)
{
    gfx_Begin();

    for (int j = 0; j < 4; j++)
    {
        gfx_SetClipRegion(clip_regions[j][0], 0, clip_regions[j][1], 240);

        for (int i = 0; i < (int)(sizeof(test_params) / sizeof(test_params[0])); i++)
        {
            gfx_SetColor(i);
            gfx_HorizLine(test_params[i][0], j * 60 + i * 2 + 1, test_params[i][1]);
        }
    }

    while (!os_GetCSC());

    gfx_End();

    return 0;
}
