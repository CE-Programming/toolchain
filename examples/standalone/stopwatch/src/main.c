#include <tice.h>

void PrintTime(float elapsed);

int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Display an initial time of zero */
    PrintTime(0.0f);

    /* Disable the timer */
    timer_Control = TIMER1_DISABLE;

    /* Reset the timer's counter */
    timer_1_Counter = 0;

    /* Wait for a key press */
    while (!os_GetCSC());

    /* Enable the timer while setting it to 32768 KHz and making it count up */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_UP;

    /* Continue running until a key is pressed */
    do
    {
        /* Calculate and print the elapsed time */
        float elapsed = (float)atomic_load_increasing_32(&timer_1_Counter) / 32768;
        PrintTime(elapsed);
    } while (!os_GetCSC());

    /* Wait for a key */
    while (!os_GetCSC());

    return 0;
}

/* PrintTime a stopwatch value on the home screen */
void PrintTime(float elapsed)
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
