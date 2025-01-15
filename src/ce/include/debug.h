/**
 * @file
 *
 * These debug functions are provided to help in the process of debugging
 * an application. To enable them, use `make debug` when compiling a program.
 */

#include <stdio.h>
#include <stdint.h>
#include <cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDEBUG

/** Standard debug output */
#define dbgout ((char*)0xFB0000)
/** Standard error debug output */
#define dbgerr ((char*)0xFC0000)

/** Break on read. */
#define DBG_WATCHPOINT_READ (1 << 0) 
/** Break on write. */
#define DBG_WATCHPOINT_WRITE (1 << 1)
/** Break on execute. */
#define DBG_WATCHPOINT_EXECUTE (1 << 2)
/** Break on read, write, or execute. */
#define DBG_WATCHPOINT_ALL (DBG_WATCHPOINT_READ | DBG_WATCHPOINT_WRITE | DBG_WATCHPOINT_EXECUTE)
/** Remove watchpoint. */
#define DBG_WATCHPOINT_NONE 0

/**
 * Used to print to the emulator console.
 *
 * See the syntax for 'printf' for format specifiers.
 * @param[in] ... Uses printf-formated specifier string.
 * @note Does not support floats unless `HAS_PRINTF = YES`.
 */
#define dbg_printf(...) \
sprintf(dbgout, ##__VA_ARGS__)

/**
 * Used to print to the emulator console.
 *
 * See the syntax for 'printf' for format specifiers.
 * @param[in] out Use \p dbgout for normal output and \p dbgerr for errors.
 * @param[in] ... Uses printf-formated specifier string.
 * @note Does not support floats unless `HAS_PRINTF = YES`.
 */
#define dbg_sprintf(out, ...) \
sprintf(out, ##__VA_ARGS__)

/**
 * Clears the emulation console.
 */
#define dbg_ClearConsole() \
do { \
    *(volatile unsigned char*)0xFD0000 = 1; \
} while (0)

/**
 * Opens the emulator's debugger immediately
 */
void dbg_Debugger(void);

/**
 * Sets a watchpoint to open the debugger when an address
 * is read, written, or executed. Use the masks DBG_WATCHPOINT_READ,
 * DBG_WATCHPOINT_WRITE, and DBG_WATCHPOINT_EXECUTE respectively to
 * configure the watchpoint.
 * 
 * @param[in] address Watchpoint address.
 * @param[in] size Watchpoint size in bytes. Currently must be 1.
 * @param[in] mask Watchpoint mask, use DBG_WATCHPOINT_NONE to remove
 *                 the watchpoint.
 */
void dbg_WatchpointSet(void *address, size_t size, uint8_t mask);

/**
 * Removes all watchpoints.
 */
void dbg_WatchpointRemoveAll(void);

#else
#define dbg_printf(...) ((void)0)
#define dbg_sprintf(...) ((void)0)
#define dbg_ClearConsole(...) ((void)0)
#define dbg_Debugger(...) ((void)0)
#define dbg_WatchpointSet(...) ((void)0)
#define dbg_WatchpointRemoveAll(...) ((void)0)
#endif

#ifdef __cplusplus
}
#endif
