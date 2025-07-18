#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <fenv.h>
#include <errno.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include "f32_ldexp_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
    struct {
        uint24_t mant;
        uint8_t expon;
    };
} F32_pun;

#if 0
#define test_printf printf
#else
#define test_printf(...)
#endif

size_t run_test(void) {
    typedef struct { F32_pun value; int expon; } input_t;
    typedef F32_pun output_t;

    const size_t length = ARRAY_LENGTH(f32_ldexp_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_ldexp_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_ldexp_LUT_output);
    for (size_t i = 0; i < length; i++) {
        feclearexcept(FE_ALL_EXCEPT);
        errno = 0;
        F32_pun result;
        result.flt = ldexpf(input[i].value.flt, input[i].expon);
        if (result.bin != output[i].bin) {
            if (
                /* ignore NaN's with differing payloads */
                (!(isnan(result.flt) && isnan(output[i].flt)))
                #if 1
                    /* treat signed zeros as equal for now */
                    && (!((result.bin == 0) && (output[i].bin == UINT32_C(0x80000000))))
                #endif
            ) {
                test_printf(
                    "%zu:\nI: %08lX %+d\nG: %08lX\nT: %08lX\n",
                    i, input[i].value.bin, input[i].expon,
                    result.bin, output[i].bin
                );
                return i;
            }
        }
        /* test exceptions */
        if (!(isnan(input[i].value.flt) || isnan(output[i].flt))) {
            int temp;
            F32_pun mant_0, mant_1;
            mant_0.flt = frexpf(fabsf(input[i].value.flt), &temp);
            mant_1.flt = frexpf(fabsf(output[i].flt     ), &temp);
            bool inexact_raised = fetestexcept(FE_INEXACT);
            bool mant_equal = (mant_0.bin == mant_1.bin);
            bool became_zero = (mant_0.bin != 0 && mant_1.bin == 0);
            bool became_infinite = (mant_0.bin != UINT32_C(0x7F800000) && mant_1.bin == UINT32_C(0x7F800000));
            if (!((mant_equal != inexact_raised) && ((became_zero || became_infinite) == (errno == ERANGE)))) {
                test_printf(
                    "%zu: FE: %02X errno: %d\nI: %08lX %+d\nO: %08lX\n",
                    i, (unsigned int)__fe_cur_env, errno,
                    input[i].value.bin, input[i].expon, output[i].bin
                );
                fputs("fenv/errno\n", stdout);
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
