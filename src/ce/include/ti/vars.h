/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS user variables and memory
 * 
 * This declares routines for low-level access to user variables (AppVars, programs, Str0-9, matrix, &c.),
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

/** Start of RAM. Type: `uint8_t[1024 * 256]`*/
#define os_RamStart        ((uint8_t*)0xD00000)

/** @see `<ti/flags.h>` */
#define os_RclFlags        (*(uint8_t*)0xD0008E)

/** Generally unused by the OS. Type: `uint8_t[256]` */
#define os_AppData         ((uint8_t*)0xD00429)

/* @cond */
#define os_ProgToEdit      ((char*)0xD0065B)
#define os_NameBuff        ((char*)0xD00663)
/* @endcond */

/** Current size of executing program. Type: `uint24_t` */
#define os_AsmPrgmSize     (*(uint24_t*)0xD0118C)

/** Set after asm_ArcChk call. Type: `uint24_t` */
#define os_TempFreeArc     (*(uint24_t*)0xD02655)

/**
 * When writing to flash, the calculator's hardware cannot read from flash.
 * So the flash writing code has to be copied to RAM first.
 * It is copied here.
 * You can use this as long as you don't attempt any flash writes.
 * 
 * Type: `uint8_t[1023]`
 */
#define os_RamCode         ((uint8_t*)0xD18C7C)

/**
 * Gets an element from a matrix
 *
 * @param matrix Structure of matrix
 * @param row Row in matrix
 * @param col Column in matrix
 * @returns real_t containing element data
 */
#define OS_MATRIX_ELEMENT(matrix, row, col) ((matrix)->items[(col)+(row)*(matrix)->cols])

/** Maximum size of OS variable */
#define OS_VAR_MAX_SIZE      (65512)

/** Real variable */
#define OS_TYPE_REAL         (0x00)
/** Real variable list */
#define OS_TYPE_REAL_LIST    (0x01)
/** Matrix variable */
#define OS_TYPE_MATRIX       (0x02)
/** Equation */ 
#define OS_TYPE_EQU          (0x03)
/** String */
#define OS_TYPE_STR          (0x04)
/** Unprotected program */
#define OS_TYPE_PRGM         (0x05)
/** Protected (uneditable) program */
#define OS_TYPE_PROT_PRGM    (0x06)
/** Complex variable */
#define OS_TYPE_CPLX         (0x0C)
/** Complex variable list */
#define OS_TYPE_CPLX_LIST    (0x0D)
/** AppVar */
#define OS_TYPE_APPVAR       (0x15)
/** Temporary program, deleted on homescreen */
#define OS_TYPE_TMP_PRGM     (0x16)

/** Name of Ans variable */
#define OS_VAR_ANS      "\x72\0"

/**
 * Name of Str1 string variable.
 * Other Str variables follow the naming format `OS_VAR_STR?` where `?`
 * is the value [0-9].
 */
#define OS_VAR_STR1     "\xAA\x0\0"
/* @cond */
#define OS_VAR_STR2     "\xAA\x1\0"
#define OS_VAR_STR3     "\xAA\x2\0"
#define OS_VAR_STR4     "\xAA\x3\0"
#define OS_VAR_STR5     "\xAA\x4\0"
#define OS_VAR_STR6     "\xAA\x5\0"
#define OS_VAR_STR7     "\xAA\x6\0"
#define OS_VAR_STR8     "\xAA\x7\0"
#define OS_VAR_STR9     "\xAA\x8\0"
#define OS_VAR_STR0     "\xAA\x9\0"
/* @endcond */

/**
 * Name of Y1 equation variable.
 * Other Y variables follow the naming format `OS_VAR_Y?` where `?` is [0-9].
 */
#define OS_VAR_Y1       "\x5E\x10\0"
/* @cond */
#define OS_VAR_Y2       "\x5E\x11\0"
#define OS_VAR_Y3       "\x5E\x12\0"
#define OS_VAR_Y4       "\x5E\x13\0"
#define OS_VAR_Y5       "\x5E\x14\0"
#define OS_VAR_Y6       "\x5E\x15\0"
#define OS_VAR_Y7       "\x5E\x16\0"
#define OS_VAR_Y8       "\x5E\x17\0"
#define OS_VAR_Y9       "\x5E\x18\0"
#define OS_VAR_Y0       "\x5E\x19\0"
/* @endcond */

/**
 * Name of A real variable.
 * Other real variables follow the naming format `OS_VAR_?` where `?` is [A-Z] (and THETA).
 */
#define OS_VAR_A        "\x41\0\0"
/* @cond */
#define OS_VAR_B        "\x42\0\0"
#define OS_VAR_C        "\x43\0\0"
#define OS_VAR_D        "\x44\0\0"
#define OS_VAR_E        "\x45\0\0"
#define OS_VAR_F        "\x46\0\0"
#define OS_VAR_G        "\x47\0\0"
#define OS_VAR_H        "\x48\0\0"
#define OS_VAR_I        "\x49\0\0"
#define OS_VAR_J        "\x4A\0\0"
#define OS_VAR_K        "\x4B\0\0"
#define OS_VAR_L        "\x4C\0\0"
#define OS_VAR_M        "\x4D\0\0"
#define OS_VAR_N        "\x4E\0\0"
#define OS_VAR_O        "\x4F\0\0"
#define OS_VAR_P        "\x50\0\0"
#define OS_VAR_Q        "\x51\0\0"
#define OS_VAR_R        "\x52\0\0"
#define OS_VAR_S        "\x53\0\0"
#define OS_VAR_T        "\x54\0\0"
#define OS_VAR_U        "\x55\0\0"
#define OS_VAR_V        "\x56\0\0"
#define OS_VAR_W        "\x57\0\0"
#define OS_VAR_X        "\x58\0\0"
#define OS_VAR_Y        "\x59\0\0"
#define OS_VAR_Z        "\x5A\0\0"
#define OS_VAR_THETA    "\x5B\0\0"
/* @endcond */

/**
 * Name of A matrix variable.
 * Other matrix variables follow the naming format `OS_VAR_MAT_?` where `?`
 * is value [A-J].
 */
#define OS_VAR_MAT_A    "\x5C\x0\0"
/* @cond */
#define OS_VAR_MAT_B    "\x5C\x1\0"
#define OS_VAR_MAT_C    "\x5C\x2\0"
#define OS_VAR_MAT_D    "\x5C\x3\0"
#define OS_VAR_MAT_E    "\x5C\x4\0"
#define OS_VAR_MAT_F    "\x5C\x5\0"
#define OS_VAR_MAT_G    "\x5C\x6\0"
#define OS_VAR_MAT_H    "\x5C\x7\0"
#define OS_VAR_MAT_I    "\x5C\x8\0"
#define OS_VAR_MAT_J    "\x5C\x9\0"
/* @endcond */

/**
 * Name of L1 list variable.
 * Other list variables follow the naming format `OS_VAR_L?` where `?`
 * is the value [1-6].
 */
#define OS_VAR_L1       "\x5D\x0\0"
/* @cond */
#define OS_VAR_L2       "\x5D\x1\0"
#define OS_VAR_L3       "\x5D\x2\0"
#define OS_VAR_L4       "\x5D\x3\0"
#define OS_VAR_L5       "\x5D\x4\0"
#define OS_VAR_L6       "\x5D\x5\0"
/* @endcond */

/**
 * @brief Structure of list variable type
 */
typedef struct list_t { uint16_t dim; real_t items[1]; } list_t;
/**
 * @brief Structure of complex list variable type
 */
typedef struct cplx_list_t { uint16_t dim; cplx_t items[1]; } cplx_list_t;
/**
 * @brief Structure of matrix variable type
 */
typedef struct matrix_t { uint8_t cols, rows; real_t items[1]; } matrix_t;
/**
 * @brief Structure of string variable type
 */
typedef struct string_t { uint16_t len; char data[1]; } string_t;
/**
 * @brief Structure of equation variable type
 */
typedef struct equ_t { uint16_t len; char data[1]; } equ_t;
/**
 * @brief Structure of miscellaneous variable type
 */
typedef struct var_t { uint16_t size; uint8_t data[1]; } var_t;

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
 * Iterates over the OS symbol table.
 * This table stores the name and pointers to the variables (such as AppVars and programs)
 * on the calculator. This function can be used to find all the variables on the calculator,
 * to search for a specific variable the function os_ChkFindSym should be used instead.
 *
 * @param[in] entry Current iterative entry, pass the output of os_GetSymTablePtr to start the search.
 * @param[in] type Type of variable returned.
 * @param[in] nameLength Length of variable name. The name may not be null-terminated.
 * @param[in] name Variable name.
 * @param[in] data Returns a pointer to the variable's data, which may be in either RAM or flash.
 * @return next entry to pass to the \p entry argument on subsequent calls.
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
 * Note that this will destroy the currently running program. The function has
 * an optional callback entry point for when a program finishes, which can be
 * used to rebuild the program context. Additional program context information
 * can be safely stored by using the extra \p data argument, which is
 * delivered to the callback entry point.
 *
 * @param[in] prgm Name of program to execute.
 * @param[in] data User data that will be available in the callback function.
 * May be \c NULL.
 * @param[in] size Size of user data (keep this small, it is stored on the stack!)
 * @param[in] callback This callback is used as the entry point to the program
 * rather than \p main when the called program finishes.
 * The argument \p data will contain the \p data argument, and \p
 * retval will contain the error code if a TI-BASIC program, or the exit code if
 * a C program. Other types of programs may have an undefined \p retval. This
 * argument may be left \c NULL if execution should not return to the calling
 * program.
 *
 * @return This function should not return, but if it does, -1 indicates the
 * program could not be found, -2 if not enough memory, and < 0 if some other
 * error occurred.
 *
 * @note The integer return of the callback acts the same as the integer return
 * of the \p main function, and is returned to the parent caller (either the OS
 * or a shell).
 */
int os_RunPrgm(const char *prgm, void *data, size_t size, os_runprgm_callback_t callback);

/**
 * Evalutes a tokenized expression.
 *
 * @param[in] data Tokenized expression to evaluate.
 * @param[in] len Length of tokenized data.
 * @returns TIOS System Error Code or 0 on success, with the result stored in
 * the Ans variable.
 */
int os_Eval(const void *data, size_t len);

/**
 * Evalutes a tokenized equation or string variable.
 *
 * @param[in] name Name of variable to evaluate.
 * @returns TIOS System Error Code or 0 on success, with the result stored in
 * the Ans variable.
 */
int os_EvalVar(const char *name);

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
