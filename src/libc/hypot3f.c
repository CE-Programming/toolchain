#include <math.h>
#include <stdint.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

float __hypot3f(float arg_x, float arg_y, float arg_z) {
    F32_pun x, y, z;
    x.flt = fabsf(arg_x);
    y.flt = fabsf(arg_y);
    z.flt = fabsf(arg_z);
    if (y.bin < z.bin) {
        float temp = y.flt;
        y.flt = z.flt;
        z.flt = temp;
    }
    if (x.bin < y.bin) {
        float temp = x.flt;
        x.flt = y.flt;
        y.flt = temp;
    }
    // x >= y && x >= z, or x is NaN
    if (isfinite(x.flt)) {
        int expon;
        // scale the arguments to prevent overflow/underflow
        x.flt = frexpf(x.flt, &expon);
        y.flt = ldexpf(y.flt, -expon);
        z.flt = ldexpf(z.flt, -expon);
        // evaluating in this order ensures consistency when arguments are swapped
        float ret = sqrtf(x.flt * x.flt + (y.flt * y.flt + z.flt * z.flt));
        return ldexpf(ret, expon);
    }
    if (isinf(y.flt) || isinf(z.flt)) {
        // return infinity, even if the other argument is NaN
        return HUGE_VALF;
    }
    // x is infinity/NaN
    return x.flt;
}

double __hypot3(double, double, double) __attribute__((alias("__hypot3f")));
