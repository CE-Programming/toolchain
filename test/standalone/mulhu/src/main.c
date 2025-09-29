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

__attribute__((__unused__)) static uint48_t rand48(void) {
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

__attribute__((__unused__)) static uint64_t rand64(void) {
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

uint16_t CRT_smulhu(uint16_t, uint16_t);
uint24_t CRT_imulhu(uint24_t, uint24_t);
uint32_t CRT_lmulhu(uint32_t, uint32_t);
uint48_t CRT_i48mulhu(uint48_t, uint48_t);
uint64_t CRT_llmulhu(uint64_t, uint64_t);

static __attribute__((__unused__))
uint16_t truth_smulhu(uint16_t x, uint16_t y) {
    return (uint16_t)(((uint32_t)x * (uint32_t)y) >> 16);
}

static __attribute__((__unused__))
uint24_t truth_imulhu(uint24_t x, uint24_t y) {
    return (uint24_t)(((uint48_t)x * (uint48_t)y) >> 24);
}

static __attribute__((__unused__))
uint32_t truth_lmulhu(uint32_t x, uint32_t y) {
    return (uint32_t)(((uint64_t)x * (uint64_t)y) >> 32);
}

static __attribute__((__unused__))
uint48_t truth_i48mulhu(uint48_t x, uint48_t y) {
    const uint48_t x_hi = (x >> 24);
    const uint48_t y_hi = (y >> 24);
    const uint48_t x_lo = (x & UINT24_MAX);
    const uint48_t y_lo = (y & UINT24_MAX);
    uint48_t result = x_lo * y_lo;
    result >>= 24;
    result += x_hi * y_lo + x_lo * y_hi;
    result >>= 24;
    result += x_hi * y_hi;
    return result;
}

static __attribute__((__unused__))
uint64_t truth_llmulhu(uint64_t x, uint64_t y) {
    const uint64_t x_hi = (x >> 32);
    const uint64_t y_hi = (y >> 32);
    const uint64_t x_lo = (x & UINT32_MAX);
    const uint64_t y_lo = (y & UINT32_MAX);
    uint64_t result = x_lo * y_lo;
    result >>= 32;
    result += x_hi * y_lo + x_lo * y_hi;
    result >>= 32;
    result += x_hi * y_hi;
    return result;
}

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

__attribute__((__unused__))
static bool test_A_UBC_UDE_UIY_UIX(void) {
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

__attribute__((__unused__))
static bool test_A_UBC_UD_UIY_UIX(void) {
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

__attribute__((__unused__))
static bool test_A_UBC_UIY_UIX(void) {
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

__attribute__((__unused__))
static bool test_A_UIY_UIX(void) {
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

int test_smulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint16_t truth, guess, x, y;
        x = rand16();
        y = rand16();
        truth = truth_smulhu(x, y);
        guess = CRT_smulhu(x, y);
        CMP("%04X", x, y, truth, guess);
        C((test_A_UBC_UDE_UIY_UIX()));
    }
    return 0;
}

int test_imulhu(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint24_t truth, guess, x, y;
        x = rand24();
        y = rand24();
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
        x = rand32();
        y = rand32();
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
        x = rand48();
        y = rand48();
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
        x = rand64();
        y = rand64();
        truth = truth_llmulhu(x, y);
        guess = CRT_llmulhu(x, y);
        CMP("%016llX", x, y, truth, guess);
        C((test_A_UIY_UIX()));
    }
    return 0;
}

int run_tests(void) {
    srandom(AUTOTEST_SEED);
    int ret = 0;
    TEST(test_smulhu());
    TEST(test_imulhu());
    TEST(test_lmulhu());
    TEST(test_i48mulhu());
    TEST(test_llmulhu());

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
