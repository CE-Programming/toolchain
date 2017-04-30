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

/* Function Prototypes */
void reset_counter(void);

void main(void) {
    unsigned int count = 0;
    char str[10];
    
    timer_1_MatchValue_1 = ONE_SECOND;
    
    /* Clear the homescreen */
    os_ClrHome();

    /* Reset the counter */
    reset_counter();
    
    do {

        /* Poll until we reach the match value */
        if (timer_IntStatus & TIMER1_MATCH1) {
            /* Print the count */
            sprintf(str, "%u", count++);
            os_SetCursorPos(0, 0);
            os_PutStrFull(str);
            
            /* Reset the count */
            reset_counter();
            
            /* Acknowledge the interrupt */
            timer_IntStatus = TIMER1_MATCH1;
        }

    } while (count < 5);
}

void reset_counter(void) {
    /* Disable the timer so it doesn't run when we don't want it to be running */
    timer_Control = TIMER1_DISABLE;
    
    /* By using the 32768 kHz clock, we can count for exactly 1 second here, or a different interval of time */
    timer_1_Counter = 0;
    
    /* Enable the timer, set it to the 32768 kHz clock, enable an interrupt once it reaches 0, and make it count down */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_NOINT | TIMER1_UP;
}

