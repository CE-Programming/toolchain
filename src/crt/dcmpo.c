#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union {
    struct {
        uint8_t carry : 1;
        uint8_t : 5;
        uint8_t zero : 1;
        uint8_t sign : 1;
    };
    uint8_t bin;
} Flags;

typedef union {
    long double flt;
    uint64_t bin;
} F64_pun;

typedef struct {
    long double x;
    uint8_t x_padding;
    unsigned int const return_address;
    long double y;
    uint8_t y_padding;
} f64_cmp_arg;

uint8_t _dcmpo_c(f64_cmp_arg const *__restrict const arg) {
    F64_pun x, y;
    x.flt = arg->x;
    y.flt = arg->y;
    Flags flags;
    if (_isnanl(x.flt) || _isnanl(y.flt)) {
        flags.zero = 0;
        flags.carry = 0;
        flags.sign = 1;
        return flags.bin;
    }
    bool x_sign = _signbitl(x.flt);
    bool y_sign = _signbitl(y.flt);
    if (x_sign != y_sign) {
        if (_iszerol(x.flt) && _iszerol(y.flt)) {
            flags.zero = 1;
            flags.carry = 0;
            flags.sign = 0;
            return flags.bin;
        }
        flags.zero = 0;
        flags.carry = x_sign ? 1 : 0;
        flags.sign = x_sign ? 1 : 0;
        return flags.bin;
    }
    if (x.bin == y.bin) {
        flags.zero = 1;
        flags.carry = 0;
        flags.sign = 0;
        return flags.bin;
    }
    bool cmp_less = ((x.bin < y.bin) != x_sign);
    flags.zero = 0;
    flags.carry = cmp_less ? 1 : 0;
    flags.sign = cmp_less ? 1 : 0;
    return flags.bin;
}
