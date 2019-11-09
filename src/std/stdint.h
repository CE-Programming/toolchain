#ifndef _STDINT_H
#define _STDINT_H

typedef         __INT8_TYPE__          int8_t;
#define           INT8_MIN          ~__INT8_MAX__
#define           INT8_MAX           __INT8_MAX__
#define           INT8_WIDTH         __INT8_WIDTH__
#define           INT8_C(C)  C  ##   __INT8_C_SUFFIX__
typedef        __UINT8_TYPE__         uint8_t;
#define          UINT8_MAX          __UINT8_MAX__
#define          UINT8_WIDTH        __UINT8_WIDTH__
#define          UINT8_C(C)  C  ##  __UINT8_C_SUFFIX__
typedef    __INT_FAST8_TYPE__     int_fast8_t;
#define      INT_FAST8_MIN     ~__INT_FAST8_MAX__
#define      INT_FAST8_MAX      __INT_FAST8_MAX__
#define      INT_FAST8_WIDTH    __INT_FAST8_WIDTH__
typedef   __UINT_FAST8_TYPE__    uint_fast8_t;
#define     UINT_FAST8_MAX     __UINT_FAST8_MAX__
#define     UINT_FAST8_WIDTH   __UINT_FAST8_WIDTH__
typedef   __INT_LEAST8_TYPE__    int_least8_t;
#define     INT_LEAST8_MIN    ~__INT_LEAST8_MAX__
#define     INT_LEAST8_MAX     __INT_LEAST8_MAX__
#define     INT_LEAST8_WIDTH   __INT_LEAST8_WIDTH__
typedef  __UINT_LEAST8_TYPE__   uint_least8_t;
#define    UINT_LEAST8_MAX    __UINT_LEAST8_MAX__
#define    UINT_LEAST8_WIDTH  __UINT_LEAST8_WIDTH__

typedef        __INT16_TYPE__         int16_t;
#define          INT16_MIN         ~__INT16_MAX__
#define          INT16_MAX          __INT16_MAX__
#define          INT16_WIDTH        __INT16_WIDTH__
#define          INT16_C(C)  C  ##  __INT16_C_SUFFIX__
typedef       __UINT16_TYPE__        uint16_t;
#define         UINT16_MAX         __UINT16_MAX__
#define         UINT16_WIDTH       __UINT16_WIDTH__
#define         UINT16_C(C)  C  ## __UINT16_C_SUFFIX__
typedef   __INT_FAST16_TYPE__    int_fast16_t;
#define     INT_FAST16_MIN    ~__INT_FAST16_MAX__
#define     INT_FAST16_MAX     __INT_FAST16_MAX__
#define     INT_FAST16_WIDTH   __INT_FAST16_WIDTH__
typedef  __UINT_FAST16_TYPE__   uint_fast16_t;
#define    UINT_FAST16_MAX    __UINT_FAST16_MAX__
#define    UINT_FAST16_WIDTH  __UINT_FAST16_WIDTH__
typedef  __INT_LEAST16_TYPE__   int_least16_t;
#define    INT_LEAST16_MIN   ~__INT_LEAST16_MAX__
#define    INT_LEAST16_MAX    __INT_LEAST16_MAX__
#define    INT_LEAST16_WIDTH  __INT_LEAST16_WIDTH__
typedef __UINT_LEAST16_TYPE__  uint_least16_t;
#define   UINT_LEAST16_MAX   __UINT_LEAST16_MAX__
#define   UINT_LEAST16_WIDTH __UINT_LEAST16_WIDTH__

#ifdef         __INT24_TYPE__
typedef        __INT24_TYPE__        int24_t;
#define          INT24_MIN        ~__INT24_MAX__
#define          INT24_MAX         __INT24_MAX__
#define          INT24_WIDTH       __INT24_WIDTH__
#define          INT24_C(C) C  ##  __INT24_C_SUFFIX__
typedef       __UINT24_TYPE__       uint24_t;
#define         UINT24_MAX        __UINT24_MAX__
#define         UINT24_WIDTH      __UINT24_WIDTH__
#define         UINT24_C(C) C  ## __UINT24_C_SUFFIX__
#endif      /* __INT24_TYPE__ */

typedef        __INT32_TYPE__         int32_t;
#define          INT32_MIN         ~__INT32_MAX__
#define          INT32_MAX          __INT32_MAX__
#define          INT32_WIDTH        __INT32_WIDTH__
#define          INT32_C(C)  C  ##  __INT32_C_SUFFIX__
typedef       __UINT32_TYPE__        uint32_t;
#define         UINT32_MAX         __UINT32_MAX__
#define         UINT32_WIDTH       __UINT32_WIDTH__
#define         UINT32_C(C)  C  ## __UINT32_C_SUFFIX__
typedef   __INT_FAST32_TYPE__    int_fast32_t;
#define     INT_FAST32_MIN    ~__INT_FAST32_MAX__
#define     INT_FAST32_MAX     __INT_FAST32_MAX__
#define     INT_FAST32_WIDTH   __INT_FAST32_WIDTH__
typedef  __UINT_FAST32_TYPE__   uint_fast32_t;
#define    UINT_FAST32_MAX    __UINT_FAST32_MAX__
#define    UINT_FAST32_WIDTH  __UINT_FAST32_WIDTH__
typedef  __INT_LEAST32_TYPE__   int_least32_t;
#define    INT_LEAST32_MIN   ~__INT_LEAST32_MAX__
#define    INT_LEAST32_MAX    __INT_LEAST32_MAX__
#define    INT_LEAST32_WIDTH  __INT_LEAST32_WIDTH__
typedef __UINT_LEAST32_TYPE__  uint_least32_t;
#define   UINT_LEAST32_MAX   __UINT_LEAST32_MAX__
#define   UINT_LEAST32_WIDTH __UINT_LEAST32_WIDTH__

#ifdef         __INT48_TYPE__
typedef        __INT48_TYPE__        int48_t;
#define          INT48_MIN        ~__INT48_MAX__
#define          INT48_MAX         __INT48_MAX__
#define          INT48_WIDTH       __INT48_WIDTH__
#define          INT48_C(C) C  ##  __INT48_C_SUFFIX__
typedef       __UINT48_TYPE__       uint48_t;
#define         UINT48_MAX        __UINT48_MAX__
#define         UINT48_WIDTH      __UINT48_WIDTH__
#define         UINT48_C(C) C  ## __UINT48_C_SUFFIX__
#endif      /* __INT48_TYPE__ */

typedef        __INT64_TYPE__         int64_t;
#define          INT64_MIN         ~__INT64_MAX__
#define          INT64_MAX          __INT64_MAX__
#define          INT64_WIDTH        __INT64_WIDTH__
#define          INT64_C(C)  C  ##  __INT64_C_SUFFIX__
typedef       __UINT64_TYPE__        uint64_t;
#define         UINT64_MAX         __UINT64_MAX__
#define         UINT64_WIDTH       __UINT64_WIDTH__
#define         UINT64_C(C)  C  ## __UINT64_C_SUFFIX__
typedef   __INT_FAST64_TYPE__    int_fast64_t;
#define     INT_FAST64_MIN    ~__INT_FAST64_MAX__
#define     INT_FAST64_MAX     __INT_FAST64_MAX__
#define     INT_FAST64_WIDTH   __INT_FAST64_WIDTH__
typedef  __UINT_FAST64_TYPE__   uint_fast64_t;
#define    UINT_FAST64_MAX    __UINT_FAST64_MAX__
#define    UINT_FAST64_WIDTH  __UINT_FAST64_WIDTH__
typedef  __INT_LEAST64_TYPE__   int_least64_t;
#define    INT_LEAST64_MIN   ~__INT_LEAST64_MAX__
#define    INT_LEAST64_MAX    __INT_LEAST64_MAX__
#define    INT_LEAST64_WIDTH  __INT_LEAST64_WIDTH__
typedef __UINT_LEAST64_TYPE__  uint_least64_t;
#define   UINT_LEAST64_MAX   __UINT_LEAST64_MAX__
#define   UINT_LEAST64_WIDTH __UINT_LEAST64_WIDTH__

typedef       __INTMAX_TYPE__       intmax_t;
#define         INTMAX_MIN       ~__INTMAX_MAX__
#define         INTMAX_MAX        __INTMAX_MAX__
#define         INTMAX_WIDTH      __INTMAX_WIDTH__
#define         INTMAX_C(C) C ##  __INTMAX_C_SUFFIX__
typedef      __UINTMAX_TYPE__      uintmax_t;
#define        UINTMAX_MAX       __UINTMAX_MAX__
#define        UINTMAX_WIDTH     __UINTMAX_WIDTH__
#define        UINTMAX_C(C) C ## __UINTMAX_C_SUFFIX__

typedef       __INTPTR_TYPE__       intptr_t;
#define         INTPTR_MIN       ~__INTPTR_MAX__
#define         INTPTR_MAX        __INTPTR_MAX__
#define         INTPTR_WIDTH      __INTPTR_WIDTH__
typedef      __UINTPTR_TYPE__      uintptr_t;
#define        UINTPTR_MAX       __UINTPTR_MAX__
#define        UINTPTR_WIDTH     __UINTPTR_WIDTH__

#define        PTRDIFF_MIN      ~__PTRDIFF_MAX__
#define        PTRDIFF_MAX       __PTRDIFF_MAX__
#define        PTRDIFF_WIDTH     __PTRDIFF_WIDTH__

#define           SIZE_MAX          __SIZE_MAX__
#define           SIZE_WIDTH        __SIZE_WIDTH__

#define          WCHAR_WIDTH       __WCHAN_WIDTH__

#define           WINT_MIN         ~__WINT_MAX__
#define           WINT_MAX          __WINT_MAX__
#define           WINT_WIDTH        __WINT_WIDTH__

#endif /* _STDINT_H */
