#include <float.h>
#include <math.h>

float nextafterf(float x, float y)
{
    if (x == y) return y;
    if (x == 0.f) return copysignf(FLT_TRUE_MIN, y);
    return x - nearbyintf(x / y) * y;
}

double nextafter(double, double) __attribute__((alias("nextafterf")));
