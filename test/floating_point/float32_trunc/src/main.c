#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include "f32_trunc_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

size_t run_test(void) {
    typedef F32_pun input_t;
    typedef F32_pun output_t;

    const size_t length = ARRAY_LENGTH(f32_trunc_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_trunc_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_trunc_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F32_pun result;
        result.flt = truncf(input[i].flt);
        if (result.bin != output[i].bin && !(isnan(result.flt) || isnan(output[i].flt))) {
            #if 0
                printf(
                    "I: %08lX T: %zu\nG: %08lX\nT: %08lX\n",
                    input[i].bin, i,
                    result.bin,
                    output[i].bin
                );
            #endif
            return i;
        }
    }

    /* passed all */
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
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
