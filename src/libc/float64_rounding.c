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

#if 0
/* implemented in truncl.c */
long double truncl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_minMag, false);
    return ret.flt;
}
#endif

#if 0
/* implemented in floorl.c */
long double floorl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_min, false);
    return ret.flt;
}
#endif

#if 0
/* implemented in ceill.c */
long double ceill(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, softfloat_round_max, false);
    return ret.flt;
}
#endif

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

/* flags handled by softfloat */
long lroundl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_i32(arg_x.soft, softfloat_round_near_maxMag, false);
}

/* flags handled by softfloat */
long long llroundl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_i64(arg_x.soft, softfloat_round_near_maxMag, false);
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

/* flags handled by softfloat */
long double rintl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_roundToInt(arg_x.soft, GET_FENV_SOFTFLOAT_ROUNDING(), true);
    return ret.flt;
}

/* flags handled by softfloat */
long lrintl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_i32(arg_x.soft, GET_FENV_SOFTFLOAT_ROUNDING(), true);
}

/* flags handled by softfloat */
long long llrintl(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_i64(arg_x.soft, GET_FENV_SOFTFLOAT_ROUNDING(), true);
}
