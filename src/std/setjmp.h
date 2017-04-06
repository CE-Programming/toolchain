/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 */
#ifndef __SETJMP_H
#define __SETJMP_H

typedef unsigned char jmp_buf[12];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#endif

