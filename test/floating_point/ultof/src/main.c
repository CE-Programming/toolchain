#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include "ultof_lut.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

#define AUTOTEST_DEBUG 0

#ifndef AUTOTEST_DEBUG
#define AUTOTEST_DEBUG 0
#endif

#if AUTOTEST_DEBUG
void print_failed(uint32_t input, uint32_t guess, uint32_t truth) {
    printf(
        "I: %lu\nU: %08lX -->\nG: %08lX !=\nT: %08lX\n",
        input, input, guess, truth
    );
}
#else
#define print_failed(...)
#endif

size_t run_test(void) {
    typedef uint32_t input_t;
    typedef F32_pun output_t;

    const size_t length = ARRAY_LENGTH(ultof_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)ultof_LUT_input );
    const output_t *output = (const output_t*)((const void*)ultof_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F32_pun result;

        result.flt = (float)input[i];
        if (result.bin != output[i].bin) {
            // ignore round to maximum magnitude errors from __ltof
            #if 0
                bool ignore_ltof_failure =
                    (input[i] <= INT32_MAX) &&
                    (result.bin == output[i].bin + 1);
                if (ignore_ltof_failure == false) {
                    print_failed(input[i], result.bin, output[i].bin);
                    return i;
                }
            #else
                // round to nearest ties away from zero to match __ltof behaviour
                bool ignore_ltof_failure =
                    (result.bin == output[i].bin + 1);
                if (ignore_ltof_failure == false) {
                    print_failed(input[i], result.bin, output[i].bin);
                    return i;
                }
            #endif
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
