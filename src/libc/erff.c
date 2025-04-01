#include <math.h>
#include "__float32_constants.h"

/**
 * @remarks Minimum ulp:
 * ulp of -9	at +0x1.00030ap-5 with ideal erfcf
 * ulp of +5549 at +0x1.c46b04p-5 with current erfcf
 */
float erff(float arg) {
	float x = fabsf(arg);
	if (x < 0x1.0p-5f) {
		return F32_2_DIV_SQRTPI * (arg - arg * arg * arg * F32_1_DIV_3);
	}
	x = 1.0f - erfcf(x);
	return copysignf(x, arg);
}

double erf(double) __attribute__((alias("erff")));
