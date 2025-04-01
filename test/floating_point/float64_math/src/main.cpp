#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include <bit>
#include <cmath>
#include <numbers>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static int64_t calc_ULP(long double guess, long double truth) {
	if (std::signbit(guess) == std::signbit(truth)) {
		return std::bit_cast<int64_t>(guess) - std::bit_cast<int64_t>(truth);
	}
	return (
		std::bit_cast<int64_t>(std::fabs(guess)) + std::bit_cast<int64_t>(std::fabs(truth))
	) * (std::signbit(guess) ? -1 : 1);
}

constexpr int Maximum_ULP = 512;
static int64_t fail_ulp = 0;

static bool test_result(long double guess, long double truth) {
	if (std::bit_cast<uint64_t>(guess) != std::bit_cast<uint64_t>(truth)) {
		int64_t ulp = calc_ULP(guess, truth);
		if (std::abs(ulp) > Maximum_ULP) {
			fail_ulp = ulp;
			return true;
		}
	}
	return false;
}

static size_t run_test(void) {
	
	if (test_result(std::asinh(   2.5L),  1.647231146371095710624858610444L)) { return __LINE__; }
	if (test_result(std::asinh(  -9.6L), -2.957611980815783849435355905152L)) { return __LINE__; }
	if (test_result(std::acosh(   3.5L),  1.924847300238413789991035653698L)) { return __LINE__; }
	if (test_result(std::acosh( 1.001L),  0.044717633608309309571769903614L)) { return __LINE__; }
	if (test_result(std::atanh(   0.3L),  0.309519604203111715474067349061L)) { return __LINE__; }
	if (test_result(std::atanh(  -0.9L), -1.472219489583220230004513715944L)) { return __LINE__; }
	if (test_result(std::atan (  12.0L),  1.487655094906455389320653376989L)) { return __LINE__; }
	if (test_result(std::atan (  -1.1L), -0.832981266674431705417693561837L)) { return __LINE__; }

	// if (test_result(std::sinh (   5.0L),  74.20321057778875897700947199607L)) { return __LINE__; }
	// if (test_result(std::sinh (  -9.0L), -4051.541902082789960515223595898L)) { return __LINE__; }
	// if (test_result(std::cosh (   8.0L),  1490.479161252178088627715460421L)) { return __LINE__; }
	// if (test_result(std::cosh (  -2.0L),  3.762195691083631459562213477774L)) { return __LINE__; }
	// if (test_result(std::tanh (   0.8L),  0.664036770267848963684844656400L)) { return __LINE__; }
	// if (test_result(std::tanh (  -3.2L), -0.996682397839651156180968063061L)) { return __LINE__; }

	if (test_result(std::exp  (   6.3L),  544.5719101259290330593886677332L)) { return __LINE__; }
	if (test_result(std::exp  (  -4.2L),  0.014995576820477706211984360229L)) { return __LINE__; }
	if (test_result(std::log  (1.0e-6L), -13.81551055796427410410794872811L)) { return __LINE__; }
	if (test_result(std::log  (3.0e+8L),  19.51929303262047516353917687440L)) { return __LINE__; }

	if (test_result(std::expm1 (	0.2L),  0.221402758160169833921071994640L)) { return __LINE__; }
	if (test_result(std::expm1 (-1.0e-8L), -9.999999950000000166666666250e-9L)) { return __LINE__; }
	if (test_result(std::log1p (   -0.2L), -0.223143551314209755766295090310L)) { return __LINE__; }
	if (test_result(std::log1p ( 1.0e-8L),  9.999999950000000333333330833e-9L)) { return __LINE__; }

	if (test_result(std::erfc (  -1.3L),  1.934007944940652436603893327504L)) { return __LINE__; }
	if (test_result(std::erfc (   3.1L),  0.000011648657367199596033706164L)) { return __LINE__; }
	if (test_result(std::erf  (  -2.2L), -0.998137153702018108556548243971L)) { return __LINE__; }
	if (test_result(std::erf  (   0.5L),  0.520499877813046537682746653892L)) { return __LINE__; }

	if (test_result(
		std::hypot(1.23L, 4.56L, 7.89L),
		9.195575022803087326242198470012610630662L
	)) { return __LINE__; }

	/* passed all */
	return SIZE_MAX;
}

int main(void) {
	os_ClrHome();
	size_t fail_index = run_test();
	if (fail_index == SIZE_MAX) {
		printf("april fools");
	} else {
		printf("Failed test: L%zu\nULP: %lld", fail_index, fail_ulp);
	}

	while (!os_GetCSC());

	return 0;
}
