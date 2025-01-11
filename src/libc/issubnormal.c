#include <stdbool.h>
#include <stdint.h>
#include <math.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

#define Float32_exp_mask UINT32_C(0x7F800000)

int _issubnormalf(float x) {
    // zero is not a subnormal number
    if (iszero(x)) {
        return false;
    }
    F32_pun val;
    val.flt = x;
    val.bin &= Float32_exp_mask;
    // check if the exponent is all zeros
    return (val.bin == 0);
}

int _issubnormal(double) __attribute__((alias("_issubnormalf")));

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_exp_mask UINT64_C(0x7FF0000000000000)

int _issubnormall(long double x) {
    // zero is not a subnormal number
    if (iszero(x)) {
        return false;
    }
    F64_pun val;
    val.flt = x;
    val.bin &= Float64_exp_mask;
    // check if the exponent is all zeros
    return (val.bin == 0);
}
