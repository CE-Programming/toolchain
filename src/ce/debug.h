/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @brief Contains useful debugging features for use with the integrated CEmu debugger
 */

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * void dbg_sprintf(out, const char *format, ...)
 *
 * @brief Use to print to the emulator console.
 *
 * See the syntax for 'printf' for more information
 * @param out Can be dbgout (black) or dbgerr (red)
 * @param format Uses printf-formated specifier string
 * @def dbg_sprintf
 */

/**
 * void dbg_ClearConsole(void)
 *
 * @brief Clears the emulator's console screen.
 * @def dbg_ClearConsole
 */

#ifndef NDEBUG

/**
 * Opens the emulator debugger
 */
void dbg_Debugger(void);

/**
 * Sets an emulated breakpoint at a particular address
 *
 * @param address The address of the breakpoint to remove
 */
void dbg_SetBreakpoint(void *address);

/**
 * Removes an emulated breakpoint at a particular address
 *
 * @param address The address of the breakpoint to remove
 */
void dbg_RemoveBreakpoint(void *address);

/**
 * Sets an emulated empty watchpoint at a particular address
 *
 * @param address The address of the watchpoint to set
 * @param length The size of the data at the address (values 1-4)
 */
void dbg_SetWatchpoint(void *address, unsigned int length);

/**
 * Sets an emulated read watchpoint at a particular address
 *
 * @param address The address of the watchpoint to set
 * @param length The size of the data at the address (values 1-4)
 */
void dbg_SetReadWatchpoint(void *address, unsigned int length);

/**
 * Sets an emulated write watchpoint at a particular address
 *
 * @param address The address of the watchpoint to set
 * @param length The size of the data at the address (values 1-4)
 */
void dbg_SetWriteWatchpoint(void *address, unsigned int length);

/**
 * Sets an emulated read/write watchpoint at a particular address
 *
 * @param address The address of the watchpoint to set
 * @param length The size of the data at the address (values 1-4)
 */
void dbg_SetReadWriteWatchpoint(void *address, unsigned int length);

/**
 * Removes an emulated watchpoint at a particular address
 *
 * @param address The address of the watchpoint to remove
 */
void dbg_RemoveWatchpoint(void *address);

/**
 * Removes all emulated watchpoints
 */
void dbg_RemoveAllWatchpoints(void);

/**
 * Removes all emulated breakpoints
 */
void dbg_RemoveAllBreakpoints(void);

#define dbgout ((char*)0xFB0000) /**< Standard debug output */
#define dbgerr ((char*)0xFC0000) /**< Error debug output */
#define dbg_sprintf sprintf
#define dbg_ClearConsole() (*(unsigned char*)0xFD0000 = 1)
#else
#define dbg_Debugger(ignore) ((void)0)
#define dbg_SetBreakpoint(ignore) ((void)0)
#define dbg_RemoveBreakpoint(ignore) ((void)0)
#define dbg_SetWatchpoint(ignore,ignore) ((void)0)
#define dbg_SetReadWatchpoint(ignore,ignore) ((void)0)
#define dbg_SetWriteWatchpoint(ignore,ignore) ((void)0)
#define dbg_SetReadWriteWatchpoint(ignore,ignore) ((void)0)
#define dbg_RemoveWatchpoint(ignore) ((void)0)
#define dbg_RemoveAllWatchpoints(ignore) ((void)0)
#define dbg_RemoveAllBreakpoints(ignore) ((void)0)
#define dbg_sprintf if(0)(void)
#define dbg_ClearConsole(ignore) ((void)0)
#define dbgout (NULL)
#define dbgerr (NULL)
#endif

#ifdef __cplusplus
}
#endif
