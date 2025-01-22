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

#define Float64_nan_mask UINT64_C(0x0007FFFFFFFFFFFF)
#define Float64_pos_nan  UINT64_C(0x7FF8000000000000)

long double nanl(const char *tag)
{
    return (union { uint64_t u; long double f; }) {
        .u = (strtoll(tag, NULL, 0) & Float64_nan_mask) | Float64_pos_nan,
    }.f;
}
