#include <math.h>
#include <stdint.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

float hypotf(float arg_x, float arg_y) {
    F32_pun x, y;
    x.flt = fabsf(arg_x);
    y.flt = fabsf(arg_y);
    if (x.bin < y.bin) {
        float temp = x.flt;
        x.flt = y.flt;
        y.flt = temp;
    }
    // x >= y, or x is NaN
    if (isfinite(x.flt)) {
        int expon;
        // scale the arguments to prevent overflow/underflow
        x.flt = frexpf(x.flt, &expon);
        y.flt = ldexpf(y.flt, -expon);
        float ret = sqrtf(x.flt * x.flt + y.flt * y.flt);
        return ldexpf(ret, expon);
    }
    if (isinf(y.flt)) {
        // return infinity, even if the other argument is NaN
        return y.flt;
    }
    // x is infinity/NaN
    return x.flt;
}

double hypot(double, double) __attribute__((alias("hypotf")));
