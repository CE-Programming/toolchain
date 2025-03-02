#include <math.h>

long long llroundf(float x)
{
    return roundf(x);
}

long long llround(double) __attribute__((alias("llroundf")));
