#include <math.h>

float roundf(float x)
{
	/**
	 * The below magic number allows the expression `fabsf(x) + 0.5f` to be
	 * calculated as round-to-zero instead of round-to-nearest.
	 * The magic number is nextafterf(0.5f, 0.0f) or 0x3EFFFFFF
	 */
	return copysignf(truncf(fabsf(x) + 0.4999999701976776f), x);
}

double round(double) __attribute__((alias("roundf")));
