#include <limits.h>
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

#define Float64_frexp_mask         UINT64_C(0x800FFFFFFFFFFFFF)
#define Float64_one_half_exp       UINT64_C(0x3FE0000000000000)

#define Float64_mantissa_bits       52
#define Float64_exp_bias            1023
#define Float64_ilogb_subnorm_max  -1023
#define Float64_biased_inf_nan_exp  2047

#define Float64_exponent_bits  11
#define Float64_sign_bits      1

#define uint48_bits 48

/**
 * @note x is assumed to be positive
 */
static long double _frexpl_c_positive(long double x, int *expon) {
    F64_pun val;
    val.flt = x;
    int x_exp = (int)(val.reg.BC >> (Float64_mantissa_bits - uint48_bits));
    /* isnormal(x) || isinf(x) || isnan(x) */
    if (x_exp != 0) {
        /* isinf(x) || isnan(x) */
        if (x_exp == Float64_biased_inf_nan_exp) {
            // Unspecified exponent value for inf and NaN
            *expon = INT_MAX;
            return val.flt;
        }
        /* isnormal(x) */
        x_exp -= Float64_exp_bias;
        // frexp is ilogb(x) + 1
        x_exp++;
        *expon = x_exp;
        // Clear the exponent bits
        val.reg.BC &= 0x000F;
        // Copy the exponent of 0.5 to normalize the value to [0.5, 1.0)
        val.reg.BC |= 0x3FE0;
        return val.flt;
    }
    /* iszero(x) */
    if (val.bin == 0) {
        // return unmodified
        *expon = 0;
        return val.flt;
    }
    /* issubnormal(x) */
    const int clz_offset = Float64_exponent_bits + Float64_sign_bits;
    int clz_result = __builtin_clzll(val.bin);
    // frexp is ilogb(x) + 1
    *expon = (Float64_ilogb_subnorm_max + clz_offset + 1) - clz_result;
    // Shift everything such that the MSB of the mantissa is in the LSB of the exponent
    val.bin <<= clz_result - clz_offset + 1;
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
        val.reg.BC ^= 0x3FF0;
    #endif
    return val.flt;
}

long double frexpl(long double x, int *expon) {
    return copysignl(_frexpl_c_positive(fabsl(x), expon), x);
}
