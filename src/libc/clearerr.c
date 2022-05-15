#include <stdio.h>
#include <fileioc.h>

extern FILE _file_streams[FOPEN_MAX];

void __attribute__((weak)) clearerr(FILE *stream)
{
    if (stream == NULL ||
        stream == stdin ||
        stream == stdout ||
        stream == stderr)
    {
        return;
    }

    _file_streams[stream->slot].eof = 0;
    _file_streams[stream->slot].err = 0;
}
