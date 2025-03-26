#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include "f32_modf_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

size_t run_test(void) {
    typedef F32_pun input_t;
    typedef struct { F32_pun frac_part; F32_pun trunc_part; } output_t;

    const size_t length = ARRAY_LENGTH(f32_modf_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_modf_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_modf_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F32_pun trunc_part;
        F32_pun frac_part;
        frac_part.bin = 0xDEADBEEF;
        trunc_part.bin = 0xCAFE4B1D;
        frac_part.flt = modff(input[i].flt, &(trunc_part.flt));
        if (frac_part.bin != output[i].frac_part.bin || trunc_part.bin != output[i].trunc_part.bin) {
            if (!(
                isnan(frac_part.flt) && isnan(output[i].frac_part.flt) &&
                isnan(trunc_part.flt) && isnan(output[i].trunc_part.flt)
            )) {
                printf(
                    "I: %08lX T: %zu\nG: %08lX %08lX\nT: %08lX %08lX\n",
                    input[i].bin, i,
                    frac_part.bin, trunc_part.bin,
                    output[i].frac_part.bin, output[i].trunc_part.bin
                );
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
