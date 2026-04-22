#include "__fileioc_stdio.h"

int __attribute__((weak)) fflush(FILE *stream)
{
    (void)stream;

    return 0;
}
