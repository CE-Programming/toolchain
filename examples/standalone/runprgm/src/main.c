#include <tice.h>
#include <stdlib.h>

int prgm_ret(void *data, int retval)
{
    (void)data;
    (void)retval;
    return 0;
}

int main(void)
{
    const char string[6] = "hello";
    int ret;

    os_ClrHome();

    ret = os_RunPrgm("\x05PRGM", (void*)string, sizeof string, NULL);
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

    os_GetKey();

    return 0;
}
