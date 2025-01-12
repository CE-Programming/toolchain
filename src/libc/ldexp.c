/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                              Zilog, Inc.                             */
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/
#include <errno.h>
#include <math.h>
#include <stdint.h>

typedef union
{
    float             value;
    unsigned long     bits;
} Ieee754;

enum
{   //  The IEEE 754 format is:
    //  SEEEEEEE EMMMMMMM MMMMMMMM MMMMMMMM
    //  (with an implicit mantissa high-order 1-bit.)
    mastissa_shift = 0,
    mastissa_bits  = 23,
    exponent_bits  = 8,
    exponent_shift = mastissa_shift + mastissa_bits,
    sign_shift     = exponent_shift + exponent_bits,
    exponent_mask  = (1 << exponent_bits) -1,  // shifted = 0x7F800000
    exponent_max   = (1 << exponent_bits) -1,
    exponent_base  = 127,
    exponent_min   = 0
};

// ldexp - Standard C library routine
// ldexp returns the argument multiplied by an integral (positive or
// negative) power of two.
//
// Arguments:
//   value - the floating point argument
//   power - the power of two to be used
//
// Returns:
//   - the argument multiplied by an integral power of two
//
float _ldexpf_c(float value, int power)
{
    Ieee754 floating;
    int     exponent;
    int powerplusexponent;

    if ( value == 0.0 || !isfinite(value) ) return value;

    floating.value = value;
    exponent = (floating.bits >> exponent_shift) & exponent_mask;
    powerplusexponent = power + exponent;

    if ( powerplusexponent > exponent_max )
    {
        errno = ERANGE;
        return (floating.bits & (1L << sign_shift)) == 0 ? HUGE_VALF : - HUGE_VALF;
    }
    if ( powerplusexponent <= exponent_min )		// CR 3964
    {
        errno = ERANGE;
        return 0.0;
    }
    floating.bits += (long) power << exponent_shift;  // adjust exponent
    return floating.value;
}

double _ldexp_c(double, int) __attribute__((alias("_ldexpf_c")));

// when FLT_RADIX == 2, scalbn is equivilent to ldexp
float scalbnf(float, int) __attribute__((alias("_ldexpf_c")));
double scalbn(double, int) __attribute__((alias("_ldexpf_c")));



typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_pos_inf           UINT64_C(0x7FF0000000000000)
#define Float64_norm_min_exp_mask UINT64_C(0x0010000000000000)
#define Float64_inf_lsh_1         UINT64_C(0xFFE0000000000000)
#define Float64_norm_min_lsh_1    UINT64_C(0x0020000000000000)
#define Float64_frexp_mask        UINT64_C(0x800FFFFFFFFFFFFF)

#define Float64_huge_val Float64_pos_inf

#define Float64_mantissa_bits  52
#define Float64_exp_bias       1023
#define Float64_max_exp        1023
#define Float64_norm_min_exp  -1022

#define Float64_exponent_bits  11
#define Float64_sign_bits      1

/** Generates a normalized constant that is 2^expon */
static long double generate_ldexpl_mult(int expon) {
    F64_pun ret;
    ret.bin = (uint64_t)(expon + Float64_exp_bias) << Float64_mantissa_bits;
    return ret.flt;
}

/**
 * @remarks Assumes round to nearest ties to even for correct rounding of
 * subnormal values.
 */
long double ldexpl(long double x, int expon) {
    F64_pun val;
    val.flt = x;
    // clears the signbit
    val.bin <<= 1;
    /* expon == 0 || iszero(x) || isinf(x) || isnan(x) */
    if (expon == 0 || val.bin == 0 || val.bin >= Float64_inf_lsh_1) {
        // return unmodifed
        return x;
    }
    /* isnormal(x) */
    if (val.bin >= Float64_norm_min_lsh_1) {
        // shift an additional bit to account for the signbit clear shift
        int x_exp = (int)(val.bin >> (Float64_mantissa_bits + 1));
        x_exp -= Float64_exp_bias;
        x_exp += expon;
        // overflow
        if (x_exp > Float64_max_exp) {
            errno = ERANGE;
            F64_pun ret;
            ret.bin = Float64_huge_val;
            return copysignl(ret.flt, x);
        }
        // normalized
        if (x_exp >= Float64_norm_min_exp) {
            F64_pun ret;
            ret.flt = x;
            // Clear the exponent bits
            ret.bin &= Float64_frexp_mask;
            x_exp += Float64_exp_bias;
            ret.bin |= ((uint64_t)x_exp) << Float64_mantissa_bits;
            return ret.flt;
        }
        // make subnormal (with correct rounding)
        int subnorm_exp = x_exp - Float64_norm_min_exp;
        if (subnorm_exp < -53) {
            // rounds to zero (round to nearest ties to even)
            errno = ERANGE;
            return copysignl(0.0L, x);
        }
        F64_pun ret;
        ret.flt = x;
        // Clear the exponent bits
        ret.bin &= Float64_frexp_mask;
        // Copy the exponent of the minimum normalized value
        ret.bin |= Float64_norm_min_exp_mask;
        // precision may be lost
        ret.flt *= generate_ldexpl_mult(subnorm_exp);
        return ret.flt;
    }
    // make normalized (with correct rounding)
    if (expon < -52) {
        // rounds to zero (round to nearest ties to even)
        errno = ERANGE;
        return copysignl(0.0L, x);
    }
    /**
     * fallsback to multiplication if there is a chance the subnormal value
     * wont't be normalized
     */
    if (expon < Float64_mantissa_bits) {
        // precision may be lost when expon < 0
        x *= generate_ldexpl_mult(expon);
        return x;
    }
    // val.bin was already shifted by one, so subtract one from the clz_offset
    const int clz_offset = Float64_exponent_bits + Float64_sign_bits - 1;
    int clz_result = __builtin_clzll(val.bin);
    expon -= clz_result - clz_offset + 1;
    /**
     * 2045 is the largest power of 2 that you can multiply the smallest
     * normalized number by without overflowing the expoenent field
     * (creating infinity/NaN). Any lower, and floats will be wrongly rounded
     * to infinty.
     */
    if (expon > 2045) {
        // overflow
        errno = ERANGE;
        F64_pun ret;
        ret.bin = Float64_huge_val;
        return copysignl(ret.flt, x);
    }
    // Shift everything such that the MSB of the mantissa is in the LSB of the exponent
    val.bin <<= clz_result - clz_offset;
    // Add the exponent
    val.bin += ((uint64_t)expon) << Float64_mantissa_bits;
    return copysignl(val.flt, x);
}

// when FLT_RADIX == 2, scalbn is equivilent to ldexp
long double scalbnl(long double, int) __attribute__((alias("ldexpl")));
