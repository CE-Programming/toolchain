#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>
#include <ctype.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

// define to 0 or 1 (prevents Clang from replacing functions with builtins)
#define RENAME_FUNCTIONS 1

//------------------------------------------------------------------------------
// Utilities
//------------------------------------------------------------------------------

#define C(expr) if (!(expr)) { return __LINE__; }

#define TEST(test) { ret = test; if (ret != 0) { return ret; } }

#define SINK (char*)0xE40000

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#ifndef RENAME_FUNCTIONS
#error "RENAME_FUNCTIONS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

/* pass NULL into functions without triggering -Wnonnull */
extern void* NULL_ptr;

//------------------------------------------------------------------------------
// Debug routines
//------------------------------------------------------------------------------

__attribute__((__unused__)) static void write_letter(char ch) {
    if (isgraph(ch)) {
        fputc(ch, stdout);
        return;
    }
    fputc('\\', stdout);
    switch (ch) {
        case '\0': fputc('0', stdout); return;
        case ' ' : fputc('s', stdout); return;
        case '\n': fputc('n', stdout); return;
        case '\t': fputc('t', stdout); return;
        case '\v': fputc('v', stdout); return;
        case '\r': fputc('r', stdout); return;
        case '\f': fputc('f', stdout); return;
        case '\b': fputc('b', stdout); return;
        default: {
            char buf[sizeof("xFF")];
            boot_sprintf(buf, "x%02X", (unsigned int)ch);
            fputs(buf, stdout);
            return;
        }
    }
}

__attribute__((__unused__)) static void print_mem_string(const char *str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        write_letter(*str++);
    }
    fputc('\n', stdout);
}

__attribute__((__unused__)) static void print_string(const char* str) {
    print_mem_string(str, strlen(str));
}

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

// prevents Clang from replacing function calls with builtins
#if RENAME_FUNCTIONS

void T_bzero(void* s, size_t n);

void *T_memccpy(void *__restrict dest, const void *__restrict src, int c, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_memchr(const void *s, int c, size_t n)
    __attribute__((nonnull(1)));

int T_memcmp(const void *s1, const void *s2, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_memcpy(void *__restrict dest, const void *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_memmem(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len)
    __attribute__((nonnull(1, 3)));

void *T_memmove(void *dest, const void *src, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_mempcpy(void *__restrict dest, const void *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_memchr(const void *s, int c, size_t n)
    __attribute__((nonnull(1)));

void *T_memrchr(const void *s, int c, size_t n)
    __attribute__((nonnull(1)));

void *T_memrmem(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len)
    __attribute__((nonnull(1, 3)));

void *T_memset(void *s, int c, size_t n)
    __attribute__((nonnull(1)));

char *T_stpcpy(char *__restrict dest, const char *__restrict src)
    __attribute__((nonnull(1, 2)));

char *T_stpncpy(char *__restrict dest, const char *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

char *T_strcat(char *__restrict dest, const char *__restrict src)
    __attribute__((nonnull(1, 2)));

char *T_strchr(const char *s, int c)
    __attribute__((nonnull(1)));

char *T_strchrnul(const char *s, int c)
    __attribute__((nonnull(1)));

int T_strcmp(const char *s1, const char *s2)
    __attribute__((nonnull(1, 2)));

char *T_strcpy(char *__restrict dest, const char *__restrict src)
    __attribute__((nonnull(1, 2)));

size_t T_strlcat(void *__restrict dest, const void *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

size_t T_strlen(const char *s)
    __attribute__((nonnull(1)));

char *T_strncat(char *__restrict dest, const char *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

int T_strncmp(const char *s1, const char *s2, size_t n)
    __attribute__((nonnull(1, 2)));

char *T_strncpy(char *__restrict dest, const char *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

size_t T_strnlen(const char *s, size_t maxlen)
    __attribute__((nonnull(1)));

char *T_strrchr(const char *s, int c)
    __attribute__((nonnull(1)));

char *T_strrstr(const char *haystack, const char *needle)
    __attribute__((nonnull(1, 2)));

char *T_strstr(const char *haystack, const char *needle)
    __attribute__((nonnull(1, 2)));

char *T_strtok(char *__restrict s, const char *__restrict delim)
    __attribute__((nonnull(2)));

char *T_strtok_r(char *__restrict s, const char *__restrict delim, char **__restrict save_ptr)
    __attribute__((nonnull(2, 3)));

#else

#define T_bzero bzero
#define T_memccpy memccpy
#define T_memchr memchr
#define T_memcmp memcmp
#define T_memcpy memcpy
#define T_memmem memmem
#define T_memmove memmove
#define T_mempcpy mempcpy
#define T_memchr memchr
#define T_memrchr memrchr
#define T_memrmem memrmem
#define T_memset memset
#define T_stpcpy stpcpy
#define T_stpncpy stpncpy
#define T_strcat strcat
#define T_strchr strchr
#define T_strchrnul strchrnul
#define T_strcmp strcmp
#define T_strcpy strcpy
#define T_strlcat strlcat
#define T_strlen strlen
#define T_strncat strncat
#define T_strncmp strncmp
#define T_strncpy strncpy
#define T_strnlen strnlen
#define T_strrchr strrchr
#define T_strrstr strrstr
#define T_strstr strstr
#define T_strtok strtok
#define T_strtok_r strtok_r

#endif

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

const char gnu_copypasta[] =
    "I would just like to interject for a moment. What you're referring to "\
    "as Linux, is in fact, GNU/Linux, or as I\'ve recently taken to calling "\
    "it, GNU plus Linux. Linux is not an operating system unto itself, but "\
    "rather another free component of a fully functioning GNU system made "\
    "useful by the GNU corelibs, shell utilities and vital system "\
    "components comprising a full OS as defined by POSIX";

static char const * const test_1 =
"+123 asprintf% 076543 0x9abcd  0XFE1 0\n";
static char const * const test_2 =
"+123 asprintf% 076543 0x9abcd  0XFE1 0\nfoo";
static const int pos_1 = 30;
static const int pos_2 = 42;

static char const * const test_3 =
"sprintf%%%% %%is unsafe";
static const int pos_3 = 20;

static const int pos_4 = 212;

static char* buf = NULL;
static FILE* file = NULL;

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

int boot_sprintf_tests(void) {
    int pos;
    int len = boot_asprintf(
        &buf, "%+d %s%% %#o %#x %n %#X %i\n",
        123, "asprintf", 076543, 0x9abcd, &pos, 0xFE1, 0
    );
    if (buf == NULL || len <= 0) {
        test_printf("buf %p len %d\n", buf, len);
        return __LINE__;
    }
    if (buf[len] != '\0') {
        return __LINE__;
    }
    size_t buf_len = T_strlen(buf);
    if (buf_len != T_strlen(test_1) || buf_len != (size_t)len) {
        test_printf("E: %zu != %zu != %d\n", T_strlen(test_1), buf_len, len);
        return __LINE__;
    }
    if (pos != pos_1) {
        test_printf("E: %d != %d\n", pos, pos_1);
        return __LINE__;
    }
    int cmp = strcmp(buf, test_1);
    if (cmp != 0) {
        test_printf("cmp: %d\n", cmp);
        return __LINE__;
    }
    char append[128];
    int snprintf_test = boot_snprintf(append, 20, "%s", test_1);
    if (snprintf_test != (int)T_strlen(test_1)) {
        test_printf("sprintf_test: %d\n", snprintf_test);
        return __LINE__;
    }
    int len_2 = boot_snprintf(append, sizeof(append), "%s", test_1);
    if (len_2 != (int)T_strlen(test_1)) {
        test_printf("E: %d != %zu\n", len_2, T_strlen(test_1));
        return __LINE__;
    }
    char str2[128];
    char* end;
    end = T_stpcpy(str2, append);
    end = T_stpcpy(end, "");
    end = T_stpcpy(end, "foo");
    if (*end != '\0') {
        return __LINE__;
    }
    if (end != &str2[pos_2]) {
        test_printf("diff %p - %p = %td\n", end, str2, (ptrdiff_t)(end - str2));
        return __LINE__;
    }
    int cmp2 = T_strcmp(str2, test_2);
    if (cmp2 != 0) {
        test_printf("cmp: %d\n", cmp2);
        return __LINE__;
    }
    char buf_3[30];
    int len_3 = boot_snprintf(buf_3, sizeof(buf_3), test_3);
    if (len_3 != pos_3) {
        test_printf("E: %d != %d\n", len_3, pos_3);
        return __LINE__;
    }

    // large string test
    static char const * const s = "Hello";
    int len_4 = boot_snprintf(SINK, 300,
        "Strings:\n"
        " padding:\n"
        "*[%10s]\n"
        "*[%-10s]\n"
        "*[%*s]\n"
        " truncating:\n"
        "%%%.4s\n"
        "%%%.*s\n"
        "Characters:\t%c %%\n"
        "Integers:\n"
        "%%*Decimal:\t%i %d %.6i %i %3u %+i %i\n"
        "*%%Hexadecimal:\t%x %x %X %#x\n"
        "%%*.*%%Octal:\t%o %#o %#o\n"
        "Width trick: %*d \n",
        s,
        s,
        10, s,
        s,
        3, s,
        'A',
        1, 2, 3, 0, 0, 4, -4,
        5, 10, 10, 6,
        10, 10, 4,
        5, 10
    );
    if (len_4 != pos_4) {
        test_printf("E: %d != %d\n", len_4, pos_4);
        return __LINE__;
    }
    int len_5 = boot_snprintf(SINK, 10, "");
    if (len_5 != 0) {
        test_printf("E: %d != 0\n", len_5);
        return __LINE__;
    }

    return 0;
}

static char const float_str[] = "+2.7182817459106445312500";
static char const long_double_str[] = "2.7182818284590450907956";

int nano_tests(void) {
    int pos;
    int len = asprintf(
        &buf, "%+d %s%% %#o %#x %n %#X %i\n",
        123, "asprintf", 076543, 0x9abcd, &pos, 0xFE1, 0
    );
    if (buf == NULL || len <= 0) {
        test_printf("buf %p len %d\n", buf, len);
        return __LINE__;
    }
    if (buf[len] != '\0') {
        return __LINE__;
    }
    size_t buf_len = T_strlen(buf);
    if (buf_len != T_strlen(test_1) || buf_len != (size_t)len) {
        test_printf("E: %zu != %zu != %d\n", T_strlen(test_1), buf_len, len);
        return __LINE__;
    }
    if (pos != pos_1) {
        test_printf("E: %d != %d\n", pos, pos_1);
        return __LINE__;
    }
    int cmp = strcmp(buf, test_1);
    if (cmp != 0) {
        test_printf("cmp: %d\n", cmp);
        return __LINE__;
    }
    char append[128];
    int snprintf_test = snprintf(append, 20, "%s", test_1);
    if (snprintf_test != (int)T_strlen(test_1)) {
        test_printf("sprintf_test: %d\n", snprintf_test);
        return __LINE__;
    }
    int len_2 = snprintf(append, sizeof(append), "%s", test_1);
    if (len_2 != (int)T_strlen(test_1)) {
        test_printf("E: %d != %zu\n", len_2, T_strlen(test_1));
        return __LINE__;
    }
    char str2[128];
    char* end;
    end = T_stpcpy(str2, append);
    end = T_stpcpy(end, "");
    end = T_stpcpy(end, "foo");
    if (*end != '\0') {
        return __LINE__;
    }
    if (end != &str2[pos_2]) {
        test_printf("diff %p - %p = %td\n", end, str2, (ptrdiff_t)(end - str2));
        return __LINE__;
    }
    int cmp2 = T_strcmp(str2, test_2);
    if (cmp2 != 0) {
        test_printf("cmp: %d\n", cmp2);
        return __LINE__;
    }
    char buf_30[30];
    int len_3sn = snprintf(buf_30, sizeof(buf_30), test_3);
    if (len_3sn != pos_3) {
        test_printf("E: %d != %d\n", len_3sn, pos_3);
        return __LINE__;
    }

    int len_3s = sprintf(buf_30, test_3);
    if (len_3s != pos_3) {
        test_printf("E: %d != %d\n", len_3s, pos_3);
        return __LINE__;
    }

    // https://en.cppreference.com/w/c/io/fprintf
    static char const * const s = "Hello";
    int len_4 = snprintf(SINK, 300,
        "Strings:\n"
        " padding:\n"
        "*[%10s]\n"
        "*[%-10s]\n"
        "*[%*s]\n"
        " truncating:\n"
        "%%%.4s\n"
        "%%%.*s\n"
        "Characters:\t%c %%\n"
        "Integers:\n"
        "%%*Decimal:\t%i %d %.6i %i %3u %+i %i\n"
        "*%%Hexadecimal:\t%x %x %X %#x\n"
        "%%*.*%%Octal:\t%o %#o %#o\n"
        "Width trick: %*d \n",
        s,
        s,
        10, s,
        s,
        3, s,
        'A',
        1, 2, 3, 0, 0, 4, -4,
        5, 10, 10, 6,
        10, 10, 4,
        5, 10
    );
    if (len_4 != pos_4) {
        test_printf("E: %d != %d\n", len_4, pos_4);
        return __LINE__;
    }
    int len_5 = snprintf(SINK, 10, "");
    if (len_5 != 0) {
        test_printf("E: %d != 0\n", len_5);
        return __LINE__;
    }

    memset(buf_30, 'T', sizeof(buf_30) - 1);
    buf_30[sizeof(buf_30) - 1] = '\0';

    // I have memorized e to 70 digits
    sprintf(buf_30, "%.22f", 2.71828182845904523536028747135f);
    C(T_strcmp(buf_30, &float_str[1]) == 0);
    snprintf(buf_30, sizeof(buf_30), "%+.22lf", 2.71828182845904523536028747135);
    C(T_strcmp(buf_30, &float_str[0]) == 0);
    snprintf(buf_30, sizeof(long_double_str), "%.22Lf", 2.71828182845904523536028747135L);
    C(T_strcmp(buf_30, long_double_str) == 0);

    return 0;
}

static char const * const fprintf_test =
    "Terminal ':' (found):\t\"Stars:\"\n"
    "Terminal ' ' (found):\t\"Stars: \"\n"
    "Terminal ',' (found):\t\"Stars: Altair,\"\n"
    "Terminal '.' (found):\t\"Stars: Altair, Sun, Vega.\"\n"
    "Terminal '!' (absent):\t\"Stars: Altair, Sun, Vega.@\"\n"
    "\n"
    "Separate star names from distances (ly):\n"
    "Arcturus Vega Capella Rigel Procyon \n"
/* fprintf_test */;

static char const * const file_name = "FPRINTST";

static void get_diff_char(const char* data, const char* test) {
    size_t char_pos = 0;
    char prev = '\0';
    while (*data != '\0' && *test != '\0') {
        if (*data != *test) {
            printf("prev %02X: %02X != %02X at %zu\n", prev, *data, *test, char_pos);
            return;
        }
        prev = *data;
        data++;
        test++;
        char_pos++;
    }
}

int memccpy_tests(void) {
    // test zero byte case
    void* ptr = T_memccpy((void*)0xC0FFEE, (void*)0x123456, 123, 0);
    if (ptr != NULL) {
        test_printf("%p != NULL\n", ptr);
        return __LINE__;
    }
    file = fopen(file_name, "wb");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return __LINE__;
    }
    // https://en.cppreference.com/w/c/string/byte/memccpy
    const char src[] = "Stars: Altair, Sun, Vega.";
    const char terminal[] = {':', ' ', ',', '.', '!'};
    char dest[sizeof src];
    const char alt = '@';

    for (size_t i = 0; i != sizeof terminal; ++i)
    {
        void* to = T_memccpy(dest, src, terminal[i], sizeof dest);

        fprintf(file,"Terminal '%c' (%s):\t\"", terminal[i], to ? "found" : "absent");

        // if `terminal` character was not found - print the whole `dest`
        to = to ? to : dest + sizeof dest;

        for (char* from = dest; from != to; ++from) {
            fputc(isprint(*from) ? *from : alt, file);
        }

        fputs("\"\n", file);
    }


    fprintf(file, "%c%s", '\n', "Separate star names from distances (ly):\n");
    const char *star_distance[] = {
        "Arcturus : 37", "Vega : 25", "Capella : 43", "Rigel : 860", "Procyon : 11"
    };
    char names_only[64];
    char *first = names_only;
    char *last = names_only + sizeof names_only;

    for (size_t t = 0; t != (sizeof star_distance) / (sizeof star_distance[0]); ++t)
    {
        if (first) {
            first = T_memccpy(first, star_distance[t], ' ', last - first);
        } else {
            break;
        }
    }

    if (first) {
        *first = '\0';
        fprintf(file, "%s%c", names_only, '\n');
    } else {
        printf("Error Buffer is too small.\n");
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        perror("file_size <= 0");
        return __LINE__;
    }

    /* check that no crashes occur with small calloc sizes */
    buf = (char*)calloc(1, sizeof(char));
    free(buf);
    buf = (char*)calloc(0, sizeof(char));
    free(buf);

    buf = (char*)calloc(file_size + 1, sizeof(char));
    if (buf == NULL) {
        perror("calloc failure");
        return __LINE__;
    }

    size_t bytes_read = fread(buf, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        perror("Error reading from file");
        return __LINE__;
    }
    if (T_strlen(buf) != T_strlen(fprintf_test)) {
        printf("E: %zu != %zu\n", T_strlen(buf), T_strlen(fprintf_test));
        get_diff_char(buf, fprintf_test);
        return __LINE__;
    }
    int cmp = strcmp(buf, fprintf_test);
    if (cmp != 0) {
        printf("fprintf_cmp: %d\n", cmp);
        get_diff_char(buf, fprintf_test);
        return __LINE__;
    }
    return 0;
}

int mempcpy_test(void) {
    // test zero byte case
    void* ptr = T_mempcpy((void*)0xC0FFEE, (void*)0x123456, 0);
    if (ptr != (void*)0xC0FFEE) {
        test_printf("%p != %p\n", ptr, (void*)0xC0FFEE);
        return __LINE__;
    }
    char data[192 + 1];
    T_memset(&data[  0], 0x12, 64);
    T_memset(&data[ 64], 0x12, 64);
    T_memset(&data[128], 0x56, 64);
    char append[64 + 1];
    T_memset(append, 0x34, 64);
    char* res = T_mempcpy(&data[64], append, 64);
    if (res != &data[128]) {
        test_printf("%p != %p\n", res, &data[128]);
        return __LINE__;
    }

    char truth[192 + 1];
    T_memset(&truth[  0], 0x12, 64);
    T_memset(&truth[ 64], 0x34, 64);
    T_memset(&truth[128], 0x56, 64);

    int cmp = T_memcmp(data, truth, 192);
    if (cmp != 0) {
        test_printf("cmp: %d\n", cmp);
        return __LINE__;
    }
    return 0;
}

int bzero_test(void) {
    char truth[32];
    char data[32];

    // test zero size cases
    C(T_memset(NULL_ptr, 0xCE, 0) == NULL_ptr);
    C(T_memset((void*)0xFFFFFF, 0xCE, 0) == (void*)0xFFFFFF);
    C(T_memset((void*)0x000001, 0xCE, 0) == (void*)0x000001);
    T_bzero(NULL_ptr, 0);
    T_bzero((void*)0xFFFFFF, 0);
    T_bzero((void*)0x000001, 0);

    T_memset(data, 0x8F, sizeof(data));
    T_memset(&truth[ 0], 0x8F,  8);
    T_memset(&truth[ 2], 0x00,  1);
    T_memset(&truth[ 8], 0x00, 17);
    T_memset(&truth[25], 0x8F,  7);
    T_bzero(&data[2], 0);
    T_bzero(&data[2], 1);
    if (T_strlen(&data[0]) != 2) {
        return __LINE__;
    }
    if (T_strlen(&data[1]) != 1) {
        return __LINE__;
    }
    if (T_strlen(&data[2]) != 0) {
        return __LINE__;
    }
    T_bzero(NULL, 0);
    T_bzero(&data[8], 17);
    int cmp = T_memcmp(data, truth, 32);
    if (cmp != 0) {
        test_printf("cmp: %d\n", cmp);
        return __LINE__;
    }
    return 0;
}

int strncmp_test(void) {
    const char* str0 = "Hello World!";
    const char* str1 = "Hello!";
    const char* str2 = "Hello";
    const char* str3 = "Hello there";
    const char* str4 = "Hello, everybody!";
    const char* str5 = "Hello, somebody!";

    C(T_strcmp(SINK, SINK) == 0);
    C(T_strcmp("C", "C") == 0);
    C(T_strcmp("A", "C") < 0);
    C(T_strcmp("C", "A") > 0);
    C(T_strcmp("CD", "CD") == 0);
    C(T_strcmp("AB", "CD") < 0);
    C(T_strcmp("CD", "AB") > 0);
    C(T_strcmp("FE", "FG") < 0);
    C(T_strcmp("FG", "FE") > 0);
    C(T_strcmp(str0, str1) < 0);
    C(T_strcmp(str0, str2) > 0);
    C(T_strcmp(str0, str3) < 0);
    C(T_strcmp(str4 + 12, str5 + 11) == 0);

    C(T_strncmp(SINK, SINK, 0) == 0);
    C(T_strncmp(SINK, SINK, 1) == 0);
    C(T_strncmp(SINK, SINK, 2) == 0);
    C(T_strncmp("C", "C", 1) == 0);
    C(T_strncmp("A", "C", 1) < 0);
    C(T_strncmp("C", "A", 1) > 0);
    C(T_strncmp("CD", "CD", 2) == 0);
    C(T_strncmp("AB", "CD", 2) < 0);
    C(T_strncmp("CD", "AB", 2) > 0);
    C(T_strncmp("FE", "FG", 2) < 0);
    C(T_strncmp("FG", "FE", 2) > 0);
    C(T_strncmp(str0, str1, 5) == 0);
    C(T_strncmp(str0, str2, 10) > 0);
    C(T_strncmp(str0, str3, 10) < 0);
    C(T_strncmp(str4 + 12, str5 + 11, 5) == 0);

    C(T_memcmp(SINK, SINK, 0) == 0);
    C(T_memcmp(SINK, SINK, 1) == 0);
    C(T_memcmp(SINK, SINK, 2) == 0);
    C(T_memcmp("C", "C", 1) == 0);
    C(T_memcmp("A", "C", 1) < 0);
    C(T_memcmp("C", "A", 1) > 0);
    C(T_memcmp("CD", "CD", 2) == 0);
    C(T_memcmp("AB", "CD", 2) < 0);
    C(T_memcmp("CD", "AB", 2) > 0);
    C(T_memcmp("FE", "FG", 2) < 0);
    C(T_memcmp("FG", "FE", 2) > 0);
    C(T_memcmp(str0, str1, 5) == 0);
    C(T_memcmp(str0, str2, 10) > 0);
    C(T_memcmp(str0, str3, 10) < 0);
    C(T_memcmp(str4 + 12, str5 + 11, 5) == 0);

    return 0;
}

int memchr_test(void) {
    C(T_memchr(NULL_ptr, 0x00, 0) == NULL_ptr);
    C(T_memchr(NULL_ptr, 0xFF, 0) == NULL_ptr);

    C(T_memchr(SINK, 0x00, 0) == NULL);
    C(T_memchr(SINK, 0x00, 1) == SINK);
    C(T_memchr(SINK, 0xFF, 1) == NULL);
    C(T_memchr(SINK, 0x00, 2) == SINK);
    C(T_memchr(SINK, 0x00, 500) == SINK);
    const char test0[] = "ABCDEFABCDEF\0G";
    char const * const test = &test0[0];

    const size_t test_size = sizeof(test0) - 2;
    const size_t test_strlen = sizeof(test0) - 3;

    C(T_memchr(test, '\0', sizeof(test0)) == &test[12]);
    C(T_memchr(test, 'A', test_strlen) == &test[0]);
    C(T_memchr(&test[7], 'A', 5) == NULL);
    C(T_memchr(&test[6], 'A', 6) == &test[6]);
    C(T_memchr(&test[5], 'A', 7) == &test[6]);
    C(T_memchr(&test[7], 'B', 5) == &test[7]);
    C(T_memchr(&test[8], 'C', 1) == &test[8]);
    C(T_memchr(&test[8], 'C', 8) == &test[8]);
    C(T_memchr(test, 'G', test_strlen) == NULL);
    C(T_memchr(test, 'G', test_size) == NULL);
    C(T_memchr(test0, 'G', sizeof(test0)) == &test[test_size]);

    return 0;
}

int memrchr_test(void) {
    C(T_memrchr(NULL_ptr, 0x00, 0) == NULL_ptr);
    C(T_memrchr(NULL_ptr, 0xFF, 0) == NULL_ptr);

    C(T_memrchr(SINK, 0x00, 0) == NULL);
    C(T_memrchr(SINK, 0x00, 1) == SINK);
    C(T_memrchr(SINK, 0xFF, 1) == NULL);
    C(T_memrchr(SINK, 0x00, 2) == SINK + 2 - 1);
    C(T_memrchr(SINK, 0x00, 500) == SINK + 500 - 1);
    const char test0[] = "GABCDEFABCDEF";
    char const * const test = &test0[1];

    const size_t test_size = sizeof(test0) - 1;
    const size_t test_strlen = sizeof(test0) - 2;

    C(T_memrchr(test, '\0', test_size) == &test[12]);
    C(T_memrchr(test, 'A', test_strlen) == &test[6]);
    C(T_memrchr(&test[7], 'A', 5) == NULL);
    C(T_memrchr(&test[6], 'A', 6) == &test[6]);
    C(T_memrchr(&test[5], 'A', 7) == &test[6]);
    C(T_memrchr(&test[7], 'B', 5) == &test[7]);
    C(T_memrchr(&test[8], 'C', 1) == &test[8]);
    C(T_memrchr(&test[8], 'C', 8) == &test[8]);
    C(T_memrchr(test, 'G', test_strlen) == NULL);
    C(T_memrchr(test, 'G', test_size) == NULL);
    C(T_memrchr(test0, 'G', sizeof(test0)) == test0);

    return 0;
}

int memmove_test(void) {
    char move_str[]        = "0123456789";
    const char truth_str[] = "9344545689";
    C(move_str + 5 == (char*)T_memmove(move_str + 5, move_str + 4, 3));
    C(move_str + 3 == (char*)T_memmove(move_str + 3, move_str + 3, 0));
    C(move_str + 1 == (char*)T_memmove(move_str + 1, move_str + 3, 4));
    C(move_str + 2 == (char*)T_memmove(move_str + 2, move_str + 2, 6));
    C(move_str + 9 == (char*)T_memmove(move_str + 9, move_str + 0, 0));
    C(move_str + 0 == (char*)T_memmove(move_str + 0, move_str + 9, 1));
    C(strcmp(move_str, truth_str) == 0);

    C(NULL_ptr - 0 == (char*)T_memmove(NULL_ptr - 0, NULL_ptr - 0, 0));
    C(NULL_ptr - 0 == (char*)T_memmove(NULL_ptr - 0, NULL_ptr - 1, 0));
    C(NULL_ptr - 1 == (char*)T_memmove(NULL_ptr - 1, NULL_ptr - 0, 0));

    return 0;
}

static bool strcmp_exact(const char* x, const char* y) {
    if (strlen(x) != strlen(y)) {
        return false;
    }
    if (strcmp(x, y) != 0) {
        return false;
    }
    return true;
}

int strlcat_test(void) {
    const char* src1 = "Foo";
    const char* src2 = "Bar";
    char dst[10];

    strcpy(dst, src1); C(T_strlcat(dst , src2, 0) == 3); C(strcmp_exact(dst, "Foo"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 1) == 4); C(strcmp_exact(dst, "Foo"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 2) == 5); C(strcmp_exact(dst, "Foo"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 3) == 6); C(strcmp_exact(dst, "Foo"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 4) == 6); C(strcmp_exact(dst, "Foo"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 5) == 6); C(strcmp_exact(dst, "FooB"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 6) == 6); C(strcmp_exact(dst, "FooBa"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 7) == 6); C(strcmp_exact(dst, "FooBar"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 8) == 6); C(strcmp_exact(dst, "FooBar"));
    strcpy(dst, src1); C(T_strlcat(dst , src2, 9) == 6); C(strcmp_exact(dst, "FooBar"));

    strcpy(dst, src1); C(T_strlcat(dst , SINK, 0) == 0); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strlcat(dst , SINK, 1) == 1); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strlcat(dst , SINK, 2) == 2); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strlcat(dst , SINK, 3) == 3); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strlcat(dst , SINK, 4) == 3); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strlcat(dst , SINK, 5) == 3); C(strcmp_exact(dst, src1));

    C(T_strlcat(NULL_ptr, SINK, 0) == 0);
    C(T_strlcat(NULL_ptr, src1, 0) == 3);

    dst[0] = '\0'; C(T_strlcat(dst, SINK, 0) == 0); C(dst[0] == '\0');
    dst[0] = '\0'; C(T_strlcat(dst, SINK, 1) == 0); C(dst[0] == '\0');
    dst[0] = '\0'; C(T_strlcat(dst, SINK, 2) == 0); C(dst[0] == '\0');

    dst[0] = '\0'; C(T_strlcat(dst, src1, 0) == 3); C(strcmp_exact(dst, ""));
    dst[0] = '\0'; C(T_strlcat(dst, src1, 1) == 3); C(strcmp_exact(dst, ""));
    dst[0] = '\0'; C(T_strlcat(dst, src1, 2) == 3); C(strcmp_exact(dst, "F"));
    dst[0] = '\0'; C(T_strlcat(dst, src1, 3) == 3); C(strcmp_exact(dst, "Fo"));
    dst[0] = '\0'; C(T_strlcat(dst, src1, 4) == 3); C(strcmp_exact(dst, "Foo"));
    dst[0] = '\0'; C(T_strlcat(dst, src1, 5) == 3); C(strcmp_exact(dst, "Foo"));

    return 0;
}

int strcpy_test(void) {
    char dst[10];
    dst[0] = '\0';
    C(T_strcpy(SINK, dst) == SINK);
    C(T_strcpy(dst, SINK) == dst);

    dst[0] = '\xff';
    C(T_strcpy(dst, "") == dst); C(strcmp_exact(dst, ""));
    C(T_strcpy(dst, "a") == dst); C(strcmp_exact(dst, "a"));
    C(T_strcpy(dst, "bc") == dst); C(strcmp_exact(dst, "bc"));
    C(T_strcpy(dst, "def") == dst); C(strcmp_exact(dst, "def"));
    C(T_strcpy(dst, "123456789") == dst); C(strcmp_exact(dst, "123456789"));

    return 0;
}

int strcat_test(void) {
    char dst[10];
    memset(dst, '\0', sizeof(dst));
    C(T_strcat(SINK, dst) == SINK);
    C(T_strcat(dst, SINK) == dst);

    dst[0] = '\0';
    C(T_strcat(dst, "" ) == dst); C(strcmp_exact(dst, ""));
    C(T_strcat(dst, "a") == dst); C(strcmp_exact(dst, "a"));
    C(T_strcat(dst, "b") == dst); C(strcmp_exact(dst, "ab"));
    C(T_strcat(dst, "" ) == dst); C(strcmp_exact(dst, "ab"));
    dst[0] = '\0';
    C(T_strcat(dst, "Foo") == dst); C(strcmp_exact(dst, "Foo"));
    C(T_strcat(dst, "Bar") == dst); C(strcmp_exact(dst, "FooBar"));

    return 0;
}

int strncat_test(void) {
    const char* src1 = "Foo";
    const char* src2 = "Bar";
    char dst[10];

    strcpy(dst, src1); C(T_strncat(dst , src2, 0) == dst); C(strcmp_exact(dst, "Foo"));
    strcpy(dst, src1); C(T_strncat(dst , src2, 1) == dst); C(strcmp_exact(dst, "FooB"));
    strcpy(dst, src1); C(T_strncat(dst , src2, 2) == dst); C(strcmp_exact(dst, "FooBa"));
    strcpy(dst, src1); C(T_strncat(dst , src2, 3) == dst); C(strcmp_exact(dst, "FooBar"));
    strcpy(dst, src1); C(T_strncat(dst , src2, 4) == dst); C(strcmp_exact(dst, "FooBar"));
    strcpy(dst, src1); C(T_strncat(dst , src2, 5) == dst); C(strcmp_exact(dst, "FooBar"));

    strcpy(dst, src1); C(T_strncat(dst , SINK, 0) == dst); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strncat(dst , SINK, 1) == dst); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strncat(dst , SINK, 2) == dst); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strncat(dst , SINK, 3) == dst); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strncat(dst , SINK, 4) == dst); C(strcmp_exact(dst, src1));
    strcpy(dst, src1); C(T_strncat(dst , SINK, 5) == dst); C(strcmp_exact(dst, src1));

    dst[0] = '\0'; C(T_strncat(dst, SINK, 0) == dst); C(dst[0] == '\0');
    dst[0] = '\0'; C(T_strncat(dst, SINK, 1) == dst); C(dst[0] == '\0');
    dst[0] = '\0'; C(T_strncat(dst, SINK, 2) == dst); C(dst[0] == '\0');

    dst[0] = '\0'; C(T_strncat(dst, src1, 0) == dst); C(strcmp_exact(dst, ""));
    dst[0] = '\0'; C(T_strncat(dst, src1, 1) == dst); C(strcmp_exact(dst, "F"));
    dst[0] = '\0'; C(T_strncat(dst, src1, 2) == dst); C(strcmp_exact(dst, "Fo"));
    dst[0] = '\0'; C(T_strncat(dst, src1, 3) == dst); C(strcmp_exact(dst, "Foo"));
    dst[0] = '\0'; C(T_strncat(dst, src1, 4) == dst); C(strcmp_exact(dst, "Foo"));
    dst[0] = '\0'; C(T_strncat(dst, src1, 5) == dst); C(strcmp_exact(dst, "Foo"));

    return 0;
}

int strncpy_test(void) {
    char text[6];

    C(T_strncpy(NULL_ptr, "", 0) == NULL_ptr + 0);
    C(T_strncpy(NULL_ptr, "foobar", 0) == NULL_ptr + 0);

    memset(text, '\xee', 6);

    C(T_strncpy(text, "1", 5) == text);
    C(memcmp(text, "1\0\0\0\0\xee", 6) == 0);

    C(T_strncpy(text, "1234", 5) == text);
    C(memcmp(text, "1234\0\xee", 6) == 0);

    C(T_strncpy(text, "12345", 5) == text);
    C(memcmp(text, "12345\xee", 6) == 0);

    C(T_strncpy(text, "123456", 5) == text);
    C(memcmp(text, "12345\xee", 6) == 0);

    memset(text, '\xff', 6);

    C(T_strncpy(text, "", 0) == text);
    C(memcmp(text, "\xff\xff\xff\xff\xff\xff", 6) == 0);

    C(T_strncpy(text, "123456", 1) == text);
    C(memcmp(text, "1\xff\xff\xff\xff\xff", 6) == 0);

    C(T_strncpy(text, "6", 1) == text);
    C(memcmp(text, "6\xff\xff\xff\xff\xff", 6) == 0);

    C(T_strncpy(text, "", 1) == text);
    C(memcmp(text, "\0\xff\xff\xff\xff\xff", 6) == 0);

    C(T_strncpy(text, "a", 2) == text);
    C(memcmp(text, "a\0\xff\xff\xff\xff", 6) == 0);

    C(T_strncpy(text, "", 5) == text);
    C(memcmp(text, "\0\0\0\0\0\xff", 6) == 0);

    return 0;
}

int stpncpy_test(void) {
    char text[6];

    C(T_stpncpy(NULL_ptr, "", 0) == NULL_ptr + 0);
    C(T_stpncpy(NULL_ptr, "foobar", 0) == NULL_ptr + 0);

    memset(text, '\xee', 6);

    C(T_stpncpy(text, "1", 5) == text + 1);
    C(memcmp(text, "1\0\0\0\0\xee", 6) == 0);

    C(T_stpncpy(text, "1234", 5) == text + 4);
    C(memcmp(text, "1234\0\xee", 6) == 0);

    C(T_stpncpy(text, "12345", 5) == text + 5);
    C(memcmp(text, "12345\xee", 6) == 0);

    C(T_stpncpy(text, "123456", 5) == text + 5);
    C(memcmp(text, "12345\xee", 6) == 0);

    memset(text, '\xff', 6);

    C(T_stpncpy(text, "", 0) == text + 0);
    C(memcmp(text, "\xff\xff\xff\xff\xff\xff", 6) == 0);

    C(T_stpncpy(text, "123456", 1) == text + 1);
    C(memcmp(text, "1\xff\xff\xff\xff\xff", 6) == 0);

    C(T_stpncpy(text, "6", 1) == text + 1);
    C(memcmp(text, "6\xff\xff\xff\xff\xff", 6) == 0);

    C(T_stpncpy(text, "", 1) == text + 0);
    C(memcmp(text, "\0\xff\xff\xff\xff\xff", 6) == 0);

    C(T_stpncpy(text, "a", 2) == text + 1);
    C(memcmp(text, "a\0\xff\xff\xff\xff", 6) == 0);

    C(T_stpncpy(text, "", 5) == text + 0);
    C(memcmp(text, "\0\0\0\0\0\xff", 6) == 0);

    return 0;
}

int memmem_test(void) {
    const char str1[] = "abcdef123\0aababc123";
    const char str2[] = "wxyz";

    /* Test NULL */

    C(T_memmem(NULL_ptr, 0, NULL_ptr, 0) == NULL_ptr);
    C(T_memmem(NULL_ptr, 0, SINK, 0) == NULL_ptr);
    C(T_memmem(NULL_ptr, 0, SINK, 1) == NULL_ptr);
    C(T_memmem(NULL_ptr, 0, SINK, 2) == NULL_ptr);
    C(T_memmem(SINK, 0, NULL_ptr, 0) == SINK);
    C(T_memmem(SINK, 1, NULL_ptr, 0) == SINK);
    C(T_memmem(SINK, 2, NULL_ptr, 0) == SINK);

    /* Test same */

    C(T_memmem(SINK, 0, SINK, 0) == SINK);
    C(T_memmem(SINK, 1, SINK, 0) == SINK);
    C(T_memmem(SINK, 2, SINK, 0) == SINK);
    C(T_memmem(SINK, 0, SINK, 1) == NULL);
    C(T_memmem(SINK, 1, SINK, 1) == SINK);
    C(T_memmem(SINK, 2, SINK, 1) == SINK);
    C(T_memmem(SINK, 0, SINK, 2) == NULL);
    C(T_memmem(SINK, 1, SINK, 2) == NULL);
    C(T_memmem(SINK, 2, SINK, 2) == SINK);

    C(T_memmem(SINK, 300, SINK, 300) == SINK);
    C(T_memmem(SINK, 300, SINK, 301) == NULL);
    C(T_memmem(SINK, 300, SINK, 299) == SINK);
    C(T_memmem(SINK, 300, SINK, 30 ) == SINK);
    C(T_memmem(SINK,  30, SINK, 300) == NULL);

    C(T_memmem(SINK + 30, 60, SINK +  0, 60) == SINK + 30);
    C(T_memmem(SINK +  0, 60, SINK + 30, 60) == SINK +  0);
    C(T_memmem(SINK + 30, 60, SINK +  0, 59) == SINK + 30);
    C(T_memmem(SINK +  0, 60, SINK + 30, 59) == SINK +  0);

    C(T_memmem(str1, 20, str1,  0) == str1);
    C(T_memmem(str1, 20, str1,  1) == str1);
    C(T_memmem(str1, 20, str1,  2) == str1);
    C(T_memmem(str1, 20, str1,  3) == str1);
    C(T_memmem(str1, 20, str1,  9) == str1);
    C(T_memmem(str1, 20, str1, 10) == str1);
    C(T_memmem(str1, 20, str1, 19) == str1);
    C(T_memmem(str1, 20, str1, 20) == str1);

    /* Test different */

    C(T_memmem(str1, 0, SINK, 0) == str1);
    C(T_memmem(str1, 1, SINK, 0) == str1);
    C(T_memmem(str1, 2, SINK, 0) == str1);
    C(T_memmem(str1, 0, SINK, 1) == NULL);
    C(T_memmem(str1, 1, SINK, 1) == NULL);
    C(T_memmem(str1, 2, SINK, 1) == NULL);
    C(T_memmem(str1, 0, SINK, 2) == NULL);
    C(T_memmem(str1, 1, SINK, 2) == NULL);
    C(T_memmem(str1, 2, SINK, 2) == NULL);

    /* Other tests */

    C(T_memmem(str1 +  1, 19, "abc", 3) == str1 + 13);
    C(T_memmem(str1 +  0, 20, "123", 4) == str1 +  6);
    C(T_memmem(str1 +  7, 13, "123", 4) == str1 + 16);

    C(T_memmem(str1 +  0, 20, "aabaab", 6) == NULL);
    C(T_memmem(str1 +  0, 20, "\xff\x00\xff", 4) == NULL);
    C(T_memmem(str1 +  0, 20, "\xff", 1) == NULL);

    C(T_memmem(SINK, 300, "\xff", 1) == NULL);
    C(T_memmem(SINK, 300, "\xff\xff", 2) == NULL);
    C(T_memmem(SINK, 300, "\xff", 2) == NULL);
    C(T_memmem(SINK, 300, "\0\xff", 2) == NULL);

    C(T_memmem(str2 + 0, 5, "", 1) == str2 + 4);
    C(T_memmem(str2 + 4, 1, "", 1) == str2 + 4);
    C(T_memmem(str2 + 0, 5, "z", 1) == str2 + 3);
    C(T_memmem(str2 + 0, 5, "z", 2) == str2 + 3);
    C(T_memmem(str2 + 2, 5, "z", 1) == str2 + 3);
    C(T_memmem(str2 + 2, 5, "z", 2) == str2 + 3);
    C(T_memmem(str2 + 0, 3, "z", 1) == NULL);
    C(T_memmem(str2 + 0, 4, "z", 2) == NULL);
    C(T_memmem(str2 + 0, 5, "w", 1) == str2 + 0);
    C(T_memmem(str2 + 0, 5, "x", 1) == str2 + 1);
    C(T_memmem(str2 + 0, 5, "wx", 2) == str2 + 0);
    C(T_memmem(str2 + 0, 5, "xy", 2) == str2 + 1);
    C(T_memmem(str2 + 0, 5, "w", 2) == NULL);
    C(T_memmem(str2 + 0, 5, "x", 2) == NULL);
    C(T_memmem(str2 + 0, 5, "wx", 3) == NULL);
    C(T_memmem(str2 + 0, 5, "xy", 3) == NULL);

    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "a"         ,  1) == gnu_copypasta +  35);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "by"        ,  2) == gnu_copypasta + 286);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "GNU"       ,  3) == gnu_copypasta +  92);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "full"      ,  4) == gnu_copypasta + 245);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "linux"     ,  5) == NULL);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "Linux"     ,  5) == gnu_copypasta +  73);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "I would"   ,  7) == gnu_copypasta +   0);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "POSIX"     ,  5) == gnu_copypasta + 386);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "POsIX"     ,  5) == NULL);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "POSIX"     ,  6) == gnu_copypasta + 386);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), "system"    ,  6) == gnu_copypasta + 186);
    C(T_memmem(gnu_copypasta, sizeof(gnu_copypasta), " component", 10) == gnu_copypasta + 229);

    return 0;
}

int memrmem_test(void) {
    const char str1[] = "abcdef123\0aababc123";
    const char str2[] = "wxyz";

    /* Test NULL */

    C(T_memrmem(NULL_ptr, 0, NULL_ptr, 0) == NULL_ptr);
    C(T_memrmem(NULL_ptr, 0, SINK, 0) == NULL_ptr);
    C(T_memrmem(NULL_ptr, 0, SINK, 1) == NULL_ptr);
    C(T_memrmem(NULL_ptr, 0, SINK, 2) == NULL_ptr);
    C(T_memrmem(SINK, 0, NULL_ptr, 0) == SINK + 0);
    C(T_memrmem(SINK, 1, NULL_ptr, 0) == SINK + 0);
    C(T_memrmem(SINK, 2, NULL_ptr, 0) == SINK + 1);

    /* Test same */

    C(T_memrmem(SINK, 0, SINK, 0) == SINK + 0);
    C(T_memrmem(SINK, 1, SINK, 0) == SINK + 0);
    C(T_memrmem(SINK, 2, SINK, 0) == SINK + 1);
    C(T_memrmem(SINK, 0, SINK, 1) == NULL);
    C(T_memrmem(SINK, 1, SINK, 1) == SINK + 0);
    C(T_memrmem(SINK, 2, SINK, 1) == SINK + 1);
    C(T_memrmem(SINK, 0, SINK, 2) == NULL);
    C(T_memrmem(SINK, 1, SINK, 2) == NULL);
    C(T_memrmem(SINK, 2, SINK, 2) == SINK + 0);

    C(T_memrmem(SINK, 300, SINK, 300) == SINK);
    C(T_memrmem(SINK, 300, SINK, 301) == NULL);
    C(T_memrmem(SINK, 300, SINK, 299) == SINK + 1);
    C(T_memrmem(SINK, 300, SINK, 30 ) == SINK + 270);
    C(T_memrmem(SINK,  30, SINK, 300) == NULL);

    C(T_memrmem(SINK + 30, 60, SINK +  0, 60) == SINK + 30);
    C(T_memrmem(SINK +  0, 60, SINK + 30, 60) == SINK +  0);
    C(T_memrmem(SINK + 30, 60, SINK +  0, 59) == SINK + 31);
    C(T_memrmem(SINK +  0, 60, SINK + 30, 59) == SINK +  1);

    C(T_memrmem(str1, 20, str1,  0) == str1 + 20 -  1);
    C(T_memrmem(str1, 20, str1,  1) == str1 + 20 -  7);
    C(T_memrmem(str1, 20, str1,  2) == str1 + 20 -  7);
    C(T_memrmem(str1, 20, str1,  3) == str1 + 20 -  7);
    C(T_memrmem(str1, 15, str1,  3) == str1);
    C(T_memrmem(str1, 20, str1,  9) == str1);
    C(T_memrmem(str1, 20, str1, 10) == str1);
    C(T_memrmem(str1, 20, str1, 19) == str1);
    C(T_memrmem(str1, 20, str1, 20) == str1);

    /* Test different */

    C(T_memrmem(str1, 0, SINK, 0) == str1 + 0);
    C(T_memrmem(str1, 1, SINK, 0) == str1 + 0);
    C(T_memrmem(str1, 2, SINK, 0) == str1 + 1);
    C(T_memrmem(str1, 0, SINK, 1) == NULL);
    C(T_memrmem(str1, 1, SINK, 1) == NULL);
    C(T_memrmem(str1, 2, SINK, 1) == NULL);
    C(T_memrmem(str1, 0, SINK, 2) == NULL);
    C(T_memrmem(str1, 1, SINK, 2) == NULL);
    C(T_memrmem(str1, 2, SINK, 2) == NULL);

    /* Other tests */

    C(T_memrmem(str1 +  0, 20, "123", 4) == str1 + 16);
    C(T_memrmem(str1 +  6, 13, "123", 4) == str1 +  6);
    C(T_memrmem(str1 +  7, 13, "123", 4) == str1 + 16);
    C(T_memrmem(str1 +  0, 18, "123", 4) == str1 +  6);

    C(T_memrmem(str1 +  0, 20, "aabaab", 6) == NULL);
    C(T_memrmem(str1 +  0, 20, "\xff\x00\xff", 4) == NULL);
    C(T_memrmem(str1 +  0, 20, "\xff", 1) == NULL);

    C(T_memrmem(SINK, 300, "\xff", 1) == NULL);
    C(T_memrmem(SINK, 300, "\xff\xff", 2) == NULL);
    C(T_memrmem(SINK, 300, "\xff", 2) == NULL);
    C(T_memrmem(SINK, 300, "\0\xff", 2) == NULL);

    C(T_memrmem(str2 + 0, 5, "", 1) == str2 + 4);
    C(T_memrmem(str2 + 4, 1, "", 1) == str2 + 4);
    C(T_memrmem(str2 + 0, 5, "z", 1) == str2 + 3);
    C(T_memrmem(str2 + 0, 5, "z", 2) == str2 + 3);
    C(T_memrmem(str2 + 2, 5, "z", 1) == str2 + 3);
    C(T_memrmem(str2 + 2, 5, "z", 2) == str2 + 3);
    C(T_memrmem(str2 + 0, 3, "z", 1) == NULL);
    C(T_memrmem(str2 + 0, 4, "z", 2) == NULL);
    C(T_memrmem(str2 + 0, 5, "w", 1) == str2 + 0);
    C(T_memrmem(str2 + 0, 5, "x", 1) == str2 + 1);
    C(T_memrmem(str2 + 0, 5, "wx", 2) == str2 + 0);
    C(T_memrmem(str2 + 0, 5, "xy", 2) == str2 + 1);
    C(T_memrmem(str2 + 0, 5, "w", 2) == NULL);
    C(T_memrmem(str2 + 0, 5, "x", 2) == NULL);
    C(T_memrmem(str2 + 0, 5, "wx", 3) == NULL);
    C(T_memrmem(str2 + 0, 5, "xy", 3) == NULL);

    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "a"         ,  1) == gnu_copypasta +  372);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "by"        ,  2) == gnu_copypasta +  383);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "GNU"       ,  3) == gnu_copypasta +  293);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "full"      ,  4) == gnu_copypasta +  364);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "linux"     ,  5) == NULL);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "Linux"     ,  5) == gnu_copypasta +  160);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "I would"   ,  7) == gnu_copypasta +    0);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "POSIX"     ,  5) == gnu_copypasta +  386);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "POsIX"     ,  5) == NULL);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "POSIX"     ,  6) == gnu_copypasta +  386);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), "system"    ,  6) == gnu_copypasta +  333);
    C(T_memrmem(gnu_copypasta, sizeof(gnu_copypasta), " component", 10) == gnu_copypasta +  339);

    return 0;
}

int strstr_test(void) {
    const char str1[] = "abcdef123\0aababc123";

    C(T_strstr(SINK, SINK) == SINK);
    C(T_strstr(SINK, str1) == NULL);
    C(T_strstr(str1, SINK) == str1);
    C(T_strstr(str1, str1) == str1);

    C(T_strstr(str1 +  0, str1 + 6) == str1 +  6);
    C(T_strstr(str1 +  9, str1 + 9) == str1 +  9);
    C(T_strstr(str1 + 10, "ab") == str1 + 11);
    C(T_strstr(str1 + 10, "aa") == str1 + 10);
    C(T_strstr(str1 + 10, "b" ) == str1 + 12);
    C(T_strstr(str1 + 10, "ba") == str1 + 12);
    C(T_strstr(str1 + 10, "aac") == NULL);

    C(T_strstr(gnu_copypasta, ""          ) == gnu_copypasta +   0);
    C(T_strstr(gnu_copypasta, "a"         ) == gnu_copypasta +  35);
    C(T_strstr(gnu_copypasta, "by"        ) == gnu_copypasta + 286);
    C(T_strstr(gnu_copypasta, "GNU"       ) == gnu_copypasta +  92);
    C(T_strstr(gnu_copypasta, "full"      ) == gnu_copypasta + 245);
    C(T_strstr(gnu_copypasta, "linux"     ) == NULL);
    C(T_strstr(gnu_copypasta, "Linux"     ) == gnu_copypasta +  73);
    C(T_strstr(gnu_copypasta, "I would"   ) == gnu_copypasta +   0);
    C(T_strstr(gnu_copypasta, "POSIX"     ) == gnu_copypasta + 386);
    C(T_strstr(gnu_copypasta, "POsIX"     ) == NULL);
    C(T_strstr(gnu_copypasta, "system"    ) == gnu_copypasta + 186);
    C(T_strstr(gnu_copypasta, " component") == gnu_copypasta + 229);

    return 0;
}

int strrstr_test(void) {
    const char str1[] = "abcdef123\0aababc123";

    C(T_strrstr(SINK, SINK) == SINK);
    C(T_strrstr(SINK, str1) == NULL);
    C(T_strrstr(str1, SINK) == str1 + 8);
    C(T_strrstr(str1, str1) == str1);

    C(T_strrstr(str1 +  0, str1 + 6) == str1 +  6);
    C(T_strrstr(str1 +  9, str1 + 9) == str1 +  9);
    C(T_strrstr(str1 + 10, "ab") == str1 + 13);
    C(T_strrstr(str1 + 10, "aa") == str1 + 10);
    C(T_strrstr(str1 + 10, "b" ) == str1 + 14);
    C(T_strrstr(str1 + 10, "ba") == str1 + 12);
    C(T_strrstr(str1 + 10, "aac") == NULL);

    C(T_strrstr(gnu_copypasta, ""          ) == gnu_copypasta +  390);
    C(T_strrstr(gnu_copypasta, "a"         ) == gnu_copypasta +  372);
    C(T_strrstr(gnu_copypasta, "by"        ) == gnu_copypasta +  383);
    C(T_strrstr(gnu_copypasta, "GNU"       ) == gnu_copypasta +  293);
    C(T_strrstr(gnu_copypasta, "full"      ) == gnu_copypasta +  364);
    C(T_strrstr(gnu_copypasta, "linux"     ) == NULL);
    C(T_strrstr(gnu_copypasta, "Linux"     ) == gnu_copypasta +  160);
    C(T_strrstr(gnu_copypasta, "I would"   ) == gnu_copypasta +    0);
    C(T_strrstr(gnu_copypasta, "POSIX"     ) == gnu_copypasta +  386);
    C(T_strrstr(gnu_copypasta, "POsIX"     ) == NULL);
    C(T_strrstr(gnu_copypasta, "system"    ) == gnu_copypasta +  333);
    C(T_strrstr(gnu_copypasta, " component") == gnu_copypasta +  339);

    return 0;
}

int strchrnul_test(void) {
    const char one_char[] = "S";

    C(T_strchr(SINK, '\0') == SINK);
    C(T_strchr(SINK, '\xff') == NULL);
    C(T_strchr(one_char, 'S') == one_char);
    C(T_strchr(one_char, 's') == NULL);
    C(T_strchr(one_char, '\0') == one_char + 1);

    C(T_strrchr(SINK, '\0') == SINK);
    C(T_strrchr(SINK, '\xff') == NULL);
    C(T_strrchr(one_char, 'S') == one_char);
    C(T_strrchr(one_char, 's') == NULL);
    C(T_strrchr(one_char, '\0') == one_char + 1);

    C(T_strchrnul(SINK, '\0') == SINK);
    C(T_strchrnul(SINK, '\xff') == SINK);
    C(T_strchrnul(one_char, 'S') == one_char);
    C(T_strchrnul(one_char, 's') == one_char + 1);
    C(T_strchrnul(one_char, '\0') == one_char + 1);

    C(T_strchr(gnu_copypasta, '\0') == gnu_copypasta + 391);
    C(T_strchr(gnu_copypasta, 'a') == gnu_copypasta + 35);
    C(T_strchr(gnu_copypasta, 'A') == NULL);
    C(T_strrchr(gnu_copypasta, '\0') == gnu_copypasta + 391);
    C(T_strrchr(gnu_copypasta, 'a') == gnu_copypasta + 372);
    C(T_strrchr(gnu_copypasta, 'A') == NULL);

    const size_t test_3_len = strlen(test_3);
    C(T_strchrnul(test_3, '\0') == test_3 + test_3_len);
    for (size_t i = 0; i < test_3_len; i++) {
        C(T_strchrnul(test_3, test_3[i]) == strchr(test_3, test_3[i]));
    }
    return 0;
}

int strtok_test(void) {
    const char input_empty[] = "\x00\xff";
    const char truth_empty[] = "\x00\xff";
    const char input_text[] = "?a???b,,,#c";
    const char truth_text[] = "?a\0??b\0,,#c";
    const char input_str[] = "A bird came... down the walk";
    const char truth_str[] = "A\0bird\0came\0.. down\0the\0walk";
    const char delim[] = " .,";
    char empty[sizeof(input_empty)];
    char text[sizeof(input_text)];
    char str[sizeof(input_str)];

    /* strtok */ {
        char *token;
        memcpy(empty, input_empty, sizeof(input_empty));
        strcpy(text, input_text);
        strcpy(str, input_str);

        token = T_strtok(empty, "");
        C(token == NULL);

        token = T_strtok(NULL, "");
        C(token == NULL);

        C(T_memcmp(empty, truth_empty, sizeof(truth_empty)) == 0);

        // token points to the token "a"
        token = T_strtok(text, "?");
        C(token == text + 1);
        C(strcmp_exact(token, "a"));

        // token points to the token "??b"
        token = T_strtok(NULL, ",");
        C(token == text + 3);
        C(strcmp_exact(token, "??b"));

        // token points to the token "c"
        token = T_strtok(NULL, "#,");
        C(token == text + 10);
        C(strcmp_exact(token, "c"));

        // token is a null pointer
        token = T_strtok(NULL, "?");
        C(token == NULL);

        C(T_memcmp(text, truth_text, sizeof(truth_text)) == 0);

        strcpy(str, input_str);

        token = strtok(str , delim);
        C(token == str + 0);

        token = strtok(NULL, delim);
        C(token == str + 2);

        token = strtok(NULL, delim);
        C(token == str + 7);

        token = strtok(NULL, delim);
        C(token == str + 15);

        token = strtok(NULL, delim);
        C(token == str + 20);

        token = strtok(NULL, delim);
        C(token == str + 24);

        token = strtok(NULL, delim);
        C(token == NULL);

        C(T_memcmp(str, truth_str, sizeof(truth_str)) == 0);
    }

    /* strtok_r */ {
        char *save_ptr;
        char *token;
        memcpy(empty, input_empty, sizeof(input_empty));
        strcpy(text, input_text);
        strcpy(str, input_str);

        token = T_strtok_r(empty, "", &save_ptr);
        C(token == NULL);
        C(save_ptr == empty);

        token = T_strtok_r(NULL, "", &save_ptr);
        C(token == NULL);
        C(save_ptr == empty);

        C(T_memcmp(empty, truth_empty, sizeof(truth_empty)) == 0);

        // token points to the token "a"
        token = T_strtok_r(text, "?", &save_ptr);
        C(token == text + 1);
        C(strcmp_exact(token, "a"));
        C(save_ptr == text + 3);

        // token points to the token "??b"
        token = T_strtok_r(NULL, ",", &save_ptr);
        C(token == text + 3);
        C(strcmp_exact(token, "??b"));
        C(save_ptr == text + 7);

        // token points to the token "c"
        token = T_strtok_r(NULL, "#,", &save_ptr);
        C(token == text + 10);
        C(strcmp_exact(token, "c"));
        C(save_ptr == text + 11);

        // token is a null pointer
        token = T_strtok_r(NULL, "?", &save_ptr);
        C(token == NULL);
        C(save_ptr == text + 11);

        C(T_memcmp(text, truth_text, sizeof(truth_text)) == 0);

        token = T_strtok_r(str , delim, &save_ptr);
        C(token == str + 0);
        C(save_ptr == str + 2);

        token = T_strtok_r(NULL, delim, &save_ptr);
        C(token == str + 2);
        C(save_ptr == str + 7);

        token = T_strtok_r(NULL, delim, &save_ptr);
        C(token == str + 7);
        C(save_ptr == str + 12);

        token = T_strtok_r(NULL, delim, &save_ptr);
        C(token == str + 15);
        C(save_ptr == str + 20);

        token = T_strtok_r(NULL, delim, &save_ptr);
        C(token == str + 20);
        C(save_ptr == str + 24);

        token = T_strtok_r(NULL, delim, &save_ptr);
        C(token == str + 24);
        C(save_ptr == str + 28);

        token = T_strtok_r(NULL, delim, &save_ptr);
        C(token == NULL);
        C(save_ptr == str + 28);

        C(T_memcmp(str, truth_str, sizeof(truth_str)) == 0);
    }
    return 0;
}

int mem65536_test(void) {
    void fill_mem32(void *dst, size_t bytes, uint32_t pattern);

    uint8_t * const dst = (uint8_t*)0xD40000;
    const size_t screen_size = 320 * 240 * 2;
    memset(dst, 0, screen_size);
    const size_t B16 = 65536;
    const size_t B17 = 131072;

    /* test return values */

    C(T_memcpy(SINK, SINK, B16) == SINK);
    C(T_memcpy(SINK, SINK, B17) == SINK);

    C(T_memmove(SINK, SINK, B16) == SINK);
    C(T_memmove(SINK, SINK, B17) == SINK);

    C(T_memmove(SINK + 16, SINK, B16) == SINK + 16);
    C(T_memmove(SINK + 16, SINK, B17) == SINK + 16);

    C(T_memmove(SINK, SINK + 16, B16) == SINK);
    C(T_memmove(SINK, SINK + 16, B17) == SINK);

    /* test memcpy and memmove when size is a non-zero multiple of 65536 */

    fill_mem32(dst + screen_size - B16, B16, 0x78563412);
    C(T_memcpy(dst + 32, dst + screen_size - B16, B16) == dst + 32);
    C(T_memchr(dst, 0x00, 32) == dst);
    C(T_memchr(dst, 0x12, 32) == NULL_ptr);
    C(T_memchr(dst, 0x12, 33) == dst + 32);
    C(T_memrchr(dst, 0x78, 32 + B16 + 32) == dst + 32 + B16 - 1);
    const uint32_t pattern_1 = 0xA3A0A1A0;
    const uint32_t pattern_2 = 0xFECDAB89;
    fill_mem32(dst, 32, pattern_1);
    fill_mem32(dst + 24576, B16, pattern_2);

    C(T_memmove(dst + 61, dst, B16) == dst + 61);
    C(T_memmem(dst, B17, &pattern_1, sizeof(pattern_1)) == dst);
    C(T_memrmem(dst, B17, &pattern_1, sizeof(pattern_1)) == dst + 61 - 4 + 32);
    C(T_memmove(dst + 24578, dst, B16) == dst + 24578);
    C(T_memmem(dst, B16, &pattern_1, sizeof(pattern_1)) ==  dst + 0);
    C(T_memrmem(dst, B16, &pattern_1, sizeof(pattern_1)) == dst + 24578 + 61 + 32 - 4);
    C(T_memmem(dst, B16, &pattern_2, sizeof(pattern_2)) ==  dst + 24576 + 24578 + 61);
    C(T_memrmem(dst, B16, &pattern_2, sizeof(pattern_2)) == dst + B16 - 4u - (((24578u - 24576u) - 61u) % 4u));

    return 0;
}

int run_tests(void) {
    int ret = 0;
    /* boot_asprintf */
        ret = boot_sprintf_tests();
        free(buf); buf = NULL;
        if (ret != 0) { return ret; }

    /* nano_asprintf */
        ret = nano_tests();
        free(buf); buf = NULL;
        if (ret != 0) { return ret; }

    /* nano_fprintf memccpy */
        ret = memccpy_tests();
        free(buf); buf = NULL;
        fclose(file);
        if (remove(file_name) != 0) {
            perror("Couldn't delete file");
        }
        if (ret != 0) { return ret; }

    TEST(mempcpy_test());
    TEST(bzero_test());
    TEST(strncmp_test());
    TEST(memchr_test());
    TEST(memrchr_test());
    TEST(memmove_test());
    TEST(strcpy_test());
    TEST(strcat_test());
    TEST(strncat_test());
    TEST(strlcat_test());
    TEST(strncpy_test());
    TEST(stpncpy_test());
    TEST(memmem_test());
    TEST(memrmem_test());
    TEST(strstr_test());
    TEST(strrstr_test());
    TEST(strchrnul_test());
    TEST(strtok_test());

    TEST(mem65536_test());
    os_ClrHome();

    return 0;
}

int main(void)
{
    os_ClrHome();
    int ret = run_tests();
    if (ret != 0) {
        printf("Failed test L%d\n", ret);
    } else {
        #if 1
            fprintf(stdout, "All tests %s", "passed");
        #else
            printf("All tests %s", "passed");
        #endif
    }

    while (!os_GetCSC());

    return 0;
}
