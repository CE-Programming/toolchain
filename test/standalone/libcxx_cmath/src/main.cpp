#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <numbers>

#include <ti/getcsc.h>
#include <ti/screen.h>

#define C(expr) if (!(expr)) { return __LINE__; }

static_assert(sizeof(long double) == sizeof(std::uint64_t));
#if __cplusplus >= 202302L
static_assert(std::signbit(-0.0f) && std::signbit(-0.0L));
static_assert(std::isnan(std::numeric_limits<float>::quiet_NaN()));
static_assert(std::isinf(std::numeric_limits<long double>::infinity()));
static_assert(!std::isfinite(std::numeric_limits<double>::infinity()));
static_assert(std::isnormal(1.0f));
#endif

template <class Float, class Bits>
static int test_classification(const Bits* patterns) {
    const int classes[] = {FP_ZERO, FP_ZERO, FP_NORMAL, FP_SUBNORMAL,
                           FP_INFINITE, FP_INFINITE, FP_NAN, FP_NAN};
    for (unsigned i = 0; i < 8; ++i) {
        // Prevent folding: the compiler must classify both quiet and signaling NaNs.
        volatile Bits bits = patterns[i];
        Float value = std::bit_cast<Float>(Bits(bits));
        C((std::fpclassify(value) == classes[i]));
        C((std::isnan(value) == (classes[i] == FP_NAN)));
        C((std::isinf(value) == (classes[i] == FP_INFINITE)));
        C((std::isfinite(value) == (classes[i] != FP_NAN && classes[i] != FP_INFINITE)));
        C((std::isnormal(value) == (classes[i] == FP_NORMAL)));
        C((std::signbit(value) == (i == 1 || i == 5)));
    }
    return 0;
}

// Keep the bit patterns and comparisons at runtime. The reference below uses
// integer ranks, independently of floating-point arithmetic or classification.
template <class F> __attribute__((noinline)) unsigned short compare_flags(F x, F y) {
    int p[] = {false,
               x == y,
               __builtin_isgreater(x, y),
               __builtin_isgreaterequal(x, y),
               __builtin_isless(x, y),
               __builtin_islessequal(x, y),
               __builtin_islessgreater(x, y),
               !__builtin_isunordered(x, y),
               __builtin_isunordered(x, y),
               !__builtin_islessgreater(x, y),
               !__builtin_islessequal(x, y),
               !__builtin_isless(x, y),
               !__builtin_isgreaterequal(x, y),
               !__builtin_isgreater(x, y),
               x != y,
               true};
    unsigned short mask = 0;
    for (unsigned i = 0; i < 16; ++i)
        if (p[i])
            mask |= (unsigned short)(1u << i);
    return mask;
}
static unsigned short expected_flags(unsigned i, unsigned j) {
    bool ord = i < 10 && j < 10;
    unsigned ri = i == 5 ? 4 : i, rj = j == 5 ? 4 : j;
    bool eq = ri == rj, gt = ri > rj, lt = ri < rj, uno = !ord;
    int p[] = {false,     ord && eq,         ord && gt,  ord && (gt || eq),
               ord && lt, ord && (lt || eq), ord && !eq, ord,
               uno,       uno || eq,         uno || gt,  uno || gt || eq,
               uno || lt, uno || lt || eq,   uno || !eq, true};
    unsigned short mask = 0;
    for (unsigned k = 0; k < 16; ++k)
        if (p[k])
            mask |= (unsigned short)(1u << k);
    return mask;
}
template <class F, class U> static int test_comparisons(const U* bits) {
    for (unsigned i = 0; i < 14; ++i)
        for (unsigned j = 0; j < 14; ++j) {
            volatile U a = bits[i], b = bits[j];
            unsigned short got = compare_flags(std::bit_cast<F>(U(a)), std::bit_cast<F>(U(b)));
            unsigned short expected = expected_flags(i, j);
            if (got != expected) {
                std::printf("T%u %u/%u %04X %04X\n", (unsigned)sizeof(F), i, j, (unsigned)got,
                            (unsigned)expected);
                return __LINE__;
            }
        }
    return 0;
}

int run_tests() {
    using std::bit_cast;

    const std::uint32_t patterns32[] = {0x00000000, 0x80000000, 0x3F800000, 0x00000001,
                                        0x7F800000, 0xFF800000, 0x7FC00000, 0x7FA00000};
    const std::uint64_t patterns64[] = {UINT64_C(0x0000000000000000), UINT64_C(0x8000000000000000),
                                        UINT64_C(0x3FF0000000000000), UINT64_C(0x0000000000000001),
                                        UINT64_C(0x7FF0000000000000), UINT64_C(0xFFF0000000000000),
                                        UINT64_C(0x7FF8000000000000), UINT64_C(0x7FF4000000000000)};
    int failure = test_classification<float>(patterns32);
    if (failure)
        return failure;
    failure = test_classification<double>(patterns32);
    if (failure)
        return failure;
    failure = test_classification<long double>(patterns64);
    if (failure)
        return failure;

    const std::uint32_t b32[] = {0xFF800000, 0xFF7FFFFF, 0xBF800000, 0x80000001, 0x80000000,
                                 0,          1,          0x3F800000, 0x7F7FFFFF, 0x7F800000,
                                 0x7FC00000, 0x7F800001, 0xFFC00000, 0xFF800001};
    const std::uint64_t b64[] = {0xFFF0000000000000ULL,
                                 0xFFEFFFFFFFFFFFFFULL,
                                 0xBFF0000000000000ULL,
                                 0x8000000000000001ULL,
                                 0x8000000000000000ULL,
                                 0,
                                 1,
                                 0x3FF0000000000000ULL,
                                 0x7FEFFFFFFFFFFFFFULL,
                                 0x7FF0000000000000ULL,
                                 0x7FF8000000000000ULL,
                                 0x7FF0000000000001ULL,
                                 0xFFF8000000000000ULL,
                                 0xFFF0000000000001ULL};
    failure = test_comparisons<float>(b32);
    if (failure)
        return failure;
    failure = test_comparisons<double>(b32);
    if (failure)
        return failure;
    failure = test_comparisons<long double>(b64);
    if (failure)
        return failure;

    const long double pos_zero = bit_cast<long double>(UINT64_C(0x0000000000000000));
    const long double neg_zero = bit_cast<long double>(UINT64_C(0x8000000000000000));
    const long double pos_pi = bit_cast<long double>(UINT64_C(0x400921FB54442D18));
    const long double neg_pi = bit_cast<long double>(UINT64_C(0xC00921FB54442D18));
    const long double pos_inf = bit_cast<long double>(UINT64_C(0x7FF0000000000000));

    C((bit_cast<std::uint64_t>(std::numbers::pi_v<long double>) == UINT64_C(0x400921FB54442D18)));
    C((bit_cast<std::uint64_t>(std::numbers::e_v<long double>) == UINT64_C(0x4005BF0A8B145769)));
    C((bit_cast<std::uint64_t>(std::numbers::ln2_v<long double>) == UINT64_C(0x3FE62E42FEFA39EF)));
    C((bit_cast<std::uint64_t>(std::numbers::egamma_v<long double>) == UINT64_C(0x3FE2788CFC6FB619)));

    C((bit_cast<std::uint64_t>(std::abs(neg_zero)) == UINT64_C(0x0000000000000000)));
    C((bit_cast<std::uint64_t>(std::abs(neg_pi)) == UINT64_C(0x400921FB54442D18)));
    C((bit_cast<std::uint64_t>(std::fabs(neg_pi)) == UINT64_C(0x400921FB54442D18)));

    C((bit_cast<std::uint64_t>(std::copysign(pos_pi, neg_zero)) == UINT64_C(0xC00921FB54442D18)));
    C((bit_cast<std::uint64_t>(std::copysign(neg_pi, pos_zero)) == UINT64_C(0x400921FB54442D18)));
    C((bit_cast<std::uint64_t>(std::copysign(pos_zero, neg_zero)) == UINT64_C(0x8000000000000000)));
    C((bit_cast<std::uint64_t>(std::copysign(pos_inf, neg_zero)) == UINT64_C(0xFFF0000000000000)));

    return 0;
}

int main(void) {
    os_ClrHome();

    int failed_test = run_tests();
    if (failed_test != 0) {
        std::printf("Failed test L%d\n", failed_test);
    } else {
        std::printf("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
