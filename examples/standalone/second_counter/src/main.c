#include <tice.h>
#include <stdio.h>

#define ONE_SECOND      (32768/1)
#define HALF_SECOND     (32768/2)
#define QUARTER_SECOND  (32768/4)

int main(void)
{
    unsigned count = 0;
    char str[10];

    /* Clear the homescreen */
    os_ClrHome();

    /* Disable the timer so it doesn't run when setting the configuration */
    timer_Control = TIMER1_DISABLE;

    /* By using the 32768 kHz clock, we can count for exactly 1 second */
    /* or for a more precise interval of time */
    timer_1_ReloadValue = timer_1_Counter = ONE_SECOND;

    /* Enable the timer */
    /* Set the timer to use the 32768 kHz clock */
    /* Enable an interrupt once the timer reaches 0 */
    /* Set the timer to count down */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_0INT | TIMER1_DOWN;

    do
    {
        /* If the timer is reloaded, we reached 0 */
        if (timer_IntStatus & TIMER1_RELOADED)
        {
            /* Increment number of counts */
            count++;

            /* Print the number of counts */
            sprintf(str, "%u", count);
            os_SetCursorPos(0, 0);
            os_PutStrFull(str);

            /* Acknowledge the reload */
            timer_IntAcknowledge = TIMER1_RELOADED;
        }
    } while (!os_GetCSC());

    return 0;
}
