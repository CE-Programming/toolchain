#include <algorithm>
#include <charconv>
#include <chrono>
#include <cmath>
#include <expected>
#include <iterator>
#include <map>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include <stdio.h>
#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/sprintf.h>

#define C(expr) if (!(expr)) { return __LINE__; }

// libc++ 23 used a floating-point expression cast to int here. The CE has
// 24-bit int and 32-bit double, so the period must be formed with exact integers.
static_assert(std::chrono::years::period::num == 31556952L);
static_assert(std::chrono::years::period::den == 1);
static_assert(std::chrono::months::period::num == 2629746L);
static_assert(std::chrono::months::period::den == 1);

// The CE extended integer must participate in the same overloads as standard integers.
static_assert(std::is_same_v<decltype(std::hypot(int48_t{}, uint48_t{}, float{})), double>);
static_assert(std::is_same_v<decltype(std::to_string(int48_t{})), std::string>);
static_assert(std::is_same_v<decltype(std::to_string(uint48_t{})), std::string>);
#if _LIBCPP_HAS_WIDE_CHARACTERS
static_assert(std::is_same_v<decltype(std::to_wstring(int48_t{})), std::wstring>);
static_assert(std::is_same_v<decltype(std::to_wstring(uint48_t{})), std::wstring>);
#endif

static int test_int48_conversions() {
    struct SignedConversion { int48_t value; float single; long double wide; };
    const SignedConversion signed_cases[] = {
        {0, 0.0f, 0.0L}, {-1, -1.0f, -1.0L}, {1, 1.0f, 1.0L},
        {-140737488355328LL, -0x1p47f, -140737488355328.0L},
        {140737488355327LL, 0x1p47f, 140737488355327.0L},
        {-4294967297LL, -0x1p32f, -4294967297.0L},
        {4294967297LL, 0x1p32f, 4294967297.0L}
    };
    struct UnsignedConversion { uint48_t value; float single; long double wide; };
    const UnsignedConversion unsigned_cases[] = {
        {0, 0.0f, 0.0L}, {1, 1.0f, 1.0L},
        {4294967297ULL, 0x1p32f, 4294967297.0L},
        {281474976710655ULL, 0x1p48f, 281474976710655.0L}
    };
    for (const auto& c : signed_cases) {
        volatile int48_t value = c.value;
        C(static_cast<float>(value) == c.single);
        C(static_cast<double>(value) == c.single); // CE double is binary32.
        C(static_cast<long double>(value) == c.wide);
    }
    for (const auto& c : unsigned_cases) {
        volatile uint48_t value = c.value;
        C(static_cast<float>(value) == c.single);
        C(static_cast<double>(value) == c.single);
        C(static_cast<long double>(value) == c.wide);
    }
    // All reverse-cast inputs are in range; fractional cases must truncate toward zero.
    struct SignedReverse32 { float value; int48_t expected; };
    const SignedReverse32 sr32[] = {
        {0.0f, 0}, {1.75f, 1}, {-1.75f, -1}, {0x1p32f, 4294967296LL},
        {-0x1p32f, -4294967296LL}, {-0x1p47f, -140737488355328LL},
        {0x1.fffffep46f, 140737479966720LL}
    };
    struct UnsignedReverse32 { float value; uint48_t expected; };
    const UnsignedReverse32 ur32[] = {
        {0.0f, 0}, {1.75f, 1}, {0x1p32f, 4294967296ULL},
        {0x1p47f, 140737488355328ULL}, {0x1.fffffep47f, 281474959933440ULL}
    };
    struct SignedReverse64 { long double value; int48_t expected; };
    const SignedReverse64 sr64[] = {
        {0.0L, 0}, {1.875L, 1}, {-1.875L, -1}, {4294967297.75L, 4294967297LL},
        {-4294967297.75L, -4294967297LL}, {-140737488355328.0L, -140737488355328LL},
        {140737488355327.75L, 140737488355327LL}
    };
    struct UnsignedReverse64 { long double value; uint48_t expected; };
    const UnsignedReverse64 ur64[] = {
        {0.0L, 0}, {1.875L, 1}, {4294967297.75L, 4294967297ULL},
        {140737488355328.75L, 140737488355328ULL}, {281474976710655.75L, 281474976710655ULL}
    };
    for (const auto& c : sr32) {
        volatile float value = c.value;
        volatile double double_value = c.value;
        C(static_cast<int48_t>(value) == c.expected);
        C(static_cast<int48_t>(double_value) == c.expected);
    }
    for (const auto& c : ur32) {
        volatile float value = c.value;
        volatile double double_value = c.value;
        C(static_cast<uint48_t>(value) == c.expected);
        C(static_cast<uint48_t>(double_value) == c.expected);
    }
    for (const auto& c : sr64) {
        volatile long double value = c.value;
        C(static_cast<int48_t>(value) == c.expected);
    }
    for (const auto& c : ur64) {
        volatile long double value = c.value;
        C(static_cast<uint48_t>(value) == c.expected);
    }
    volatile int48_t three = 3;
    volatile uint48_t four = 4;
    C(std::hypot(three, four, 0.0f) == 5.0);

    return 0;
}

static int test_int48() {
    volatile int48_t signed_count = 3;
    volatile uint48_t unsigned_count = 3;
    int input[] = {1, 2, 3};
    int output[] = {0, 0, 0};
    C(std::copy_n(input, signed_count, output) == output + 3);
    C(std::equal(input, input + 3, output));
    C(std::fill_n(output, unsigned_count, 7) == output + 3);
    C(std::all_of(output, output + 3, [](int x) { return x == 7; }));
    // Exercise both signednesses through each algorithm.
    C(std::copy_n(input, unsigned_count, output) == output + 3);
    C(std::equal(input, input + 3, output));
    C(std::fill_n(output, signed_count, 8) == output + 3);
    C(std::all_of(output, output + 3, [](int x) { return x == 8; }));

    volatile int48_t signed_values[] = {0, -1, 1, std::numeric_limits<int48_t>::min(),
                                      std::numeric_limits<int48_t>::max()};
    volatile uint48_t unsigned_values[] = {0, 1, 0x100000000ULL, std::numeric_limits<uint48_t>::max()};
    const char* signed_text[] = {"0", "-1", "1", "-140737488355328", "140737488355327"};
    const char* unsigned_text[] = {"0", "1", "4294967296", "281474976710655"};
    for (unsigned i = 0; i < 5; ++i) {
        C(std::to_string(signed_values[i]) == signed_text[i]);
    }
    for (unsigned i = 0; i < 4; ++i) {
        C(std::to_string(unsigned_values[i]) == unsigned_text[i]);
    }
#if _LIBCPP_HAS_WIDE_CHARACTERS
    const wchar_t* signed_wtext[] = {L"0", L"-1", L"1", L"-140737488355328", L"140737488355327"};
    const wchar_t* unsigned_wtext[] = {L"0", L"1", L"4294967296", L"281474976710655"};
    for (unsigned i = 0; i < 5; ++i) {
        C(std::to_wstring(signed_values[i]) == signed_wtext[i]);
    }
    for (unsigned i = 0; i < 4; ++i) {
        C(std::to_wstring(unsigned_values[i]) == unsigned_wtext[i]);
    }
#endif

    std::mt19937 engine(12345);
    std::uniform_int_distribution<int48_t> signed_dist(std::numeric_limits<int48_t>::min(),
                                                     std::numeric_limits<int48_t>::max());
    std::uniform_int_distribution<uint48_t> unsigned_dist(0, std::numeric_limits<uint48_t>::max());
    // Neither interval fits in 32 bits; the signed interval also crosses zero.
    const int48_t low = -0x1000000000LL;
    const int48_t high = 0x1000000000LL;
    const uint48_t base = 0x10000000000ULL;
    std::uniform_int_distribution<int48_t> bounded_signed(low, high);
    std::uniform_int_distribution<uint48_t> bounded_unsigned(base, base + 0x1000000000ULL);
    bool negative = false, positive = false, upper_bits = false;
    for (unsigned i = 0; i < 64; ++i) {
        int48_t s = signed_dist(engine);
        uint48_t u = unsigned_dist(engine);
        negative |= s < 0;
        positive |= s > 0;
        upper_bits |= u > 0xFFFFFFFFULL;
        s = bounded_signed(engine);
        u = bounded_unsigned(engine);
        C(s >= low && s <= high);
        C(u >= base && u <= base + 0x1000000000ULL);
    }
    C(negative && positive && upper_bits);
    std::uniform_int_distribution<int48_t> single_signed(-1, -1);
    std::uniform_int_distribution<uint48_t> single_unsigned(base, base);
    C(single_signed(engine) == -1);
    C(single_unsigned(engine) == base);
    return 0;
}

static int run_tests() {
    int int48_failure = test_int48_conversions();
    if (int48_failure) return int48_failure;
    int48_failure = test_int48();
    if (int48_failure) return int48_failure;
    using namespace std::chrono;
    volatile int year_count = 2;
    C(duration_cast<seconds>(years{year_count}).count() == 63113904L);
    C(duration_cast<seconds>(months{year_count}).count() == 5259492L);
    C((year_month_day{year{2024}, February, day{29}}.ok()));
    C((!year_month_day{year{2023}, February, day{29}}.ok()));

    // Exercise the v23 weak-allocation fallback, including both nothrow overloads.
    std::unique_ptr<int> scalar(new (std::nothrow) int(42));
    C(scalar && *scalar == 42);
    std::unique_ptr<int[]> array(new (std::nothrow) int[3]{1, 2, 3});
    C(array && array[2] == 3);
    void* zero_size = ::operator new(0, std::nothrow);
    C(zero_size != nullptr);
    ::operator delete(zero_size);

    std::expected<int, std::string> result = 7;
    C(result.has_value() && result.value() == 7);
    result = std::unexpected(std::string("conversion failed"));
    C(!result && result.error() == "conversion failed");
    C(result.value_or(11) == 11);

    char buffer[16];
    auto encoded = std::to_chars(buffer, buffer + sizeof(buffer), 1234567L);
    C(encoded.ec == std::errc{});
    long decoded = 0;
    auto parsed = std::from_chars(buffer, encoded.ptr, decoded);
    C(parsed.ec == std::errc{} && parsed.ptr == encoded.ptr && decoded == 1234567L);
    std::vector<int> values{9, 2, 7, 1};
    values.push_back(3);
    std::sort(values.begin(), values.end());
    C(values.front() == 1 && values.back() == 9);
    C(std::binary_search(values.begin(), values.end(), 7));

    std::string text("a string long enough to require heap allocation");
    text += " on the CE";
    C(text.substr(text.size() - 9) == "on the CE");
    C(text.find("heap") != std::string::npos);

    auto owned = std::make_unique<std::string>(text);
    C(*owned == text);
    std::optional<std::string> maybe(*owned);
    C(maybe.has_value() && *maybe == text);
    maybe.reset();
    C(!maybe.has_value());

    // LLVM 22.1.8 fixes extraction to select the first equivalent element.
    std::multimap<int, int> map{{1, 10}, {1, 20}, {1, 30}};
    auto node = map.extract(1);
    C(!node.empty() && node.mapped() == 10);
    C(map.size() == 2 && map.begin()->second == 20);

    std::multiset<int> set{1, 1, 2};
    auto first = set.begin();
    auto second = std::next(first);
    auto* second_address = &*second;
    auto set_node = set.extract(1);
    C(!set_node.empty() && set_node.value() == 1);
    C(set.size() == 2 && &*set.begin() == second_address);
    return 0;
}

extern "C" int main() {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }
    while (!os_GetCSC());
    return 0;
}
