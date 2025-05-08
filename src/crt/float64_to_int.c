#include <stdbool.h>
#include <stdint.h>
#include <math.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
    struct {
        uint24_t UHL;
        uint24_t UDE;
        uint16_t BC;
    } reg;
} F64_pun;

#define Float64_pos_one       UINT64_C(0x3FF0000000000000)

#define Float64_bias         1023
#define Float64_mant_bits    52
#define Float64_u64_max_exp  64
#define Float64_u32_max_exp  32
#define Float64_i64_max_exp  63
#define Float64_i32_max_exp  31
#define Float64_exp_BC_shift 4

#if 0
/**
 * This routine can be used for specifically _dtoul and _dtoull
 */
uint64_t _dtoull_c(long double x) {
    F64_pun val;
    val.flt = x;
    // if trunc(x) is zero or x is negative
    if ((int64_t)val.bin < (int64_t)Float64_pos_one) {
        #if 0
            if (iszero(x)) {
                return 0;
            }
            return UINT32_MAX;
        #else
            /* undefined behaviour for negative values of x */
            return 0;
        #endif
    }
    unsigned expon = val.reg.BC;
    // exponent is stored in bits [4, 14], so we shift it to be bits [0, 10].
    expon >>= 4;
    // doesn't underflow since 1.0 - Float64_bias gives us an exponent of zero
    expon -= Float64_bias;
    if (expon >= Float64_u64_max_exp) {
        /* undefined return value for overflow */
        return UINT64_MAX;
    }
    // clears the exponent field without touching the mantissa
    val.reg.BC &= 0x000F;
    // sets the LSB of the exponent since x is normalized
    val.reg.BC |= 0x0010;
    if (expon < Float64_mant_bits) {
        val.bin >>= Float64_mant_bits - expon;
        return val.bin;
    }
    /* expon >= 52 or [52, 63] */
    val.bin <<= expon - 52;
    return val.bin;
}
#endif

typedef struct f64_sign {
    long double flt;
    bool sign;
} f64_sign;

/**
 * @note val must have the signbit cleared
 */
static uint64_t f64_to_unsigned(F64_pun val) {
    // if trunc(x) is zero
    if (val.bin < Float64_pos_one) {
        return 0;
    }
    unsigned expon = val.reg.BC;
    // exponent is stored in bits [4, 14], so we shift it to be bits [0, 10].
    expon >>= Float64_exp_BC_shift;
    // doesn't underflow since 1.0 - Float64_bias gives us an exponent of zero
    expon -= Float64_bias;
    // clears the exponent field without touching the mantissa
    val.reg.BC &= 0x000F;
    // sets the LSB of the exponent since x is normalized
    val.reg.BC |= 0x0010;
    if (expon < Float64_mant_bits) {
        /* expon is [0, 51] */
        val.bin >>= Float64_mant_bits - expon;
        return val.bin;
    }
    /* expon >= 52 or [52, 63] */
    val.bin <<= expon - 52;
    return val.bin;
}



/**
 * @brief the exact same routine is used for (long long)long double and
 * (unsigned long long)long double. If the input long double is out of range,
 * then the conversion is UB anyways.
 */
int64_t _dtoll_c(f64_sign arg) {
    F64_pun val;
    bool x_sign = arg.sign;
    val.flt = arg.flt;
    
    /* overflow || isinf(x) || isnan(x) */
    if (val.reg.BC >= ((Float64_bias + Float64_u64_max_exp) << Float64_exp_BC_shift)) {
        /* undefined return value for underflow/overflow/inf/NaN values of x */
        return 0;
    }

    int64_t ret = (int64_t)f64_to_unsigned(val);
    ret = x_sign ? -ret : ret;
    return ret;
}

/**
 * @brief the exact same routine is used for (long)long double and
 * (unsigned long)long double. If the input long double is out of range,
 * then the conversion is UB anyways.
 */
int32_t _dtol_c(f64_sign arg) {
    F64_pun val;
    bool x_sign = arg.sign;
    val.flt = arg.flt;
    
    /* overflow || isinf(x) || isnan(x) */
    if (val.reg.BC >= ((Float64_bias + Float64_u32_max_exp) << Float64_exp_BC_shift)) {
        /* undefined return value for underflow/overflow/inf/NaN values of x */
        return 0;
    }
    int32_t ret = (int32_t)f64_to_unsigned(val);
    ret = x_sign ? -ret : ret;
    return ret;
}
