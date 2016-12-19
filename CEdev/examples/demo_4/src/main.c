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
// stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h, debug.h, intce.h

#define ONE_SECOND         32768/1
#define HALF_SECOND        32768/2
#define QUARTER_SECOND     32768/4

/* Function Prototypes */
void reset_counter(void);

/* Put all your code here */
void main(void) {
    unsigned count = 0;
    char str[10];
    
    timer_1_MatchValue_1 = ONE_SECOND;
    
    /* Clean up the home screen */
    prgm_CleanUp();
    
    /* Reset the counter */
    reset_counter();
    
    do {
        /* Count until we reach the match value */
        if(timer_IntStatus & TIMER1_MATCH1) {
            /* Print the count */
            sprintf( str, "%u", count++ );
            os_SetCursorPos( 0, 0 );
            os_PutStrFull( str );
            
            /* Reset the count */
            reset_counter();
            
            /* Acknowledge the interrupt */
            timer_IntStatus = TIMER1_MATCH1;
        }
    } while(!os_GetCSC());
    
    /* Clean up for the return to the OS */
    prgm_CleanUp();
}

void reset_counter(void) {
    /* Disable the timer so it doesn't run when we don't want it to be running */
    timer_Control = TIMER1_DISABLE;
    
    /* By using the 32768 kHz clock, we can count for exactly 1 second here, or a different interval of time */
    timer_1_Counter = 0;
    
    /* Enable the timer, set it to the 32768 kHz clock, enable an interrupt once it reaches 0, and make it count down */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_NOINT | TIMER1_UP;
}