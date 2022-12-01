#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

void FillScreen(uint8_t color);

int main(void)
{
    /* Turn the whole screen black */
    FillScreen(0x00);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Turn the whole screen red */
    FillScreen(0xe0);

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}

/* Fill the screen with a given color */
void FillScreen(uint8_t color)
{
    memset(lcd_Ram, color, LCD_SIZE);
}
