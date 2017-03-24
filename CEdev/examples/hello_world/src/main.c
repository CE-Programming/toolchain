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
void printText(const char *text, uint8_t x, uint8_t y);
void printTextSmall(const char *text, uint8_t xpos, uint8_t ypos);

/* Initialize some strings */
const char *HelloWorld = "Hello World!";
const char *Welcome = "Welcome to C!";

/* Put all your code here */
void main(void) {
    /* uint8_t is an unsigned integer that can range from 0-255. It performs faster than just an int, so try to use it (or int8_t) when possible */
    uint8_t count;

    /* This function cleans up the screen and gets everything ready for the OS */
    prgm_CleanUp();
    
    /* Print a few strings */
    printText( HelloWorld, 0, 0 );
    printText( Welcome, 0, 1 );
    
    /* Wait for a key press */
    while( !os_GetCSC() );
    
    /* Clean up, and exit */
    prgm_CleanUp();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(const char *text, uint8_t xpos, uint8_t ypos) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

/* Draw small text at the given X/Y location */
void printTextSmall(const char *text, uint8_t xpos, uint8_t ypos) {
    os_FontDrawText(text, xpos, ypos);
}