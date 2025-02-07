#include <float.h>
#include <math.h>
#include <stdint.h>

float truncf(float x)
{
    const union { float f; uint32_t u; struct { uint32_t mantissa: FLT_MANT_DIG - 1, exponent: 8, sign: 1; }; } parts = { .f = x };
    const uint8_t exponent = parts.exponent, bias = (1 << 7) - 1;
    int shift;
    if (exponent < bias)
        shift = 32 - 1;
    else if (exponent < bias + FLT_MANT_DIG - 1)
        shift = bias + (FLT_MANT_DIG - 1) - exponent;
    else
        return parts.f;
    return (union { uint32_t u; float f; }) { .u = parts.u & ~UINT32_C(0) << shift }.f;
}

double trunc(double) __attribute__((alias("truncf")));
