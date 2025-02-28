#include <math.h>

/**
 * @remarks This function has a bug. Because `fabsf(x) + 0.5f` uses
 * round-to-nearest ties-to-even, `roundf(0.4999999702f)` will
 * return 1.0f instead of 0.0f
 */
float roundf(float x)
{
    return copysignf(truncf(fabsf(x) + .5f), x);
}

double round(double) __attribute__((alias("roundf")));
