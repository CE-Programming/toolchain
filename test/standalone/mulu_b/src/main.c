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
        test_printf("I: " format " * %02X\nT: " format "\nG: " format "\n", x, y, truth, guess); \
        return __LINE__; \
    } \
} while(0)

static_assert(RAND_MAX == INT_MAX, "RAND_MAX has changed");

#define rand8() ((uint8_t)rand())

#define rand16() ((uint16_t)rand())

__attribute__((__unused__)) static uint24_t rand24(void) {
    union {
        uint24_t u24;
        struct {
            uint16_t lo16;
            uint8_t hi8;
        } part;
    } split;
    split.part.lo16 = (uint16_t)rand();
    split.part.hi8 = (uint8_t)rand();
    return split.u24;
}

__attribute__((__unused__)) static uint32_t rand32(void) {
    union {
        uint32_t u32;
        uint16_t u16[2];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    return split.u32;
}

__attribute__((__unused__)) static uint48_t rand48(void) {
    union {
        uint48_t u48;
        uint16_t u16[3];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    return split.u48;
}

__attribute__((__unused__)) static uint64_t rand64(void) {
    union {
        uint64_t u64;
        uint16_t u16[4];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    split.u16[3] = (uint16_t)rand();
    return split.u64;
}

uint16_t CRT_smulu_b(uint16_t, uint8_t);
uint16_t CRT_smulu_b_fast(uint16_t, uint8_t);

uint24_t CRT_imulu_b(uint24_t, uint8_t);
uint24_t CRT_imulu_b_fast(uint24_t, uint8_t);

uint32_t CRT_lmulu_b(uint32_t, uint8_t);
uint32_t CRT_lmulu_b_fast(uint32_t, uint8_t);

uint64_t CRT_llmulu_b(uint64_t, uint8_t);

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
    // uint24_t IX;
    // uint24_t IY;
} reg_group;
extern reg_group prev_reg;
extern reg_group next_reg;

void print_reg(void) {
    test_printf(
        "A: %02X -> %02X\n"\
        "HL: %06X -> %06X\n"\
        "BC: %06X -> %06X\n"\
        "DE: %06X -> %06X\n",
        prev_reg.A , next_reg.A ,
        prev_reg.HL, next_reg.HL,
        prev_reg.DE, next_reg.DE,
        prev_reg.BC, next_reg.BC
    );
}

static bool test_A_UBC_UDE(void) {
    if (
        (prev_reg.A   == next_reg.A  ) &&
        (prev_reg.BC  == next_reg.BC ) &&
        (prev_reg.DE  == next_reg.DE )
    ) {
        return true;
    }
    print_reg();
    return false;
}

static bool test_A_UBC_UD(void) {
    if (
        (prev_reg.A   == next_reg.A  ) &&
        (prev_reg.BC  == next_reg.BC ) &&
        (prev_reg.UDE == next_reg.UDE) &&
        (prev_reg.D   == next_reg.D  )
    ) {
        return true;
    }
    print_reg();
    return false;
}

static bool test_A(void) {
    if (prev_reg.A == next_reg.A) {
        return true;
    }
    print_reg();
    return false;
}

int test_smulu_b(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint16_t truth, guess, x;
        uint8_t y;
        x = rand16();
        y = rand8();
        truth = x * (uint16_t)y;
        guess = CRT_smulu_b(x, y);
        CMP("%04X", x, y, truth, guess);
        C((test_A_UBC_UDE()));
    }
    return 0;
}

int test_smulu_b_fast(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint16_t truth, guess, x;
        uint8_t y;
        x = rand16();
        y = rand8();
        truth = x * (uint16_t)y;
        guess = CRT_smulu_b_fast(x, y);
        CMP("%04X", x, y, truth, guess);
    }
    return 0;
}

int test_imulu_b(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint24_t truth, guess, x;
        uint8_t y;
        x = rand24();
        y = rand8();
        truth = x * (uint24_t)y;
        guess = CRT_imulu_b(x, y);
        CMP("%06X", x, y, truth, guess);
        C((test_A_UBC_UDE()));
    }
    return 0;
}

int test_imulu_b_fast(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint24_t truth, guess, x;
        uint8_t y;
        x = rand24();
        y = rand8();
        truth = x * (uint24_t)y;
        guess = CRT_imulu_b_fast(x, y);
        CMP("%06X", x, y, truth, guess);
    }
    return 0;
}

int test_lmulu_b(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint32_t truth, guess, x;
        uint8_t y;
        x = rand32();
        y = rand8();
        truth = x * (uint32_t)y;
        guess = CRT_lmulu_b(x, y);
        CMP("%08lX", x, y, truth, guess);
        C((test_A_UBC_UD()));
    }
    return 0;
}

int test_lmulu_b_fast(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint32_t truth, guess, x;
        uint8_t y;
        x = rand32();
        y = rand8();
        truth = x * (uint32_t)y;
        guess = CRT_lmulu_b_fast(x, y);
        CMP("%08lX", x, y, truth, guess);
    }
    return 0;
}

int test_llmulu_b(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint64_t truth, guess, x;
        uint8_t y;
        x = rand64();
        y = rand8();
        truth = x * (uint64_t)y;
        guess = CRT_llmulu_b(x, y);
        CMP("%016llX", x, y, truth, guess);
        C((test_A()));
    }
    return 0;
}

int run_tests(void) {
    srand(AUTOTEST_SEED);
    int ret = 0;
    TEST(test_smulu_b());
    TEST(test_smulu_b_fast());
    TEST(test_imulu_b());
    TEST(test_imulu_b_fast());
    TEST(test_lmulu_b());
    TEST(test_lmulu_b_fast());
    TEST(test_llmulu_b());

    return ret;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
