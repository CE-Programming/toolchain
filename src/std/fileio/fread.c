#include <stdio.h>
#include <fileioc.h>

size_t fread(void *ptr, size_t size, size_t count, FILE *stream) {
    return ti_Read(ptr, size, count, stream->slot);
}
