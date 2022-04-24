#include <ti/screen.h>
#include <sys/timers.h>
#include <time.h>

int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Wait for 5 seconds */
    os_PutStrFull("Waiting...");
    ticksleep(5 * CLOCKS_PER_SEC);
    os_PutStrFull(" Done!");
    delay(100);

    return 0;
}
