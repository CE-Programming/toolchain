#include <math.h>

float erfcf(float x)
{
    static const float p = 0.47047f, a1 = 0.3480242f, a2 = -0.0958798f, a3 = 0.7478556f;
    const float t = 1.0f / (1.0f + p * fabsf(x));
    return copysignf(t * (a1 + t * (a2 + t * a3)) * expf(-x * x), x);
}

double erfc(double) __attribute__((alias("erfcf")));
