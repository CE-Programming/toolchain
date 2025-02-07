#include <math.h>
#include <stdint.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define Float64_pos_zero UINT64_C(0x0000000000000000)

long double ceill(long double x) {
    if (signbit(x)) {
        return truncl(x);
    }
    if (!isfinite(x)) {
        return x;
    }
    F64_pun frac;
    frac.flt = modfl(x, &x);
    if (frac.bin != Float64_pos_zero) {
        x += 1.0L;
    }
    return x;
}
