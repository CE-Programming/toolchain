#include <limits.h>
#include <math.h>

float _lltof(long long x)
{
    long long doubled;
    int exponent = LONG_WIDTH - LLONG_WIDTH;
    while (!__builtin_add_overflow(x, x, &doubled)) {
        x = doubled;
        --exponent;
    }
    return ldexpf((long)(x >> (LLONG_WIDTH - LONG_WIDTH)), exponent);
}

double _lltod(long long) __attribute__((alias("_lltof")));
