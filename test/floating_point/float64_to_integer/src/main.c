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

#include "f64_to_integer_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

void print_failed(long double input, uint64_t guess, uint64_t truth) {
    F64_pun value;
    value.flt = input;
    printf(
        "I: %016llX -->\nG: %016llX !=\nT: %016llX\n",
        value.bin, guess, truth
    );
}

size_t run_test(const char** failed_func) {
    typedef long double input_t;
    typedef struct { uint32_t u32; int32_t i32; uint64_t u64; int64_t i64; } output_t;

    const size_t length = ARRAY_LENGTH(f64_to_integer_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_to_integer_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_to_integer_LUT_output);

    for (size_t i = 0; i < length; i++) {

        if (input[i] >= 0.0L) {
            uint32_t ru32 = (uint32_t)input[i];
            if (ru32 != output[i].u32) {
                print_failed(input[i], (uint64_t)ru32, (uint64_t)output[i].u32);
                *failed_func = "dtoul";
                return i; 
            }

            uint64_t ru64 = (uint64_t)input[i];
            if (ru64 != output[i].u64) {
                print_failed(input[i], (uint64_t)ru64, (uint64_t)output[i].u64);
                *failed_func = "dtoull";
                return i;
            }
        }

        int32_t ri32 = (int32_t)input[i];
        if (ri32 != output[i].i32) {
            print_failed(input[i], (uint64_t)ri32, (uint64_t)output[i].i32);
            *failed_func = "dtol";
            return i;
        }

        

        int64_t ri64 = (int64_t)input[i];
        if (ri64 != output[i].i64) {
            print_failed(input[i], (uint64_t)ri64, (uint64_t)output[i].i64);
            *failed_func = "dtoll";
            return i;
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
