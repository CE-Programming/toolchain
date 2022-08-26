#include <ti/getcsc.h>
#include <graphx.h>

#define COLOR gfx_RGBTo1555(34, 55, 89)

int main(void)
{
    uint8_t i = 0;

    /* Initialize graphics drawing */
    gfx_Begin();

    /* For i in 0..255 */
    do
    {
        /* Fade out to black */
        gfx_palette[0] = gfx_Darken(COLOR, i);
        gfx_SetColor(0);
        gfx_FillRectangle_NoClip(0, 0, 160, 120);

        /* Fade in from black */
        gfx_palette[1] = gfx_Darken(COLOR, ~i);
        gfx_SetColor(1);
        gfx_FillRectangle_NoClip(160, 0, 160, 120);

        /* Fade in from white */
        gfx_palette[2] = gfx_Lighten(COLOR, i);
        gfx_SetColor(2);
        gfx_FillRectangle_NoClip(0, 120, 160, 120);

        /* Fade out to white */
        gfx_palette[3] = gfx_Lighten(COLOR, ~i);
        gfx_SetColor(3);
        gfx_FillRectangle_NoClip(160, 120, 160, 120);

        /* Wait for a keypress at the start of each quarter of the fade */
        if (!(i & 0x3f))
        {
            while (!os_GetCSC());
        }

    /* Loop until i is 0 again because of 8 bit range */
    } while (++i);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
