/**
 * Copyright (c) 2016, Matthew Waltz
 *
 * This file provides some useful debugging functions
 */

#ifdef dbg_printf
#undef dbg_printf
#endif

#ifdef dbg_sprintf
#undef dbg_sprintf
#endif

#ifdef dbgout
#undef dbgout
#endif

#ifdef debugger
#undef debugger
#endif

#ifndef NDEBUG

/**
 * Use dbg_sprintf(dbgout, const char*, ...);
 * to print to the console
 */
#define dbg_sprintf sprintf
#define dbg_printf sprintf
#define dbgout ((const char*)0xFB0000)
#define dbgerr ((const char*)0xFC0000)

/**
 * opens the debugger
 */
void debugger(void);

#else
    
#define dbg_printf (void)
#define dbgout (NULL)
#define debugger (void)

#endif