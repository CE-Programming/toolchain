#ifndef _ERRNO_H
#define _ERRNO_H

#define EPERM       1   /* permission error */
#define EINVAL      2   /* invalid argument */
#define EIO         3   /* io error */
#define EDOM        4   /* math domain error */
#define ERANGE      5   /* math range error */

extern int errno;

#endif /* _ERRNO_H */
