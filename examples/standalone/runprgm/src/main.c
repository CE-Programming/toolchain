#include <tice.h>
#include <stdlib.h>
#include <stdio.h>

void run_prgm(const char *msg, size_t msg_size, os_runprgm_callback_t callback)
{
    int ret;

    /* attempt to run the program PRGM */
    ret = os_RunPrgm("\x05PRGM", (void*)msg, msg_size, callback);
    switch (ret)
    {
        case -1:
            os_PutStrFull("PRGM not found.");
            break;

        case -2:
            os_PutStrFull("Not enough mem.");
            break;

        default:
            break;
    }

    while (!os_GetCSC());
}

int prgm_ret(void *data, int retval)
{
    /* this should print "hello world" because the string context was saved */
    printf("%s\n", (char*)data);
    printf("retval: %d", retval);

    while (!os_GetCSC());

    /* run the program PRGM again, but don't use a callback this time */
    run_prgm(NULL, 0, NULL);

    return 0;
}

int main(void)
{
    static const char string[] = "hello world";

    os_ClrHome();

    run_prgm(string, sizeof string, prgm_ret);

    return 0;
}
