/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <format.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <cio.h>

#ifndef _PTR_
#define _PTR_ *
#endif

/*************************************************
*
* _u_print - print formated string to a file
*
* Inputs:
*       dest - address to put string, NULL = output via putch
*       fmt - format string
*       argp - argument list pointer
*
* Returns:
*       Number of characters transmitted, or
*       -1 if an error occured.
*
*************************************************/

#ifndef _MULTI_THREAD
int _u_print(char _PTR_ dest,char _PTR_ fmt,va_list argp)
#else
int _mt_print(char _PTR_ fmt,va_list argp)
#endif
{
#ifdef _MULTI_THREAD
#define __print_putch putch
#define __print_send() __print_len += __mt_print_send('\0',__print_buff,&__print_fmt)
#define __print_sendstring(s) __print_len+=__mt_print_sendstring(s,&__print_fmt)
#define _u_ltoa(l) __print_len+=__mt_print_send(_mt_ltoa(l,__print_buff,&__print_fmt),__print_buff,&__print_fmt)
#define _u_ultoa(l) _mt_ultoa(l,__print_buff,&__print_fmt);__print_len+=__mt_print_send('\0',__print_buff,&__print_fmt)
#define _u_dtof(d) __print_len+=__mt_fprint_send(_mt_dtof(d,__print_buff,&__print_fmt),__print_buff,&__print_fmt)
#define _u_dtog(d) __print_len+=__mt_fprint_send(_mt_dtog(d,__print_buff,&__print_fmt),__print_buff,&__print_fmt)
#endif
//  register char _PTR_ p;
  register char _PTR_ sp;
//  register int i;
  double d;
#ifdef _MULTI_THREAD
  struct fmt_type __print_fmt;
  register unsigned char __print_len;
  char __print_buff[12];
  __print_fmt=__clear_fmt_type;
#endif

  __print_len = 0;
#ifndef _MULTI_THREAD
  __print_out = dest;
#endif
  while (*fmt) {
    while (*fmt && *fmt != (char)'%') {
      __print_putch(*fmt++);
      ++__print_len;
    }
    if (*fmt) {         /* we found a % in format string */
      fmt = _u_pscan(sp = fmt,&__print_fmt,&argp);
      if (__print_fmt.status == (unsigned char)FMT_ERR) {

        /* error in format string, just dump out from p to fmt */

        for (;sp < fmt;++__print_len,++sp) { 
          __print_putch(*sp++);
	    }
        return(-1);
      }
      else if (__print_fmt.status == (unsigned char)FMT_PASS_THRU) {
        __print_putch(__print_fmt.chr);
        ++__print_len;
      }
      else {
        switch (__print_fmt.type) {
          case 'd':
          case 'i':
                if (__print_fmt.size == (char)'l' || __print_fmt.size == (char)'L') {
                  _u_ltoa(va_arg(argp,long));
                }
                else /* %d or %hd */ {
                  _u_ltoa((long)va_arg(argp,int));
                }
                break;
          case 'x':
          case 'X':
          case 'u':
          case 'o':
                if (__print_fmt.size == (char)'l' || __print_fmt.size == (char)'L') {
                  _u_ultoa(va_arg(argp,long));
                }
                else /* %x or %hx */ {
                  _u_ultoa((unsigned long)va_arg(argp,unsigned int));
                }
                break;
          case 'f':
          case 'e':
          case 'E':
          case 'g':
          case 'G':
                d = va_arg(argp,double);
                if (__print_fmt.type == (char)'g')
                  _u_dtog(d);
		else
                  _u_dtof(d);
		break;
          case 'c':
                __print_buff[0] = va_arg(argp,int);
                __print_buff[1] = '\0';
                __print_send();
                break;
          case 's':
                sp = va_arg(argp,char _PTR_);
                __print_sendstring(sp);
		break;
          case 'p':
                _u_ultoa((long)va_arg(argp,void*));
		break;
          case 'n':
                sp = va_arg(argp,char _PTR_);
                if (__print_fmt.size == (char)'l' || __print_fmt.size == (char)'L')
                  *((long _PTR_)sp) = __print_len;
                else
                  *((int _PTR_)sp) = __print_len;
		break;
        }
      }
    }
  }

#ifndef _MULTI_THREAD
  if (__print_out)
    *__print_out = '\0';
#endif
  return(__print_len);
}
