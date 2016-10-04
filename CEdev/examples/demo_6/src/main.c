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
// assert.h stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h
#include <intce.h>

/* Place function prototypes here */
void interrupt isr_on(void);

/* Global status flag */
bool exit_loop = false;

/* Main function */
void main(void) {
	/* Print a little string -- Note that using OS routines doesn't work too well when interrupts are actually running */
	prgm_CleanUp();
	os_SetCursorPos( 0, 0 );
	os_PutStrFull("Press ON");
	
	/* Initialize the interrupt handlers */
	int_Initialize();
	
	/* Set the isr_on routine to run when the [ON] key is pressed */
	int_SetVector(ON_IVECT, isr_on);
	
	/* Tell the interrupt controller that the ON flag should latch and be enabled */
	int_LatchConfig = int_EnableConfig = INT_ON;
	
	/* Interrupts can now generate after this */
	int_Enable();
	
	/* Wait for the [ON] key to be pressed */
	while( !exit_loop );
	
	/* Reset the interrupt handler and cleanup the program */
	int_Reset();
	prgm_CleanUp();
}

/* Interrupt routine to run when the [ON] key is pressed */
void interrupt isr_on(void) {
	/* Exit the "infinite" loop */
	exit_loop = true;
	
	/* Must acknowledge that the interrupt occured to clear the flag */
	int_Acknowledge = INT_ON;
}