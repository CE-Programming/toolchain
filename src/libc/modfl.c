#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include "../softfloat/include/softfloat.h"

typedef union F64_pun {
    long double flt;
    float64_t soft;
    uint64_t bin;
} F64_pun;

long double modfl(long double x, long double *integral_part) {
    if (iszero(x)) {
        *integral_part = x;
        return x;
    }
    if (isinf(x)) {
        *integral_part = x;
        return copysignl(0.0L, x);
    }
    F64_pun arg_x, arg_y, ret;
    // modf does not set exceptions
     __fenv_t temp_fe = __fe_cur_env;
    arg_x.flt = x;
    arg_y.flt = 1.0L;
    *integral_part = truncl(x);
    ret.soft = f64_rem(arg_x.soft, &arg_y.soft);
    __fe_cur_env = temp_fe;
    return ret.flt;
}
