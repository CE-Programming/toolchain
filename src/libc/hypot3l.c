#include <math.h>
#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

long double __hypot3l(long double arg_x, long double arg_y, long double arg_z) {
    F64_pun x, y, z;
    x.flt = fabsl(arg_x);
    y.flt = fabsl(arg_y);
    z.flt = fabsl(arg_z);
    if (y.bin < z.bin) {
        long double temp = y.flt;
        y.flt = z.flt;
        z.flt = temp;
    }
    if (x.bin < y.bin) {
        long double temp = x.flt;
        x.flt = y.flt;
        y.flt = temp;
    }
    // x >= y && x >= z, or x is NaN
    if (isfinite(x.flt)) {
        int expon;
        // scale the arguments to prevent overflow/underflow
        x.flt = frexpl(x.flt, &expon);
        y.flt = ldexpl(y.flt, -expon);
        z.flt = ldexpl(z.flt, -expon);
        // evaluating in this order ensures consistency when arguments are swapped
        long double ret = sqrtl(x.flt * x.flt + (y.flt * y.flt + z.flt * z.flt));
        return ldexpl(ret, expon);
    }
    if (isinf(y.flt) || isinf(z.flt)) {
        // return infinity, even if the other argument is NaN
        return HUGE_VALL;
    }
    // x is infinity/NaN
    return x.flt;
}
