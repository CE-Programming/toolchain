#include <tice.h>
#include <stdio.h>

#define ONE_SECOND      (32768/1)
#define HALF_SECOND     (32768/2)
#define QUARTER_SECOND  (32768/4)

void reset_counter(void);

int main(void)
{
    unsigned int count = 0;
    char str[10];

    /* Set the match value to trigger the interrupt in the timer */
    timer_1_MatchValue_1 = ONE_SECOND;

    /* Clear the homescreen */
    os_ClrHome();

    /* Reset the counter */
    reset_counter();

    do
    {
        /* Poll until we reach the match value */
        if (timer_IntStatus & TIMER1_MATCH1)
        {
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

    return 0;
}

void reset_counter(void)
{
    /* Disable the timer so it doesn't run when setting the configuration */
    timer_Control = TIMER1_DISABLE;

    /* By using the 32768 kHz clock, we can count for a */
    /* precise interval of time */
    timer_1_ReloadValue = timer_1_Counter = timer_1_MatchValue_1;

    /* Enable the timer */
    /* Set the timer to use the 32768 kHz clock */
    /* Enable an interrupt once the timer reaches 0 */
    /* Set the timer to count down */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_0INT | TIMER1_DOWN;
}
