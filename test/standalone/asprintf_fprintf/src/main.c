#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <boot_sprintf.h>
#include <ctype.h>

/**
 * @brief Tests the following functions/macros:
 * boot_sprintf
 * boot_snprintf
 * boot_asprintf
 * asprintf
 * fprintf
 * stpcpy
 * memccpy
 */

// prevents Clang from replacing function calls with builtins
#if 1

void *T_memcpy(void *__restrict dest, const void *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_memset(void *s, int c, size_t n)
    __attribute__((nonnull(1)));

int T_memcmp(const void *s1, const void *s2, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_memccpy(void *__restrict dest, const void *__restrict src, int c, size_t n)
    __attribute__((nonnull(1, 2)));

void *T_mempcpy(void *__restrict dest, const void *__restrict src, size_t n)
    __attribute__((nonnull(1, 2)));

char *T_stpcpy(char *__restrict dest, const char *__restrict src)
    __attribute__((nonnull(1, 2)));

size_t T_strlen(const char *s)
    __attribute__((nonnull(1)));

int T_strcmp(const char *s1, const char *s2)
    __attribute__((nonnull(1, 2)));

#else

#define T_memcpy memcpy
#define T_memset memset
#define T_memcmp memcmp
#define T_memccpy memccpy
#define T_mempcpy mempcpy
#define T_stpcpy stpcpy
#define T_strlen strlen
#define T_strcmp strcmp

#endif

static char const * const test_1 =
"+123 asprintf% 076543 0x9abcd  0XFE1 0\n";
static char const * const test_2 =
"+123 asprintf% 076543 0x9abcd  0XFE1 0\nfoo";
static const int pos_1 = 30;
static const int pos_2 = 42;

static char* buf = NULL;
static FILE* file = NULL;

int boot_sprintf_tests(void) {
    int pos;
    int len = boot_asprintf(
        &buf, "%+d %s%% %#o %#x %n %#X %i\n",
        123, "asprintf", 076543, 0x9abcd, &pos, 0xFE1, 0
    );
    if (buf == NULL || len <= 0) {
        printf("buf %p len %d\n", buf, len);
        return __LINE__;
    }
    if (buf[len] != '\0') {
        return __LINE__;
    }
    size_t buf_len = T_strlen(buf);
    if (buf_len != T_strlen(test_1) || buf_len != (size_t)len) {
        printf("E: %zu != %zu != %d\n", T_strlen(test_1), buf_len, len);
        return __LINE__;
    }
    if (pos != pos_1) {
        printf("E: %d != %d\n", pos, pos_1);
        return __LINE__;
    }
    int cmp = strcmp(buf, test_1);
    if (cmp != 0) {
        printf("cmp: %d\n", cmp);
        return __LINE__;
    }
    char append[128];
    int snprintf_test = boot_snprintf(append, 20, "%s", test_1);
    if (snprintf_test >= 0) {
        printf("sprintf_test: %d\n", snprintf_test);
        return __LINE__;
    }
    int len_2 = boot_snprintf(append, sizeof(append), "%s", test_1);
    if (len_2 != (int)T_strlen(test_1)) {
        printf("E: %d != %zu\n", len_2, T_strlen(test_1));
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
        printf("diff %p - %p = %td\n", end, str2, (ptrdiff_t)(end - str2));
        return __LINE__;
    }
    int cmp2 = T_strcmp(str2, test_2);
    if (cmp2 != 0) {
        printf("cmp: %d\n", cmp2);
        return __LINE__;
    }
    return 0;
}

int nano_tests(void) {
    int pos;
    int len = asprintf(
        &buf, "%+d %s%% %#o %#x %n %#X %i\n",
        123, "asprintf", 076543, 0x9abcd, &pos, 0xFE1, 0
    );
    if (buf == NULL || len <= 0) {
        printf("buf %p len %d\n", buf, len);
        return __LINE__;
    }
    if (buf[len] != '\0') {
        return __LINE__;
    }
    size_t buf_len = T_strlen(buf);
    if (buf_len != T_strlen(test_1) || buf_len != (size_t)len) {
        printf("E: %zu != %zu != %d\n", T_strlen(test_1), buf_len, len);
        return __LINE__;
    }
    if (pos != pos_1) {
        printf("E: %d != %d\n", pos, pos_1);
        return __LINE__;
    }
    int cmp = T_strcmp(buf, test_1);
    if (cmp != 0) {
        printf("cmp: %d\n", cmp);
        return __LINE__;
    }
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
        printf("%p != NULL\n", ptr);
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
        printf("%p != %p\n", ptr, (void*)0xC0FFEE);
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
        printf("%p != %p\n", res, &data[128]);
        return __LINE__;
    }

    char truth[192 + 1];
    T_memset(&truth[  0], 0x12, 64);
    T_memset(&truth[ 64], 0x34, 64);
    T_memset(&truth[128], 0x56, 64);

    int cmp = T_memcmp(data, truth, 192);
    if (cmp != 0) {
        printf("cmp: %d\n", cmp);
        return __LINE__;
    }
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

    /* mempcpy */
        ret = mempcpy_test();
        if (ret != 0) { return ret; }

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
