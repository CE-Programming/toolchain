#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include "f64_ldexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

size_t run_test(void) {
    typedef struct { long double value; int expon; } input_t;
    typedef F64_pun output_t;

    const size_t length = ARRAY_LENGTH(f64_ldexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_ldexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_ldexp_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F64_pun result;
        result.flt = ldexpl(input[i].value, input[i].expon);
        if (result.bin != output[i].bin) {
            if (!(isnan(result.flt) && isnan(output[i].flt))) {
                return i;
            }
        }
    }

    /* passed all */
    return SIZE_MAX;
}

static int32_t rand_i32_expon() {
    union {
        struct {
            uint16_t part[2];
        };
        int32_t full;
    } ret;
    ret.part[0] = rand() & 0x1FFF;
    ret.part[1] = rand() & 0xC0C0;
    return ret.full;
}

static long double rand_f64() {
    union {
        struct {
            uint16_t part[4];
        };
        long double full;
    } ret;
    ret.part[0] = rand();
    ret.part[1] = rand();
    ret.part[2] = rand();
    ret.part[3] = rand();
    return ret.full;
}

static int clamp_exponent(long expon) {
    if (expon > INT_MAX) {
        return INT_MAX;
    }
    if (expon < INT_MIN) {
        return INT_MIN;
    }
    return (int)expon;
}

void run_edge_case(void) {
    srand(0x7184CE);
    long double input, output_i24, output_i32;
    for (size_t i = 0; i < 512; i++) {
        input = rand_f64();
        int32_t expon = rand_i32_expon();
        output_i24 = scalbnl(input, clamp_exponent(expon));
        output_i32 = scalblnl(input, expon);
        if (memcmp(&output_i24, &output_i32, sizeof(long double)) != 0) {
            puts("Failed edge case");
            return;
        }
    }
}

int main(void) {
    os_ClrHome();
    run_edge_case();
    size_t fail_index = run_test();
    if (fail_index == SIZE_MAX) {
        puts("All tests passed");
    } else {
        char buf[sizeof("Failed test: 16777215")];
        boot_sprintf(buf, "Failed test: %u", fail_index);
        puts(buf);
    }

    while (!os_GetCSC());

    return 0;
}
