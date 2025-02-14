#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include "f64_frexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

size_t run_test(void) {
    typedef long double input_t;
    typedef struct { long double frac; int expon; } output_t;

    const size_t length = ARRAY_LENGTH(f64_frexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_frexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_frexp_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int expon;
        long double result = frexpl(input[i], &expon);
        if (result != output[i].frac || expon != output[i].expon) {
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
        printf("All tests passed");
    } else {
        printf("Failed test: %zu", fail_index);
    }

    while (!os_GetCSC());

    return 0;
}
