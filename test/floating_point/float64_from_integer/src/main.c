#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdlib.h>
#include <ti/sprintf.h>

#include "f64_from_integer_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define AUTOTEST_DEBUG 0

#ifndef AUTOTEST_DEBUG
#define AUTOTEST_DEBUG 0
#endif

#if AUTOTEST_DEBUG
void print_failed(uint64_t input, uint64_t guess, uint64_t truth) {
    printf(
        "I: %016llX -->\nG: %016llX !=\nT: %016llX\n",
        input, guess, truth
    );
}
#else
#define print_failed(...)
#endif

long double CRT_utod(unsigned int);
long double CRT_itod(signed int);

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

        if ((uint32_t)input[i].u32 <= UINT24_MAX) {
            result.flt = CRT_utod((uint24_t)input[i].u32);
            if (result.bin != output[i].fu32.bin) {
                print_failed((uint64_t)input[i].u32, result.bin, output[i].fu32.bin);
                *failed_func = "utod";
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

        result.flt = (long double)((uint64_t)input[i].u64);
        if (result.bin != output[i].fu64.bin) {
            print_failed((uint64_t)input[i].u64, result.bin, output[i].fu64.bin);
            *failed_func = "ulltod";
            return i;
        }

        result.flt = (long double)((int64_t)input[i].u64);
        if (result.bin != output[i].fi64.bin) {
            print_failed((uint64_t)input[i].u64, result.bin, output[i].fi64.bin);
            *failed_func = "lltod";
            return i;
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
        fputs("All tests passed", stdout);
    } else {
        char buf[sizeof("Failed test: 16777215\n")];
        boot_sprintf(buf, "Failed test: %u\n", fail_index);
        fputs(buf, stdout);
        fputs(failed_func, stdout);
    }

    while (!os_GetCSC());

    return 0;
}
