#include <cstdio>
#include <source_location>
#include <cinttypes>

// Do not change the location of this function
int source_location_test(char *buf) {
	const std::source_location location = std::source_location::current();
	char const * const file_name = location.file_name();
	uint_least32_t line = location.line();
	uint_least32_t column = location.column();
	char const * const function_name = location.function_name();
	int ret = std::sprintf(buf,
		"%s(%" PRIuLEAST32 ":%" PRIuLEAST32 ") `%s`\n",
		file_name, line, column, function_name
	);
	return ret;
}

#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <cstring>
#include <type_traits>
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

constexpr int text_len = 54;
static char const * const text =
"src/main.cpp(7:43) `int source_location_test(char *)`\n";

static const int swap_truth[] = {
	5, 3, 3, 5, 6, 9, 9, 6
};

namespace test_swap {
	namespace Ns {
		class A {
			int id {};
	 
			friend void swap(A& lhs, A& rhs) {
				std::swap(lhs.id, rhs.id);
			}
	 
		public:
			A(int i) : id {i} {}
			A(A const&) = delete;
			A& operator = (A const&) = delete;
			int get_val(void) { return id; }
		};
	}
	 
	void swap_test(int *arr) {
		int a = 5, b = 3;
		*arr++ = a;
		*arr++ = b;
		std::swap(a, b);
		*arr++ = a;
		*arr++ = b;
	 
		Ns::A p {6}, q {9};
		*arr++ = p.get_val();
		*arr++ = q.get_val();
		swap(p, q);
		*arr++ = p.get_val();
		*arr++ = q.get_val();
	}
}

int run_tests(void) {
	{
		char buf[64];
		int ret = source_location_test(buf);
		int cmp = std::strcmp(buf, text);
		if (ret != text_len || cmp != 0) {
			std::printf(
				"ret: %d != %d\nstrcmp(buf, text) == %d\n",
				ret, text_len, cmp
			);
			std::fputs(buf, stdout);
			return __LINE__;
		}
	}
	{
		int arr[sizeof(swap_truth) / sizeof(int)];
		test_swap::swap_test(arr);
		for (size_t i = 0; i < sizeof(swap_truth) / sizeof(int); i++) {
			if (arr[i] != swap_truth[i]) {
				printf("%d: %d != %d", i, arr[i], swap_truth[i]);
				return __LINE__;
			}
		}
	}
	return 0;
}

int main(void) {
	os_ClrHome();
	int failed_test = run_tests();
	if (failed_test != 0) {
		std::printf("Failed test L%d\n", failed_test);
	} else {
		std::printf("april fools");
	}

	while (!os_GetCSC());

	return 0;
}
