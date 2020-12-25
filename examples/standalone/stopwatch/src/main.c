#include <tice.h>

/* Print a stopwatch value on the home screen */
static void PrintTime(float elapsed)
{
    /* Float format for printf may be unimplemented, so go through an OS real */
    real_t elapsed_real;

    /* Max stopwatch value is (2^32 - 1) / 32768 = 131072.00, */
    /* so create a buffer with room for 9 characters plus a null terminator */
    char str[10];

    /* If the elapsed time is small enough that the OS would print it using */
    /* scientific notation, force it down to zero before conversion */
    elapsed_real = os_FloatToReal(elapsed <= 0.001f ? 0.0f : elapsed);

    /* Convert the elapsed time real to a string */
    os_RealToStr(str, &elapsed_real, 8, 1, 2);

    /* print the string */
    os_SetCursorPos(0, 0);
    os_PutStrFull(str);
}

int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Display an initial time of zero */
    PrintTime(0.0f);

    /* Disable timer 1 so it doesn't run when setting the configuration */
    timer_Disable(1);

    /* Reset the timer's counter */
    timer_Set(1, 0);

    /* Wait for a key press */
    while (!os_GetCSC());

    /* Enable the timer while setting it to 32768 Hz and making it count up */
    timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_UP);

    /* Continue running until a key is pressed */
    do
    {
        /* Calculate and print the elapsed time */
        /* timer_Get or timer_GetLow may be used in place of timer_GetSafe */
        float elapsed = (float)timer_GetSafe(1, TIMER_UP) / 32768;
        PrintTime(elapsed);
    } while (!os_GetCSC());

    /* Wait for a key */
    while (!os_GetCSC());

    return 0;
}
