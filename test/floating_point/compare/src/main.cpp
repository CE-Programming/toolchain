#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 1

//------------------------------------------------------------------------------
// Tables
//------------------------------------------------------------------------------

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static const uint32_t f32_ordered_values[] = {
    UINT32_C(0xFF800000),
    UINT32_C(0xFF7FFFFF),
    UINT32_C(0xFF7FFFFE),
    UINT32_C(0xC0000001),
    UINT32_C(0xC0000000),
    UINT32_C(0xBFFFFFFF),
    UINT32_C(0xBF800001),
    UINT32_C(0xBF800000),
    UINT32_C(0xBF7FFFFF),
    UINT32_C(0xBF000001),
    UINT32_C(0xBF000000),
    UINT32_C(0xBEFFFFFF),
    UINT32_C(0x80800001),
    UINT32_C(0x80800000),
    UINT32_C(0x807FFFFF),
    UINT32_C(0x80000002),
    UINT32_C(0x80000001),
    UINT32_C(0x80000000),

    UINT32_C(0x00000000),
    UINT32_C(0x00000001),
    UINT32_C(0x00000002),
    UINT32_C(0x007FFFFF),
    UINT32_C(0x00800000),
    UINT32_C(0x00800001),
    UINT32_C(0x3EFFFFFF),
    UINT32_C(0x3F000000),
    UINT32_C(0x3F000001),
    UINT32_C(0x3F7FFFFF),
    UINT32_C(0x3F800000),
    UINT32_C(0x3F800001),
    UINT32_C(0x3FFFFFFF),
    UINT32_C(0x40000000),
    UINT32_C(0x40000001),
    UINT32_C(0x7F7FFFFE),
    UINT32_C(0x7F7FFFFF),
    UINT32_C(0x7F800000),
};
static_assert(ARRAY_LENGTH(f32_ordered_values) % 2 == 0);

static const uint32_t f32_unordered_values[] = {
    UINT32_C(0xFFFFFFFF),
    UINT32_C(0xFFC00000),
    UINT32_C(0xFFBFFFFF),
    UINT32_C(0xFFA00000),
    UINT32_C(0xFF800001),

    UINT32_C(0x7F800001),
    UINT32_C(0x7FA00000),
    UINT32_C(0x7FBFFFFF),
    UINT32_C(0x7FC00000),
    UINT32_C(0x7FFFFFFF),
};
static_assert(ARRAY_LENGTH(f32_unordered_values) % 2 == 0);

static const uint64_t f64_ordered_values[] = {
    UINT64_C(0xFFF0000000000000),
    UINT64_C(0xFFEFFFFFFFFFFFFF),
    UINT64_C(0xFFEFFFFFFFFFFFFE),
    UINT64_C(0xC000000000000001),
    UINT64_C(0xC000000000000000),
    UINT64_C(0xBFFFFFFFFFFFFFFF),
    UINT64_C(0xBFF0000000000001),
    UINT64_C(0xBFF0000000000000),
    UINT64_C(0xBFEFFFFFFFFFFFFF),
    UINT64_C(0xBFE0000000000001),
    UINT64_C(0xBFE0000000000000),
    UINT64_C(0xBFDFFFFFFFFFFFFF),
    UINT64_C(0x8010000000000001),
    UINT64_C(0x8010000000000000),
    UINT64_C(0x800FFFFFFFFFFFFF),
    UINT64_C(0x8000000000000002),
    UINT64_C(0x8000000000000001),
    UINT64_C(0x8000000000000000),

    UINT64_C(0x0000000000000000),
    UINT64_C(0x0000000000000001),
    UINT64_C(0x0000000000000002),
    UINT64_C(0x000FFFFFFFFFFFFF),
    UINT64_C(0x0010000000000000),
    UINT64_C(0x0010000000000001),
    UINT64_C(0x3FDFFFFFFFFFFFFF),
    UINT64_C(0x3FE0000000000000),
    UINT64_C(0x3FE0000000000001),
    UINT64_C(0x3FEFFFFFFFFFFFFF),
    UINT64_C(0x3FF0000000000000),
    UINT64_C(0x3FF0000000000001),
    UINT64_C(0x3FFFFFFFFFFFFFFF),
    UINT64_C(0x4000000000000000),
    UINT64_C(0x4000000000000001),
    UINT64_C(0x7FEFFFFFFFFFFFFE),
    UINT64_C(0x7FEFFFFFFFFFFFFF),
    UINT64_C(0x7FF0000000000000),
};
static_assert(ARRAY_LENGTH(f64_ordered_values) % 2 == 0);

static const uint64_t f64_unordered_values[] = {
    UINT64_C(0xFFFFFFFFFFFFFFFF),
    UINT64_C(0xFFF8000000000000),
    UINT64_C(0xFFF7FFFFFFFFFFFF),
    UINT64_C(0xFFF4000000000000),
    UINT64_C(0xFFF0000000000001),

    UINT64_C(0x7FF0000000000001),
    UINT64_C(0x7FF4000000000000),
    UINT64_C(0x7FF7FFFFFFFFFFFF),
    UINT64_C(0x7FF8000000000000),
    UINT64_C(0x7FFFFFFFFFFFFFFF),
};
static_assert(ARRAY_LENGTH(f64_unordered_values) % 2 == 0);

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------

#define C(expr) if (!(expr)) { return __LINE__; }

#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

static inline uint32_t f32_to_u32(float x) {
    union {
        float flt;
        uint32_t bin;
    } conv;
    conv.flt = x;
    return conv.bin;
}

static inline uint64_t f64_to_u64(long double x) {
    union {
        long double flt;
        uint64_t bin;
    } conv;
    conv.flt = x;
    return conv.bin;
}

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

extern "C" {
uint8_t crt_fcmp(uint32_t LHS, uint32_t RHS);
uint8_t crt_fcmpo(uint32_t LHS, uint32_t RHS);
uint8_t crt_fcmpu(uint32_t LHS, uint32_t RHS);
uint8_t crt_dcmp(uint64_t LHS, uint64_t RHS);
uint8_t crt_dcmpo(uint64_t LHS, uint64_t RHS);
uint8_t crt_dcmpu(uint64_t LHS, uint64_t RHS);
}

static constexpr bool  EQ_O = true;
static constexpr bool NEQ_U = false;

static constexpr bool  LT_O = true;
static constexpr bool NLT_U = false;

static constexpr bool NGE_U = true;
static constexpr bool  GE_O = false;

static constexpr bool NLG_U = true;
static constexpr bool  LG_O = false;

static constexpr bool ORDER = true;
static constexpr bool UNORD = false;

static bool test_fcmp(
    uint32_t LHS, uint32_t RHS,
    bool truth_o_zero,
    bool truth_o_carry,
    bool truth_o_sign,
    bool truth_u_zero,
    bool truth_u_carry
) {
    uint8_t cmpc = crt_fcmp(LHS, RHS);
    uint8_t cmpo = crt_fcmpo(LHS, RHS);
    uint8_t cmpu = crt_fcmpu(LHS, RHS);
    bool ordered = (truth_u_carry == ORDER);
    bool truth_c_zero = truth_o_zero;
    bool truth_c_sign = truth_o_sign;
    bool cmpc_fail = (ordered && (
        (((cmpc & (1 << 6)) != 0) != truth_c_zero ) ||
        (((cmpc & (1 << 7)) != 0) != truth_c_sign )
    ));
    if (
        (((cmpo & (1 << 6)) != 0) != truth_o_zero ) ||
        (((cmpo & (1 << 0)) != 0) != truth_o_carry) ||
        (((cmpo & (1 << 7)) != 0) != truth_o_sign ) ||
        (((cmpu & (1 << 6)) != 0) != truth_u_zero ) ||
        (((cmpu & (1 << 0)) != 0) != truth_u_carry) ||
        cmpc_fail
    ) {
        test_printf(
            "LHS %08lX\nRHS %08lX\n"
            "OT %c%c-----%c !=\nOG %08b\n"
            "UT -%c-----%c !=\nUG %08b\n"
            "CT %c%c------ %c=\nCG %08b\n",
            LHS, RHS,
            truth_o_sign ? '1' : '0',
            truth_o_zero ? '1' : '0',
            truth_o_carry ? '1' : '0',
            cmpo,
            truth_u_zero ? '1' : '0',
            truth_u_carry ? '1' : '0',
            cmpu,
            !ordered ? '?' : (truth_c_sign ? '1' : '0'),
            !ordered ? '?' : (truth_c_zero ? '1' : '0'),
            !ordered ? '?' : '!',
            cmpc
        );
        return false;
    }
    return true;
}

static bool test_dcmp(
    uint64_t LHS, uint64_t RHS,
    bool truth_o_zero,
    bool truth_o_carry,
    bool truth_o_sign,
    bool truth_u_zero,
    bool truth_u_carry
) {
    uint8_t cmpc = crt_dcmp(LHS, RHS);
    uint8_t cmpo = crt_dcmpo(LHS, RHS);
    uint8_t cmpu = crt_dcmpu(LHS, RHS);
    bool ordered = (truth_u_carry == ORDER);
    bool truth_c_zero = truth_o_zero;
    bool truth_c_sign = truth_o_sign;
    bool cmpc_fail = (ordered && (
        (((cmpc & (1 << 6)) != 0) != truth_c_zero ) ||
        (((cmpc & (1 << 7)) != 0) != truth_c_sign )
    ));
    if (
        (((cmpo & (1 << 6)) != 0) != truth_o_zero ) ||
        (((cmpo & (1 << 0)) != 0) != truth_o_carry) ||
        (((cmpo & (1 << 7)) != 0) != truth_o_sign ) ||
        (((cmpu & (1 << 6)) != 0) != truth_u_zero ) ||
        (((cmpu & (1 << 0)) != 0) != truth_u_carry) ||
        cmpc_fail
    ) {
        test_printf(
            "LHS %016llX\nRHS %016llX\n"
            "OT %c%c-----%c !=\nOG %08b\n"
            "UT -%c-----%c !=\nUG %08b\n"
            "CT %c%c------ %c=\nCG %08b\n",
            LHS, RHS,
            truth_o_sign ? '1' : '0',
            truth_o_zero ? '1' : '0',
            truth_o_carry ? '1' : '0',
            cmpo,
            truth_u_zero ? '1' : '0',
            truth_u_carry ? '1' : '0',
            cmpu,
            !ordered ? '?' : (truth_c_sign ? '1' : '0'),
            !ordered ? '?' : (truth_c_zero ? '1' : '0'),
            !ordered ? '?' : '!',
            cmpc
        );
        return false;
    }
    return true;
}

static bool test_fcmp(
    float LHS, float RHS,
    bool truth_o_zero,
    bool truth_o_carry,
    bool truth_o_sign,
    bool truth_u_zero,
    bool truth_u_carry
) {
    return test_fcmp(
        f32_to_u32(LHS), f32_to_u32(RHS),
        truth_o_zero,
        truth_o_carry,
        truth_o_sign,
        truth_u_zero,
        truth_u_carry
    );
}

static bool test_dcmp(
    long double LHS, long double RHS,
    bool truth_o_zero,
    bool truth_o_carry,
    bool truth_o_sign,
    bool truth_u_zero,
    bool truth_u_carry
) {
    return test_dcmp(
        f64_to_u64(LHS), f64_to_u64(RHS),
        truth_o_zero,
        truth_o_carry,
        truth_o_sign,
        truth_u_zero,
        truth_u_carry
    );
}

int fcmp_basic_test(void) {
    // test signed zero
    C(test_fcmp(+0.0f, +0.0f, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
    C(test_fcmp(-0.0f, -0.0f, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
    C(test_fcmp(+0.0f, -0.0f, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
    C(test_fcmp(-0.0f, +0.0f, EQ_O, NLT_U, GE_O, NLG_U, ORDER));

    // test signed finite value
    C(test_fcmp(+1.0f, +1.0f,  EQ_O, NLT_U,  GE_O, NLG_U, ORDER));
    C(test_fcmp(-1.0f, -1.0f,  EQ_O, NLT_U,  GE_O, NLG_U, ORDER));
    C(test_fcmp(+1.0f, -1.0f, NEQ_U, NLT_U,  GE_O,  LG_O, ORDER));
    C(test_fcmp(-1.0f, +1.0f, NEQ_U,  LT_O, NGE_U,  LG_O, ORDER));

    // test zero and one
    C(test_fcmp(+0.0f, +1.0f, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));
    C(test_fcmp(-0.0f, +1.0f, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));
    C(test_fcmp(+0.0f, -1.0f, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_fcmp(-0.0f, -1.0f, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_fcmp(+1.0f, +0.0f, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_fcmp(+1.0f, -0.0f, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_fcmp(-1.0f, +0.0f, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));
    C(test_fcmp(-1.0f, -0.0f, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));

    return 0;
}

int fcmp_ordered(void) {
    for (size_t iy = 0; iy < ARRAY_LENGTH(f32_ordered_values); iy++) {
        uint32_t y = f32_ordered_values[iy];
        for (size_t ix = 0; ix < ARRAY_LENGTH(f32_ordered_values); ix++) {
            uint32_t x = f32_ordered_values[ix];
            // this loop tests both (x, y) and (y, x) along with (x, x)

            // test if both are signed zeros
            if ((x << 1) == 0 && (y << 1) == 0) {
                C(test_fcmp(x, y, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
                continue;
            }
            if (ix < iy) {
                C(test_fcmp(x, y, NEQ_U, LT_O, NGE_U, LG_O, ORDER));
                continue;
            }
            if (ix > iy) {
                C(test_fcmp(x, y, NEQ_U, NLT_U, GE_O, LG_O, ORDER));
                continue;
            }
            // ix == iy
            C(test_fcmp(x, y, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
        }
    }

    return 0;
}

int fcmp_nan(void) {
    // compare NaN to NaN
    for (size_t iy = 0; iy < ARRAY_LENGTH(f32_unordered_values); iy++) {
        uint32_t y = f32_unordered_values[iy];
        for (size_t ix = 0; ix < ARRAY_LENGTH(f32_unordered_values); ix++) {
            uint32_t x = f32_unordered_values[ix];
            // this loop tests both (x, y) and (y, x)
            C(test_fcmp(x, y, NEQ_U, NLT_U, NGE_U, NLG_U, UNORD));
        }
    }

    // unordered comparison
    for (size_t n = 0; n < ARRAY_LENGTH(f32_unordered_values); n++) {
        uint32_t nan_value = f32_unordered_values[n];
        for (size_t i = 0; i < ARRAY_LENGTH(f32_ordered_values); i++) {
            uint32_t ordered_value = f32_ordered_values[i];
            C(test_fcmp(ordered_value, nan_value, NEQ_U, NLT_U, NGE_U, NLG_U, UNORD));
            C(test_fcmp(nan_value, ordered_value, NEQ_U, NLT_U, NGE_U, NLG_U, UNORD));
        }
    }

    return 0;
}

int dcmp_basic_test(void) {
    // test signed zero
    C(test_dcmp(+0.0L, +0.0L, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
    C(test_dcmp(-0.0L, -0.0L, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
    C(test_dcmp(+0.0L, -0.0L, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
    C(test_dcmp(-0.0L, +0.0L, EQ_O, NLT_U, GE_O, NLG_U, ORDER));

    // test signed finite value
    C(test_dcmp(+1.0L, +1.0L,  EQ_O, NLT_U,  GE_O, NLG_U, ORDER));
    C(test_dcmp(-1.0L, -1.0L,  EQ_O, NLT_U,  GE_O, NLG_U, ORDER));
    C(test_dcmp(+1.0L, -1.0L, NEQ_U, NLT_U,  GE_O,  LG_O, ORDER));
    C(test_dcmp(-1.0L, +1.0L, NEQ_U,  LT_O, NGE_U,  LG_O, ORDER));

    // test zero and one
    C(test_dcmp(+0.0L, +1.0L, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));
    C(test_dcmp(-0.0L, +1.0L, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));
    C(test_dcmp(+0.0L, -1.0L, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_dcmp(-0.0L, -1.0L, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_dcmp(+1.0L, +0.0L, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_dcmp(+1.0L, -0.0L, NEQ_U, NLT_U,  GE_O, LG_O, ORDER));
    C(test_dcmp(-1.0L, +0.0L, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));
    C(test_dcmp(-1.0L, -0.0L, NEQ_U,  LT_O, NGE_U, LG_O, ORDER));

    return 0;
}

int dcmp_ordered(void) {
    for (size_t iy = 0; iy < ARRAY_LENGTH(f64_ordered_values); iy++) {
        uint64_t y = f64_ordered_values[iy];
        for (size_t ix = 0; ix < ARRAY_LENGTH(f64_ordered_values); ix++) {
            uint64_t x = f64_ordered_values[ix];
            // this loop tests both (x, y) and (y, x) along with (x, x)

            // test if both are signed zeros
            if ((x << 1) == 0 && (y << 1) == 0) {
                C(test_dcmp(x, y, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
                continue;
            }
            if (ix < iy) {
                C(test_dcmp(x, y, NEQ_U, LT_O, NGE_U, LG_O, ORDER));
                continue;
            }
            if (ix > iy) {
                C(test_dcmp(x, y, NEQ_U, NLT_U, GE_O, LG_O, ORDER));
                continue;
            }
            // ix == iy
            C(test_dcmp(x, y, EQ_O, NLT_U, GE_O, NLG_U, ORDER));
        }
    }

    return 0;
}

int dcmp_nan(void) {
    // compare NaN to NaN
    for (size_t iy = 0; iy < ARRAY_LENGTH(f64_unordered_values); iy++) {
        uint64_t y = f64_unordered_values[iy];
        for (size_t ix = 0; ix < ARRAY_LENGTH(f64_unordered_values); ix++) {
            uint64_t x = f64_unordered_values[ix];
            // this loop tests both (x, y) and (y, x)
            C(test_dcmp(x, y, NEQ_U, NLT_U, NGE_U, NLG_U, UNORD));
        }
    }

    // unordered comparison
    for (size_t n = 0; n < ARRAY_LENGTH(f64_unordered_values); n++) {
        uint64_t nan_value = f64_unordered_values[n];
        for (size_t i = 0; i < ARRAY_LENGTH(f64_ordered_values); i++) {
            uint64_t ordered_value = f64_ordered_values[i];
            C(test_dcmp(ordered_value, nan_value, NEQ_U, NLT_U, NGE_U, NLG_U, UNORD));
            C(test_dcmp(nan_value, ordered_value, NEQ_U, NLT_U, NGE_U, NLG_U, UNORD));
        }
    }

    return 0;
}

int run_tests(void) {
    int ret = 0;

    TEST(fcmp_basic_test());
    TEST(fcmp_ordered());
    TEST(fcmp_nan());

    TEST(dcmp_basic_test());
    TEST(dcmp_ordered());
    TEST(dcmp_nan());

    /* passed all */
    return ret;
}

extern "C" int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608\n")];
        boot_sprintf(buf, "Failed test L%d\n", failed_test);
        fputs(buf, stdout);
    } else {
        fputs("All tests passed", stdout);
    }

    while (!os_GetCSC());

    return 0;
}
