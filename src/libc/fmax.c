#include <math.h>

float fmaxf(float x, float y) {
    return
        isless(x, y) ? y :
        isless(y, x) ? x :
        /* attempts to return a non-NaN value */
        isnan(x) ? y :
        isnan(y) ? x :
        /* arguments are equal or signed zero */
        signbit(x) ? y : x;
}

double fmax(double, double) __attribute__((alias("fmaxf")));

long double fmaxl(long double x, long double y) {
    return
        isless(x, y) ? y :
        isless(y, x) ? x :
        /* attempts to return a non-NaN value */
        isnan(x) ? y :
        isnan(y) ? x :
        /* arguments are equal or signed zero */
        signbit(x) ? y : x;
}
