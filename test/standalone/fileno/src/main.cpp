#include <stdbool.h>
#include <stdio.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <sys/util.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <algorithm>

#define C(expr) if (!(expr)) { return __LINE__; }

static const char *name_1 = "foo1";
static const char *name_2 = "bar2";

constexpr int FILEIOC_SLOT_COUNT = 5;
constexpr int MIN_FILEIOC_SLOT = 1 + std::max(STDIN_FILENO, std::max(STDOUT_FILENO, STDERR_FILENO));
constexpr int MAX_FILEIOC_SLOT = MIN_FILEIOC_SLOT + (FILEIOC_SLOT_COUNT - 1);

static bool is_fileioc_fd(int fd) {
    if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        return false;
    }
    return (fd >= MIN_FILEIOC_SLOT && fd <= MAX_FILEIOC_SLOT);
}

int run_tests(void) {

    // create some files
    FILE *file_1 = fopen(name_1, "w");
    C(file_1 != NULL);
    FILE *file_2 = fopen(name_2, "a+");
    C(file_2 != NULL);

    C(errno == 0);

    // test fileno

    int fileno_1 = fileno(file_1);
    C(is_fileioc_fd(fileno_1));
    int fileno_2 = fileno(file_2);
    C(is_fileioc_fd(fileno_2));

    C(fileno_1 != fileno_2);
    C(errno == 0);

    int fileno_stdin = fileno(stdin);
    int fileno_stdout = fileno(stdout);
    int fileno_stderr = fileno(stderr);

    C(fileno_stdin == STDIN_FILENO);
    C(fileno_stdout == STDOUT_FILENO);

    // we current define stdout to be stderr
    if (stdout != stderr) {
        C(fileno_stderr == STDERR_FILENO);
    } else {
        C(fileno_stderr == STDOUT_FILENO);
    }
    C(errno == 0);

    int fileno_nullptr = fileno(nullptr);
    C(fileno_nullptr == -1);
    C(errno == EBADF);

    errno = 0;

    // we currently treat stdin/stdout/stderr as a tty/terminal
    C(isatty(fileno_stdin) == 1);
    C(isatty(fileno_stdout) == 1);
    C(isatty(fileno_stderr) == 1);
    C(errno == 0);

    // test invalid fd
    C(isatty(-1) == 0);
    C(errno == EBADF);
    errno = 0;
    C(isatty(MAX_FILEIOC_SLOT + 1) == 0);
    C(errno == EBADF);
    errno = 0;

    // test valid fd that are not a terminal
    C(isatty(fileno_1) == 0);
    C(errno == ENOTTY);
    errno = 0;
    C(isatty(fileno_2) == 0);
    C(errno == ENOTTY);
    errno = 0;

    // remove the files
    C(fclose(file_1) == 0);
    file_1 = fopen(name_1, "r+");
    C(file_1 != NULL);
    C(fclose(file_2) == 0);
    C(remove(name_2) == 0);
    C(fclose(file_1) == 0);
    C(remove(name_1) == 0);
    C(errno == 0);

    // attempt to read a removed file
    file_1 = fopen(name_1, "r");
    C(file_1 == NULL);

    // discard errno value
    errno = 0;

    return 0;
}

extern "C" int main(void) {
    os_ClrHome();
    errno = 0;
    int failed_test = run_tests();
    if (errno != 0) {
        perror("errno");
    }
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
