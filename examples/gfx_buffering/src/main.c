#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

/* This tutorial is meant to be played around with to get a feeling for how buffering works */
void main(void) {
    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);
    
    /* Set up the palette */
    gfx_SetColor(gfx_black);
    
    /* Draw to buffer to avoid tearing */
    gfx_SetDrawBuffer();
    
    /* Draw a line on the buffer */
    //gfx_FillScreen(gfx_black);
    gfx_Line(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
    
    /* Wait for a key */
    while (!os_GetCSC()); 
    
    /* Swap the buffer with the screen */
    gfx_SwapDraw();
    
    /* Copy part of the screen to the offscreen buffer */
    gfx_Blit(gfx_buffer);
    //gfx_BlitLines(gfx_buffer, 0, 20);
    //gfx_BlitRectangle(gfx_buffer, 0, 0, 160, 120);
    
    /* This should cause half of the line to flicker, and the other half to stay steady */
    
    while (!os_GetCSC()) {
        gfx_SwapDraw();
    }
    
    /* Close the graphics */
    gfx_End();
}
