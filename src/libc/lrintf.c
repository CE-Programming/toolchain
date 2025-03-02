#include <math.h>

long lrintf(float x)
{
    return rintf(x);
}

long lrint(double) __attribute__((alias("lrintf")));
