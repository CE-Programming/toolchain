/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

/*************************************************************************
 * We now assume that the maximum number of fields processed in a format
 * string is 255.  Then, we can fit the field count into a char, for a
 * slight saving in space and time. <THH>
 *************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdarg.h>
#include <format.h>
#include <float.h>
#include <string.h>
#include <cio.h>


/*  Sizes allowed for various data */
/*  For small model, we must restrict the allowed input */
#if (defined(__MODEL__) && (__MODEL__ == 0)) && !defined(__ACCLAIM__)
#define FLT_CHARS (2*FLT_DIG+7)  // Only need FLT_DIG+7, but allow for extra data
#define PTR_CHARS 11
#define INT_CHARS 9
#else
#define FLT_CHARS 127
#define PTR_CHARS 127
#define INT_CHARS 127
#endif

#ifndef _MULTI_THREAD
static char _PTR_  bptr;
static va_list argp;
static int len;
static unsigned char fields;
static struct fmt_type fmt_str;
static int prev_ch;
static char isunget;

#else
#define bptr (*bptr)
#define argp (*argp)
#define len (*len)
#define fields (*fields)
#define fmt_str (*fmt_str)
#define prev_ch (*prev_ch)
#define isunget (*isunget)
#endif

/****************************************/
/*					*/
/*	     get a character		*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static int get(void)
{
  ++len;
  if (bptr)
    return(*(bptr++));
  else if (isunget==1) {
    	isunget = 0;
		return prev_ch;	
  }
  return(prev_ch = getchar());
}
#else
#define get() (len++,isunget)?(isunget=0,prev_ch):(prev_ch=getch())
#endif

/****************************************/
/*					*/
/*	     unget a character		*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static void unget(void)
{
  --len;
  isunget = 1;
  if (bptr)
    --bptr; 
}
#else
#define unget() --len,isunget=1
#endif

/****************************************/
/*					*/
/*	Handle pointer conversions	*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static unsigned char pointer(void)
#else
static unsigned char pointer(va_list argp,int len,unsigned char fields,struct fmt_type fmt_str,int prev_ch,char isunget)
#endif
{
  unsigned char i;
  char ch;
  char buffer[PTR_CHARS];
  char _PTR_ bp = buffer;
  unsigned int addr;

  if (fmt_str.field_width == 0 || fmt_str.field_width > sizeof(buffer)-1)
    fmt_str.field_width = sizeof(buffer)-1;
  if ((ch = get()) == EOF)
    return FALSE;
  for (i=0;isxdigit(ch);) {
    *(bp++) = ch;
    i++;
    if (i >= fmt_str.field_width)
      break;
    if ((ch = get()) == EOF)
      return FALSE;
  }
  if (bp == buffer)
    return FALSE;
  if (i < fmt_str.field_width)
    unget();
  *bp = '\0';
  addr = strtoul(buffer,(void *)NULL,16);

  if (!(fmt_str.flags & FMT_FLAG_IGNORE))
  {
    *(va_arg(argp,int _PTR_ _PTR_)) = (int _PTR_)addr;
    ++fields;
  }

  return TRUE;
}

/****************************************/
/*					*/
/*	Handle string conversions	*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static unsigned char string(void)
#else
static unsigned char string(va_list argp,int len,unsigned char fields,struct fmt_type fmt_str,int prev_ch,char isunget)
#endif
{
  unsigned char i;
  char ch;
  char _PTR_ p = NULL;

  if (!(fmt_str.flags & FMT_FLAG_IGNORE))
     p = va_arg(argp,char _PTR_);
  if (fmt_str.field_width == 0)
    fmt_str.field_width = 127;
  do {
    if ((ch = get()) == EOF)
      return FALSE;
  } while (isspace(ch));
  unget();
  if ((ch = get()) == EOF)
    return FALSE;
  for (i=0; !isspace(ch) && ch;) {
    if (p)
      *(p++) = ch;
    i++;
    if (i >= fmt_str.field_width)
      break;
    if ((ch = get()) == EOF)
      return FALSE;
  }
  if (i < fmt_str.field_width)
    unget();
  if (p)
  {
    *p = '\0';
    ++fields;
  }
  return TRUE;
}

/****************************************/
/*					*/
/*	Handle character conversions	*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static unsigned char character(void)
#else
static unsigned char character(va_list argp,int len,unsigned char fields,struct fmt_type fmt_str,int prev_ch,char isunget)
#endif
{
  unsigned char i;
  char ch;
  char _PTR_ p=NULL;

  if (!(fmt_str.flags & FMT_FLAG_IGNORE))
    p = va_arg(argp,char _PTR_);
  if (fmt_str.field_width == 0)
    fmt_str.field_width = 1;
  for (i=0;i<fmt_str.field_width;++i)
  {
    if ((ch = get()) == EOF)
      return FALSE;
    if (p)
      *(p++) = ch;
    ++fields;
  }
  return TRUE;
}

/****************************************/
/*					*/
/*	Floating point conversions	*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static unsigned char fpoint(void)
#else
static unsigned char fpoint(va_list argp,int len,unsigned char fields,struct fmt_type fmt_str,int prev_ch,char isunget)
#endif
{
  unsigned char i;
  char ch;
  char buffer[FLT_CHARS];
  char _PTR_ bp = buffer;
  double dval;
  unsigned char takeEe=TRUE;
  unsigned char takeDot=TRUE;
  unsigned char takeSign=TRUE;

  if (fmt_str.field_width == 0 || fmt_str.field_width > sizeof(buffer)-1)
    fmt_str.field_width = sizeof(buffer)-1;
  do {
    if ((ch = get()) == EOF)
      return FALSE;
  } while (isspace(ch));

  for (i=0; i < fmt_str.field_width; ++i)
  {
    if (takeEe && (ch == 'e' || ch == 'E'))
    {
       takeEe = FALSE;
       takeSign=TRUE;
       takeDot=FALSE;
    } else
    if (takeDot && ch=='.')
    {
      takeDot=FALSE;
    } else
    if (   (takeSign && (ch == '-' || ch == '+'))
       ||  isdigit(ch) )
    {
        takeSign = FALSE;
    } else
    {
        break;
    }
    *(bp++) = ch;
    if ((ch = get()) == EOF)
      return FALSE;
  }
  if (bp == buffer)
    return(fields);
  if (i < fmt_str.field_width)
    unget();
  *bp = '\0';
  dval = strtod(buffer,(void _PTR_)NULL);

  if (!(fmt_str.flags & FMT_FLAG_IGNORE)) {
#if 0
    /* EZ8 Specific */
    /* float, double and long double are indistinguishable 4-byte
       floating-point representations. <THH> */
    if (fmt_str.size == 'l')
      *(va_arg(argp,double _PTR_)) = dval;
    else if (fmt_str.size == 'L')
      *(va_arg(argp,long double _PTR_)) = dval;
    else
       *(va_arg(argp,float _PTR_)) = dval;
#else
    *(va_arg(argp, float _PTR_)) = dval;
#endif
    ++fields;
  }

  return TRUE;
}

/****************************************/
/*					*/
/*	Handle scalar conversions	*/
/*					*/
/****************************************/
#ifndef _MULTI_THREAD
static unsigned char scalar(int radix)
#else
static unsigned char scalar(va_list argp,int len,unsigned char fields,struct fmt_type fmt_str,int prev_ch,char isunget,int radix)
#endif
{
  unsigned char i;
  char ch;
  char buffer[INT_CHARS];
  char _PTR_ bp = buffer;
  long val;

  if (fmt_str.field_width == 0 || fmt_str.field_width > sizeof(buffer)-1)
    fmt_str.field_width = sizeof(buffer)-1;
  do {
    if ((ch = get()) == EOF)
      return FALSE;
  } while (isspace(ch));
  unget();
  if ((ch = get()) == EOF)
    return FALSE;
  for (i=0;radix == 10 && isdigit(ch) ||
	   radix == 16 && isxdigit(ch) ||
	   radix == 8 && ch >= '0' && ch <= '7' ||
	   ch == '-' ||
	   ch == '+';) {
    *(bp++) = ch;
    i++;
    if (i >= fmt_str.field_width)
      break;
    if ((ch = get()) == EOF)
      return FALSE;
  }
  if (bp == buffer)
    return(fields);
  if (i < fmt_str.field_width)
    unget();
  *bp = '\0';
  if ((fmt_str.type == 'u') || (radix == 8) || (radix == 16))
    val = strtoul(buffer,(void _PTR_)NULL,radix);
  else
    val = strtol(buffer,(void _PTR_)NULL,radix);

  if (!(fmt_str.flags & FMT_FLAG_IGNORE)) {
    if (fmt_str.size == 'h')
      *(va_arg(argp,short _PTR_)) = val;
    else if (fmt_str.size == 'l' || fmt_str.size == 'L')
      *(va_arg(argp,long _PTR_)) = val;
    else
      *(va_arg(argp,int _PTR_)) = val;
    ++fields;
  }

  return TRUE;
}

/****************************************/
/*					*/
/*	  Handle set conversions	*/
/*					*/
/****************************************/


#ifndef _MULTI_THREAD
static unsigned char set(void)
#else
static unsigned char set(va_list argp,int len,struct fmt_type fmt_str,int prev_ch,char isunget)
#endif
{
  char _PTR_ p2;
  char neg,ch;
  char _PTR_ p = 0;
  char width;

  /* Use (p == 0) to signal the case that we are skipping this input
     string. <THH> */
  if (!(fmt_str.flags & FMT_FLAG_IGNORE))
    p = va_arg(argp,char _PTR_);

  if (neg = (*fmt_str.set_begin == '^'))
    fmt_str.set_begin++;

  width = fmt_str.field_width;
  if (width == 0)
    width = 127;

  while (width--)
  {
    if ((ch = get()) == EOF)
      return FALSE;

    /* Look for a match in the set. */
    for(p2 = fmt_str.set_begin; p2 < fmt_str.set_end; ++p2)
      if (*p2 == ch)
	break;	/* Matched one in the set. */

    if (p2 < fmt_str.set_end && *p2 == ch)
    {
      /* We stop scanning if we match a character in the negative set. */
      if (neg)
	break;
    }
    else
    {
      /* Likewise, we stop scanning if we fail to match a character in
	 the positive set. */
      if (!neg)
	break;
    }

    /* Store the valid character. <THH> */
    if (p)
      *(p++) = ch;
  }

  if (width > 0)
    unget();

  if (p)
    *p = '\0';

  return TRUE;
}

/*************************************************
*
* _u_scan - scan formated string from a file or string
*
* Inputs:
*	src - NULL = input from keyboard, else input from string
*       fmt - format string
*	argp - argument list pointer
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/
#ifndef _MULTI_THREAD
int _u_scan(char _PTR_ src,char _PTR_ fmt,va_list ap)
#else
int _mt_scan(char _PTR_ fmt,va_list ap)
#endif
{
#ifdef _MULTI_THREAD
#undef argp
#undef len
#undef fields
#undef fmt_str
#undef prev_ch
#undef isunget

	va_list argp;
	int len;
	unsigned char fields;
	struct fmt_type fmt_str;
	int prev_ch;
	char isunget;
#endif

  int i;
  int ch;
  unsigned char ok=TRUE;

  argp = ap;
  fields = 0;
  len = 0;
  prev_ch = 0;
  isunget = 0;
#ifndef _MULTI_THREAD
  bptr = (void _PTR_)NULL;

  if (src)
    bptr = src;
#endif

  while ( ok && prev_ch!=EOF && *fmt) {
    fmt = _u_sscan(fmt,&fmt_str);
    if (fmt_str.status == FMT_ERR)
      return(fields);
    else if (fmt_str.status == FMT_PASS_THRU) {
      if (isspace(fmt_str.chr))
      {
        do ch=get();
        while(isspace(ch));
        unget();
      } else
      {
        ch = get();
        if (ch && ch != fmt_str.chr)
	  break;
      }
    }
    else if (fmt_str.flags & FMT_FLAG_SET) {
#ifndef _MULTI_THREAD
      ok = set();
#else
	  ok = set(&argp,&len,&fmt_str,&prev_ch,&isunget);
#endif
    }
    else {
      switch (fmt_str.type) {
	  register int radix;
	  case 'd':
	  case 'i':
	  case 'u':
				radix=10;
				goto _sclr;
	  case 'x':
	  case 'X':
				radix=16;
				goto _sclr;
	  case 'o':
	  			radix=8;
	  _sclr:
#ifndef _MULTI_THREAD
				ok = scalar(radix);
#else
				ok = scalar(&argp,&len,&fields,&fmt_str,&prev_ch,&isunget,radix);
#endif

		break;
#if __FPLIB__ || 1
	  case 'A':
	  case 'E':
	  case 'F':
	  case 'G':
	  case 'a':
	  case 'e':
	  case 'f':
	  case 'g':
#ifndef _MULTI_THREAD
                ok = fpoint();
#else
				ok = fpoint(&argp,&len,&fields,&fmt_str,&prev_ch,&isunget);
#endif

		break;
#endif
	  case 'c':
#ifndef _MULTI_THREAD
		ok = character();
#else
		ok = character(&argp,&len,&fields,&fmt_str,&prev_ch,&isunget);
#endif
		break;
	  case 's':
#ifndef _MULTI_THREAD
		ok = string();
#else
		ok = string(&argp,&len,&fields,&fmt_str,&prev_ch,&isunget);
#endif
		break;
	  case 'p':
#ifndef _MULTI_THREAD
		ok = pointer();
#else
		ok = pointer(&argp,&len,&fields,&fmt_str,&prev_ch,&isunget);
#endif
		break;
	  case 'n':
		if (!(fmt_str.flags & FMT_FLAG_IGNORE)) {
		  *(va_arg(argp,int _PTR_)) = len;
		  ++fields;
		}
		break;
      }
    }
  }
  // ISO Spec:  Return EOF if an input error occurs before any conversion.
  // Otherwise return the number of input items assigned.
  // A sucessfull passthrough counts as a conversion, so we look at len,
  // which will be 1 for a unsucessfull call to get on the first try.
  if (prev_ch == EOF && len<=1)
     return EOF;
  return fields;
}
