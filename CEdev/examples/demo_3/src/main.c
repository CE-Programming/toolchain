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

/* Put all your code here */
void main(void) {
	unsigned seconds = 0;
	char str[10];
	
	/* Clean up the home screen */
	prgm_CleanUp();
	
	/* Set the cursor posistion */
	os_SetCursorPos( 0, 0 );
	
	/* Disable everything in the timers so they don't run when we don't want them to */
	boot_SetTimersControlRegister( 0 );
	
	/* By using the 32768 kHz clock, we can count for exactly 1 second here, or a different interval of time */
	boot_SetTimer1ReloadValue( 32768 );
	boot_SetTimer1Counter( 32768 );
	
	/* Enable the timer, set it to the 32768 kHz clock, enable an interrupt once it reaches 0, and make it count down */
	boot_SetTimersControlRegister( TIMER1_ENABLE | TIMER1_32K | TIMER1_INT | TIMER1_DOWN );
	
	while(!os_GetCSC()) {
		if(boot_GetTimersInterruptStatus() & TIMER1_RELOADED) {
			/* Print a string */
			sprintf(str, "%u", seconds++);
			os_SetCursorPos(0,0);
			os_PutStrFull(str);
			
			/* Acknowledge the reload */
			boot_SetTimersInterruptStatus( TIMER1_RELOADED );
		}
	}
	
	/* Clean up for the return to the OS */
	prgm_CleanUp();
}