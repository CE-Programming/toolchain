/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *  Modified by Matt "MateoConLechuga" Waltz for TI84+CE platform
 */
#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <format.h>

#define L_tmpnam  12
#define SEEK_CUR  1
#define SEEK_END  2
#define SEEK_SET  0
#define SYS_OPEN  5          /* max open files */
#define FOPEN_MAX SYS_OPEN

/* ANSI prototypes */
#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned int size_t;
#endif

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef EOF
#define EOF (-1)             /* end of file */
#endif

int sprintf(char *s, const char *format, ...);
int vprintf(const char *format, va_list arg);
int vsprintf(char *s, const char *format, va_list arg);

#endif
