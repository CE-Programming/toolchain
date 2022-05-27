/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS user variables and memory
 * 
 * This declares routines for low-level access to user variables (appvars, programs, Str0-9, matrix, &c.),
 * as well as other user-memory management routines (not the heap!), stat vars, and the RunPrgm interface.
 */

#ifndef TI_VARS_H
#define TI_VARS_H

#include <stdint.h>
#include <stddef.h>
#include <ti/real.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

/**
 * @brief Structure of list variable type
 */
typedef struct { uint16_t dim; real_t items[1]; } list_t;
/**
 * @brief Structure of complex list variable type
 */
typedef struct { uint16_t dim; cplx_t items[1]; } cplx_list_t;
/**
 * @brief Structure of matrix variable type
 */
typedef struct { uint8_t cols, rows; real_t items[1]; } matrix_t;
/**
 * @brief Structure of string variable type
 */
typedef struct { uint16_t len; char data[1]; } string_t;
/**
 * @brief Structure of equation variable type
 */
typedef struct { uint16_t len; char data[1]; } equ_t;
/**
 * @brief Structure of miscellaneous variable type
 */
typedef struct { uint16_t size; uint8_t data[1]; } var_t;

/**
 * Gets an element from a matrix
 *
 * @param matrix Structure of matrix
 * @param row Row in matrix
 * @param col Column in matrix
 * @returns real_t containing element data
 */
#define matrix_element(matrix, row, col) ((matrix)->items[(row)+(col)*(matrix)->rows])

/**
 * Returns the size in bytes of free RAM that the user isn't using. A pointer is
 * also returned to the start of this region; you can use it for your own
 * purposes but do not exceed the size returned. This function is useful if you
 * are running out of space in the bss or heap and need a little extra memory.
 *
 * @param[out] free Set to start of free available RAM
 * @returns Size of available RAM
 */
size_t os_MemChk(void **free);

/**
 * Routine checks the amount of free archive
 */
tiflags void os_ArcChk(void);

/**
 * @return A pointer to symtable of the OS
 */
void *os_GetSymTablePtr(void);

/**
 * @return next entry or NULL if no more entries, pass os_GetSymTablePtr() as first entry
 */
void *os_NextSymEntry(void *entry, uint24_t *type, uint24_t *nameLength, char *name, void **data);

/**
 * Delete a var from RAM.
 *
 * @param[in] entry An entry as returned from os_NextSymEntry().
 * @return TIOS System Error Code or 0 on success.
 */
int os_DelSymEntry(void *entry);

/**
 * Creates an TIOS Str.
 *
 * @param[in] name Name of the Str to create.
 * @param[in] data Initial contents of the created Str.
 * @returns A TIOS error code, or 0 on success.
 */
int os_CreateString(const char *name, const string_t *data);

/**
 * Gets a pointer to an TIOS Str's data, which may be in archive.
 *
 * @param[in] name Name of the Str to lookup.
 * @param[in] archived Set to 1 if the Str is archived, otherwise 0, may be NULL if you don't need it.
 * @returns A pointer to the Str data
 * @note Returns NULL if the Str doesn't exist, otherwise a pointer to the size bytes.
 */
string_t *os_GetStringData(const char *name, int *archived);

/**
 * Creates a TIOS Equ.
 *
 * @param[in] name Name of the Equ to create.
 * @param[in] data Initial contents of the created Equ.
 * @returns A TIOS error code, or 0 on success.
 */
int os_CreateEquation(const char *name, const equ_t *data);

/**
 * Gets a pointer to an TIOS Equ's data, which may be in archive.
 *
 * @param[in] name Name of the Equ to lookup.
 * @param[in] archived Set to 1 if the Equ is archived, otherwise 0, may be NULL if you don't need it.
 * @returns A pointer to the Equ data.
 * @note Returns NULL if the Equ doesn't exist, otherwise a pointer to the size bytes.
 */
equ_t *os_GetEquationData(const char *name, int *archived);

/**
 * Creates a TIOS AppVar.
 *
 * @param[in] name Name of the AppVar to create.
 * @param[in] size Size of AppVar to create.
 * @returns A pointer to the AppVar data.
 * @note Returns NULL if creation failed for some reason, otherwise a pointer to the size bytes.
 * @note If successful, the AppVar contents will be uninitialized, aka filled with random bytes.
 */
var_t *os_CreateAppVar(const char *name, uint16_t size);

/**
 * Gets a pointer to a TIOS AppVar's data, which may be in archive.
 *
 * @param[in] name Name of the AppVar to lookup.
 * @param[in] archived Set to 1 if the AppVar is archived, otherwise 0, may be NULL if you don't need it.
 * @returns A pointer to the AppVar data.
 * @note Returns NULL if the AppVar doesn't exist, otherwise a pointer to the size bytes.
 */
var_t *os_GetAppVarData(const char *name, int *archived);

/**
 * Deletes an AppVar from RAM.
 *
 * @param[in] name Name of the AppVar to delete.
 */
void os_DelAppVar(const char *name);

/**
 * Locates a symbol in the symtable
 *
 * @param[in] type Type of symbol to find
 * @param[in] name Pointer to name of symbol to find
 * @param[out] entry Can be NULL if you don't care
 * @param[out] data Can be NULL if you don't care
 * @return If file exists, returns 1 and sets entry and data, otherwise returns 0.
 */
int os_ChkFindSym(uint8_t type, const char *name, void **entry, void **data);

/**
 * Gets the size of sized vars such as equations, string, programs, appvars,
 * or the dimension of a list.
 *
 * @param[in] name Name of the var to lookup.
 * @param[out] size Pointer to store size of variable.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetVarSize(const char *name, size_t *size);

/**
 * Gets the dimensions of a matrix.
 *
 * @param[in] name Name of the matrix to lookup.
 * @param[in] rows Pointer to store number of rows.
 * @param[in] cols Pointer to store number of columns.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetMatrixDims(const char *name, int *rows, int *cols);

/**
 * Gets a real value from a real list or a complex list where the selected
 * element has no imaginary component.
 *
 * @param[in] name Name of the list.
 * @param[in] index Element index (1-based).
 * @param[out] value Set to the value of the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetRealListElement(const char *name, int index, real_t *value);

/**
 * Gets a real value from a matrix.
 *
 * @param[in] name Name of the matrix.
 * @param[in] row Element row (1-based).
 * @param[in] col Element col (1-based).
 * @param[out] value Set to the value of the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetMatrixElement(const char *name, int row, int col, real_t *value);

/**
 * Gets the real value of a real variable or a complex variable with
 * no imaginary component.
 *
 * @param[in] name Name of TIOS variable.
 * @param[out] value Set to the value of the variable.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetRealVar(const char *name, real_t *value);

/**
 * If list \p name doesn't exist, create it with \p dim elements, otherwise
 * resize the list, with new elements being set to 0.
 *
 * @param[in] name Name of the list to resize.
 * @param[in] dim New list dimension.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetListDim(const char *name, int dim);

/**
 * If matrix \p name doesn't exist, create it with dimensions \p rows and
 * \p cols, otherwise resize the matrix, with new elements being set to 0.
 *
 * @param[in] name Name of the matrix to resize.
 * @param[in] rows New row dimension.
 * @param[in] cols New col dimension.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetMatrixDims(const char *name, int rows, int cols);

/**
 * Sets a list element to a real value.  If the list doesn't exist, then index
 * must be 1 and it creates a 1 element list.
 *
 * @param[in] name Name of the list.
 * @param[in] index Element index (1-based).
 * @param[in] value The value to set to the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetRealListElement(const char *name, int index, const real_t *value);

/**
 * Sets a matrix element to a real value.
 *
 * @param[in] name Name of the matrix.
 * @param[in] row Element row (1-based).
 * @param[in] col Element col (1-based).
 * @param[in] value The value to set to the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetMatrixElement(const char *name, int row, int col, const real_t *value);

/**
 * Sets a variable to a real value, creating it if it doesn't exist.
 *
 * @param[in] name Name of variable to lookup.
 * @param[in] value The value to set the variable to.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetRealVar(const char *name, const real_t *value);

/**
 * Gets the Ans variable
 *
 * @param[in] type This is set to the current variable type in ANS
 * @returns Pointer to the data
 * @note Returns NULL if Ans doesn't exist or type is NULL
 */
void *os_GetAnsData(uint8_t *type);

/**
 * Invalidate and clear stat variables
 */
tiflags void os_DelRes(void);

/**
 * @brief Callback function pointer type for os_RunPrgm
 * @see os_RunPrgm
 */
typedef int (*os_runprgm_callback_t)(void *data, int retval);

/**
 * Runs a program that exists on the calculator.
 * Note that this will destroy the currently running program, requiring you to
 * save any data as needed. This program has an optional callback that will be
 * executed when the called program finishes, which can be used to rebuild the
 * program state. Additionally, program context information can be safely
 * stored by using the extra user data arguments, which will then be delivered
 * to the callback.
 *
 * @param[in] prgm Name of program to execute.
 * @param[in] data User data that will be available in the callback function.
 * May be \c NULL.
 * @param[in] size Size of user data (keep this small, it is stored on the stack!)
 * @param[in] callback Callback function to run when program finishes executing.
 * The argument \p data will contain the provided \p data contents, and \p
 * retval will contain the error code if a TI-BASIC program, or the exit code if
 * a C program. Other types of programs may have an undefined \p retval. This
 * argument may be left \c NULL if execution should not return to the calling
 * program.
 *
 * @return This function should not return, but if it does, -1 indicates the
 * program could not be found, -2 if not enough memory, and < 0 if some other
 * error occurred.
 *
 * @note The callback return code is passed to the launcher of the original program that called this function.
 */
int os_RunPrgm(const char *prgm, void *data, size_t size, os_runprgm_callback_t callback);

#define os_RamStart          ((uint8_t*)0xD00000) /**< Start of RAM. Type: `uint8_t[1024 * 256]`*/

#define os_RclFlags          (*(uint8_t*)0xD0008E) /**< @see `<ti/flags.h>` */

#define os_AppData           ((uint8_t*)0xD00429) /**< Generally unused by the OS. Type: `uint8_t[256]` */

#define os_ProgToEdit        ((char*)0xD0065B)
#define os_NameBuff          ((char*)0xD00663)

#define os_AsmPrgmSize          (*(uint16_t*)0xD0118C) /**< Current size of executing program. Type: `uint16_t` */

#define os_TempFreeArc       (*(uint24_t*)0xD02655)        /**< Set after asm_ArcChk call. Type: `uint24_t` */

/**
 * When writing to flash, the calculator's hardware cannot read from flash.
 * So the flash writing code has to be copied to RAM first.
 * It is copied here.
 * You can use this as long as you don't attempt any flash writes.
 * 
 * Type: `uint8_t[1023]`
 */
#define os_RamCode           ((uint8_t*)0xD18C7C)

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
