#include <math.h>

/**
 * Algorithm from:
 * https://en.wikipedia.org/wiki/Error_function#Approximation_with_elementary_functions
 */
float erfcf(float x)
{
    static const float
        p = 0.47047f,
        a1 = 0.3480242f,
        a2 = -0.0958798f,
        a3 = 0.7478556f;
    const float t = 1.0f / (1.0f + p * fabsf(x));
    float ret = t * (a1 + t * (a2 + t * a3)) * expf(-x * x);
    if (signbit(x)) {
        ret = 2.0f - ret;
    }
    return ret;
}

double erfc(double) __attribute__((alias("erfcf")));
