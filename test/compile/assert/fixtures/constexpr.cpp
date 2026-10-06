#include <cassert>

constexpr int check_constexpr_assert(int value) {
    assert(value > 0);
    return value;
}

static_assert(check_constexpr_assert(1) == 1, "passing assert must allow constexpr");
