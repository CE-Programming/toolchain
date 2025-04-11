#include <stdbit.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "data.h"

int test_stdc_leading_zeros(void) {
    C((stdc_leading_zeros_uc  (zero_u8 ) == val_8 ));
    C((stdc_leading_zeros_us  (zero_u16) == val_16));
    C((stdc_leading_zeros_ui  (zero_u24) == val_24));
    C((stdc_leading_zeros_ul  (zero_u32) == val_32));
    C((stdc_leading_zeros_ui48(zero_u48) == val_48));
    C((stdc_leading_zeros_ull (zero_u64) == val_64));
    C((stdc_leading_zeros_uc  ( one_u8 ) == val_7 ));
    C((stdc_leading_zeros_us  ( one_u16) == val_15));
    C((stdc_leading_zeros_ui  ( one_u24) == val_23));
    C((stdc_leading_zeros_ul  ( one_u32) == val_31));
    C((stdc_leading_zeros_ui48( one_u48) == val_47));
    C((stdc_leading_zeros_ull ( one_u64) == val_63));
    C((stdc_leading_zeros_uc  (umax_u8 ) == val_0 ));
    C((stdc_leading_zeros_us  (umax_u16) == val_0 ));
    C((stdc_leading_zeros_ui  (umax_u24) == val_0 ));
    C((stdc_leading_zeros_ul  (umax_u32) == val_0 ));
    C((stdc_leading_zeros_ui48(umax_u48) == val_0 ));
    C((stdc_leading_zeros_ull (umax_u64) == val_0 ));
    C((stdc_leading_zeros_uc  (smax_u8 ) == val_1 ));
    C((stdc_leading_zeros_us  (smax_u16) == val_1 ));
    C((stdc_leading_zeros_ui  (smax_u24) == val_1 ));
    C((stdc_leading_zeros_ul  (smax_u32) == val_1 ));
    C((stdc_leading_zeros_ui48(smax_u48) == val_1 ));
    C((stdc_leading_zeros_ull (smax_u64) == val_1 ));
    C((stdc_leading_zeros_uc  (smin_u8 ) == val_0 ));
    C((stdc_leading_zeros_us  (smin_u16) == val_0 ));
    C((stdc_leading_zeros_ui  (smin_u24) == val_0 ));
    C((stdc_leading_zeros_ul  (smin_u32) == val_0 ));
    C((stdc_leading_zeros_ui48(smin_u48) == val_0 ));
    C((stdc_leading_zeros_ull (smin_u64) == val_0 ));
    return 0;
}

int test_stdc_trailing_zeros(void) {
    C((stdc_trailing_zeros_uc  (zero_u8 ) == val_8 ));
    C((stdc_trailing_zeros_us  (zero_u16) == val_16));
    C((stdc_trailing_zeros_ui  (zero_u24) == val_24));
    C((stdc_trailing_zeros_ul  (zero_u32) == val_32));
    C((stdc_trailing_zeros_ui48(zero_u48) == val_48));
    C((stdc_trailing_zeros_ull (zero_u64) == val_64));
    C((stdc_trailing_zeros_uc  ( one_u8 ) == val_0 ));
    C((stdc_trailing_zeros_us  ( one_u16) == val_0 ));
    C((stdc_trailing_zeros_ui  ( one_u24) == val_0 ));
    C((stdc_trailing_zeros_ul  ( one_u32) == val_0 ));
    C((stdc_trailing_zeros_ui48( one_u48) == val_0 ));
    C((stdc_trailing_zeros_ull ( one_u64) == val_0 ));
    C((stdc_trailing_zeros_uc  (umax_u8 ) == val_0 ));
    C((stdc_trailing_zeros_us  (umax_u16) == val_0 ));
    C((stdc_trailing_zeros_ui  (umax_u24) == val_0 ));
    C((stdc_trailing_zeros_ul  (umax_u32) == val_0 ));
    C((stdc_trailing_zeros_ui48(umax_u48) == val_0 ));
    C((stdc_trailing_zeros_ull (umax_u64) == val_0 ));
    C((stdc_trailing_zeros_uc  (smax_u8 ) == val_0 ));
    C((stdc_trailing_zeros_us  (smax_u16) == val_0 ));
    C((stdc_trailing_zeros_ui  (smax_u24) == val_0 ));
    C((stdc_trailing_zeros_ul  (smax_u32) == val_0 ));
    C((stdc_trailing_zeros_ui48(smax_u48) == val_0 ));
    C((stdc_trailing_zeros_ull (smax_u64) == val_0 ));
    C((stdc_trailing_zeros_uc  (smin_u8 ) == val_7 ));
    C((stdc_trailing_zeros_us  (smin_u16) == val_15));
    C((stdc_trailing_zeros_ui  (smin_u24) == val_23));
    C((stdc_trailing_zeros_ul  (smin_u32) == val_31));
    C((stdc_trailing_zeros_ui48(smin_u48) == val_47));
    C((stdc_trailing_zeros_ull (smin_u64) == val_63));
    return 0;
}

int test_stdc_first_trailing_one(void) {
    C((stdc_first_trailing_one_uc  (zero_u8 ) == val_0 ));
    C((stdc_first_trailing_one_us  (zero_u16) == val_0 ));
    C((stdc_first_trailing_one_ui  (zero_u24) == val_0 ));
    C((stdc_first_trailing_one_ul  (zero_u32) == val_0 ));
    C((stdc_first_trailing_one_ui48(zero_u48) == val_0 ));
    C((stdc_first_trailing_one_ull (zero_u64) == val_0 ));
    C((stdc_first_trailing_one_uc  ( one_u8 ) == val_1 ));
    C((stdc_first_trailing_one_us  ( one_u16) == val_1 ));
    C((stdc_first_trailing_one_ui  ( one_u24) == val_1 ));
    C((stdc_first_trailing_one_ul  ( one_u32) == val_1 ));
    C((stdc_first_trailing_one_ui48( one_u48) == val_1 ));
    C((stdc_first_trailing_one_ull ( one_u64) == val_1 ));
    C((stdc_first_trailing_one_uc  (umax_u8 ) == val_1 ));
    C((stdc_first_trailing_one_us  (umax_u16) == val_1 ));
    C((stdc_first_trailing_one_ui  (umax_u24) == val_1 ));
    C((stdc_first_trailing_one_ul  (umax_u32) == val_1 ));
    C((stdc_first_trailing_one_ui48(umax_u48) == val_1 ));
    C((stdc_first_trailing_one_ull (umax_u64) == val_1 ));
    C((stdc_first_trailing_one_uc  (smax_u8 ) == val_1 ));
    C((stdc_first_trailing_one_us  (smax_u16) == val_1 ));
    C((stdc_first_trailing_one_ui  (smax_u24) == val_1 ));
    C((stdc_first_trailing_one_ul  (smax_u32) == val_1 ));
    C((stdc_first_trailing_one_ui48(smax_u48) == val_1 ));
    C((stdc_first_trailing_one_ull (smax_u64) == val_1 ));
    C((stdc_first_trailing_one_uc  (smin_u8 ) == val_8 ));
    C((stdc_first_trailing_one_us  (smin_u16) == val_16));
    C((stdc_first_trailing_one_ui  (smin_u24) == val_24));
    C((stdc_first_trailing_one_ul  (smin_u32) == val_32));
    C((stdc_first_trailing_one_ui48(smin_u48) == val_48));
    C((stdc_first_trailing_one_ull (smin_u64) == val_64));
    return 0;
}

int test_stdc_count_ones(void) {
    C((stdc_count_ones_uc  (zero_u8 ) == val_0 ));
    C((stdc_count_ones_us  (zero_u16) == val_0 ));
    C((stdc_count_ones_ui  (zero_u24) == val_0 ));
    C((stdc_count_ones_ul  (zero_u32) == val_0 ));
    C((stdc_count_ones_ui48(zero_u48) == val_0 ));
    C((stdc_count_ones_ull (zero_u64) == val_0 ));
    C((stdc_count_ones_uc  ( one_u8 ) == val_1 ));
    C((stdc_count_ones_us  ( one_u16) == val_1 ));
    C((stdc_count_ones_ui  ( one_u24) == val_1 ));
    C((stdc_count_ones_ul  ( one_u32) == val_1 ));
    C((stdc_count_ones_ui48( one_u48) == val_1 ));
    C((stdc_count_ones_ull ( one_u64) == val_1 ));
    C((stdc_count_ones_uc  (umax_u8 ) == val_8 ));
    C((stdc_count_ones_us  (umax_u16) == val_16));
    C((stdc_count_ones_ui  (umax_u24) == val_24));
    C((stdc_count_ones_ul  (umax_u32) == val_32));
    C((stdc_count_ones_ui48(umax_u48) == val_48));
    C((stdc_count_ones_ull (umax_u64) == val_64));
    C((stdc_count_ones_uc  (smax_u8 ) == val_7 ));
    C((stdc_count_ones_us  (smax_u16) == val_15));
    C((stdc_count_ones_ui  (smax_u24) == val_23));
    C((stdc_count_ones_ul  (smax_u32) == val_31));
    C((stdc_count_ones_ui48(smax_u48) == val_47));
    C((stdc_count_ones_ull (smax_u64) == val_63));
    C((stdc_count_ones_uc  (smin_u8 ) == val_1 ));
    C((stdc_count_ones_us  (smin_u16) == val_1 ));
    C((stdc_count_ones_ui  (smin_u24) == val_1 ));
    C((stdc_count_ones_ul  (smin_u32) == val_1 ));
    C((stdc_count_ones_ui48(smin_u48) == val_1 ));
    C((stdc_count_ones_ull (smin_u64) == val_1 ));
    return 0;
}

int test_stdbit(void) {
    int ret = 0;
    TEST(test_stdc_leading_zeros());
    TEST(test_stdc_trailing_zeros());
    TEST(test_stdc_first_trailing_one());
    TEST(test_stdc_count_ones());
    return 0;
}
