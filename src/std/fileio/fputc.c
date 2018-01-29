#include <stdio.h>
#include <fileioc.h>

int fputc(int c, FILE *stream) {
    return ti_PutC((char)c, stream->slot);
}
