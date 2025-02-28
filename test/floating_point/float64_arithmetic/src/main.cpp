#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include <bit>
#include <cmath>
#include <numbers>

#include "f64_arithmetic_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static long double arithmetic_test(long double arg) {
	long double x = arg;
	x += std::numbers::pi_v<long double>;
	x *= std::numbers::e_v<long double>;
	long double y = ++x;
	x = std::fma(x, std::numbers::egamma_v<long double>, y);
	y /= std::numbers::ln2_v<long double> - x;
	y = std::copysign(y, x--);
	x -= std::fabs(x) + y;
	return x;
}

static int64_t calc_ULP(long double guess, long double truth) {
    if (std::signbit(guess) == std::signbit(truth)) {
        return std::bit_cast<int64_t>(guess) - std::bit_cast<int64_t>(truth);
    }
    return (
        std::bit_cast<int64_t>(std::fabs(guess)) + std::bit_cast<int64_t>(std::fabs(truth))
    ) * (std::signbit(guess) ? -1 : 1);
}

static size_t run_test(int64_t* fail_ulp) {
    typedef long double input_t;
    typedef long double output_t;

    const size_t length = ARRAY_LENGTH(f64_arithmetic_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_arithmetic_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_arithmetic_LUT_output);

    long double result;
    for (size_t i = 0; i < length; i++) {
        result = arithmetic_test(input[i]);
        if (std::bit_cast<uint64_t>(result) != std::bit_cast<uint64_t>(output[i])) {
            int64_t ulp = calc_ULP(result, output[i]);
            if (std::abs(ulp) > 32) {
                *fail_ulp = ulp;
                return i;
            }
        }
    }

    /* passed all */
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    int64_t fail_ulp = 0;
    size_t fail_index = run_test(&fail_ulp);
    if (fail_index == SIZE_MAX) {
        printf("All tests passed");
    } else {
        printf("Failed test: %zu\nULP: %lld", fail_index, fail_ulp);
    }

    while (!os_GetCSC());

    return 0;
}
