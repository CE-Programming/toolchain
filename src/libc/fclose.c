#include "__fileioc_stdio.h"

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

    int status = ti_Close(slot);
    return (status == 0) ? EOF : 0;
}
