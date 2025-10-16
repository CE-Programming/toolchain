#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ti/sprintf.h>
#include <ez80_builtin.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

#define RANDOM_TEST_COUNT 256

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

#define AUTOTEST_SEED 0x7184CE

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

#define C(expr) if (!(expr)) { return __LINE__; }

#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if RANDOM_TEST_COUNT < 4
#error "RANDOM_TEST_COUNT is out of range"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

static_assert(RAND_MAX == INT_MAX, "RAND_MAX has changed");

#define rand8() ((int8_t)rand())

#define rand16() ((int16_t)rand())

__attribute__((__unused__)) static int24_t rand24(void) {
    union {
        int24_t u24;
        struct {
            uint16_t lo16;
            uint8_t hi8;
        } part;
    } split;
    split.part.lo16 = (uint16_t)rand();
    split.part.hi8 = (uint8_t)rand();
    return split.u24;
}

__attribute__((__unused__)) static int32_t rand32(void) {
    union {
        int32_t u32;
        uint16_t u16[2];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    return split.u32;
}

__attribute__((__unused__)) static int48_t rand48(void) {
    union {
        int48_t u48;
        uint16_t u16[3];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    return split.u48;
}

__attribute__((__unused__)) static int64_t rand64(void) {
    union {
        int64_t u64;
        uint16_t u16[4];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    split.u16[3] = (uint16_t)rand();
    return split.u64;
}

static bool test_i48div(int48_t x, int48_t y) {
    if (y == 0) {
        // division by zero
        return true;
    }
    lldiv_t truth = lldiv((int64_t)x, (int64_t)y);
    i48div_t guess = i48div(x, y);
    if (
        ((uint48_t)truth.quot != (uint48_t)guess.quot) ||
        ((uint48_t)truth.rem != (uint48_t)guess.rem)
    ) {
        test_printf(
            "XN: %012llX\nYD: %012llX\n"\
            "GQ: %012llX\nGR: %012llX\n"\
            "TQ: %012llX\nTR: %012llX\n",
            (uint64_t)(uint48_t)x         , (uint64_t)(uint48_t)y,
            (uint64_t)(uint48_t)guess.quot, (uint64_t)(uint48_t)guess.rem,
            (uint64_t)(uint48_t)truth.quot, (uint64_t)(uint48_t)truth.rem
        );
        return false;
    }
    return true;
}

int run_tests(void) {
    srand(AUTOTEST_SEED);

    C(test_i48div(         0,          1));
    C(test_i48div(         1,          1));
    C(test_i48div(        -1,          1));
    C(test_i48div( INT48_MAX,          1));
    C(test_i48div(-INT48_MAX,          1));
    C(test_i48div( INT48_MIN,          1));
    C(test_i48div(         0,         -1));
    C(test_i48div(         1,         -1));
    C(test_i48div(        -1,         -1));
    C(test_i48div( INT48_MAX,         -1));
    C(test_i48div(-INT48_MAX,         -1));
    C(test_i48div( INT48_MIN,         -1));
    C(test_i48div(         0,  INT48_MAX));
    C(test_i48div(         1,  INT48_MAX));
    C(test_i48div(        -1,  INT48_MAX));
    C(test_i48div(         0, -INT48_MAX));
    C(test_i48div(         1, -INT48_MAX));
    C(test_i48div(        -1, -INT48_MAX));
    C(test_i48div(         0,  INT48_MIN));
    C(test_i48div(         1,  INT48_MIN));
    C(test_i48div(        -1,  INT48_MIN));
    C(test_i48div( INT48_MAX,  INT48_MAX));
    C(test_i48div( INT48_MAX, -INT48_MAX));
    C(test_i48div( INT48_MAX,  INT48_MIN));
    C(test_i48div(-INT48_MAX,  INT48_MAX));
    C(test_i48div(-INT48_MAX, -INT48_MAX));
    C(test_i48div(-INT48_MAX,  INT48_MIN));
    C(test_i48div( INT48_MIN,  INT48_MAX));
    C(test_i48div( INT48_MIN, -INT48_MAX));
    C(test_i48div( INT48_MIN,  INT48_MIN));

    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        if (!test_i48div(rand48(), rand48())) {
            return __LINE__;
        }
    }

    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        if (!test_i48div(rand48(), rand24())) {
            return __LINE__;
        }
    }

    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        if (!test_i48div(rand48(), rand8())) {
            return __LINE__;
        }
    }
    
    return 0;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608\n")];
        boot_sprintf(buf, "Failed test L%d\n", failed_test);
        fputs(buf, stdout);
    } else {
        fputs("All tests passed", stdout);
    }

    while (!os_GetCSC());

    return 0;
}
