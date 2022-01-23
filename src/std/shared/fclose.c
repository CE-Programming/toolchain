#include <stdio.h>
#include <fileioc.h>

extern FILE _file_streams[FOPEN_MAX];

int __attribute__((weak)) fclose(FILE *stream)
{
    ti_var_t slot;

    if (stream == NULL ||
        stream == stdin ||
        stream == stdout ||
        stream == stderr)
    {
        return EOF;
    }

    slot = stream->slot;

    _file_streams[slot - 1].slot = 0;

    return ti_Close(slot);
}
