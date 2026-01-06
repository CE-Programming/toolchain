#if PREFER_OS_LIBC

asm
(
    "\t.global _fmodf\n"
    "\t.type _fmodf, @function\n"
    "\t.equ _fmodf, 0x0220FC\n"
    "\t.global _fmod\n"
    "\t.type _fmod, @function\n"
    "\t.equ _fmod, _fmodf\n"
);
 
#else

#include <math.h>

float fmodf(float x, float y)
{
    return x - truncf(x / y) * y;
}

double fmod(double, double) __attribute__((alias("fmodf")));

#endif
