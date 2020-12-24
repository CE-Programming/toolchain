#include <tice.h>
#include <string.h>

int main(void)
{
    unsigned int seconds = 0;

    /* Clear the homescreen */
    os_ClrHome();

    /* Configure the RTC */
    rtc_LoadSeconds = rtc_LoadMinutes = rtc_LoadHours = rtc_LoadDays = 0;
    rtc_Control = RTC_ENABLE | RTC_LOAD | RTC_SEC_INT_SOURCE;

    /* Wait for the RTC to load in the new values and acknowledge all the interrupts */
    while (rtc_IsBusy());
    rtc_IntAcknowledge = RTC_INT_MASK;

    /* Wait until 5 seconds have passed */
    while (seconds < 5)
    {
        /* If a second passed, increment the second counter */
        /* Fill the screen with a new color */
        if (rtc_IntStatus & RTC_SEC_INT)
        {
            memset((void*)lcd_Ram, randInt(0,255), LCD_SIZE);
            seconds++;

            rtc_IntAcknowledge = rtc_IntStatus;
        }
    }

    return 0;
}
