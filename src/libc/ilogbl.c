#include <errno.h>
#include <fenv.h>
#include <float.h>
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

#define Float64_ilogb_subnorm_max -1023
#define Float64_exp_bias          1023
#define Float64_mantissa_bits     52
#define Float64_inf_lsh_1         UINT64_C(0xFFE0000000000000)
#define Float64_norm_min_lsh_1    UINT64_C(0x0020000000000000)

#define Float64_exponent_bits  11
#define Float64_sign_bits      1

#define uint48_bits 48

/**
 * @note x is assumed to be positive
 */
int _ilogbl_c(long double x) {
    F64_pun val;
    val.flt = x;
    uint8_t fp_class = (uint8_t)fpclassify(val.flt);
    switch(fp_class) {
        case FP_ZERO: {
            errno = EDOM;
            feraiseexcept(FE_INVALID);
            return FP_ILOGB0;
        }
        case FP_INFINITE:
        case FP_NAN: {
            errno = EDOM;
            feraiseexcept(FE_INVALID);
            // Assumes FP_ILOGBNAN == INT_MAX
            return FP_ILOGBNAN;
        }
        case FP_NORMAL: {
            int x_exp = (int)(val.reg.BC >> (Float64_mantissa_bits - uint48_bits));
            x_exp -= Float64_exp_bias;
            return x_exp;
        }
        case FP_SUBNORMAL: {
            const int clz_offset = Float64_exponent_bits + Float64_sign_bits;
            return (Float64_ilogb_subnorm_max + clz_offset) - __builtin_clzll(val.bin);
        }
        default:
            __builtin_unreachable();
    }
}
