#if 0

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

#else

#include <errno.h>
#include <math.h>
#include <stdint.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
    struct {
        uint24_t HL;
        uint8_t E;
    } reg;
} F32_pun;

#define Float32_exp_bias            127
#define Float32_ilogb_subnorm_max  -127
#define Float32_max_exp             127
#define Float32_norm_min_exp       -126
#define Float32_biased_inf_nan_exp  255

#define Float32_mantissa_bits  23
#define Float32_exponent_bits  8
#define Float32_sign_bits      1
#define Float32_implicit_mantissa_bits 1

/** Generates a normalized constant that is 2^expon */
static float generate_ldexpf_mult(int expon) {
    F32_pun ret;
    ret.bin = (uint32_t)(expon + Float32_exp_bias) << Float32_mantissa_bits;
    return ret.flt;
}

/**
 * @note x is assumed to be positive
 * @remarks Cases where the result/output is subnormal rely on _fmul handling
 * subnormals correctly.
 */
float _ldexpf_c_positive(float x, int expon) {
    F32_pun val;
    val.flt = x;
    int x_class = fpclassify(val.flt);
    switch(x_class) {
        case FP_INFINITE:
        case FP_NAN:
        case FP_ZERO: {
            // return unmodified
            return val.flt;
        }
        case FP_NORMAL: {
            val.bin <<= 1;
            int x_exp = val.reg.E;
            x_exp -= Float32_exp_bias;
            x_exp += expon;
            // overflow
            if (x_exp > Float32_max_exp) {
                errno = ERANGE;
                return HUGE_VALF;
            }
            // normalized
            if (x_exp >= Float32_norm_min_exp) {
                // Copy the new exponent
                x_exp += Float32_exp_bias;
                val.reg.E = (uint8_t)x_exp;
                val.bin >>= 1;
                return val.flt;
            }
            // make subnormal (with correct rounding)
            int subnorm_exp = x_exp - Float32_norm_min_exp;
            if (subnorm_exp < -(Float32_mantissa_bits + Float32_implicit_mantissa_bits)) {
                // rounds to zero (round to nearest ties to even)
                errno = ERANGE;
                return 0.0f;
            }
            // Copy the exponent of the minimum normalized value
            val.reg.E = 0x01;
            val.bin >>= 1;
            // precision may be lost
            val.flt *= generate_ldexpf_mult(subnorm_exp);
            return val.flt;
        }
        case FP_SUBNORMAL: {
            // make normalized (with correct rounding)
            if (expon < -Float32_mantissa_bits) {
                // rounds to zero (round to nearest ties to even)
                errno = ERANGE;
                return 0.0f;
            }
            
            int clz_result = __builtin_clz(val.reg.HL);
            int shift_amount = clz_result - Float32_implicit_mantissa_bits + 1;

            // fallsback to multiplication if the value will stay subnormal
            if (expon - shift_amount < 0) {
                // precision may be lost
                val.flt *= generate_ldexpf_mult(expon);
                return val.flt;
            }
            
            expon -= shift_amount;
            if (expon >= Float32_biased_inf_nan_exp - 1) {
                // overflow
                errno = ERANGE;
                return HUGE_VALF;
            }
            // Shift everything such that the MSB of the mantissa is in the LSB of the exponent
            val.reg.HL <<= shift_amount;
            // Add the exponent
            #if 1
                if ((expon & 1)) {
                    val.reg.HL += 0x800000;
                    expon++;
                }
                val.reg.E += ((uint8_t)expon >> 1);
                return val.flt;
            #else
                val.bin <<= 1;
                val.reg.E += (uint8_t)expon;
                val.bin >>= 1;
                return val.flt;
            #endif
        }
        default:
            __builtin_unreachable();
    }
}

float _ldexpf_c(float x, int expon) {
    return copysignf(_ldexpf_c_positive(fabsf(x), expon), x);
}

#endif

double _ldexp_c(double, int) __attribute__((alias("_ldexpf_c")));
