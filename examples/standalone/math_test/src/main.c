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
#   include <tice.h>

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


static uint64_t atoull_(const char *str)
{
    uint64_t result = 0;
    while (isdigit(*str))
    {
        result = result * 10 + (unsigned)(*str++ - '0');
    }

    return result;
}

static int64_t atoll_(const char *str)
{
    bool negative = false;
    if (*str == '-')
    {
        negative = true;
        str++;
    }

    uint64_t x = atoull_(str);
    int64_t result = (int64_t)(negative ? -x : x);

    return result;
}


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


#define DEFINE_UNOP_FUNC(op, name, prefix, type) \
    static type prefix##name##_(type x)          \
    {                                            \
        return (type)(op(x));                    \
    }

#define DEFINE_BINOP_FUNC(op, name, prefix, type) \
    static type prefix##name##_(type x, type y)   \
    {                                             \
        return (type)(x op y);                    \
    }

#define DEFINE_UNOP_FUNC_B(op, name, u) DEFINE_UNOP_FUNC(op, name, b, u##int8_t)
#define DEFINE_UNOP_FUNC_S(op, name, u) DEFINE_UNOP_FUNC(op, name, s, u##int16_t)
#define DEFINE_UNOP_FUNC_I(op, name, u) DEFINE_UNOP_FUNC(op, name, i, u##int24_t)
#define DEFINE_UNOP_FUNC_L(op, name, u) DEFINE_UNOP_FUNC(op, name, l, u##int32_t)
#define DEFINE_UNOP_FUNC_LL(op, name, u) DEFINE_UNOP_FUNC(op, name, ll, u##int64_t)

#define DEFINE_BINOP_FUNC_B(op, name, u) DEFINE_BINOP_FUNC(op, name, b, u##int8_t)
#define DEFINE_BINOP_FUNC_S(op, name, u) DEFINE_BINOP_FUNC(op, name, s, u##int16_t)
#define DEFINE_BINOP_FUNC_I(op, name, u) DEFINE_BINOP_FUNC(op, name, i, u##int24_t)
#define DEFINE_BINOP_FUNC_L(op, name, u) DEFINE_BINOP_FUNC(op, name, l, u##int32_t)
#define DEFINE_BINOP_FUNC_LL(op, name, u) DEFINE_BINOP_FUNC(op, name, ll, u##int64_t)


#define DEFINE_UNOP_FUNCS_UP_TO_B(op, name, u) \
    DEFINE_UNOP_FUNC_B(op, name, u)
#define DEFINE_UNOP_FUNCS_UP_TO_S(op, name, u) \
    DEFINE_UNOP_FUNCS_UP_TO_B(op, name, u)     \
    DEFINE_UNOP_FUNC_S(op, name, u)
#define DEFINE_UNOP_FUNCS_UP_TO_I(op, name, u) \
    DEFINE_UNOP_FUNCS_UP_TO_S(op, name, u)     \
    DEFINE_UNOP_FUNC_I(op, name, u)
#define DEFINE_UNOP_FUNCS_UP_TO_L(op, name, u) \
    DEFINE_UNOP_FUNCS_UP_TO_I(op, name, u)     \
    DEFINE_UNOP_FUNC_L(op, name, u)
#define DEFINE_UNOP_FUNCS_UP_TO_LL(op, name, u) \
    DEFINE_UNOP_FUNCS_UP_TO_L(op, name, u)      \
    DEFINE_UNOP_FUNC_LL(op, name, u)

#define DEFINE_BINOP_FUNCS_UP_TO_B(op, name, u) \
    DEFINE_BINOP_FUNC_B(op, name, u)
#define DEFINE_BINOP_FUNCS_UP_TO_S(op, name, u) \
    DEFINE_BINOP_FUNCS_UP_TO_B(op, name, u)     \
    DEFINE_BINOP_FUNC_S(op, name, u)
#define DEFINE_BINOP_FUNCS_UP_TO_I(op, name, u) \
    DEFINE_BINOP_FUNCS_UP_TO_S(op, name, u)     \
    DEFINE_BINOP_FUNC_I(op, name, u)
#define DEFINE_BINOP_FUNCS_UP_TO_L(op, name, u) \
    DEFINE_BINOP_FUNCS_UP_TO_I(op, name, u)     \
    DEFINE_BINOP_FUNC_L(op, name, u)
#define DEFINE_BINOP_FUNCS_UP_TO_LL(op, name, u) \
    DEFINE_BINOP_FUNCS_UP_TO_L(op, name, u)      \
    DEFINE_BINOP_FUNC_LL(op, name, u)


#define DEFINE_UNOP_STRUCT_UP_TO_B(name, u) \
    static const u##UnOp unop_##name = {#name, b##name##_};
#define DEFINE_UNOP_STRUCT_UP_TO_S(name, u) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_};
#define DEFINE_UNOP_STRUCT_UP_TO_I(name, u) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_, i##name##_};
#define DEFINE_UNOP_STRUCT_UP_TO_L(name, u) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_};
#define DEFINE_UNOP_STRUCT_UP_TO_LL(name, u) \
    static const u##UnOp unop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_, ll##name##_};

#define DEFINE_BINOP_STRUCT_UP_TO_B(name, u) \
    static const u##BinOp binop_##name = {#name, b##name##_};
#define DEFINE_BINOP_STRUCT_UP_TO_S(name, u) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_};
#define DEFINE_BINOP_STRUCT_UP_TO_I(name, u) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_, i##name##_};
#define DEFINE_BINOP_STRUCT_UP_TO_L(name, u) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_};
#define DEFINE_BINOP_STRUCT_UP_TO_LL(name, u) \
    static const u##BinOp binop_##name = {#name, b##name##_, s##name##_, i##name##_, l##name##_, ll##name##_};


#define DEFINE_UNOP_UP_TO_B(op, name, u)   \
    DEFINE_UNOP_FUNCS_UP_TO_B(op, name, u) \
    DEFINE_UNOP_STRUCT_UP_TO_B(name, u)
#define DEFINE_UNOP_UP_TO_S(op, name, u)   \
    DEFINE_UNOP_FUNCS_UP_TO_S(op, name, u) \
    DEFINE_UNOP_STRUCT_UP_TO_S(name, u)
#define DEFINE_UNOP_UP_TO_I(op, name, u)   \
    DEFINE_UNOP_FUNCS_UP_TO_I(op, name, u) \
    DEFINE_UNOP_STRUCT_UP_TO_I(name, u)
#define DEFINE_UNOP_UP_TO_L(op, name, u)   \
    DEFINE_UNOP_FUNCS_UP_TO_L(op, name, u) \
    DEFINE_UNOP_STRUCT_UP_TO_L(name, u)
#define DEFINE_UNOP_UP_TO_LL(op, name, u)   \
    DEFINE_UNOP_FUNCS_UP_TO_LL(op, name, u) \
    DEFINE_UNOP_STRUCT_UP_TO_LL(name, u)

#define DEFINE_BINOP_UP_TO_B(op, name, u)   \
    DEFINE_BINOP_FUNCS_UP_TO_B(op, name, u) \
    DEFINE_BINOP_STRUCT_UP_TO_B(name, u)
#define DEFINE_BINOP_UP_TO_S(op, name, u)   \
    DEFINE_BINOP_FUNCS_UP_TO_S(op, name, u) \
    DEFINE_BINOP_STRUCT_UP_TO_S(name, u)
#define DEFINE_BINOP_UP_TO_I(op, name, u)   \
    DEFINE_BINOP_FUNCS_UP_TO_I(op, name, u) \
    DEFINE_BINOP_STRUCT_UP_TO_I(name, u)
#define DEFINE_BINOP_UP_TO_L(op, name, u)   \
    DEFINE_BINOP_FUNCS_UP_TO_L(op, name, u) \
    DEFINE_BINOP_STRUCT_UP_TO_L(name, u)
#define DEFINE_BINOP_UP_TO_LL(op, name, u)   \
    DEFINE_BINOP_FUNCS_UP_TO_LL(op, name, u) \
    DEFINE_BINOP_STRUCT_UP_TO_LL(name, u)


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

#define TEST_OP(prefix, bits)                                                                            \
    if (op->prefix)                                                                                      \
    {                                                                                                    \
        unsigned digits = (bits + 3) / 4;                                                                \
        unsigned long long result = (op->prefix)(x, y) & ((1ULL << (bits - 1) << 1) - 1);                \
        x_printf("\n%*s%s=%*s%0*llX", prefixLength, #prefix, op->name, 16 - digits, "", digits, result); \
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


DEFINE_UNOP_UP_TO_LL(~, not, )
DEFINE_UNOP_UP_TO_LL(-, neg, )

DEFINE_UNOP_FUNCS_UP_TO_I(abs, abs, )
DEFINE_UNOP_FUNC_L(labs, abs, )
DEFINE_UNOP_FUNC_LL(llabs, abs, )
DEFINE_UNOP_STRUCT_UP_TO_LL(abs, )

DEFINE_UNOP_FUNC_B(__builtin_bitreverse8, bitrev, )
DEFINE_UNOP_FUNC_S(__builtin_bitreverse16, bitrev, )
DEFINE_UNOP_FUNC_I(__builtin_bitreverse24, bitrev, )
DEFINE_UNOP_FUNC_L(__builtin_bitreverse32, bitrev, )
DEFINE_UNOP_FUNC_LL(__builtin_bitreverse64, bitrev, )
DEFINE_UNOP_STRUCT_UP_TO_LL(bitrev, )

// Needs to be unsigned to avoid extra bits from sign extension
DEFINE_UNOP_FUNCS_UP_TO_I(__builtin_popcount, popcnt, u)
DEFINE_UNOP_FUNC_L(__builtin_popcountl, popcnt, u)
DEFINE_UNOP_FUNC_LL(__builtin_popcountll, popcnt, u)
DEFINE_UNOP_STRUCT_UP_TO_LL(popcnt, u)

DEFINE_BINOP_UP_TO_LL(&, and, )
DEFINE_BINOP_UP_TO_LL(|, or, )
DEFINE_BINOP_UP_TO_LL(^, xor, )
DEFINE_BINOP_UP_TO_LL(+, add, )
DEFINE_BINOP_UP_TO_LL(-, sub, )
DEFINE_BINOP_UP_TO_LL(<<, shl, )
DEFINE_BINOP_UP_TO_LL(>>, shru, u)
DEFINE_BINOP_UP_TO_LL(>>, shrs, )
DEFINE_BINOP_UP_TO_LL(*, mulu, u)
DEFINE_BINOP_UP_TO_LL(/, divu, u)
DEFINE_BINOP_UP_TO_LL(/, divs, )
DEFINE_BINOP_UP_TO_LL(%, remu, u)
DEFINE_BINOP_UP_TO_LL(%, rems, )


static const UnOp *unops[] = {
    &unop_not,
    &unop_neg,
    &unop_abs,
    &unop_bitrev,
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
};


int main(int argc, char *argv[])
{
    int64_t x = argc > 1 ? atoll_(argv[1]) : (int64_t)0xDFA5FBC197EDB389LL;
    int64_t y = argc > 2 ? atoll_(argv[2]) : (int64_t)0x08010A030C050E07LL;

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
