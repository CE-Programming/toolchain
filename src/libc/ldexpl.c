#include <errno.h>
#include <math.h>
#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
    struct {
        uint24_t HL;
        uint24_t DE;
        uint16_t BC;
    } reg;
} F64_pun;

#define Float64_norm_min_exp_mask UINT64_C(0x0010000000000000)
#define Float64_frexp_mask        UINT64_C(0x800FFFFFFFFFFFFF)

#define Float64_mantissa_bits  52
#define Float64_exp_bias       1023
#define Float64_max_exp        1023
#define Float64_norm_min_exp  -1022

#define Float64_biased_inf_nan_exp 2047

#define Float64_implicit_mantissa_bits 1

#define Float64_exponent_bits  11
#define Float64_sign_bits      1

#define uint48_bits 48

/** Generates a normalized constant that is 2^expon */
static long double generate_ldexpl_mult(int expon) {
    F64_pun ret;
    ret.bin = (uint64_t)(expon + Float64_exp_bias) << Float64_mantissa_bits;
    return ret.flt;
}

/**
 * @note x is assumed to be positive
 * @remarks Assumes round to nearest ties to even for correct rounding of
 * subnormal values.
 */
static long double _ldexpl_c_positive(long double x, int expon) {
    /* clamps the exponent to avoid signed overflow bugs */
    /* hopefully these can also remove call pe, __setflag from the assembly output */
    if (expon > 4095) {
        expon = 4095;
    }
    if (expon < -4096) {
        expon = -4096;
    }
    F64_pun val;
    val.flt = x;
    /* expon == 0 || iszero(x) */
    if (expon == 0 || val.bin == 0) {
        // return unmodifed
        return val.flt;
    }
    int x_exp = (int)(val.reg.BC >> (Float64_mantissa_bits - uint48_bits));
    /* isnormal(x) || isinf(x) || isnan(x) */
    if (x_exp != 0) {
        /* isinf(x) || isnan(x) */
        if (x_exp == Float64_biased_inf_nan_exp) {
            // return unmodifed
            return val.flt;
        }
        x_exp -= Float64_exp_bias;
        x_exp += expon;
        // overflow
        if (x_exp > Float64_max_exp) {
            errno = ERANGE;
            return HUGE_VALL;
        }
        // normalized
        if (x_exp >= Float64_norm_min_exp) {
            // Clear the exponent bits
            val.reg.BC &= 0x000F;
            x_exp += Float64_exp_bias;
            val.reg.BC |= (x_exp << (Float64_mantissa_bits - uint48_bits));
            return val.flt;
        }
        // make subnormal (with correct rounding)
        int subnorm_exp = x_exp - Float64_norm_min_exp;
        if (subnorm_exp < -(Float64_mantissa_bits + Float64_implicit_mantissa_bits)) {
            // rounds to zero (round to nearest ties to even)
            errno = ERANGE;
            return 0.0L;
        }
        // Clear the exponent bits
        val.bin &= Float64_frexp_mask;
        // Copy the exponent of the minimum normalized value
        val.bin |= Float64_norm_min_exp_mask;
        // precision may be lost
        val.flt *= generate_ldexpl_mult(subnorm_exp);
        return val.flt;
    }
    // make normalized (with correct rounding)
    if (expon < -Float64_mantissa_bits) {
        // rounds to zero (round to nearest ties to even)
        errno = ERANGE;
        return 0.0L;
    }

    int clz_result = __builtin_clzll(val.bin);
    int shift_amount = clz_result - (Float64_exponent_bits + Float64_sign_bits) + 1;

    // fallsback to multiplication if the value will stay subnormal
    if (expon - shift_amount < 0) {
        // precision may be lost
        val.flt *= generate_ldexpl_mult(expon);
        return val.flt;
    }

    expon -= shift_amount;
    if (expon >= Float64_biased_inf_nan_exp - 1) {
        // overflow
        errno = ERANGE;
        return HUGE_VALL;
    }
    // Shift everything such that the MSB of the mantissa is in the LSB of the exponent
    val.bin <<= shift_amount;
    // Add the exponent
    val.reg.BC += expon << (Float64_mantissa_bits - uint48_bits);
    return val.flt;
}

long double ldexpl(long double x, int expon) {
    return copysignl(_ldexpl_c_positive(fabsl(x), expon), x);
}

long double scalbnl(long double, int) __attribute__((alias("ldexpl")));
