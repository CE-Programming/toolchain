#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define F64_CMP_EQUAL      0 /* sets the Z flag */
#define F64_CMP_LESS      -1 /* sets the S flag */
#define F64_CMP_GREATER    1 /* doesn't trigger flags */
#define F64_CMP_UNORDERED  1 /* doesn't trigger flags */

typedef struct f64_cmp_arg {
    long double x;
    bool x_sign; /* <-- unimplemented */
    unsigned int const return_address;
    long double y;
    bool y_sign; /* <-- unimplemented */
} f64_cmp_arg;

// assumes no NaN
int _dcmp_c(f64_cmp_arg *__restrict const arg) {
    F64_pun x, y;
    x.flt = arg->x;
    y.flt = arg->y;

    bool x_sign = signbit(x.flt);
    bool y_sign = signbit(y.flt);
    if (x_sign != y_sign) {
        if (iszero(x.flt) && iszero(y.flt)) {
            return F64_CMP_EQUAL;
        }
        return (x_sign ? F64_CMP_LESS : F64_CMP_GREATER);
    }
    
    if (x.bin == y.bin) {
        return F64_CMP_EQUAL;
    }
    return ((x.bin < y.bin) != x_sign) ? F64_CMP_LESS : F64_CMP_GREATER;
}
