#include "__fileioc_stdio.h"

int __attribute__((weak)) feof(FILE *stream)
{
    return stream->eof;
}
