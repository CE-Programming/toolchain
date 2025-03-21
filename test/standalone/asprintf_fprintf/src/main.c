#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti_sprintf.h>
#include <ctype.h>

/**
 * @brief Tests the following functions/macros:
 * ti_sprintf
 * ti_snprintf
 * ti_asprintf
 * asprintf
 * fprintf
 * stpcpy
 * memccpy
 */

static char const * const test_1 =
"+123 asprintf% 076543 0x9abcd  0XFE1 0\n";
static char const * const test_2 =
"+123 asprintf% 076543 0x9abcd  0XFE1 0\nfoo";
static const int pos_1 = 30;
static const int pos_2 = 42;

static char* buf = NULL;
static FILE* file = NULL;

int ti_tests(void) {
    int pos;
    int len = ti_asprintf(
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
    size_t buf_len = strlen(buf);
    if (buf_len != strlen(test_1) || buf_len != (size_t)len) {
        printf("E: %zu != %zu != %d\n", strlen(test_1), buf_len, len);
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
    int snprintf_test = ti_snprintf(append, 20, "%s", test_1);
    if (snprintf_test >= 0) {
        printf("sprintf_test: %d\n", snprintf_test);
        return __LINE__;
    }
    int len_2 = ti_snprintf(append, sizeof(append), "%s", test_1);
    if (len_2 != strlen(test_1)) {
        printf("E: %d != %zu\n", len_2, strlen(test_1));
        return __LINE__;
    }
    char str2[128];
    char* end;
    end = stpcpy(str2, append);
    end = stpcpy(end, "");
    end = stpcpy(end, "foo");
    if (*end != '\0') {
        return __LINE__;
    }
    if (end != &str2[pos_2]) {
        printf("diff %p - %p = %td\n", end, str2, (ptrdiff_t)(end - str2));
        return __LINE__;
    }
    int cmp2 = strcmp(str2, test_2);
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
    size_t buf_len = strlen(buf);
    if (buf_len != strlen(test_1) || buf_len != (size_t)len) {
        printf("E: %zu != %zu != %d\n", strlen(test_1), buf_len, len);
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

static void get_diff_char(const char* buf, const char* test) {
    size_t char_pos = 0;
    char prev = '\0';
    while (*buf != '\0' && *test != '\0') {
        if (*buf != *test) {
            printf("prev %02X: %02X != %02X at %zu\n", prev, *buf, *test, char_pos);
            break;
        }
        prev = *buf;
        buf++;
        test++;
        char_pos++;
    }
}

int memccpy_tests(void) {
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
        void* to = memccpy(dest, src, terminal[i], sizeof dest);
 
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
            first = memccpy(first, star_distance[t], ' ', last - first);
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

    int alloc_size = (int)ftell(file);
    buf = (char*)calloc(alloc_size + 2, sizeof(char));
    if (buf == NULL) {
        perror("calloc failure");
        return __LINE__;
    }

    size_t bytes_read = fread(buf, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        perror("Error reading from file");
        return __LINE__;
    }
    if (strlen(buf) != strlen(fprintf_test)) {
        printf("E: %zu != %zu\n", strlen(buf), strlen(fprintf_test));
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

int run_tests(void) {
    int ret = 0;
    /* ti_asprintf */
        ret = ti_tests();
        free(buf); buf = NULL;
        if (ret != 0) { return ret; }

    /* nano_asprintf */
        ret = nano_tests();
        free(buf); buf = NULL;
        if (ret != 0) { return ret; }

    /* nano_fprintf */
        ret = memccpy_tests();
        free(buf); buf = NULL;
        fclose(file);
        if (remove(file_name) != 0) {
            perror("Couldn't delete file");
        }
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
        fprintf(stdout, "All tests %s", "passed");
    }
    
    while (!os_GetCSC());

    return 0;
}
