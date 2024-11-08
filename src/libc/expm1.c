#include <math.h>

float M_expm1f(const float x)
{
    #if 1
        /**
         * 0x1.0p-12f: At least 12.0bits of precision
         */
        if (fabsf(x) < 2.44140625e-4f /* 0x1.0p-12f */) {
            return x;
        }
    #else
        /**
         * 0x1.0p-8f: At least 16.0bits of precision
         */
        if (fabsf(x) < 3.90625e-3f /* 0x1.0p-8f */) {
            return x + 0.5f * (x * x);
        }
    #endif
    return expf(x) - 1.0f;
}


double expm1(double) __attribute__((alias("expm1f")));
