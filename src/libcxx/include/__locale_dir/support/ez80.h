//===-----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___LOCALE_DIR_SUPPORT_EZ80_H
#define _LIBCPP___LOCALE_DIR_SUPPORT_EZ80_H

#include <__config>
#include <__cstddef/size_t.h>
#include <__std_mbstate_t.h>
#include <clocale> // std::lconv
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#if _LIBCPP_HAS_WIDE_CHARACTERS
#  include <cwchar>
#  include <wctype.h>
#endif

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD
namespace __locale {

struct __locale_guard {
  _LIBCPP_HIDE_FROM_ABI __locale_guard(locale_t& __loc) : __old_loc_(::uselocale(__loc)) {}

  _LIBCPP_HIDE_FROM_ABI ~__locale_guard() {
    if (__old_loc_)
      ::uselocale(__old_loc_);
  }

  locale_t __old_loc_;

  __locale_guard(__locale_guard const&)            = delete;
  __locale_guard& operator=(__locale_guard const&) = delete;
};

//
// Locale management
//
#define _LIBCPP_COLLATE_MASK LC_COLLATE_MASK
#define _LIBCPP_CTYPE_MASK LC_CTYPE_MASK
#define _LIBCPP_MONETARY_MASK LC_MONETARY_MASK
#define _LIBCPP_NUMERIC_MASK LC_NUMERIC_MASK
#define _LIBCPP_TIME_MASK LC_TIME_MASK
#define _LIBCPP_MESSAGES_MASK LC_MESSAGES_MASK
#define _LIBCPP_ALL_MASK LC_ALL_MASK
#define _LIBCPP_LC_ALL LC_ALL

using __locale_t _LIBCPP_NODEBUG = ::locale_t;

#if defined(_LIBCPP_BUILDING_LIBRARY)
using __lconv_t _LIBCPP_NODEBUG = std::lconv;

inline _LIBCPP_HIDE_FROM_ABI __locale_t __newlocale(int __category_mask, const char* __locale, __locale_t __base) {
  return ::newlocale(__category_mask, __locale, __base);
}

inline _LIBCPP_HIDE_FROM_ABI void __freelocale(__locale_t __loc) { ::freelocale(__loc); }

inline _LIBCPP_HIDE_FROM_ABI char* __setlocale(int __category, char const* __locale) {
  return ::setlocale(__category, __locale);
}

inline _LIBCPP_HIDE_FROM_ABI __lconv_t* __localeconv(__locale_t& __loc) {
  __locale_guard __current(__loc);
  return std::localeconv();
}
#endif // _LIBCPP_BUILDING_LIBRARY

//
// Character manipulation functions
//
#if defined(_LIBCPP_BUILDING_LIBRARY)

//
// Other functions
//
inline _LIBCPP_HIDE_FROM_ABI decltype(MB_CUR_MAX) __mb_len_max(__locale_t __loc) {
  __locale_guard __current(__loc);
  return MB_CUR_MAX;
}

#  if _LIBCPP_HAS_WIDE_CHARACTERS
inline _LIBCPP_HIDE_FROM_ABI wint_t __btowc(int __c, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::btowc(__c);
}

inline _LIBCPP_HIDE_FROM_ABI int __wctob(wint_t __c, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::wctob(__c);
}

inline _LIBCPP_HIDE_FROM_ABI size_t
__wcsnrtombs(char* __dest, const wchar_t** __src, size_t __nwc, size_t __len, mbstate_t* __ps, __locale_t __loc) {
  __locale_guard __current(__loc);
  return ::wcsnrtombs(__dest, __src, __nwc, __len, __ps); // non-standard
}

inline _LIBCPP_HIDE_FROM_ABI size_t __wcrtomb(char* __s, wchar_t __wc, mbstate_t* __ps, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::wcrtomb(__s, __wc, __ps);
}

inline _LIBCPP_HIDE_FROM_ABI size_t
__mbsnrtowcs(wchar_t* __dest, const char** __src, size_t __nms, size_t __len, mbstate_t* __ps, __locale_t __loc) {
  __locale_guard __current(__loc);
  return ::mbsnrtowcs(__dest, __src, __nms, __len, __ps); // non-standard
}

inline _LIBCPP_HIDE_FROM_ABI size_t
__mbrtowc(wchar_t* __pwc, const char* __s, size_t __n, mbstate_t* __ps, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::mbrtowc(__pwc, __s, __n, __ps);
}

inline _LIBCPP_HIDE_FROM_ABI int __mbtowc(wchar_t* __pwc, const char* __pmb, size_t __max, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::mbtowc(__pwc, __pmb, __max);
}

inline _LIBCPP_HIDE_FROM_ABI size_t __mbrlen(const char* __s, size_t __n, mbstate_t* __ps, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::mbrlen(__s, __n, __ps);
}

inline _LIBCPP_HIDE_FROM_ABI size_t
__mbsrtowcs(wchar_t* __dest, const char** __src, size_t __len, mbstate_t* __ps, __locale_t __loc) {
  __locale_guard __current(__loc);
  return std::mbsrtowcs(__dest, __src, __len, __ps);
}
#  endif // _LIBCPP_HAS_WIDE_CHARACTERS
#endif   // _LIBCPP_BUILDING_LIBRARY

#ifndef _LIBCPP_COMPILER_GCC // GCC complains that this can't be always_inline due to C-style varargs
_LIBCPP_HIDE_FROM_ABI
#endif
inline _LIBCPP_ATTRIBUTE_FORMAT(__printf__, 4, 5) int __snprintf(
    char* __s, size_t __n, __locale_t __loc, const char* __format, ...) {
  va_list __va;
  va_start(__va, __format);
  __locale_guard __current(__loc);
  int __res = std::vsnprintf(__s, __n, __format, __va);
  va_end(__va);
  return __res;
}

#ifndef _LIBCPP_COMPILER_GCC // GCC complains that this can't be always_inline due to C-style varargs
_LIBCPP_HIDE_FROM_ABI
#endif
inline _LIBCPP_ATTRIBUTE_FORMAT(__printf__, 3, 4) int __asprintf(
    char** __s, __locale_t __loc, const char* __format, ...) {
  va_list __va;
  va_start(__va, __format);
  __locale_guard __current(__loc);
  int __res = ::vasprintf(__s, __format, __va); // non-standard
  va_end(__va);
  return __res;
}
} // namespace __locale
_LIBCPP_END_NAMESPACE_STD

#include <__locale_dir/support/no_locale/characters.h>
#include <__locale_dir/support/no_locale/strtonum.h>

#endif // _LIBCPP___LOCALE_DIR_SUPPORT_EZ80_H
