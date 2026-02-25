#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ti/sprintf.h>

static constexpr char errno_strings[] = {
    "no error"
    "\0" "EPERM"
    "\0" "EINVAL"
    "\0" "EIO"
    "\0" "EDOM"
    "\0" "ERANGE"
    "\0" "EILSEQ"
    /* C++ errno */
    "\0" "E2BIG"
    "\0" "EACCES"
    "\0" "EADDRINUSE"
    "\0" "EADDRNOTAVAIL"
    "\0" "EAFNOSUPPORT"
    "\0" "EAGAIN"
    "\0" "EALREADY"
    "\0" "EBADF"
    "\0" "EBADMSG"
    "\0" "EBUSY"
    "\0" "ECANCELED"
    "\0" "ECHILD"
    "\0" "ECONNABORTED"
    "\0" "ECONNREFUSED"
    "\0" "ECONNRESET"
    "\0" "EDEADLK"
    "\0" "EDESTADDRREQ"
    "\0" "EEXIST"
    "\0" "EFAULT"
    "\0" "EFBIG"
    "\0" "EHOSTUNREACH"
    "\0" "EIDRM"
    "\0" "EINPROGRESS"
    "\0" "EINTR"
    "\0" "EISCONN"
    "\0" "EISDIR"
    "\0" "ELOOP"
    "\0" "EMFILE"
    "\0" "EMLINK"
    "\0" "EMSGSIZE"
    "\0" "ENAMETOOLONG"
    "\0" "ENETDOWN"
    "\0" "ENETRESET"
    "\0" "ENETUNREACH"
    "\0" "ENFILE"
    "\0" "ENOBUFS"
    "\0" "ENODATA"
    "\0" "ENODEV"
    "\0" "ENOENT"
    "\0" "ENOEXEC"
    "\0" "ENOLCK"
    "\0" "ENOLINK"
    "\0" "ENOMEM"
    "\0" "ENOMSG"
    "\0" "ENOPROTOOPT"
    "\0" "ENOSPC"
    "\0" "ENOSR"
    "\0" "ENOSTR"
    "\0" "ENOSYS"
    "\0" "ENOTCONN"
    "\0" "ENOTDIR"
    "\0" "ENOTEMPTY"
    "\0" "ENOTRECOVERABLE"
    "\0" "ENOTSOCK"
    "\0" "ENOTSUP"
    "\0" "ENOTTY"
    "\0" "ENXIO"
    "\0" "EOPNOTSUPP"
    "\0" "EOVERFLOW"
    "\0" "EOWNERDEAD"
    "\0" "EPIPE"
    "\0" "EPROTO"
    "\0" "EPROTONOSUPPORT"
    "\0" "EPROTOTYPE"
    "\0" "EROFS"
    "\0" "ESPIPE"
    "\0" "ESRCH"
    "\0" "ETIME"
    "\0" "ETIMEDOUT"
    "\0" "ETXTBSY"
    "\0" "EWOULDBLOCK"
    "\0" "EXDEV"
};

static constexpr size_t count_errno_strings(const char *str, size_t size)
{
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (str[i] == '\0') {
            ++count;
        }
    }
    return count;
}

static constexpr int errno_strings_count = count_errno_strings(errno_strings, sizeof(errno_strings));

static constexpr size_t unknown_errno_number_offset = 14;
#define UNKNOWN_ERRNO_STRING "unknown error -8388608"
static char unknown_errno_string[] = UNKNOWN_ERRNO_STRING;

static_assert(
    UNKNOWN_ERRNO_STRING[unknown_errno_number_offset + 0] == '-' &&
    UNKNOWN_ERRNO_STRING[unknown_errno_number_offset + 8] == '\0',
    "the string for unknown errno numbers has been changed"
);

char *strerror(int errnum)
{
    if (errnum < 0 || errnum >= errno_strings_count) {
        boot_sprintf(&unknown_errno_string[unknown_errno_number_offset], "%d", errnum);
        return const_cast<char*>(unknown_errno_string);
    }
    const char* ret = errno_strings;
    // worst case retrieval takes ~0.8ms (79 strings)
    for (int i = 0; i < errnum; i++) {
        // skips to the start of the next string
        ret += strlen(ret) + 1;
    }
    return const_cast<char*>(ret);
}

void perror(const char *str)
{
    /* Normally this would print to stderr, but since they are handled the same and pulling */
    /* in fputs would create a dependency on fileioc, just use puts rather than fputs here */

    if (str != nullptr && *str != '\0') {
        while (*str) {
            putchar(*str++);
        }
        putchar(':');
        putchar(' ');
    }
    puts(strerror(errno));
}
