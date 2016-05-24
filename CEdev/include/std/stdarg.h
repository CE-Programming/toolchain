/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef STDARG_H
#define STDARG_H

typedef char * va_list;
#define _INTSIZEOF(n) (sizeof(n) + sizeof(int)-1-((sizeof(n)-1)%sizeof(int)))

#define va_start(ap, parm) (ap = (char *)&parm + _INTSIZEOF(parm))
#define va_arg(ap,type)    (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))
#define va_end(ap)

#endif
