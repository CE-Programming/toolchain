#include <tice.h>
#include <stdio.h>

#define TIMER_FREQ      32768 /* Frequency of timer in Hz */
#define ONE_SECOND      (TIMER_FREQ / 1)
#define HALF_SECOND     (TIMER_FREQ / 2)
#define QUARTER_SECOND  (TIMER_FREQ / 4)

int main(void)
{
    unsigned count = 0;
    char str[10];

    /* Clear the homescreen */
    os_ClrHome();

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

    do
    {
        /* If the timer is reloaded, we reached 0 */
        if (timer_ChkInterrupt(1, TIMER_RELOADED))
        {
            /* Increment number of counts */
            count++;

            /* Print the number of counts */
            sprintf(str, "%u", count);
            os_SetCursorPos(0, 0);
            os_PutStrFull(str);

            /* Acknowledge the reload */
            timer_AckInterrupt(1, TIMER_RELOADED);
        }
    } while (!os_GetCSC());

    return 0;
}
