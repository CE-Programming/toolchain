#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
    /* Starting text posistion */
    int x = GFX_LCD_WIDTH / 2;
    int y = GFX_LCD_HEIGHT / 2;
    int movex = 1;
    int movey = 1;

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the text colors */
    gfx_SetTextFGColor(6);
    gfx_SetTextBGColor(255);
    gfx_SetTextTransparentColor(5);

    /* Enable text clipping */
    gfx_SetTextConfig(gfx_text_clip);
    gfx_SetMonospaceFont(8);

    /* Draw to buffer to avoid flicker */
    gfx_SetDrawBuffer();

    /* Draw the box, and set clip region one pixel around box */
    gfx_Rectangle(25, 25, 270, 190);
    gfx_SetClipRegion(25 + 1, 25 + 1, 270 + 25 - 1, 190 + 25 - 1);

    /* Bounce text around screen */
    /* Run until any key is pressed */
    do
    {
        x += movex;
        y += movey;

        if (x >= GFX_LCD_WIDTH || x < 0)
        {
            movex = -movex;
        }
        if (y >= GFX_LCD_HEIGHT || y < 0)
        {
            movey = -movey;
        }

        gfx_PrintStringXY("CLIPPED TXT", x, y);

        gfx_BlitBuffer();

        gfx_PrintStringXY("                 ", x, y);

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
