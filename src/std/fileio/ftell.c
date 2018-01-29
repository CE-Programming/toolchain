#include <stdio.h>
#include <fileioc.h>

long int ftell(FILE *stream) {
    return (long int)ti_Tell(stream->slot);
}
