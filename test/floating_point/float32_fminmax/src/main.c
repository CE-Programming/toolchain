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

#if 0
#define test_printf printf
#else
#define test_printf(...)
#endif

#include "f32_fminmax_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

size_t run_test(void) {
    typedef struct { F32_pun x; F32_pun y; } input_t;
    typedef struct { F32_pun f_min; F32_pun f_max; } output_t;

    const size_t length = ARRAY_LENGTH(f32_fminmax_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f32_fminmax_LUT_input );
    const output_t *output = (const output_t*)((const void*)f32_fminmax_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F32_pun f_min;
        F32_pun f_max;
        f_min.flt = fminf(input[i].x.flt, input[i].y.flt);
        f_max.flt = fmaxf(input[i].x.flt, input[i].y.flt);

        if (f_min.bin != output[i].f_min.bin || f_max.bin != output[i].f_max.bin) {
            if (
                !(
                    isnan(f_min.flt) && isnan(output[i].f_min.flt) &&
                    isnan(f_max.flt) && isnan(output[i].f_max.flt)
                )
            ) {
                test_printf(
                    "%zu:\nI: %08lX : %08lX\nG: %08lX < %08lX\nT: %08lX < %08lX\n",
                    i,
                    input[i].x.bin, input[i].y.bin,
                    f_min.bin, f_max.bin,
                    output[i].f_min.bin, output[i].f_max.bin
                );
                return i;
            }
        }
    }

    /* passed all */
    return SIZE_MAX;
}

#ifdef __cplusplus
extern "C" {
    int main(void);
}
#endif /* __cplusplus */

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
