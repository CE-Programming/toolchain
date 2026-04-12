#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>

typedef union F64Pun {
    long double flt;
    uint64_t bin;
} F64Pun;

typedef struct SqrtCase {
    uint64_t in;
    uint64_t out;
    bool out_is_nan;
} SqrtCase;

typedef struct TestResult {
    bool passed;
    size_t index;
    uint64_t in;
    uint64_t guess;
    uint64_t truth;
    bool guess_is_nan;
    bool truth_is_nan;
} TestResult;

static_assert(sizeof(long double) == sizeof(uint64_t), "unexpected long double size");

static const SqrtCase sqrt_cases[] = {
    { UINT64_C(0x0000000000000000), UINT64_C(0x0000000000000000), false },
    { UINT64_C(0x8000000000000000), UINT64_C(0x8000000000000000), false },
    { UINT64_C(0x3FF0000000000000), UINT64_C(0x3FF0000000000000), false },
    { UINT64_C(0x4010000000000000), UINT64_C(0x4000000000000000), false },
    { UINT64_C(0x4022000000000000), UINT64_C(0x4008000000000000), false },
    { UINT64_C(0x7FF0000000000000), UINT64_C(0x7FF0000000000000), false },
    { UINT64_C(0xBFF0000000000000), UINT64_C(0x0000000000000000), true  },
    { UINT64_C(0x7FF8000000000001), UINT64_C(0x0000000000000000), true  },
};

static TestResult run_test(void) {
    TestResult result = { .passed = true };

    for (size_t i = 0; i < sizeof(sqrt_cases) / sizeof(sqrt_cases[0]); i++) {
        F64Pun in = { .bin = sqrt_cases[i].in };
        F64Pun out = { .flt = sqrtl(in.flt) };

        bool guess_is_nan = isnan(out.flt);
        if ((guess_is_nan != sqrt_cases[i].out_is_nan) ||
            (!guess_is_nan && out.bin != sqrt_cases[i].out)) {
            result.passed = false;
            result.index = i;
            result.in = in.bin;
            result.guess = out.bin;
            result.truth = sqrt_cases[i].out;
            result.guess_is_nan = guess_is_nan;
            result.truth_is_nan = sqrt_cases[i].out_is_nan;
            return result;
        }
    }

    return result;
}

int main(void) {
    os_ClrHome();

    TestResult result = run_test();
    if (result.passed) {
        puts("All tests passed");
    } else {
        printf(
            "Test: %u\nI:%016llX\nG:%016llX%s\nT:%016llX%s",
            (unsigned int)result.index,
            result.in,
            result.guess,
            result.guess_is_nan ? " NaN" : "",
            result.truth,
            result.truth_is_nan ? " NaN" : ""
        );
    }

    while (!os_GetCSC()) {
    }

    return 0;
}
