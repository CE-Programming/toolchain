#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int seconds = 0;

void main(void) {

    /* Clear the homescreen */
    os_ClrHome();

    /* Randomize things */
    srand(rtc_Time());

    /* Configure the RTC */
    rtc_LoadSeconds = rtc_LoadMinutes = rtc_LoadHours = rtc_LoadDays = 0;
    rtc_Control = RTC_ENABLE | RTC_LOAD | RTC_SEC_INT_SOURCE;

    /* Wait for the RTC to load in the new values and then acknowledge all the interrupts */
    while (rtc_IsBusy());
    rtc_IntAcknowledge = RTC_INT_MASK;

    /* Wait until 5 seconds have passed */
    while (seconds < 5) {

        /* If a second passed, increment the second counter */
        if (rtc_IntStatus & RTC_SEC_INT) {
            memset(lcd_Ram, randInt(0,255), LCD_SIZE);
            seconds++;

            rtc_IntAcknowledge = rtc_IntStatus;
        }
    }
}
