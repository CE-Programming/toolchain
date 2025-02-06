#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include "../softfloat/include/softfloat.h"

typedef union F64_pun {
    long double flt;
    float64_t soft;
    uint64_t bin;
} F64_pun;

/* flags handled by softfloat */

#if 0
long double fmal(long double x, long double y, long double z) {
    F64_pun arg_x, arg_y, arg_z, ret;
    arg_x.flt = x;
    arg_y.flt = y;
    arg_z.flt = z;
    ret.soft = f64_mulAdd(arg_x.soft, arg_y.soft, arg_z.soft);
    return ret.flt;
}
#else
float64_t softfloat_mulAddF64(
	uint_fast64_t uiA, uint_fast64_t uiB, uint_fast64_t uiC, uint_fast8_t op
);

long double fmal(long double x, long double y, long double z) {
    F64_pun arg_x, arg_y, arg_z, ret;
    arg_x.flt = x;
    arg_y.flt = y;
    arg_z.flt = z;
    ret.soft = softfloat_mulAddF64(arg_x.bin, arg_y.bin, arg_z.bin, 0);
    return ret.flt;
}
#endif
