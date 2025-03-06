#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of +2  at +0x1.fe2dd0p-9 with ideal log1pf
 * ulp of -9  at +0x1.e1e8d0p-5 with current log1pf and ideal logf
 * ulp of +11 at +0x1.f30abcp-5 with current log1pf and logf
 */
float atanhf(float arg) {
    float x = fabsf(arg);
    x = 0.5f * log1pf((2.0f * x) / (1.0f - x));
    return copysignf(x, arg);
}

double atanh(double) __attribute__((alias("atanhf")));
