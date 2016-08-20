/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

/*
  Buffer Layout:	sp	;stack pointer
			ix	;frame pointer.
			retpch	;return pc low.
			retpcl	;return pc high.

*/

#ifndef SETJMP_H
#define SETJMP_H

typedef unsigned char jmp_buf[12];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env,int val);

#endif
