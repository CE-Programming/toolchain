#include <ti/screen.h>
#include <sys/timers.h>

int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Wait for 5 seconds */
    os_PutStrFull("Waiting...");
    sleep(5);
    os_PutStrFull(" Done!");
    delay(100);

    return 0;
}
