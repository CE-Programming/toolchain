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

#include "f64_frexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

size_t run_test(void) {
    typedef long double input_t;
    typedef struct { F64_pun frac; int expon; } output_t;

    const size_t length = ARRAY_LENGTH(f64_frexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_frexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_frexp_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int expon;
        F64_pun result;
        result.flt = frexpl(input[i], &expon);
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
        puts("All tests passed");
    } else {
        char buf[sizeof("Failed test: 16777215")];
        boot_sprintf(buf, "Failed test: %u", fail_index);
        puts(buf);
    }

    while (!os_GetCSC());

    return 0;
}
