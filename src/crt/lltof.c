#include <limits.h>
#include <math.h>
#include <stdint.h>

float _lltof_c(long long x)
{
    uint8_t exponent = x ? __builtin_clrsbll(x) : LLONG_WIDTH - 1;
    if (exponent >= LLONG_WIDTH - LONG_WIDTH) return (long)x;
    exponent = LLONG_WIDTH - LONG_WIDTH - exponent;
    return ldexpf((long)(x >> exponent), exponent);
}
