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
void cleanUp();


/* Put all your globals here. */

const static char hello[]   = "HELLO WORLD!";
const static char welcome[] = "Welcome to C programming!";


/* Put all your code here */

void main()
{
    // initial variables
    char Apples[] = "Apples.";
    char Orange[] = "Orange.";
    uint8_t i;

    cleanUp();

    print(hello, 0, 0);

    for (i=1; i<5; i++)
    {
        print(welcome, 0, i);
    }

    strcpy(Apples, Orange);
    print(Apples, 0, i);    // Should print "Orange."
    print(Orange, 0, i+1);  // Should also print "Orange."

    _OS( GetKey() );
    cleanUp();
}



/* Other functions */

void print(const char* string, uint8_t xpos, uint8_t ypos)
{
    _OS( asm("LD HL,(IX+6)");
         asm("LD A,(IX+9)");
         asm("LD (curCol),A");
         asm("LD A,(IX+12)");
         asm("LD (curRow),A");
         asm("CALL _PutS");
       );
}

void printSmall(const char* string, uint16_t x, uint8_t y)
{
    _OS( asm("LD HL,(IX+6)");
         asm("LD DE,(IX+9)");
         asm("LD (penCol),DE");
         asm("LD A,(IX+12)");
         asm("LD (penRow),A");
         asm("RES textInverse,(IY+textFlags)"); // SET for inverted
         asm("CALL _VPutS");
       );
}

void cleanUp()
{
    // Clear/invalidate some RAM areas
    _OS( asm("CALL _DelRes");
         asm("CALL _ClrTxtShd");
         asm("CALL _ClrScrn");
         asm("SET  graphDraw,(iy+graphFlags)");
         // Restore the home screen nicely
         asm("CALL _HomeUp");
         asm("CALL _DrawStatusBar");
       );
}