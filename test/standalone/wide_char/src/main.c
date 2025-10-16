#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>
#include <wchar.h>

#if 0
#define test_printf printf
#else
#define test_printf(...)
#endif

#define C(expr) if (!(expr)) { return __LINE__; }
#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#define SINK (wchar_t*)0xE40000

#define ARRAY_LEN(x) (sizeof((x)) / sizeof((x)[0]))

extern wchar_t * const PTR_000000;
extern wchar_t * const PTR_FFFFFF;

#if 0

int       T_wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n) __NOEXCEPT __attribute__((__pure__));
wchar_t * T_wmemchr(const wchar_t *ptr, int ch, size_t count) __NOEXCEPT __attribute__((__pure__));
size_t    T_wcslen(const wchar_t *str) __NOEXCEPT __attribute__((__pure__));
size_t    T_wcsnlen(const wchar_t *str, size_t maxlen) __NOEXCEPT __attribute__((__pure__));
wchar_t * T_wmemset(wchar_t *dst, wchar_t ch, size_t count) __NOEXCEPT;
wchar_t * T_wmemmove(wchar_t *dest, const wchar_t *src, size_t count) __NOEXCEPT;
wchar_t * T_wmemcpy(wchar_t* dest, const wchar_t* src, size_t count) __NOEXCEPT;

#define wcslen T_wcslen
#define wcsnlen T_wcsnlen
#define wmemcpy T_wmemcpy
#define wmemmove T_wmemmove
#define wmemcmp T_wmemcmp
#define wmemchr T_wmemchr
#define wmemset T_wmemset

#endif

int test_wcsnlen(void) {
    const wchar_t str_0[] = {0x0000, 0xCAFE, 0x0000};
    const wchar_t str_1[] = {0x1111, 0x0000, 0x0000};
    const wchar_t str_2[] = {0x2200, 0x0000, 0x0000};
    const wchar_t str_3[] = {0x0033, 0x0000, 0x0000};
    const wchar_t str_4[] = {0x4444, 0x4444, 0x0000, 0xCAFE, 0x0000, 0x00FF, 0x0000, 0xFF00, 0x0000};
    const wchar_t str_5[] = {0x0055, 0x0055, 0x0000, 0xCAFE, 0x0000, 0x00FF, 0x0000, 0xFF00, 0x0000};
    const wchar_t str_6[] = {0x6600, 0x6600, 0x0000, 0xCAFE, 0x0000, 0x00FF, 0x0000, 0xFF00, 0x0000};
    const wchar_t str_7[] = {0x7700, 0x0077, 0x0000, 0xCAFE, 0x0000, 0x00FF, 0x0000, 0xFF00, 0x0000};
    const wchar_t str_8[] = {0x0088, 0x0099, 0xAA00, 0x00BB, 0x00CC, 0xDDDD, 0xEE00, 0xFFFF, 0x0000};
    const wchar_t str_9[] = L"How many wide characters does this string contain?";

    C( 0 == wcslen(L""  ));
    C( 0 == wcslen(str_0));
    C( 1 == wcslen(str_1));
    C( 1 == wcslen(str_2));
    C( 1 == wcslen(str_3));
    C( 2 == wcslen(str_4));
    C( 2 == wcslen(str_5));
    C( 2 == wcslen(str_6));
    C( 2 == wcslen(str_7));
    C( 8 == wcslen(str_8));
    C(50 == wcslen(str_9));

    C( 0 == wcsnlen(L""  , 99));
    C( 0 == wcsnlen(str_0, 99));
    C( 1 == wcsnlen(str_1, 99));
    C( 1 == wcsnlen(str_2, 99));
    C( 1 == wcsnlen(str_3, 99));
    C( 2 == wcsnlen(str_4, 99));
    C( 2 == wcsnlen(str_5, 99));
    C( 2 == wcsnlen(str_6, 99));
    C( 2 == wcsnlen(str_7, 99));
    C( 8 == wcsnlen(str_8, 99));
    C(50 == wcsnlen(str_9, 99));

    C( 0 == wcsnlen(L""  , 0));
    C( 0 == wcsnlen(str_0, 0));
    C( 0 == wcsnlen(str_1, 0));
    C( 0 == wcsnlen(str_2, 0));
    C( 0 == wcsnlen(str_3, 0));
    C( 0 == wcsnlen(str_4, 0));
    C( 0 == wcsnlen(str_5, 0));
    C( 0 == wcsnlen(str_6, 0));
    C( 0 == wcsnlen(str_7, 0));
    C( 0 == wcsnlen(str_8, 0));
    C( 0 == wcsnlen(str_9, 0));

    C( 7 == wcsnlen(str_8,  7));
    C( 8 == wcsnlen(str_8,  8));
    C( 8 == wcsnlen(str_8,  9));
    C(49 == wcsnlen(str_9, 49));
    C(50 == wcsnlen(str_9, 50));
    C(50 == wcsnlen(str_9, 51));

    C( 0 == wcsnlen(L""  , 1));
    C( 0 == wcsnlen(str_0, 1));
    C( 1 == wcsnlen(str_1, 1));
    C( 1 == wcsnlen(str_2, 1));
    C( 1 == wcsnlen(str_3, 1));
    C( 1 == wcsnlen(str_4, 1));
    C( 1 == wcsnlen(str_5, 1));
    C( 1 == wcsnlen(str_6, 1));
    C( 1 == wcsnlen(str_7, 1));
    C( 1 == wcsnlen(str_8, 1));

    C( 0 == wcsnlen(L""  , 2));
    C( 0 == wcsnlen(str_0, 2));
    C( 1 == wcsnlen(str_1, 2));
    C( 1 == wcsnlen(str_2, 2));
    C( 1 == wcsnlen(str_3, 2));
    C( 2 == wcsnlen(str_4, 2));
    C( 2 == wcsnlen(str_5, 2));
    C( 2 == wcsnlen(str_6, 2));
    C( 2 == wcsnlen(str_7, 2));
    C( 2 == wcsnlen(str_8, 2));

    return 0;
}

int test_wmemchr(void) {
    C(wmemchr(PTR_000000, 0x0000, 0) == NULL);
    C(wmemchr(PTR_000000, 0xFFFF, 0) == NULL);

    C(wmemchr(SINK, 0x0000, 0) == NULL);
    C(wmemchr(SINK, 0x0000, 1) == SINK);
    C(wmemchr(SINK, 0x00FF, 1) == NULL);
    C(wmemchr(SINK, 0xFF00, 1) == NULL);
    C(wmemchr(SINK, 0xFFFF, 1) == NULL);
    C(wmemchr(SINK, 0x0000, 2) == SINK);
    C(wmemchr(SINK, 0x0000, 10) == SINK);
    C(wmemchr(SINK, 0x00FF, 10) == NULL);
    C(wmemchr(SINK, 0xFF00, 10) == NULL);
    C(wmemchr(SINK, 0xFFFF, 10) == NULL);
    const wchar_t test0[] = L"GABCDEFABCDEF";
    wchar_t const * const test = &test0[1];

    const size_t test_size = ARRAY_LEN(test0) - 1;
    const size_t test0_size = ARRAY_LEN(test0);
    const size_t test_strlen = ARRAY_LEN(test0) - 2;

    C(wmemchr(test, '\0', test_size) == &test[12]);
    C(wmemchr(test0, 'A', test_strlen) == &test0[1]);
    C(wmemchr(test, 'A', test_strlen) == &test[0]);
    C(wmemchr(&test[7], 'A', 5) == NULL);
    C(wmemchr(&test[6], 'A', 6) == &test[6]);
    C(wmemchr(&test[5], 'A', 7) == &test[6]);
    C(wmemchr(&test[7], 'B', 5) == &test[7]);
    C(wmemchr(&test[8], 'C', 1) == &test[8]);
    C(wmemchr(&test[8], 'C', 8) == &test[8]);
    C(wmemchr(test, 'G', test_strlen) == NULL);
    C(wmemchr(test, 'G', test_size) == NULL);
    C(wmemchr(test0, 'G', test0_size) == test0);
    return 0;
}

int test_wmemcmp(void) {
    const wchar_t a1[] = {L'α',L'β',L'γ'};
    const wchar_t a2[] = {L'α',L'β',L'δ'};

    const size_t sz = (sizeof(a1) / sizeof(a1[0]));
    C(wmemcmp(a1, a1, sz) == 0);
    C(wmemcmp(a1, a2, sz) < 0);
    C(wmemcmp(a2, a1, sz) > 0);
    C(wmemcmp(a1, a2, 0) == 0);
    C(wmemcmp(a1, a2, 1) == 0);
    C(wmemcmp(a1 + 2, a2 + 2, 0) == 0);
    C(wmemcmp(a1 + 2, a2 + 2, 1) < 0);
    return 0;
}

int test_wmemset(void) {
    // test zero byte case
    void* ptr = wmemcpy((void*)0xC0FFEE, (void*)0x123456, 0);
    if (ptr != (void*)0xC0FFEE) {
        test_printf("%p != %p\n", ptr, (void*)0xC0FFEE);
        return __LINE__;
    }
    wchar_t data[192 + 1];
    memset(data, 0xBC, sizeof(data));
    wmemset(wmemset(&data[  0], 0x0012, 64) + 64, 0x0012, 64);
    wmemset(&data[128], 0x0056, 64);
    wchar_t append[64 + 1];
    memset(append, 0xF0, sizeof(append));
    wmemset(append, 0x0034, 64);
    wchar_t* res = wmemset(wmemset(wmemcpy(&data[64], append, 64), 0xA987, 1), 0x2468, 0);
    if (res != &data[64]) {
        test_printf("%p != %p\n", res, &data[64]);
        return __LINE__;
    }
    
    wchar_t truth[192 + 1];
    memset(truth, 0xDE, sizeof(truth));
    C(&truth[  0] == wmemset(&truth[  0], 0x0012, 64));
    C(&truth[ 64] == wmemset(&truth[ 64], 0x0034, 64));
    C(&truth[128] == wmemset(&truth[128], 0x0056, 64));
    wchar_t value = 0xA987;
    C(&truth[64] == wmemcpy(&truth[64], &value, 1));

    int cmp;
    cmp = memcmp(data, truth, 192 * sizeof(wchar_t));
    if (cmp != 0) {
        test_printf("cmp: %d\n", cmp);
        return __LINE__;
    }
    cmp = wmemcmp(data, truth, 192);
    if (cmp != 0) {
        test_printf("cmp: %d\n", cmp);
        return __LINE__;
    }

    wchar_t* ch_test;
    ch_test = wmemchr(data, 0xBCBC, ARRAY_LEN(data));
    C((ch_test != NULL) && (*ch_test == (wchar_t)0xBCBC));
    ch_test = wmemchr(truth, 0xDEDE, ARRAY_LEN(truth));
    C((ch_test != NULL) && (*ch_test == (wchar_t)0xDEDE));

    ch_test = wmemchr(data, 0x1200, ARRAY_LEN(data));
    C(ch_test == NULL);
    ch_test = wmemchr(truth, 0x3400, ARRAY_LEN(truth));
    return 0;
}

int test_wmemmove(void) {
    wchar_t move_str[] =
    {0x000F, 0x111F, 0x222F, 0x333F, 0x444F, 0x555F, 0x666F, 0x777F, 0x888F, 0x999F};
    const wchar_t truth_str[] = 
    {0x999F, 0x333F, 0x444F, 0x444F, 0x555F, 0x444F, 0x555F, 0x666F, 0x888F, 0x999F};
    C(move_str + 5 == wmemmove(move_str + 5, move_str + 4, 3));
    C(move_str + 3 == wmemmove(move_str + 3, move_str + 3, 0));
    C(move_str + 1 == wmemmove(move_str + 1, move_str + 3, 4));
    C(move_str + 2 == wmemmove(move_str + 2, move_str + 2, 6));
    C(move_str + 9 == wmemmove(move_str + 9, move_str + 0, 0));
    C(move_str + 0 == wmemmove(move_str + 0, move_str + 9, 1));
    C(wmemcmp(move_str, truth_str, ARRAY_LEN(move_str)) == 0);

    C(PTR_000000 == wmemcpy(PTR_000000, PTR_000000, 0));
    C(PTR_000000 == wmemcpy(PTR_000000, PTR_FFFFFF, 0));
    C(PTR_FFFFFF == wmemcpy(PTR_FFFFFF, PTR_000000, 0));
    C(PTR_FFFFFF == wmemcpy(PTR_FFFFFF, PTR_FFFFFF, 0));

    C(PTR_000000 == wmemmove(PTR_000000, PTR_000000, 0));
    C(PTR_000000 == wmemmove(PTR_000000, PTR_FFFFFF, 0));
    C(PTR_FFFFFF == wmemmove(PTR_FFFFFF, PTR_000000, 0));
    C(PTR_FFFFFF == wmemmove(PTR_FFFFFF, PTR_FFFFFF, 0));

    return 0;
}

int run_tests(void) {
    int ret = 0;

    TEST(test_wcsnlen());
    TEST(test_wmemchr());
    TEST(test_wmemcmp());
    TEST(test_wmemset());
    TEST(test_wmemmove());

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
