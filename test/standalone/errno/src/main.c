#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

/** @note assumes that the following strings are used: */
static char const * const truth[] = {
    "no error",
    "EPERM",
    "EINVAL",
    "EIO",
    "EDOM",
    "ERANGE",
    "EILSEQ",
    /* C++ errno */
    "E2BIG",
    "EACCES",
    "EADDRINUSE",
    "EADDRNOTAVAIL",
    "EAFNOSUPPORT",
    "EAGAIN",
    "EALREADY",
    "EBADF",
    "EBADMSG",
    "EBUSY",
    "ECANCELED",
    "ECHILD",
    "ECONNABORTED",
    "ECONNREFUSED",
    "ECONNRESET",
    "EDEADLK",
    "EDESTADDRREQ",
    "EEXIST",
    "EFAULT",
    "EFBIG",
    "EHOSTUNREACH",
    "EIDRM",
    "EINPROGRESS",
    "EINTR",
    "EISCONN",
    "EISDIR",
    "ELOOP",
    "EMFILE",
    "EMLINK",
    "EMSGSIZE",
    "ENAMETOOLONG",
    "ENETDOWN",
    "ENETRESET",
    "ENETUNREACH",
    "ENFILE",
    "ENOBUFS",
    "ENODATA",
    "ENODEV",
    "ENOENT",
    "ENOEXEC",
    "ENOLCK",
    "ENOLINK",
    "ENOMEM",
    "ENOMSG",
    "ENOPROTOOPT",
    "ENOSPC",
    "ENOSR",
    "ENOSTR",
    "ENOSYS",
    "ENOTCONN",
    "ENOTDIR",
    "ENOTEMPTY",
    "ENOTRECOVERABLE",
    "ENOTSOCK",
    "ENOTSUP",
    "ENOTTY",
    "ENXIO",
    "EOPNOTSUPP",
    "EOVERFLOW",
    "EOWNERDEAD",
    "EPIPE",
    "EPROTO",
    "EPROTONOSUPPORT",
    "EPROTOTYPE",
    "EROFS",
    "ESPIPE",
    "ESRCH",
    "ETIME",
    "ETIMEDOUT",
    "ETXTBSY",
    "EWOULDBLOCK",
    "EXDEV",
};

int main(void)
{
    os_ClrHome();

    errno = 0; perror(NULL);
    errno = 1; perror("");
    errno = 2; perror("\0");
    errno = 3; perror(" ");
    errno = 4; perror("%*.*d%n");
    errno = 5; perror("perror");
    errno = 6; perror(NULL);

    while (!os_GetCSC());

    os_ClrHome();

    errno = ARRAY_LENGTH(truth) - 1; perror("\\");
    errno = ARRAY_LENGTH(truth); perror(NULL);
    errno = -1; perror("");
    errno = -123456; perror("%*.*d%n");
    errno = 123456; perror("???");
    errno = INT_MIN; perror(" ");
    errno = INT_MAX; perror("#");

    for (size_t i = 0; i < ARRAY_LENGTH(truth); i++) {
        const char * str = strerror(i);
        errno = (int)i;
        if (strlen(truth[i]) != strlen(str) || strcmp(truth[i], str) != 0) {
            puts("strerror failed");
            break;
        }
    }
    puts("finished");

    while (!os_GetCSC());

    return 0;
}
