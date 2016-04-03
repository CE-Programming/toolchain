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

int test(int a) {
	return a;
}

/* Put all your code here */
void main(void) {
    int a,b,c,d,e;
    a = b = c = d = e = 1;
    
    e = d + (c = b + a);
    test(e);
}
	