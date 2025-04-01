#include <math.h>

float _fmodf_c(float x, float y)
{
	return x - truncf(x / y) * y;
}

double _fmod_c(double, double) __attribute__((alias("_fmodf_c")));
