#include <math.h>

long double erfl(long double x)
{
    return 1 - erfcl(x);
}
