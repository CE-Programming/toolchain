#include <fenv.h>
#include <math.h>
#include <stdint.h>

typedef union F32_pun {
	float flt;
	uint32_t bin;
} F32_pun;

#define Float32_pos_subnorm_min UINT32_C(0x00000001)
#define Float32_neg_subnorm_min UINT32_C(0x80000001)
#define Float32_pos_inf		 UINT32_C(0x7F800000)
#define Float32_neg_inf		 UINT32_C(0xFF800000)

float nextupf(float x) {
	F32_pun arg_x;
	arg_x.flt = x;

	if (isnan(x) || arg_x.bin == Float32_pos_inf) {
		// return unmodified
		return x;
	}

	if (iszero(x)) {
		F32_pun ret;
		ret.bin = Float32_pos_subnorm_min;
		return ret.flt;
	}

	if (signbit(x)) {
		// Towards negative zero
		arg_x.bin--;
	} else {
		// Towards positive infinity
		arg_x.bin++;
	}
	return arg_x.flt;
}

double nextup(double) __attribute__((alias("nextupf")));

float nextdownf(float x) {
	F32_pun arg_x;
	arg_x.flt = x;

	if (isnan(x) || arg_x.bin == Float32_neg_inf) {
		// return unmodified
		return x;
	}

	if (iszero(x)) {
		F32_pun ret;
		ret.bin = Float32_neg_subnorm_min;
		return ret.flt;
	}
	
	if (signbit(x)) {
		// Towards negative infinity
		arg_x.bin++;
	} else {
		// Towards positive zero
		arg_x.bin--;
	}
	return arg_x.flt;
}

double nextdown(double) __attribute__((alias("nextdownf")));
