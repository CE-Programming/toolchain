#include "__fileioc_stdio.h"

#include <stdint.h>

void __attribute__((weak)) clearerr(FILE *stream)
{
    if (stream == NULL ||
        stream == stdin ||
        stream == stdout ||
        stream == stderr)
    {
        return;
    }
    uint8_t index = stream->slot - 1;
    _file_streams[index].eof = 0;
    _file_streams[index].err = 0;
}
