#include <math.h>
#include <stdint.h>
#include "../../softfloat/include/softfloat.h"

typedef union F64_pun {
    long double flt;
    float64_t soft;
    uint64_t bin;
} F64_pun;

long double fmal(long double x, long double y, long double z) {
    F64_pun arg_x, arg_y, arg_z, ret;
    arg_x.flt = x;
    arg_y.flt = y;
    arg_z.flt = z;
    ret.soft = f64_mulAdd(arg_x.soft, arg_y.soft, arg_z.soft);
    return ret.flt;
}

long double sqrtl(long double x) {
    F64_pun arg_x, ret;
    arg_x.flt = x;
    ret.soft = f64_sqrt(arg_x.soft);
    return ret.flt;
}

// _drem
long double fmodl(long double x, long double y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = y;
    ret.soft = f64_rem(arg_x.soft, arg_y.soft);
    return ret.flt;
}

long double modfl(long double x, long double *integral_part) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = 1.0L;
    *integral_part = truncl(x);
    ret.soft = f64_rem(arg_x.soft, arg_y.soft);
    return ret.flt;
}
