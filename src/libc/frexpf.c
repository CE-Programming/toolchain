/**
 * @remarks Zilog's implementation of ldexpf is probably smaller since it does
 * not handle subnormals.
 */
#if 1
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

#else

#include <stdint.h>
#include <math.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
    struct {
        uint24_t HL;
        uint8_t E;
    } reg;
} F32_pun;

#define Float32_mantissa_bits       23
#define Float32_exp_bias            127
#define Float32_ilogb_subnorm_max  -127

#define Float32_exponent_bits  8
#define Float32_sign_bits      1
#define Float32_implicit_mantissa_bits 1

float _frexpf_c(float x, int *expon) {
    F32_pun val;
    val.flt = x;
    int x_class = fpclassify(val.flt);
    switch(x_class) {
        case FP_INFINITE:
        case FP_NAN: {
            // Unspecified exponent value for inf and NaN
            *expon = FP_ILOGBNAN;
            return val.flt;
        }
        case FP_ZERO: {
            // return unmodified
            *expon = 0;
            return val.flt;
        }
        case FP_NORMAL: {
            val.bin <<= 1;
            int x_exp = val.reg.E;
            x_exp -= Float32_exp_bias;
            // frexp is ilogb(x) + 1
            x_exp++;
            *expon = x_exp;
            // Copy the exponent of 0.5 to normalize the value to [0.5, 1.0)
            val.reg.E = 0x7E;
            val.bin >>= 1;
            return copysignf(val.flt, x);
        }
        case FP_SUBNORMAL: {
            int clz_result = __builtin_clz(val.reg.HL);
            // frexp is ilogb(x) + 1
            *expon = (Float32_ilogb_subnorm_max + Float32_implicit_mantissa_bits + 1) - clz_result;
            // Shift everything such that the MSB of the mantissa is in the LSB of the exponent
            val.reg.HL <<= clz_result - Float32_implicit_mantissa_bits + 1;
            // Copy the exponent of 0.5 to normalize the value to [0.5, 1.0)
            val.reg.HL += 0x800000; /* reset the LSB of the exponent */
            /**
             * since x is denormal, the exponent field is all zeros apart from
             * the signbit. This allows us to set an exponent of 0.5 via an XOR
             */
            val.reg.E ^= 0x3F;
            return copysignf(val.flt, x);
        }
        default:
            __builtin_unreachable();
    }
}

#endif

double _frexp_c(double, int *) __attribute__((alias("_frexpf_c")));
