#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define MLA(x, y, z) fmal(x, y, z)
#define mla(x, y, z) fmal(x, y, z)

#define C2V(x) (x)

#define POLY2(x, c1, c0) MLA(x, C2V(c1), C2V(c0))
#define POLY3(x, x2, c2, c1, c0) MLA(x2, C2V(c2), MLA(x, C2V(c1), C2V(c0)))
#define POLY4(x, x2, c3, c2, c1, c0) MLA(x2, MLA(x, C2V(c3), C2V(c2)), MLA(x, C2V(c1), C2V(c0)))
#define POLY5(x, x2, x4, c4, c3, c2, c1, c0) MLA(x4, C2V(c4), POLY4(x, x2, c3, c2, c1, c0))
#define POLY6(x, x2, x4, c5, c4, c3, c2, c1, c0) MLA(x4, POLY2(x, c5, c4), POLY4(x, x2, c3, c2, c1, c0))
#define POLY7(x, x2, x4, c6, c5, c4, c3, c2, c1, c0) MLA(x4, POLY3(x, x2, c6, c5, c4), POLY4(x, x2, c3, c2, c1, c0))
#define POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0) MLA(x4, POLY4(x, x2, c7, c6, c5, c4), POLY4(x, x2, c3, c2, c1, c0))
#define POLY9(x, x2, x4, x8, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, C2V(c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY10(x, x2, x4, x8, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY2(x, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY11(x, x2, x4, x8, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY3(x, x2, ca, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY12(x, x2, x4, x8, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY4(x, x2, cb, ca, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY13(x, x2, x4, x8, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY5(x, x2, x4, cc, cb, ca, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY14(x, x2, x4, x8, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY6(x, x2, x4, cd, cc, cb, ca, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY15(x, x2, x4, x8, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY7(x, x2, x4, ce, cd, cc, cb, ca, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY16(x, x2, x4, x8, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x8, POLY8(x, x2, x4, cf, ce, cd, cc, cb, ca, c9, c8), POLY8(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY17(x, x2, x4, x8, x16, d0, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x16, C2V(d0), POLY16(x, x2, x4, x8, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY18(x, x2, x4, x8, x16, d1, d0, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x16, POLY2(x, d1, d0), POLY16(x, x2, x4, x8, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY19(x, x2, x4, x8, x16, d2, d1, d0, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x16, POLY3(x, x2, d2, d1, d0), POLY16(x, x2, x4, x8, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY20(x, x2, x4, x8, x16, d3, d2, d1, d0, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x16, POLY4(x, x2, d3, d2, d1, d0), POLY16(x, x2, x4, x8, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0))
#define POLY21(x, x2, x4, x8, x16, d4, d3, d2, d1, d0, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0)\
    MLA(x16, POLY5(x, x2, x4, d4, d3, d2, d1, d0), POLY16(x, x2, x4, x8, cf, ce, cd, cc, cb, ca, c9, c8, c7, c6, c5, c4, c3, c2, c1, c0))

//   Copyright Naoki Shibata and contributors 2010 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/**
 * https://github.com/shibatch/sleef/blob/master/src/libm/sleefdp.c
 * 2025-JAN-28
 */
long double sleef_xatan(long double s) {
    long double t, u;
    int q = 0;

    if (signbit(s)) { s = fabsl(s); q = 2; }
    if (s > 1.0L) { s = 1.0L / s; q |= 1; }

    t = s * s;

    long double t2 = t * t, t4 = t2 * t2, t8 = t4 * t4, t16 = t8 * t8;
    u = POLY19(t, t2, t4, t8, t16,
            -1.88796008463073496563746e-05L,
            0.000209850076645816976906797L,
            -0.00110611831486672482563471L,
            0.00370026744188713119232403L,
            -0.00889896195887655491740809L,
            0.016599329773529201970117L,
            -0.0254517624932312641616861L,
            0.0337852580001353069993897L,
            -0.0407629191276836500001934L,
            0.0466667150077840625632675L,
            -0.0523674852303482457616113L,
            0.0587666392926673580854313L,
            -0.0666573579361080525984562L,
            0.0769219538311769618355029L,
            -0.090908995008245008229153L,
            0.111111105648261418443745L,
            -0.14285714266771329383765L,
            0.199999999996591265594148L,
            -0.333333333333311110369124L);

    t = s + s * (t * u);

    if ((q & 1) != 0) { t = 1.570796326794896557998982L - t; }
    if ((q & 2) != 0) { t = -t; }

    return t;
}

int test_func(void) {
    static const long double input[] = {
        /*  0 */ -0.5L,
        /*  1 */ -0.0L,
        /*  2 */ 0.0L,
        /*  3 */ LDBL_TRUE_MIN,
        /*  4 */ LDBL_MIN,
        /*  5 */ LDBL_MAX,
        /*  6 */ 0.5L,
        /*  7 */ 1.0L - LDBL_EPSILON,
        /*  8 */ 1.0L,
        /*  9 */ 1.0L + LDBL_EPSILON,
        /* 10 */ 1.75L,
        /* 11 */ 3.015625L,
        /* 12 */ 11.0L,
        /* 13 */ 2.7182818284590452353602874713527L,
        /* 14 */ 3.1415926535897932384626433832795L,
        /* 15 */ 0.69314718055994530941723212145818L,
        /* 16 */ 1618.1779919126535016686912254836L,
        /* 17 */ 3814279.1047602205922092195940982L
    };
    #if 0
    /* correctly rounded from arbitrary precision */
    static const long double truth[] = {
        /*  0 */ -0.46364760900080611621425623146121L,
        /*  1 */ -0.0L,
        /*  2 */ 0.0L,
        /*  3 */ 4.9406564584124654417656879286822e-324L,
        /*  4 */ 2.2250738585072013830902327173324e-308L,
        /*  5 */ 1.5707963267948966192313216916398L,
        /*  6 */ 0.46364760900080611621425623146121L,
        /*  7 */ 0.78539816339744819859335838330421L,
        /*  8 */ 0.78539816339744830961566084581988L,
        /*  9 */ 0.78539816339744842063796330833552L,
        /* 10 */ 1.0516502125483736674598673120863L,
        /* 11 */ 1.2506009810977492475077687103988L,
        /* 12 */ 1.4801364395941515057329350163313L,
        /* 13 */ 1.2182829050172776217604617689158L,
        /* 14 */ 1.2626272556789116834443220836057L,
        /* 15 */ 0.60611193473285500238598826957669L,
        /* 16 */ 1.5701783478842338275008416704873L,
        /* 17 */ 1.5707960646221576731020209182045L
    };
    #endif
    static const uint64_t expected_u64[] = {
        /*  0 */ UINT64_C(0xBFDDAC670561BB50),
        /*  1 */ UINT64_C(0x8000000000000000), /* negative zero */
        /*  2 */ UINT64_C(0x0000000000000000), /* positive zero */
        /*  3 */ UINT64_C(0x0000000000000001), /* LDBL_TRUE_MIN */
        /*  4 */ UINT64_C(0x0010000000000000), /* LDBL_MIN */
        /*  5 */ UINT64_C(0x3FF921FB54442D18),
        /*  6 */ UINT64_C(0x3FDDAC670561BB50),
        /*  7 */ UINT64_C(0x3FE921FB54442D18),
        /*  8 */ UINT64_C(0x3FE921FB54442D18),
        /*  9 */ UINT64_C(0x3FE921FB54442D18),
        /* 10 */ UINT64_C(0x3FF0D38F2C5BA09E),
        /* 11 */ UINT64_C(0x3FF402762CA290C8),
        /* 12 */ UINT64_C(0x3FF7AEA38C1ACBD1),
        /* 13 */ UINT64_C(0x3FF37E1637253388),
        /* 14 */ UINT64_C(0x3FF433B8A322DDD2),
        /* 15 */ UINT64_C(0x3FE36544DB2C92A0),
        /* 16 */ UINT64_C(0x3FF91F7354D0CD30),
        /* 17 */ UINT64_C(0x3FF921FB0DE3CD7F)
    };
    const long double *expected_f64 = ((const long double*)((const void*)expected_u64));

    for (size_t i = 0; i < sizeof(input) / sizeof(long double); i++) {
        if (sleef_xatan(input[i]) != *expected_f64) {
            return i;
        }
        expected_f64++;
    }
    return -1; // Passed all tests
}

int main(void) {
    os_ClrHome();

    int ret = test_func();
    if (ret == -1) {
        printf("All tests passed");
    } else {
        printf("Failed test %d", ret);
    }

    while (!os_GetCSC());

    return 0;
}
