#include <math.h>
#include "__float32_constants.h"

/**
 * @remarks Minimum ulp:
 * ulp of -20 at +0x1.ff2afcp-5
 */
float asinhf(float arg) {
	float x = fabsf(arg);
	if (x < 0.0703125f) {
		x = x - (x * x * x) * F32_1_DIV_6;
	} else if (x < 0x1.0p+63f) {
		x = logf(x + sqrtf(x * x + 1.0f));
	} else {
		x = logf(x) + F32_LN2;
	}
	return copysignf(x, arg);
}

double asinh(double) __attribute__((alias("asinhf")));
