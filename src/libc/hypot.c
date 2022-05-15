#include <math.h>

float hypotf(float x, float y)
{
    return sqrtf(x * x + y * y); // FIXME: accuracy
}

double hypot(double, double) __attribute__((alias("hypotf")));
