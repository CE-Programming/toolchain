#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union F64_pun {
	long double flt;
	uint64_t bin;
} F64_pun;

#define F64_CMP_EQUAL	  0 /* sets the Z flag */
#define F64_CMP_LESS	  -1 /* sets the S flag */
#define F64_CMP_GREATER	1 /* doesn't trigger flags */
#define F64_CMP_UNORDERED  1 /* doesn't trigger flags */

// assumes no NaN
int _dcmp_c(const long double *__restrict x, const long double *__restrict y) {
	F64_pun arg_x, arg_y;
	arg_x.flt = *x;
	arg_y.flt = *y;

	bool x_sign = signbit(arg_x.flt);
	bool y_sign = signbit(arg_y.flt);
	if (x_sign != y_sign) {
		if (iszero(arg_x.flt) && iszero(arg_y.flt)) {
			return F64_CMP_EQUAL;
		}
		return (x_sign ? F64_CMP_LESS : F64_CMP_GREATER);
	}
	
	if (arg_x.bin == arg_y.bin) {
		return F64_CMP_EQUAL;
	}
	return ((arg_x.bin < arg_y.bin) != x_sign) ? F64_CMP_LESS : F64_CMP_GREATER;
}
