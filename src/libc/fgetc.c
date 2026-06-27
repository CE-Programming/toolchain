#include "__fileioc_stdio.h"

int __attribute__((weak)) fgetc(FILE *stream)
{
    if (stream == NULL || stream == stdout || stream == stderr)
    {
        return EOF;
    }
    if (stream == stdin)
    {
        return getchar();
    }

    int c = ti_GetC(stream->slot);

    if (c == EOF)
    {
        stream->eof = 1;
    }

    return c;
}

int getc(FILE *stream) __attribute__((weak, alias("fgetc")));
