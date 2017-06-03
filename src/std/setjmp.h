/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 */
#ifndef __SETJMP_H
#define __SETJMP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char jmp_buf[12];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#ifdef __cplusplus
}
#endif

#endif

