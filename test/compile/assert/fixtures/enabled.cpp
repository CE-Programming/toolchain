#include <cassert>

struct condition {
    explicit operator bool() const { return true; }
};

void check_cassert(int value) {
    assert(value);
    assert(condition{});

    /* The macro must also compose correctly with an outer if/else. */
    if (value)
        assert(value > 0);
    else
        assert(value == 0);
}
