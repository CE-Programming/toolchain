#include <stdbool.h>
#include <stdio.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <sys/util.h>
#include <fileioc.h>
#include <errno.h>
#include <stdint.h>

#define C(expr) if (!(expr)) { return __LINE__; }
#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

static const char *name0 = "foo1";
static const char *name1 = "bar2";
static const char *name2 = "foobar3";

int test_fileioc_rename(void) {
    uint8_t test_fileioc;
    uint8_t other_fileioc;

    test_fileioc = ti_Open(name0, "w");
    other_fileioc = ti_Open(name2, "w");

    C(test_fileioc != 0);
    C(other_fileioc != 0);

    // close out of order

    C(ti_Close(other_fileioc) != 0);
    C(ti_Close(test_fileioc) != 0);

    // test renames

    // old name doesn't exist
    C(ti_Rename(name1, name0) != 0);

    // new name already exists
    C(ti_Rename(name0, name2) != 0);

    // valid rename
    C(ti_Rename(name0, name1) == 0);

    // delete a file that doesn't exist
    C(ti_Delete(name0) == 0);

    // delete a valid file
    C(ti_Delete(name1) != 0);

    // delete the same file again
    C(ti_Delete(name1) == 0);

    // delete a valid file
    C(ti_Delete(name2) != 0);

    return 0;
}

int test_stdio_rename(void) {
    FILE *test_stdio;
    FILE *other_stdio;

    test_stdio = fopen(name0, "w");
    other_stdio = fopen(name2, "w");

    C(test_stdio != NULL);
    C(other_stdio != NULL);

    C(fclose(other_stdio) == 0);
    C(fclose(test_stdio) == 0);

    // old name doesn't exist
    C(rename(name1, name0) != 0);

    // new name already exists
    C(rename(name0, name2) != 0);

    // valid rename
    C(rename(name0, name1) == 0);

    // delete a file that doesn't exist
    C(remove(name0) != 0);

    // delete a valid file
    C(remove(name1) == 0);

    // delete the same file again
    C(remove(name1) != 0);

    // delete a valid file
    C(remove(name2) == 0);

    return 0;
}

int run_tests(void) {
    int ret = 0;

    TEST(test_fileioc_rename());
    TEST(test_stdio_rename());

    return ret;
}

int main(void) {
    os_ClrHome();
    errno = 0;
    int failed_test = run_tests();
    if (errno != 0) {
        perror(NULL);
    }
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
