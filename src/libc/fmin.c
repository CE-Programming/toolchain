#include <math.h>

float fminf(float x, float y) {
    return
        isless(x, y) ? x :
        isless(y, x) ? y :
        /* attempts to return a non-NaN value */
        isnan(x) ? y :
        isnan(y) ? x :
        /* arguments are equal or signed zero */
        signbit(x) ? x : y;
}

double fmin(double, double) __attribute__((alias("fminf")));

#ifdef fminl
#undef fminl
#endif

long double fminl(long double x, long double y) {
    return
        isless(x, y) ? x :
        isless(y, x) ? y :
        /* attempts to return a non-NaN value */
        isnan(x) ? y :
        isnan(y) ? x :
        /* arguments are equal or signed zero */
        signbit(x) ? x : y;
}

long double _debug_fminl(long double, long double) __attribute__((alias("fminl")));
