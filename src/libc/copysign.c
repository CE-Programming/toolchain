#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_signbit   UINT64_C(0x8000000000000000)
#define Float64_fabs_mask UINT64_C(0x7FFFFFFFFFFFFFFF)

// Should be easy to implement in assembly
long double copysignl(long double x, long double y) {
    F64_pun arg_x, arg_y;
    arg_x.flt = x;
    arg_y.flt = y;
    // clear the signbit of x
    arg_x.bin &= Float64_fabs_mask;
    // copy the signbit of y
    arg_x.bin ^= arg_y.bin & Float64_signbit;
    return arg_x.flt;
}
