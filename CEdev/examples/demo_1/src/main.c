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
// stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h

/* Put function prototypes here */
void fillScreen(uint8_t color);

/* Location of memory-mapped screen */
uint16_t *lcd_vramArray =  (uint16_t*)0xD40000;

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
    memset_fast(lcd_vramArray, color, 320*240*2);
}
