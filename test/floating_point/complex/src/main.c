#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include <complex.h>

typedef union CF32_pun {
    float complex c;
    float f[2];
} CF32_pun;

static_assert(sizeof(CF32_pun) == sizeof(float) * 2, "sizeof(float _Complex) has changed");

typedef union CFD2_pun {
    double complex c;
    double f[2];
} CD32_pun;

static_assert(sizeof(CD32_pun) == sizeof(double) * 2, "sizeof(double _Complex) has changed");


typedef union CF64_pun {
    long double complex c;
    long double f[2];
} CF64_pun;

static_assert(sizeof(CF64_pun) == sizeof(long double) * 2, "sizeof(long double _Complex) has changed");

#define CF32_RE (1.23f)
#define CF32_IM (-4.56f)

#define CD32_RE (1.23)
#define CD32_IM (-4.56)

#define CF64_RE (1.23L)
#define CF64_IM (-4.56L)

double _Complex T_CMPLX(double x, double y);
float _Complex T_CMPLXF(float x, float y);
long double _Complex T_CMPLXL(long double x, long double y);

double T_creal(double _Complex);
float T_crealf(float _Complex);
long double T_creall(long double _Complex);

double T_cimag(double _Complex);
float T_cimagf(float _Complex);
long double T_cimagl(long double _Complex);

double _Complex T_conj(double _Complex);
float _Complex T_conjf(float _Complex);
long double _Complex T_conjl(long double _Complex);

static size_t run_test(void) {
    /* test float _Complex without any Clang chicanery */
    {
        CF32_pun c32;
        c32.c = T_CMPLXF(CF32_RE, CF32_IM);
        if (c32.f[0] != CF32_RE) { return __LINE__; }
        if (c32.f[1] != CF32_IM) { return __LINE__; }
        if (T_crealf(c32.c) != CF32_RE) { return __LINE__; }
        if (T_cimagf(c32.c) != CF32_IM) { return __LINE__; }
        c32.c = conjf(c32.c);
        if (c32.f[0] != CF32_RE) { return __LINE__; }
        if (c32.f[1] != -CF32_IM) { return __LINE__; }
        if (T_crealf(c32.c) != CF32_RE) { return __LINE__; }
        if (T_cimagf(c32.c) != -CF32_IM) { return __LINE__; }
        c32.c = T_conjf(T_CMPLXF(T_cimagf(c32.c), T_crealf(c32.c)));
        if (T_crealf(c32.c) != -CF32_IM) { return __LINE__; }
        if (T_cimagf(c32.c) != -CF32_RE) { return __LINE__; }
    }

    /* test double _Complex without any Clang chicanery */
    {
        CD32_pun c32;
        c32.c = T_CMPLX(CD32_RE, CD32_IM);
        if (c32.f[0] != CD32_RE) { return __LINE__; }
        if (c32.f[1] != CD32_IM) { return __LINE__; }
        if (T_creal(c32.c) != CD32_RE) { return __LINE__; }
        if (T_cimag(c32.c) != CD32_IM) { return __LINE__; }
        c32.c = conj(c32.c);
        if (c32.f[0] != CD32_RE) { return __LINE__; }
        if (c32.f[1] != -CD32_IM) { return __LINE__; }
        if (T_creal(c32.c) != CD32_RE) { return __LINE__; }
        if (T_cimag(c32.c) != -CD32_IM) { return __LINE__; }
        c32.c = T_conj(T_CMPLX(T_cimag(c32.c), T_creal(c32.c)));
        if (T_creal(c32.c) != -CD32_IM) { return __LINE__; }
        if (T_cimag(c32.c) != -CD32_RE) { return __LINE__; }
    }

    /* test long double _Complex without any Clang chicanery */
    {
        CF64_pun c64;
        c64.c = T_CMPLXL(CF64_RE, CF64_IM);
        if (c64.f[0] != CF64_RE) { return __LINE__; }
        if (c64.f[1] != CF64_IM) { return __LINE__; }
        if (T_creall(c64.c) != CF64_RE) { return __LINE__; }
        if (T_cimagl(c64.c) != CF64_IM) { return __LINE__; }
        c64.c = T_conjl(c64.c);
        if (c64.f[0] != CF64_RE) { return __LINE__; }
        if (c64.f[1] != -CF64_IM) { return __LINE__; }
        if (T_creall(c64.c) != CF64_RE) { return __LINE__; }
        if (T_cimagl(c64.c) != -CF64_IM) { return __LINE__; }
        c64.c = T_conjl(T_CMPLXL(T_cimagl(c64.c), T_creall(c64.c)));
        if (T_creall(c64.c) != -CF64_IM) { return __LINE__; }
        if (T_cimagl(c64.c) != -CF64_RE) { return __LINE__; }
    }

    /* special zero test for TiOS floats (-0.0f != +0.0f) */
    {
        CF32_pun c32;
        c32.c = T_CMPLXF(0.0f, 0.0f);
        if (c32.f[0] != 0.0f) { return __LINE__; }
        if (c32.f[1] != 0.0f) { return __LINE__; }
        if (T_crealf(c32.c) != 0.0f) { return __LINE__; }
        if (T_cimagf(c32.c) != 0.0f) { return __LINE__; }
        c32.c = conjf(c32.c); /* ensure that fneg is skipped for +0.0f */
        if (c32.f[0] != 0.0f) { return __LINE__; }
        if (c32.f[1] != 0.0f) { return __LINE__; } /* fails if c32.f[1] == -0.0f */
        if (T_crealf(c32.c) != 0.0f) { return __LINE__; }
        if (T_cimagf(c32.c) != 0.0f) { return __LINE__; }
        c32.c = T_conjf(T_CMPLXF(T_cimagf(c32.c), T_crealf(c32.c)));
        if (T_crealf(c32.c) != 0.0f) { return __LINE__; }
        if (T_cimagf(c32.c) != 0.0f) { return __LINE__; }
    }

    /* test if Clang handles float _Complex correctly */
    {
        CF32_pun c32;
        c32.c = CMPLXF(CF32_RE, CF32_IM);
        if (c32.f[0] != CF32_RE) { return __LINE__; }
        if (c32.f[1] != CF32_IM) { return __LINE__; }
        if (crealf(c32.c) != CF32_RE) { return __LINE__; }
        if (cimagf(c32.c) != CF32_IM) { return __LINE__; }
        c32.c = conjf(c32.c);
        if (c32.f[0] != CF32_RE) { return __LINE__; }
        if (c32.f[1] != -CF32_IM) { return __LINE__; }
        if (crealf(c32.c) != CF32_RE) { return __LINE__; }
        if (cimagf(c32.c) != -CF32_IM) { return __LINE__; }
        c32.c = conjf(CMPLXF(cimagf(c32.c), crealf(c32.c)));
        if (crealf(c32.c) != -CF32_IM) { return __LINE__; }
        if (cimagf(c32.c) != -CF32_RE) { return __LINE__; }
    }

    /* test if Clang handles double _Complex correctly */
    {
        CD32_pun c32;
        c32.c = CMPLX(CD32_RE, CD32_IM);
        if (c32.f[0] != CD32_RE) { return __LINE__; }
        if (c32.f[1] != CD32_IM) { return __LINE__; }
        if (creal(c32.c) != CD32_RE) { return __LINE__; }
        if (cimag(c32.c) != CD32_IM) { return __LINE__; }
        c32.c = conj(c32.c);
        if (c32.f[0] != CD32_RE) { return __LINE__; }
        if (c32.f[1] != -CD32_IM) { return __LINE__; }
        if (creal(c32.c) != CD32_RE) { return __LINE__; }
        if (cimag(c32.c) != -CD32_IM) { return __LINE__; }
        c32.c = conj(CMPLX(cimag(c32.c), creal(c32.c)));
        if (creal(c32.c) != -CD32_IM) { return __LINE__; }
        if (cimag(c32.c) != -CD32_RE) { return __LINE__; }
    }

    /* test if Clang handles long double _Complex correctly */
    {
        CF64_pun c64;
        c64.c = CMPLXL(CF64_RE, CF64_IM);
        if (c64.f[0] != CF64_RE) { return __LINE__; }
        if (c64.f[1] != CF64_IM) { return __LINE__; }
        if (creall(c64.c) != CF64_RE) { return __LINE__; }
        if (cimagl(c64.c) != CF64_IM) { return __LINE__; }
        c64.c = conjl(c64.c);
        if (c64.f[0] != CF64_RE) { return __LINE__; }
        if (c64.f[1] != -CF64_IM) { return __LINE__; }
        if (creall(c64.c) != CF64_RE) { return __LINE__; }
        if (cimagl(c64.c) != -CF64_IM) { return __LINE__; }
        c64.c = conjl(CMPLXL(cimagl(c64.c), creall(c64.c)));
        if (creall(c64.c) != -CF64_IM) { return __LINE__; }
        if (cimagl(c64.c) != -CF64_RE) { return __LINE__; }
    }

    /* passed all */
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    size_t fail_index = run_test();
    if (fail_index == SIZE_MAX) {
        printf("All tests passed");
    } else {
        printf("Failed test: L%zu\n", fail_index);
    }

    while (!os_GetCSC());

    return 0;
}
