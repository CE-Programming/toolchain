#ifndef __SETJMP_H
#define __SETJMP_H

typedef unsigned char jmp_buf[12];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#endif

