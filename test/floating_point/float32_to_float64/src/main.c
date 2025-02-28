#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include "f32_to_f64_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

size_t run_test(void) {
    typedef float input_t;
    typedef F64_pun output_t;

    const size_t length = ARRAY_LENGTH(f32_to_f64_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_to_f64_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_to_f64_LUT_output);

    F64_pun result;
    for (size_t i = 0; i < length; i++) {
        result.flt = (long double)input[i];
        if (result.bin != output[i].bin) {
            if (!(isnan(result.flt) && isnan(output[i].flt))) {
                return i;
            }
        }
    }

    /* passed all */
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    size_t fail_index = run_test();
    if (fail_index == SIZE_MAX) {
        printf("All tests passed");
    } else {
        printf("Failed test: %zu", fail_index);
    }

    while (!os_GetCSC());

    return 0;
}
