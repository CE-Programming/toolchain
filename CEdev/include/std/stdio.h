/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <format.h>

#define _IOFBF		0
#define _IOLBF		1
#define _IONBF		2
#define BUFSIZ		128		/* buffer size */
#define EOF		(-1)		/* end of file */
#define L_tmpnam	12
#define SEEK_CUR	0
#define SEEK_END	1
#define SEEK_SET	2
#define SYS_OPEN	3		/* max open files */
#define FOPEN_MAX	SYS_OPEN
#define TMP_MAX 	50

#define _IO_READ	0x0001	/* file opened for read */
#define _IO_WRITE	0x0002	/* file opened for write */
#define _IO_APPEND	0x0004	/* file opened for append */
#define _IO_UPDATE	0x0008	/* update access boolean */
#define _IO_ASCII	0x0010	/* ASCII file */
#define _IO_BINARY	0x0020	/* BINARY file */
#define _IO_INDEX	0x0040	/* VERSADOS indexed sequential file */
#define _IO_EOF 	0x0100	/* EOF seen boolean */
#define _IO_ERROR	0x0200	/* io error encountered */
#define _IO_ALLOC	0x0400	/* FILE block allocated boolean */
#define _IO_DISK	0x0800	/* disk vs. device boolean */
#define _IO_FBUF	0x1000	/* file is fully buffered */
#define _IO_LBUF	0x2000	/* file is line buffered */
#define _IO_NBUF	0x4000	/* file is not buffered */
#define _IO_SETVBUF	0x8000	/* setvbuf allocated buffer */

/* ANSI prototypes */
#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned int size_t;
#endif

#ifndef NULL
#define NULL		(void *)0
#endif

int printf(char * format, ...);
int scanf(char * format, ...);
int sprintf(char * s,char * format, ...);
int sscanf(char * s,char * format, ...);
int vprintf(char * format,va_list arg);
int vsprintf(char * s,char * format,va_list arg);
char *gets(char * s);
int puts(char * s);

int getchar(void);
int putchar(int c);

#endif
