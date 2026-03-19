#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdio.h>
#include <stdlib.h>
#include <ti/sprintf.h>

/**
 * If the algorithm/output for random/srandom or rand/srand changes, you can
 * set GENERATE_TESTS to 1, and copy and paste the new lookup table values.
 */

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

/**
 * define to 0 or 1
 * 0: run test cases
 * 1: regenerate test cases
 */
#define GENERATE_TESTS 0

#define TEST_COUNT (16)

//------------------------------------------------------------------------------
// Test data
//------------------------------------------------------------------------------

const unsigned long random_0[] = {
    0x03050704,
    0x54710D87,
    0xA5BD8B69,
    0xA9F363AF,
    0xD886A9DD,
    0x7E80E185,
    0xBEE50F75,
    0xE084D90B,
    0x1ABFA826,
    0xB374C8E7,
    0x38383D5E,
    0xC4A1AACA,
    0xCB856CF1,
    0x0891BB41,
    0xA5D37384,
    0xC59A3F68,
};

const unsigned long random_X[] = {
    0x03050704,
    0x3A2805E1,
    0x1825044C,
    0x394804A2,
    0x1F5D0344,
    0x08800A73,
    0x5A1D0FAF,
    0x26680D98,
    0x49AD0ED1,
    0x3E280E2C,
    0x4E4D0B5A,
    0x17A01302,
    0x8EB51683,
    0x39B0165A,
    0x8A651905,
    0x4150221B,
};

const int rand_0[] = {
    0x050704,
    0x710D87,
    0x3D8B69,
    0x7363AF,
    0x06A9DD,
    0x00E184,
    0x650F74,
    0x04D90B,
    0x3FA825,
    0x74C8E6,
    0x383D5D,
    0x21AACA,
    0x056CF1,
    0x11BB40,
    0x537384,
    0x1A3F68,
};

const int rand_X[] = {
    0x050704,
    0x2805C9,
    0x6503BE,
    0x180A56,
    0x2D0FC7,
    0x180B3B,
    0x4510F9,
    0x1013C9,
    0x5D163F,
    0x281AB6,
    0x1D1B1E,
    0x701CDD,
    0x1D22ED,
    0x78295A,
    0x2D3213,
    0x38359A,
};

//------------------------------------------------------------------------------
// Code
//------------------------------------------------------------------------------

#ifndef GENERATE_TESTS
#error "GENERATE_TESTS must be 0 or 1"
#endif /* GENERATE_TESTS */

#if GENERATE_TESTS

void outchar(char ch) {
    *(char*)0xFB0000 = ch;
    *(char*)0xFB0001 = '\0';
}
#define gen_printf printf
#define C(...)

#else /* GENERATE_TESTS */

#define gen_printf(...)
#define C(expr) if (!(expr)) { return __LINE__; }

#endif /* GENERATE_TESTS */

int run_tests() {
    gen_printf("const unsigned long random_0[] = {\n");
    srandom(0);
    for (int i = 0; i < TEST_COUNT; i++) {
        unsigned long value = random();
        C(value == random_0[i]);
        gen_printf("    0x%08lX,\n", value);
    }
    gen_printf("};\n\n");

    gen_printf("const unsigned long random_X[] = {\n");
    srandom(0);
    for (int i = 0; i < TEST_COUNT; i++) {
        unsigned long value = random();
        C(value == random_X[i]);
        srandom(value);
        gen_printf("    0x%08lX,\n", value);
    }
    gen_printf("};\n\n");

    gen_printf("const int rand_0[] = {\n");
    srand(0);
    for (int i = 0; i < TEST_COUNT; i++) {
        int value = rand();
        C(value == rand_0[i]);
        gen_printf("    0x%06X,\n", value);
    }
    gen_printf("};\n\n");

    gen_printf("const int rand_X[] = {\n");
    srand(0);
    for (int i = 0; i < TEST_COUNT; i++) {
        int value = rand();
        C(value == rand_X[i]);
        srand(value);
        gen_printf("    0x%06X,\n", value);
    }
    gen_printf("};\n\n");
    return 0;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }

#if GENERATE_TESTS
    os_PutStrLine("check debug console");
#endif /* GENERATE_TESTS */

    while (!os_GetCSC());

    return 0;
}
