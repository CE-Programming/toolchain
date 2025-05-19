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

#include "f64_ldexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

size_t run_test(void) {
    typedef struct { long double value; int expon; } input_t;
    typedef F64_pun output_t;

    const size_t length = ARRAY_LENGTH(f64_ldexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_ldexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_ldexp_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F64_pun result;
        result.flt = ldexpl(input[i].value, input[i].expon);
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
        fputs("All tests passed", stdout);
    } else {
        char buf[sizeof("Failed test: 16777215\n")];
        boot_sprintf(buf, "Failed test: %u\n", fail_index);
        fputs(buf, stdout);
    }

    while (!os_GetCSC());

    return 0;
}
