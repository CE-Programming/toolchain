#include <stdio.h>
#include <fileioc.h>

int fgetc(FILE *stream) {
    return ti_GetC(stream->slot);
}
