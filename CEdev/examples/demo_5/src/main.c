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
#include <assert.h>
#include <debug.h>

/* Put function prototypes here */

/* Put all your code here */
void main(void) {
	/* Set the intial value of some variables */
	int dbg_test_var_1 = 10;
	uint8_t dbg_test_var_2 = 3;
	
	/* Print a simple debugging string */
	dbg_sprintf(dbgout, "This is the start of a CEmu debugging test\n");
	
	/* Set a watchpoint that will break anytime we write/change this varaible */
	dbg_SetWriteWatchpoint( &dbg_test_var_1, sizeof dbg_test_var_1 );
	
	/* Set a non breaking watchpoint just so we can see what is in this variable at any given time */
	dbg_SetWatchpoint( &dbg_test_var_2, sizeof dbg_test_var_2 );
	
	/* Now, let's write to the varaible to see what happens (Go to the 'Watchpoints' tab in CEmu to view the status) */
	dbg_test_var_1 = 5;
	
	/* Remove the watchpoint that we had set */
	dbg_RemoveWatchpoint( &dbg_test_var_1 );
	dbg_RemoveWatchpoint( &dbg_test_var_2 );
	
	/* Clean up everything */
	prgm_CleanUp();
}