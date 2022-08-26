#include <ti/getcsc.h>
#include <graphx.h>
#include <compression.h>

#include "gfx/gfx.h"

int main(void)
{
    gfx_Begin();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    zx7_Decompress(gfx_vram, background_compressed);

    while (!os_GetCSC());

    gfx_End();

    return 0;
}
