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

#include "f64_to_f32_LUT.h"

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

#define RANDOM_TEST_COUNT 512

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

#define AUTOTEST_SEED 0x7184CE

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if RANDOM_TEST_COUNT < 4
#error "RANDOM_TEST_COUNT is out of range"
#endif

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;


/* debugging code */
#if DEBUG_DIAGNOSTICS

void print_failed(long double input, uint32_t guess, uint32_t truth) {
    F64_pun value;
    value.flt = input;
    printf(
        "I: %016llX -->\nG: %08lX != %08lX\n",
        value.bin, guess, truth
    );
}

#else

#define print_failed(...)

#endif

uint32_t _dtof_c(uint64_t x) {
    uint64_t mant = x & ((UINT64_C(1) << 52) - 1);
    const uint16_t biased = (x >> 52) & 0x7FF;
    const uint16_t BC = (uint16_t)((x >> 48) & 0x7FFF);
    // 879 == 0x369
    if (BC < 16 * (1023 - (126 + 24))) {
        return 0;
    }
    // 897 == 0x381
    if (BC < 16 * (1023 - 126)) {
        uint64_t norm = mant | (UINT64_C(1) << 52);
        uint8_t sub_expon = -(uint8_t)((BC - 16 * (1023 - 126)) >> 4);
        const bool sticky = norm & ((UINT64_C(1) << (sub_expon + (4 + 24))) - 1);
        norm >>= sub_expon + (4 + 24);
        const bool round = norm & 1;
        const bool guard = norm & 2;
        norm >>= 1;

        uint32_t ret = (uint32_t)norm;
        if (round && (guard || sticky)) {
            // round up to even
            ret++;
        }
        return ret;
    }
    // 1151 == 0x47F
    if (biased >= 128 + 1023) {
        #if 1
        if (biased == 0x7FF) {
            uint32_t ret = (uint32_t)(mant >> (5 + 24)) & UINT32_C(0x007FFFFF);
            #if 1
                /* Preserve NaN */
                bool low_nan = mant & ((UINT32_C(1) << (5 + 24)) - 1);
                if (low_nan) {
                    ret |= 1;
                }
            #else
                /* Signal NaN */
                ret |= (UINT32_C(1) << 22);
            #endif
            ret |= UINT32_C(0x7F800000);
            return ret;
        }
        #endif
        return UINT32_C(0x7F800000);
    }
    // result is normal or rounds to infinity
    const bool sticky = mant & ((UINT64_C(1) << (4 + 24)) - 1);
    const bool round = mant & (UINT64_C(1) << (4 + 24));
    const bool guard = mant & (UINT64_C(1) << (5 + 24));
    mant >>= (5 + 24);
    uint32_t ret = (uint32_t)mant;
    // -896 == -0x380
    uint16_t new_expon = biased + (uint16_t)(127 - 1023);
    ret |= (uint32_t)new_expon << 23;
    // we round afterwards incase we round up to the next exponent
    if (round && (guard || sticky)) {
        // round up to even
        ret++;
    }
    return ret;
}

float dtof(long double x_flt) {
    F64_pun x;
    F32_pun y;
    #if 1
        x.flt = fabsl(x_flt);
        y.bin = _dtof_c(x.bin);
        if (signbit(x_flt)) {
            y.bin ^= (UINT32_C(1) << 31);
        }
    #else
        x.flt_part = x_flt;
        y.u32_part = _dtof_c(x.u64_part);
    #endif
    return y.flt;
}

static uint64_t rand_u64(void) {
    union {
        uint64_t u64;
        uint16_t u16[4];
    } split;
    #if 1
        split.u16[0] = (uint16_t)rand();
        split.u16[1] = (uint16_t)rand();
        split.u16[2] = (uint16_t)rand();
    #else
        split.u16[0] = (uint16_t)rand() & 0x0001;
        split.u16[1] = (uint16_t)rand() & 0xFF00;
        split.u16[2] = (uint16_t)rand() & 0x8000;
    #endif
    #if 0
        split.u16[3] = (uint16_t)rand() | 0x3E60;
    #elif 0
        split.u16[3] = ((unsigned)rand() % (0x4820 - 0x3660)) + 0x3660;
    #else
        split.u16[3] = ((unsigned)rand() % (0x3840 - 0x3660)) + 0x3660;
    #endif

    return split.u64;
}

void brute_force_test(void) {
    srand(AUTOTEST_SEED);
    for (size_t i = 0; i < RANDOM_TEST_COUNT; i++) {
        F64_pun x;
        F32_pun t;
        F32_pun g;
        x.bin = rand_u64();
        g.flt = (float)x.flt;
        t.flt = dtof(x.flt);
        if (g.bin != t.bin) {
            print_failed(x.flt, g.bin, t.bin);
            if (!(isnan(g.flt) && isnan(t.flt))) {
                return;
            }
        }
    }
    puts("Passed random tests");
}

size_t run_test(void) {
    typedef long double input_t;
    typedef F32_pun output_t;

    const size_t length = ARRAY_LENGTH(f64_to_f32_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_to_f32_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_to_f32_LUT_output);

    F32_pun result;
    for (size_t i = 0; i < length; i++) {
        result.flt = (float)input[i];
        if (result.bin != output[i].bin) {
            if (!(isnan(result.flt) && isnan(output[i].flt))) {
                print_failed(input[i], result.bin, output[i].bin);
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
        puts("Passed edge cases");
    } else {
        char buf[sizeof("Failed test: 16777215")];
        boot_sprintf(buf, "Failed test: %u", fail_index);
        puts(buf);
    }
    brute_force_test();

    while (!os_GetCSC());

    return 0;
}
