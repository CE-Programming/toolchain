#include <math.h>

/**
 * Algorithm from:
 * https://en.wikipedia.org/wiki/Error_function#Approximation_with_elementary_functions
 */
long double erfcl(long double x)
{
    static const long double
        p = 0.3275911L,
        a1 = 0.254829592L,
        a2 = -0.284496736L,
        a3 = 1.421413741L,
        a4 = -1.453152027L,
        a5 = 1.061405429L;
    const long double t = 1.0L / (1.0L + p * fabsl(x));
    long double ret = t * (a1 + t * (a2 + t * (a3 + t * (a4 + t * a5)))) * expl(-x * x);
    if (signbit(x)) {
        ret = 2.0L - ret;
    }
    return ret;
}
