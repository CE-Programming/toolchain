#include "__fileioc_stdio.h"

void __attribute__((weak)) rewind(FILE *stream)
{
    stream->eof = 0;

    (void)fseek(stream, 0L, SEEK_SET);
}
