#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <limits>
#include <bit>
#include <ti/sprintf.h>

#include "data.h"


//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

static constexpr int Random_Test_Count = 128;

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

static constexpr int Auto_Test_Seed = 0x7184CE;

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

static_assert(RAND_MAX == INT_MAX, "RAND_MAX has changed");

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

template<typename T>
static inline T rand_gen(void);

template<>
inline uint8_t rand_gen(void) {
    return (uint8_t)rand();
}

template<>
inline uint16_t rand_gen(void) {
    return (uint16_t)rand();
}

template<>
inline uint24_t rand_gen(void) {
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

template<>
inline uint32_t rand_gen(void) {
    union {
        uint32_t u32;
        uint16_t u16[2];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    return split.u32;
}

template<>
inline uint48_t rand_gen(void) {
    union {
        uint48_t u48;
        uint16_t u16[3];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    return split.u48;
}

template<>
inline uint64_t rand_gen(void) {
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

/* prevents clang from constant folding builtins */

extern uint8_t byteswap_u8[4];
extern uint16_t byteswap_u16[4];
extern uint24_t byteswap_u24[4];
extern uint32_t byteswap_u32[4];
extern uint48_t byteswap_u48[4];
extern uint64_t byteswap_u64[4];

extern uint8_t byteswap_i8[4];
extern uint16_t byteswap_i16[4];
extern uint24_t byteswap_i24[4];
extern uint32_t byteswap_i32[4];
extern uint48_t byteswap_i48[4];
extern uint64_t byteswap_i64[4];

int test_byteswap(void) {
    using std::byteswap;

    C((byteswap(byteswap_u8 [0]) == byteswap_i8 [0]));
    C((byteswap(byteswap_u8 [1]) == byteswap_i8 [1]));
    C((byteswap(byteswap_u8 [2]) == byteswap_i8 [2]));
    C((byteswap(byteswap_u8 [3]) == byteswap_i8 [3]));
    C((byteswap(byteswap_i8 [2]) == byteswap_u8 [2]));
    C((byteswap(byteswap_i8 [3]) == byteswap_u8 [3]));

    C((byteswap(byteswap_u16[0]) == byteswap_i16[0]));
    C((byteswap(byteswap_u16[1]) == byteswap_i16[1]));
    C((byteswap(byteswap_u16[2]) == byteswap_i16[2]));
    C((byteswap(byteswap_u16[3]) == byteswap_i16[3]));
    C((byteswap(byteswap_i16[2]) == byteswap_u16[2]));
    C((byteswap(byteswap_i16[3]) == byteswap_u16[3]));

    C((byteswap(byteswap_u24[0]) == byteswap_i24[0]));
    C((byteswap(byteswap_u24[1]) == byteswap_i24[1]));
    C((byteswap(byteswap_u24[2]) == byteswap_i24[2]));
    C((byteswap(byteswap_u24[3]) == byteswap_i24[3]));
    C((byteswap(byteswap_i24[2]) == byteswap_u24[2]));
    C((byteswap(byteswap_i24[3]) == byteswap_u24[3]));

    C((byteswap(byteswap_u32[0]) == byteswap_i32[0]));
    C((byteswap(byteswap_u32[1]) == byteswap_i32[1]));
    C((byteswap(byteswap_u32[2]) == byteswap_i32[2]));
    C((byteswap(byteswap_u32[3]) == byteswap_i32[3]));
    C((byteswap(byteswap_i32[2]) == byteswap_u32[2]));
    C((byteswap(byteswap_i32[3]) == byteswap_u32[3]));

    C((byteswap(byteswap_u48[0]) == byteswap_i48[0]));
    C((byteswap(byteswap_u48[1]) == byteswap_i48[1]));
    C((byteswap(byteswap_u48[2]) == byteswap_i48[2]));
    C((byteswap(byteswap_u48[3]) == byteswap_i48[3]));
    C((byteswap(byteswap_i48[2]) == byteswap_u48[2]));
    C((byteswap(byteswap_i48[3]) == byteswap_u48[3]));

    C((byteswap(byteswap_u64[0]) == byteswap_i64[0]));
    C((byteswap(byteswap_u64[1]) == byteswap_i64[1]));
    C((byteswap(byteswap_u64[2]) == byteswap_i64[2]));
    C((byteswap(byteswap_u64[3]) == byteswap_i64[3]));
    C((byteswap(byteswap_i64[2]) == byteswap_u64[2]));
    C((byteswap(byteswap_i64[3]) == byteswap_u64[3]));

    return 0;
}

int test_cxxbit_edge_cases(void) {
    C((std::countl_zero(zero_u8 ) == val_8 ));
    C((std::countl_zero(zero_u16) == val_16));
    C((std::countl_zero(zero_u24) == val_24));
    C((std::countl_zero(zero_u32) == val_32));
    C((std::countl_zero(zero_u48) == val_48));
    C((std::countl_zero(zero_u64) == val_64));
    C((std::countl_zero(ones_u8 ) == val_0 ));
    C((std::countl_zero(ones_u16) == val_0 ));
    C((std::countl_zero(ones_u24) == val_0 ));
    C((std::countl_zero(ones_u32) == val_0 ));
    C((std::countl_zero(ones_u48) == val_0 ));
    C((std::countl_zero(ones_u64) == val_0 ));

    C((std::countl_one(zero_u8 ) == val_0 ));
    C((std::countl_one(zero_u16) == val_0 ));
    C((std::countl_one(zero_u24) == val_0 ));
    C((std::countl_one(zero_u32) == val_0 ));
    C((std::countl_one(zero_u48) == val_0 ));
    C((std::countl_one(zero_u64) == val_0 ));
    C((std::countl_one(ones_u8 ) == val_8 ));
    C((std::countl_one(ones_u16) == val_16));
    C((std::countl_one(ones_u24) == val_24));
    C((std::countl_one(ones_u32) == val_32));
    C((std::countl_one(ones_u48) == val_48));
    C((std::countl_one(ones_u64) == val_64));

    C((std::countr_zero(zero_u8 ) == val_8 ));
    C((std::countr_zero(zero_u16) == val_16));
    C((std::countr_zero(zero_u24) == val_24));
    C((std::countr_zero(zero_u32) == val_32));
    C((std::countr_zero(zero_u48) == val_48));
    C((std::countr_zero(zero_u64) == val_64));
    C((std::countr_zero(ones_u8 ) == val_0 ));
    C((std::countr_zero(ones_u16) == val_0 ));
    C((std::countr_zero(ones_u24) == val_0 ));
    C((std::countr_zero(ones_u32) == val_0 ));
    C((std::countr_zero(ones_u48) == val_0 ));
    C((std::countr_zero(ones_u64) == val_0 ));

    C((std::countr_one(zero_u8 ) == val_0 ));
    C((std::countr_one(zero_u16) == val_0 ));
    C((std::countr_one(zero_u24) == val_0 ));
    C((std::countr_one(zero_u32) == val_0 ));
    C((std::countr_one(zero_u48) == val_0 ));
    C((std::countr_one(zero_u64) == val_0 ));
    C((std::countr_one(ones_u8 ) == val_8 ));
    C((std::countr_one(ones_u16) == val_16));
    C((std::countr_one(ones_u24) == val_24));
    C((std::countr_one(ones_u32) == val_32));
    C((std::countr_one(ones_u48) == val_48));
    C((std::countr_one(ones_u64) == val_64));

    C((std::bit_width(zero_u8 ) == val_0 ));
    C((std::bit_width(zero_u16) == val_0 ));
    C((std::bit_width(zero_u24) == val_0 ));
    C((std::bit_width(zero_u32) == val_0 ));
    C((std::bit_width(zero_u48) == val_0 ));
    C((std::bit_width(zero_u64) == val_0 ));
    C((std::bit_width(ones_u8 ) == val_8 ));
    C((std::bit_width(ones_u16) == val_16));
    C((std::bit_width(ones_u24) == val_24));
    C((std::bit_width(ones_u32) == val_32));
    C((std::bit_width(ones_u48) == val_48));
    C((std::bit_width(ones_u64) == val_64));

    C((std::bit_ceil(zero_u8 ) == val_1 ));
    C((std::bit_ceil(zero_u16) == val_1 ));
    C((std::bit_ceil(zero_u24) == val_1 ));
    C((std::bit_ceil(zero_u32) == val_1 ));
    C((std::bit_ceil(zero_u48) == val_1 ));
    C((std::bit_ceil(zero_u64) == val_1 ));

    C((std::bit_floor(zero_u8 ) == val_0 ));
    C((std::bit_floor(zero_u16) == val_0 ));
    C((std::bit_floor(zero_u24) == val_0 ));
    C((std::bit_floor(zero_u32) == val_0 ));
    C((std::bit_floor(zero_u48) == val_0 ));
    C((std::bit_floor(zero_u64) == val_0 ));

    C((std::popcount(zero_u8 ) == val_0 ));
    C((std::popcount(zero_u16) == val_0 ));
    C((std::popcount(zero_u24) == val_0 ));
    C((std::popcount(zero_u32) == val_0 ));
    C((std::popcount(zero_u48) == val_0 ));
    C((std::popcount(zero_u64) == val_0 ));
    C((std::popcount(ones_u8 ) == val_8 ));
    C((std::popcount(ones_u16) == val_16));
    C((std::popcount(ones_u24) == val_24));
    C((std::popcount(ones_u32) == val_32));
    C((std::popcount(ones_u48) == val_48));
    C((std::popcount(ones_u64) == val_64));
    return 0;
}

template<typename T>
static inline bool verify_bit_ceil(void) {
    __attribute__((__unused__)) constexpr int width = std::numeric_limits<T>::digits / 4;
    for (int i = 0; i < Random_Test_Count; i++) {
        T input = rand_gen<T>();
        T output = std::bit_ceil(input);
        if (
            (!std::has_single_bit(output) || output < input) && output != 0
        ) {
            test_printf(
                "bit_ceil:\nI: %0*llX\nO: %0*llX\n",
                width, (uint64_t)input,
                width, (uint64_t)output
            );
            return false;
        }
    }
    return true;
}

int test_bit_ceil(void) {
    C((verify_bit_ceil<uint8_t>()));
    C((verify_bit_ceil<uint16_t>()));
    C((verify_bit_ceil<uint24_t>()));
    C((verify_bit_ceil<uint32_t>()));
    C((verify_bit_ceil<uint48_t>()));
    C((verify_bit_ceil<uint64_t>()));
    return 0;
}

template<typename T>
static inline bool verify_bit_floor(void) {
    __attribute__((__unused__)) constexpr int width = std::numeric_limits<T>::digits / 4;
    for (int i = 0; i < Random_Test_Count; i++) {
        T input = rand_gen<T>();
        T output = std::bit_floor(input);
        if (
            (!std::has_single_bit(output) || output > input) && output != 0
        ) {
            test_printf(
                "bit_floor:\nI: %0*llX\nO: %0*llX\n",
                width, (uint64_t)input,
                width, (uint64_t)output
            );
            return false;
        }
    }
    return true;
}

int test_bit_floor(void) {
    C((verify_bit_floor<uint8_t>()));
    C((verify_bit_floor<uint16_t>()));
    C((verify_bit_floor<uint24_t>()));
    C((verify_bit_floor<uint32_t>()));
    C((verify_bit_floor<uint48_t>()));
    C((verify_bit_floor<uint64_t>()));
    return 0;
}

template<typename T>
static inline bool verify_rotate(void) {
    __attribute__((__unused__)) constexpr int width = std::numeric_limits<T>::digits / 4;
    for (int i = 0; i < Random_Test_Count; i++) {
        T input = rand_gen<T>();
        int shift = (int)((int8_t)rand());
        T shift_l = std::rotl(input, shift);
        T shift_r = std::rotr(input, -shift);
        if (shift_l != shift_r) {
            test_printf(
                "rotate: %d\nI: %0*llX\nL: %0*llX\nR: %0*llX\n",
                shift,
                width, (uint64_t)input,
                width, (uint64_t)shift_l,
                width, (uint64_t)shift_r
            );
            return false;
        }
    }
    return true;
}

int test_rotate(void) {
    C((verify_rotate<uint8_t>()));
    C((verify_rotate<uint16_t>()));
    C((verify_rotate<uint24_t>()));
    C((verify_rotate<uint32_t>()));
    C((verify_rotate<uint48_t>()));
    C((verify_rotate<uint64_t>()));
    return 0;
}

extern "C" {
    int test_stdbit(void);
}

int run_tests(void) {
    srand(Auto_Test_Seed);
    int ret = 0;
    TEST(test_byteswap());
    TEST(test_stdbit());
    TEST(test_cxxbit_edge_cases());
    TEST(test_bit_ceil());
    TEST(test_bit_floor());
    TEST(test_rotate());
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
