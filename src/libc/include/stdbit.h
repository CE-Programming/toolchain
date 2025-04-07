#ifndef _STDBIT_H
#define _STDBIT_H

#include <cdefs.h>
#include <stdbool.h>
#include <ez80_builtin.h>

#ifdef __cplusplus
extern "C" {
#endif

// #define __STDC_VERSION_STDBIT_H__ 202311L

#define __STDC_ENDIAN_LITTLE__ __ORDER_LITTLE_ENDIAN__
#define __STDC_ENDIAN_BIG__ __ORDER_BIG_ENDIAN__
#define __STDC_ENDIAN_NATIVE__ __BYTE_ORDER__

//------------------------------------------------------------------------------
// stdc_leading_zeros
//------------------------------------------------------------------------------

#define stdc_leading_zeros_uc(x) \
__ez80_clzc(x)

#define stdc_leading_zeros_us(x) \
__builtin_clzs(x)

#define stdc_leading_zeros_ui(x) \
__builtin_clz(x)

#define stdc_leading_zeros_ul(x) \
__builtin_clzl(x)

#define stdc_leading_zeros_ui48(x) \
__ez80_clzi48(x)

#define stdc_leading_zeros_ull(x) \
__builtin_clzll(x)

//------------------------------------------------------------------------------
// stdc_leading_ones
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_trailing_zeros
//------------------------------------------------------------------------------

#define stdc_trailing_zeros_uc(x) \
__ez80_ctzc(x)

#define stdc_trailing_zeros_us(x) \
__builtin_ctzs(x)

#define stdc_trailing_zeros_ui(x) \
__builtin_ctz(x)

#define stdc_trailing_zeros_ul(x) \
__builtin_ctzl(x)

#define stdc_trailing_zeros_ui48(x) \
__ez80_ctzi48(x)

#define stdc_trailing_zeros_ull(x) \
__builtin_ctzll(x)

//------------------------------------------------------------------------------
// stdc_trailing_ones
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_first_leading_zero
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_first_trailing_one
//------------------------------------------------------------------------------

#define stdc_first_trailing_one_uc(x) \
__ez80_ffsc(x)

#define stdc_first_trailing_one_us(x) \
__ez80_ffss(x)

#define stdc_first_trailing_one_ui(x) \
__builtin_ffs(x)

#define stdc_first_trailing_one_ul(x) \
__builtin_ffsl(x)

#define stdc_first_trailing_one_ui48(x) \
__ez80_ffsi48(x)

#define stdc_first_trailing_one_ull(x) \
__builtin_ffsll(x)

//------------------------------------------------------------------------------
// stdc_first_trailing_zero
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_count_ones
//------------------------------------------------------------------------------

#define stdc_count_ones_uc(x) \
__ez80_popcountc(x)
#define stdc_count_ones_us(x) \
__ez80_popcounts(x)
#define stdc_count_ones_ui(x) \
__builtin_popcount(x)
#define stdc_count_ones_ul(x) \
__builtin_popcountl(x)
#define stdc_count_ones_ui48(x) \
__ez80_popcounti48(x)
#define stdc_count_ones_ull(x) \
__builtin_popcountll(x)

//------------------------------------------------------------------------------
// stdc_count_zeros
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_has_single_bit
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_bit_width
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_bit_floor
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// stdc_rotate_left
//------------------------------------------------------------------------------

#define stdc_rotate_left_uc(x, s) \
__builtin_rotateleft8(x, s)

#define stdc_rotate_left_us(x, s) \
__builtin_rotateleft16(x, s)

#define stdc_rotate_left_ui(x, s) \
__ez80_rotateleft24(x, s)

#define stdc_rotate_left_ul(x, s) \
__builtin_rotateleft32(x, s)

#define stdc_rotate_left_ui48(x, s) \
__ez80_rotateleft48(x, s)

#define stdc_rotate_left_ull(x, s) \
__builtin_rotateleft64(x, s)

//------------------------------------------------------------------------------
// stdc_rotate_right
//------------------------------------------------------------------------------

#define stdc_rotate_right_uc(x, s) \
__builtin_rotateright8(x, s)

#define stdc_rotate_right_us(x, s) \
__builtin_rotateright16(x, s)

#define stdc_rotate_right_ui(x, s) \
__ez80_rotateright24(x, s)

#define stdc_rotate_right_ul(x, s) \
__builtin_rotateright32(x, s)

#define stdc_rotate_right_ui48(x, s) \
__ez80_rotateright48(x, s)

#define stdc_rotate_right_ull(x, s) \
__builtin_rotateright64(x, s)

#ifdef __cplusplus
}
#endif

#endif /* _STDBIT_H */
