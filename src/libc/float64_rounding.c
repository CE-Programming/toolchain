#include <stdint.h>
#include <fenv.h>
#include <errno.h>
#include <math.h>
#include "../softfloat/include/softfloat.h"

typedef union F64_pun {
    long double flt;
    float64_t soft;
    uint64_t bin;
} F64_pun;

long double truncl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_minMag, false);
    return ret.flt;
}

long double floorl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_min, false);
    return ret.flt;
}

long double ceill(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_max, false);
    return ret.flt;
}

long double roundevenl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_near_even, false);
    return ret.flt;
}

long double roundl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_near_maxMag, false);
    return ret.flt;
}

long lroundl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    
    softfloat_exceptionFlags = 0;
    int32_t ret = f64_to_i32(arg_x.soft, softfloat_round_near_maxMag, false);

    if (softfloat_exceptionFlags & softfloat_flag_invalid) {
        feraiseexcept(FE_INVALID);
    }
    return ret;
}

long long llroundl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    
    softfloat_exceptionFlags = 0;
    int64_t ret = f64_to_i64(arg_x.soft, softfloat_round_near_maxMag, false);
    
    if (softfloat_exceptionFlags & softfloat_flag_invalid) {
        feraiseexcept(FE_INVALID);
    }
    return ret;
}

#if ( \
    FE_TONEAREST  == softfloat_round_near_even && \
    FE_TOWARDZERO == softfloat_round_minMag    && \
    FE_DOWNWARD   == softfloat_round_min       && \
    FE_UPWARD     == softfloat_round_max)

// assumes fenv.h macros match softfloat_roundingModes
#define GET_FENV_SOFTFLOAT_ROUNDING() (fegetround())

#else
    static uint_fast8_t GET_FENV_SOFTFLOAT_ROUNDING(void) {
        switch(fegetround()) {
            default:
            case FE_TONEAREST : return softfloat_round_near_even;
            case FE_TOWARDZERO: return softfloat_round_minMag   ;
            case FE_DOWNWARD  : return softfloat_round_min      ;
            case FE_UPWARD    : return softfloat_round_max      ;
        }
    }
#endif

long double nearbyintl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, GET_FENV_SOFTFLOAT_ROUNDING(), false);
    return ret.flt;
}

long double rintl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    
    softfloat_exceptionFlags = 0;
    ret.soft = f64_roundToInt(arg_x.soft, GET_FENV_SOFTFLOAT_ROUNDING(), true);
    
    if (softfloat_exceptionFlags & softfloat_flag_inexact) {
        feraiseexcept(FE_INEXACT);
    }
    return ret.flt;
}

long lrintl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;

    softfloat_exceptionFlags = 0;
    int32_t ret = f64_to_i32(arg_x.soft, softfloat_round_near_maxMag, true);

    if (softfloat_exceptionFlags & softfloat_flag_inexact) {
        feraiseexcept(FE_INEXACT);
    } else if (softfloat_exceptionFlags & softfloat_flag_invalid) {
        feraiseexcept(FE_INVALID);
    }
    return ret;
}

long long llrintl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;

    softfloat_exceptionFlags = 0;
    int64_t ret = f64_to_i64(arg_x.soft, softfloat_round_near_maxMag, true);

    if (softfloat_exceptionFlags & softfloat_flag_inexact) {
        feraiseexcept(FE_INEXACT);
    } else if (softfloat_exceptionFlags & softfloat_flag_invalid) {
        feraiseexcept(FE_INVALID);
    }
    return ret;
}
