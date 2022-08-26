#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    gfx_FillScreen(19);
    gfx_SetColor(255);
    gfx_FillRectangle(100, 100, 60, 40);
    gfx_SetColor(227);
    gfx_FillRectangle(160, 100, 60, 40);

    /* Waits for a key */
    while (!os_GetCSC());

    gfx_ShiftDown(20);
    gfx_ShiftDown(20);

    /* Waits for a key */
    while (!os_GetCSC());

    gfx_ShiftLeft(20);
    gfx_ShiftLeft(20);

    /* Waits for a key */
    while (!os_GetCSC());

    gfx_ShiftUp(20);
    gfx_ShiftUp(20);

    /* Waits for a key */
    while (!os_GetCSC());

    gfx_ShiftRight(20);
    gfx_ShiftRight(20);

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
