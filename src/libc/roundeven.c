#include <math.h>

float roundevenf(float x)
{
    float i, f = modff(x, &i);
    if (!isgreaterequal(f, .5f)) return i;
    if (f == .5f) {
        float half = ldexp(i, -1);
        if (truncf(half) == half) return i;
    }
    return signbit(i) ? i - 1 : i + 1;
}

double roundeven(double x) __attribute__((alias("roundevenf")));

long double roundevenl(long double x)
{
    long double i, f = modfl(x, &i);
    if (!isgreaterequal(f, .5f)) return i;
    if (f == .5f) {
        long double half = ldexpl(i, -1);
        if (truncl(half) == half) return i;
    }
    return signbit(i) ? i - 1 : i + 1;
}
