#include <math.h>

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
