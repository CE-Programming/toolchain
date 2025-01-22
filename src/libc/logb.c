#include <fenv.h>
#include <math.h>

float logbf(float x) {
    if (isfinite(x)) {
        if (iszero(x)) {
            feraiseexcept(FE_DIVBYZERO);
            return -HUGE_VALF;
        }
        return (float)ilogbf(x);
    }
    // infinity and NaN
    return fabsf(x);
}

double logb(double) __attribute__((alias("logbf")));

long double logbl(long double x) {
    if (isfinite(x)) {
        if (iszero(x)) {
            feraiseexcept(FE_DIVBYZERO);
            return -HUGE_VALL;
        }
        return (long double)ilogbl(x);
    }
    // infinity and NaN
    return fabsl(x);
}
