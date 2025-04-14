#include <math.h>

float exp2f(float x)
{
    // this can be made much more accurately using frexp and ldexp
    return expf(x * (float)M_LN2);
}

double exp2(double) __attribute__((alias("exp2f")));
