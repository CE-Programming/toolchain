/**
 * @file
 *
 * @author Matt "MateoConLechuga" Waltz
 */

#ifndef _FILEIOC_H
#define _FILEIOC_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ti/vars.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TI_PRGM_TYPE            (0x05) /**< Unprotected program */
#define TI_PPRGM_TYPE           (0x06) /**< Protected program */
#define TI_TPRGM_TYPE           (0x16) /**< Temporary program */
#define TI_APPVAR_TYPE          (0x15) /**< AppVar */
#define TI_STRING_TYPE          (0x04) /**< String */
#define TI_EQU_TYPE             (0x03) /**< Equation */
#define TI_ANS_TYPE             (0x00) /**< Ans */
#define TI_REAL_LIST_TYPE       (0x01) /**< Real variable list */
#define TI_CPLX_LIST_TYPE       (0x0D) /**< Complex variable list */
#define TI_REAL_TYPE            (0x00) /**< Real variable */
#define TI_CPLX_TYPE            (0x0C) /**< Complex variable */
#define TI_MATRIX_TYPE          (0x02) /**< Matrix variable */

#define TI_MAX_SIZE             (65505) /**< Maximum variable size */

/* @cond */
#ifndef EOF
#define EOF (-1)
#endif
/* @endcond */


/**
 * Opens an AppVar for reading, writing, and/or appending.
 * AppVars may be stored in either the archive (aka flash memory), or in RAM.
 * Depending on the mode used to open the AppVar it may be moved from archive memory into RAM.
 * \rst
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | **mode**     | **Description**                                                                                                                 |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | "r"          | Read mode. If the AppVar does not exist :code:`0` is returned. The AppVar is not moved from its storage location.               |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | "w"          | Write mode. Deletes any existing AppVar and creates the AppVar in RAM.                                                          |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | "a"          | Append mode. The AppVar is created if it does not exist. If the AppVar is stored in the archive it is moved to RAM.             |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | "r+"         | Read/Write mode. If the AppVar does not exist :code:`0` is returned. If the AppVar is stored in the archive it is moved to RAM. |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | "w+"         | Write/Read mode. Deletes any existing AppVar and creates the AppVar in RAM.                                                     |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 *   | "a+"         | Append/Read mode. The AppVar is created if it does not exist. If the AppVar is stored in the archive it is moved to RAM.        |
 *   +--------------+---------------------------------------------------------------------------------------------------------------------------------+
 * \endrst
 * @param[in] name Name of AppVar to open.
 * @param[in] mode Documented in the above table.
 * @returns AppVar variable handle, or `0` (zero) on error.
 */
uint8_t ti_Open(const char *name, const char *mode);

/**
 * Opens a variable for reading, writing, and/or appending.
 * Variables may be stored in either the archive (aka flash memory), or in RAM.
 * Depending on the mode used to open the variable it may be moved from archive memory into RAM.
 * \rst
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | **mode**     | **Description**                                                                                                                     |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | "r"          | Read mode. If the variable does not exist :code:`0` is returned. The variable is not moved from its storage location.               |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | "w"          | Write mode. Deletes any existing variable and creates the variable in RAM.                                                          |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | "a"          | Append mode. The variable is created if it does not exist. If the variable is stored in the archive it is moved to RAM.             |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | "r+"         | Read/Write mode. If the variable does not exist :code:`0` is returned. If the variable is stored in the archive it is moved to RAM. |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | "w+"         | Write/Read mode. Deletes any existing variable and creates the variable in RAM.                                                     |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 *   | "a+"         | Append/Read mode. The variable is created if it does not exist. If the variable is stored in the archive it is moved to RAM.        |
 *   +--------------+-------------------------------------------------------------------------------------------------------------------------------------+
 * \endrst
 * @param[in] name Name of variable to open.
 * @param[in] mode Documented in the above table.
 * @param[in] type Variable type.
 * @returns Variable handle, or `0` (zero) on error.
 */
uint8_t ti_OpenVar(const char *name, const char *mode, uint8_t type);

/**
 * Closes an open AppVar/variable handle.
 * This must be performed for every ti_Open or ti_OpenVar call.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns `0` (zero) on error.
 */
int ti_Close(uint8_t handle);

/**
 * Locates AppVars stored in archive and RAM.
 * This function searches for AppVars whose data section begins with a specific string.
 * The null terminator of the string is not included in the search.
 *
 * \p vat_ptr should be set to NULL to begin a search, and is updated with each call.
 *
 * @code{.cpp}
 * char *var_name;
 * void *vat_ptr = NULL;
 *
 * while ((var_name = ti_Detect(&vat_ptr, "my_data")))
 * {
 *     // do something with var_name or vat_ptr
 * }
 * @endcode
 *
 * @param[in] vat_ptr Current offset in the VAT.
 * @param[in] detect_string String to search for (NULL to search for all).
 * @returns The AppVar name. This should be duplicated to another buffer
 *          as subsequent calls of this function change the name stored at the
 *          returned pointer's address.
 * @note If the return value is NULL, there are no more variables to find.
 */
char *ti_Detect(void **vat_ptr, const char *detect_string);

/**
 * Locates variables stored in archive and RAM.
 * This function searches for variables whose data section begins with a specific string.
 * The null terminator of the string is not included in the search.
 *
 * \p vat_ptr should be set to NULL to begin a search, and is updated with each call.
 *
 * @code{.cpp}
 * char *var_name;
 * void *vat_ptr = NULL;
 *
 * while ((var_name = ti_DetectVar(&vat_ptr, "my_data", TI_PRGM_TYPE)))
 * {
 *     // do something with var_name or vat_ptr
 * }
 * @endcode
 *
 * @param[in,out] vat_ptr Current offset in the VAT.
 * @param[in] detect_string String to search for (NULL to search for all).
 * @param[in] var_type Type of variable to detect.
 * @returns The variable name. This should be duplicated to another buffer
 *          as subsequent calls of this function change the name stored at the
 *          returned pointer's address.
 * @note If the return value is NULL, there are no more variables to find.
 */
char *ti_DetectVar(void **vat_ptr, const char *detect_string, uint8_t var_type);

/**
 * Locates any variables stored in archive and RAM.
 * This function searches for variables whose data section begins with a specific string.
 * The null terminator of the string is not included in the search.
 *
 * \p vat_ptr should be set to NULL to begin a search, and is updated with each call.
 *
 * @code{.cpp}
 * uint8_t var_type;
 * char *var_name;
 * void *vat_ptr = NULL;
 *
 * while ((var_name = ti_DetectAny(&vat_ptr, "my_data", &var_type)))
 * {
 *     if (var_type == TI_PRGM_TYPE || var_type == TI_PPRGM_TYPE)
 *     {
 *         // do something with var_name or vat_ptr
 *     }
 * }
 * @endcode
 *
 * @param[in,out] vat_ptr Current offset in the VAT.
 * @param[in] detect_string String to search for (NULL to search for all).
 * @param[out] var_type Type of variable found.
 * @returns The variable name. This should be duplicated to another buffer
 *          as subsequent calls of this function change the name stored at the
 *          returned pointer's address.
 * @note If the return value is NULL, there are no more variables to find.
 */
char *ti_DetectAny(void **vat_ptr, const char *detect_string, uint8_t *var_type);

/**
 * Writes data to an AppVar/variable handle.
 *
 * @param[in] data Pointer to data structure(s).
 * @param[in] size Size (in bytes) of a single \p data structure.
 * @param[in] count Number of \p data structures to write.
 * @param[in] handle AppVar/variable handle.
 * @returns Number of data structures written; equals count on success.
 */
size_t ti_Write(const void *data, size_t size, size_t count, uint8_t handle);

/**
 * Reads data from an AppVar/variable handle.
 *
 * @param[out] data Pointer to data structure(s).
 * @param[in] size Size (in bytes) of a single \p data structure.
 * @param[in] count Number of \p data structures to write.
 * @param[in] handle AppVar/variable handle.
 * @returns Number of data structures written; equals count on success.
 */
size_t ti_Read(void *data, size_t size, size_t count, uint8_t handle);

/**
 * Writes a character to an AppVar/variable handle.
 *
 * @param[in] ch Character to write.
 * @param[in] handle AppVar/variable handle.
 * @returns `EOF` on error, or \p ch.
 */
int ti_PutC(char ch, uint8_t handle);

/**
 * Reads a character from an AppVar/variable handle.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns `EOF` on error, or a valid character.
 */
int ti_GetC(uint8_t handle);

/**
 * Seeks to an offset in the file.
 * \rst
 *   +--------------+-------------------------------------------------------+
 *   | **origin**   | **Description**                                       |
 *   +--------------+-------------------------------------------------------+
 *   | SEEK_SET     | Seek from beginning of AppVar/variable.               |
 *   +--------------+-------------------------------------------------------+
 *   | SEEK_CUR     | Seek from current AppVar/variable offset.             |
 *   +--------------+-------------------------------------------------------+
 *   | SEEK_END     | Seek from end of AppVar/variable.                     |
 *   +--------------+-------------------------------------------------------+
 * \endrst
 * @param[in] offset Number of bytes to offest from (can be negative).
 * @param[in] origin Documented in the above table.
 * @param[in] handle AppVar/variable handle.
 * @returns `EOF` on failure.
 */
int ti_Seek(int offset, unsigned int origin, uint8_t handle);

/**
 * Seeks to the start of an AppVar/variable's data.
 * Functionally equivalent to <tt>ti_Seek(0, SEEK_SET, handle)</tt>
 *
 * @param[in] handle AppVar/variable handle.
 * @returns `EOF` on failure.
 */
int ti_Rewind(uint8_t handle);

/**
 * Gets the current data offset from the start of an AppVar/variable.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns The current data offset from the start of the AppVar/variable.
 */
uint16_t ti_Tell(uint8_t handle);

/**
 * Gets the size of an AppVar/variable.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns The size of the AppVar/variable.
 */
uint16_t ti_GetSize(uint8_t handle);

/**
 * Resizes an AppVar/variable.
 *
 * @param[in] handle AppVar/variable handle.
 * @param[in] size New AppVar/variable size.
 * @returns Resized size on success, `0` on failure, or `-1` if the AppVar/variable cannot be opened.
 */
int ti_Resize(size_t size, uint8_t handle);

/**
 * Checks if an AppVar/variable is stored in archive memory.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns `0` if the AppVar/variable is not in the archive.
 */
int ti_IsArchived(uint8_t handle);

/**
 * Moves an AppVar/variable between archive or RAM storage.
 * \rst
 *   +-------------+-----------------------------------------+
 *   | **archive** | **Description**                         |
 *   +-------------+-----------------------------------------+
 *   | true        | Store AppVar/variable in archive.       |
 *   +-------------+-----------------------------------------+
 *   | false       | Store AppVar/variable in RAM.           |
 *   +-------------+-----------------------------------------+
 * \endrst
 * @param[in] archive Documented in the above table.
 * @param[in] handle AppVar/variable handle.
 * @returns `0` on failure.
 *
 * @warning Archiving a variable can cause a garbage collection cycle.
 * You should use ti_SetGCBehavior to catch this event.
 */
int ti_SetArchiveStatus(bool archive, uint8_t handle);

/**
 * Deletes an AppVar.
 *
 * @param[in] name AppVar name.
 * @returns `0` on failure.
 */
int ti_Delete(const char *name);

/**
 * Deletes a variable.
 *
 * @param[in] name Variable name.
 * @param[in] type Variable type.
 * @returns `0` on failure.
 */
int ti_DeleteVar(const char *name, uint8_t type);

/**
 * Gets the string used for displaying a TI token.
 * The TI calculators encode programs and other variables in "tokens", which are
 * either 1 or 2 bytes in length. For example, the token :code:`0x21`
 * corresponds to the string :code:`mean(` in TI-BASIC programs. This allows
 * program size to be reduced as the whole string is not stored - but requires
 * additional decoding in order to resolve the token's string representation.
 *
 * @param[in,out] read_pointer Address of pointer to data to read.
 * @returns A pointer to a null-terminated string used for displaying a TI token.
 * @param[out] token_len Pointer to variable to hold length of the token,
 * used for determining the next read location (Can be NULL if unused).
 * @param[out] str_len Pointer to variable to hold length of resulting
 * string (Can be NULL if unused). The returned string is static, and should be
 * copied to another buffer as needed if it needs to be preserved across
 * function calls.
 *
 * @note \p read_pointer is automatically updated to point to the next token,
 * incremented by the value of \p token_len.
 */
char *ti_GetTokenString(void **read_pointer, uint8_t *token_len, unsigned int *str_len);

/**
 * Gets a direct data pointer to the current offset in an AppVar/variable.
 * This may be used for direct reading/writing without the need for an extra
 * copy. It is easily prone to memory corruption if not used correctly, so use
 * at your own risk.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns Pointer to AppVar/variable data.
 *
 * @note If the AppVar is in RAM, the direct pointer can be used to read/modify
 * its contents directly, with the caveat that the AppVar must be large enough
 * to consume any writes. If the AppVar is in the archive, direct reading is
 * possible but writes will lead to a system reset.
 *
 * @warning This function is potentially unsafe to use as variables may be
 * shifted around in memory, causing this pointer to become invalid and
 * potentially corrupt memory. Avoid creating, deleting, resizing, or changing
 * the storage location any variables while this pointer is being actively used.
 */
void *ti_GetDataPtr(uint8_t handle);

/**
 * Gets a pointer to the VAT entry of an AppVar/variable.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns VAT location of the variable.
 *
 * @note If the variable is in RAM, the direct pointer can be used to
 * read/modify its contents directly, with the caveat that the AppVar must be
 * large enough to consume any writes. If the AppVar is in the archive, direct
 * reading is possible but writes will lead to a system reset.
 *
 * @warning This function is potentially unsafe to use as variables may be
 * shifted around in memory, causing this pointer to become invalid and
 * potentially corrupt memory. Avoid creating, deleting, resizing, or changing
 * the storage location any variables while this pointer is being actively used.
 */
void *ti_GetVATPtr(uint8_t handle);

/**
 * Gets the AppVar/variable name of an already opened handle.
 *
 * @param[in] name Buffer to store name, must be at least 10 bytes in sizew.
 * @param[in] handle AppVar/variable handle.
 */
void ti_GetName(char *name, uint8_t handle);

/**
 * Renames an AppVar.
 *
 * @param[in] old_name Old name of AppVar.
 * @param[in] new_name New name of AppVar.
 * @returns `0` if success, `1` if AppVar already exists, `2` any other error occurs.
 *
 * @warning It is hazardous to rename an open AppVar.
 * Close the AppVar before renaming.
 */
uint8_t ti_Rename(const char *old_name, const char *new_name);

/**
 * Renames a variable.
 *
 * @param[in] old_name Old name of variable.
 * @param[in] new_name New name of variable.
 * @param[in] type Type of variable.
 * @returns `0` if success, `1` if variable already exists, `2` any other error occurs.
 *
 * @warning It is hazardous to rename an open variable.
 * Close the variable before renaming.
 */
uint8_t ti_RenameVar(const char *old_name, const char *new_name, uint8_t type);

/**
 * Stores data or values to an OS variable.
 *
 * @param[in] type Variable type.
 * @param[in] name Variable name.
 * @param[in] data Data to set variable to.
 *
 * @returns `0` if success.
 */
uint8_t ti_SetVar(uint8_t type, const char *name, const void *data);

/**
 * Stores an OS variable to another variable.
 *
 * @param[in] type_to Variable type to store data to.
 * @param[in] to Variable name to store data to.
 * @param[in] type_from Variable type to get data from.
 * @param[in] from Variable name to get data from.
 * @returns `0` if success.
 */
uint8_t ti_StoVar(uint8_t type_to, const char *to, uint8_t type_from, const char *from);

/**
 * Recalls a OS variable.
 *
 * @param[in] type Variable type.
 * @param[in] name Variable name.
 * @param[out] data Address of pointer to variable structure.
 * @returns `0` if success.
 *
 * @note data_struct is set to the variable's data.
 */
uint8_t ti_RclVar(uint8_t type, const char *name, void **data);

/**
 * Checks to see if there is room in the archive for storing \p num_bytes,
 * without needing to execute a Garbage Collect.
 *
 * @param[in] num_bytes Number of bytes to be stored to the archive.
 * @returns `true` if the bytes can be stored to the archive without a Garbage Collect.
 */
bool ti_ArchiveHasRoom(uint24_t num_bytes);

/**
 * Set routines to run before and after a garbage collect would be triggered.
 * A garbage collect is used to free up space in archive memory by reorganizing
 * archive variable storage and removing variables marked for deletion. The OS
 * is required to request the user if they want to perform the operation,
 * and this request may be triggered any time a variable is moved to archive
 * memory. This function is used to set up callbacks that are triggered when
 * this event occurs.
 *
 * The OS prompt requires the LCD to be in the standard 16-bit color mode, so
 * if `graphx` or custom LCD behavior is being used `gfx_End` should be used
 * to restore the OS to its default state in the routine run before garbage
 * collection.
 *
 * In the after garbage collection rotuine, the LCD state can be restored (using
 * `gfx_Begin` or similar as appropriate), as well as potentially reloading
 * cached variable pointers created with ti_GetDataPtr.
 * 
 * @param[in] before Routine to run before a garbage collect. NULL sets it to do nothing.
 * @param[in] after Routine to run following a garbage collect. NULL sets it to do nothing.
 * */
void ti_SetGCBehavior(void (*before)(void), void (*after)(void));

/** @addtogroup Variables
 *  @{
 */

/* @cond */
#define ti_Ans      ("\x72\0")

#define ti_Str1     ("\xAA\x0\0")
#define ti_Str2     ("\xAA\x1\0")
#define ti_Str3     ("\xAA\x2\0")
#define ti_Str4     ("\xAA\x3\0")
#define ti_Str5     ("\xAA\x4\0")
#define ti_Str6     ("\xAA\x5\0")
#define ti_Str7     ("\xAA\x6\0")
#define ti_Str8     ("\xAA\x7\0")
#define ti_Str9     ("\xAA\x8\0")
#define ti_Str0     ("\xAA\x9\0")
#define ti_StrT     ('\xAA')

/* Some equation definitions */
#define ti_Y1       ("\x5E\x10\0")
#define ti_Y2       ("\x5E\x11\0")
#define ti_Y3       ("\x5E\x12\0")
#define ti_Y4       ("\x5E\x13\0")
#define ti_Y5       ("\x5E\x14\0")
#define ti_Y6       ("\x5E\x15\0")
#define ti_Y7       ("\x5E\x16\0")
#define ti_Y8       ("\x5E\x17\0")
#define ti_Y9       ("\x5E\x18\0")
#define ti_Y0       ("\x5E\x19\0")
#define ti_EquT     ('\x5E')

/* Some real and complex defines */
#define ti_A        ("\x41\0\0")
#define ti_B        ("\x42\0\0")
#define ti_C        ("\x43\0\0")
#define ti_D        ("\x44\0\0")
#define ti_E        ("\x45\0\0")
#define ti_F        ("\x46\0\0")
#define ti_G        ("\x47\0\0")
#define ti_H        ("\x48\0\0")
#define ti_I        ("\x49\0\0")
#define ti_J        ("\x4A\0\0")
#define ti_K        ("\x4B\0\0")
#define ti_L        ("\x4C\0\0")
#define ti_M        ("\x4D\0\0")
#define ti_N	    ("\x4E\0\0")
#define ti_O        ("\x4F\0\0")
#define ti_P        ("\x50\0\0")
#define ti_Q        ("\x51\0\0")
#define ti_R        ("\x52\0\0")
#define ti_S        ("\x53\0\0")
#define ti_T        ("\x54\0\0")
#define ti_U        ("\x55\0\0")
#define ti_V        ("\x56\0\0")
#define ti_W        ("\x57\0\0")
#define ti_X        ("\x58\0\0")
#define ti_Y        ("\x59\0\0")
#define ti_Z        ("\x60\0\0")
#define ti_Theta    ("\x61\0\0")

/* Some matrix defines */
#define ti_MatA     ("\x5C\x0\0")
#define ti_MatB     ("\x5C\x1\0")
#define ti_MatC     ("\x5C\x2\0")
#define ti_MatD     ("\x5C\x3\0")
#define ti_MatE     ("\x5C\x4\0")
#define ti_MatF     ("\x5C\x5\0")
#define ti_MatG     ("\x5C\x6\0")
#define ti_MatH     ("\x5C\x7\0")
#define ti_MatI     ("\x5C\x8\0")
#define ti_MatJ     ("\x5C\x9\0")
#define ti_MatT     ('\x5C')

/*  Some list defines */
#define ti_L1        ("\x5D\x0\0")
#define ti_L2        ("\x5D\x1\0")
#define ti_L3        ("\x5D\x2\0")
#define ti_L4        ("\x5D\x3\0")
#define ti_L5        ("\x5D\x4\0")
#define ti_L6        ("\x5D\x5\0")
#define ti_LT        ('\x5D')
/* @endcond */

/** @}*/

/* Compatibility defines */
/* @cond */
string_t *ti_AllocString(unsigned len, void *(*malloc_routine)(size_t)) __attribute__((deprecated ("This function is deprecated")));
list_t *ti_AllocList(unsigned dim, void *(*malloc_routine)(size_t)) __attribute__((deprecated ("This function is deprecated")));
matrix_t *ti_AllocMatrix(uint8_t rows, uint8_t cols, void *(*malloc_routine)(size_t)) __attribute__((deprecated ("This function is deprecated")));
cplx_list_t *ti_AllocCplxList(unsigned dim, void *(*malloc_routine)(size_t)) __attribute__((deprecated ("This function is deprecated")));
equ_t *ti_AllocEqu(unsigned len, void *(*malloc_routine)(size_t)) __attribute__((deprecated ("This function is deprecated")));
#define ti_MallocReal() ((real_t*)malloc(sizeof(real_t)))
#define ti_MallocCplx() ((cplx_t*)malloc(sizeof(cplx_t)))
#define ti_MallocString(len) ti_AllocString((len), malloc)
#define ti_MallocList(dim) ti_AllocList((dim), malloc)
#define ti_MallocMatrix(rows, cols) ti_AllocMatrix((rows), (cols), malloc)
#define ti_MallocCplxList(dim) ti_AllocCplxList((dim), malloc)
#define ti_MallocEqu(len) ti_AllocEqu((len), malloc)
#define ti_Program             _Pragma("GCC warning \"'ti_Program' is deprecated, use 'TI_PRGM_TYPE' instead\"") TI_PRGM_TYPE
#define ti_ProtectedProgram    _Pragma("GCC warning \"'ti_ProtectedProgram' is deprecated, use 'TI_PPRGM_TYPE' instead\"") TI_PPRGM_TYPE
#define ti_TempProgram         _Pragma("GCC warning \"'ti_TempProgram' is deprecated, use 'TI_TPRGM_TYPE' instead\"") TI_TPRGM_TYPE
#define ti_AppVar              _Pragma("GCC warning \"'ti_AppVar' is deprecated, use 'TI_APPVAR_TYPE' instead\"") TI_APPVAR_TYPE
typedef uint8_t ti_var_t;
void ti_CloseAll(void) __attribute__((deprecated ("Use ti_Close(handle) for each handle instead")));
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
