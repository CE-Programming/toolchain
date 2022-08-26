#include <string.h>
#include <ti/getcsc.h>
#include <graphx.h>

#define TEXT_FG_COLOR            247
#define TEXT_BG_COLOR            0
#define FONT_WIDTH               8
#define FONT_HEIGHT              8

void PrintCenteredFlippedText(char *str);

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();
    gfx_ZeroScreen();

    /* Setup the text */
    gfx_SetTextFGColor(TEXT_FG_COLOR);
    gfx_SetTextBGColor(TEXT_BG_COLOR);
    gfx_SetMonospaceFont(FONT_WIDTH);

    /* Print some upside down text */
    PrintCenteredFlippedText("THIS TEXT IS FLIPPED");

    /* Waits for a key */
    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}

void PrintCenteredFlippedText(char *str)
{
    int x, y;
    char *string = str + strlen(str) - 1;
    gfx_TempSprite(ch, 8, 8);

    x = (GFX_LCD_WIDTH - gfx_GetStringWidth(str)) / 2;
    y = (GFX_LCD_HEIGHT - FONT_HEIGHT) / 2;

    while (*string)
    {
        gfx_Sprite(gfx_RotateSpriteHalf(gfx_GetSpriteChar(*string), ch), x, y);
        x += gfx_GetCharWidth(*string--);
    }
}
