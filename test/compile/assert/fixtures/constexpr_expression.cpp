#include <cassert>

// expected-no-diagnostics

constexpr int check_constexpr_expression(int value) {
    return (assert(value > 0), value);
}

static_assert(check_constexpr_expression(1) == 1, "assert expression must allow constexpr");
