#ifndef _STDINT_H
#define _STDINT_H

#include <cdefs.h>

typedef          __INT8_TYPE__                        int8_t;
#define            INT8_MIN                       (~__INT8_MAX__)
#define            INT8_MAX                         __INT8_MAX__
#define            INT8_WIDTH          __STDINT_WIDTH(INT8)
#define            INT8_C(C)            __STDINT_C(C, INT8)
typedef         __UINT8_TYPE__                       uint8_t;
#define           UINT8_MAX                        __UINT8_MAX__
#define           UINT8_WIDTH         __STDINT_WIDTH(UINT8)
#define           UINT8_C(C)           __STDINT_C(C, UINT8)
typedef     __INT_FAST8_TYPE__                   int_fast8_t;
#define       INT_FAST8_MIN                  (~__INT_FAST8_MAX__)
#define       INT_FAST8_MAX                    __INT_FAST8_MAX__
#define       INT_FAST8_WIDTH     __STDINT_WIDTH(INT_FAST8)
typedef    __UINT_FAST8_TYPE__                  uint_fast8_t;
#define      UINT_FAST8_MAX                   __UINT_FAST8_MAX__
#define      UINT_FAST8_WIDTH    __STDINT_WIDTH(UINT_FAST8)
typedef    __INT_LEAST8_TYPE__                  int_least8_t;
#define      INT_LEAST8_MIN                 (~__INT_LEAST8_MAX__)
#define      INT_LEAST8_MAX                   __INT_LEAST8_MAX__
#define      INT_LEAST8_WIDTH    __STDINT_WIDTH(INT_LEAST8)
typedef   __UINT_LEAST8_TYPE__                 uint_least8_t;
#define     UINT_LEAST8_MAX                  __UINT_LEAST8_MAX__
#define     UINT_LEAST8_WIDTH   __STDINT_WIDTH(UINT_LEAST8)

typedef         __INT16_TYPE__                       int16_t;
#define           INT16_MIN                      (~__INT16_MAX__)
#define           INT16_MAX                        __INT16_MAX__
#define           INT16_WIDTH         __STDINT_WIDTH(INT16)
#define           INT16_C(C)           __STDINT_C(C, INT16)
typedef        __UINT16_TYPE__                      uint16_t;
#define          UINT16_MAX                       __UINT16_MAX__
#define          UINT16_WIDTH        __STDINT_WIDTH(UINT16)
#define          UINT16_C(C)          __STDINT_C(C, UINT16)
typedef    __INT_FAST16_TYPE__                  int_fast16_t;
#define      INT_FAST16_MIN                 (~__INT_FAST16_MAX__)
#define      INT_FAST16_MAX                   __INT_FAST16_MAX__
#define      INT_FAST16_WIDTH    __STDINT_WIDTH(INT_FAST16)
typedef   __UINT_FAST16_TYPE__                 uint_fast16_t;
#define     UINT_FAST16_MAX                  __UINT_FAST16_MAX__
#define     UINT_FAST16_WIDTH   __STDINT_WIDTH(UINT_FAST16)
typedef   __INT_LEAST16_TYPE__                 int_least16_t;
#define     INT_LEAST16_MIN                (~__INT_LEAST16_MAX__)
#define     INT_LEAST16_MAX                  __INT_LEAST16_MAX__
#define     INT_LEAST16_WIDTH   __STDINT_WIDTH(INT_LEAST16)
typedef  __UINT_LEAST16_TYPE__                uint_least16_t;
#define    UINT_LEAST16_MAX                 __UINT_LEAST16_MAX__
#define    UINT_LEAST16_WIDTH  __STDINT_WIDTH(UINT_LEAST16)

#ifdef          __INT24_TYPE__
typedef         __INT24_TYPE__                       int24_t;
#define           INT24_MIN                      (~__INT24_MAX__)
#define           INT24_MAX                        __INT24_MAX__
#define           INT24_WIDTH         __STDINT_WIDTH(INT24)
#define           INT24_C(C)           __STDINT_C(C, INT24)
typedef        __UINT24_TYPE__                      uint24_t;
#define          UINT24_MAX                       __UINT24_MAX__
#define          UINT24_WIDTH        __STDINT_WIDTH(UINT24)
#define          UINT24_C(C)          __STDINT_C(C, UINT24)
#endif        /*__INT24_TYPE_*/

typedef         __INT32_TYPE__                       int32_t;
#define           INT32_MIN                      (~__INT32_MAX__)
#define           INT32_MAX                        __INT32_MAX__
#define           INT32_WIDTH         __STDINT_WIDTH(INT32)
#define           INT32_C(C)           __STDINT_C(C, INT32)
typedef        __UINT32_TYPE__                      uint32_t;
#define          UINT32_MAX                       __UINT32_MAX__
#define          UINT32_WIDTH        __STDINT_WIDTH(UINT32)
#define          UINT32_C(C)          __STDINT_C(C, UINT32)
typedef    __INT_FAST32_TYPE__                  int_fast32_t;
#define      INT_FAST32_MIN                 (~__INT_FAST32_MAX__)
#define      INT_FAST32_MAX                   __INT_FAST32_MAX__
#define      INT_FAST32_WIDTH    __STDINT_WIDTH(INT_FAST32)
typedef   __UINT_FAST32_TYPE__                 uint_fast32_t;
#define     UINT_FAST32_MAX                  __UINT_FAST32_MAX__
#define     UINT_FAST32_WIDTH   __STDINT_WIDTH(UINT_FAST32)
typedef   __INT_LEAST32_TYPE__                 int_least32_t;
#define     INT_LEAST32_MIN                (~__INT_LEAST32_MAX__)
#define     INT_LEAST32_MAX                  __INT_LEAST32_MAX__
#define     INT_LEAST32_WIDTH   __STDINT_WIDTH(INT_LEAST32)
typedef  __UINT_LEAST32_TYPE__                uint_least32_t;
#define    UINT_LEAST32_MAX                 __UINT_LEAST32_MAX__
#define    UINT_LEAST32_WIDTH  __STDINT_WIDTH(UINT_LEAST32)

#ifdef   __SIZEOF_INT48__
#define         __INT48_TYPE__              signed __int48
#define         __INT48_MAX__  ((__INT48_TYPE__)(__UINT48_MAX__>>1))
typedef         __INT48_TYPE__                       int48_t;
#define           INT48_MIN                      (~__INT48_MAX__)
#define           INT48_MAX                        __INT48_MAX__
#define           INT48_WIDTH         __STDINT_WIDTH(INT48)
#define           INT48_C(C)                     ((__INT48_TYPE__)(INT64_C(C)))
#define        __UINT48_TYPE__            unsigned __int48
#define        __UINT48_MAX__                   ((__UINT48_TYPE__)~0)
typedef        __UINT48_TYPE__                      uint48_t;
#define          UINT48_MAX                       __UINT48_MAX__
#define          UINT48_WIDTH        __STDINT_WIDTH(UINT48)
#define          UINT48_C(C)                    ((__UINT48_TYPE__)(UINT64_C(C)))
#endif /*__SIZEOF_INT48__*/

typedef         __INT64_TYPE__                       int64_t;
#define           INT64_MIN                      (~__INT64_MAX__)
#define           INT64_MAX                        __INT64_MAX__
#define           INT64_WIDTH         __STDINT_WIDTH(INT64)
#define           INT64_C(C)           __STDINT_C(C, INT64)
typedef        __UINT64_TYPE__                      uint64_t;
#define          UINT64_MAX                       __UINT64_MAX__
#define          UINT64_WIDTH        __STDINT_WIDTH(UINT64)
#define          UINT64_C(C)          __STDINT_C(C, UINT64)
typedef    __INT_FAST64_TYPE__                  int_fast64_t;
#define      INT_FAST64_MIN                 (~__INT_FAST64_MAX__)
#define      INT_FAST64_MAX                   __INT_FAST64_MAX__
#define      INT_FAST64_WIDTH    __STDINT_WIDTH(INT_FAST64)
typedef   __UINT_FAST64_TYPE__                 uint_fast64_t;
#define     UINT_FAST64_MAX                  __UINT_FAST64_MAX__
#define     UINT_FAST64_WIDTH   __STDINT_WIDTH(UINT_FAST64)
typedef   __INT_LEAST64_TYPE__                 int_least64_t;
#define     INT_LEAST64_MIN                (~__INT_LEAST64_MAX__)
#define     INT_LEAST64_MAX                  __INT_LEAST64_MAX__
#define     INT_LEAST64_WIDTH   __STDINT_WIDTH(INT_LEAST64)
typedef  __UINT_LEAST64_TYPE__                uint_least64_t;
#define    UINT_LEAST64_MAX                 __UINT_LEAST64_MAX__
#define    UINT_LEAST64_WIDTH  __STDINT_WIDTH(UINT_LEAST64)

#ifdef  __SIZEOF_INT128__
#define        __INT128_TYPE__             signed __int128
#define        __INT128_MAX__ ((__INT128_TYPE__)(__UINT128_MAX__>>1))
typedef        __INT128_TYPE__                      int128_t;
#define          INT128_MIN                     (~__INT128_MAX__)
#define          INT128_MAX                       __INT128_MAX__
#define          INT128_WIDTH        __STDINT_WIDTH(INT128)
#define       __UINT128_TYPE__           unsigned __int128
#define       __UINT128_MAX__                  ((__UINT128_TYPE__)~0)
typedef       __UINT128_TYPE__                     uint128_t;
#define         UINT128_MAX                      __UINT128_MAX__
#define         UINT128_WIDTH       __STDINT_WIDTH(UINT128)
#endif/*__SIZEOF_INT128__*/

typedef        __INTMAX_TYPE__                      intmax_t;
#define          INTMAX_MIN                     (~__INTMAX_MAX__)
#define          INTMAX_MAX                       __INTMAX_MAX__
#define          INTMAX_WIDTH                     __INTMAX_WIDTH__
#define          INTMAX_C(C)          __STDINT_C(C, INTMAX)
typedef       __UINTMAX_TYPE__                     uintmax_t;
#define         UINTMAX_MAX                      __UINTMAX_MAX__
#define         UINTMAX_WIDTH                    __UINTMAX_WIDTH__
#define         UINTMAX_C(C)         __STDINT_C(C, UINTMAX)

typedef        __INTPTR_TYPE__                      intptr_t;
#define          INTPTR_MIN                     (~__INTPTR_MAX__)
#define          INTPTR_MAX                       __INTPTR_MAX__
#define          INTPTR_WIDTH                     __INTPTR_WIDTH__
typedef       __UINTPTR_TYPE__                     uintptr_t;
#define         UINTPTR_MAX                      __UINTPTR_MAX__
#define         UINTPTR_WIDTH                    __UINTPTR_WIDTH__

#define         PTRDIFF_MIN                    (~__PTRDIFF_MAX__)
#define         PTRDIFF_MAX                      __PTRDIFF_MAX__
#define         PTRDIFF_WIDTH                    __PTRDIFF_WIDTH__

#define            SIZE_MAX                         __SIZE_MAX__
#define            SIZE_WIDTH                       __SIZE_WIDTH__

#define            WINT_MIN                       (~__WINT_MAX__)
#define            WINT_MAX                         __WINT_MAX__
#define            WINT_WIDTH                       __WINT_WIDTH__

#ifndef _WCHAR_LIMITS_DEFINED
#define _WCHAR_LIMITS_DEFINED
#define           WCHAR_MIN                      (~__WCHAR_MAX__)
#define           WCHAR_MAX                        __WCHAR_MAX__
#define           WCHAR_WIDTH                      __WCHAR_WIDTH__
#endif

#endif/*_STDINT_H*/
