#include <math.h>

float remainderf(float x, float y)
{
	return x - nearbyintf(x / y) * y;
}

double remainder(double, double) __attribute__((alias("remainderf")));
