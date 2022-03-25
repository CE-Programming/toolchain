#include <ti/getcsc.h>
#include <graphx.h>
#include <stdlib.h>

void PrintCentered(const char *str);

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();

    /* Print the message on the screen */
    PrintCentered("Hello, World!");

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}

/* Prints a screen centered string */
void PrintCentered(const char *str)
{
    gfx_PrintStringXY(str,
                      (gfx_lcdWidth - gfx_GetStringWidth(str)) / 2,
                      (gfx_lcdHeight - 8) / 2);
}
