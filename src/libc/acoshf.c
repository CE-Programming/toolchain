#include <math.h>

float acoshf(float x)
{
    return logf(x + sqrtf(x * x - 1));
}

double acosh(double) __attribute__((alias("acoshf")));
