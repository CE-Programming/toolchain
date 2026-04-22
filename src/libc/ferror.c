#include "__fileioc_stdio.h"

int __attribute__((weak)) ferror(FILE *stream)
{
    return stream->err;
}
