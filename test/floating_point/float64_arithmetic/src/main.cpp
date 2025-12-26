#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include <bit>
#include <cmath>
#include <numbers>

#define AUTOTEST_DEBUG 0

#ifndef AUTOTEST_DEBUG
#define AUTOTEST_DEBUG 0
#endif

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

#define C(expr) if (!(expr)) { return __LINE__; }

extern volatile long double f64_pos_zero;
extern volatile long double f64_neg_zero;
extern volatile long double f64_pos_one;
extern volatile long double f64_neg_one;
extern volatile long double f64_pos_pi;
extern volatile long double f64_neg_pi;

extern volatile long double f64_pos_tanx;
extern volatile long double f64_neg_tanx;
extern volatile long double f64_pos_tany;
extern volatile long double f64_neg_tany;

extern "C" {
long double drem_libcall(long double x, long double y);
}

int comparison_test(void) {

    /* equal values */

    C((f64_pos_zero == f64_pos_zero));
    C((f64_pos_zero <= f64_pos_zero));
    C((f64_pos_zero >= f64_pos_zero));

    C((f64_neg_zero == f64_neg_zero));
    C((f64_neg_zero <= f64_neg_zero));
    C((f64_neg_zero >= f64_neg_zero));

    C((f64_pos_one == f64_pos_one));
    C((f64_pos_one <= f64_pos_one));
    C((f64_pos_one >= f64_pos_one));

    C((f64_neg_one == f64_neg_one));
    C((f64_neg_one <= f64_neg_one));
    C((f64_neg_one >= f64_neg_one));

    C((f64_pos_pi == f64_pos_pi));
    C((f64_pos_pi <= f64_pos_pi));
    C((f64_pos_pi >= f64_pos_pi));

    C((f64_neg_pi == f64_neg_pi));
    C((f64_neg_pi <= f64_neg_pi));
    C((f64_neg_pi >= f64_neg_pi));

    /* negated values */

    C((f64_pos_zero == f64_neg_zero));
    C((f64_pos_zero <= f64_neg_zero));
    C((f64_pos_zero >= f64_neg_zero));

    C((f64_neg_zero == f64_pos_zero));
    C((f64_neg_zero <= f64_pos_zero));
    C((f64_neg_zero >= f64_pos_zero));

    C((f64_pos_one != f64_neg_one));
    C((f64_pos_one >  f64_neg_one));
    C((f64_pos_one >= f64_neg_one));

    C((f64_neg_one != f64_pos_one));
    C((f64_neg_one <  f64_pos_one));
    C((f64_neg_one <= f64_pos_one));

    C((f64_pos_pi  != f64_neg_pi ));
    C((f64_pos_pi  >  f64_neg_pi ));
    C((f64_pos_pi  >= f64_neg_pi ));

    C((f64_neg_pi  != f64_pos_pi ));
    C((f64_neg_pi  <  f64_pos_pi ));
    C((f64_neg_pi  <= f64_pos_pi ));

    /* compare to zero */

    C((f64_pos_zero != f64_pos_one));
    C((f64_pos_zero <  f64_pos_one));
    C((f64_pos_zero <= f64_pos_one));

    C((f64_pos_zero != f64_pos_pi ));
    C((f64_pos_zero <  f64_pos_pi ));
    C((f64_pos_zero <= f64_pos_pi ));

    C((f64_neg_zero != f64_pos_one));
    C((f64_neg_zero <  f64_pos_one));
    C((f64_neg_zero <= f64_pos_one));

    C((f64_neg_zero != f64_pos_pi ));
    C((f64_neg_zero <  f64_pos_pi ));
    C((f64_neg_zero <= f64_pos_pi ));

    C((f64_pos_zero != f64_neg_one));
    C((f64_pos_zero >  f64_neg_one));
    C((f64_pos_zero >= f64_neg_one));

    C((f64_pos_zero != f64_neg_pi ));
    C((f64_pos_zero >  f64_neg_pi ));
    C((f64_pos_zero >= f64_neg_pi ));

    C((f64_neg_zero != f64_neg_one));
    C((f64_neg_zero >  f64_neg_one));
    C((f64_neg_zero >= f64_neg_one));

    C((f64_neg_zero != f64_neg_pi ));
    C((f64_neg_zero >  f64_neg_pi ));
    C((f64_neg_zero >= f64_neg_pi ));

    /* compare to one */

    C((f64_pos_one != f64_pos_zero));
    C((f64_pos_one >  f64_pos_zero));
    C((f64_pos_one >= f64_pos_zero));

    C((f64_pos_one != f64_pos_pi  ));
    C((f64_pos_one <  f64_pos_pi  ));
    C((f64_pos_one <= f64_pos_pi  ));

    C((f64_neg_one != f64_pos_zero));
    C((f64_neg_one <  f64_pos_zero));
    C((f64_neg_one <= f64_pos_zero));

    C((f64_neg_one != f64_pos_pi  ));
    C((f64_neg_one <  f64_pos_pi  ));
    C((f64_neg_one <= f64_pos_pi  ));

    C((f64_pos_one != f64_neg_zero));
    C((f64_pos_one >  f64_neg_zero));
    C((f64_pos_one >= f64_neg_zero));

    C((f64_pos_one != f64_neg_pi  ));
    C((f64_pos_one >  f64_neg_pi  ));
    C((f64_pos_one >= f64_neg_pi  ));

    C((f64_neg_one != f64_neg_zero));
    C((f64_neg_one <  f64_neg_zero));
    C((f64_neg_one <= f64_neg_zero));

    C((f64_neg_one != f64_neg_pi  ));
    C((f64_neg_one >  f64_neg_pi  ));
    C((f64_neg_one >= f64_neg_pi  ));

    /* compare to pi */

    C((f64_pos_pi != f64_pos_zero));
    C((f64_pos_pi >  f64_pos_zero));
    C((f64_pos_pi >= f64_pos_zero));

    C((f64_pos_pi != f64_pos_one ));
    C((f64_pos_pi >  f64_pos_one ));
    C((f64_pos_pi >= f64_pos_one ));

    C((f64_neg_pi != f64_pos_zero));
    C((f64_neg_pi <  f64_pos_zero));
    C((f64_neg_pi <= f64_pos_zero));

    C((f64_neg_pi != f64_pos_one ));
    C((f64_neg_pi <  f64_pos_one ));
    C((f64_neg_pi <= f64_pos_one ));

    C((f64_pos_pi != f64_neg_zero));
    C((f64_pos_pi >  f64_neg_zero));
    C((f64_pos_pi >= f64_neg_zero));

    C((f64_pos_pi != f64_neg_one ));
    C((f64_pos_pi >  f64_neg_one ));
    C((f64_pos_pi >= f64_neg_one ));

    C((f64_neg_pi != f64_neg_zero));
    C((f64_neg_pi <  f64_neg_zero));
    C((f64_neg_pi <= f64_neg_zero));

    C((f64_neg_pi != f64_neg_one ));
    C((f64_neg_pi <  f64_neg_one ));
    C((f64_neg_pi <= f64_neg_one ));

    return 0;
}

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define F64_CMP_EQUAL      0 /* sets the Z flag */
#define F64_CMP_LESS      -1 /* sets the S flag */
#define F64_CMP_GREATER    1 /* doesn't trigger flags */
#define F64_CMP_UNORDERED  1 /* doesn't trigger flags */

// assumes no NaN
int dcmp(long double arg_x, long double arg_y) {
    F64_pun x, y;
    x.flt = arg_x;
    y.flt = arg_y;

    bool x_sign = signbit(x.flt);
    bool y_sign = signbit(y.flt);
    if (x_sign != y_sign) {
        if (iszero(x.flt) && iszero(y.flt)) {
            return F64_CMP_EQUAL;
        }
        return (x_sign ? F64_CMP_LESS : F64_CMP_GREATER);
    }
    
    if (x.bin == y.bin) {
        return F64_CMP_EQUAL;
    }
    return ((x.bin < y.bin) != x_sign) ? F64_CMP_LESS : F64_CMP_GREATER;
}

static uint64_t rand64(void) {
    union {
        uint64_t u64;
        uint16_t u16[4];
    } split;
    split.u16[0] = (uint16_t)rand();
    split.u16[1] = (uint16_t)rand();
    split.u16[2] = (uint16_t)rand();
    split.u16[3] = (uint16_t)rand();
    return split.u64;
}

#if AUTOTEST_DEBUG
void print_failed(size_t i, const char* s, uint64_t x, uint64_t y) {
    printf(
        "%zu: %s\nX: %016llX\nY: %016llX\n",
        i, s, x, y
    );
}
#else
#define print_failed(...)
#endif

int random_comparison_test(void) {
    srand(0x7184CE);
    for (size_t i = 0; i < 128; i++) {
        F64_pun x, y;
        x.bin = rand64();
        y.bin = rand64();
        int cmp = dcmp(x.flt, y.flt);
        if ((cmp == 0) != (x.flt == y.flt)) {
            print_failed(i, "eq", x.bin, y.bin);
            return __LINE__;
        }
        if ((cmp != 0) != (x.flt != y.flt)) {
            print_failed(i, "ne", x.bin, y.bin);
            return __LINE__;
        }
        if ((cmp < 0) != (x.flt < y.flt)) {
            print_failed(i, "lt", x.bin, y.bin);
            return __LINE__;
        }
        if ((cmp <= 0) != (x.flt <= y.flt)) {
            print_failed(i, "le", x.bin, y.bin);
            return __LINE__;
        }
        if ((cmp > 0) != (x.flt > y.flt)) {
            print_failed(i, "gt", x.bin, y.bin);
            return __LINE__;
        }
        if ((cmp >= 0) != (x.flt >= y.flt)) {
            print_failed(i, "ge", x.bin, y.bin);
            return __LINE__;
        }
    }
    return 0;
}

int basic_test(void) {
    {
        int ret = comparison_test();
        if (ret != 0) {
            return ret;
        }
        ret = random_comparison_test();
        if (ret != 0) {
            return ret;
        }
    }
    
    /*  fmodl test */
    long double trunc_part;
    C((std::fmod(f64_pos_pi, f64_pos_one) == std::modf(f64_pos_pi, &trunc_part)));
    C((trunc_part == 3.0L));
    C((std::fmod(f64_neg_pi, f64_pos_one) == std::modf(f64_neg_pi, &trunc_part)));
    C((trunc_part == -3.0L));
    C((std::fmod(f64_pos_pi, f64_neg_one) == std::modf(f64_pos_pi, &trunc_part)));
    C((trunc_part == 3.0L));
    C((std::fmod(f64_neg_pi, f64_neg_one) == std::modf(f64_neg_pi, &trunc_part)));
    C((trunc_part == -3.0L));

    /*  drem test */
    C((drem_libcall(f64_pos_pi, f64_pos_one) == std::modf(f64_pos_pi, &trunc_part)));
    C((trunc_part == 3.0L));
    C((drem_libcall(f64_neg_pi, f64_pos_one) == std::modf(f64_neg_pi, &trunc_part)));
    C((trunc_part == -3.0L));
    C((drem_libcall(f64_pos_pi, f64_neg_one) == std::modf(f64_pos_pi, &trunc_part)));
    C((trunc_part == 3.0L));
    C((drem_libcall(f64_neg_pi, f64_neg_one) == std::modf(f64_neg_pi, &trunc_part)));
    C((trunc_part == -3.0L));

    return 0;
}

int main(void) {
    os_ClrHome();
    int comparison_result = basic_test();
    if (comparison_result != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", comparison_result);
        puts(buf);
    } else {
        int64_t fail_ulp = 0;
        size_t fail_index = run_test(&fail_ulp);
        if (fail_index == SIZE_MAX) {
            puts("All tests passed");
        } else {
            char buf[sizeof("Failed test: 16777215")];
            boot_sprintf(buf, "Failed test: %u", fail_index);
            puts(buf);
            #if 0
                /* debugging */
                printf("ULP: %lld\n", fail_ulp);
            #endif
        }
    }
    while (!os_GetCSC());

    return 0;
}
