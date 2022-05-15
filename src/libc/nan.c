#include <math.h>
#include <stdint.h>
#include <stdlib.h>

float nanf(const char *tag)
{
    return (union { uint32_t u; float f; }) {
        .u = (strtol(tag, NULL, 0) & ((UINT32_C(1) << (24 - 2)) - 1)) | ((UINT32_C(1) << (8 + 1)) - 1) << (24 - 2),
    }.f;
}

double nan(const char *) __attribute__((alias("nanf")));
