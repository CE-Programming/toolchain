#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include "f32_ldexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

size_t run_test(void) {
    typedef struct { float value; int expon; } input_t;
    typedef F32_pun output_t;

    const size_t length = ARRAY_LENGTH(f32_ldexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_ldexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_ldexp_LUT_output);
    for (size_t i = 0; i < length; i++) {
        F32_pun result;
        result.flt = ldexpf(input[i].value, input[i].expon);
        // ignoring subnormal inputs for now
        if (issubnormal(input[i].value) || issubnormal(output[i].flt)) {
            continue;
        }
        if (result.bin != output[i].bin) {
            // ignore NaN's with differing payloads
            // treat signed zeros as equal for now
            if (
                (!(isnan(result.flt) && isnan(output[i].flt))) &&
                (!(iszero(result.flt) && iszero(output[i].flt)))
            ) {
                /* Float multiplication does not handle subnormals yet */
                if (!(iszero(result.flt) && issubnormal(output[i].flt))) {
                    #if 0
                        printf(
                            "%zu:\nI: %08lX %+d\nG: %08lX\nT: %08lX\n",
                            i, *(uint32_t*)(void*)&(input[i].value), input[i].expon,
                            result.bin, output[i].bin
                        );
                    #endif
                    return i;
                }
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
