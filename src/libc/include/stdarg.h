#ifndef _STDARG_H
#define _STDARG_H

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif /* __GNUC_VA_LIST */

#ifndef _VA_LIST
#define _VA_LIST
typedef __builtin_va_list va_list;
#endif /* _VA_LIST */

#define va_start(ap, param)  __builtin_va_start(ap, param)
#define va_end(ap)           __builtin_va_end(ap)
#define va_arg(ap, type)     __builtin_va_arg(ap, type)
#define __va_copy(dest, src) __builtin_va_copy(dest, src)
#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
# define va_copy(dest, src)   __builtin_va_copy(dest, src)
#endif /* __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L */

#endif /* _STDARG_H */
