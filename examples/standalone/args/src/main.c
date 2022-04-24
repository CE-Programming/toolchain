#include <ti/screen.h>
#include <ti/getcsc.h>

int main(int argc, char *argv[])
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Print each argument on a new line */
    for (int i = 0; i < argc; i++)
    {
        os_PutStrFull(argv[i]);
        os_NewLine();
    }

    /* Wait for a key */
    while (!os_GetCSC());

    /* Return 0 for success */
    return 0;
}
