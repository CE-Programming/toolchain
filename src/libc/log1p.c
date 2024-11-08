#include <math.h>

float log1pf(const float x)
{
#if 1
    /**
     * 0x1.0p-12f: At least 12.0bits of precision
     */
    if (fabsf(x) < 2.44140625e-4f /* 0x1.0p-12f */) {
        return x;
    }
#else
    #if 0
        /**
         * 0x1.0p-63f: Fast denormalized/small value check for Assembly
         * `0.5f (x * x)` rounds to zero when `x` is less than +-2^-74. We can
         * perform a quick denormal test by checking that bits 6 and 5 of the
         * highest byte of the float are zero. This allows any float less than
         * +-2^-63 to take the fast `return x` path, and allows later code to
         * assume that `x` is neither denormal nor zero.
         */
        if (fabsf(x) < 1.084202172e-19f /* 0x1.0p-63f */) {
            return x;
        }
    #endif
    /**
     * 0x1.7p-8f: At least 16.0bits of precision
     * 0x1.8p-8f: At least 15.8bits of precision
     * 0x1.0p-8f: At least 15.0bits of precision
     */
    if (fabsf(x) < 5.615234375e-3f /* 0x1.7p-8f */) {
        /**
        * 0.5f can be turned into a decrement of the exponent assuming that
        * `x` is normalized.
        */
        return x - 0.5f * (x * x);
    }
#endif
    return logf(x + 1.0f);
}

double log1p(double) __attribute__((alias("log1pf")));
