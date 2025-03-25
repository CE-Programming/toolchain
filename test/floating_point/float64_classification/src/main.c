#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

/* Float64 test */

typedef struct testb {
    // uint64_t start;
    uint64_t end;
    bool is_finite;
    bool is_inf;
    bool is_nan;
    bool is_normal;
    bool is_subnormal;
    bool is_zero;
    int fp_class;
} testb;

typedef struct test_result {
    bool passed;
    uint64_t failed_index;
    unsigned int truth;
    unsigned int truth_fp;
    unsigned int guess;
    unsigned int guess_fp;
} test_result;

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

static_assert(
    FP_ZERO      == 0 &&
    FP_INFINITE  == 1 &&
    FP_SUBNORMAL == 2 &&
    FP_NAN       == 3 &&
    FP_NORMAL    == 4,
    "FP_MACROS are wrong"
);

#define MACRO_TO_STR(x) #x
#define NUM_TO_STR(x) MACRO_TO_STR(x)

/**
 * Basic Testing: 13 (Covers all exponent values and the MSB of the mantissa)
 * Advanced Testing: 18 (Covers bugs that involve checking if the lower 48 bits are zero)
 */
#define test_count 13
/* fastest type that can handle 2^test_count */
typedef uint24_t test_count_t;

static const testb test_values[] = {
    {/* UINT64_C(0x0000000000000000), */ UINT64_C(0x0000000000000000), true , false, false, false, false, true , FP_ZERO     },
    {/* UINT64_C(0x0000000000000001), */ UINT64_C(0x000FFFFFFFFFFFFF), true , false, false, false, true , false, FP_SUBNORMAL},
    {/* UINT64_C(0x0010000000000000), */ UINT64_C(0x7FEFFFFFFFFFFFFF), true , false, false, true , false, false, FP_NORMAL   },
    {/* UINT64_C(0x7FF0000000000000), */ UINT64_C(0x7FF0000000000000), false, true , false, false, false, false, FP_INFINITE },
    {/* UINT64_C(0x7FF0000000000001), */ UINT64_C(0x7FFFFFFFFFFFFFFF), false, false, true , false, false, false, FP_NAN      },
    {/* UINT64_C(0x8000000000000000), */ UINT64_C(0x8000000000000000), true , false, false, false, false, true , FP_ZERO     },
    {/* UINT64_C(0x8000000000000001), */ UINT64_C(0x800FFFFFFFFFFFFF), true , false, false, false, true , false, FP_SUBNORMAL},
    {/* UINT64_C(0x8010000000000000), */ UINT64_C(0xFFEFFFFFFFFFFFFF), true , false, false, true , false, false, FP_NORMAL   },
    {/* UINT64_C(0xFFF0000000000000), */ UINT64_C(0xFFF0000000000000), false, true , false, false, false, false, FP_INFINITE },
    {/* UINT64_C(0xFFF0000000000001), */ UINT64_C(0xFFFFFFFFFFFFFFFF), false, false, true , false, false, false, FP_NAN      },
};

/**
 * @param test_count Performs 2^test_count tests
 */
static test_result fpclassify_test(void) {

    test_result ret;
    ret.passed = false;
    
    F64_pun x;
    x.bin = 0;
    const testb* ground_truth = &test_values[0];
    int grouth_truth_index = 0;
    for (test_count_t i = 0; i < ((test_count_t)1 << test_count); i++) {
        bool is_finite = isfinite(x.flt);
        bool is_inf = isinf(x.flt);
        bool is_nan = isnan(x.flt);
        bool is_normal = isnormal(x.flt);
        bool is_subnormal = issubnormal(x.flt);
        bool is_zero = iszero(x.flt);
        int fp_class = fpclassify(x.flt);
        if (
            is_finite != ground_truth->is_finite ||
            is_inf != ground_truth->is_inf ||
            is_nan != ground_truth->is_nan ||
            is_normal != ground_truth->is_normal ||
            is_subnormal != ground_truth->is_subnormal ||
            is_zero != ground_truth->is_zero ||
            fp_class != ground_truth->fp_class
        ) {
            ret.passed = false;
            ret.failed_index = x.bin;
            ret.truth =
                (ground_truth->is_finite << (0 * 4)) | (ground_truth->is_inf << (1 * 4))
                | (ground_truth->is_nan << (2 * 4)) | (ground_truth->is_normal << (3 * 4))
                | (ground_truth->is_subnormal << (4 * 4)) | (ground_truth->is_zero << (5 * 4));

            ret.truth_fp = ground_truth->fp_class;
            ret.guess =
                (is_finite << (0 * 4)) | (is_inf << (1 * 4))
                | (is_nan << (2 * 4)) | (is_normal << (3 * 4))
                | (is_subnormal << (4 * 4)) | (is_zero << (5 * 4));

            ret.guess_fp = fp_class;
            return ret;
        }
        x.bin += UINT64_C(1) << (64 - test_count);
        if (x.bin > ground_truth->end) {
            ground_truth++;
            if (grouth_truth_index >= (signed)(sizeof(test_values) / sizeof(testb))) {
                // end of testing
                break;
            }
        }
    }
    ret.passed = true;
    return ret;
}

int main(void) {
    os_ClrHome();
    printf("Testing 2^" NUM_TO_STR(test_count) " inputs");
    test_result ret = fpclassify_test();
    os_ClrHome();
    if (ret.passed) {
        printf("All tests passed");
    } else {
        // just in-case printf does not support long long or uint64_t
        const uint32_t* failed_index_split = (const uint32_t*)((const void*)&(ret.failed_index));
        printf(
            "Failed test:\n0x%08lX%08lX\nTruth: %06X_%d\nGuess: %06X_%d",
            failed_index_split[1], failed_index_split[0], ret.truth, ret.truth_fp, ret.guess, ret.guess_fp
        );
    }

    while (!os_GetCSC());

    return 0;
}