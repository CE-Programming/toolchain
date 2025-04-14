#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -1  at +0x1.000006p-4   with ideal expf logf (1/16 < |x| < 16)
 * ulp of -5  at +0x1.cb149cp-4   with current expf logf (1/16 < |x| < 16)
 * ulp of -70 at +0x1.e9b19ep-100 with current expf logf (1.0e-30 < |x| < 1.0e+30)
 * ulp of +81 at +0x1.e40000p-142 with current expf logf (entire range)
 */
float cbrtf(float x)
{
    if (x == 0.0f) {
        return x;
    }
    return copysignf(expf(logf(fabsf(x)) / 3.0f), x);
}

double cbrt(double) __attribute__((alias("cbrtf")));
