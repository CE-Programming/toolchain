#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONE_SECOND         32768/1
#define HALF_SECOND        32768/2
#define QUARTER_SECOND     32768/4

/* Put all your code here */
void main(void) {
    unsigned seconds = 0;
    char str[10];

    /* Clear the homescreen */
    os_ClrHome();

    /* Disable the timer so it doesn't run when we don't want it to be running */
    timer_Control = TIMER1_DISABLE;

    /* By using the 32768 kHz clock, we can count for exactly 1 second here, or a different interval of time */
    timer_1_ReloadValue = timer_1_Counter = ONE_SECOND;

    /* Enable the timer, set it to the 32768 kHz clock, enable an interrupt once it reaches 0, and make it count down */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_0INT | TIMER1_DOWN;

    do {
        /* If the timer is reloaded, we reached 0 */
        if (timer_IntStatus & TIMER1_RELOADED) {
            /* Print a string */
            sprintf(str, "%u", seconds++);
            os_SetCursorPos(0, 0);
            os_PutStrFull(str);

            /* Acknowledge the reload */
            timer_IntAcknowledge = TIMER1_RELOADED;
        }
    } while (!os_GetCSC());
}
