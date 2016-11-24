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
	uint8_t i, bl_level_copy;
	
	bl_level_copy = lcd_BacklightLevel;
	
	for(i = bl_level_copy; i > 0; i--) {
		boot_WaitShort();
		lcd_BacklightLevel = i;
	}
	
	for(i = 0; i < 255; i++) {
		boot_WaitShort();
		lcd_BacklightLevel = i;
	}

	lcd_BacklightLevel = bl_level_copy;

	/* Clean up for the return to the OS */
	prgm_CleanUp();
}
