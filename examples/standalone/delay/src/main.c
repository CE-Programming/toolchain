#include <tice.h>

int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Wait for 5 seconds */
    os_PutStrFull("Waiting for 5000 ms...");
    delay(5000);
    os_SetCursorPos(1, 22);
    os_PutStrFull("Done");
    delay(100);

    return 0;
}
