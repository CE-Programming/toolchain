#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/real.h>
#include <sys/timers.h>
#include <time.h>

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
    float timer_seconds = 5.0f;
    float difference;

    /* Clear the homescreen */
    os_ClrHome();

    /* Display an initial timer starting point */
    PrintTime(timer_seconds);

    /* Wait for a key press */
    while (!os_GetCSC());

    /* Record the start time */
    clock_t start = clock();

    /* Continue running until a key is pressed */
    do
    {
        /* Calculate and print the elapsed time */
        clock_t now = clock();
        float elapsed = (float)(now - start) / CLOCKS_PER_SEC;
        /* Calculate the difference between start and end */
        difference = timer_seconds - elapsed;
        PrintTime(difference);
    } while (difference > 0);

    /* Wait for a key */
    while (!os_GetCSC());

    return 0;
}
