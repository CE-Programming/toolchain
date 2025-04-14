#include <stdbool.h>
#include <stdint.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
    struct {
        uint24_t UHL;
        uint8_t E;
    } reg;
} F32_pun;

#define Float32_pos_one      UINT32_C(0x3F800000)
#define Float32_bias         127
#define Float32_mant_bits    23
#define Float32_u64_max_exp  64

// this should be easy to rewrite in assembly
uint64_t _ftoull_c(float x) {
    F32_pun val;
    val.flt = x;
    // if trunc(x) is zero or x is negative
    if ((int32_t)val.bin < (int32_t)Float32_pos_one) {
        /* undefined return value for negative inputs */
        return 0;
    }
    // signbit is zero here
    uint8_t expon = (uint8_t)(val.bin >> 23);
    // doesn't underflow since 1.0 - Float32_bias gives us an exponent of zero
    expon -= Float32_bias;
    if (expon >= Float32_u64_max_exp) {
        /* undefined return value for overflow */
        return 0;
    }
    // sets the LSB of the exponent since x is normalized
    uint24_t mant = val.reg.UHL | 0x800000;
    if (expon < Float32_mant_bits) {
        mant >>= Float32_mant_bits - expon;
        return mant;
    }
    /* expon >= 23 or [23, 63] */
    return (uint64_t)mant << (expon - Float32_mant_bits);
}
