#define INTERACTIVE 1


#undef NDEBUG

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef _EZ80

#   include <debug.h>
#   include <ti/screen.h>
#   include <ti/getcsc.h>
#   include <ez80_builtin.h>

#   if INTERACTIVE
#       define x_printf printf
#   else
#       define x_printf(...) dbg_printf(__VA_ARGS__)
#   endif

#else

#   define x_printf printf

#   if __STDC_VERSION__ >= 202311L

typedef _BitInt(24) int24_t;
typedef unsigned _BitInt(24) uint24_t;
typedef _BitInt(48) int48_t;
typedef unsigned _BitInt(48) uint48_t;

#   elif defined(__clang__)

typedef _ExtInt(24) int24_t;
typedef unsigned _ExtInt(24) uint24_t;
typedef _ExtInt(48) int48_t;
typedef unsigned _ExtInt(48) uint48_t;

#   elif defined(__cplusplus)

template <unsigned bits, typename U>
struct IntN final
{
private:
    static constexpr int extraBits = sizeof(U) * 8 - bits;
    static_assert(extraBits >= 0, "underlying type is not big enough");

public:
    constexpr IntN(U value) : value(value * (1ULL << extraBits)) {}
    constexpr operator U() const { return value >> extraBits; }

private:
    U value;
};
using uint24_t = IntN<24, uint_fast32_t>;
using int24_t = IntN<24, int_fast32_t>;
using uint48_t = IntN<48, uint_fast64_t>;
using int48_t = IntN<48, int_fast64_t>;

#   else

#error "Use a more modern language standard/compiler"

#   endif

static int24_t __builtin_bitreverse24(int24_t x)
{
    return __builtin_bitreverse32(x) >> 8;
    // return __builtin_bitreverse16(x >> 8) | __builtin_bitreverse8(x) << 16;
}

#endif

#ifndef _EZ80
static int48_t __builtin_bitreverse48(int48_t x)
{
    // return __builtin_bitreverse64(x) >> 16;
    return __builtin_bitreverse32(x >> 16) | (int48_t)__builtin_bitreverse16(x) << 32;
}
static uint48_t __builtin_bswap48(uint48_t x)
{
    return __builtin_bswap64(x) >> 16;
    // return __builtin_bswap32(x >> 16) | (uint48_t)__builtin_bswap16(x) << 32;
}
static int __builtin_popcounti48(uint48_t x)
{
    return __builtin_popcountll(x & ((1LL << 48) - 1));
}
#else
static int48_t __builtin_bitreverse48(int48_t x)
{
    return __ez80_bitreverse48(x);
}
static uint48_t __builtin_bswap48(uint48_t x)
{
    return __ez80_bswap48(x);
}
static int __builtin_popcounti48(uint48_t x)
{
    return __ez80_popcounti48(x);
}
#endif
static int24_t iabs(int24_t x)
{
    return x < 0 ? (int24_t)-x : x;
}
#ifndef _EZ80
static int48_t i48abs(int48_t x)
{
    return x < 0 ? (int48_t)-x : x;
}
#endif


#if INTERACTIVE && defined(_EZ80)
#   define x_printffull x_printf
#else
#   define x_printffull(format, ...) x_printf(format "\n", __VA_ARGS__)
#endif

static void separateOutput()
{
#if INTERACTIVE && defined(_EZ80)
    os_ClrHomeFull();
#else
    x_printf("\n--------------------------\n");
#endif
}

static void waitForKey()
{
#if INTERACTIVE && defined(_EZ80)
    while (!os_GetCSC())
        ;
#endif
}

static void finishOutput()
{
    waitForKey();
    separateOutput();
}


#define DEFINE_UNOP_PREFIX_FUNC(type, name, op) \
    static type name##_(type x)                 \
    {                                           \
        return (type)(op(x));                   \
    }

#define DEFINE_BINOP_INFIX_FUNC(type, name, op) \
    static type name##_(type x, type y)         \
    {                                           \
        return (type)(x op y);                  \
    }

#define DEFINE_BINOP_DIV_LIKE_FUNC(type, name, func, post) \
    static type name##_(type x, type y)                    \
    {                                                      \
        return (type)(func(x + 0, y + 0)post);                     \
    }

#define DEFINE_UNOP_PREFIX_FUNC_B(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int8_t, b##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_S(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int16_t, s##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_I(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int24_t, i##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_L(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int32_t, l##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_I48(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int48_t, i48##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_LL(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int64_t, ll##name, op)

#define DEFINE_BINOP_INFIX_FUNC_B(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int8_t, b##name, op)
#define DEFINE_BINOP_INFIX_FUNC_S(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int16_t, s##name, op)
#define DEFINE_BINOP_INFIX_FUNC_I(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int24_t, i##name, op)
#define DEFINE_BINOP_INFIX_FUNC_L(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int32_t, l##name, op)
#define DEFINE_BINOP_INFIX_FUNC_I48(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int48_t, i48##name, op)
#define DEFINE_BINOP_INFIX_FUNC_LL(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int64_t, ll##name, op)

#define DEFINE_BINOP_DIV_LIKE_FUNC_B(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC(u##int8_t, b##name, b##func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_S(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC(u##int16_t, s##name, s##func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_I(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC(u##int24_t, i##name, func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_L(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC(u##int32_t, l##name, l##func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_I48(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC(u##int48_t, i48##name, i48##func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_LL(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC(u##int64_t, ll##name, ll##func, post)

#define DEFINE_UNOP_PREFIX_FUNC_B_TO_S(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B(u, name, op)          \
    DEFINE_UNOP_PREFIX_FUNC_S(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_S(u, name, op)     \
    DEFINE_UNOP_PREFIX_FUNC_I(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_L(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, name, op)     \
    DEFINE_UNOP_PREFIX_FUNC_L(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_I48(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_L(u, name, op)       \
    DEFINE_UNOP_PREFIX_FUNC_I48(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_I48(u, name, op)    \
    DEFINE_UNOP_PREFIX_FUNC_LL(u, name, op)

#define DEFINE_BINOP_INFIX_FUNC_B_TO_S(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC_B(u, name, op)          \
    DEFINE_BINOP_INFIX_FUNC_S(u, name, op)
#define DEFINE_BINOP_INFIX_FUNC_B_TO_I(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC_B_TO_S(u, name, op)     \
    DEFINE_BINOP_INFIX_FUNC_I(u, name, op)
#define DEFINE_BINOP_INFIX_FUNC_B_TO_L(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC_B_TO_I(u, name, op)     \
    DEFINE_BINOP_INFIX_FUNC_L(u, name, op)
#define DEFINE_BINOP_INFIX_FUNC_B_TO_I48(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC_B_TO_L(u, name, op)       \
    DEFINE_BINOP_INFIX_FUNC_I48(u, name, op)
#define DEFINE_BINOP_INFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC_B_TO_I48(u, name, op)    \
    DEFINE_BINOP_INFIX_FUNC_LL(u, name, op)

#define DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_L(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC_I(u, name, func, post)          \
    DEFINE_BINOP_DIV_LIKE_FUNC_L(u, name, func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_I48(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_L(u, name, func, post)       \
    // DEFINE_BINOP_DIV_LIKE_FUNC_I48(u, name, func, post)
#define DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_LL(u, name, func, post) \
    DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_I48(u, name, func, post)    \
    DEFINE_BINOP_DIV_LIKE_FUNC_LL(u, name, func, post)


typedef struct Op_
{
    bool isBinary;
    bool isUnsigned;
    const char *name;
    void (*b)();
    void (*s)();
    void (*i)();
    void (*l)();
    void (*i48)();
    void (*ll)();
} Op;

#define DEFINE_UNOP_TYPE(u)            \
    typedef struct u##UnOp_            \
    {                                  \
        bool isBinary;                 \
        bool isUnsigned;               \
        const char *name;              \
        u##int8_t (*b)(u##int8_t);     \
        u##int16_t (*s)(u##int16_t);   \
        u##int24_t (*i)(u##int24_t);   \
        u##int32_t (*l)(u##int32_t);   \
        u##int48_t (*i48)(u##int48_t); \
        u##int64_t (*ll)(u##int64_t);  \
    } u##UnOp;

#define DEFINE_BINOP_TYPE(u)                       \
    typedef struct u##BinOp_                       \
    {                                              \
        bool isBinary;                             \
        bool isUnsigned;                           \
        const char *name;                          \
        u##int8_t (*b)(u##int8_t, u##int8_t);      \
        u##int16_t (*s)(u##int16_t, u##int16_t);   \
        u##int24_t (*i)(u##int24_t, u##int24_t);   \
        u##int32_t (*l)(u##int32_t, u##int32_t);   \
        u##int48_t (*i48)(u##int48_t, u##int48_t); \
        u##int64_t (*ll)(u##int64_t, u##int64_t);  \
    } u##BinOp;

DEFINE_UNOP_TYPE()
DEFINE_UNOP_TYPE(u)

DEFINE_BINOP_TYPE()
DEFINE_BINOP_TYPE(u)

static const bool _0IsUnsigned = 0;
static const bool _0IsUnsignedu = 1;

#define DEFINE_UNOP_STRUCT_B(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_S(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_, s##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_I(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_L(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_I48(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_, i48##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_LL(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_, i48##name##_, ll##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_LL_EXCEPT_I48(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_, NULL, ll##name##_};
#define DEFINE_UNOP_STRUCT_BSWAP(u, name) \
    static const u##UnOp u##unop_##name = {0, _0IsUnsigned##u, #name, NULL, s##name##_, NULL, l##name##_, i48##name##_, ll##name##_};

#define DEFINE_BINOP_STRUCT_B(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, b##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_S(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, b##name##_, s##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_I(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_L(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_I48(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_, i48##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_LL(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, b##name##_, s##name##_, i##name##_, l##name##_, i48##name##_, ll##name##_};
#define DEFINE_BINOP_STRUCT_I_TO_L(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, NULL, NULL, i##name##_, l##name##_};
// #define DEFINE_BINOP_STRUCT_I_TO_I48(u, name) \
//     static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, NULL, NULL, i##name##_, l##name##_, i48##name##_};
#define DEFINE_BINOP_STRUCT_I_TO_LL(u, name) \
    static const u##BinOp u##binop_##name = {1, _0IsUnsigned##u, #name, NULL, NULL, i##name##_, l##name##_, NULL, ll##name##_};


#define DEFINE_UNOP_PREFIX_B(u, name, op)  \
    DEFINE_UNOP_PREFIX_FUNC_B(u, name, op) \
    DEFINE_UNOP_STRUCT_B(u, name)
#define DEFINE_UNOP_PREFIX_B_TO_S(u, name, op)  \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_S(u, name, op) \
    DEFINE_UNOP_STRUCT_B_TO_S(u, name)
#define DEFINE_UNOP_PREFIX_B_TO_I(u, name, op)  \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, name, op) \
    DEFINE_UNOP_STRUCT_B_TO_I(u, name)
#define DEFINE_UNOP_PREFIX_B_TO_L(u, name, op)  \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_L(u, name, op) \
    DEFINE_UNOP_STRUCT_B_TO_L(u, name)
#define DEFINE_UNOP_PREFIX_B_TO_I48(u, name, op)  \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_I48(u, name, op) \
    DEFINE_UNOP_STRUCT_B_TO_I48(u, name)
#define DEFINE_UNOP_PREFIX_B_TO_LL(u, name, op)  \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_UNOP_STRUCT_B_TO_LL(u, name)

#define DEFINE_BINOP_INFIX_B(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B(u, name, op) \
    DEFINE_BINOP_STRUCT_B(u, name)
#define DEFINE_BINOP_INFIX_B_TO_S(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B_TO_S(u, name, op) \
    DEFINE_BINOP_STRUCT_B_TO_S(u, name)
#define DEFINE_BINOP_INFIX_B_TO_I(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B_TO_I(u, name, op) \
    DEFINE_BINOP_STRUCT_B_TO_I(u, name)
#define DEFINE_BINOP_INFIX_B_TO_L(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B_TO_L(u, name, op) \
    DEFINE_BINOP_STRUCT_B_TO_L(u, name)
#define DEFINE_BINOP_INFIX_B_TO_I48(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B_TO_I48(u, name, op) \
    DEFINE_BINOP_STRUCT_B_TO_I48(u, name)
#define DEFINE_BINOP_INFIX_B_TO_LL(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_BINOP_STRUCT_B_TO_LL(u, name)


static void testOp(const Op *op, int64_t x, int64_t y)
{
    unsigned lhsLength = 9;
    unsigned nameLength = strlen(op->name);
    unsigned prefixLength = lhsLength - nameLength;

    x_printffull("%*s=%016llX", lhsLength, "x", (long long)x);
    if (!op->isBinary)
    {
        x_printf("\n");
    }
    else
    {
        x_printffull("%*s=%016llX", lhsLength, "y", (long long)y);
    }
    x_printf("\n");

#define TEST_OP(prefix, bits)                               \
    if (op->prefix)                                         \
    {                                                       \
        unsigned digits = (bits + 3) / 4;                   \
        unsigned long long result =                         \
            !op->isBinary                                   \
                ? !op->isUnsigned                           \
                    ? ((const   UnOp *)(op))->prefix(x)     \
                    : ((const  uUnOp *)(op))->prefix(x)     \
                : !op->isUnsigned                           \
                    ? ((const  BinOp *)(op))->prefix(x, y)  \
                    : ((const uBinOp *)(op))->prefix(x, y); \
        result &= ((1ULL << (bits - 1) << 1) - 1);          \
        x_printffull("%*s%s=%*s%0*llX",                     \
                     prefixLength,                          \
                     #prefix,                               \
                     op->name,                              \
                     16 - digits,                           \
                     "",                                    \
                     digits,                                \
                     result);                               \
    }                                                       \
    else                                                    \
    {                                                       \
        x_printf("\n");                                     \
    }

    TEST_OP(b, 8)
    TEST_OP(s, 16)
    TEST_OP(i, 24)
    TEST_OP(l, 32)
    TEST_OP(i48, 48)
    TEST_OP(ll, 64)

    finishOutput();
}


DEFINE_UNOP_PREFIX_B_TO_LL( , not, ~)
DEFINE_UNOP_PREFIX_B_TO_LL( , neg, -)

DEFINE_UNOP_PREFIX_FUNC_B_TO_S( , abs, abs)
DEFINE_UNOP_PREFIX_FUNC_I( , abs, iabs)
DEFINE_UNOP_PREFIX_FUNC_L( , abs, labs)
DEFINE_UNOP_PREFIX_FUNC_I48( , abs, i48abs)
DEFINE_UNOP_PREFIX_FUNC_LL( , abs, llabs)
DEFINE_UNOP_STRUCT_B_TO_LL(, abs)

DEFINE_UNOP_PREFIX_FUNC_B( , bitrev, __builtin_bitreverse8)
DEFINE_UNOP_PREFIX_FUNC_S( , bitrev, __builtin_bitreverse16)
DEFINE_UNOP_PREFIX_FUNC_I( , bitrev, __builtin_bitreverse24)
DEFINE_UNOP_PREFIX_FUNC_L( , bitrev, __builtin_bitreverse32)
DEFINE_UNOP_PREFIX_FUNC_I48( , bitrev, __builtin_bitreverse48)
DEFINE_UNOP_PREFIX_FUNC_LL( , bitrev, __builtin_bitreverse64)
DEFINE_UNOP_STRUCT_B_TO_LL(, bitrev)

DEFINE_UNOP_PREFIX_FUNC_S(u, bswap, __builtin_bswap16)
DEFINE_UNOP_PREFIX_FUNC_L(u, bswap, __builtin_bswap32)
DEFINE_UNOP_PREFIX_FUNC_I48(u, bswap, __builtin_bswap48)
DEFINE_UNOP_PREFIX_FUNC_LL(u, bswap, __builtin_bswap64)
DEFINE_UNOP_STRUCT_BSWAP(u, bswap)

DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, popcnt, __builtin_popcount)
DEFINE_UNOP_PREFIX_FUNC_L(u, popcnt, __builtin_popcountl)
DEFINE_UNOP_PREFIX_FUNC_I48(u, popcnt, __builtin_popcounti48)
DEFINE_UNOP_PREFIX_FUNC_LL(u, popcnt, __builtin_popcountll)
DEFINE_UNOP_STRUCT_B_TO_LL(u, popcnt)

DEFINE_BINOP_INFIX_B_TO_LL( , and, &)
DEFINE_BINOP_INFIX_B_TO_LL( , or, |)
DEFINE_BINOP_INFIX_B_TO_LL( , xor, ^)
DEFINE_BINOP_INFIX_B_TO_LL( , add, +)
DEFINE_BINOP_INFIX_B_TO_LL( , sub, -)
DEFINE_BINOP_INFIX_B_TO_LL( , shl, <<)
DEFINE_BINOP_INFIX_B_TO_LL(u, shru, >>)
DEFINE_BINOP_INFIX_B_TO_LL( , shrs, >>)
DEFINE_BINOP_INFIX_B_TO_LL(u, mulu, *)
DEFINE_BINOP_INFIX_B_TO_LL(u, divu, /)
DEFINE_BINOP_INFIX_B_TO_LL(u, remu, %)
DEFINE_BINOP_INFIX_B_TO_LL( , divs, /)
DEFINE_BINOP_INFIX_B_TO_LL( , rems, %)

DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_LL( , div_q, div, .quot)
DEFINE_BINOP_STRUCT_I_TO_LL( , div_q)

DEFINE_BINOP_DIV_LIKE_FUNC_I_TO_LL( , div_r, div, .rem)
DEFINE_BINOP_STRUCT_I_TO_LL( , div_r)


static const Op *ops[] = {
    (const Op *)&unop_not,
    (const Op *)&unop_neg,
    (const Op *)&unop_abs,
    (const Op *)&unop_bitrev,
    (const Op *)&uunop_bswap,
    (const Op *)&uunop_popcnt,
    (const Op *)&binop_and,
    (const Op *)&binop_or,
    (const Op *)&binop_xor,
    (const Op *)&binop_add,
    (const Op *)&binop_sub,
    (const Op *)&binop_shl,
    (const Op *)&ubinop_shru,
    (const Op *)&binop_shrs,
    (const Op *)&ubinop_mulu,
    (const Op *)&ubinop_divu,
    (const Op *)&ubinop_remu,
    (const Op *)&binop_divs,
    (const Op *)&binop_rems,
    (const Op *)&binop_div_q,
    (const Op *)&binop_div_r,
};


int main(int argc, char *argv[])
{
    int64_t x = argc > 1 ? atoll(argv[1]) : (int64_t)0xDFA5FBC197EDB389LL;
    int64_t y = argc > 2 ? atoll(argv[2]) : (int64_t)0x08010A030C050E07LL;

    separateOutput();

    for (size_t i = 0; i < sizeof(ops) / sizeof(*ops); i++)
    {
        testOp(ops[i], x, y);
    }

    return 0;
}
