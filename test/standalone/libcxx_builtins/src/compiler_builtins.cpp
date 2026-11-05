#include <algorithm>
#include <bitset>
#include <cstdint>
#include <limits>
#include <__locale_dir/num.h>

#define C(expr)                                                                                    \
    if (!(expr))                                                                                   \
        return __LINE__;

// Keep signedness and value ranges unknown to the optimizer, as in num_get.
template <class T> __attribute__((noinline)) bool multiply(T value, int base, T* out) {
    return __builtin_mul_overflow(value, base, out);
}
template <class T> __attribute__((noinline)) bool parse_step(T value, int base, int digit) {
    return __builtin_mul_overflow(value, base, &value) ||
           __builtin_add_overflow(value, digit, &value);
}

template <class T> static int test_overflow() {
    constexpr T max = std::numeric_limits<T>::max();
    const T values[] = {0, 1, 2, T(max / 16), T(max / 10), T(max / 2), T(max - 1), max};
    const int bases[] = {2, 8, 10, 16};
    for (T initial : values) {
        volatile T input = initial;
        for (int base : bases) {
            T product;
            volatile int unknown_base = base;
            bool overflow = multiply(T(input), unknown_base, &product);
            C(overflow == (input > max / unsigned(base)));
            C(product == T(std::uint64_t(input) * unsigned(base)));
            for (unsigned digit = 0; digit < unsigned(base); ++digit) {
                T sum;
                volatile int unknown_digit = int(digit);
                overflow = __builtin_add_overflow(T(input), unknown_digit, &sum);
                C(overflow == (input > max - digit));
                C(sum == T(std::uint64_t(input) + digit));
                // Match num_get's mixed-width operands and short circuit.
                bool combined = parse_step(T(input), unknown_base, unknown_digit);
                C(combined == (input > (max - digit) / unsigned(base)));
            }
        }
    }
    return 0;
}

template <unsigned N> static constexpr bool check_bitset() {
    std::bitset<N> bits;
    if (bits.count() != 0)
        return false;
    bits.set();
    if (bits.count() != N)
        return false;
    bits.flip();
    if (bits.count() != 0)
        return false;
    for (unsigned i = 0; i < N; ++i) {
        bits.set(i);
        if (bits.count() != i + 1)
            return false;
    }
    return true;
}
static_assert(check_bitset<0>() && check_bitset<1>() && check_bitset<7>() && check_bitset<8>());
static_assert(check_bitset<9>() && check_bitset<16>() && check_bitset<23>() && check_bitset<24>());
static_assert(check_bitset<25>() && check_bitset<47>() && check_bitset<48>() &&
              check_bitset<49>() && check_bitset<64>());

template <unsigned N> static int test_bitset() {
    std::bitset<N> bits;
    // A runtime recurrence and per-bit reference cover partial storage words.
    volatile unsigned seed = 0x13579B;
    unsigned state = seed;
    for (unsigned round = 0; round < 20; ++round) {
        unsigned expected = 0;
        for (unsigned i = 0; i < N; ++i) {
            state = state * 33 + 1;
            bool bit = (state & 0x100) != 0;
            bits.set(i, bit);
            expected += bit;
        }
        C(bits.count() == expected);
        C((~bits).count() == N - expected);
    }
    return 0;
}

template <class T> static int test_algorithms() {
    T a[35], b[35];
    for (unsigned n = 0; n <= 35; ++n) {
        for (unsigned i = 0; i < 35; ++i)
            a[i] = b[i] = T(i % 5);
        volatile T needle = 3;
        T value = needle;
        C(std::find(a, a + n, value) == a + (n > 3 ? 3 : n));
        C(std::count(a, a + n, value) == (n + 1) / 5);
        C(std::equal(a, a + n, b));
        C(std::mismatch(a, a + n, b).first == a + n);
        // Mismatches at every offset catch vector/tail boundary mistakes.
        for (unsigned i = 0; i < n; ++i) {
            b[i] = T(42);
            C(!std::equal(a, a + n, b));
            C(std::mismatch(a, a + n, b).first == a + i);
            C(std::mismatch(a, a + n, b).second == b + i);
            b[i] = a[i];
        }
        C(std::find(a, a + n, T(42)) == a + n);
    }
    return 0;
}

static int test_locale_search() {
    const char atoms[] = "0123456789abcdefABCDEFxX+-";
    for (unsigned i = 0; i < 26; ++i) {
        volatile char value = atoms[i];
        C(std::__num_get<char>::__atoms_offset(atoms, value) == std::ptrdiff_t(i));
    }
    volatile char missing = '?';
    C(std::__num_get<char>::__atoms_offset(atoms, missing) == 26);
    return 0;
}

int test_compiler_builtins() {
    int failure;
#define TEST(expr)                                                                                 \
    if ((failure = (expr)))                                                                        \
        return failure;
    TEST(test_locale_search());
    TEST(test_overflow<std::uint8_t>());
    TEST(test_overflow<std::uint16_t>());
    TEST(test_overflow<unsigned>());
    TEST(test_overflow<std::uint32_t>());
    TEST(test_overflow<uint48_t>());
    TEST(test_overflow<std::uint64_t>());
    TEST(test_bitset<0>());
    TEST(test_bitset<1>());
    TEST(test_bitset<7>());
    TEST(test_bitset<8>());
    TEST(test_bitset<9>());
    TEST(test_bitset<16>());
    TEST(test_bitset<23>());
    TEST(test_bitset<24>());
    TEST(test_bitset<25>());
    TEST(test_bitset<47>());
    TEST(test_bitset<48>());
    TEST(test_bitset<49>());
    TEST(test_bitset<64>());
    TEST(test_algorithms<char>());
    TEST(test_algorithms<short>());
    TEST(test_algorithms<int>());
    TEST(test_algorithms<long>());
    TEST(test_algorithms<long long>());
#undef TEST
    return 0;
}
