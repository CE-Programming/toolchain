#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <fenv.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdlib.h>
#include <ti/sprintf.h>

#include "f64_from_integer_LUT.h"

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

#define AUTOTEST_DEBUG 0

/* (u)int24_t variants of (u)ltod */
#define TEST_UITOD 0

/* tests FE_INEXACT in (u)lltod */
#define TEST_FENV 0

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

#ifndef AUTOTEST_DEBUG
#error "AUTOTEST_DEBUG must be defined to 0 or 1"
#endif

#ifndef TEST_UITOD
#error "TEST_UITOD must be defined to 0 or 1"
#endif

#ifndef TEST_FENV
#error "TEST_FENV must be defined to 0 or 1"
#endif

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#if AUTOTEST_DEBUG
void print_failed(uint64_t input, uint64_t guess, uint64_t truth) {
    printf(
        "I: %016llX -->\nG: %016llX !=\nT: %016llX\n",
        input, guess, truth
    );
}
#define test_printf printf
#else
#define print_failed(...)
#define test_printf(...)
#endif

long double CRT_uitod(unsigned int);
long double CRT_itod(signed int);

void clear_fe_cur_env(void);
unsigned char get_fe_cur_env(void);

size_t run_test(const char** failed_func) {
    typedef struct { uint32_t u32; uint64_t u64; } input_t;
    typedef struct { F64_pun fu32; F64_pun fi32; F64_pun fu64; F64_pun fi64; } output_t;

    const size_t length = ARRAY_LENGTH(f64_from_integer_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_from_integer_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_from_integer_LUT_output);

    for (size_t i = 0; i < length; i++) {
        F64_pun result;

        result.flt = (long double)((uint32_t)input[i].u32);
        if (result.bin != output[i].fu32.bin) {
            print_failed((uint64_t)input[i].u32, result.bin, output[i].fu32.bin);
            *failed_func = "ultod";
            return i;
        }

        result.flt = (long double)((int32_t)input[i].u32);
        if (result.bin != output[i].fi32.bin) {
            print_failed((uint64_t)input[i].u32, result.bin, output[i].fi32.bin);
            *failed_func = "ltod";
            return i;
        }

        #if TEST_UITOD
            if ((uint32_t)input[i].u32 <= UINT24_MAX) {
                result.flt = CRT_uitod((uint24_t)input[i].u32);
                if (result.bin != output[i].fu32.bin) {
                    print_failed((uint64_t)input[i].u32, result.bin, output[i].fu32.bin);
                    *failed_func = "uitod";
                    return i;
                }
            }

            if ((int32_t)input[i].u32 >= INT24_MIN && (int32_t)input[i].u32 <= INT24_MAX) {
                result.flt = CRT_itod((int24_t)input[i].u32);
                if (result.bin != output[i].fi32.bin) {
                    print_failed((uint64_t)input[i].u32, result.bin, output[i].fi32.bin);
                    *failed_func = "itod";
                    return i;
                }
            }
        #endif /* TEST_UITOD */

        {
            clear_fe_cur_env();
            result.flt = (long double)((uint64_t)input[i].u64);
            if (result.bin != output[i].fu64.bin) {
                print_failed((uint64_t)input[i].u64, result.bin, output[i].fu64.bin);
                *failed_func = "ulltod";
                return i;
            }
            #if TEST_FENV
                unsigned char fe_env = get_fe_cur_env();
                bool rounding_occured = ((uint64_t)output[i].fu64.flt != (uint64_t)input[i].u64);
                bool inexact_raised = (fe_env & FE_INEXACT);
                if (rounding_occured != inexact_raised) {
                    test_printf(
                        "%zu: FE: %02X\nI: %016llX\nO: %016llX\n",
                        i, fe_env,
                        input[i].u64, output[i].fu64.bin
                    );
                    *failed_func = "ulltod";
                    puts("fenv");
                    return i;
                }
            #endif /* TEST_FENV */
        }

        {
            clear_fe_cur_env();
            result.flt = (long double)((int64_t)input[i].u64);
            if (result.bin != output[i].fi64.bin) {
                print_failed((uint64_t)input[i].u64, result.bin, output[i].fi64.bin);
                *failed_func = "lltod";
                return i;
            }
            #if TEST_FENV
                unsigned char fe_env = get_fe_cur_env();
                bool rounding_occured = ((int64_t)output[i].fi64.flt != (int64_t)input[i].u64);
                bool inexact_raised = (fe_env & FE_INEXACT);
                if (rounding_occured != inexact_raised) {
                    test_printf(
                        "%zu: FE: %02X\nI: %016llX\nO: %016llX\n",
                        i, fe_env,
                        input[i].u64, output[i].fu64.bin
                    );
                    *failed_func = "lltod";
                    puts("fenv");
                    return i;
                }
            #endif /* TEST_FENV */
        }
    }

    /* passed all */
    *failed_func = "none";
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    const char* failed_func;
    size_t fail_index = run_test(&failed_func);
    if (fail_index == SIZE_MAX) {
        puts("All tests passed");
    } else {
        char buf[sizeof("Failed test: 16777215\n")];
        boot_sprintf(buf, "Failed test: %u", fail_index);
        puts(buf);
        puts(failed_func);
    }

    while (!os_GetCSC());

    return 0;
}
