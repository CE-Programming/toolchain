#include <stdbit.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "data.h"

#define C(expr) do { if (!(expr)) { return __LINE__; } } while(0)

int test_stdbit(void) {
    C((stdc_leading_zeros_uc  (zero_u8 ) == val_8 ));
    C((stdc_leading_zeros_us  (zero_u16) == val_16));
    C((stdc_leading_zeros_ui  (zero_u24) == val_24));
    C((stdc_leading_zeros_ul  (zero_u32) == val_32));
    C((stdc_leading_zeros_ui48(zero_u48) == val_48));
    C((stdc_leading_zeros_ull (zero_u64) == val_64));
    C((stdc_leading_zeros_uc  (ones_u8 ) == val_0 ));
    C((stdc_leading_zeros_us  (ones_u16) == val_0 ));
    C((stdc_leading_zeros_ui  (ones_u24) == val_0 ));
    C((stdc_leading_zeros_ul  (ones_u32) == val_0 ));
    C((stdc_leading_zeros_ui48(ones_u48) == val_0 ));
    C((stdc_leading_zeros_ull (ones_u64) == val_0 ));

    C((stdc_trailing_zeros_uc  (zero_u8 ) == val_8 ));
    C((stdc_trailing_zeros_us  (zero_u16) == val_16));
    C((stdc_trailing_zeros_ui  (zero_u24) == val_24));
    C((stdc_trailing_zeros_ul  (zero_u32) == val_32));
    C((stdc_trailing_zeros_ui48(zero_u48) == val_48));
    C((stdc_trailing_zeros_ull (zero_u64) == val_64));
    C((stdc_trailing_zeros_uc  (ones_u8 ) == val_0 ));
    C((stdc_trailing_zeros_us  (ones_u16) == val_0 ));
    C((stdc_trailing_zeros_ui  (ones_u24) == val_0 ));
    C((stdc_trailing_zeros_ul  (ones_u32) == val_0 ));
    C((stdc_trailing_zeros_ui48(ones_u48) == val_0 ));
    C((stdc_trailing_zeros_ull (ones_u64) == val_0 ));

    C((stdc_first_trailing_one_uc  (zero_u8 ) == val_0 ));
    C((stdc_first_trailing_one_us  (zero_u16) == val_0 ));
    C((stdc_first_trailing_one_ui  (zero_u24) == val_0 ));
    C((stdc_first_trailing_one_ul  (zero_u32) == val_0 ));
    C((stdc_first_trailing_one_ui48(zero_u48) == val_0 ));
    C((stdc_first_trailing_one_ull (zero_u64) == val_0 ));
    C((stdc_first_trailing_one_uc  (ones_u8 ) == val_1 ));
    C((stdc_first_trailing_one_us  (ones_u16) == val_1 ));
    C((stdc_first_trailing_one_ui  (ones_u24) == val_1 ));
    C((stdc_first_trailing_one_ul  (ones_u32) == val_1 ));
    C((stdc_first_trailing_one_ui48(ones_u48) == val_1 ));
    C((stdc_first_trailing_one_ull (ones_u64) == val_1 ));

    C((stdc_count_ones_uc  (zero_u8 ) == val_0 ));
    C((stdc_count_ones_us  (zero_u16) == val_0 ));
    C((stdc_count_ones_ui  (zero_u24) == val_0 ));
    C((stdc_count_ones_ul  (zero_u32) == val_0 ));
    C((stdc_count_ones_ui48(zero_u48) == val_0 ));
    C((stdc_count_ones_ull (zero_u64) == val_0 ));
    C((stdc_count_ones_uc  (ones_u8 ) == val_8 ));
    C((stdc_count_ones_us  (ones_u16) == val_16));
    C((stdc_count_ones_ui  (ones_u24) == val_24));
    C((stdc_count_ones_ul  (ones_u32) == val_32));
    C((stdc_count_ones_ui48(ones_u48) == val_48));
    C((stdc_count_ones_ull (ones_u64) == val_64));
    return 0;
}
