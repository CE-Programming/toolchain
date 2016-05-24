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
	uint8_t i;
	
	for(i=0; i<200; i++) {
		dbg_sprintf(dbgout,"This is test %d of a really long string to make sure output is okayish.\n", i);
	}
	
	/* Clean up for the return to the OS */
	prgm_CleanUp();
}