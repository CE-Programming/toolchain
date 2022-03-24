#include <limits.h>
#include <math.h>

float _ulltof(unsigned long long x)
{
    unsigned long long doubled;
    int exponent = ULONG_WIDTH - ULLONG_WIDTH;
    while (!__builtin_add_overflow(x, x, &doubled)) {
        x = doubled;
        --exponent;
    }
    return ldexpf((unsigned long)(x >> (ULLONG_WIDTH - ULONG_WIDTH)), exponent);
}

double _ulltod(unsigned long long) __attribute__((alias("_ulltof")));
