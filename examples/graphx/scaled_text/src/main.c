#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the text colors */
    gfx_SetTextFGColor(6);
    gfx_SetTextBGColor(255);

    /* Print some scaled text */
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("SCALED TXT", 10, 10);
    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("SCALED TXT", 10, 40);
    gfx_SetTextScale(4, 4);
    gfx_PrintStringXY("SCALED TXT", 10, 90);
    gfx_SetTextScale(4, 8);
    gfx_PrintStringXY("SCALED TXT", 10, 150);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
