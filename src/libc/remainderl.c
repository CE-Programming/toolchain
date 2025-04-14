#include <math.h>

long double remainderl(long double x, long double y)
{
    return x - roundevenl(x / y) * y;
}
