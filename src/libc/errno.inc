.ifndef __ERRNO_INC__
	.set	__ERRNO_INC__, 1

; errno.inc
; Assembly errno equates for libc <errno.h>
; Remember to keep this file in sync with <errno.h>

; Note that many routines assume that EDOM and ERANGE are between 1 and 255.

	.equ	EPERM           ,   1 ; permission error
	.equ	EINVAL          ,   2 ; invalid argument
	.equ	EIO             ,   3 ; io error
	.equ	EDOM            ,   4 ; math domain error
	.equ	ERANGE          ,   5 ; math range error
	.equ	EILSEQ          ,   6 ; Illegal byte sequence (C95)
	.equ	E2BIG           ,   7 ; Argument list too long
	.equ	EACCES          ,   8 ; Permission denied
	.equ	EADDRINUSE      ,   9 ; Address in use
	.equ	EADDRNOTAVAIL   ,  10 ; Address not available
	.equ	EAFNOSUPPORT    ,  11 ; Address family not supported
	.equ	EAGAIN          ,  12 ; Resource unavailable, try again
	.equ	EALREADY        ,  13 ; Connection already in progress
	.equ	EBADF           ,  14 ; Bad file descriptor
	.equ	EBADMSG         ,  15 ; Bad message
	.equ	EBUSY           ,  16 ; Device or resource busy
	.equ	ECANCELED       ,  17 ; Operation canceled
	.equ	ECHILD          ,  18 ; No child processes
	.equ	ECONNABORTED    ,  19 ; Connection aborted
	.equ	ECONNREFUSED    ,  20 ; Connection refused
	.equ	ECONNRESET      ,  21 ; Connection reset
	.equ	EDEADLK         ,  22 ; Resource deadlock avoided
	.equ	EDESTADDRREQ    ,  23 ; Destination address required
	.equ	EEXIST          ,  24 ; File exists
	.equ	EFAULT          ,  25 ; Bad address
	.equ	EFBIG           ,  26 ; File too large
	.equ	EHOSTUNREACH    ,  27 ; Host is unreachable
	.equ	EIDRM           ,  28 ; Identifier removed
	.equ	EINPROGRESS     ,  29 ; Operation in progress
	.equ	EINTR           ,  30 ; Interrupted function
	.equ	EISCONN         ,  31 ; Socket is connected
	.equ	EISDIR          ,  32 ; Is a directory
	.equ	ELOOP           ,  33 ; Too many levels of symbolic links
	.equ	EMFILE          ,  34 ; Too many open files
	.equ	EMLINK          ,  35 ; Too many links
	.equ	EMSGSIZE        ,  36 ; Message too long
	.equ	ENAMETOOLONG    ,  37 ; Filename too long
	.equ	ENETDOWN        ,  38 ; Network is down
	.equ	ENETRESET       ,  39 ; Connection aborted by network
	.equ	ENETUNREACH     ,  40 ; Network is unreachable
	.equ	ENFILE          ,  41 ; Too many open files in system
	.equ	ENOBUFS         ,  42 ; No buffer space available
	.equ	ENODATA         ,  43 ; No message is available on the STREAM head read queue
	.equ	ENODEV          ,  44 ; No such device
	.equ	ENOENT          ,  45 ; No such file or directory
	.equ	ENOEXEC         ,  46 ; Executable file format error
	.equ	ENOLCK          ,  47 ; No locks available
	.equ	ENOLINK         ,  48 ; Link has been severed
	.equ	ENOMEM          ,  49 ; Not enough space
	.equ	ENOMSG          ,  50 ; No message of desired type
	.equ	ENOPROTOOPT     ,  51 ; Protocol not available
	.equ	ENOSPC          ,  52 ; No space left on device
	.equ	ENOSR           ,  53 ; No stream resources
	.equ	ENOSTR          ,  54 ; Not a stream
	.equ	ENOSYS          ,  55 ; Function not implemented
	.equ	ENOTCONN        ,  56 ; The socket is not connected
	.equ	ENOTDIR         ,  57 ; Not a directory
	.equ	ENOTEMPTY       ,  58 ; Directory not empty
	.equ	ENOTRECOVERABLE ,  59 ; State not recoverable
	.equ	ENOTSOCK        ,  60 ; Not a socket
	.equ	ENOTSUP         ,  61 ; Not supported
	.equ	ENOTTY          ,  62 ; Inappropriate I/O control operation
	.equ	ENXIO           ,  63 ; No such device or address
	.equ	EOPNOTSUPP      ,  64 ; Operation not supported on socket
	.equ	EOVERFLOW       ,  65 ; Value too large to be stored in data type
	.equ	EOWNERDEAD      ,  66 ; Previous owner died
	.equ	EPIPE           ,  67 ; Broken pipe
	.equ	EPROTO          ,  68 ; Protocol error
	.equ	EPROTONOSUPPORT ,  69 ; Protocol not supported
	.equ	EPROTOTYPE      ,  70 ; Protocol wrong type for socket
	.equ	EROFS           ,  71 ; Read-only file system
	.equ	ESPIPE          ,  72 ; Invalid seek
	.equ	ESRCH           ,  73 ; No such process
	.equ	ETIME           ,  74 ; Stream ioctl() timeout
	.equ	ETIMEDOUT       ,  75 ; Connection timed out
	.equ	ETXTBSY         ,  76 ; Text file busy
	.equ	EWOULDBLOCK     ,  77 ; Operation would block
	.equ	EXDEV           ,  78 ; Cross-device link

.if	ERANGE & 0xFF != ERANGE
	.print	"ERANGE is assumed to be between 1 and 255"
	.err
.endif
.if	EDOM & 0xFF != EDOM
	.print	"EDOM is assumed to be between 1 and 255"
	.err
.endif

.endif
