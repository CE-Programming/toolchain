#ifndef _ERRNO_H
#define _ERRNO_H

#define EPERM       1   /* permission error */
#define EINVAL      2   /* invalid argument */
#define EIO         3   /* io error */
#define EDOM        4   /* math domain error */
#define ERANGE      5   /* math range error */
#define EILSEQ      6   /* Illegal byte sequence (C95) */

/* C++ errno */
#define E2BIG            7 /* Argument list too long */
#define EACCES           8 /* Permission denied */
#define EADDRINUSE       9 /* Address in use */
#define EADDRNOTAVAIL   10 /* Address not available */
#define EAFNOSUPPORT    11 /* Address family not supported */
#define EAGAIN          12 /* Resource unavailable, try again */
#define EALREADY        13 /* Connection already in progress */
#define EBADF           14 /* Bad file descriptor */
#define EBADMSG         15 /* Bad message */
#define EBUSY           16 /* Device or resource busy */
#define ECANCELED       17 /* Operation canceled */
#define ECHILD          18 /* No child processes */
#define ECONNABORTED    19 /* Connection aborted */
#define ECONNREFUSED    20 /* Connection refused */
#define ECONNRESET      21 /* Connection reset */
#define EDEADLK         22 /* Resource deadlock avoided */
#define EDESTADDRREQ    23 /* Destination address required */
#define EEXIST          24 /* File exists */
#define EFAULT          25 /* Bad address */
#define EFBIG           26 /* File too large */
#define EHOSTUNREACH    27 /* Host is unreachable */
#define EIDRM           28 /* Identifier removed */
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
