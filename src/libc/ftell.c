#include <stdio.h>
#include <fileioc.h>
#include <stdint.h>

long int __attribute__((weak)) ftell(FILE *stream)
{
    if (stream == NULL ||
        stream == stdin ||
        stream == stdout ||
        stream == stderr)
    {
        return -1L;
    }

    // ti_Tell shouldn't return a value greater than OS_VAR_MAX_SIZE (65512) unless an error occurs
    uint16_t ret = ti_Tell(stream->slot);
    // Convert a result of UINT16_MAX to -1L, leaving other results the same
    return ((uint16_t)ret + 1) - 1L;
}
