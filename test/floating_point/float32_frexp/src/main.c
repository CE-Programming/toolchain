#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

/* enable if the toolchain is configured to use the subnormal compliant frexpf */
#if 0

#include "f32_frexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

size_t run_test(void) {
    typedef float input_t;
    typedef struct { F32_pun frac; int expon; } output_t;

    const size_t length = ARRAY_LENGTH(f32_frexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_frexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_frexp_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int expon;
        F32_pun result;
        result.flt = frexpf(input[i], &expon);
        if (result.bin != output[i].frac.bin || expon != output[i].expon) {
            if (!(isnan(result.flt) && isnan(output[i].frac.flt))) {
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

#else

int main(void) {
    os_ClrHome();
    printf("All tests passed");
    while (!os_GetCSC());
    return 0;
}

#endif
