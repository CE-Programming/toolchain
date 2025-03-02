#include <math.h>

long double erfcl(long double x)
{
    static const long double p = 0.3275911l, a1 = 0.254829592l, a2 = -0.284496736l, a3 = 1.421413741l, a4 = -1.453152027l, a5 = 1.061405429l;
    const long double t = 1.0l / (1.0l + p * fabsl(x));
    return copysignl(t * (a1 + t * (a2 + t * (a3 + t * (a4 + t * a5)))) * expl(-x * x), x);
}
