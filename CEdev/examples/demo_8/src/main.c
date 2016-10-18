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
// assert.h stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h
#include <intce.h>

/* Place function prototypes here */
void interrupt isr_rtc(void);
void interrupt isr_on(void);

unsigned seconds = 0;
bool exit_loop = false;

/* Main function */
void main(void) {
    char str[10];

    /* Randomize things */
    srand( rtc_Time() );

    /* Clean up the home screen */
    prgm_CleanUp();

    /* Initialize the interrupt handlers */
    int_Initialize();

    /* Set the isr_on routine to run when the [ON] key is pressed */
    int_SetVector(ON_IVECT, isr_on);
    int_SetVector(RTC_IVECT, isr_rtc);
    int_EnableConfig = INT_ON | INT_RTC;

    /* Configure the RTC */
    rtc_LoadSeconds = rtc_LoadMinutes = rtc_LoadHours = rtc_LoadDays = 0;
    rtc_Control = RTC_ENABLE | RTC_LOAD | RTC_SEC_INT_SOURCE;

    /* Wait for the RTC to load in the new values and then acknowledge all the interrupts */
    while( rtc_IsBusy() );
    rtc_IntAcknowledge = RTC_INT_MASK;

    /* Enable interrupts */
    int_Enable();

    while(!exit_loop);

    /* Reset interrupts and exit */
    int_Reset();
    prgm_CleanUp();
}

void interrupt isr_rtc(void) {
    /* Get the status of the RTC interrupt register */
    uint8_t status = rtc_IntStatus;

    /* If a second passed, increment a counter */
    if(status & RTC_SEC_INT) {
        seconds++;
        memset_fast((uint8_t*)0xD40000, randInt(0,255), 320*240*2);
    }

    /* Acknowledge all outstanding interrupts */
    rtc_IntAcknowledge = status;
}

/* This interrupt is triggered when the [ON] key is pressed */
void interrupt isr_on(void) {
    exit_loop = true;
}
