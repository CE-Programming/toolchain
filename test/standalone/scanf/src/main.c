#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ti/sprintf.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 1

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

#define C(expr) if (!(expr)) { return __LINE__; }
#define B(expr) if (!(expr)) { return false; }

#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

bool double_equals(double x, double y, double absolute_difference) {
    return (fabs(x - y) <= absolute_difference);
}

bool strcmp_exact(const char *x, const char *y) {
    if (strlen(x) != strlen(y)) {
        return false;
    }
    if (strcmp(x, y) != 0) {
        return false;
    }
    return true;
}

int stdc_test(void) {
    const char* input_1 = (
        "2 quarts of oil\n"\
        "-12.8degrees Celsius\n"\
    );
    const char* input_2 = (
        "lots of luck\n"\
        "10.0LBS of\n"\
        "dirt\n"\
        /* "100ergs of energy\n"\ */ /* strtod doesn't handle this error currently */
        "f100ergs of energy\n"
    );

    struct {
        float quant;
        char unit[21];
        char item[21];
    } data[2];
    memset(data, '\0', sizeof(data));
    int count;

    count = sscanf(input_1,
        "%f%20s of %20s%*[^\n]"\
        "%f%20s of %20s%*[^\n]",
        &data[0].quant, data[0].unit, data[0].item,
        &data[1].quant, data[1].unit, data[1].item
    );
    C(count == 5);
    C(double_equals(data[0].quant, 2.0, 1.0e-5));
    C(strcmp_exact(data[0].unit, "quarts"));
    C(strcmp_exact(data[0].item, "oil"));
    C(double_equals(data[1].quant, -12.8, 1.0e-5));
    C(strcmp_exact(data[1].unit, "degrees"));
    C(*data[0].item != 'C'); /* test that "Celius" was not written at all */

    count = sscanf(input_2,
        "%f%20s of %20s%*[^\n]"\
        "%f%20s of %20s%*[^\n]",
        &data[0].quant, data[0].unit, data[0].item,
        &data[1].quant, data[1].unit, data[1].item
    );
    C(count == 0);

    count = sscanf(strchr(input_2, '\n'),
        "%*[^!@#\n$%d]"\
        "%f%20s of %20s%*[^\n]"\
        "%f%20s of %20s%*[^\n]",
        &data[0].quant, data[0].unit, data[0].item,
        &data[1].quant, data[1].unit, data[1].item
    );
    C(count == 3);
    C(double_equals(data[0].quant, 10.0, 1.0e-5));
    C(strcmp_exact(data[0].unit, "LBS"));
    C(strcmp_exact(data[0].item, "dirt"));

    int d1 = 0, d2 = 0xC0FFEE, n1 = 0, n2 = 0xA5A500;
    int c = sscanf("123", "%d%n%hhn%d", &d1, &n1, (char*)((void*)&n2), &d2);
    C(c == 1);
    C(d1 == 123);
    C(n1 == 3);
    C(n2 == (int)(0xA5A500 | 3));
    C(d2 == (int)0xC0FFEE);

    long long i3 = 0xFEEDFACECAFEBEEF;
    int n3 = sscanf("foo %bar -42", "foo%%bar%lld", &i3);
    C(i3 == -42);
    C(n3 == 1);

    return 0;
}

int basic_test(void) {
    int i, j;
    float x, y;
    char str1[10] = "ZZZZZZZZZ", str2[4] = "FFF";

    char input[] = "25 54.32E-1 Thompson 56789 0123 40";
    /**
     * https://en.cppreference.com/w/c/io/fscanf
     * parse as follows:
     * %d: an integer
     * %f: a floating-point value
     * %9s: a string of at most 9 non-whitespace characters
     * %2d: two-digit integer (digits 5 and 6)
     * %f:  a floating-point value (digits 7, 8, 9)
     * %*d: an integer which isn't stored anywhere
     * ' ': all consecutive whitespace
     * %3[0123456789]: a string of at most 3 decimal digits (digits 5 and 6)
     */
    int ret = sscanf(
        input, "%d%f%9s%2d%f%*d %3[0123456789]",
        &i, &x, str1, &j, &y, str2
    );

    C(i == 25);
    C(double_equals(x, 5.432000, 1.0e-5));
    C(strcmp_exact(str1, "Thompson"));
    C(j == 56);
    C(y == 789.000000);
    C(strcmp_exact(str2, "40"));
    C(ret == 6);

    return 0;
}

/**
 * @brief https://stackoverflow.com/questions/9537072/properly-using-sscanf
 */
int stackoverflow_test(void) {
    const char *data[] =
    {
        "text1 char2 , word3",
        "text1 char2 ,word3",
        "text1 char2, word3",
        "text1 char2,word3",
        "text1 char2       ,       word3",
    };
    char text1[20]; text1[0] = '\0';
    char char2[32]; char2[0] = '\0';
    char word3[48]; word3[0] = '\0';
    for (size_t i = 0; i < ARRAY_LENGTH(data); i++) {
        int n = sscanf(data[i], "%19s %31[^, ] %*[,]%47s", text1, char2, word3);
        C(n == 3);
        C(strcmp_exact("text1", text1));
        C(strcmp_exact("char2", char2));
        C(strcmp_exact("word3", word3));
    }
    return 0;
}

/**
 * @brief tests if strto(f/d/ld) sets endptr correctly
 */
bool strtod_test(void);

int other_test(void) {
    const char* text = "abc]]]def]ghi^^]]^^^jklm^^";
    char buf_1[10] = {'\0'};
    char buf_2[10] = {'\0'};
    char buf_3[10] = {'\0','\0','\0', ';', '\0'};
    char buf_4[10] = {'\0'};
    char buf_5[10] = {'\0'};
    char buf_6[10] = {'\0'};
    char buf_7[10] = {'\0'};

    ptrdiff_t end_1 = 0xE0E0E0;
    intmax_t end_2 = UINTMAX_C(0xD0D0D0D0D0D0D0D0);
    int count = sscanf(text,
        "%9[^]]%1[]]%*[]]%3c%9[^^]%9[^]^]%3[]^]%*4[]^]%tn%4[^]^]%jn",
        buf_1, buf_2, buf_3, buf_4, buf_5, buf_6, &end_1, buf_7, &end_2
    );
    C(count == 7);
    C(end_1 == 20);
    C(end_2 == 24);
    C(strcmp_exact(buf_1, "abc"));
    C(strcmp_exact(buf_2, "]"));
    C(memcmp(buf_3, "def;", 4) == 0);
    C(strcmp_exact(buf_4, "]ghi"));
    C(*buf_5 == '\0');
    C(strcmp_exact(buf_6, "^^]"));
    C(strcmp_exact(buf_7, "jklm"));
    return 0;
}

int run_tests(void) {
    int ret = 0;

    C(strtod_test());
    TEST(basic_test());
    TEST(stdc_test());
    TEST(stackoverflow_test());
    TEST(other_test());

    return ret;
}

int main(void) {
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
