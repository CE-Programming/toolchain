#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fflush(FILE *stream)
{
    (void)stream;

    return 0;
}
