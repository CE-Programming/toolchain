#include <stdint.h>
#include <math.h>

typedef union Float32_Bitwise {
	float flt_part;
	uint32_t u32_part;
} Float32_Bitwise;

/**
 * @note this function may only be used if it can be guaranteed that
 * multiplying `x` by two will result in a finite and normal value.
 */
static float Float32_mul_2(float x) {
	Float32_Bitwise ret;
	ret.flt_part = x;
	ret.u32_part += 0x800000;
	return ret.flt_part;
}

// Used for range reduction `2^111`. This value can fit inside a uint8_t
#define around_2_pow_111 0x77000000

// Used for range reduction `2^-111`. This value can fit inside a uint8_t
#define around_recip_2_pow_111 0x08000000

/**
 * @remarks Minimum precision: 22.513754 bits (Across all 2^32 input values)
 * @note Precision tested with 32bit floats on x86_64
 */
float cbrtf(const float x)
{
	if (x == 0.0f || !isfinite(x)) {
		// Perserves signed zeros, inf, and NaN
		return x;
	}

	const float fabs_x = fabsf(x);

	int range_reduce = 0;
	int range_return = 0;

	Float32_Bitwise bin_x;
	bin_x.flt_part = fabs_x;
	/**
	 * 2^111 and 2^-111 only use the upper 8 bits of a 32 bit float, which
	 * might allow for some assembly optimizations
	 */
	if (bin_x.u32_part >= around_2_pow_111) {
		/**
		 * Values chosen to avoid NaN/inf for large finite inputs.
		 * Other values may be used instead.
		 */
		range_reduce = -18;
		range_return =   6;
	} else if (bin_x.u32_part <= around_recip_2_pow_111) {
		/**
		 * Values choosen to avoid precision loss for denormal numbers.
		 * Other values may be used instead.
		 */
		range_reduce =  36;
		range_return = -12;
	}
	
	const float scaled_x = ldexpf(fabs_x, range_reduce);
	const float scaled_x_mul_2 = Float32_mul_2(scaled_x);

	int expon = ilogbf(scaled_x);
	/**
	 * @remarks Adds two for rounding purposes
	 * @note trunc rounds in the opposite direction when expon is negative
	 */
	expon += (expon >= 0) ? 2 : 0;
	expon /= 3;

	float guess = ldexpf(1.0f, expon);
	float guess_cubed;

	/* Halley iteration */
	guess_cubed = guess * guess * guess;
	guess = guess * ((guess_cubed + scaled_x_mul_2) / (Float32_mul_2(guess_cubed) + scaled_x));

	/* Halley iteration */
	guess_cubed = guess * guess * guess;
	guess = guess * ((guess_cubed + scaled_x_mul_2) / (Float32_mul_2(guess_cubed) + scaled_x));

	/* Newton iteration */
	#if 1
		// 22.513754 bits
		guess = ((scaled_x / (guess * guess)) + Float32_mul_2(guess)) / 3.0f;
	#else
		// 22.206228 bits
		guess = ((scaled_x / (guess * guess)) + Float32_mul_2(guess)) * 0.33333333333333333333f;
	#endif

	guess = ldexpf(guess, range_return);

	return copysignf(guess, x);
}

double cbrt(double) __attribute__((alias("cbrtf")));
