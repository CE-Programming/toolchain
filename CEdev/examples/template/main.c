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

/* Function Prototypes */
void print(char* string, uint8_t xpos, uint8_t ypos);
void cleanUp();

const static char hello[] = "HELLO WORLD!";
const static char welcome[] = "Welcome To The World Of C!";
const static char Apples[] ="Apples.";
const static char Orange[] ="Oranges.";
    
void main() {
	uint8_t i;
    
	_OS( cleanUp();
	     print(hello, 0, 0);
       );
	
	for(i=1; i<5; i++) {
		_OS( print(welcome, 0, i) );
	}
	
	strcpy(Apples, Orange);
    
	_OS( print(Apples, 0, i);       /* Should print "Oranges."   */
	     print(Orange, 0, i+1);     /* Should also print "Oranges."   */
         GetKey();
	     cleanUp();
       );
}

void cleanUp() {
	asm("CALL _DelRes");
	asm("CALL _ClrTxtShd");
	asm("CALL _ClrScrn");
	asm("set 0,(iy+3)");
	asm("CALL _HomeUp");
	asm("CALL _DrawStatusBar");
}

void print(char* string, uint8_t xpos, uint8_t ypos) {
	asm("LD A,(IX+9)");
	asm("LD (D00596h),A");
	asm("LD A,(IX+12)");
	asm("LD (D00595h),A");
	asm("LD	HL,(IX+6)");
	asm("CALL _PutS");
}