#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_inf_lsh_1 UINT64_C(0xFFE0000000000000)

int _isnanl(long double x) {
    F64_pun val;
    val.flt = x;
    // clears the signbit
    val.bin <<= 1;
    // positive NaN is greater than positive infinity
    return (val.bin > Float64_inf_lsh_1);
}
