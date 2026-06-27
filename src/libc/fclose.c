#include "__fileioc_stdio.h"

#include <stdint.h>

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

    int status = ti_Close(slot);
    if (status == 0)
    {
        // failed to close file
        return EOF;
    }
    uint8_t index = slot - 1;
    _file_streams[index].slot = 0;
    return 0;
}
