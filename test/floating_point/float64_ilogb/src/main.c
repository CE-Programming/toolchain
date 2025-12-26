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

#include "f64_ilogb_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

#if 0
#define test_printf printf
#else
#define test_printf(...)
#endif

long double truth_logbl(long double x) {
    if (isfinite(x)) {
        if (iszero(x)) {
            errno = EDOM;
            feraiseexcept(FE_DIVBYZERO);
            return -HUGE_VALL;
        }
        return (long double)ilogbl(x);
    }
    // infinity and NaN
    return fabsl(x);
}

size_t run_test(void) {
    typedef long double input_t;
    typedef int output_t;

    const size_t length = ARRAY_LENGTH(f64_ilogb_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_ilogb_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_ilogb_LUT_output);

    for (size_t i = 0; i < length; i++) {
        int result = ilogbl(input[i]);
        if (result != output[i]) {
            test_printf("%4zu: %016llX\n%d != %d\n", i, input[i], result, output[i]);
            return i;
        }

        errno = 0;
        feclearexcept(FE_ALL_EXCEPT);
        long double f_truth = truth_logbl(input[i]);
        unsigned char fe_truth = __fe_cur_env;
        int errno_truth = errno;

        errno = 0;
        feclearexcept(FE_ALL_EXCEPT);
        long double f_guess = logbl(input[i]);
        unsigned char fe_guess = __fe_cur_env;
        int errno_guess = errno;

        if (memcmp(&f_guess, &f_truth, sizeof(long double)) != 0) {
            test_printf("%4zu:\n%016llX %d\n%016llX !=\n%016llX\n", i, input[i], output[i], f_guess, f_truth);
            return i;
        }
        if (fe_guess != fe_truth) {
            puts("fenv fail");
            return i;
        }
        if (errno_guess != errno_truth) {
            puts("errno fail");
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
