#include <ti/screen.h>
#include <ti/getcsc.h>
#include <cstdio>
#include <expected>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

#define CHECK(expr) do { if (!(expr)) return __LINE__; } while (0)

namespace {

int live = 0;

struct Tracked {
    int value;
    explicit Tracked(int v = 0) noexcept : value(v) { ++live; }
    Tracked(const Tracked& other) noexcept : value(other.value) { ++live; }
    Tracked& operator=(const Tracked&) = default;
    ~Tracked() { --live; }
};

struct NonTrivial {
    int value;
    constexpr NonTrivial(int v) noexcept : value(v) {}
    constexpr NonTrivial(const NonTrivial& other) noexcept : value(other.value) {}
    constexpr NonTrivial& operator=(const NonTrivial& other) {
        value = other.value;
        return *this;
    }
    constexpr ~NonTrivial() {}
};

struct MoveOnly {
    int value;
    constexpr MoveOnly(int v) : value(v) {}
    MoveOnly(const MoveOnly&) = delete;
    constexpr MoveOnly(MoveOnly&& other) noexcept : value(other.value) {}
    MoveOnly& operator=(const MoveOnly&) = delete;
    constexpr MoveOnly& operator=(MoveOnly&& other) noexcept {
        value = other.value;
        return *this;
    }
};

struct Pinned {
    int value;
    constexpr Pinned(int v) : value(v) {}
    Pinned(const Pinned&) = delete;
    Pinned(Pinned&&) = delete;
};

static_assert(sizeof(std::optional<int>) == sizeof(int) + 1);
static_assert(sizeof(std::expected<int, char>) == sizeof(int) + 1);
static_assert(sizeof(std::expected<void, int>) == sizeof(int) + 1);
static_assert(std::is_trivially_copyable_v<std::optional<int>>);
static_assert(std::is_trivially_destructible_v<std::optional<int>>);
static_assert(!std::is_trivially_copyable_v<std::optional<NonTrivial>>);
static_assert(std::is_trivially_copyable_v<std::expected<int, long>>);
static_assert(std::is_trivially_copyable_v<std::expected<void, long>>);
static_assert(!std::is_trivially_destructible_v<std::expected<NonTrivial, int>>);
static_assert(!std::is_copy_constructible_v<std::optional<MoveOnly>>);
static_assert(std::is_move_constructible_v<std::optional<MoveOnly>>);
static_assert(!std::is_copy_constructible_v<std::expected<MoveOnly, int>>);
static_assert(std::is_move_constructible_v<std::expected<MoveOnly, int>>);
static_assert(!std::is_move_constructible_v<std::optional<Pinned>>);
static_assert(std::is_convertible_v<int, std::optional<long>>);
static_assert(std::is_convertible_v<std::optional<int>, std::optional<long>>);
static_assert(std::is_convertible_v<int, std::optional<NonTrivial>>);
static_assert(!std::is_convertible_v<std::unique_ptr<int>, std::expected<int, int>>);

constexpr bool optional_constexpr() {
    std::optional<int> a;
    if (a || a.has_value() || a != std::nullopt) {
        return false;
    }
    a = 5;
    std::optional<int> b = a;
    a.reset();
    if (a.has_value() || b.value() != 5 || *b != 5 || b != 5 || !(a < b) || !(b > 4)) {
        return false;
    }
    std::optional<long> c = b;
    if (c != 5L || std::make_optional(3) != 3) {
        return false;
    }
    if (b.value_or(1) != 5 || a.value_or(1) != 1) {
        return false;
    }
    if (b.transform([](int x) { return x * 2; }) != 10) {
        return false;
    }
    auto positive = [](int x) -> std::optional<long> { return x > 0 ? std::optional<long>(x) : std::nullopt; };
    if (b.and_then(positive) != 5L || std::optional<int>(-1).and_then(positive).has_value()) {
        return false;
    }
    if (a.or_else([] { return std::optional<int>(7); }) != 7) {
        return false;
    }
    std::optional<Pinned> pinned = b.transform([](int x) { return Pinned(x); });
    return pinned->value == 5;
}
static_assert(optional_constexpr());

constexpr bool optional_nontrivial_constexpr() {
    std::optional<NonTrivial> a(std::in_place, 3);
    std::optional<NonTrivial> b = a;
    b.emplace(4);
    a = b;
    a.swap(b);
    std::optional<NonTrivial> c;
    c.swap(a);
    if (a.has_value() || c->value != 4) {
        return false;
    }
    a = std::nullopt;
    b = 9;
    std::optional<MoveOnly> m(std::in_place, 6);
    std::optional<MoveOnly> n = std::move(m);
    return b->value == 9 && n->value == 6;
}
static_assert(optional_nontrivial_constexpr());

constexpr bool expected_constexpr() {
    std::expected<int, int> a = 3;
    std::expected<int, int> b = std::unexpected(4);
    if (!a || b || *a != 3 || b.error() != 4 || a != 3 || b != std::unexpected(4)) {
        return false;
    }
    a = b;
    if (a.has_value() || a.error() != 4) {
        return false;
    }
    a = 9;
    a.swap(b);
    if (b != 9 || a.error() != 4 || a.value_or(0) != 0 || a.error_or(0) != 4) {
        return false;
    }
    if (b.transform([](int x) { return x + 1; }) != 10) {
        return false;
    }
    std::expected<int, long> widened = a.transform_error([](int e) { return e * 10L; });
    if (widened.error() != 40L) {
        return false;
    }
    auto half = [](int x) -> std::expected<int, int> {
        if (x % 2 != 0) {
            return std::unexpected(x);
        }
        return x / 2;
    };
    if (std::expected<int, int>(8).and_then(half) != 4 || std::expected<int, int>(7).and_then(half).error() != 7) {
        return false;
    }
    if (a.or_else([](int e) { return std::expected<int, int>(e + 1); }) != 5) {
        return false;
    }
    std::expected<void, int> v;
    if (!v) {
        return false;
    }
    v = std::unexpected(2);
    if (v || v.error() != 2) {
        return false;
    }
    v.emplace();
    std::expected<long, int> from_void = v.transform([] { return 7L; });
    std::expected<Pinned, int> pinned = std::expected<int, int>(1).transform([](int x) { return Pinned(x); });
    return v.has_value() && from_void == 7L && pinned->value == 1;
}
static_assert(expected_constexpr());

constexpr bool expected_nontrivial_constexpr() {
    std::expected<NonTrivial, NonTrivial> a(std::in_place, 1);
    std::expected<NonTrivial, NonTrivial> b(std::unexpect, 2);
    a = b;
    if (a.has_value() || a.error().value != 2) {
        return false;
    }
    a = NonTrivial(5);
    a.swap(b);
    if (b->value != 5 || a.error().value != 2) {
        return false;
    }
    b = std::unexpected(NonTrivial(6));
    std::expected<NonTrivial, NonTrivial> c = b;
    std::expected<MoveOnly, int> m(std::in_place, 3);
    std::expected<MoveOnly, int> n = std::move(m);
    std::expected<void, NonTrivial> v(std::unexpect, 4);
    std::expected<void, NonTrivial> w;
    v.swap(w);
    return c.error().value == 6 && n->value == 3 && v.has_value() && w.error().value == 4;
}
static_assert(expected_nontrivial_constexpr());

int test_optional() {
    {
        std::optional<Tracked> a(std::in_place, 1);
        std::optional<Tracked> b;
        CHECK(live == 1);
        b = a;
        CHECK(live == 2 && b->value == 1);
        a.reset();
        CHECK(live == 1 && !a);
        a.swap(b);
        CHECK(live == 1 && a && !b);
        b.emplace(4);
        a = std::move(b);
        CHECK(live == 2 && a->value == 4);
        a = std::nullopt;
        CHECK(live == 1);
    }
    CHECK(live == 0);
    {
        std::optional<std::unique_ptr<int>> p = std::make_unique<int>(3);
        std::optional<std::unique_ptr<int>> q = std::move(p);
        CHECK(**q == 3 && *p == nullptr);
    }
    return 0;
}

int test_expected() {
    {
        std::expected<Tracked, Tracked> a(std::in_place, 1);
        std::expected<Tracked, Tracked> b(std::unexpect, 2);
        CHECK(live == 2);
        a = b;
        CHECK(live == 2 && !a && a.error().value == 2);
        b = Tracked(3);
        CHECK(live == 2 && b->value == 3);
        a.swap(b);
        CHECK(live == 2 && a->value == 3 && b.error().value == 2);
        std::expected<Tracked, Tracked> c = a;
        CHECK(live == 3);
    }
    CHECK(live == 0);
    {
        std::expected<void, Tracked> v(std::unexpect, 1);
        CHECK(live == 1);
        v.emplace();
        CHECK(live == 0 && v);
        v = std::unexpected(Tracked(2));
        CHECK(live == 1 && v.error().value == 2);
    }
    CHECK(live == 0);
    {
        std::expected<std::unique_ptr<int>, int> p = std::make_unique<int>(5);
        auto doubled = std::move(p).transform([](std::unique_ptr<int> ptr) { return *ptr * 2; });
        CHECK(doubled == 10);
    }
    return 0;
}

int run_tests() {
    int failed = test_optional();
    if (failed == 0) {
        failed = test_expected();
    }
    return failed;
}

} // namespace

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
