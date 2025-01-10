#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_signbit UINT64_C(0x8000000000000000)

// Should be easy to implement in assembly
long double _dneg_c(long double x) {
    F64_pun ret;
    ret.flt = x;
    ret.bin ^= Float64_signbit;
    return ret.flt;
}
