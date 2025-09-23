#ifndef _ERRNO_H
#define _ERRNO_H

#define EPERM       1   /* permission error */
#define EINVAL      2   /* invalid argument */
#define EIO         3   /* io error */
#define EDOM        4   /* math domain error */
#define ERANGE      5   /* math range error */

// Not used, but defined for compatibility
#define E2BIG           6 /* Argument list too long */
#define EACCES          7 /* Permission denied */
#define EADDRINUSE      8 /* Address in use */
#define EADDRNOTAVAIL   9 /* Address not available */
#define EAFNOSUPPORT    10 /* Address family not supported */
#define EAGAIN          11 /* Resource unavailable, try again */
#define EALREADY        12 /* Connection already in progress */
#define EBADF           13 /* Bad file descriptor */
#define EBADMSG         14 /* Bad message */
#define EBUSY           15 /* Device or resource busy */
#define ECANCELED       16 /* Operation canceled */
#define ECHILD          17 /* No child processes */
#define ECONNABORTED    18 /* Connection aborted */
#define ECONNREFUSED    19 /* Connection refused */
#define ECONNRESET      20 /* Connection reset */
#define EDEADLK         21 /* Resource deadlock avoided */
#define EDESTADDRREQ    22 /* Destination address required */
#define EEXIST          23 /* File exists */
#define EFAULT          24 /* Bad address */
#define EFBIG           25 /* File too large */
#define EHOSTUNREACH    26 /* Host is unreachable */
#define EIDRM           27 /* Identifier removed */
#define EILSEQ          28 /* Illegal byte sequence */
#define EINPROGRESS     29 /* Operation in progress */
#define EINTR           30 /* Interrupted function */
#define EISCONN         31 /* Socket is connected */
#define EISDIR          32 /* Is a directory */
#define ELOOP           33 /* Too many levels of symbolic links */
#define EMFILE          34 /* Too many open files */
#define EMLINK          35 /* Too many links */
#define EMSGSIZE        36 /* Message too long */
#define ENAMETOOLONG    37 /* Filename too long */
#define ENETDOWN        38 /* Network is down */
#define ENETRESET       39 /* Connection aborted by network */
#define ENETUNREACH     40 /* Network is unreachable */
#define ENFILE          41 /* Too many open files in system */
#define ENOBUFS         42 /* No buffer space available */
#define ENODATA         43 /* No message is available on the STREAM head read queue */
#define ENODEV          44 /* No such device */
#define ENOENT          45 /* No such file or directory */
#define ENOEXEC         46 /* Executable file format error */
#define ENOLCK          47 /* No locks available */
#define ENOLINK         48 /* Link has been severed */
#define ENOMEM          49 /* Not enough space */
#define ENOMSG          50 /* No message of desired type */
#define ENOPROTOOPT     51 /* Protocol not available */
#define ENOSPC          52 /* No space left on device */
#define ENOSR           53 /* No stream resources */
#define ENOSTR          54 /* Not a stream */
#define ENOSYS          55 /* Function not implemented */
#define ENOTCONN        56 /* The socket is not connected */
#define ENOTDIR         57 /* Not a directory */
#define ENOTEMPTY       58 /* Directory not empty */
#define ENOTRECOVERABLE 59 /* State not recoverable */
#define ENOTSOCK        60 /* Not a socket */
#define ENOTSUP         61 /* Not supported */
#define ENOTTY          62 /* Inappropriate I/O control operation */
#define ENXIO           63 /* No such device or address */
#define EOPNOTSUPP      64 /* Operation not supported on socket */
#define EOVERFLOW       65 /* Value too large to be stored in data type */
#define EOWNERDEAD      66 /* Previous owner died */
#define EPIPE           67 /* Broken pipe */
#define EPROTO          68 /* Protocol error */
#define EPROTONOSUPPORT 69 /* Protocol not supported */
#define EPROTOTYPE      70 /* Protocol wrong type for socket */
#define EROFS           71 /* Read-only file system */
#define ESPIPE          72 /* Invalid seek */
#define ESRCH           73 /* No such process */
#define ETIME           74 /* Stream ioctl() timeout */
#define ETIMEDOUT       75 /* Connection timed out */
#define ETXTBSY         76 /* Text file busy */
#define EWOULDBLOCK     77 /* Operation would block */
#define EXDEV           78 /* Cross-device link */

extern int errno;

#endif /* _ERRNO_H */
