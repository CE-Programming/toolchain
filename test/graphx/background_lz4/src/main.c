#include <ti/getcsc.h>
#include <graphx.h>
#include <compression.h>

#include "gfx/gfx.h"

int main(void)
{
    gfx_Begin();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    lz4_Decompress(gfx_vram, background_compressed);

    while (!os_GetCSC());

    gfx_ZeroScreen();

    if (lz4_Decompress_Block(gfx_vram, background_compressed + sizeof(uint24_t), background_compressed_size) != background_size)
    {
        gfx_ZeroScreen();
    }

    while (!os_GetCSC());

    gfx_End();

    return 0;
}
