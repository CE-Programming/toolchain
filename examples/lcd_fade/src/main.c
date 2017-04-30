#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
    uint8_t i, level;
    
    /* Store the current brightness level */
    level = lcd_BacklightLevel;
    
    /* Change lcd brightness levels */
    for (i = level; i > 0; i--) {
        boot_WaitShort();
        lcd_BacklightLevel = i;
    }
    
    for (i = 0; i < 255; i++) {
        boot_WaitShort();
        lcd_BacklightLevel = i;
    }

    /* Restore the old brightness level */
    lcd_BacklightLevel = level;
}
