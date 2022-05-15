#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fseek(FILE *stream, long int offset, int origin)
{
    if (stream == NULL ||
        stream == stdin ||
        stream == stdout ||
        stream == stderr)
    {
        return -1;
    }

    return ti_Seek((int)offset, origin, stream->slot);
}
