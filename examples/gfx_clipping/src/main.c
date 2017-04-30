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

void main(void) {
    uint8_t key = 24;
    
    /* Starting text posistion */
    int x = (LCD_WIDTH/2)-20, y = (LCD_HEIGHT/2)-5;
    
    int box_stride = 1;
    int box_scale = 20;
    
    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);
    gfx_FillScreen(gfx_black);
    
    /* Setup the colors */
    gfx_SetColor(gfx_white);
    gfx_SetTextFGColor(gfx_red);
    
    /* Set the transparent text background color */
    gfx_SetTextBGColor(TRANSPARENT_COLOR);
    gfx_SetTextTransparentColor(TRANSPARENT_COLOR);
    
    /* Print some scaled font */
    gfx_SetTextScale(2,2);
    gfx_PrintStringXY("This text is SCALED!!", 15, 10);
    
    /* Wait for a key before continuing */
    while (!os_GetCSC());
    
    /* Configure the font to normal size, clipped, and monospaced */
    gfx_SetTextScale(1,1);
    gfx_SetTextConfig(gfx_text_clip);
    gfx_SetMonospaceFont(FONT_WIDTH);
    
    /* Graphics routines draw to the back buffer */
    gfx_SetDrawBuffer();
    
    /* Run until the [ENTER] key is pressed */
    do {
        /* Check if any keys are pressed */
        if (key == sk_Left)  { x--; }
        if (key == sk_Right) { x++; }
        if (key == sk_Down)  { y++; }
        if (key == sk_Up)    { y--; }
        if (key) {
            gfx_SetClipRegion((LCD_WIDTH/2) - box_scale, (LCD_HEIGHT/2) - box_scale, (LCD_WIDTH/2) + box_scale, (LCD_HEIGHT/2) + box_scale);
            
            gfx_FillScreen(gfx_black);
            gfx_PrintStringXY("FUN WITH CLIPPING", x, y);
            
            /* Draw a rectangle on the edged of the clipping region so we can see it */
            gfx_Rectangle((LCD_WIDTH/2) - box_scale, (LCD_HEIGHT/2) - box_scale, box_scale * 2, box_scale * 2);
            
            /* Change the clipping region */
            box_scale += box_stride;
            
            /* Check if we should increase or decrease the clip region */
            if (box_scale > 100 || box_scale < 1) {
                box_stride = -box_stride;
            }
            
            /* Move the graphics so the user can see it */
            gfx_SwapDraw();
        }
    } while ((key = os_GetCSC()) != sk_Enter);
    
    /* Usual cleanup */
    gfx_End();
}
