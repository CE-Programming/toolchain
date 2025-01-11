#include <stdint.h>
#include <math.h>

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

#define Float32_exp_mask INT32_C(0x7F800000)

int _isnormalf(float x)
{
    F32_pun val;
    val.flt = x;
    val.bin &= Float32_exp_mask;
    
    // Check that the exponent isn't all zeros (subnormal) or all ones (nan/inf)
    return (val.bin != 0 && val.bin != Float32_exp_mask);
}

int _isnormal(double) __attribute__((alias("_isnormalf")));

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_exp_mask UINT64_C(0x7FF0000000000000)

int _isnormall(long double x)
{
    F64_pun val;
    val.flt = x;
    val.bin &= Float64_exp_mask;
    
    // Check that the exponent isn't all zeros (subnormal) or all ones (nan/inf)
    return (val.bin != 0 && val.bin != Float64_exp_mask);
}
