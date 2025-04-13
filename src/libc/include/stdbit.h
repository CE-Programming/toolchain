#ifndef _STDBIT_H
#define _STDBIT_H

#include <cdefs.h>
#include <stdbool.h>
#include <ez80_builtin.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __STDC_VERSION_STDBIT_H__ 202311L

#define __STDC_ENDIAN_LITTLE__ __ORDER_LITTLE_ENDIAN__
#define __STDC_ENDIAN_BIG__ __ORDER_BIG_ENDIAN__
#define __STDC_ENDIAN_NATIVE__ __BYTE_ORDER__

//------------------------------------------------------------------------------
// prototypes
//------------------------------------------------------------------------------

unsigned int stdc_leading_zeros_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_leading_zeros_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_leading_zeros_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_leading_zeros_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_leading_zeros_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_leading_zeros_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_leading_ones_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_leading_ones_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_leading_ones_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_leading_ones_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_leading_ones_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_leading_ones_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_trailing_zeros_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_trailing_zeros_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_trailing_zeros_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_trailing_zeros_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_trailing_zeros_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_trailing_zeros_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_trailing_ones_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_trailing_ones_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_trailing_ones_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_trailing_ones_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_trailing_ones_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_trailing_ones_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_first_leading_zero_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_zero_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_zero_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_zero_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_zero_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_zero_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_first_leading_one_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_one_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_one_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_one_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_one_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_first_leading_one_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_first_trailing_zero_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_zero_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_zero_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_zero_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_zero_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_zero_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_first_trailing_one_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_one_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_one_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_one_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_one_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_first_trailing_one_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_count_zeros_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_count_zeros_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_count_zeros_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_count_zeros_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_count_zeros_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_count_zeros_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_count_ones_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_count_ones_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_count_ones_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_count_ones_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_count_ones_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_count_ones_ull(unsigned long long) __NOEXCEPT_CONST;

bool stdc_has_single_bit_uc(unsigned char) __NOEXCEPT_CONST;
bool stdc_has_single_bit_us(unsigned short) __NOEXCEPT_CONST;
bool stdc_has_single_bit_ui(unsigned int) __NOEXCEPT_CONST;
bool stdc_has_single_bit_ul(unsigned long) __NOEXCEPT_CONST;
bool stdc_has_single_bit_ui48(unsigned __int48) __NOEXCEPT_CONST;
bool stdc_has_single_bit_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned int stdc_bit_width_uc(unsigned char) __NOEXCEPT_CONST;
unsigned int stdc_bit_width_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_bit_width_ui(unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_bit_width_ul(unsigned long) __NOEXCEPT_CONST;
unsigned int stdc_bit_width_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned int stdc_bit_width_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned char stdc_bit_floor_uc(unsigned char) __NOEXCEPT_CONST;
unsigned short stdc_bit_floor_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_bit_floor_ui(unsigned int) __NOEXCEPT_CONST;
unsigned long stdc_bit_floor_ul(unsigned long) __NOEXCEPT_CONST;
unsigned __int48 stdc_bit_floor_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned long long stdc_bit_floor_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned char stdc_bit_ceil_uc(unsigned char) __NOEXCEPT_CONST;
unsigned short stdc_bit_ceil_us(unsigned short) __NOEXCEPT_CONST;
unsigned int stdc_bit_ceil_ui(unsigned int) __NOEXCEPT_CONST;
unsigned long stdc_bit_ceil_ul(unsigned long) __NOEXCEPT_CONST;
unsigned __int48 stdc_bit_ceil_ui48(unsigned __int48) __NOEXCEPT_CONST;
unsigned long long stdc_bit_ceil_ull(unsigned long long) __NOEXCEPT_CONST;

unsigned char stdc_rotate_left_uc(unsigned char, unsigned int) __NOEXCEPT_CONST;
unsigned short stdc_rotate_left_us(unsigned short, unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_rotate_left_ui(unsigned int, unsigned int) __NOEXCEPT_CONST;
unsigned long stdc_rotate_left_ul(unsigned long, unsigned int) __NOEXCEPT_CONST;
unsigned __int48 stdc_rotate_left_ui48(unsigned __int48, unsigned int) __NOEXCEPT_CONST;
unsigned long long stdc_rotate_left_ull(unsigned long long, unsigned int) __NOEXCEPT_CONST;

unsigned char stdc_rotate_right_uc(unsigned char, unsigned int) __NOEXCEPT_CONST;
unsigned short stdc_rotate_right_us(unsigned short, unsigned int) __NOEXCEPT_CONST;
unsigned int stdc_rotate_right_ui(unsigned int, unsigned int) __NOEXCEPT_CONST;
unsigned long stdc_rotate_right_ul(unsigned long, unsigned int) __NOEXCEPT_CONST;
unsigned __int48 stdc_rotate_right_ui48(unsigned __int48, unsigned int) __NOEXCEPT_CONST;
unsigned long long stdc_rotate_right_ull(unsigned long long, unsigned int) __NOEXCEPT_CONST;

//------------------------------------------------------------------------------
// stdc_leading_zeros
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_zeros_uc(unsigned char __x) {
    return __ez80_clzc(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_zeros_us(unsigned short __x) {
    return __builtin_clzs(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_zeros_ui(unsigned int __x) {
    return __builtin_clz(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_zeros_ul(unsigned long __x) {
    return __builtin_clzl(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_zeros_ui48(unsigned __int48 __x) {
    return __ez80_clzi48(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_zeros_ull(unsigned long long __x) {
    return __builtin_clzll(__x);
}

#define stdc_leading_zeros_uc(x) \
__stdc_leading_zeros_uc(x)

#define stdc_leading_zeros_us(x) \
__stdc_leading_zeros_us(x)

#define stdc_leading_zeros_ui(x) \
__stdc_leading_zeros_ui(x)

#define stdc_leading_zeros_ul(x) \
__stdc_leading_zeros_ul(x)

#define stdc_leading_zeros_ui48(x) \
__stdc_leading_zeros_ui48(x)

#define stdc_leading_zeros_ull(x) \
__stdc_leading_zeros_ull(x)

#define stdc_leading_zeros(x) _Generic((x), \
    unsigned char:      __stdc_leading_zeros_uc, \
    unsigned short:     __stdc_leading_zeros_us, \
    unsigned int:       __stdc_leading_zeros_ui, \
    unsigned long:      __stdc_leading_zeros_ul, \
    unsigned __int48:   __stdc_leading_zeros_ui48, \
    unsigned long long: __stdc_leading_zeros_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_leading_ones
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_ones_uc(unsigned char __x) {
    return __stdc_leading_zeros_uc(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_ones_us(unsigned short __x) {
    return __stdc_leading_zeros_us(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_ones_ui(unsigned int __x) {
    return __stdc_leading_zeros_ui(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_ones_ul(unsigned long __x) {
    return __stdc_leading_zeros_ul(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_ones_ui48(unsigned __int48 __x) {
    return __stdc_leading_zeros_ui48(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_leading_ones_ull(unsigned long long __x) {
    return __stdc_leading_zeros_ull(~__x);
}

#define stdc_leading_ones_uc(x) \
__stdc_leading_ones_uc(x)

#define stdc_leading_ones_us(x) \
__stdc_leading_ones_us(x)

#define stdc_leading_ones_ui(x) \
__stdc_leading_ones_ui(x)

#define stdc_leading_ones_ul(x) \
__stdc_leading_ones_ul(x)

#define stdc_leading_ones_ui48(x) \
__stdc_leading_ones_ui48(x)

#define stdc_leading_ones_ull(x) \
__stdc_leading_ones_ull(x)

#define stdc_leading_ones(x) _Generic((x), \
    unsigned char:      __stdc_leading_ones_uc, \
    unsigned short:     __stdc_leading_ones_us, \
    unsigned int:       __stdc_leading_ones_ui, \
    unsigned long:      __stdc_leading_ones_ul, \
    unsigned __int48:   __stdc_leading_ones_ui48, \
    unsigned long long: __stdc_leading_ones_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_trailing_zeros
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_zeros_uc(unsigned char __x) {
    return __ez80_ctzc(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_zeros_us(unsigned short __x) {
    return __builtin_ctzs(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_zeros_ui(unsigned int __x) {
    return __builtin_ctz(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_zeros_ul(unsigned long __x) {
    return __builtin_ctzl(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_zeros_ui48(unsigned __int48 __x) {
    return __ez80_ctzi48(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_zeros_ull(unsigned long long __x) {
    return __builtin_ctzll(__x);
}

#define stdc_trailing_zeros_uc(x) \
__stdc_trailing_zeros_uc(x)

#define stdc_trailing_zeros_us(x) \
__stdc_trailing_zeros_us(x)

#define stdc_trailing_zeros_ui(x) \
__stdc_trailing_zeros_ui(x)

#define stdc_trailing_zeros_ul(x) \
__stdc_trailing_zeros_ul(x)

#define stdc_trailing_zeros_ui48(x) \
__stdc_trailing_zeros_ui48(x)

#define stdc_trailing_zeros_ull(x) \
__stdc_trailing_zeros_ull(x)

#define stdc_trailing_zeros(x) _Generic((x), \
    unsigned char:      __stdc_trailing_zeros_uc, \
    unsigned short:     __stdc_trailing_zeros_us, \
    unsigned int:       __stdc_trailing_zeros_ui, \
    unsigned long:      __stdc_trailing_zeros_ul, \
    unsigned __int48:   __stdc_trailing_zeros_ui48, \
    unsigned long long: __stdc_trailing_zeros_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_trailing_ones
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_ones_uc(unsigned char __x) {
    return __stdc_trailing_zeros_uc(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_ones_us(unsigned short __x) {
    return __stdc_trailing_zeros_us(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_ones_ui(unsigned int __x) {
    return __stdc_trailing_zeros_ui(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_ones_ul(unsigned long __x) {
    return __stdc_trailing_zeros_ul(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_ones_ui48(unsigned __int48 __x) {
    return __stdc_trailing_zeros_ui48(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_trailing_ones_ull(unsigned long long __x) {
    return __stdc_trailing_zeros_ull(~__x);
}

#define stdc_trailing_ones_uc(x) \
__stdc_trailing_ones_uc(x)

#define stdc_trailing_ones_us(x) \
__stdc_trailing_ones_us(x)

#define stdc_trailing_ones_ui(x) \
__stdc_trailing_ones_ui(x)

#define stdc_trailing_ones_ul(x) \
__stdc_trailing_ones_ul(x)

#define stdc_trailing_ones_ui48(x) \
__stdc_trailing_ones_ui48(x)

#define stdc_trailing_ones_ull(x) \
__stdc_trailing_ones_ull(x)

#define stdc_trailing_ones(x) _Generic((x), \
    unsigned char:      __stdc_trailing_ones_uc, \
    unsigned short:     __stdc_trailing_ones_us, \
    unsigned int:       __stdc_trailing_ones_ui, \
    unsigned long:      __stdc_trailing_ones_ul, \
    unsigned __int48:   __stdc_trailing_ones_ui48, \
    unsigned long long: __stdc_trailing_ones_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_first_leading_one
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_one_uc(unsigned char __x) {
    return (__x == 0) ? 0 : (__stdc_leading_zeros_uc(__x) + 1);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_one_us(unsigned short __x) {
    return (__x == 0) ? 0 : (__stdc_leading_zeros_us(__x) + 1);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_one_ui(unsigned int __x) {
    return (__x == 0) ? 0 : (__stdc_leading_zeros_ui(__x) + 1);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_one_ul(unsigned long __x) {
    return (__x == 0) ? 0 : (__stdc_leading_zeros_ul(__x) + 1);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_one_ui48(unsigned __int48 __x) {
    return (__x == 0) ? 0 : (__stdc_leading_zeros_ui48(__x) + 1);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_one_ull(unsigned long long __x) {
    return (__x == 0) ? 0 : (__stdc_leading_zeros_ull(__x) + 1);
}

#define stdc_first_leading_one_uc(x) \
__stdc_first_leading_one_uc(x)

#define stdc_first_leading_one_us(x) \
__stdc_first_leading_one_us(x)

#define stdc_first_leading_one_ui(x) \
__stdc_first_leading_one_ui(x)

#define stdc_first_leading_one_ul(x) \
__stdc_first_leading_one_ul(x)

#define stdc_first_leading_one_ui48(x) \
__stdc_first_leading_one_ui48(x)

#define stdc_first_leading_one_ull(x) \
__stdc_first_leading_one_ull(x)

#define stdc_first_leading_one(x) _Generic((x), \
    unsigned char:      __stdc_first_leading_one_uc, \
    unsigned short:     __stdc_first_leading_one_us, \
    unsigned int:       __stdc_first_leading_one_ui, \
    unsigned long:      __stdc_first_leading_one_ul, \
    unsigned __int48:   __stdc_first_leading_one_ui48, \
    unsigned long long: __stdc_first_leading_one_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_first_leading_zero
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_zero_uc(unsigned char __x) {
    return __stdc_first_leading_one_uc(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_zero_us(unsigned short __x) {
    return __stdc_first_leading_one_us(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_zero_ui(unsigned int __x) {
    return __stdc_first_leading_one_ui(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_zero_ul(unsigned long __x) {
    return __stdc_first_leading_one_ul(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_zero_ui48(unsigned __int48 __x) {
    return __stdc_first_leading_one_ui48(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_leading_zero_ull(unsigned long long __x) {
    return __stdc_first_leading_one_ull(~__x);
}

#define stdc_first_leading_zero_uc(x) \
__stdc_first_leading_zero_uc(x)

#define stdc_first_leading_zero_us(x) \
__stdc_first_leading_zero_us(x)

#define stdc_first_leading_zero_ui(x) \
__stdc_first_leading_zero_ui(x)

#define stdc_first_leading_zero_ul(x) \
__stdc_first_leading_zero_ul(x)

#define stdc_first_leading_zero_ui48(x) \
__stdc_first_leading_zero_ui48(x)

#define stdc_first_leading_zero_ull(x) \
__stdc_first_leading_zero_ull(x)

#define stdc_first_leading_zero(x) _Generic((x), \
    unsigned char:      __stdc_first_leading_zero_uc, \
    unsigned short:     __stdc_first_leading_zero_us, \
    unsigned int:       __stdc_first_leading_zero_ui, \
    unsigned long:      __stdc_first_leading_zero_ul, \
    unsigned __int48:   __stdc_first_leading_zero_ui48, \
    unsigned long long: __stdc_first_leading_zero_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_first_trailing_one
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_one_uc(unsigned char __x) {
    return __ez80_ffsc(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_one_us(unsigned short __x) {
    return __ez80_ffss(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_one_ui(unsigned int __x) {
    return __builtin_ffs(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_one_ul(unsigned long __x) {
    return __builtin_ffsl(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_one_ui48(unsigned __int48 __x) {
    return __ez80_ffsi48(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_one_ull(unsigned long long __x) {
    return __builtin_ffsll(__x);
}

#define stdc_first_trailing_one_uc(x) \
__stdc_first_trailing_one_uc(x)

#define stdc_first_trailing_one_us(x) \
__stdc_first_trailing_one_us(x)

#define stdc_first_trailing_one_ui(x) \
__stdc_first_trailing_one_ui(x)

#define stdc_first_trailing_one_ul(x) \
__stdc_first_trailing_one_ul(x)

#define stdc_first_trailing_one_ui48(x) \
__stdc_first_trailing_one_ui48(x)

#define stdc_first_trailing_one_ull(x) \
__stdc_first_trailing_one_ull(x)

#define stdc_first_trailing_one(x) _Generic((x), \
    unsigned char:      __stdc_first_trailing_one_uc, \
    unsigned short:     __stdc_first_trailing_one_us, \
    unsigned int:       __stdc_first_trailing_one_ui, \
    unsigned long:      __stdc_first_trailing_one_ul, \
    unsigned __int48:   __stdc_first_trailing_one_ui48, \
    unsigned long long: __stdc_first_trailing_one_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_first_trailing_zero
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_zero_uc(unsigned char __x) {
    return __stdc_first_trailing_one_uc(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_zero_us(unsigned short __x) {
    return __stdc_first_trailing_one_us(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_zero_ui(unsigned int __x) {
    return __stdc_first_trailing_one_ui(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_zero_ul(unsigned long __x) {
    return __stdc_first_trailing_one_ul(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_zero_ui48(unsigned __int48 __x) {
    return __stdc_first_trailing_one_ui48(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_first_trailing_zero_ull(unsigned long long __x) {
    return __stdc_first_trailing_one_ull(~__x);
}

#define stdc_first_trailing_zero_uc(x) \
__stdc_first_trailing_zero_uc(x)

#define stdc_first_trailing_zero_us(x) \
__stdc_first_trailing_zero_us(x)

#define stdc_first_trailing_zero_ui(x) \
__stdc_first_trailing_zero_ui(x)

#define stdc_first_trailing_zero_ul(x) \
__stdc_first_trailing_zero_ul(x)

#define stdc_first_trailing_zero_ui48(x) \
__stdc_first_trailing_zero_ui48(x)

#define stdc_first_trailing_zero_ull(x) \
__stdc_first_trailing_zero_ull(x)

#define stdc_first_trailing_zero(x) _Generic((x), \
    unsigned char:      __stdc_first_trailing_zero_uc, \
    unsigned short:     __stdc_first_trailing_zero_us, \
    unsigned int:       __stdc_first_trailing_zero_ui, \
    unsigned long:      __stdc_first_trailing_zero_ul, \
    unsigned __int48:   __stdc_first_trailing_zero_ui48, \
    unsigned long long: __stdc_first_trailing_zero_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_count_ones
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_count_ones_uc(unsigned char __x) {
    return __ez80_popcountc(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_ones_us(unsigned short __x) {
    return __ez80_popcounts(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_ones_ui(unsigned int __x) {
    return __builtin_popcount(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_ones_ul(unsigned long __x) {
    return __builtin_popcountl(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_ones_ui48(unsigned __int48 __x) {
    return __ez80_popcounti48(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_ones_ull(unsigned long long __x) {
    return __builtin_popcountll(__x);
}

#define stdc_count_ones_uc(x) \
__stdc_count_ones_uc(x)

#define stdc_count_ones_us(x) \
__stdc_count_ones_us(x)

#define stdc_count_ones_ui(x) \
__stdc_count_ones_ui(x)

#define stdc_count_ones_ul(x) \
__stdc_count_ones_ul(x)

#define stdc_count_ones_ui48(x) \
__stdc_count_ones_ui48(x)

#define stdc_count_ones_ull(x) \
__stdc_count_ones_ull(x)

#define stdc_count_ones(x) _Generic((x), \
    unsigned char:      __stdc_count_ones_uc, \
    unsigned short:     __stdc_count_ones_us, \
    unsigned int:       __stdc_count_ones_ui, \
    unsigned long:      __stdc_count_ones_ul, \
    unsigned __int48:   __stdc_count_ones_ui48, \
    unsigned long long: __stdc_count_ones_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_count_zeros
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_count_zeros_uc(unsigned char __x) {
    return __stdc_count_ones_uc(~__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_zeros_us(unsigned short __x) {
    return 16 - __stdc_count_ones_us(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_zeros_ui(unsigned int __x) {
    return 24 - __stdc_count_ones_ui(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_zeros_ul(unsigned long __x) {
    return 32 - __stdc_count_ones_ul(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_zeros_ui48(unsigned __int48 __x) {
    return 48 - __stdc_count_ones_ui48(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_count_zeros_ull(unsigned long long __x) {
    return 64 - __stdc_count_ones_ull(__x);
}

#define stdc_count_zeros_uc(x) \
__stdc_count_zeros_uc(x)

#define stdc_count_zeros_us(x) \
__stdc_count_zeros_us(x)

#define stdc_count_zeros_ui(x) \
__stdc_count_zeros_ui(x)

#define stdc_count_zeros_ul(x) \
__stdc_count_zeros_ul(x)

#define stdc_count_zeros_ui48(x) \
__stdc_count_zeros_ui48(x)

#define stdc_count_zeros_ull(x) \
__stdc_count_zeros_ull(x)

#define stdc_count_zeros(x) _Generic((x), \
    unsigned char:      __stdc_count_zeros_uc, \
    unsigned short:     __stdc_count_zeros_us, \
    unsigned int:       __stdc_count_zeros_ui, \
    unsigned long:      __stdc_count_zeros_ul, \
    unsigned __int48:   __stdc_count_zeros_ui48, \
    unsigned long long: __stdc_count_zeros_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_has_single_bit
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
bool __stdc_has_single_bit_uc(unsigned char __x) {
    return (__x != 0 && (__x & (__x - 1)) == 0);
}
static inline __attribute__((__always_inline__))
bool __stdc_has_single_bit_us(unsigned short __x) {
    return (__x != 0 && (__x & (__x - 1)) == 0);
}
static inline __attribute__((__always_inline__))
bool __stdc_has_single_bit_ui(unsigned int __x) {
    return (__x != 0 && (__x & (__x - 1)) == 0);
}
static inline __attribute__((__always_inline__))
bool __stdc_has_single_bit_ul(unsigned long __x) {
    return (__x != 0 && (__x & (__x - 1)) == 0);
}
static inline __attribute__((__always_inline__))
bool __stdc_has_single_bit_ui48(unsigned __int48 __x) {
    return (__x != 0 && (__x & (__x - 1)) == 0);
}
static inline __attribute__((__always_inline__))
bool __stdc_has_single_bit_ull(unsigned long long __x) {
    return (__x != 0 && (__x & (__x - 1)) == 0);
}

#define stdc_has_single_bit_uc(x) \
__stdc_has_single_bit_uc(x)

#define stdc_has_single_bit_us(x) \
__stdc_has_single_bit_us(x)

#define stdc_has_single_bit_ui(x) \
__stdc_has_single_bit_ui(x)

#define stdc_has_single_bit_ul(x) \
__stdc_has_single_bit_ul(x)

#define stdc_has_single_bit_ui48(x) \
__stdc_has_single_bit_ui48(x)

#define stdc_has_single_bit_ull(x) \
__stdc_has_single_bit_ull(x)

#define stdc_has_single_bit(x) _Generic((x), \
    unsigned char:      __stdc_has_single_bit_uc, \
    unsigned short:     __stdc_has_single_bit_us, \
    unsigned int:       __stdc_has_single_bit_ui, \
    unsigned long:      __stdc_has_single_bit_ul, \
    unsigned __int48:   __stdc_has_single_bit_ui48, \
    unsigned long long: __stdc_has_single_bit_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_bit_width
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_width_uc(unsigned char __x) {
    return 8 - __stdc_leading_zeros_uc(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_width_us(unsigned short __x) {
    return 16 - __stdc_leading_zeros_us(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_width_ui(unsigned int __x) {
    return 24 - __stdc_leading_zeros_ui(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_width_ul(unsigned long __x) {
    return 32 - __stdc_leading_zeros_ul(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_width_ui48(unsigned __int48 __x) {
    return 48 - __stdc_leading_zeros_ui48(__x);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_width_ull(unsigned long long __x) {
    return 64 - __stdc_leading_zeros_ull(__x);
}

#define stdc_bit_width_uc(x) \
__stdc_bit_width_uc(x)

#define stdc_bit_width_us(x) \
__stdc_bit_width_us(x)

#define stdc_bit_width_ui(x) \
__stdc_bit_width_ui(x)

#define stdc_bit_width_ul(x) \
__stdc_bit_width_ul(x)

#define stdc_bit_width_ui48(x) \
__stdc_bit_width_ui48(x)

#define stdc_bit_width_ull(x) \
__stdc_bit_width_ull(x)

#define stdc_bit_width(x) _Generic((x), \
    unsigned char:      __stdc_bit_width_uc, \
    unsigned short:     __stdc_bit_width_us, \
    unsigned int:       __stdc_bit_width_ui, \
    unsigned long:      __stdc_bit_width_ul, \
    unsigned __int48:   __stdc_bit_width_ui48, \
    unsigned long long: __stdc_bit_width_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_bit_ceil
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned char __stdc_bit_ceil_uc(unsigned char __x) {
    return ((__x < 2) ? 1 : ((unsigned char)(2) << (__stdc_bit_width_uc(__x - 1) - 1)));
}
static inline __attribute__((__always_inline__))
unsigned short __stdc_bit_ceil_us(unsigned short __x) {
    return ((__x < 2) ? 1 : ((unsigned short)(2) << (__stdc_bit_width_us(__x - 1) - 1)));
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_ceil_ui(unsigned int __x) {
    return ((__x < 2) ? 1 : ((unsigned int)(2) << (__stdc_bit_width_ui(__x - 1) - 1)));
}
static inline __attribute__((__always_inline__))
unsigned long __stdc_bit_ceil_ul(unsigned long __x) {
    return ((__x < 2) ? 1 : ((unsigned long)(2) << (__stdc_bit_width_ul(__x - 1) - 1)));
}
static inline __attribute__((__always_inline__))
unsigned __int48 __stdc_bit_ceil_ui48(unsigned __int48 __x) {
    return ((__x < 2) ? 1 : ((unsigned __int48)(2) << (__stdc_bit_width_ui48(__x - 1) - 1)));
}
static inline __attribute__((__always_inline__))
unsigned long long __stdc_bit_ceil_ull(unsigned long long __x) {
    return ((__x < 2) ? 1 : ((unsigned long long)(2) << (__stdc_bit_width_ull(__x - 1) - 1)));
}

#define stdc_bit_ceil_uc(x) \
__stdc_bit_ceil_uc(x)

#define stdc_bit_ceil_us(x) \
__stdc_bit_ceil_us(x)

#define stdc_bit_ceil_ui(x) \
__stdc_bit_ceil_ui(x)

#define stdc_bit_ceil_ul(x) \
__stdc_bit_ceil_ul(x)

#define stdc_bit_ceil_ui48(x) \
__stdc_bit_ceil_ui48(x)

#define stdc_bit_ceil_ull(x) \
__stdc_bit_ceil_ull(x)

#define stdc_bit_ceil(x) _Generic((x), \
    unsigned char:      __stdc_bit_ceil_uc, \
    unsigned short:     __stdc_bit_ceil_us, \
    unsigned int:       __stdc_bit_ceil_ui, \
    unsigned long:      __stdc_bit_ceil_ul, \
    unsigned __int48:   __stdc_bit_ceil_ui48, \
    unsigned long long: __stdc_bit_ceil_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_bit_floor
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned char __stdc_bit_floor_uc(unsigned char __x) {
    return (__x == 0) ? 0 : ((unsigned char)(1) << (__stdc_bit_width_uc(__x) - 1));
}
static inline __attribute__((__always_inline__))
unsigned short __stdc_bit_floor_us(unsigned short __x) {
    return (__x == 0) ? 0 : ((unsigned short)(1) << (__stdc_bit_width_us(__x) - 1));
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_bit_floor_ui(unsigned int __x) {
    return (__x == 0) ? 0 : ((unsigned int)(1) << (__stdc_bit_width_ui(__x) - 1));
}
static inline __attribute__((__always_inline__))
unsigned long __stdc_bit_floor_ul(unsigned long __x) {
    return (__x == 0) ? 0 : ((unsigned long)(1) << (__stdc_bit_width_ul(__x) - 1));
}
static inline __attribute__((__always_inline__))
unsigned __int48 __stdc_bit_floor_ui48(unsigned __int48 __x) {
    return (__x == 0) ? 0 : ((unsigned __int48)(1) << (__stdc_bit_width_ui48(__x) - 1));
}
static inline __attribute__((__always_inline__))
unsigned long long __stdc_bit_floor_ull(unsigned long long __x) {
    return (__x == 0) ? 0 : ((unsigned long long)(1) << (__stdc_bit_width_ull(__x) - 1));
}

#define stdc_bit_floor_uc(x) \
__stdc_bit_floor_uc(x)

#define stdc_bit_floor_us(x) \
__stdc_bit_floor_us(x)

#define stdc_bit_floor_ui(x) \
__stdc_bit_floor_ui(x)

#define stdc_bit_floor_ul(x) \
__stdc_bit_floor_ul(x)

#define stdc_bit_floor_ui48(x) \
__stdc_bit_floor_ui48(x)

#define stdc_bit_floor_ull(x) \
__stdc_bit_floor_ull(x)

#define stdc_bit_floor(x) _Generic((x), \
    unsigned char:      __stdc_bit_floor_uc, \
    unsigned short:     __stdc_bit_floor_us, \
    unsigned int:       __stdc_bit_floor_ui, \
    unsigned long:      __stdc_bit_floor_ul, \
    unsigned __int48:   __stdc_bit_floor_ui48, \
    unsigned long long: __stdc_bit_floor_ull \
)(x)

//------------------------------------------------------------------------------
// stdc_rotate_left
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned char __stdc_rotate_left_uc(unsigned char __x, unsigned int __s) {
    return __builtin_rotateleft8(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned short __stdc_rotate_left_us(unsigned short __x, unsigned int __s) {
    return __builtin_rotateleft16(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_rotate_left_ui(unsigned int __x, unsigned int __s) {
    return __ez80_rotateleft24(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned long __stdc_rotate_left_ul(unsigned long __x, unsigned int __s) {
    return __builtin_rotateleft32(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned __int48 __stdc_rotate_left_ui48(unsigned __int48 __x, unsigned int __s) {
    return __ez80_rotateleft48(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned long long __stdc_rotate_left_ull(unsigned long long __x, unsigned int __s) {
    return __builtin_rotateleft64(__x, (unsigned char)__s);
}

#define stdc_rotate_left_uc(x, s) \
__stdc_rotate_left_uc(x, s)

#define stdc_rotate_left_us(x, s) \
__stdc_rotate_left_us(x, s)

#define stdc_rotate_left_ui(x, s) \
__stdc_rotate_left_ui(x, s)

#define stdc_rotate_left_ul(x, s) \
__stdc_rotate_left_ul(x, s)

#define stdc_rotate_left_ui48(x, s) \
__stdc_rotate_left_ui48(x, s)

#define stdc_rotate_left_ull(x, s) \
__stdc_rotate_left_ull(x, s)

#define stdc_rotate_left(x, s) _Generic((x), \
    unsigned char:      __stdc_rotate_left_uc, \
    unsigned short:     __stdc_rotate_left_us, \
    unsigned int:       __stdc_rotate_left_ui, \
    unsigned long:      __stdc_rotate_left_ul, \
    unsigned __int48:   __stdc_rotate_left_ui48, \
    unsigned long long: __stdc_rotate_left_ull \
)(x, s)

//------------------------------------------------------------------------------
// stdc_rotate_right
//------------------------------------------------------------------------------

static inline __attribute__((__always_inline__))
unsigned char __stdc_rotate_right_uc(unsigned char __x, unsigned int __s) {
    return __builtin_rotateright8(__x, __s);
}
static inline __attribute__((__always_inline__))
unsigned short __stdc_rotate_right_us(unsigned short __x, unsigned int __s) {
    return __builtin_rotateright16(__x, __s);
}
static inline __attribute__((__always_inline__))
unsigned int __stdc_rotate_right_ui(unsigned int __x, unsigned int __s) {
    return __ez80_rotateright24(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned long __stdc_rotate_right_ul(unsigned long __x, unsigned int __s) {
    return __builtin_rotateright32(__x, __s);
}
static inline __attribute__((__always_inline__))
unsigned __int48 __stdc_rotate_right_ui48(unsigned __int48 __x, unsigned int __s) {
    return __ez80_rotateright48(__x, (unsigned char)__s);
}
static inline __attribute__((__always_inline__))
unsigned long long __stdc_rotate_right_ull(unsigned long long __x, unsigned int __s) {
    return __builtin_rotateright64(__x, __s);
}

#define stdc_rotate_right_uc(x, s) \
__stdc_rotate_right_uc(x, s)

#define stdc_rotate_right_us(x, s) \
__stdc_rotate_right_us(x, s)

#define stdc_rotate_right_ui(x, s) \
__stdc_rotate_right_ui(x, s)

#define stdc_rotate_right_ul(x, s) \
__stdc_rotate_right_ul(x, s)

#define stdc_rotate_right_ui48(x, s) \
__stdc_rotate_right_ui48(x, s)

#define stdc_rotate_right_ull(x, s) \
__stdc_rotate_right_ull(x, s)

#define stdc_rotate_right(x, s) _Generic((x), \
    unsigned char:      __stdc_rotate_right_uc, \
    unsigned short:     __stdc_rotate_right_us, \
    unsigned int:       __stdc_rotate_right_ui, \
    unsigned long:      __stdc_rotate_right_ul, \
    unsigned __int48:   __stdc_rotate_right_ui48, \
    unsigned long long: __stdc_rotate_right_ull \
)(x, s)


#ifdef __cplusplus
}
#endif

#endif /* _STDBIT_H */
