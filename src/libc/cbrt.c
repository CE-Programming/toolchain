#include <math.h>

/**
 * @remarks Newtons iteration will typically divide by 3.0, but I found that
 * multiplying by ~0.3328 gives a more accurate result somehow. This is rather
 * convienient since multiplication is faster than division.
 */
#define magic_third 0.3328f

/**
 * @remarks Minimum precision: 21.415037 bits at both +4.251052856e+02 and
 * +7.969426579e+17 for cbrtf.
 * The previous method of powf(x, 1.0f / 3.0f) had a minimum precision of
 * 21.0 bits at +4.037431946e+02, and a minimum precision 19.299560 bits
 * at +1.187444200e+07, slowly losing precision at larger magnitudes.
 * @note Precision tested with 32bit floats on x86_64
 */
float cbrtf(const float x)
{
	if (x == 0.0f || !isfinite(x)) {
		// Perserves signed zeros, inf, and NaN
		return x;
	}
	const float fabs_x = fabsf(x);
	const float fabs_x_mul_2 = 2.0f * x;

	int expon = ilogbf(fabs_x);
	
	/**
	 * @remarks Adds one for rounding purposes
	 * @note trunc rounds in the opposite direction when expon is negative
	 */
	expon += (expon < 0) ? -1 : 1;
	expon /= 3;

	float guess = ldexpf(1.0f, expon);
	float guess_cubed;

	/* Halley iteration */
	guess_cubed = guess * guess * guess;
	guess = guess * ((guess_cubed + fabs_x_mul_2) / (2.0f * guess_cubed + fabs_x));

	/* Newton iteration */
	guess = magic_third * ((fabs_x / (guess * guess)) + 2.0f * guess);

	/* Halley iteration */
	guess_cubed = guess * guess * guess;
	guess = guess * ((guess_cubed + fabs_x_mul_2) / (2.0f * guess_cubed + fabs_x));

	return signbit(x) ? -guess : guess;
}

double cbrt(double) __attribute__((alias("cbrtf")));
