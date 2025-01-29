#include <math.h>
#include <stdint.h>

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

/**
 * @note x is assumed to be positive
 */
long double _frexpl_c(long double x, int *expon) {
    F64_pun val;
    val.flt = x;
    /* iszero(x) */
    if (val.bin == 0) {
        // return unmodified
        *expon = 0;
        return x;
    }
    /* isinf(x) || isnan(x) */
    if (!isfinite(x)) {
        // Unspecified exponent value for inf and NaN
        *expon = FP_ILOGBNAN;
        return x;
    }
    /* isnormal(x) */
    if (isnormal(val.flt)) {
        int x_exp = (int)(val.bin >> (Float64_mantissa_bits));
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
    const int clz_offset = Float64_exponent_bits + Float64_sign_bits;
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
    return val.flt;
}
