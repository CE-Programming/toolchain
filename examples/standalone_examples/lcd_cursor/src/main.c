#include <stdio.h>
#include <string.h>
#include <ti/getcsc.h>
#include <ti/screen.h>
#include <sys/lcd.h>

/* Include the converted image data */
#include "gfx/gfx.h"

bool quit = false;

uint24_t cursorX = 0;
uint24_t cursorY = 0;

int main(void)
{
    os_ClrHome();

    // Some demo text
    for (uint8_t i = 0; i < 5; i++) {
        printf("Cursor demo: arrow keys\n");
        printf(" move cursor, clear quits\n");    
    }

    // Set up the hardware cursor
    lcd_CrsrSetup();
    lcd_CrsrSetSize(LCD_CURSOR_SIZE_LARGE);
    lcd_CrsrSetImageLarge(cursor_data);

    lcd_CrsrShow();

    while (!quit) {

        uint8_t scancode = os_GetCSC();

        if (scancode == sk_Clear) {
            quit = true;
        }

        switch (scancode) {
            case sk_Up:
                cursorY -= 8;
                break;
            case sk_Down:
                cursorY += 8;
                break;
            case sk_Left:
                cursorX -= 8;
                break;
            case sk_Right:
                cursorX += 8;
                break;
        }

        lcd_CrsrSetPosition(cursorX, cursorY);

    }

    // Clean up the hardware cursor
    lcd_CrsrHide();
    lcd_CrsrCleanup();

    return 0;
}
