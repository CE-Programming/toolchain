#include <math.h>
#include <stdint.h>

#if 0

    /* Portable version */

    int _fpclassifyf(float x)
    {
        return
            isnan(x)    ? FP_NAN      :
            isinf(x)    ? FP_INFINITE :
            (x == 0.0f) ? FP_ZERO     :
            isnormal(x) ? FP_NORMAL   :
            FP_SUBNORMAL;
    }

#else

    /* Bitwise version */

    typedef union Float32_Bitwise {
        float flt_part;
        uint32_t u32_part;
        uint24_t u24_part;
    } Float32_Bitwise;

    #define Float32_Exponent_Mask INT32_C(0x7F800000)
    #define Float32_Mantissa_Mask INT32_C(0x007FFFFF)

    int _fpclassifyf(float x)
    {
        Float32_Bitwise x_bin;
        x_bin.flt_part = x;
        
        const uint32_t exp_mask = x_bin.u32_part & Float32_Exponent_Mask;
        
        // Both of these compile to the same lto.src as of 2024-Oct-10
        #if 1
            uint24_t mantissa = x_bin.u24_part;
            // bit 23 is part of the exponent, so it must be cleared
            mantissa += mantissa;
        #else
            uint32_t mantissa = x_bin.u32_part & Float32_Mantissa_Mask;
        #endif
        
        return (
            (exp_mask == 0) ? FP_ZERO :
            (exp_mask == Float32_Exponent_Mask) ? FP_INFINITE :
            FP_NORMAL
        ) | (mantissa != 0);
    }

#endif

int _fpclassify(double) __attribute__((alias("_fpclassifyf")));
