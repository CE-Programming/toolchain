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

#ifndef _TI_USER_VARIABLES_H
#define _TI_USER_VARIABLES_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

#ifndef _TI_REAL_STRUCT /* X-ref with real.h */
#define _TI_REAL_STRUCT
/**
 * @brief Structure of real variable type
 */
typedef struct { int8_t sign, exp; uint8_t mant[7]; } real_t;
/**
 * @brief Structure of complex variable type
 */
typedef struct { real_t real, imag; } cplx_t;
#endif
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
 * @param free Set to start of free available RAM
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
 * @param entry An entry as returned from os_NextSymEntry().
 * @return TIOS System Error Code or 0 on success.
 */
int os_DelSymEntry(void *entry);

/**
 * Creates an TIOS Str.
 *
 * @param name Name of the Str to create.
 * @param data Initial contents of the created Str.
 * @returns A TIOS error code, or 0 on success.
 */
int os_CreateString(const char *name, const string_t *data);

/**
 * Gets a pointer to an TIOS Str's data, which may be in archive.
 *
 * @param name Name of the Str to lookup.
 * @param archived Set to 1 if the Str is archived, otherwise 0, may be NULL if you don't need it.
 * @returns A pointer to the Str data
 * @note Returns NULL if the Str doesn't exist, otherwise a pointer to the size bytes.
 */
string_t *os_GetStringData(const char *name, int *archived);

/**
 * Creates a TIOS Equ.
 *
 * @param name Name of the Equ to create.
 * @param data Initial contents of the created Equ.
 * @returns A TIOS error code, or 0 on success.
 */
int os_CreateEquation(const char *name, const equ_t *data);

/**
 * Gets a pointer to an TIOS Equ's data, which may be in archive.
 *
 * @param name Name of the Equ to lookup.
 * @param archived Set to 1 if the Equ is archived, otherwise 0, may be NULL if you don't need it.
 * @returns A pointer to the Equ data.
 * @note Returns NULL if the Equ doesn't exist, otherwise a pointer to the size bytes.
 */
equ_t *os_GetEquationData(const char *name, int *archived);

/**
 * Creates a TIOS AppVar.
 *
 * @param name Name of the AppVar to create.
 * @param size Size of AppVar to create.
 * @returns A pointer to the AppVar data.
 * @note Returns NULL if creation failed for some reason, otherwise a pointer to the size bytes.
 * @note If successful, the AppVar contents will be uninitialized, aka filled with random bytes.
 */
var_t *os_CreateAppVar(const char *name, uint16_t size);

/**
 * Gets a pointer to a TIOS AppVar's data, which may be in archive.
 *
 * @param name Name of the AppVar to lookup.
 * @param archived Set to 1 if the AppVar is archived, otherwise 0, may be NULL if you don't need it.
 * @returns A pointer to the AppVar data.
 * @note Returns NULL if the AppVar doesn't exist, otherwise a pointer to the size bytes.
 */
var_t *os_GetAppVarData(const char *name, int *archived);

/**
 * Deletes an AppVar from RAM.
 *
 * @param name Name of the AppVar to delete.
 */
void os_DelAppVar(const char *name);

/**
 * Locates a symbol in the symtable
 *
 * @param type Type of symbol to find
 * @param name Pointer to name of symbol to find
 * @param entry Can be NULL if you don't care
 * @param data Can be NULL if you don't care
 * @return If file exists, returns 1 and sets entry and data, otherwise returns 0.
 */
int os_ChkFindSym(uint8_t type, const char *name, void **entry, void **data);

/**
 * Gets the size of sized vars such as equations, string, programs, appvars,
 * or the dimension of a list.
 *
 * @param name Name of the var to lookup.
 * @param size Pointer to store size of variable.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetVarSize(const char *name, size_t *size);

/**
 * Gets the dimensions of a matrix.
 *
 * @param name Name of the matrix to lookup.
 * @param rows Pointer to store number of rows.
 * @param cols Pointer to store number of columns.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetMatrixDims(const char *name, int *rows, int *cols);

/**
 * Gets a real value from a real list or a complex list where the selected
 * element has no imaginary component.
 *
 * @param name Name of the list.
 * @param index Element index (1-based).
 * @param value Set tto the value of the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetRealListElement(const char *name, int index, real_t *value);

/**
 * Gets a real value from a matrix.
 *
 * @param name Name of the matrix.
 * @param row Element row (1-based).
 * @param col Element col (1-based).
 * @param value Set to the value of the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetMatrixElement(const char *name, int row, int col, real_t *value);

/**
 * Gets the real value of a real variable or a complex variable with
 * no imaginary component.
 *
 * @param name Name of TIOS variable.
 * @param value Set to the value of the variable.
 * @return TIOS System Error Code or 0 on success.
 */
int os_GetRealVar(const char *name, real_t *value);

/**
 * If list \p name doesn't exist, create it with \p dim elements, otherwise
 * resize the list, with new elements being set to 0.
 *
 * @param name Name of the list to resize.
 * @param dim New list dimension.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetListDim(const char *name, int dim);

/**
 * If matrix \p name doesn't exist, create it with dimensions \p rows and
 * \p cols, otherwise resize the matrix, with new elements being set to 0.
 *
 * @param name Name of the matrix to resize.
 * @param rows New row dimension.
 * @param cols New col dimension.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetMatrixDims(const char *name, int rows, int cols);

/**
 * Sets a list element to a real value.  If the list doesn't exist, then index
 * must be 1 and it creates a 1 element list.
 *
 * @param name Name of the list.
 * @param index Element index (1-based).
 * @param value The value to set to the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetRealListElement(const char *name, int index, const real_t *value);

/**
 * Sets a matrix element to a real value.
 *
 * @param name Name of the matrix.
 * @param row Element row (1-based).
 * @param col Element col (1-based).
 * @param value The value to set to the selected element.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetMatrixElement(const char *name, int row, int col, const real_t *value);

/**
 * Sets a variable to a real value, creating it if it doesn't exist.
 *
 * @param name Name of variable to lookup.
 * @param value The value to set the variable to.
 * @return TIOS System Error Code or 0 on success.
 */
int os_SetRealVar(const char *name, const real_t *value);

/**
 * Gets the Ans variable
 *
 * @param type This is set to the current variable type in ANS
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
 * @param prgm Name of program to execute.
 * @param data User data that will be available in the callback function.
 * May be \c NULL.
 * @param size Size of user data (keep this small, it is stored on the stack!)
 * @param callback Callback function to run when program finishes executing. The
 * argument \p data will contain the provided \p data contents, and \p retval
 * will contain the error code if a TI-BASIC program, or the exit code if a C
 * program. Other types of programs may have an undefined \p retval. This
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

#define os_RamStart          ((uint8_t*)0xD00000)

#define os_RclFlags          (*(uint8_t*)0xD0008E)

#define os_AppData           ((uint8_t*)0xD00429)

#define os_OP1                  ((uint8_t*)0xD005F8) /**< OP1 Variable */
#define os_OP2                  ((uint8_t*)0xD00603) /**< OP2 Variable */
#define os_OP3                  ((uint8_t*)0xD0060E) /**< OP3 Variable */
#define os_OP4                  ((uint8_t*)0xD00619) /**< OP4 Variable */
#define os_OP5                  ((uint8_t*)0xD00624) /**< OP5 Variable */
#define os_OP6                  ((uint8_t*)0xD0062F) /**< OP6 Variable */
#define os_OP7                  ((uint8_t*)0xD0063A) /**< OP7 Variable */

#define os_ProgToEdit        ((char*)0xD0065B)
#define os_NameBuff          ((char*)0xD00663)

#define os_AsmPrgmSize          (*(uint16_t*)0xD0118C) /**< Current size of executing program. */

#define os_StatVars          ((uint8_t*)0xD01191)

#define os_uXMin             (*(real_t*)0xD01D61)
#define os_uXMax             (*(real_t*)0xD01D6A)
#define os_uXScl             (*(real_t*)0xD01D73)
#define os_uYMin             (*(real_t*)0xD01D7C)
#define os_uYMax             (*(real_t*)0xD01D85)
#define os_uYScl             (*(real_t*)0xD01D8E)
#define os_uThetaMin         (*(real_t*)0xD01D97)
#define os_uThetaMax         (*(real_t*)0xD01DA0)
#define os_uThetaStep        (*(real_t*)0xD01DA9)
#define os_uTmin             (*(real_t*)0xD01DB2)
#define os_uTmax             (*(real_t*)0xD01DBB)
#define os_uTStep            (*(real_t*)0xD01DC4)
#define os_uPlotStart        (*(real_t*)0xD01DCD)
#define os_unMax             (*(real_t*)0xD01DD6)
#define os_uu0               (*(real_t*)0xD01DDF)
#define os_uv0               (*(real_t*)0xD01DE8)
#define os_unMin             (*(real_t*)0xD01DF1)
#define os_uu02              (*(real_t*)0xD01DFA)
#define os_uv02              (*(real_t*)0xD01E03)
#define os_uw0               (*(real_t*)0xD01E0C)
#define os_uPlotStep         (*(real_t*)0xD01E15)
#define os_uXres             (*(real_t*)0xD01E1E)
#define os_uw02              (*(real_t*)0xD01E27)
#define os_XMin              (*(real_t*)0xD01E33)
#define os_XMax              (*(real_t*)0xD01E3C)
#define os_XScl              (*(real_t*)0xD01E45)
#define os_YMin              (*(real_t*)0xD01E4E)
#define os_YMax              (*(real_t*)0xD01E57)
#define os_YScl              (*(real_t*)0xD01E60)
#define os_ThetaMin          (*(real_t*)0xD01E69)
#define os_ThetaMax          (*(real_t*)0xD01E72)
#define os_ThetaStep         (*(real_t*)0xD01E7B)
#define os_TMinPar           (*(real_t*)0xD01E84)
#define os_TMaxPar           (*(real_t*)0xD01E8D)
#define os_TStep             (*(real_t*)0xD01E96)
#define os_PlotStart         (*(real_t*)0xD01E9F)
#define os_NMax              (*(real_t*)0xD01EA8)
#define os_u0                (*(real_t*)0xD01EB1)
#define os_V0                (*(real_t*)0xD01EBA)
#define os_NMin              (*(real_t*)0xD01EC3)
#define os_u02               (*(real_t*)0xD01ECC)
#define os_V02               (*(real_t*)0xD01ED5)
#define os_W0                (*(real_t*)0xD01EDE)
#define os_PlotStep          (*(real_t*)0xD01EE7)
#define os_XResO             (*(real_t*)0xD01EF0)
#define os_W02               (*(real_t*)0xD01EF9)
#define os_un1               (*(real_t*)0xD01F02)
#define os_un2               (*(real_t*)0xD01F0B)
#define os_Vn1               (*(real_t*)0xD01F14)
#define os_Vn2               (*(real_t*)0xD01F1D)
#define os_Wn1               (*(real_t*)0xD01F26)
#define os_Wn2               (*(real_t*)0xD01F2F)
#define os_Fin_N             (*(real_t*)0xD01F38)
#define os_Fin_I             (*(real_t*)0xD01F41)
#define os_Fin_PV            (*(real_t*)0xD01F4A)
#define os_Fin_PMT           (*(real_t*)0xD01F53)
#define os_Fin_FV            (*(real_t*)0xD01F5C)
#define os_Fin_PY            (*(real_t*)0xD01F65)
#define os_Fin_CY            (*(real_t*)0xD01F6E)
#define os_Cal_N             (*(real_t*)0xD01F77)
#define os_Cal_I             (*(real_t*)0xD01F80)
#define os_Cal_PV            (*(real_t*)0xD01F89)
#define os_Cal_PMT           (*(real_t*)0xD01F92)
#define os_Cal_FV            (*(real_t*)0xD01F9B)
#define os_Cal_PY            (*(real_t*)0xD01FA4)

#define os_Y1LineType        (*(uint8_t*)0xD024BF)
#define os_Y2LineType        (*(uint8_t*)0xD024C0)
#define os_Y3LineType        (*(uint8_t*)0xD024C1)
#define os_Y4LineType        (*(uint8_t*)0xD024C2)
#define os_Y5LineType        (*(uint8_t*)0xD024C3)
#define os_Y6LineType        (*(uint8_t*)0xD024C4)
#define os_Y7LineType        (*(uint8_t*)0xD024C5)
#define os_Y8LineType        (*(uint8_t*)0xD024C6)
#define os_Y9LineType        (*(uint8_t*)0xD024C7)
#define os_Y0LineType        (*(uint8_t*)0xD024C8)
#define os_Para1LineType     (*(uint8_t*)0xD024C9)
#define os_Para2LineType     (*(uint8_t*)0xD024CA)
#define os_Para3LineType     (*(uint8_t*)0xD024CB)
#define os_Para4LineType     (*(uint8_t*)0xD024CC)
#define os_Para5LineType     (*(uint8_t*)0xD024CD)
#define os_Para6LineType     (*(uint8_t*)0xD024CE)
#define os_Polar1LineType    (*(uint8_t*)0xD024CF)
#define os_Polar2LineType    (*(uint8_t*)0xD024D0)
#define os_Polar3LineType    (*(uint8_t*)0xD024D1)
#define os_Polar4LineType    (*(uint8_t*)0xD024D2)
#define os_Polar5LineType    (*(uint8_t*)0xD024D3)
#define os_Polar6LineType    (*(uint8_t*)0xD024D4)
#define os_SecULineType      (*(uint8_t*)0xD024D5)
#define os_SecVLineType      (*(uint8_t*)0xD024D6)
#define os_SecWLineType      (*(uint8_t*)0xD024D7)
#define os_Y1LineColor       (*(uint8_t*)0xD024D8)
#define os_Y2LineColor       (*(uint8_t*)0xD024D9)
#define os_Y3LineColor       (*(uint8_t*)0xD024DA)
#define os_Y4LineColor       (*(uint8_t*)0xD024DB)
#define os_Y5LineColor       (*(uint8_t*)0xD024DC)
#define os_Y6LineColor       (*(uint8_t*)0xD024DD)
#define os_Y7LineColor       (*(uint8_t*)0xD024DE)
#define os_Y8LineColor       (*(uint8_t*)0xD024DF)
#define os_Y9LineColor       (*(uint8_t*)0xD024E0)
#define os_Y0LineColor       (*(uint8_t*)0xD024E1)
#define os_Para1LineColor    (*(uint8_t*)0xD024E2)
#define os_Para2LineColor    (*(uint8_t*)0xD024E3)
#define os_Para3LineColor    (*(uint8_t*)0xD024E4)
#define os_Para4LineColor    (*(uint8_t*)0xD024E5)
#define os_Para5LineColor    (*(uint8_t*)0xD024E6)
#define os_Para6LineColor    (*(uint8_t*)0xD024E7)
#define os_Polar1LineColor   (*(uint8_t*)0xD024E8)
#define os_Polar2LineColor   (*(uint8_t*)0xD024E9)
#define os_Polar3LineColor   (*(uint8_t*)0xD024EA)
#define os_Polar4LineColor   (*(uint8_t*)0xD024EB)
#define os_Polar5LineColor   (*(uint8_t*)0xD024EC)
#define os_Polar6LineColor   (*(uint8_t*)0xD024ED)
#define os_SecULineColor     (*(uint8_t*)0xD024EE)
#define os_SecVLineColor     (*(uint8_t*)0xD024EF)
#define os_SecWLineColor     (*(uint8_t*)0xD024F0)

#define os_TempFreeArc       (*(uint24_t*)0xD02655)        /**< Set after asm_ArcChk call */

#define os_RamCode           ((uint8_t*)0xD18C7C)          /**< 1023 bytes free ram */

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
