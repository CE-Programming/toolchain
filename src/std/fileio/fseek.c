#include <stdio.h>
#include <fileioc.h>

int fseek(FILE *stream, long int offset, int origin) {
    return ti_Seek((int)offset, origin, stream->slot);
}
