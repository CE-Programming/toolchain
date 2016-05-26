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
	
	dbg_sprintf(dbgout,"Testing\n");
	
	
	
	/* Clean up for the return to the OS */
	prgm_CleanUp();
}