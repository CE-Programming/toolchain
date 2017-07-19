#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

#define FONT_HEIGHT 8

/* Function prototypes */
void print_string_centered(const char *str);

void main(void) {
    const char *msg = "Hello World!";
    
    /* Seed the random numbers */
    srand(rtc_Time());
    
    /* Initialize the 8bpp graphics */
    gfx_Begin();
    
    /* Fill the screen black */
    gfx_FillScreen(gfx_black);
    
    /* Set the random text color */
    gfx_SetTextFGColor(randInt(1, 255));
    
    /* Print the message on the screen */
    print_string_centered(msg);
    
    /* Wait for a key to be pressed */
    while (!os_GetCSC());
    
    /* Close the graphics */
    gfx_End();
}

/* Prints a screen centered string */
void print_string_centered(const char *str) {
    gfx_PrintStringXY(str, (LCD_WIDTH - gfx_GetStringWidth(str)) / 2, (LCD_HEIGHT - FONT_HEIGHT) / 2);
}

