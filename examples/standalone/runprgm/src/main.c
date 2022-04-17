#include <ti/vars.h>
#include <ti/getcsc.h>
#include <stdlib.h>
#include <stdio.h>

int prgm2_ret(void *data, int retval)
{
    printf("executed prgm 2.\n");
    printf("retval: %d", retval);
    (void)data;

    while (!os_GetCSC());

    return 0;
}

int prgm1_ret(void *data, int retval)
{
    int ret;

    printf("executed prgm 1.\n");
    printf("msg: %s\n", (char*)data);
    printf("retval: %d", retval);

    while (!os_GetCSC());

    ret = os_RunPrgm("PRGM2", NULL, 0, prgm2_ret);
    printf("Error running prgm 2: %d\n", ret);

    return 0;
}

int main(void)
{
    static const char msg[] = "hello";
    int ret;

    ret = os_RunPrgm("PRGM1", (void*)msg, sizeof msg, prgm1_ret);
    printf("Error running prgm 1: %d\n", ret);

    return 0;
}
