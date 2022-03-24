#include <math.h>

float erfcf(float x)
{
    static const float p = 0.47047f, a1 = 0.3480242f, a2 = -0.0958798f, a3 = 0.7478556f;
    const float t = 1 / (1 + p * fabs(x));
    return copysignf(t * (a1 + t * (a2 + t * a3)) * expf(-x * x), x);
}

double erfc(double) __attribute__((alias("erfcf")));

long double erfcl(long double x)
{
    static const long double p = 0.3275911l, a1 = 0.254829592l, a2 = -0.284496736l, a3 = 1.421413741l, a4 = -1.453152027l, a5 = 1.061405429l;
    const long double t = 1 / (1 + p * fabs(x));
    return copysignf(t * (a1 + t * (a2 + t * (a3 + t * (a4 + t * a5)))) * expl(-x * x), x);
}
