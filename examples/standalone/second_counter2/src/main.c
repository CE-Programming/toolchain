#include <tice.h>
#include <stdio.h>

#define TIMER_FREQ      32768 /* Frequency of timer in Hz */
#define ONE_SECOND      (TIMER_FREQ / 1)
#define HALF_SECOND     (TIMER_FREQ / 2)
#define QUARTER_SECOND  (TIMER_FREQ / 4)

static void reset_counter(void)
{
    /* Disable timer 1 so it doesn't run when setting the configuration */
    timer_Disable(1);

    /* Count for 1 second. The counter will be reloaded once it reaches 0 */
    timer_Set(1, ONE_SECOND);
    timer_SetReload(1, ONE_SECOND);

    /* Enable timer 1 */
    /* Set the timer to use the 32768 Hz clock */
    /* Trigger an interrupt once the timer reaches 0 and reloads */
    /* Set the timer to count down */
    timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_DOWN);
}

int main(void)
{
    unsigned int count = 0;
    char str[10];

    /* Clear the homescreen */
    os_ClrHome();

    /* Trigger an interrupt when the timer 1's match 1 count is equal to */
    /* one second. There are 2 match count comparators per timer. */
    timer_SetMatch(1, TIMER_MATCH(1), ONE_SECOND);

    /* Reset the counter */
    reset_counter();

    do
    {
        /* Poll until the match value is detected */
        if (timer_ChkInterrupt(1, TIMER_MATCH(1)))
        {
            /* Print the count */
            sprintf(str, "%u", count++);
            os_SetCursorPos(0, 0);
            os_PutStrFull(str);

            /* Reset the count */
            reset_counter();

            /* Acknowledge the interrupt */
            timer_AckInterrupt(1, TIMER_MATCH(1));
        }

    } while (count < 5);

    return 0;
}
