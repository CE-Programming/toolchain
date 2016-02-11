/*************************************************
 * CE debug header file
 *************************************************/

/* To print to the console, just use
 * dbg_printf(dbgout, const char*, ...); */

#ifdef dbg_printf
#undef dbg_printf
#endif

#ifdef dbgout
#undef dbgout
#endif

#ifdef debugger
#undef debugger
#endif

#ifndef NDEBUG

#define dbg_printf sprintf
#define dbgout ((const char*)0xFB0000)

void debugger(void);                    /* Opens the debugger */

#else
    
#define dbg_printf (void)
#define dbgout (NULL)
#define debugger (void)

#endif