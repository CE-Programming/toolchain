#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union F32_pun {
	float flt;
	uint32_t bin;
	struct {
		uint24_t mant;
		uint8_t expon;
	} split;
} F32_pun;

typedef union F64_pun {
	long double flt;
	uint64_t bin;
	struct {
		uint24_t lo;
		uint24_t hi;
	} u24;
} F64_pun;

#define Float64_pos_zero UINT64_C(0x0000000000000000)
#define Float64_neg_zero UINT64_C(0x8000000000000000)
#define Float64_pos_inf  UINT64_C(0x7FF0000000000000)
#define Float64_neg_inf  UINT64_C(0xFFF0000000000000)
#define Float64_pos_nan  UINT64_C(0x7FF8000000000000)
#define Float64_neg_nan  UINT64_C(0xFFF8000000000000)

#define Float64_mant_bits  52
#define Float32_mant_bits  23
#define Float64_expon_bits 11
#define Float32_expon_bits 8
#define Float64_bias       1023
#define Float32_bias       127

long double _ftod_c(float x) {
	bool x_sign = signbit(x);
	F32_pun val;
	F64_pun ret;
	val.flt = x;

	/* common path */
	if (isnormal(val.flt)) {
		uint24_t mantissa = val.split.mant;
		uint24_t expon =
			(val.split.expon + ((Float64_bias - Float32_bias) >> 1)) +
			(x_sign ? (((1 << Float64_expon_bits) - (1 << Float32_expon_bits)) >> 1) : (0));
		ret.u24.hi = expon;
		ret.u24.lo = mantissa;
		// mantissa[0, 22] exponent[23, 33] signbit[34]
		ret.bin <<= Float64_mant_bits - Float32_mant_bits;
		return ret.flt;
	}
	if (issubnormal(val.flt)) {
		// since this is subnormal, the LSB of the exponent is already zero
		uint24_t mantissa = val.split.mant;
		
		// shift until the MSB of the mantissa is the LSB of the exponent
		uint8_t clz_result = (uint8_t)__builtin_clz(mantissa);
		mantissa <<= clz_result;

		/**
		 * Sets the LSB of the exponent. If the clz_result is odd, then the
		 * exponent will also be odd
		 */
		mantissa += (clz_result & 0x1) ? 0x800000 : 0x000000;

		uint24_t expon =
			(((Float64_bias - Float32_bias) >> 1) -
			(clz_result >> 1)) +
			(x_sign ? ((1 << Float64_expon_bits) >> 1) : 0);

		ret.u24.hi = expon;
		ret.u24.lo = mantissa;
		// mantissa[0, 22] exponent[23, 33] signbit[34]
		ret.bin <<= Float64_mant_bits - Float32_mant_bits;
		return ret.flt;
	}
	if (iszero(val.flt)) {
		ret.bin = x_sign ? Float64_neg_zero : Float64_pos_zero;
		return ret.flt;
	}
	if (isinf(val.flt)) {
		ret.bin = x_sign ? Float64_neg_inf : Float64_pos_inf;
		return ret.flt;
	}
	/* isnan(val.flt) */
	ret.bin = x_sign ? Float64_neg_nan : Float64_pos_nan;
	return ret.flt;
}
