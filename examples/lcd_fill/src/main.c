#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes */
void fill_screen(uint8_t color);

void main(void) { 
    /* Turn the whole screen black */
    fill_screen(0x00);
    
    /* Wait for a key press */
    while (!os_GetCSC());
    
    /* Turn the whole screen red */
    fill_screen(0xe0);
    
    /* Wait for a key press */
    while (!os_GetCSC());
}

/* Fill the screen with a given color */
void fill_screen(uint8_t color) {
    memset(lcd_Ram, color, LCD_SIZE);
}

