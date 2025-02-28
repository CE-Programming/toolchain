#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdlib.h>

#include "f64_rounding_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

size_t run_test(const char** failed_func) {
    typedef long double input_t;
    typedef struct { F64_pun r_floor; F64_pun r_ceil; F64_pun r_round; } output_t;

    const size_t length = ARRAY_LENGTH(f64_rounding_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_rounding_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_rounding_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F64_pun result;
        input_t value = input[i];
        
        result.flt = floorl(value);
        if (result.bin != output[i].r_floor.bin) {
            if (!(isnan(result.flt) && isnan(output[i].r_floor.flt))) {
                *failed_func = "floor";
                return i;
            }
        }

        result.flt = ceill(value);
        if (result.bin != output[i].r_ceil.bin) {
            if (!(isnan(result.flt) && isnan(output[i].r_ceil.flt))) {
                *failed_func = "ceil";
                return i;
            }
        }

        result.flt = roundl(value);
        if (result.bin != output[i].r_round.bin) {
            if (!(isnan(result.flt) && isnan(output[i].r_round.flt))) {
                *failed_func = "round";
                return i;
            }
        }
    }

    /* passed all */
    *failed_func = "none";
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    const char* failed_func;
    size_t fail_index = run_test(&failed_func);
    if (fail_index == SIZE_MAX) {
        printf("All tests passed");
    } else {
        printf("Failed test: %zu %s", fail_index, failed_func);
    }

    while (!os_GetCSC());

    return 0;
}
