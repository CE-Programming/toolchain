#include <set>
#include <string>
#include <tuple>

#include "common.h"

struct S
{
    int n;
    std::string s;
    float d;

    friend bool operator<(const S& lhs, const S& rhs) noexcept
    {
        // compares lhs.n to rhs.n,
        // then lhs.s to rhs.s,
        // then lhs.d to rhs.d
        // in that order, first non-equal result is returned
        // or false if all elements are equal
        return std::tie(lhs.n, lhs.s, lhs.d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};

int test_tuple()
{
    // Lexicographical comparison demo:
    std::set<S> set_of_s;

    S value{42, "Test", 3.14};
    std::set<S>::iterator iter;
    bool is_inserted;

    // Unpack a pair:
    std::tie(iter, is_inserted) = set_of_s.insert(value);
    C(is_inserted);


    // std::tie and structured bindings:
    auto position = [](int w) { return std::tuple(1 * w, 2 * w); };

    auto [x, y] = position(1);
    C(x == 1 && y == 2);
    std::tie(x, y) = position(2); // reuse x, y with tie
    C(x == 2 && y == 4);


    // Implicit conversions are permitted:
    std::tuple<char, short> coordinates(6, 9);
    std::tie(x, y) = coordinates;
    C(x == 6 && y == 9);

    // Skip an element:
    std::string z;
    std::tie(x, std::ignore, z) = std::tuple(1, 2.0, "Test");
    C(x == 1 && z == "Test");
	return 0;
}
