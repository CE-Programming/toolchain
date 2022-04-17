#include <math.h>

float acoshf(float x)
{
    return logf(x + sqrtf(x * x - 1));
}

double acosh(double) __attribute__((alias("acoshf")));

long double acoshl(long double x)
{
    return logl(x + sqrtl(x * x - 1));
}
