#include "__fileioc_stdio.h"

#include <stdint.h>

FILE* __attribute__((weak)) fopen(const char *__restrict filename, const char *__restrict mode)
{
    ti_var_t slot;

    slot = ti_Open(filename, mode);
    if (slot == 0)
    {
        return NULL;
    }

    uint8_t index = slot - 1;
    _file_streams[index].slot = slot;
    _file_streams[index].eof = 0;
    _file_streams[index].err = 0;

    return &_file_streams[index];
}
