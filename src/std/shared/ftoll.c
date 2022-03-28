#include <float.h>
#include <math.h>
#include <stdint.h>

long long _ftoll_c(float x)
{
    const union { float f; uint32_t u; struct { uint32_t mantissa: FLT_MANT_DIG - 1, exponent: 8, sign: 1; }; } parts = { .f = x };
    const uint8_t exponent = parts.exponent, bias = (1 << 7) - 1;
    const uint24_t mantissa = UINT24_C(1) << (FLT_MANT_DIG - 1) | parts.mantissa;
    if (exponent < bias) return 0;
    if (exponent <= bias + FLT_MANT_DIG - 1) {
        const int24_t result = mantissa >> (bias + FLT_MANT_DIG - 1 - exponent);
        return parts.sign ? -result : result;
    }
    const long long result = (long long)mantissa << (exponent - bias);
    return parts.sign ? -result : result;
}
