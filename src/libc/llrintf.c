#include <math.h>

long long llrintf(float x)
{
	return rintf(x);
}

long long llrint(double) __attribute__((alias("llrintf")));
