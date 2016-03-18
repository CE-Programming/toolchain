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
void fillScreen(unsigned color);
void waitSeconds(uint8_t seconds);

/* Location of memory-mapped screen */
uint16_t *lcd_vramArray =  (uint16_t*)0xD40000;

/* Put all your code here */
void main(void) { 
    /* Turn the whole screen black */
    fillScreen(0x00);
    
    /* Wait for a second */
    waitSeconds(1);
    
    /* Turn the whole screen red */
    fillScreen(0xE0);
    
    /* Wait for a second */
    waitSeconds(1);
    
    /* Clean up for the return to the OS */
    pgrm_CleanUp();
}

/* Fill the screen with a given color */
void fillScreen(unsigned color) {
    /* memset_fast is a way faster implementation of memset; either one will work here though */
    memset_fast(lcd_vramArray, color, 320*240*2);
}

/* Wait for a specified about of seconds between 0 and 60 */
/* Note that this will affect the user's actual time on the calculator */
/* A better option would be to use the general purpose timers, since they provide more accurate timming */
void waitSeconds(uint8_t seconds) {
    /* Set the inital seconds to 0 */
    rtc_SetSeconds(0);
    
    /* Load the 0 seconds into the clock */
    rtc_LoadSetTime();
    
    /* Wait until we reach the second needed */
    while(rtc_GetSeconds() != seconds+1);
}