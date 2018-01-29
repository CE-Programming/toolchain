#include <stdio.h>
#include <fileioc.h>

size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream) {
    return ti_Write(ptr, size, count, stream->slot);
}
