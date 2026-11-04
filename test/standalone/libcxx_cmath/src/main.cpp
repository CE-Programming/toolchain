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

template <class Float, class Bits>
static int test_classification(const Bits* patterns) {
    const int classes[] = {FP_ZERO, FP_ZERO, FP_NORMAL, FP_SUBNORMAL,
                           FP_INFINITE, FP_INFINITE, FP_NAN, FP_NAN};
    for (unsigned i = 0; i < 8; ++i) {
        // Prevent folding: the CE runtime must classify both quiet and signaling NaNs.
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

int run_tests() {
    using std::bit_cast;

    const std::uint32_t patterns32[] = {
        0x00000000, 0x80000000, 0x3F800000, 0x00000001,
        0x7F800000, 0xFF800000, 0x7FC00000, 0x7FA00000
    };
    const std::uint64_t patterns64[] = {
        UINT64_C(0x0000000000000000), UINT64_C(0x8000000000000000),
        UINT64_C(0x3FF0000000000000), UINT64_C(0x0000000000000001),
        UINT64_C(0x7FF0000000000000), UINT64_C(0xFFF0000000000000),
        UINT64_C(0x7FF8000000000000), UINT64_C(0x7FF4000000000000)
    };
    int failure = test_classification<float>(patterns32);
    if (failure) return failure;
    failure = test_classification<double>(patterns32);
    if (failure) return failure;
    failure = test_classification<long double>(patterns64);
    if (failure) return failure;

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
