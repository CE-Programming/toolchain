#include <math.h>

float exp2f(float x)
{
    return expf(x * (float)M_LOG2E);
}

double exp2(double) __attribute__((alias("exp2f")));
