#include <fenv.h>
#include <math.h>
#include <stdint.h>

typedef union F64_pun {
	long double flt;
	uint64_t bin;
} F64_pun;

typedef union F32_pun {
	float flt;
	uint32_t bin;
} F32_pun;

#define Float32_pos_subnorm_min UINT32_C(0x00000001)
#define Float32_neg_subnorm_min UINT32_C(0x80000001)
#define Float32_pos_nan		 UINT32_C(0x7FC00000)

float nexttowardf(float x, long double y) {
	F32_pun arg_x;
	arg_x.flt = x;

	if (isnan(x)) {
		return x;
	}

	if (isnan(y)) {
		F32_pun ret;
		ret.bin = Float32_pos_nan;
		return ret.flt;
	}
	
	F64_pun x_f64, y_f64;
	x_f64.flt = (long double)x;
	y_f64.flt = y;
	if (x_f64.bin == y_f64.bin) {
		// return unmodified
		return x;
	}

	if (iszero(x)) {
		F32_pun ret;
		ret.bin = signbit(y) ? Float32_neg_subnorm_min : Float32_pos_subnorm_min;
		if (iszero(y)) {
			// pos_subnorm_min becomes +0.0, and neg_subnorm_min becomes -0.0
			ret.bin--;
		} else {
			feraiseexcept(FE_INEXACT | FE_UNDERFLOW);
		}
		return ret.flt;
	}
	if (isless(x_f64.flt, y) != signbit(x)) {
		// Towards positive/negative infinity
		arg_x.bin++;
	} else {
		// Towards negative/positive zero
		arg_x.bin--;
	}
	if (isnormal(arg_x.flt)) {
		return arg_x.flt;
	}
	if (isinf(arg_x.flt)) {
		// overflow to infinity
		feraiseexcept(FE_INEXACT | FE_OVERFLOW);
	} else {
		// result is subnormal or zero
		feraiseexcept(FE_INEXACT | FE_UNDERFLOW);
	}
	return arg_x.flt;
}

double nexttoward(double, long double) __attribute__((alias("nexttowardf")));

/* nexttowardl is aliased in nextafter.c */
