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

#define Float64_bias 1023
#define Float64_mantissa_bits 52
#define uint48_bits 48

/** @note x is assumed to be positive */
static long double _truncl_c_positive(long double x) {
    F64_pun val;
    val.flt = x;
    int expon = (int)(val.reg.BC >> (Float64_mantissa_bits - uint48_bits));
    expon -= Float64_bias;
    if (expon < 0) {
        // truncate to zero (x is less than one)
        return 0.0L;
    }
    if (expon >= Float64_mantissa_bits) {
        // guaranteed to be an integer, infinty, or NaN
        return val.flt;
    }
    uint64_t mask = UINT64_MAX << (Float64_mantissa_bits - expon);
    val.bin &= mask;
    return val.flt;
}

#ifdef truncl
#undef truncl
#endif

long double truncl(long double x) {
    return copysignl(_truncl_c_positive(fabsl(x)), x);
}

long double _debug_truncl(long double) __attribute__((alias("truncl")));
