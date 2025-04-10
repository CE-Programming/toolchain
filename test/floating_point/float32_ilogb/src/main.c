#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include "f32_ilogb_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

size_t run_test(void) {
    typedef float input_t;
    typedef int output_t;

    const size_t length = ARRAY_LENGTH(f32_ilogb_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_ilogb_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_ilogb_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int result = ilogbf(input[i]);
        if (result != output[i]) {
            // printf("%3zu: %08lX\n\t%d != %d\n", i, input[i], result, output[i]);
            // while (!os_GetCSC());
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
