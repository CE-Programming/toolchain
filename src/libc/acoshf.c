#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -2  at +0x1.0007e8p+0 with ideal log1pf
 * ulp of +10 at +0x1.01c964p+0 with current log1pf
 */
float acoshf(float x) {
    if (x < 0x1.0p+63f) {
        float t = x - 1.0f;
        return log1pf(t + sqrtf(2.0f * t + t * t));
    }
    return logf(x) + (float)M_LN2;
}

double acosh(double) __attribute__((alias("acoshf")));
