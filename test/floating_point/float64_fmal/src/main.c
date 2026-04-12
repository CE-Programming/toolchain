#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>

typedef union F64Pun {
    long double flt;
    uint64_t bin;
} F64Pun;

typedef struct FmaCase {
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t out;
    bool out_is_nan;
} FmaCase;

typedef struct TestResult {
    bool passed;
    size_t index;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t guess;
    uint64_t truth;
    bool guess_is_nan;
    bool truth_is_nan;
} TestResult;

static_assert(sizeof(long double) == sizeof(uint64_t), "unexpected long double size");

static const FmaCase fma_cases[] = {
    { UINT64_C(0x4001A88609EA30AA), UINT64_C(0x3FE2788CFC6FB619), UINT64_C(0x4001A88609EA30AA), UINT64_C(0x400BD9D732BA4A3C), false },
    { UINT64_C(0x3FF8000000000000), UINT64_C(0x4000000000000000), UINT64_C(0x3FF0000000000000), UINT64_C(0x4010000000000000), false },
    { UINT64_C(0xBFF8000000000000), UINT64_C(0x4000000000000000), UINT64_C(0x3FF0000000000000), UINT64_C(0xC000000000000000), false },
    { UINT64_C(0x3FF8000000000000), UINT64_C(0xC000000000000000), UINT64_C(0x3FF0000000000000), UINT64_C(0xC000000000000000), false },
    { UINT64_C(0xBFF8000000000000), UINT64_C(0xC000000000000000), UINT64_C(0xBFF0000000000000), UINT64_C(0x4000000000000000), false },
    { UINT64_C(0x4008000000000000), UINT64_C(0x3FF0000000000000), UINT64_C(0xBFF0000000000000), UINT64_C(0x4000000000000000), false },
};

static TestResult run_test(void) {
    TestResult result = { .passed = true };

    for (size_t i = 0; i < sizeof(fma_cases) / sizeof(fma_cases[0]); i++) {
        F64Pun x = { .bin = fma_cases[i].x };
        F64Pun y = { .bin = fma_cases[i].y };
        F64Pun z = { .bin = fma_cases[i].z };
        F64Pun out = { .flt = fmal(x.flt, y.flt, z.flt) };

        bool guess_is_nan = isnan(out.flt);
        if ((guess_is_nan != fma_cases[i].out_is_nan) ||
            (!guess_is_nan && out.bin != fma_cases[i].out)) {
            result.passed = false;
            result.index = i;
            result.x = x.bin;
            result.y = y.bin;
            result.z = z.bin;
            result.guess = out.bin;
            result.truth = fma_cases[i].out;
            result.guess_is_nan = guess_is_nan;
            result.truth_is_nan = fma_cases[i].out_is_nan;
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
            "Test: %u\nX:%016llX\nY:%016llX\nZ:%016llX\nG:%016llX%s\nT:%016llX%s",
            (unsigned int)result.index,
            result.x,
            result.y,
            result.z,
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
