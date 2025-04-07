#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdio.h>
#include <stdint.h>
#include <bit>

#include "data.h"

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

#if 0
    // cannot be tested due to compilation bugs
    C((byteswap(byteswap_u48[0]) == byteswap_i48[0]));
    C((byteswap(byteswap_u48[1]) == byteswap_i48[1]));
    C((byteswap(byteswap_u48[2]) == byteswap_i48[2]));
    C((byteswap(byteswap_u48[3]) == byteswap_i48[3]));
    C((byteswap(byteswap_i48[2]) == byteswap_u48[2]));
    C((byteswap(byteswap_i48[3]) == byteswap_u48[3]));
#endif

    C((byteswap(byteswap_u64[0]) == byteswap_i64[0]));
    C((byteswap(byteswap_u64[1]) == byteswap_i64[1]));
    C((byteswap(byteswap_u64[2]) == byteswap_i64[2]));
    C((byteswap(byteswap_u64[3]) == byteswap_i64[3]));
    C((byteswap(byteswap_i64[2]) == byteswap_u64[2]));
    C((byteswap(byteswap_i64[3]) == byteswap_u64[3]));

    return 0;
}

int test_cxxbit(void) {
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

extern "C" {
    int test_stdbit(void);
}

int run_tests(void) {
    int ret = 0;
    TEST(test_byteswap());
    TEST(test_stdbit());
    TEST(test_cxxbit());
    return ret;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        printf("Failed test L%d\n", failed_test);
    } else {
        printf("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
