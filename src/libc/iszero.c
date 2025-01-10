#include <stdint.h>

typedef union F32_pun {
    long double flt;
    uint64_t bin;
} F32_pun;

int _iszerof(float x) {
    F32_pun val;
    val.flt = x;
    // clears the signbit
    val.bin <<= 1;
    return (val.bin == 0);
}

int _iszero(double) __attribute__((alias("_iszerof")));

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

int _iszerol(long double x) {
    F64_pun val;
    val.flt = x;
    // clears the signbit
    val.bin <<= 1;
    return (val.bin == 0);
}
