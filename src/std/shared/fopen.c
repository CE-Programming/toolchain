#include <stdio.h>
#include <stdbool.h>
#include <fileioc.h>

extern FILE _file_streams[FOPEN_MAX];

static bool inited = false;

FILE* __attribute__((weak)) fopen(const char *__restrict filename, const char *__restrict mode)
{
    ti_var_t slot;

    if (inited == false)
    {
        ti_CloseAll();
        inited = true;
    }

    slot = ti_Open(filename, mode);
    if (slot == 0)
    {
        return NULL;
    }

    _file_streams[(unsigned char)slot].slot = slot;
    _file_streams[(unsigned char)slot].eof = 0;
    _file_streams[(unsigned char)slot].err = 0;

    return &_file_streams[slot];
}
