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



typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_ilogb_subnorm_max -1023
#define Float64_exp_bias          1023
#define Float64_mantissa_bits     52
#define Float64_inf_lsh_1         UINT64_C(0xFFE0000000000000)
#define Float64_norm_min_lsh_1    UINT64_C(0x0020000000000000)

#define Float64_exponent_bits  11
#define Float64_sign_bits      1

int ilogbl(long double x) {
    F64_pun val;
    val.flt = x;
    // clears the signbit
    val.bin <<= 1;
    /* iszero(x) */
    if (val.bin == 0) {
        errno = EDOM;
        feraiseexcept(FE_INVALID);
        return FP_ILOGB0;
    }
    /* isinf(x) || isnan(x) */
    if (val.bin >= Float64_inf_lsh_1) {
        errno = EDOM;
        feraiseexcept(FE_INVALID);
        // Assumes FP_ILOGBNAN == INT_MAX
        return FP_ILOGBNAN;
    }
    /* isnormal(x) */
    if (val.bin >= Float64_norm_min_lsh_1) {
        // shift an additional bit to account for the signbit clear shift
        int x_exp = (int)(val.bin >> (Float64_mantissa_bits + 1));
        x_exp -= Float64_exp_bias;
        return x_exp;
    }
    /* issubnormal(x) */
    // val.bin was already shifted by one, so subtract one from the clz_offset
    const int clz_offset = Float64_exponent_bits + Float64_sign_bits - 1;
    return (Float64_ilogb_subnorm_max + clz_offset) - __builtin_clzll(val.bin);
}
