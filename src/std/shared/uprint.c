#include <format.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

extern struct fmt_type __print_fmt;
extern unsigned char __print_len;
extern char __print_leading_char;  // Initial +, -, or space for number
extern char *__print_out;

extern void (*__print_xputch)(char);

void __print_sendstring(char *sp);
void __print_putch(char ch);

int _u_print(char *dest, char *fmt, va_list argp) {
    char *sp;
    double d;

    __print_len = 0;
    __print_out = dest;
    while (*fmt) {
        while (*fmt && *fmt != (char)'%') {
            __print_putch(*fmt++);
            ++__print_len;
        }
        if (*fmt) {         /* we found a % in format string */
            fmt = _u_pscan(sp = fmt, &__print_fmt,&argp);
            if (__print_fmt.status == (unsigned char)FMT_ERR) {

                /* error in format string, just dump out from p to fmt */

                for (;sp < fmt;++__print_len,++sp) {
                    __print_putch(*sp++);
                }
                return -1;
            } else if (__print_fmt.status == (unsigned char)FMT_PASS_THRU) {
                __print_putch(__print_fmt.chr);
                ++__print_len;
            } else {
                switch (__print_fmt.type) {
                    case 'd':
                    case 'i':
                    if (__print_fmt.size == (char)'l' || __print_fmt.size == (char)'L') {
                        _u_ltoa(va_arg(argp, long));
                    } else {
                        _u_ltoa((long)va_arg(argp, int));
                    }
                    break;
                    case 'x':
                    case 'X':
                    case 'u':
                    case 'o':
                        if (__print_fmt.size == (char)'l' || __print_fmt.size == (char)'L') {
                            _u_ultoa(va_arg(argp,long));
                        } else {
                            _u_ultoa((unsigned long)va_arg(argp,unsigned int));
                        }
                        break;
                    case 'f':
                    case 'e':
                    case 'E':
                    case 'g':
                    case 'G':
                        d = va_arg(argp,double);
                        if (__print_fmt.type == (char)'g') {
                            _u_dtog(d);
                        } else {
                            _u_dtof(d);
                        }
                        break;
                    case 'c':
                        __print_buff[0] = va_arg(argp,int);
                        __print_buff[1] = '\0';
                        __print_sendstring(__print_buff);
                        break;
                    case 's':
                        sp = va_arg(argp, char*);
                        __print_sendstring(sp);
                        break;
                    case 'p':
                        _u_ultoa((long)va_arg(argp,void*));
                        break;
                    case 'n':
                        sp = va_arg(argp, char*);
                        if (__print_fmt.size == (char)'l' || __print_fmt.size == (char)'L') {
                            *((long*)sp) = __print_len;
                        } else {
                            *((int*)sp) = __print_len;
                        }
                        break;
                }
            }
        }
    }

    if (__print_out) {
        *__print_out = '\0';
    }
    return __print_len;
}
