#if PREFER_OS_LIBC

asm
(
    "\t.global _log10f\n"
    "\t.type _log10f, @function\n"
    "\t.equ _log10f, 0x0220E8\n"
    "\t.global _log10\n"
    "\t.type _log10, @function\n"
    "\t.equ _log10, _log10f\n"
);

#else

#include <math.h>

float log10f(float x)
{
    return logf(x) * (float)(M_LOG10E);
}

double log10(double) __attribute__((alias("log10f")));

#endif
