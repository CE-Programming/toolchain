#include <math.h>

float log2f(float x)
{
    // this can be made much more accurately using frexp and ldexp
    return logf(x) * (float)(M_LOG2E);
}

double log2(double) __attribute__((alias("log2f")));
