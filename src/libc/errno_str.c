#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ti/sprintf.h>

static char const * const errno_strings[] = {
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

static char * const unknown_errno_string = "unknown error -8388608";

#define unknown_errno_number_offset 14
#if 0
/* static_assert on a string is a Clang 16.0.0 extension */
static_assert(
    unknown_errno_string[unknown_errno_number_offset + 0] == '-' &&
    unknown_errno_string[unknown_errno_number_offset + 8] == '\0',
    "the string for unknown errno numbers has been changed"
);
#endif

#define errno_strings_count (sizeof(errno_strings) / sizeof(errno_strings[0]))

char *strerror(int errnum)
{
    if ((unsigned int)errnum >= errno_strings_count)
    {
        boot_sprintf(&(unknown_errno_string[unknown_errno_number_offset]), "%d", errnum);
        return (char*)unknown_errno_string;
    }

    return (char*)errno_strings[errnum];
}

void perror(const char *str) {
    /* Normally this would print to stderr, but since they are handled the same and pulling */
    /* in fputs would create a dependency on fileioc, just use puts rather than fputs here */

    if (str != NULL && *str != '\0') {
        while (*str)
        {
            putchar(*str++);
        }
        putchar(':');
        putchar(' ');
    }
    puts(strerror(errno));
}
