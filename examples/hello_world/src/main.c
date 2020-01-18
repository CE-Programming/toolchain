#include <tice.h>

/* Main function, called first */
int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Print a string */
    os_PutStrFull("Hello, World!");

    /* Waits for a keypress */
    while (!os_GetCSC());

    /* Return 0 for success */
    return 0;
}
