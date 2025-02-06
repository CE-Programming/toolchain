#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include "../softfloat/include/softfloat.h"

typedef union F64_pun {
    long double flt;
    float64_t soft;
    uint64_t bin;
} F64_pun;

/* flags handled by softfloat */

long double fmodl(long double x, long double y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = y;

    ret.soft = f64_rem(arg_x.soft, &arg_y.soft);
    return ret.flt;
}
