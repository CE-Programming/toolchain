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
// Utility
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

#define CMP(format, x, y, truth, guess) do { \
    if (truth != guess) { \
        test_printf("I: " format "\n * " format "\nT: " format "\nG: " format "\n", x, y, truth, guess); \
        return __LINE__; \
    } \
} while(0)

#define rand8() ((uint8_t)random())

#define rand16() ((uint16_t)random())

#define rand24() ((uint24_t)random())

#define rand32() ((uint32_t)random())

static __attribute__((__always_inline__, __unused__))
uint48_t rand48(void) {
    union {
        uint48_t u48;
        struct {
            uint32_t lo32;
            uint16_t hi16;
        };
    } split;
    split.lo32 = (uint32_t)random();
    split.hi16 = (uint16_t)random();
    return split.u48;
}

static __attribute__((__always_inline__, __unused__))
uint64_t rand64(void) {
    union {
        uint64_t u64;
        struct {
            uint32_t lo32;
            uint32_t hi32;
        };
    } split;
    split.lo32 = (uint32_t)random();
    split.hi32 = (uint32_t)random();
    return split.u64;
}

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

uint16_t CRT_smulhu(uint16_t, uint16_t);
uint24_t CRT_imulhu(uint24_t, uint24_t);
uint32_t CRT_lmulhu(uint32_t, uint32_t);
uint48_t CRT_i48mulhu(uint48_t, uint48_t);
uint64_t CRT_llmulhu(uint64_t, uint64_t);

int16_t CRT_smulhs(int16_t, int16_t);
int24_t CRT_imulhs(int24_t, int24_t);
int32_t CRT_lmulhs(int32_t, int32_t);
int48_t CRT_i48mulhs(int48_t, int48_t);
int64_t CRT_llmulhs(int64_t, int64_t);

//------------------------------------------------------------------------------
// Truth
//------------------------------------------------------------------------------

static __attribute__((__always_inline__, __unused__))
uint16_t truth_smulhu(uint16_t x, uint16_t y) {
    return (uint16_t)(((uint32_t)x * (uint32_t)y) >> 16);
}

static __attribute__((__always_inline__, __unused__))
uint24_t truth_imulhu(uint24_t x, uint24_t y) {
    return (uint24_t)(((uint48_t)x * (uint48_t)y) >> 24);
}

static __attribute__((__always_inline__, __unused__))
uint32_t truth_lmulhu(uint32_t x, uint32_t y) {
    return (uint32_t)(((uint64_t)x * (uint64_t)y) >> 32);
}

static __attribute__((__always_inline__, __unused__))
uint48_t truth_i48mulhu(uint48_t x, uint48_t y) {
    const uint48_t x0 = (uint24_t)x;
    const uint48_t x1 = x >> 24;
    const uint48_t y0 = (uint24_t)y;
    const uint48_t y1 = y >> 24;
    const uint48_t p11 = x1 * y1;
    const uint48_t p01 = x0 * y1;
    const uint48_t p10 = x1 * y0;
    const uint48_t p00 = x0 * y0;
    const uint48_t middle = p10 + (p00 >> 24) + (uint24_t)p01;
    return p11 + (middle >> 24) + (p01 >> 24);
}

static __attribute__((__always_inline__, __unused__))
uint64_t truth_llmulhu(uint64_t x, uint64_t y) {
    const uint64_t x0 = (uint32_t)x;
    const uint64_t x1 = x >> 32;
    const uint64_t y0 = (uint32_t)y;
    const uint64_t y1 = y >> 32;
    const uint64_t p11 = x1 * y1;
    const uint64_t p01 = x0 * y1;
    const uint64_t p10 = x1 * y0;
    const uint64_t p00 = x0 * y0;
    const uint64_t middle = p10 + (p00 >> 32) + (uint32_t)p01;
    return p11 + (middle >> 32) + (p01 >> 32);
}

static __attribute__((__always_inline__, __unused__))
int16_t truth_smulhs(int16_t x, int16_t y) {
    return (int16_t)(((int32_t)x * (int32_t)y) >> 16);
}

static __attribute__((__always_inline__, __unused__))
int24_t truth_imulhs(int24_t x, int24_t y) {
    return (int24_t)(((int48_t)x * (int48_t)y) >> 24);
}

static __attribute__((__always_inline__, __unused__))
int32_t truth_lmulhs(int32_t x, int32_t y) {
    return (int32_t)(((int64_t)x * (int64_t)y) >> 32);
}

static __attribute__((__always_inline__, __unused__))
int48_t truth_i48mulhs(int48_t x, int48_t y) {
    int48_t result = truth_i48mulhu(x, y);
    if (x < 0) {
        result -= y;
    }
    if (y < 0) {
        result -= x;
    }
    return result;
}

static __attribute__((__always_inline__, __unused__))
int64_t truth_llmulhs(int64_t x, int64_t y) {
    int64_t result = truth_llmulhu(x, y);
    if (x < 0) {
        result -= y;
    }
    if (y < 0) {
        result -= x;
    }
    return result;
}

//------------------------------------------------------------------------------
// Registers
//------------------------------------------------------------------------------

typedef struct reg_group {
    union {
        struct {
            uint24_t HL;
            uint24_t DE;
            uint24_t BC;
        };
        struct {
            uint8_t L;
            uint8_t H;
            uint8_t UHL;
            uint8_t E;
            uint8_t D;
            uint8_t UDE;
            uint8_t C;
            uint8_t B;
            uint8_t UBC;
        };
    };
    uint8_t A;
    uint24_t IY;
    uint24_t IX;
} reg_group;
extern reg_group prev_reg;
extern reg_group next_reg;

void print_reg(void) {
    test_printf(
        "A: %02X -> %02X\n"\
        "HL: %06X -> %06X\n"\
        "DE: %06X -> %06X\n"\
        "BC: %06X -> %06X\n"\
        "IY: %06X -> %06X\n"\
        "IX: %06X -> %06X\n",
        prev_reg.A , next_reg.A ,
        prev_reg.HL, next_reg.HL,
        prev_reg.DE, next_reg.DE,
        prev_reg.BC, next_reg.BC,
        prev_reg.IY, next_reg.IY,
        prev_reg.IX, next_reg.IX
    );
}

static __attribute__((__unused__))
bool test_A_UBC_UDE_UIY_UIX(void) {
    if (
        (prev_reg.A   == next_reg.A  ) &&
        (prev_reg.BC  == next_reg.BC ) &&
        (prev_reg.DE  == next_reg.DE ) &&
        (prev_reg.IY  == next_reg.IY ) &&
        (prev_reg.IX  == next_reg.IX )
    ) {
        return true;
    }
    print_reg();
    return false;
}

static __attribute__((__unused__))
bool test_A_UBC_UD_UIY_UIX(void) {
    if (
        (prev_reg.A   == next_reg.A  ) &&
        (prev_reg.BC  == next_reg.BC ) &&
        (prev_reg.UDE == next_reg.UDE) &&
        (prev_reg.D   == next_reg.D  ) &&
        (prev_reg.IY  == next_reg.IY ) &&
        (prev_reg.IX  == next_reg.IX )
    ) {
        return true;
    }
    print_reg();
    return false;
}

static __attribute__((__unused__))
bool test_A_UBC_UIY_UIX(void) {
    if (
        (prev_reg.A   == next_reg.A  ) &&
        (prev_reg.BC  == next_reg.BC ) &&
        (prev_reg.IY  == next_reg.IY ) &&
        (prev_reg.IX  == next_reg.IX )
    ) {
        return true;
    }
    print_reg();
    return false;
}

static __attribute__((__unused__))
bool test_A_UIY_UIX(void) {
    if (
        (prev_reg.A   == next_reg.A  ) &&
        (prev_reg.IY  == next_reg.IY ) &&
        (prev_reg.IX  == next_reg.IX )
    ) {
        return true;
    }
    print_reg();
    return false;
}

//------------------------------------------------------------------------------
// Unsigned
//------------------------------------------------------------------------------

int test_smulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint16_t truth, guess, x, y;
        x = (uint16_t)rand16();
        y = (uint16_t)rand16();
        truth = truth_smulhu(x, y);
        guess = CRT_smulhu(x, y);
        CMP("%04hX", x, y, truth, guess);
        C((test_A_UBC_UDE_UIY_UIX()));
    }
    return 0;
}

int test_imulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint24_t truth, guess, x, y;
        x = (uint24_t)rand24();
        y = (uint24_t)rand24();
        truth = truth_imulhu(x, y);
        guess = CRT_imulhu(x, y);
        CMP("%06X", x, y, truth, guess);
        C((test_A_UBC_UDE_UIY_UIX()));
    }
    return 0;
}

int test_lmulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint32_t truth, guess, x, y;
        x = (uint32_t)rand32();
        y = (uint32_t)rand32();
        truth = truth_lmulhu(x, y);
        guess = CRT_lmulhu(x, y);
        CMP("%08lX", x, y, truth, guess);
        C((test_A_UBC_UD_UIY_UIX()));
    }
    return 0;
}

int test_i48mulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint48_t truth, guess, x, y;
        x = (uint48_t)rand48();
        y = (uint48_t)rand48();
        truth = truth_i48mulhu(x, y);
        guess = CRT_i48mulhu(x, y);
        CMP("%012llX", (uint64_t)x, (uint64_t)y, (uint64_t)truth, (uint64_t)guess);
        C((test_A_UBC_UIY_UIX()));
    }
    return 0;
}

int test_llmulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint64_t truth, guess, x, y;
        x = (uint64_t)rand64();
        y = (uint64_t)rand64();
        truth = truth_llmulhu(x, y);
        guess = CRT_llmulhu(x, y);
        CMP("%016llX", x, y, truth, guess);
        C((test_A_UIY_UIX()));
    }
    return 0;
}

//------------------------------------------------------------------------------
// Signed
//------------------------------------------------------------------------------

int test_smulhs(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        int16_t truth, guess, x, y;
        x = (int16_t)rand16();
        y = (int16_t)rand16();
        truth = truth_smulhs(x, y);
        guess = CRT_smulhs(x, y);
        CMP("%04hX", x, y, truth, guess);
        C((test_A_UBC_UDE_UIY_UIX()));
    }
    return 0;
}

int test_imulhs(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        int24_t truth, guess, x, y;
        x = (int24_t)rand24();
        y = (int24_t)rand24();
        truth = truth_imulhs(x, y);
        guess = CRT_imulhs(x, y);
        CMP("%06X", x, y, truth, guess);
        C((test_A_UBC_UDE_UIY_UIX()));
    }
    return 0;
}

int test_lmulhs(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        int32_t truth, guess, x, y;
        x = (int32_t)rand32();
        y = (int32_t)rand32();
        truth = truth_lmulhs(x, y);
        guess = CRT_lmulhs(x, y);
        CMP("%08lX", x, y, truth, guess);
        C((test_A_UBC_UD_UIY_UIX()));
    }
    return 0;
}

int test_i48mulhs(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        int48_t truth, guess, x, y;
        x = (int48_t)rand48();
        y = (int48_t)rand48();
        truth = truth_i48mulhs(x, y);
        guess = CRT_i48mulhs(x, y);
        CMP("%012llX", (int64_t)x, (int64_t)y, (int64_t)truth, (int64_t)guess);
        C((test_A_UBC_UIY_UIX()));
    }
    return 0;
}

int test_llmulhs(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        int64_t truth, guess, x, y;
        x = (int64_t)rand64();
        y = (int64_t)rand64();
        truth = truth_llmulhs(x, y);
        guess = CRT_llmulhs(x, y);
        CMP("%016llX", x, y, truth, guess);
        C((test_A_UIY_UIX()));
    }
    return 0;
}

//------------------------------------------------------------------------------
// Code
//------------------------------------------------------------------------------

int run_tests(void) {
    srandom(AUTOTEST_SEED);
    int ret = 0;

    TEST(test_smulhu());
    TEST(test_imulhu());
    TEST(test_lmulhu());
    TEST(test_i48mulhu());
    TEST(test_llmulhu());

    TEST(test_smulhs());
    TEST(test_imulhs());
    TEST(test_lmulhs());
    TEST(test_i48mulhs());
    TEST(test_llmulhs());

    return ret;
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
