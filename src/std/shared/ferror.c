#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) ferror(FILE *stream)
{
    return stream->err;
}
