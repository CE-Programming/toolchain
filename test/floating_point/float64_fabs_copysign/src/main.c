#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <ti/getcsc.h>
#include <ti/screen.h>

typedef union F64Pun {
    long double flt;
    uint64_t bin;
} F64Pun;

typedef enum OpKind {
    OP_FABS,
    OP_COPYSIGN,
} OpKind;

typedef struct TestCase {
    OpKind op;
    uint64_t x;
    uint64_t y;
    uint64_t out;
    bool out_is_nan;
} TestCase;

typedef struct TestResult {
    bool passed;
    size_t index;
    OpKind op;
    uint64_t x;
    uint64_t y;
    uint64_t guess;
    uint64_t truth;
    bool guess_is_nan;
    bool truth_is_nan;
} TestResult;

static const TestCase test_cases[] = {
    { OP_FABS,     UINT64_C(0x8000000000000000), UINT64_C(0),                  UINT64_C(0x0000000000000000), false },
    { OP_FABS,     UINT64_C(0xC00921FB54442D18), UINT64_C(0),                  UINT64_C(0x400921FB54442D18), false },
    { OP_FABS,     UINT64_C(0xFFF0000000000000), UINT64_C(0),                  UINT64_C(0x7FF0000000000000), false },
    { OP_FABS,     UINT64_C(0xFFF8000000000001), UINT64_C(0),                  UINT64_C(0),                  true  },
    { OP_COPYSIGN, UINT64_C(0x400921FB54442D18), UINT64_C(0xBFF0000000000000), UINT64_C(0xC00921FB54442D18), false },
    { OP_COPYSIGN, UINT64_C(0xC00921FB54442D18), UINT64_C(0x3FF0000000000000), UINT64_C(0x400921FB54442D18), false },
    { OP_COPYSIGN, UINT64_C(0x0000000000000000), UINT64_C(0x8000000000000000), UINT64_C(0x8000000000000000), false },
    { OP_COPYSIGN, UINT64_C(0x8000000000000000), UINT64_C(0x0000000000000000), UINT64_C(0x0000000000000000), false },
    { OP_COPYSIGN, UINT64_C(0x7FF0000000000000), UINT64_C(0x8000000000000000), UINT64_C(0xFFF0000000000000), false },
    { OP_COPYSIGN, UINT64_C(0x7FF8000000001234), UINT64_C(0x8000000000000000), UINT64_C(0),                  true  },
};

static TestResult run_test(void) {
    TestResult result = { .passed = true };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        F64Pun x = { .bin = test_cases[i].x };
        F64Pun y = { .bin = test_cases[i].y };
        F64Pun out;

        if (test_cases[i].op == OP_FABS) {
            out.flt = fabsl(x.flt);
        } else {
            out.flt = copysignl(x.flt, y.flt);
        }

        bool guess_is_nan = isnan(out.flt);
        if ((guess_is_nan != test_cases[i].out_is_nan) ||
            (!guess_is_nan && out.bin != test_cases[i].out)) {
            result.passed = false;
            result.index = i;
            result.op = test_cases[i].op;
            result.x = x.bin;
            result.y = y.bin;
            result.guess = out.bin;
            result.truth = test_cases[i].out;
            result.guess_is_nan = guess_is_nan;
            result.truth_is_nan = test_cases[i].out_is_nan;
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
            "Test: %u %s\nX:%016llX\nY:%016llX\nG:%016llX%s\nT:%016llX%s",
            (unsigned int)result.index,
            result.op == OP_FABS ? "fabs" : "cpy",
            result.x,
            result.y,
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
