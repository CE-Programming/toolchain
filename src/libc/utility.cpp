#include <utility>

namespace std {

namespace {

#define C(expr) static_assert(expr, #expr)

struct Arg {
    int i = 1;
    int& get() &  { return i; }
    int  get() && { return i; }
};
void foo(...) {}
template<class T> void wrapper(T&& arg) {
    foo(forward<decltype(forward<T>(arg).get())>(forward<T>(arg).get()));
}
[[gnu::used]] void test(Arg arg) {
    wrapper(arg);
    wrapper(move(arg));
}

} // namespace

} // namespace std
