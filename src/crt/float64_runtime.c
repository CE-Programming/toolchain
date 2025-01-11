#include <stdint.h>
#include "../softfloat/include/softfloat.h"

//------------------------------------------------------------------------------
// unions
//------------------------------------------------------------------------------

typedef union F64_pun {
    long double flt;
    float64_t soft;
    uint64_t bin;
} F64_pun;

typedef union F32_pun {
    float flt;
    float32_t soft;
    uint32_t bin;
} F32_pun;

//------------------------------------------------------------------------------
// Arithmetic functions
//------------------------------------------------------------------------------

/* long double _dneg_c(long double x) */

long double _dadd_c(long double x, const long double *y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = *y;
    ret.soft = f64_add(arg_x.soft, arg_y.soft);
    return ret.flt;
}

long double _dsub_c(long double x, const long double *y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = *y;
    ret.soft = f64_sub(arg_x.soft, arg_y.soft);
    return ret.flt;
}

long double _dmul_c(long double x, const long double *y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = *y;
    ret.soft = f64_mul(arg_x.soft, arg_y.soft);
    return ret.flt;
}

long double _ddiv_c(long double x, const long double *y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = *y;
    ret.soft = f64_div(arg_x.soft, arg_y.soft);
    return ret.flt;
}

long double _drem_c(long double x, const long double *y) {
    F64_pun arg_x, arg_y, ret;
    arg_x.flt = x;
    arg_y.flt = *y;
    ret.soft = f64_rem(arg_x.soft, arg_y.soft);
    return ret.flt;
}

/* int _dcmp_c(const long double *x, const long double* y) */

//------------------------------------------------------------------------------
// Convert to long double
//------------------------------------------------------------------------------

long double _ftod_c(float x) {
    F32_pun arg_x;
    F64_pun ret;
    arg_x.flt = x;
    ret.soft = f32_to_f64(arg_x.soft);
    return ret.flt;
}

long double _ltod_c(int32_t x) {
    F64_pun ret;
    ret.soft = i32_to_f64(x);
    return ret.flt;
}

long double _lltod_c(int64_t x) {
    F64_pun ret;
    ret.soft = i64_to_f64(x);
    return ret.flt;
}

long double _ultod_c(uint32_t x) {
    F64_pun ret;
    ret.soft = ui32_to_f64(x);
    return ret.flt;
}

long double _ulltod_c(uint64_t x) {
    F64_pun ret;
    ret.soft = ui64_to_f64(x);
    return ret.flt;
}

//------------------------------------------------------------------------------
// Convert from long double
//------------------------------------------------------------------------------

float _dtof_c(long double x) {
    F32_pun ret;
    F64_pun arg_x;
    arg_x.flt = x;
    ret.soft = f64_to_f32(arg_x.soft);
    return ret.flt;
}

int32_t _dtol_c(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_i32_r_minMag(arg_x.soft, false);
}

int64_t _dtoll_c(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_i64_r_minMag(arg_x.soft, false);
}

uint32_t _dtoul_c(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_ui32_r_minMag(arg_x.soft, false);
}

uint64_t _dtoull_c(long double x) {
    F64_pun arg_x;
    arg_x.flt = x;
    return f64_to_ui64_r_minMag(arg_x.soft, false);
}
