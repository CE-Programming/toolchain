#include <math.h>

/* enable when log1pl is implemented */
#if 0

/**
 * @remarks Relative precision of:
 * 2^-51 at +1.277396381e-01 with ideal log1pl
 */
long double atanhl(long double arg) {
    long double x = fabsl(arg);
    x = 0.5L * log1pl((2.0L * x) / (1.0L - x));
    return copysignl(x, arg);
}

#else

long double atanhl(long double x)
{
    return 0.5L * logl((1.0L + x) / (1.0L - x));
}

#endif
