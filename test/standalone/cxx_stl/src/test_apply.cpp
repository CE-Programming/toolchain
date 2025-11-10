#include "common.h"

static int add(int first, int second) { return first + second; }

template<typename T>
T add_generic(T first, T second) { return first + second; }

auto add_lambda = [](auto first, auto second) { return first + second; };

template<typename... Ts>
ostream& operator<<(ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}

int test_apply()
{
    // OK
    cout << std::apply(add, std::pair(1, 2)) << '\n';

    // Error: can't deduce the function type
    // cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << '\n';

    // OK
    cout << std::apply(add_lambda, std::pair(2.0f, 3.0f)) << '\n';

    // advanced example
    std::tuple myTuple{25, "Hello", 9.31f, 'c'};
    cout << myTuple << '\n';
	return 0;
}
