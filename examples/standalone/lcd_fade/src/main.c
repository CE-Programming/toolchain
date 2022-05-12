#include <sys/lcd.h>
#include <sys/timers.h>

int main(void)
{
    uint8_t i, level;

    /* Store the current brightness level */
    level = lcd_BacklightLevel;

    /* Change lcd brightness levels */
    for (i = level; i > 0; i--)
    {
        boot_WaitShort();
        lcd_BacklightLevel = i;
    }

    for (i = 0; i < 255; i++)
    {
        boot_WaitShort();
        lcd_BacklightLevel = i;
    }

    /* Restore the original brightness level */
    lcd_BacklightLevel = level;

    return 0;
}
