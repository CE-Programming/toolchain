#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_inf_lsh_1 UINT64_C(0xFFE0000000000000)

#define F64_CMP_EQUAL      0
#define F64_CMP_LESS      -1
#define F64_CMP_GREATER    1  
#define F64_CMP_UNORDERED  1

// assumes no NaN
int _dcmp_c(const long double* x, const long double *y) {
    F64_pun arg_x, arg_y;
    arg_x.flt = *x;
    arg_y.flt = *y;

    // if (isunordered(x, y)) {
    // 	return F64_CMP_UNORDERED;
    // }
    
    bool x_sign = signbit(*x);
    bool y_sign = signbit(*y);
    if (x_sign != y_sign) {
        if (iszero(*x) && iszero(*y)) {
            return F64_CMP_EQUAL;
        }
        return (x_sign ? F64_CMP_LESS : F64_CMP_GREATER);
    }
    
    if (arg_x.bin == arg_y.bin) {
        return F64_CMP_EQUAL;
    }
    return ((arg_x.bin < arg_y.bin) != x_sign) ? F64_CMP_LESS : F64_CMP_GREATER;
}
