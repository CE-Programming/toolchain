#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

/* Use some random color as the transparent one */
#define TRANSPARENT_COLOR 10
#define FONT_WIDTH        8
#define FONT_HEIGHT       8

/* Function prototypes */
void printu(char *str, int x, int y);

const char *my_str = "!!DEPPILF si txet sihT";

void main(void) {
    /* Initialize the 8bpp graphics */
    gfx_Begin();
    gfx_FillScreen(gfx_black);
    
    /* Setup the colors */
    gfx_SetTextFGColor(gfx_white);
    
    /* Set the transparent text background color */
    gfx_SetTextBGColor(TRANSPARENT_COLOR);
    gfx_SetTextTransparentColor(TRANSPARENT_COLOR);
    gfx_SetMonospaceFont(FONT_WIDTH);
    
    /* Print some upside down text */
    printu(my_str, (LCD_WIDTH - gfx_GetStringWidth(my_str)) / 2, (LCD_HEIGHT - FONT_HEIGHT) / 2);
    
    /* Wait for key */
    while (!os_GetCSC());
    
    /* Finish the graphics */
    gfx_End();
}

void printu(char *str, int x, int y) {
    gfx_TempSprite(my_char, 8, 8);
    
    while (*str) {
        gfx_TransparentSprite(gfx_RotateSpriteHalf(gfx_GetSpriteChar(*str), my_char), x, y);
        x += gfx_GetCharWidth(*str++);
    }
}
