#include <math.h>

/**
 * Algorithm from:
 * https://en.wikipedia.org/wiki/Error_function#Approximation_with_elementary_functions
 *
 * @remarks Minimum ulp:
 * ulp of +16     at +0x1.a13834p-1 with ideal expf (x < 1.0f)
 * ulp of +594482 at +0x1.251634p+3 with current expf (x >= 1.0f)
 */
float erfcf(float x)
{
    static const float
        p = 0.3275911f,
        a1 = 0.254829592f,
        a2 = -0.284496736f,
        a3 = 1.421413741f,
        a4 = -1.453152027f,
        a5 = 1.061405429f;
    const float t = 1.0f / (1.0f + p * fabsf(x));
    float ret = t * (a1 + t * (a2 + t * (a3 + t * (a4 + t * a5)))) * expf(-x * x);
    if (signbit(x)) {
        ret = 2.0f - ret;
    }
    return ret;
}


double erfc(double) __attribute__((alias("erfcf")));
