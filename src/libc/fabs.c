#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_fabs_mask UINT64_C(0x7FFFFFFFFFFFFFFF)

// Should be easy to implement in assembly
long double fabsl(long double x) {
    F64_pun ret;
    ret.flt = x;
    /**
     * @remarks This can also be done by doing a leftshift to remove the
	 * signbit, and then doing a rightsift
     */
    ret.bin &= Float64_fabs_mask;
    return ret.flt;
}
