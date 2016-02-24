/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ti84pce.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other available headers */
// stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h

/* Put your function prototypes here */
void print(const char* string, uint8_t col, uint8_t row);
void printSmall(const char* string, uint16_t x, uint8_t y);
void cleanUp(void);

/* Put all your globals here. */
const static char hello[]   = "HELLO WORLD!";
const static char welcome[] = "Welcome to C programming!";

/* Put all your code here */
void main(void) {
    // initial variables
    char Apples[] = "Apples.";
    char Orange[] = "Orange.";
    unsigned i;

    cleanUp();

    print(hello, 0, 0);

    for (i=1; i<5; i++) {
        print(welcome, 0, i);
    }

    strcpy(Apples, Orange);
    print(Apples, 0, i);    /* Should print "Orange."      */
    print(Orange, 0, i+1);  /* Should also print "Orange." */
    
    /* Don't use GetKey in your programs */
    _OS( GetKey() );
    cleanUp();
}

/* Other functions */
void print(const char* string, uint8_t xpos, uint8_t ypos) {
    _OS( asm("ld hl,(ix+6)");
         asm("ld a,(ix+9)");
         asm("ld (curCol),a");
         asm("ld a,(ix+12)");
         asm("ld (curRow),a");
         asm("call _PutS");
       );
}

void printSmall(const char* string, uint16_t x, uint8_t y) {
    _OS( asm("ld hl,(ix+6)");
         asm("ld de,(ix+9)");
         asm("ld (penCol),DE");
         asm("ld A,(ix+12)");
         asm("ld (penRow),a");
         /* Use set for inverted text */
         asm("res textInverse,(IY+textFlags)");
         asm("call _VPutS");
       );
}

void cleanUp(void) {
    /* Clear/invalidate some RAM areas */
    /* Restore the home screen nicely */
    _OS( asm("call _DelRes");
         asm("call _ClrTxtShd");
         asm("call _ClrScrn");
         asm("call _HomeUp");
         asm("call _DrawStatusBar");
    );
    asm("set graphDraw,(iy+graphFlags)");
}