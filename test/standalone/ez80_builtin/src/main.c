#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <assert.h>
#include <stdio.h>
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

#define RANDOM_TEST_COUNT 128

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

#if RANDOM_TEST_COUNT < 4 || RANDOM_TEST_COUNT > 65535
#error "RANDOM_TEST_COUNT is out of range"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

#define CMP(format, input, truth, guess) do { \
    if (truth != guess) { \
        test_printf("I: " format "\nT: %d\nG: %d\n", input, truth, guess); \
        return __LINE__; \
    } \
} while(0)

#define EQ_U48(truth, guess)  do { \
    uint48_t t = truth; \
    uint48_t g = guess; \
    if (memcmp(&t, &g, sizeof(uint48_t))) { return __LINE__; } \
} while(0)

static_assert(RAND_MAX == INT_MAX, "rand() has changed");

#define rand8() ((uint8_t)rand())

#define rand16() ((uint16_t)rand())

static uint24_t rand24(void) {
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

#if 0
static uint48_t rand48(void) {
    union {
        uint48_t u48;
        uint16_t u16[3];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    return split.u48;
}
#else
static uint64_t rand48(void) {
    union {
        uint64_t u48;
        uint16_t u16[4];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    split.u16[3] = 0;
    return split.u48;
}
#endif

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

static int test_clzc(void) {
    unsigned char truth, guess;
    unsigned char input;
    for (int i = 0; i < 256; i ++)  {
        input = (unsigned char)i;
        truth = (input == 0) ? 8 : (unsigned char)(__builtin_clz((unsigned int)input) - 16);
        guess = __ez80_clzc(input);
        CMP("%d", input, truth, guess);
    }
    return 0;
}

static int test_ctzc(void) {
    unsigned char truth, guess;
    unsigned char input;
    for (int i = 0; i < 256; i++) {
        input = (unsigned char)i;
        truth = (input == 0) ? 8 : (unsigned char)__builtin_ctz((unsigned int)input);
        guess = __ez80_ctzc(input);
        CMP("%d", input, truth, guess);
    }
    return 0;
}

static int test_ffsc(void) {
    unsigned char truth, guess;
    unsigned char input;
    for (int i = 0; i < 1024; i++) {
        input = (unsigned char)i;
        truth = (unsigned char)__builtin_ffs(input);
        guess = __ez80_ffsc(input);
        CMP("%d", input, truth, guess);
    }
    return 0;
}

static int test_popcountc(void) {
    unsigned char truth, guess;
    unsigned char input;
    for (int i = 0; i < 256; i++) {
        input = (unsigned char)i;
        truth = (unsigned char)__builtin_popcount((unsigned int)input);
        guess = __ez80_popcountc(input);
        CMP("%d", input, truth, guess);
    }
    return 0;
}

static int test_ffss(void) {
    unsigned char truth, guess;
    unsigned short input;
    CMP("%d", 0, 0, __ez80_ffss(0));
    CMP("%d", 1, 1, __ez80_ffss(1));
    CMP("%d", SHRT_MAX, 1, __ez80_ffss(SHRT_MAX));
    CMP("%d", SHRT_MIN, 16, __ez80_ffss(SHRT_MIN));
    CMP("%d", USHRT_MAX, 1, __ez80_ffss(USHRT_MAX));
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        input = rand16();
        truth = (unsigned char)__builtin_ffs((int)input);
        guess = __ez80_ffss(input);
        CMP("%d", input, truth, guess);
    }
    return 0;
}

static int test_popcounts(void) {
    unsigned char truth, guess;
    unsigned short input;
    CMP("%d", 0, 0, __ez80_popcounts(0));
    CMP("%d", 1, 1, __ez80_popcounts(1));
    CMP("%d", SHRT_MAX, 15, __ez80_popcounts(SHRT_MAX));
    CMP("%d", SHRT_MIN, 1, __ez80_popcounts(SHRT_MIN));
    CMP("%d", USHRT_MAX, 16, __ez80_popcounts(USHRT_MAX));
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        input = rand16();
        truth = (unsigned char)__builtin_popcount((unsigned int)input);
        guess = __ez80_popcounts(input);
        CMP("%d", input, truth, guess);
    }
    return 0;
}

static int test_clzi48(void) {
    unsigned char truth, guess;
    uint64_t input;
    CMP("%012llX", (uint64_t)0, 48, __ez80_clzi48((uint48_t)0));
    CMP("%012llX", (uint64_t)1, 47, __ez80_clzi48((uint48_t)1));
    CMP("%012llX", (uint64_t)INT48_MAX, 1, __ez80_clzi48(INT48_MAX));
    CMP("%012llX", (uint64_t)INT48_MIN, 0, __ez80_clzi48(INT48_MIN));
    CMP("%012llX", (uint64_t)UINT48_MAX, 0, __ez80_clzi48(UINT48_MAX));
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        input = rand48();
        truth = (input == 0) ? 48 : (unsigned char)(__builtin_clzll((unsigned long long)input) - 16);
        guess = __ez80_clzi48((uint48_t)input);
        CMP("%012llX", input, truth, guess);
    }
    return 0;
}

static int test_ctzi48(void) {
    unsigned char truth, guess;
    uint64_t input;
    CMP("%012llX", (uint64_t)0, 48, __ez80_ctzi48((uint48_t)0));
    CMP("%012llX", (uint64_t)1, 0, __ez80_ctzi48((uint48_t)1));
    CMP("%012llX", (uint64_t)INT48_MAX, 0, __ez80_ctzi48(INT48_MAX));
    CMP("%012llX", (uint64_t)INT48_MIN, 47, __ez80_ctzi48(INT48_MIN));
    CMP("%012llX", (uint64_t)UINT48_MAX, 0, __ez80_ctzi48(UINT48_MAX));
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        input = rand48();
        truth = (input == 0) ? 48 : (unsigned char)(__builtin_ctzll((unsigned long long)input));
        guess = __ez80_ctzi48((uint48_t)input);
        CMP("%012llX", input, truth, guess);
    }
    return 0;
}

static int test_ffsi48(void) {
    unsigned char truth, guess;
    uint64_t input;
    CMP("%012llX", (uint64_t)0, 0, __ez80_ffsi48((uint48_t)0));
    CMP("%012llX", (uint64_t)1, 1, __ez80_ffsi48((uint48_t)1));
    CMP("%012llX", (uint64_t)INT48_MAX, 1, __ez80_ffsi48(INT48_MAX));
    CMP("%012llX", (uint64_t)INT48_MIN, 48, __ez80_ffsi48(INT48_MIN));
    CMP("%012llX", (uint64_t)UINT48_MAX, 1, __ez80_ffsi48(UINT48_MAX));
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        input = rand48();
        truth = (unsigned char)__builtin_ffsll((unsigned long long)input);
        guess = __ez80_ffsi48((uint48_t)input);
        CMP("%012llX", (uint64_t)input, truth, guess);
    }
    return 0;
}

static int test_popcounti48(void) {
    unsigned char truth, guess;
    uint64_t input;
    CMP("%012llX", (uint64_t)0, 0, __ez80_popcounti48((uint48_t)0));
    CMP("%012llX", (uint64_t)1, 1, __ez80_popcounti48((uint48_t)1));
    CMP("%012llX", (uint64_t)INT48_MAX, 47, __ez80_popcounti48(INT48_MAX));
    CMP("%012llX", (uint64_t)INT48_MIN, 1, __ez80_popcounti48(INT48_MIN));
    CMP("%012llX", (uint64_t)UINT48_MAX, 48, __ez80_popcounti48(UINT48_MAX));
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        input = rand48();
        truth = (unsigned char)__builtin_popcountll((unsigned long long)input);
        guess = __ez80_popcounti48((uint48_t)input);
        CMP("%012llX", (uint64_t)input, truth, guess);
    }
    return 0;
}

static int test_bitrev24(void) {
    C(__ez80_bitreverse24(0x000000) == 0x000000);
    C(__ez80_bitreverse24(0xFFFFFF) == 0xFFFFFF);
    C(__ez80_bitreverse24(0xAAAAAA) == 0x555555);
    C(__ez80_bitreverse24(0x555555) == 0xAAAAAA);
    C(__ez80_bitreverse24(0x000001) == 0x800000);
    C(__ez80_bitreverse24(0x800000) == 0x000001);
    C(__ez80_bitreverse24(0x00CC00) == 0x003300);
    C(__ez80_bitreverse24(0x003300) == 0x00CC00);
    C(__ez80_bitreverse24(0x0AA550) == 0x0AA550);
    C(__ez80_bitreverse24(0x5F99FA) == 0x5F99FA);
    return 0;
}

static int test_bitrev48(void) {
    EQ_U48(__ez80_bitreverse48(0x000000000000), 0x000000000000);
    EQ_U48(__ez80_bitreverse48(0xFFFFFFFFFFFF), 0xFFFFFFFFFFFF);
    EQ_U48(__ez80_bitreverse48(0xAAAAAAAAAAAA), 0x555555555555);
    EQ_U48(__ez80_bitreverse48(0x555555555555), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_bitreverse48(0x000000000001), 0x800000000000);
    EQ_U48(__ez80_bitreverse48(0x800000000000), 0x000000000001);
    EQ_U48(__ez80_bitreverse48(0x0000CCCC0000), 0x000033330000);
    EQ_U48(__ez80_bitreverse48(0x000033330000), 0x0000CCCC0000);
    EQ_U48(__ez80_bitreverse48(0x000AAA555000), 0x000AAA555000);
    EQ_U48(__ez80_bitreverse48(0x555F0990FAAA), 0x555F0990FAAA);
    return 0;
}

static int test_rotateleft24(void) {
    C(__ez80_rotateleft24(0x000000,   0) == 0x000000);
    C(__ez80_rotateleft24(0x000000, 255) == 0x000000);
    C(__ez80_rotateleft24(0xFFFFFF,   0) == 0xFFFFFF);
    C(__ez80_rotateleft24(0xFFFFFF, 255) == 0xFFFFFF);
    C(__ez80_rotateleft24(0x555555,   1) == 0xAAAAAA);
    C(__ez80_rotateleft24(0x555555,   3) == 0xAAAAAA);
    C(__ez80_rotateleft24(0x555555,  21) == 0xAAAAAA);
    C(__ez80_rotateleft24(0x555555,  23) == 0xAAAAAA);
    C(__ez80_rotateleft24(0xAAAAAA,   1) == 0x555555);
    C(__ez80_rotateleft24(0xAAAAAA,   3) == 0x555555);
    C(__ez80_rotateleft24(0xAAAAAA,  21) == 0x555555);
    C(__ez80_rotateleft24(0xAAAAAA,  23) == 0x555555);

    C(__ez80_rotateleft24(0x123456,   0) == 0x123456);
    C(__ez80_rotateleft24(0x123456,   4) == 0x234561);
    C(__ez80_rotateleft24(0x123456,  12) == 0x456123);
    C(__ez80_rotateleft24(0x123456,  20) == 0x612345);
    C(__ez80_rotateleft24(0x123456,  24) == 0x123456);
    C(__ez80_rotateleft24(0x123456,  28) == 0x234561);
    C(__ez80_rotateleft24(0x123456,  36) == 0x456123);
    C(__ez80_rotateleft24(0x123456,  44) == 0x612345);
    C(__ez80_rotateleft24(0x123456,  48) == 0x123456);

    C(__ez80_rotateleft24(0x7184CE,   0) == 0x7184CE);
    C(__ez80_rotateleft24(0x7184CE,   4) == 0x184CE7);
    C(__ez80_rotateleft24(0x7184CE,  12) == 0x4CE718);
    C(__ez80_rotateleft24(0x7184CE,  20) == 0xE7184C);
    C(__ez80_rotateleft24(0x7184CE,  24) == 0x7184CE);
    C(__ez80_rotateleft24(0x7184CE,  28) == 0x184CE7);
    C(__ez80_rotateleft24(0x7184CE,  36) == 0x4CE718);
    C(__ez80_rotateleft24(0x7184CE,  44) == 0xE7184C);
    C(__ez80_rotateleft24(0x7184CE,  48) == 0x7184CE);
    return 0;
}

static int test_rotateright24(void) {
    C(__ez80_rotateright24(0x000000,   0) == 0x000000);
    C(__ez80_rotateright24(0x000000, 255) == 0x000000);
    C(__ez80_rotateright24(0xFFFFFF,   0) == 0xFFFFFF);
    C(__ez80_rotateright24(0xFFFFFF, 255) == 0xFFFFFF);
    C(__ez80_rotateright24(0x555555,   1) == 0xAAAAAA);
    C(__ez80_rotateright24(0x555555,   3) == 0xAAAAAA);
    C(__ez80_rotateright24(0x555555,  21) == 0xAAAAAA);
    C(__ez80_rotateright24(0x555555,  23) == 0xAAAAAA);
    C(__ez80_rotateright24(0xAAAAAA,   1) == 0x555555);
    C(__ez80_rotateright24(0xAAAAAA,   3) == 0x555555);
    C(__ez80_rotateright24(0xAAAAAA,  21) == 0x555555);
    C(__ez80_rotateright24(0xAAAAAA,  23) == 0x555555);

    C(__ez80_rotateright24(0x123456,   0) == 0x123456);
    C(__ez80_rotateright24(0x123456,   4) == 0x612345);
    C(__ez80_rotateright24(0x123456,  12) == 0x456123);
    C(__ez80_rotateright24(0x123456,  20) == 0x234561);
    C(__ez80_rotateright24(0x123456,  24) == 0x123456);
    C(__ez80_rotateright24(0x123456,  28) == 0x612345);
    C(__ez80_rotateright24(0x123456,  36) == 0x456123);
    C(__ez80_rotateright24(0x123456,  44) == 0x234561);
    C(__ez80_rotateright24(0x123456,  48) == 0x123456);

    C(__ez80_rotateright24(0x7184CE,   0) == 0x7184CE);
    C(__ez80_rotateright24(0x7184CE,   4) == 0xE7184C);
    C(__ez80_rotateright24(0x7184CE,  12) == 0x4CE718);
    C(__ez80_rotateright24(0x7184CE,  20) == 0x184CE7);
    C(__ez80_rotateright24(0x7184CE,  24) == 0x7184CE);
    C(__ez80_rotateright24(0x7184CE,  28) == 0xE7184C);
    C(__ez80_rotateright24(0x7184CE,  36) == 0x4CE718);
    C(__ez80_rotateright24(0x7184CE,  44) == 0x184CE7);
    C(__ez80_rotateright24(0x7184CE,  48) == 0x7184CE);
    return 0;
}

static int test_rotate24(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint24_t input = rand24();
        uint8_t shift_l = (uint8_t)(rand() % 24);
        uint8_t shift_r = (24 - shift_l) % 24;
        uint24_t output_l = __ez80_rotateleft24(input, shift_l);
        uint24_t output_r = __ez80_rotateright24(input, shift_r);
        if (output_l != output_r) {
            test_printf("I: %06X\nS: <<%u %u>>\nL: %06X\nR: %06X\n", input, shift_l, shift_r, output_l, output_r);
            return __LINE__;
        }
    }
    return 0;
}

static int test_rotateleft48(void) {
    EQ_U48(__ez80_rotateleft48(0x000000000000,   0), 0x000000000000);
    EQ_U48(__ez80_rotateleft48(0x000000000000, 255), 0x000000000000);
    EQ_U48(__ez80_rotateleft48(0xFFFFFFFFFFFF,   0), 0xFFFFFFFFFFFF);
    EQ_U48(__ez80_rotateleft48(0xFFFFFFFFFFFF, 255), 0xFFFFFFFFFFFF);
    EQ_U48(__ez80_rotateleft48(0x555555555555,   1), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateleft48(0x555555555555,   3), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateleft48(0x555555555555,  45), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateleft48(0x555555555555,  47), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateleft48(0xAAAAAAAAAAAA,   1), 0x555555555555);
    EQ_U48(__ez80_rotateleft48(0xAAAAAAAAAAAA,   3), 0x555555555555);
    EQ_U48(__ez80_rotateleft48(0xAAAAAAAAAAAA,  45), 0x555555555555);
    EQ_U48(__ez80_rotateleft48(0xAAAAAAAAAAAA,  47), 0x555555555555);

    EQ_U48(__ez80_rotateleft48(0x123456789ABC,   0), 0x123456789ABC);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,   4), 0x23456789ABC1);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  24), 0x789ABC123456);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  44), 0xC123456789AB);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  48), 0x123456789ABC);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  52), 0x23456789ABC1);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  72), 0x789ABC123456);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  92), 0xC123456789AB);
    EQ_U48(__ez80_rotateleft48(0x123456789ABC,  96), 0x123456789ABC);

    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,   0), 0x4B1DBEEFCAFE);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,   4), 0xB1DBEEFCAFE4);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  24), 0xEFCAFE4B1DBE);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  44), 0xE4B1DBEEFCAF);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  48), 0x4B1DBEEFCAFE);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  52), 0xB1DBEEFCAFE4);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  72), 0xEFCAFE4B1DBE);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  92), 0xE4B1DBEEFCAF);
    EQ_U48(__ez80_rotateleft48(0x4B1DBEEFCAFE,  96), 0x4B1DBEEFCAFE);
    return 0;
}

static int test_rotateright48(void) {
    EQ_U48(__ez80_rotateright48(0x000000000000,   0), 0x000000000000);
    EQ_U48(__ez80_rotateright48(0x000000000000, 255), 0x000000000000);
    EQ_U48(__ez80_rotateright48(0xFFFFFFFFFFFF,   0), 0xFFFFFFFFFFFF);
    EQ_U48(__ez80_rotateright48(0xFFFFFFFFFFFF, 255), 0xFFFFFFFFFFFF);
    EQ_U48(__ez80_rotateright48(0x555555555555,   1), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateright48(0x555555555555,   3), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateright48(0x555555555555,  21), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateright48(0x555555555555,  23), 0xAAAAAAAAAAAA);
    EQ_U48(__ez80_rotateright48(0xAAAAAAAAAAAA,   1), 0x555555555555);
    EQ_U48(__ez80_rotateright48(0xAAAAAAAAAAAA,   3), 0x555555555555);
    EQ_U48(__ez80_rotateright48(0xAAAAAAAAAAAA,  21), 0x555555555555);
    EQ_U48(__ez80_rotateright48(0xAAAAAAAAAAAA,  23), 0x555555555555);

    EQ_U48(__ez80_rotateright48(0x123456789ABC,   0), 0x123456789ABC);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,   4), 0xC123456789AB);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  24), 0x789ABC123456);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  44), 0x23456789ABC1);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  48), 0x123456789ABC);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  52), 0xC123456789AB);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  72), 0x789ABC123456);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  92), 0x23456789ABC1);
    EQ_U48(__ez80_rotateright48(0x123456789ABC,  96), 0x123456789ABC);

    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,   0), 0x4B1DBEEFCAFE);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,   4), 0xE4B1DBEEFCAF);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  24), 0xEFCAFE4B1DBE);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  44), 0xB1DBEEFCAFE4);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  48), 0x4B1DBEEFCAFE);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  52), 0xE4B1DBEEFCAF);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  72), 0xEFCAFE4B1DBE);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  92), 0xB1DBEEFCAFE4);
    EQ_U48(__ez80_rotateright48(0x4B1DBEEFCAFE,  96), 0x4B1DBEEFCAFE);
    return 0;
}

static int test_rotate48(void) {
    for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
        uint64_t input = rand48();
        uint8_t shift_l = (uint8_t)(rand() % 48);
        uint8_t shift_r = (48 - shift_l) % 48;
        uint64_t output_l = __ez80_rotateleft48((uint48_t)input, shift_l);
        uint64_t output_r = __ez80_rotateright48((uint48_t)input, shift_r);
        if (memcmp(&output_l, &output_r, sizeof(uint48_t))) {
            test_printf("I: %012llX\nS: <<%u %u>>\nL: %012llX\nR: %012llX\n", input, shift_l, shift_r, output_l, output_r);
            return __LINE__;
        }
    }
    return 0;
}

int run_tests(void) {
    srand(AUTOTEST_SEED);
    int ret = 0;
    TEST(test_clzc());
    TEST(test_ctzc());
    TEST(test_ffsc());
    TEST(test_popcountc());
    TEST(test_ffss());
    TEST(test_popcounts());
    TEST(test_clzi48());
    TEST(test_ctzi48());
    TEST(test_ffsi48());
    TEST(test_popcounti48());
    TEST(test_bitrev24());
    TEST(test_bitrev48());
    TEST(test_rotateleft24());
    TEST(test_rotateright24());
    TEST(test_rotate24());
    TEST(test_rotateleft48());
    TEST(test_rotateright48());
    TEST(test_rotate48());
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
