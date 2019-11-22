#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
    /* Fill VRAM with random data */
    uint32_t *lcd_Ram_i, *lcd_Ram_end = (uint32_t *) ((int) lcd_Ram + LCD_SIZE);
    for (lcd_Ram_i = (uint32_t *) lcd_Ram; lcd_Ram_i < lcd_Ram_end; lcd_Ram_i++) {
        *lcd_Ram_i = random();
    }

    /* Wait for a key press */
    while (!os_GetCSC());
}
