/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other available headers */
// stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h, intce.h

/* Put function prototypes here */
void fillScreen(uint8_t color);

/* Put all your code here */
void main(void) { 
    /* Turn the whole screen black */
    fillScreen(0x00);
    
    /* Wait for a key press */
    while( !os_GetCSC() );
    
    /* Turn the whole screen red */
    fillScreen(0xE0);
    
    /* Wait for a key press */
    while( !os_GetCSC() );
    
    /* Clean up for the return to the OS */
    prgm_CleanUp();
}

/* Fill the screen with a given color */
void fillScreen(uint8_t color) {
    /* memset_fast is a way faster implementation of memset; either one will work here though */
    memset_fast(lcd_Ram, color, LCD_SIZE);
}
