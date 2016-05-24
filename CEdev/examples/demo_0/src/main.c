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
void printText(const char *text, uint8_t x, uint8_t y);
void printTextSmall(const char *text, uint8_t xpos, uint8_t ypos);

/* Initialize some strings -- It is faster to place strings as globals */
const char HelloWorld[] = "Hello World!";
const char Welcome[] = "Welcome to C!";
char Apples[] = "Apples!";
char Oranges[] = "Oranges";

int24_t h = 12;

/* Put all your code here */
void main(void) {
    /* uint8_t is an unsigned integer that can range from 0-255. It generally performs faster than just an int, so try to use it when possible */
    uint8_t count = h;

    /* This function cleans up the screen and gets everything ready for the OS */
    prgm_CleanUp();
    
    /* Print a few strings */
    printText(HelloWorld, 0, 0);
    printText(Welcome, 0, 1);
    
    /* This will print 'Apples' */
    for(count=3; count<6; count++) {
        printText(Apples, 0, count);
    }
    
    /* Copy the 'Oranges' string to the 'Apples' location */
    strcpy(Apples, Oranges);
    
    /* This will print 'Oranges'. Therefore, apples are oranges */
    for(count=6; count<9; count++) {
        printText(Apples, 0, count);
    }
    
    /* Do not use os_GetKey() in your programs; this is just a demo */
    os_GetKey();
    
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