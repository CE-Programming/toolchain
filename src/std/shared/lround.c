#include <math.h>

long lroundf(float x)
{
    return roundf(x);
}

long lround(double) __attribute__((alias("lroundf")));
