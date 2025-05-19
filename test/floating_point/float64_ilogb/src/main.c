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

#include "f64_ilogb_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

size_t run_test(void) {
    typedef long double input_t;
    typedef int output_t;

    const size_t length = ARRAY_LENGTH(f64_ilogb_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_ilogb_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_ilogb_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int result = ilogbl(input[i]);
        if (result != output[i]) {
            #if 0
                printf("%4zu: %016llX\n %d != %d\n", i, input[i], result, output[i]);
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
        fputs("All tests passed", stdout);
    } else {
        char buf[sizeof("Failed test: 16777215\n")];
        boot_sprintf(buf, "Failed test: %u\n", fail_index);
        fputs(buf, stdout);
    }

    while (!os_GetCSC());

    return 0;
}
