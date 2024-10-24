#include <stdint.h>
#include <math.h>

typedef union Float32_Bitwise {
    float flt_part;
    uint32_t u32_part;
    uint24_t u24_part;
} Float32_Bitwise;

#define Float32_Exponent_Mask INT32_C(0x7F800000)

int _isnormalf(float x)
{
    Float32_Bitwise x_bin;
    x_bin.flt_part = x;
    
    const int32_t exp_mask = x_bin.u32_part & Float32_Exponent_Mask;
    
    // Check that the exponent isn't all zeros (subnormal) or all ones (nan/inf)
    return (exp_mask != 0 && exp_mask != Float32_Exponent_Mask);
}

int _isnormal(double) __attribute__((alias("_isnormalf")));
