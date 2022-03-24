#include <math.h>

float remquof(float x, float y, int *quo)
{
    const float quotient = nearbyintf(x / y);
    *quo = quotient;
    return x - quotient * y; // FIXME: accuracy
}

double remquo(double, double, int *) __attribute__((alias("remquof")));
