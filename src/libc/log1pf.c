#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -8  at +0x1.000008p-3 with ideal logf
 * ulp of -10 at +0x1.0008c8p-3 with current logf
 */
float log1pf(float x) {
    if (fabsf(x) <= 0.125f) {
        // pade(series(ln(1+x),x=0,6,polynom),x,5,3)
        // (-57*x**2-90*x)/(x**3-21*x**2-102*x-90)
        // relative error less than 1e-7
        return
            (x * (57.0f * x + 90.0f)) /
            (((21.0f - x) * x + 102.0f) * x + 90.0f);
    }
    // relative error about 2^-21 if fabs(x) is just above 0.125
    return logf(1.0f + x);
}

double log1p(double) __attribute__((alias("log1pf")));
