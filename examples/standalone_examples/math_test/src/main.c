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

#   if INTERACTIVE
#       define x_printf printf
#   else
#       define x_printf(...) dbg_printf(__VA_ARGS__)
#   endif

#else
#   ifndef __cplusplus
typedef int32_t int24_t;
typedef uint32_t uint24_t;
#   else
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
#   endif

static int24_t __builtin_bitreverse24(int24_t x)
{
    return __builtin_bitreverse32(x) >> 8;
}
#endif


#if INTERACTIVE || !defined(_EZ80)
#   define x_printf printf
#else
#   define x_printf(...) dbg_printf(__VA_ARGS__)
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

#define DEFINE_BINOP_FUNC_FUNC(type, name, func, post) \
    static type name##_(type x, type y)                \
    {                                                  \
        return (type)(func(x, y)post);                 \
    }

#define DEFINE_BINOP_INFIX_FUNC(type, name, op) \
    static type name##_(type x, type y)         \
    {                                           \
        return (type)(x op y);                  \
    }

#define DEFINE_UNOP_PREFIX_FUNC_B(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int8_t, b##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_S(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int16_t, s##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_I(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int24_t, i##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_L(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int32_t, l##name, op)
#define DEFINE_UNOP_PREFIX_FUNC_LL(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC(u##int64_t, ll##name, op)

#define DEFINE_BINOP_FUNC_FUNC_B(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC(u##int8_t, b##name, b##func, post)
#define DEFINE_BINOP_FUNC_FUNC_S(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC(u##int16_t, s##name, s##func, post)
#define DEFINE_BINOP_FUNC_FUNC_I(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC(u##int24_t, i##name, func, post)
#define DEFINE_BINOP_FUNC_FUNC_L(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC(u##int32_t, l##name, l##func, post)
#define DEFINE_BINOP_FUNC_FUNC_LL(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC(u##int64_t, ll##name, ll##func, post)

#define DEFINE_BINOP_INFIX_FUNC_B(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int8_t, b##name, op)
#define DEFINE_BINOP_INFIX_FUNC_S(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int16_t, s##name, op)
#define DEFINE_BINOP_INFIX_FUNC_I(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int24_t, i##name, op)
#define DEFINE_BINOP_INFIX_FUNC_L(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int32_t, l##name, op)
#define DEFINE_BINOP_INFIX_FUNC_LL(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC(u##int64_t, ll##name, op)

#define DEFINE_UNOP_PREFIX_FUNC_B_TO_S(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B(u, name, op)          \
    DEFINE_UNOP_PREFIX_FUNC_S(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_S(u, name, op)     \
    DEFINE_UNOP_PREFIX_FUNC_I(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_L(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, name, op)     \
    DEFINE_UNOP_PREFIX_FUNC_L(u, name, op)
#define DEFINE_UNOP_PREFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_UNOP_PREFIX_FUNC_B_TO_L(u, name, op)      \
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
#define DEFINE_BINOP_INFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_BINOP_INFIX_FUNC_B_TO_L(u, name, op)      \
    DEFINE_BINOP_INFIX_FUNC_LL(u, name, op)

#define DEFINE_BINOP_FUNC_FUNC_I_TO_L(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC_I(u, name, func, post)          \
    DEFINE_BINOP_FUNC_FUNC_L(u, name, func, post)
#define DEFINE_BINOP_FUNC_FUNC_I_TO_LL(u, name, func, post) \
    DEFINE_BINOP_FUNC_FUNC_I_TO_L(u, name, func, post)      \
    DEFINE_BINOP_FUNC_FUNC_LL(u, name, func, post)


#define DEFINE_UNOP_TYPE(u)           \
    typedef struct u##UnOp_           \
    {                                 \
        const char *name;             \
        u##int8_t (*b)(u##int8_t);    \
        u##int16_t (*s)(u##int16_t);  \
        u##int24_t (*i)(u##int24_t);  \
        u##int32_t (*l)(u##int32_t);  \
        u##int64_t (*ll)(u##int64_t); \
    } u##UnOp;

#define DEFINE_BINOP_TYPE(u)                      \
    typedef struct u##BinOp_                      \
    {                                             \
        const char *name;                         \
        u##int8_t (*b)(u##int8_t, u##int8_t);     \
        u##int16_t (*s)(u##int16_t, u##int16_t);  \
        u##int24_t (*i)(u##int24_t, u##int24_t);  \
        u##int32_t (*l)(u##int32_t, u##int32_t);  \
        u##int64_t (*ll)(u##int64_t, u##int64_t); \
    } u##BinOp;

DEFINE_UNOP_TYPE()
DEFINE_UNOP_TYPE(u)

DEFINE_BINOP_TYPE()
DEFINE_BINOP_TYPE(u)

#define DEFINE_UNOP_STRUCT_B(u, name) \
    static const u##UnOp unop_##name = {#name, b##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_S(u, name) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_I(u, name) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_, i##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_L(u, name) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_};
#define DEFINE_UNOP_STRUCT_B_TO_LL(u, name) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_, ll##name##_};
#define DEFINE_UNOP_STRUCT_S_L_LL(u, name) \
    static const u##UnOp unop_##name = {#name, 0, s##name##_, 0, l##name##_, ll##name##_};

#define DEFINE_BINOP_STRUCT_B(u, name) \
    static const u##BinOp binop_##name = {#name, b##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_S(u, name) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_I(u, name) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_, i##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_L(u, name) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_};
#define DEFINE_BINOP_STRUCT_B_TO_LL(u, name) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_, ll##name##_};
#define DEFINE_BINOP_STRUCT_I_TO_L(u, name) \
    static const u##BinOp binop_##name = {#name, NULL, NULL, i##name##_, l##name##_};
#define DEFINE_BINOP_STRUCT_I_TO_LL(u, name) \
    static const u##BinOp binop_##name = {#name, NULL, NULL, i##name##_, l##name##_, ll##name##_};


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
#define DEFINE_BINOP_INFIX_B_TO_LL(u, name, op)  \
    DEFINE_BINOP_INFIX_FUNC_B_TO_LL(u, name, op) \
    DEFINE_BINOP_STRUCT_B_TO_LL(u, name)


static void testOp(bool isBinOp, const BinOp *op, int64_t x, int64_t y)
{
    unsigned lhsLength = 8;
    unsigned nameLength = strlen(op->name);
    unsigned prefixLength = lhsLength - nameLength;

    x_printf("%*s=%016llX\n", lhsLength, "x", (long long)x);
    if (!isBinOp)
    {
        x_printf("\n");
    }
    else
    {
        x_printf("%*s=%016llX\n", lhsLength, "y", (long long)y);
    }

#define TEST_OP(prefix, bits)                                                                          \
    x_printf("\n");                                                                                    \
    if (op->prefix)                                                                                    \
    {                                                                                                  \
        unsigned digits = (bits + 3) / 4;                                                              \
        unsigned long long result = (op->prefix)(x, y) & ((1ULL << (bits - 1) << 1) - 1);              \
        x_printf("%*s%s=%*s%0*llX", prefixLength, #prefix, op->name, 16 - digits, "", digits, result); \
    }

    TEST_OP(b, 8)
    TEST_OP(s, 16)
    TEST_OP(i, 24)
    TEST_OP(l, 32)
    TEST_OP(ll, 64)

    finishOutput();
}

static void testUnOp(const UnOp *op, int64_t x)
{
    testOp(false, (const BinOp*)op, x, 0);
}

static void testBinOp(const BinOp *op, int64_t x, int64_t y)
{
    testOp(true, op, x, y);
}


DEFINE_UNOP_PREFIX_B_TO_LL( , not, ~)
DEFINE_UNOP_PREFIX_B_TO_LL( , neg, -)

DEFINE_UNOP_PREFIX_FUNC_B_TO_I( , abs, abs)
DEFINE_UNOP_PREFIX_FUNC_L( , abs, labs)
DEFINE_UNOP_PREFIX_FUNC_LL( , abs, llabs)
DEFINE_UNOP_STRUCT_B_TO_LL( , abs)

DEFINE_UNOP_PREFIX_FUNC_B( , bitrev, __builtin_bitreverse8)
DEFINE_UNOP_PREFIX_FUNC_S( , bitrev, __builtin_bitreverse16)
DEFINE_UNOP_PREFIX_FUNC_I( , bitrev, __builtin_bitreverse24)
DEFINE_UNOP_PREFIX_FUNC_L( , bitrev, __builtin_bitreverse32)
DEFINE_UNOP_PREFIX_FUNC_LL( , bitrev, __builtin_bitreverse64)
DEFINE_UNOP_STRUCT_B_TO_LL( , bitrev)

// Needs to be unsigned to avoid extra bits from sign extension
DEFINE_UNOP_PREFIX_FUNC_S(u, bswap, __builtin_bswap16)
DEFINE_UNOP_PREFIX_FUNC_L(u, bswap, __builtin_bswap32)
DEFINE_UNOP_PREFIX_FUNC_LL(u, bswap, __builtin_bswap64)
DEFINE_UNOP_STRUCT_S_L_LL(u, bswap)

// Needs to be unsigned to avoid extra bits from sign extension
DEFINE_UNOP_PREFIX_FUNC_B_TO_I(u, popcnt, __builtin_popcount)
DEFINE_UNOP_PREFIX_FUNC_L(u, popcnt, __builtin_popcountl)
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


DEFINE_BINOP_FUNC_FUNC_I_TO_LL( , div_q, div, .quot)
DEFINE_BINOP_STRUCT_I_TO_LL( , div_q)

DEFINE_BINOP_FUNC_FUNC_I_TO_LL( , div_r, div, .rem)
DEFINE_BINOP_STRUCT_I_TO_LL( , div_r)


static const UnOp *unops[] = {
    &unop_not,
    &unop_neg,
    &unop_abs,
    &unop_bitrev,
    (const UnOp *)&unop_bswap,
    (const UnOp *)&unop_popcnt,
};

static const BinOp *binops[] = {
    &binop_and,
    &binop_or,
    &binop_xor,
    &binop_add,
    &binop_sub,
    &binop_shl,
    (const BinOp *)&binop_shru,
    &binop_shrs,
    (const BinOp *)&binop_mulu,
    (const BinOp *)&binop_divu,
    (const BinOp *)&binop_remu,
    &binop_divs,
    &binop_rems,
    &binop_div_q,
    &binop_div_r,
};


int main(int argc, char *argv[])
{
    int64_t x = argc > 1 ? atoll(argv[1]) : (int64_t)0xDFA5FBC197EDB389LL;
    int64_t y = argc > 2 ? atoll(argv[2]) : (int64_t)0x08010A030C050E07LL;

    separateOutput();

    for (size_t i = 0; i < sizeof(unops) / sizeof(*unops); i++)
    {
        testUnOp(unops[i], x);
    }

    for (size_t i = 0; i < sizeof(binops) / sizeof(*binops); i++)
    {
        testBinOp(binops[i], x, y);
    }

    return 0;
}
