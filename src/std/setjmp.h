#ifndef _SETJMP_H
#define _SETJMP_H

#include <cdefs.h>

__BEGIN_DECLS

typedef unsigned char jmp_buf[12];

int setjmp(jmp_buf env) __attribute__((returns_twice));
void longjmp(jmp_buf env, int val) __attribute__((noreturn));

__END_DECLS

#endif
