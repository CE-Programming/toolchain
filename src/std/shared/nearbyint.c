#include <fenv.h>
#include <math.h>

float nearbyintf(float x)
{
    static float (*const lut[])(float) = {
        [FE_DOWNWARD] = &floorf,
        [FE_TONEAREST] = &roundevenf,
        [FE_TOWARDZERO] = &truncf,
        [FE_UPWARD] = &ceilf,
    };
    return lut[fegetround()](x);
}

double nearbyint(double) __attribute__((alias("nearbyintf")));

#if 0
long double nearbyintl(long double x)
{
    static long double (*const lut[])(long double) = {
        [FE_DOWNWARD] = &floorl,
        [FE_TONEAREST] = &roundevenl,
        [FE_TOWARDZERO] = &truncl,
        [FE_UPWARD] = &ceill,
    };
    return lut[fegetround()](x);
}
#endif
