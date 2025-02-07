#include <math.h>
#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_neg_zero UINT64_C(0x8000000000000000)

long double floorl(long double x) {
    if (!signbit(x)) {
        return truncl(x);
    }
    if (!isfinite(x)) {
        return x;
    }
    F64_pun frac;
    frac.flt = modfl(x, &x);
    if (frac.bin != Float64_neg_zero) {
        x -= 1.0L;
    }
    return x;
}
