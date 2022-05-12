#include <ti/screen.h>
#include <sys/rtc.h>
#include <sys/lcd.h>
#include <sys/util.h>

#include <string.h>

int main(void)
{
    uint8_t seconds = 0;

    /* Clear the homescreen */
    os_ClrHome();

    /* Enable the RTC, and enable second change interrupts */
    rtc_Enable(RTC_SEC_INT);

    /* Wait for the RTC to not be busy and acknowledge all interrupts */
    while (rtc_IsBusy());
    rtc_AckInterrupt(RTC_INT_MASK);

    /* Wait until 5 seconds have passed */
    while (seconds < 5)
    {
        /* If a second passed, increment the second counter and then */
        /* fill the screen with a fresh color */
        if (rtc_ChkInterrupt(RTC_SEC_INT))
        {
            memset((void*)lcd_Ram, randInt(0, 255), LCD_SIZE);
            seconds++;

            rtc_AckInterrupt(RTC_SEC_INT);
        }
    }

    return 0;
}
