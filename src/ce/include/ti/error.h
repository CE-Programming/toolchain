/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS errors; this is all the `ERR:A MESSAGE` screen stuff.
 * You can use this to show custom error screens, as well as intercept errors to prevent the error screen from showing.
 */

#ifndef TI_ERROR_H
#define TI_ERROR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Throws an OS error
 *
 * @param[in] error Error code to throw
 */
void os_ThrowError(uint8_t error) __attribute__((noreturn));

/**
 * This function can return twice (like setjmp).
 * First return always happens with a return value of 0.
 * Second return only happens if an error occurs before os_PopErrorHandler is called,
 * with the errNo as the return value.
 *
 * @code{.cpp}
 * int errno = os_PushErrorHandler();
 * if (errno) {
 *     // handle error, but no longer under the protection of the error handler so do not call os_PopErrorHandler()
 * } else {
 *     // run some code that may error
 *     os_PopErrorHandler();
 * }
 * @endcode
 * 
 * @warning This does not respect C++ destructors!  So don't use anything that requires a non-trivial destructor.
 *
 * @see os_PopErrorHandler
 */
int os_PushErrorHandler(void) __attribute__((returns_twice));

/**
 * Restores stack state after a call to os_PushErrorHandler.  Must be called with stack in the same state
 * as it was when os_PushErrorHandler returned with 0, and should not be called along the error path.
 *
 * @see os_PushErrorHandler
 */
void os_PopErrorHandler(void);

/**
 * String for custom error.
 * Can be used by calling `os_ThrowError(OS_E_APPERR1);`.
 * @note String must be null-terminated, maximum of 12 characters.
 */
#define os_AppErr1           ((char*)0xD025A9)

/**
 * String for custom error.
 * Can be used by calling `os_ThrowError(OS_E_APPERR2);`.
 * @note String must be null-terminated, maximum of 12 characters.
 */
#define os_AppErr2           ((char*)0xD025B6)

#define OS_E_EDIT           (1<<7)
#define OS_E_MASK           (0x7F)
#define OS_E_OVERFLOW       (1+OS_E_EDIT)
#define OS_E_DIVBY0         (2+OS_E_EDIT)
#define OS_E_SINGULARMAT    (3+OS_E_EDIT)
#define OS_E_DOMAIN         (4+OS_E_EDIT)
#define OS_E_INCREMENT      (5+OS_E_EDIT)
#define OS_E_BREAK          (6+OS_E_EDIT)
#define OS_E_NONREAL        (7+OS_E_EDIT)
#define OS_E_SYNTAX         (8+OS_E_EDIT)
#define OS_E_DATATYPE       (9+OS_E_EDIT)
#define OS_E_ARGUMENT       (10+OS_E_EDIT)
#define OS_E_DIMMISMATCH    (11+OS_E_EDIT)
#define OS_E_DIMENSION      (12+OS_E_EDIT)
#define OS_E_UNDEFINED      (13+OS_E_EDIT)
#define OS_E_MEMORY         (14+OS_E_EDIT)
#define OS_E_INVALID        (15+OS_E_EDIT)
#define OS_E_ILLEGALNEST    (16+OS_E_EDIT)
#define OS_E_BOUND          (17+OS_E_EDIT)
#define OS_E_GRAPHRANGE     (18+OS_E_EDIT)
#define OS_E_ZOOM           (19+OS_E_EDIT)
#define OS_E_LABEL          (20)
#define OS_E_STAT           (21)
#define OS_E_SOLVER         (22+OS_E_EDIT)
#define OS_E_SINGULARITY    (23+OS_E_EDIT)
#define OS_E_SIGNCHANGE     (24+OS_E_EDIT)
#define OS_E_ITERATIONS     (25+OS_E_EDIT)
#define OS_E_BADGUESS       (26+OS_E_EDIT)
#define OS_E_STATPLOT       (27)
#define OS_E_TOLTOOSMALL    (28+OS_E_EDIT)
#define OS_E_RESERVED       (29+OS_E_EDIT)
#define OS_E_MODE           (30+OS_E_EDIT)
#define OS_E_LNKERR         (31+OS_E_EDIT)
#define OS_E_LNKMEMERR      (32+OS_E_EDIT)
#define OS_E_LNKTRANSERR    (33+OS_E_EDIT)
#define OS_E_LNKDUPERR      (34+OS_E_EDIT)
#define OS_E_LNKMEMFULL     (35+OS_E_EDIT)
#define OS_E_UNKNOWN        (36+OS_E_EDIT)
#define OS_E_SCALE          (37+OS_E_EDIT)
#define OS_E_IDNOTFOUND     (38)
#define OS_E_NOMODE         (39+OS_E_EDIT)
#define OS_E_VALIDATION     (40)
#define OS_E_LENGTH         (41+OS_E_EDIT)
#define OS_E_APPLICATION    (42+OS_E_EDIT)
#define OS_E_APPERR1        (43+OS_E_EDIT)
#define OS_E_APPERR2        (44+OS_E_EDIT)
#define OS_E_EXPIREDAPP     (45)
#define OS_E_BADADD         (46)
#define OS_E_ARCHIVED       (47+OS_E_EDIT)
#define OS_E_VERSION        (48)
#define OS_E_ARCHFULL       (49)
#define OS_E_VARIABLE       (50+OS_E_EDIT)
#define OS_E_DUPLICATE      (51+OS_E_EDIT)

#ifdef __cplusplus
}
#endif

#endif
