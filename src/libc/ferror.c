#include "__fileioc_stdio.h"

int __attribute__((weak)) ferror(FILE *stream)
{
    if (stream == NULL || stream == stdin || stream == stdout || stream == stderr)
    {
        return 0;
    }
    return stream->err;
}
