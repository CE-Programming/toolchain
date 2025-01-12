#include <fenv.h>
#include <math.h>
#include <stdint.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

#define Float32_pos_subnorm_min UINT32_C(0x00000001)
#define Float32_neg_subnorm_min UINT32_C(0x80000001)

float nextafterf(float x, float y) {
    F32_pun arg_x, arg_y;
    arg_x.flt = x;
    arg_y.flt = y;

    if (isnan(y)) {
        return y;
    }
    if (isnan(x)) {
        return x;
    }
    if (arg_x.bin == arg_y.bin) {
        return y;
    }

    if (iszero(x)) {
        if (iszero(y)) {
            // special case where `+0.0 --> -0.0` and `-0.0 --> +0.0`
            return y;
        }
        feraiseexcept(FE_INEXACT | FE_UNDERFLOW);
        F32_pun ret;
        ret.bin = signbit(y) ? Float32_neg_subnorm_min : Float32_pos_subnorm_min;
        return ret.flt;
    }
    if (isless(x, y) != signbit(x)) {
        // Towards positive/negative infinity
        arg_x.bin++;
    } else {
        // Towards negative/positive zero
        arg_x.bin--;
    }
    if (isnormal(arg_x.flt)) {
        return arg_x.flt;
    }
    if (isinf(arg_x.flt)) {
        // overflow to infinity
        feraiseexcept(FE_INEXACT | FE_OVERFLOW);
    } else {
        // result is subnormal or zero
        feraiseexcept(FE_INEXACT | FE_UNDERFLOW);
    }
    return arg_x.flt;
}

double nextafter(double, double) __attribute__((alias("nextafterf")));



typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_pos_subnorm_min UINT64_C(0x0000000000000001)
#define Float64_neg_subnorm_min UINT64_C(0x8000000000000001)

long double nextafterl(long double x, long double y) {
    F64_pun arg_x, arg_y;
    arg_x.flt = x;
    arg_y.flt = y;

    if (isnan(y)) {
        return y;
    }
    if (isnan(x)) {
        return x;
    }
    if (arg_x.bin == arg_y.bin) {
        return y;
    }

    if (iszero(x)) {
        if (iszero(y)) {
            // special case where `+0.0 --> -0.0` and `-0.0 --> +0.0`
            return y;
        }
        feraiseexcept(FE_INEXACT | FE_UNDERFLOW);
        F64_pun ret;
        ret.bin = signbit(y) ? Float64_neg_subnorm_min : Float64_pos_subnorm_min;
        return ret.flt;
    }
    if (isless(x, y) != signbit(x)) {
        // Towards positive/negative infinity
        arg_x.bin++;
    } else {
        // Towards negative/positive zero
        arg_x.bin--;
    }
    if (isnormal(arg_x.flt)) {
        return arg_x.flt;
    }
    if (isinf(arg_x.flt)) {
        // overflow to infinity
        feraiseexcept(FE_INEXACT | FE_OVERFLOW);
    } else {
        // result is subnormal or zero
        feraiseexcept(FE_INEXACT | FE_UNDERFLOW);
    }
    return arg_x.flt;
}

long double nexttowardl(long double, long double) __attribute__((alias("nextafterl")));
