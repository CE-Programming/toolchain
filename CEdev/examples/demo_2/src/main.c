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
// stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h, intce.h

/* Put function prototypes here */

/* Put all your code here */
void main(void) {
    uint8_t i, level;
    
    /* Store the current brightness level */
    level = lcd_BacklightLevel;
    
    /* Change lcd brightness levels */
    for(i = level; i > 0; i--) {
        boot_WaitShort();
        lcd_BacklightLevel = i;
    }
    
    for(i = 0; i < 255; i++) {
        boot_WaitShort();
        lcd_BacklightLevel = i;
    }

    /* Restore the old brightness level */
    lcd_BacklightLevel = level;

    /* Clean up for the return to the OS */
    prgm_CleanUp();
}
