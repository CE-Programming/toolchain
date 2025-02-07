#include <math.h>
#include <stdint.h>

long double modfl(long double x, long double *integral_part) {
    switch (fpclassify(x)) {
        case FP_ZERO:
        case FP_NAN: {
            *integral_part = x;
            return x;
        }
        case FP_INFINITY: {
            *integral_part = x;
            return copysignl(0.0L, x);
        }
        case FP_SUBNORMAL:
        case FP_NORMAL:
    }
    long double trunc_x = truncl(x);
    *integral_part = trunc_x;
    // result will be exact, and should not raise exceptions
    return x - trunc_x;
}
