/************************************************************************/
/*                                                                      */
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

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

// frexp - Standard C library routine
// frexp returns the exponent and mantissa of its floating point
// argument.
//
// Arguments:
//   value     - the floating point argument
//   pExponent - pointer to the returned exponent
//
// Returns:
//   - a floating point number between 0.5 and 1.0 (or zero if
//     the input argument is zero)
//
float _frexpf_c(float value, int *pExponent)
{
    Ieee754 floating;
    long    exponentBits = 0;

    floating.value = value;
    if ( value != 0.0 )
    {
        exponentBits   = (floating.bits
                          & ((unsigned long) exponent_mask << exponent_shift))
                       - ((exponent_base - 1L) << exponent_shift);
        floating.bits -= exponentBits;  // adjust exponent
    }
    if ( pExponent != 0 )
    {
        *pExponent = exponentBits >> exponent_shift;
    }
    return floating.value;
}

double _frexp_c(double, int *) __attribute__((alias("_frexpf_c")));



typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_inf_lsh_1          UINT64_C(0xFFE0000000000000)
#define Float64_norm_min_lsh_1     UINT64_C(0x0020000000000000)
#define Float64_frexp_mask         UINT64_C(0x800FFFFFFFFFFFFF)
#define Float64_pos_one            UINT64_C(0x3FF0000000000000)
#define Float64_frexp_subnorm_mask Float64_pos_one
#define Float64_one_half_exp       UINT64_C(0x3FE0000000000000)

#define Float64_mantissa_bits       52
#define Float64_exp_bias            1023
#define Float64_ilogb_subnorm_max  -1023

#define Float64_exponent_bits  11
#define Float64_sign_bits      1

long double frexpl(long double x, int *expon) {
    F64_pun val;
    val.flt = x;
    // clears the signbit
    val.bin <<= 1;
    /* iszero(x) */
    if (val.bin == 0) {
        // return unmodified
        *expon = 0;
        return x;
    }
    /* isinf(x) || isnan(x) */
    if (val.bin >= Float64_inf_lsh_1) {
        // Unspecified return value for inf and NaN
        *expon = FP_ILOGBNAN;
        return x;
    }
    /* isnormal(x) */
    if (val.bin >= Float64_norm_min_lsh_1) {
        // shift an additional bit to account for the signbit clear shift
        int x_exp = (int)(val.bin >> (Float64_mantissa_bits + 1));
        // frexp is ilogb(x) + 1
        x_exp -= (Float64_exp_bias - 1);
        *expon = x_exp;
        F64_pun ret;
        ret.flt = x;
         // Clear the exponent bits
        ret.bin &= Float64_frexp_mask;
        // Copy the exponent of 0.5 to normalize the value to [0.5, 1.0)
        ret.bin |= Float64_one_half_exp;
        return ret.flt;
    }
    /* issubnormal(x) */
    // val.bin was already shifted by one, so subtract one from the clz_offset
    const int clz_offset = Float64_exponent_bits + Float64_sign_bits - 1;
    int clz_result = __builtin_clzll(val.bin);
    // frexp is ilogb(x) + 1
    *expon = (Float64_ilogb_subnorm_max + clz_offset + 1) - clz_result;
    // Shift everything such that the MSB of the mantissa is in the LSB of the exponent
    val.bin <<= clz_result - clz_offset;
    #if 0
        // Clear the exponent bits
        val.bin &= Float64_frexp_mask;
        // Copy the exponent of 0.5 to normalize the value to [0.5, 1.0)
        val.bin |= Float64_one_half_exp;
    #else
        /**
         * At this point, the exponent bits are exactly equal to `0x001`, this
         * allows us to set the exponent of 0.5 with an XOR. The XOR value is
         * `0.5_exponent ^ 0x001` which is also the exponent value for 1.0
         */
        val.bin ^= Float64_frexp_subnorm_mask;
    #endif
    return copysignl(val.flt, x);
}
