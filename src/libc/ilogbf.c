#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>

int ilogbf(float x)
{
    if (!(x != 0.f)) {
        errno = EDOM;
        feraiseexcept(FE_INVALID);
        return isnan(x) ? FP_ILOGBNAN : FP_ILOGB0;
    }
    const union { float f; uint32_t u; struct { uint32_t mantissa: FLT_MANT_DIG - 1, exponent: 8, sign: 1; }; } parts = { .f = x };
    const uint8_t bias = (1 << 7) - 1;
    const int exponent = parts.exponent - bias;
    const uint24_t mantissa = parts.mantissa;
    if (exponent == FLT_MAX_EXP) {
        errno = EDOM;
        feraiseexcept(FE_INVALID);
        return mantissa ? FP_ILOGBNAN : INT_MAX;
    }
    if (exponent > FLT_MIN_EXP - 2) return exponent;
    if (mantissa) return FLT_MIN_EXP - __builtin_clz(mantissa) - 1;
    errno = EDOM;
    feraiseexcept(FE_INVALID);
    return FP_ILOGB0;
}

int ilogb(double) __attribute__((alias("ilogbf")));
