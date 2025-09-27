#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include "f32_ilogb_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

#if 0
#define test_printf printf
#else
#define test_printf(...)
#endif

float truth_logbf(float x) {
    if (isfinite(x)) {
        if (iszero(x)) {
            errno = EDOM;
            feraiseexcept(FE_DIVBYZERO);
            return -HUGE_VALF;
        }
        return (float)ilogbf(x);
    }
    // infinity and NaN
    return fabsf(x);
}

size_t run_test(void) {
    typedef float input_t;
    typedef int output_t;

    const size_t length = ARRAY_LENGTH(f32_ilogb_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_ilogb_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_ilogb_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int result = ilogbf(input[i]);
        if (result != output[i]) {
            test_printf("%3zu: %08lX\n%d != %d\n", i, input[i], result, output[i]);
            return i;
        }

        errno = 0;
        feclearexcept(FE_ALL_EXCEPT);
        float f_truth = truth_logbf(input[i]);
        unsigned char fe_truth = __fe_cur_env;
        int errno_truth = errno;

        errno = 0;
        feclearexcept(FE_ALL_EXCEPT);
        float f_guess = logbf(input[i]);
        unsigned char fe_guess = __fe_cur_env;
        int errno_guess = errno;

        if (memcmp(&f_guess, &f_truth, sizeof(float)) != 0) {
            test_printf("%3zu: %08lX %d\n%08lX != %08lX\n", i, input[i], output[i], f_guess, f_truth);
            return i;
        }
        if (fe_guess != fe_truth) {
            fputs("fenv fail\n", stdout);
            return i;
        }
        if (errno_guess != errno_truth) {
            fputs("errno fail\n", stdout);
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
