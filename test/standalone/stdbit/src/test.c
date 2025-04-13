#include <stdbit.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "data.h"

int test_leading_zeros(void) {
    C((stdc_leading_zeros(zero_u8 ) == val_8 ));
    C((stdc_leading_zeros(zero_u16) == val_16));
    C((stdc_leading_zeros(zero_u24) == val_24));
    C((stdc_leading_zeros(zero_u32) == val_32));
    C((stdc_leading_zeros(zero_u48) == val_48));
    C((stdc_leading_zeros(zero_u64) == val_64));
    C((stdc_leading_zeros( one_u8 ) == val_7 ));
    C((stdc_leading_zeros( one_u16) == val_15));
    C((stdc_leading_zeros( one_u24) == val_23));
    C((stdc_leading_zeros( one_u32) == val_31));
    C((stdc_leading_zeros( one_u48) == val_47));
    C((stdc_leading_zeros( one_u64) == val_63));
    C((stdc_leading_zeros(umax_u8 ) == val_0 ));
    C((stdc_leading_zeros(umax_u16) == val_0 ));
    C((stdc_leading_zeros(umax_u24) == val_0 ));
    C((stdc_leading_zeros(umax_u32) == val_0 ));
    C((stdc_leading_zeros(umax_u48) == val_0 ));
    C((stdc_leading_zeros(umax_u64) == val_0 ));
    C((stdc_leading_zeros(smax_u8 ) == val_1 ));
    C((stdc_leading_zeros(smax_u16) == val_1 ));
    C((stdc_leading_zeros(smax_u24) == val_1 ));
    C((stdc_leading_zeros(smax_u32) == val_1 ));
    C((stdc_leading_zeros(smax_u48) == val_1 ));
    C((stdc_leading_zeros(smax_u64) == val_1 ));
    C((stdc_leading_zeros(smin_u8 ) == val_0 ));
    C((stdc_leading_zeros(smin_u16) == val_0 ));
    C((stdc_leading_zeros(smin_u24) == val_0 ));
    C((stdc_leading_zeros(smin_u32) == val_0 ));
    C((stdc_leading_zeros(smin_u48) == val_0 ));
    C((stdc_leading_zeros(smin_u64) == val_0 ));
    return 0;
}

int test_leading_ones(void) {
    C((stdc_leading_ones(zero_u8 ) == val_0 ));
    C((stdc_leading_ones(zero_u16) == val_0 ));
    C((stdc_leading_ones(zero_u24) == val_0 ));
    C((stdc_leading_ones(zero_u32) == val_0 ));
    C((stdc_leading_ones(zero_u48) == val_0 ));
    C((stdc_leading_ones(zero_u64) == val_0 ));
    C((stdc_leading_ones( one_u8 ) == val_0 ));
    C((stdc_leading_ones( one_u16) == val_0 ));
    C((stdc_leading_ones( one_u24) == val_0 ));
    C((stdc_leading_ones( one_u32) == val_0 ));
    C((stdc_leading_ones( one_u48) == val_0 ));
    C((stdc_leading_ones( one_u64) == val_0 ));
    C((stdc_leading_ones(umax_u8 ) == val_8 ));
    C((stdc_leading_ones(umax_u16) == val_16));
    C((stdc_leading_ones(umax_u24) == val_24));
    C((stdc_leading_ones(umax_u32) == val_32));
    C((stdc_leading_ones(umax_u48) == val_48));
    C((stdc_leading_ones(umax_u64) == val_64));
    C((stdc_leading_ones(smax_u8 ) == val_0 ));
    C((stdc_leading_ones(smax_u16) == val_0 ));
    C((stdc_leading_ones(smax_u24) == val_0 ));
    C((stdc_leading_ones(smax_u32) == val_0 ));
    C((stdc_leading_ones(smax_u48) == val_0 ));
    C((stdc_leading_ones(smax_u64) == val_0 ));
    C((stdc_leading_ones(smin_u8 ) == val_1 ));
    C((stdc_leading_ones(smin_u16) == val_1 ));
    C((stdc_leading_ones(smin_u24) == val_1 ));
    C((stdc_leading_ones(smin_u32) == val_1 ));
    C((stdc_leading_ones(smin_u48) == val_1 ));
    C((stdc_leading_ones(smin_u64) == val_1 ));
    return 0;
}

int test_trailing_zeros(void) {
    C((stdc_trailing_zeros(zero_u8 ) == val_8 ));
    C((stdc_trailing_zeros(zero_u16) == val_16));
    C((stdc_trailing_zeros(zero_u24) == val_24));
    C((stdc_trailing_zeros(zero_u32) == val_32));
    C((stdc_trailing_zeros(zero_u48) == val_48));
    C((stdc_trailing_zeros(zero_u64) == val_64));
    C((stdc_trailing_zeros( one_u8 ) == val_0 ));
    C((stdc_trailing_zeros( one_u16) == val_0 ));
    C((stdc_trailing_zeros( one_u24) == val_0 ));
    C((stdc_trailing_zeros( one_u32) == val_0 ));
    C((stdc_trailing_zeros( one_u48) == val_0 ));
    C((stdc_trailing_zeros( one_u64) == val_0 ));
    C((stdc_trailing_zeros(umax_u8 ) == val_0 ));
    C((stdc_trailing_zeros(umax_u16) == val_0 ));
    C((stdc_trailing_zeros(umax_u24) == val_0 ));
    C((stdc_trailing_zeros(umax_u32) == val_0 ));
    C((stdc_trailing_zeros(umax_u48) == val_0 ));
    C((stdc_trailing_zeros(umax_u64) == val_0 ));
    C((stdc_trailing_zeros(smax_u8 ) == val_0 ));
    C((stdc_trailing_zeros(smax_u16) == val_0 ));
    C((stdc_trailing_zeros(smax_u24) == val_0 ));
    C((stdc_trailing_zeros(smax_u32) == val_0 ));
    C((stdc_trailing_zeros(smax_u48) == val_0 ));
    C((stdc_trailing_zeros(smax_u64) == val_0 ));
    C((stdc_trailing_zeros(smin_u8 ) == val_7 ));
    C((stdc_trailing_zeros(smin_u16) == val_15));
    C((stdc_trailing_zeros(smin_u24) == val_23));
    C((stdc_trailing_zeros(smin_u32) == val_31));
    C((stdc_trailing_zeros(smin_u48) == val_47));
    C((stdc_trailing_zeros(smin_u64) == val_63));
    return 0;
}

int test_trailing_ones(void) {
    C((stdc_trailing_ones(zero_u8 ) == val_0 ));
    C((stdc_trailing_ones(zero_u16) == val_0 ));
    C((stdc_trailing_ones(zero_u24) == val_0 ));
    C((stdc_trailing_ones(zero_u32) == val_0 ));
    C((stdc_trailing_ones(zero_u48) == val_0 ));
    C((stdc_trailing_ones(zero_u64) == val_0 ));
    C((stdc_trailing_ones( one_u8 ) == val_1 ));
    C((stdc_trailing_ones( one_u16) == val_1 ));
    C((stdc_trailing_ones( one_u24) == val_1 ));
    C((stdc_trailing_ones( one_u32) == val_1 ));
    C((stdc_trailing_ones( one_u48) == val_1 ));
    C((stdc_trailing_ones( one_u64) == val_1 ));
    C((stdc_trailing_ones(umax_u8 ) == val_8 ));
    C((stdc_trailing_ones(umax_u16) == val_16));
    C((stdc_trailing_ones(umax_u24) == val_24));
    C((stdc_trailing_ones(umax_u32) == val_32));
    C((stdc_trailing_ones(umax_u48) == val_48));
    C((stdc_trailing_ones(umax_u64) == val_64));
    C((stdc_trailing_ones(smax_u8 ) == val_7 ));
    C((stdc_trailing_ones(smax_u16) == val_15));
    C((stdc_trailing_ones(smax_u24) == val_23));
    C((stdc_trailing_ones(smax_u32) == val_31));
    C((stdc_trailing_ones(smax_u48) == val_47));
    C((stdc_trailing_ones(smax_u64) == val_63));
    C((stdc_trailing_ones(smin_u8 ) == val_0 ));
    C((stdc_trailing_ones(smin_u16) == val_0 ));
    C((stdc_trailing_ones(smin_u24) == val_0 ));
    C((stdc_trailing_ones(smin_u32) == val_0 ));
    C((stdc_trailing_ones(smin_u48) == val_0 ));
    C((stdc_trailing_ones(smin_u64) == val_0 ));
    return 0;
}

int test_first_leading_one(void) {
    C((stdc_first_leading_one(zero_u8 ) == val_0 ));
    C((stdc_first_leading_one(zero_u16) == val_0 ));
    C((stdc_first_leading_one(zero_u24) == val_0 ));
    C((stdc_first_leading_one(zero_u32) == val_0 ));
    C((stdc_first_leading_one(zero_u48) == val_0 ));
    C((stdc_first_leading_one(zero_u64) == val_0 ));
    C((stdc_first_leading_one( one_u8 ) == val_8 ));
    C((stdc_first_leading_one( one_u16) == val_16));
    C((stdc_first_leading_one( one_u24) == val_24));
    C((stdc_first_leading_one( one_u32) == val_32));
    C((stdc_first_leading_one( one_u48) == val_48));
    C((stdc_first_leading_one( one_u64) == val_64));
    C((stdc_first_leading_one(umax_u8 ) == val_1 ));
    C((stdc_first_leading_one(umax_u16) == val_1 ));
    C((stdc_first_leading_one(umax_u24) == val_1 ));
    C((stdc_first_leading_one(umax_u32) == val_1 ));
    C((stdc_first_leading_one(umax_u48) == val_1 ));
    C((stdc_first_leading_one(umax_u64) == val_1 ));
    C((stdc_first_leading_one(smax_u8 ) == val_2 ));
    C((stdc_first_leading_one(smax_u16) == val_2 ));
    C((stdc_first_leading_one(smax_u24) == val_2 ));
    C((stdc_first_leading_one(smax_u32) == val_2 ));
    C((stdc_first_leading_one(smax_u48) == val_2 ));
    C((stdc_first_leading_one(smax_u64) == val_2 ));
    C((stdc_first_leading_one(smin_u8 ) == val_1 ));
    C((stdc_first_leading_one(smin_u16) == val_1 ));
    C((stdc_first_leading_one(smin_u24) == val_1 ));
    C((stdc_first_leading_one(smin_u32) == val_1 ));
    C((stdc_first_leading_one(smin_u48) == val_1 ));
    C((stdc_first_leading_one(smin_u64) == val_1 ));
    return 0;
}

int test_first_leading_zero(void) {
    C((stdc_first_leading_zero(zero_u8 ) == val_1 ));
    C((stdc_first_leading_zero(zero_u16) == val_1 ));
    C((stdc_first_leading_zero(zero_u24) == val_1 ));
    C((stdc_first_leading_zero(zero_u32) == val_1 ));
    C((stdc_first_leading_zero(zero_u48) == val_1 ));
    C((stdc_first_leading_zero(zero_u64) == val_1 ));
    C((stdc_first_leading_zero( one_u8 ) == val_1 ));
    C((stdc_first_leading_zero( one_u16) == val_1 ));
    C((stdc_first_leading_zero( one_u24) == val_1 ));
    C((stdc_first_leading_zero( one_u32) == val_1 ));
    C((stdc_first_leading_zero( one_u48) == val_1 ));
    C((stdc_first_leading_zero( one_u64) == val_1 ));
    C((stdc_first_leading_zero(umax_u8 ) == val_0 ));
    C((stdc_first_leading_zero(umax_u16) == val_0 ));
    C((stdc_first_leading_zero(umax_u24) == val_0 ));
    C((stdc_first_leading_zero(umax_u32) == val_0 ));
    C((stdc_first_leading_zero(umax_u48) == val_0 ));
    C((stdc_first_leading_zero(umax_u64) == val_0 ));
    C((stdc_first_leading_zero(smax_u8 ) == val_1 ));
    C((stdc_first_leading_zero(smax_u16) == val_1 ));
    C((stdc_first_leading_zero(smax_u24) == val_1 ));
    C((stdc_first_leading_zero(smax_u32) == val_1 ));
    C((stdc_first_leading_zero(smax_u48) == val_1 ));
    C((stdc_first_leading_zero(smax_u64) == val_1 ));
    C((stdc_first_leading_zero(smin_u8 ) == val_2 ));
    C((stdc_first_leading_zero(smin_u16) == val_2 ));
    C((stdc_first_leading_zero(smin_u24) == val_2 ));
    C((stdc_first_leading_zero(smin_u32) == val_2 ));
    C((stdc_first_leading_zero(smin_u48) == val_2 ));
    C((stdc_first_leading_zero(smin_u64) == val_2 ));
    return 0;
}

int test_first_trailing_one(void) {
    C((stdc_first_trailing_one(zero_u8 ) == val_0));
    C((stdc_first_trailing_one(zero_u16) == val_0));
    C((stdc_first_trailing_one(zero_u24) == val_0));
    C((stdc_first_trailing_one(zero_u32) == val_0));
    C((stdc_first_trailing_one(zero_u48) == val_0));
    C((stdc_first_trailing_one(zero_u64) == val_0));
    C((stdc_first_trailing_one( one_u8 ) == val_1 ));
    C((stdc_first_trailing_one( one_u16) == val_1 ));
    C((stdc_first_trailing_one( one_u24) == val_1 ));
    C((stdc_first_trailing_one( one_u32) == val_1 ));
    C((stdc_first_trailing_one( one_u48) == val_1 ));
    C((stdc_first_trailing_one( one_u64) == val_1 ));
    C((stdc_first_trailing_one(umax_u8 ) == val_1 ));
    C((stdc_first_trailing_one(umax_u16) == val_1 ));
    C((stdc_first_trailing_one(umax_u24) == val_1 ));
    C((stdc_first_trailing_one(umax_u32) == val_1 ));
    C((stdc_first_trailing_one(umax_u48) == val_1 ));
    C((stdc_first_trailing_one(umax_u64) == val_1 ));
    C((stdc_first_trailing_one(smax_u8 ) == val_1 ));
    C((stdc_first_trailing_one(smax_u16) == val_1 ));
    C((stdc_first_trailing_one(smax_u24) == val_1 ));
    C((stdc_first_trailing_one(smax_u32) == val_1 ));
    C((stdc_first_trailing_one(smax_u48) == val_1 ));
    C((stdc_first_trailing_one(smax_u64) == val_1 ));
    C((stdc_first_trailing_one(smin_u8 ) == val_8 ));
    C((stdc_first_trailing_one(smin_u16) == val_16));
    C((stdc_first_trailing_one(smin_u24) == val_24));
    C((stdc_first_trailing_one(smin_u32) == val_32));
    C((stdc_first_trailing_one(smin_u48) == val_48));
    C((stdc_first_trailing_one(smin_u64) == val_64));
    return 0;
}

int test_first_trailing_zero(void) {
    C((stdc_first_trailing_zero(zero_u8 ) == val_1 ));
    C((stdc_first_trailing_zero(zero_u16) == val_1 ));
    C((stdc_first_trailing_zero(zero_u24) == val_1 ));
    C((stdc_first_trailing_zero(zero_u32) == val_1 ));
    C((stdc_first_trailing_zero(zero_u48) == val_1 ));
    C((stdc_first_trailing_zero(zero_u64) == val_1 ));
    C((stdc_first_trailing_zero( one_u8 ) == val_2 ));
    C((stdc_first_trailing_zero( one_u16) == val_2 ));
    C((stdc_first_trailing_zero( one_u24) == val_2 ));
    C((stdc_first_trailing_zero( one_u32) == val_2 ));
    C((stdc_first_trailing_zero( one_u48) == val_2 ));
    C((stdc_first_trailing_zero( one_u64) == val_2 ));
    C((stdc_first_trailing_zero(umax_u8 ) == val_0 ));
    C((stdc_first_trailing_zero(umax_u16) == val_0 ));
    C((stdc_first_trailing_zero(umax_u24) == val_0 ));
    C((stdc_first_trailing_zero(umax_u32) == val_0 ));
    C((stdc_first_trailing_zero(umax_u48) == val_0 ));
    C((stdc_first_trailing_zero(umax_u64) == val_0 ));
    C((stdc_first_trailing_zero(smax_u8 ) == val_8 ));
    C((stdc_first_trailing_zero(smax_u16) == val_16));
    C((stdc_first_trailing_zero(smax_u24) == val_24));
    C((stdc_first_trailing_zero(smax_u32) == val_32));
    C((stdc_first_trailing_zero(smax_u48) == val_48));
    C((stdc_first_trailing_zero(smax_u64) == val_64));
    C((stdc_first_trailing_zero(smin_u8 ) == val_1 ));
    C((stdc_first_trailing_zero(smin_u16) == val_1 ));
    C((stdc_first_trailing_zero(smin_u24) == val_1 ));
    C((stdc_first_trailing_zero(smin_u32) == val_1 ));
    C((stdc_first_trailing_zero(smin_u48) == val_1 ));
    C((stdc_first_trailing_zero(smin_u64) == val_1 ));
    return 0;
}

int test_bit_width(void) {
    C((stdc_bit_width(zero_u8 ) == val_0 ));
    C((stdc_bit_width(zero_u16) == val_0 ));
    C((stdc_bit_width(zero_u24) == val_0 ));
    C((stdc_bit_width(zero_u32) == val_0 ));
    C((stdc_bit_width(zero_u48) == val_0 ));
    C((stdc_bit_width(zero_u64) == val_0 ));
    C((stdc_bit_width( one_u8 ) == val_1 ));
    C((stdc_bit_width( one_u16) == val_1 ));
    C((stdc_bit_width( one_u24) == val_1 ));
    C((stdc_bit_width( one_u32) == val_1 ));
    C((stdc_bit_width( one_u48) == val_1 ));
    C((stdc_bit_width( one_u64) == val_1 ));
    C((stdc_bit_width(umax_u8 ) == val_8 ));
    C((stdc_bit_width(umax_u16) == val_16));
    C((stdc_bit_width(umax_u24) == val_24));
    C((stdc_bit_width(umax_u32) == val_32));
    C((stdc_bit_width(umax_u48) == val_48));
    C((stdc_bit_width(umax_u64) == val_64));
    C((stdc_bit_width(smax_u8 ) == val_7 ));
    C((stdc_bit_width(smax_u16) == val_15));
    C((stdc_bit_width(smax_u24) == val_23));
    C((stdc_bit_width(smax_u32) == val_31));
    C((stdc_bit_width(smax_u48) == val_47));
    C((stdc_bit_width(smax_u64) == val_63));
    C((stdc_bit_width(smin_u8 ) == val_8 ));
    C((stdc_bit_width(smin_u16) == val_16));
    C((stdc_bit_width(smin_u24) == val_24));
    C((stdc_bit_width(smin_u32) == val_32));
    C((stdc_bit_width(smin_u48) == val_48));
    C((stdc_bit_width(smin_u64) == val_64));
    return 0;
}

int test_bit_ceil(void) {
    C((stdc_bit_ceil(zero_u8 ) ==  one_u8 ));
    C((stdc_bit_ceil(zero_u16) ==  one_u16));
    C((stdc_bit_ceil(zero_u24) ==  one_u24));
    C((stdc_bit_ceil(zero_u32) ==  one_u32));
    C((stdc_bit_ceil(zero_u48) ==  one_u48));
    C((stdc_bit_ceil(zero_u64) ==  one_u64));
    C((stdc_bit_ceil( one_u8 ) ==  one_u8 ));
    C((stdc_bit_ceil( one_u16) ==  one_u16));
    C((stdc_bit_ceil( one_u24) ==  one_u24));
    C((stdc_bit_ceil( one_u32) ==  one_u32));
    C((stdc_bit_ceil( one_u48) ==  one_u48));
    C((stdc_bit_ceil( one_u64) ==  one_u64));
    C((stdc_bit_ceil(umax_u8 ) == zero_u8 ));
    C((stdc_bit_ceil(umax_u16) == zero_u16));
    C((stdc_bit_ceil(umax_u24) == zero_u24));
    C((stdc_bit_ceil(umax_u32) == zero_u32));
    C((stdc_bit_ceil(umax_u48) == zero_u48));
    C((stdc_bit_ceil(umax_u64) == zero_u64));
    C((stdc_bit_ceil(smax_u8 ) == smin_u8 ));
    C((stdc_bit_ceil(smax_u16) == smin_u16));
    C((stdc_bit_ceil(smax_u24) == smin_u24));
    C((stdc_bit_ceil(smax_u32) == smin_u32));
    C((stdc_bit_ceil(smax_u48) == smin_u48));
    C((stdc_bit_ceil(smax_u64) == smin_u64));
    C((stdc_bit_ceil(smin_u8 ) == smin_u8 ));
    C((stdc_bit_ceil(smin_u16) == smin_u16));
    C((stdc_bit_ceil(smin_u24) == smin_u24));
    C((stdc_bit_ceil(smin_u32) == smin_u32));
    C((stdc_bit_ceil(smin_u48) == smin_u48));
    C((stdc_bit_ceil(smin_u64) == smin_u64));
    return 0;
}

int test_bit_floor(void) {
    C((stdc_bit_floor(zero_u8 ) == zero_u8 ));
    C((stdc_bit_floor(zero_u16) == zero_u16));
    C((stdc_bit_floor(zero_u24) == zero_u24));
    C((stdc_bit_floor(zero_u32) == zero_u32));
    C((stdc_bit_floor(zero_u48) == zero_u48));
    C((stdc_bit_floor(zero_u64) == zero_u64));
    C((stdc_bit_floor( one_u8 ) ==  one_u8 ));
    C((stdc_bit_floor( one_u16) ==  one_u16));
    C((stdc_bit_floor( one_u24) ==  one_u24));
    C((stdc_bit_floor( one_u32) ==  one_u32));
    C((stdc_bit_floor( one_u48) ==  one_u48));
    C((stdc_bit_floor( one_u64) ==  one_u64));
    C((stdc_bit_floor(umax_u8 ) == smin_u8 ));
    C((stdc_bit_floor(umax_u16) == smin_u16));
    C((stdc_bit_floor(umax_u24) == smin_u24));
    C((stdc_bit_floor(umax_u32) == smin_u32));
    C((stdc_bit_floor(umax_u48) == smin_u48));
    C((stdc_bit_floor(umax_u64) == smin_u64));
    C((stdc_bit_floor(smax_u8 ) == smin_u8  >> 1));
    C((stdc_bit_floor(smax_u16) == smin_u16 >> 1));
    C((stdc_bit_floor(smax_u24) == smin_u24 >> 1));
    C((stdc_bit_floor(smax_u32) == smin_u32 >> 1));
    C((stdc_bit_floor(smax_u48) == smin_u48 >> 1));
    C((stdc_bit_floor(smax_u64) == smin_u64 >> 1));
    C((stdc_bit_floor(smin_u8 ) == smin_u8 ));
    C((stdc_bit_floor(smin_u16) == smin_u16));
    C((stdc_bit_floor(smin_u24) == smin_u24));
    C((stdc_bit_floor(smin_u32) == smin_u32));
    C((stdc_bit_floor(smin_u48) == smin_u48));
    C((stdc_bit_floor(smin_u64) == smin_u64));
    return 0;
}

int test_count_ones(void) {
    C((stdc_count_ones(zero_u8 ) == val_0 ));
    C((stdc_count_ones(zero_u16) == val_0 ));
    C((stdc_count_ones(zero_u24) == val_0 ));
    C((stdc_count_ones(zero_u32) == val_0 ));
    C((stdc_count_ones(zero_u48) == val_0 ));
    C((stdc_count_ones(zero_u64) == val_0 ));
    C((stdc_count_ones( one_u8 ) == val_1 ));
    C((stdc_count_ones( one_u16) == val_1 ));
    C((stdc_count_ones( one_u24) == val_1 ));
    C((stdc_count_ones( one_u32) == val_1 ));
    C((stdc_count_ones( one_u48) == val_1 ));
    C((stdc_count_ones( one_u64) == val_1 ));
    C((stdc_count_ones(umax_u8 ) == val_8 ));
    C((stdc_count_ones(umax_u16) == val_16));
    C((stdc_count_ones(umax_u24) == val_24));
    C((stdc_count_ones(umax_u32) == val_32));
    C((stdc_count_ones(umax_u48) == val_48));
    C((stdc_count_ones(umax_u64) == val_64));
    C((stdc_count_ones(smax_u8 ) == val_7 ));
    C((stdc_count_ones(smax_u16) == val_15));
    C((stdc_count_ones(smax_u24) == val_23));
    C((stdc_count_ones(smax_u32) == val_31));
    C((stdc_count_ones(smax_u48) == val_47));
    C((stdc_count_ones(smax_u64) == val_63));
    C((stdc_count_ones(smin_u8 ) == val_1 ));
    C((stdc_count_ones(smin_u16) == val_1 ));
    C((stdc_count_ones(smin_u24) == val_1 ));
    C((stdc_count_ones(smin_u32) == val_1 ));
    C((stdc_count_ones(smin_u48) == val_1 ));
    C((stdc_count_ones(smin_u64) == val_1 ));
    return 0;
}

int test_count_zeros(void) {
    C((stdc_count_zeros(zero_u8 ) == val_8 ));
    C((stdc_count_zeros(zero_u16) == val_16));
    C((stdc_count_zeros(zero_u24) == val_24));
    C((stdc_count_zeros(zero_u32) == val_32));
    C((stdc_count_zeros(zero_u48) == val_48));
    C((stdc_count_zeros(zero_u64) == val_64));
    C((stdc_count_zeros( one_u8 ) == val_7 ));
    C((stdc_count_zeros( one_u16) == val_15));
    C((stdc_count_zeros( one_u24) == val_23));
    C((stdc_count_zeros( one_u32) == val_31));
    C((stdc_count_zeros( one_u48) == val_47));
    C((stdc_count_zeros( one_u64) == val_63));
    C((stdc_count_zeros(umax_u8 ) == val_0 ));
    C((stdc_count_zeros(umax_u16) == val_0 ));
    C((stdc_count_zeros(umax_u24) == val_0 ));
    C((stdc_count_zeros(umax_u32) == val_0 ));
    C((stdc_count_zeros(umax_u48) == val_0 ));
    C((stdc_count_zeros(umax_u64) == val_0 ));
    C((stdc_count_zeros(smax_u8 ) == val_1 ));
    C((stdc_count_zeros(smax_u16) == val_1 ));
    C((stdc_count_zeros(smax_u24) == val_1 ));
    C((stdc_count_zeros(smax_u32) == val_1 ));
    C((stdc_count_zeros(smax_u48) == val_1 ));
    C((stdc_count_zeros(smax_u64) == val_1 ));
    C((stdc_count_zeros(smin_u8 ) == val_7 ));
    C((stdc_count_zeros(smin_u16) == val_15));
    C((stdc_count_zeros(smin_u24) == val_23));
    C((stdc_count_zeros(smin_u32) == val_31));
    C((stdc_count_zeros(smin_u48) == val_47));
    C((stdc_count_zeros(smin_u64) == val_63));
    return 0;
}

int test_stdbit(void) {
    int ret = 0;
    TEST(test_leading_zeros());
    TEST(test_leading_ones());
    TEST(test_trailing_zeros());
    TEST(test_trailing_ones());
    TEST(test_first_leading_one());
    TEST(test_first_leading_zero());
    TEST(test_first_trailing_one());
    TEST(test_first_trailing_zero());
    TEST(test_bit_width());
    TEST(test_bit_ceil());
    TEST(test_bit_floor());
    TEST(test_count_ones());
    TEST(test_count_zeros());
    return 0;
}
