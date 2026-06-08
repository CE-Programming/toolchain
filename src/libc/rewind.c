#include "__fileioc_stdio.h"

void __attribute__((weak)) rewind(FILE *stream)
{
    if (stream == NULL || stream == stdin || stream == stdout || stream == stderr)
    {
        return;
    }

    stream->eof = 0;

    (void)fseek(stream, 0L, SEEK_SET);
}
