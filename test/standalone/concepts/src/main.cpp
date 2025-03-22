#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdio.h>

#include <concepts>

// test derived_from
namespace test_derived_from {
    class A {};
    class B : public A {};
    class C : private A {};
    
    static_assert(std::derived_from<B, B> == true);
    static_assert(std::derived_from<int, int> == false);
    static_assert(std::derived_from<B, A> == true);
    static_assert(std::derived_from<C, A> == false);

    static_assert(std::is_base_of_v<B, B> == true);
    static_assert(std::is_base_of_v<int, int> == false);
    static_assert(std::is_base_of_v<A, B> == true);
    static_assert(std::is_base_of_v<A, C> == true);
}

// test integral
static_assert(std::integral<bool>);
static_assert(std::integral<char>);
static_assert(std::integral<int>);
static_assert( ! std::integral<double> );
static_assert( ! std::integral<decltype("")> );

// test floating_point
namespace test_floating_point {
    constexpr std::floating_point auto x2(std::floating_point auto x) {
        return x + x;
    }
    constexpr std::integral auto x2(std::integral auto x) {
        return x << 1;
    }

    constexpr auto d = x2(1.1);
    constexpr auto f = x2(2.2f);
    constexpr auto i = x2(444);
    
    static_assert(std::is_same_v<double const, decltype(d)>);
    static_assert(std::is_same_v<float const, decltype(f)>);
    static_assert(std::is_same_v<int const, decltype(i)>);
}

int run_tests(void) {
    return 0;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        printf("Failed test L%d\n", failed_test);
    } else {
        printf("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
