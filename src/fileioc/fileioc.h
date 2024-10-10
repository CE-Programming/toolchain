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

/* @cond */
#ifndef EOF
#define EOF (-1)
#endif
/* @endcond */

/**
 * Allocate a \p real_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @returns Pointer to \p real_t allocated variable.
 */
#define ti_MallocReal() ((real_t*)malloc(sizeof(real_t)))

/**
 * Allocate a \p cplx_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @returns Pointer to \p cplx_t allocated variable.
 */
#define ti_MallocCplx() ((cplx_t*)malloc(sizeof(cplx_t)))

/**
 * Allocate a \p string_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @param[in] len Length of string to allocate in tokens/characters.
 * @returns Pointer to \p string_t allocated variable.
 */
#define ti_MallocString(len) ti_AllocString((len), malloc)

/**
 * Allocate a \p list_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @param[in] dim Dimension of list.
 * @returns Pointer to \p list_t allocated variable.
 */
#define ti_MallocList(dim) ti_AllocList((dim), malloc)

/**
 * Allocate a \p matrix_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @param[in] rows Number of rows in matrix.
 * @param[in] cols Number of columns in matrix.
 * @returns Pointer to \p matrix_t allocated variable.
 */
#define ti_MallocMatrix(rows, cols) ti_AllocMatrix((rows), (cols), malloc)

/**
 * Allocate a \p cplx_list_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @param[in] dim Dimension of list.
 * @returns Pointer to \p cplx_list_t  allocated variable.
 */
#define ti_MallocCplxList(dim) ti_AllocCplxList((dim), malloc)

/**
 * Allocate a \p equ_t variable on the C heap using malloc().
 * Does not modify OS storage. The allocated variable should be
 * free'd with the free() function when you are done using it.
 * @param[in] len Length of equation to allocate in tokens/characters.
 * @returns Pointer to \p equ_t allocated variable.
 */
#define ti_MallocEqu(len) ti_AllocEqu((len), malloc)

/* @cond */
string_t *ti_AllocString(unsigned len, void *(*malloc_routine)(size_t));
list_t *ti_AllocList(unsigned dim, void *(*malloc_routine)(size_t));
matrix_t *ti_AllocMatrix(uint8_t rows, uint8_t cols, void *(*malloc_routine)(size_t));
cplx_list_t *ti_AllocCplxList(unsigned dim, void *(*malloc_routine)(size_t));
equ_t *ti_AllocEqu(unsigned len, void *(*malloc_routine)(size_t));
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
 * while ((var_name = ti_DetectVar(&vat_ptr, "my_data", OS_TYPE_PRGM)))
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
 *     if (var_type == OS_TYPE_PRGM || var_type == OS_TYPE_PROT_PRGM)
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
 * @param[in] data Pointer to data element(s).
 * @param[in] size Size (in bytes) of a single \p data element.
 * @param[in] count Number of \p data elements to write.
 * @param[in] handle AppVar/variable handle.
 * @returns Number of data elements written; equals count on success.
 */
size_t ti_Write(const void *data, size_t size, size_t count, uint8_t handle);

/**
 * Reads data from an AppVar/variable handle.
 *
 * @param[out] data Pointer to data element(s).
 * @param[in] size Size (in bytes) of a single \p data element.
 * @param[in] count Number of \p data elements to read.
 * @param[in] handle AppVar/variable handle.
 * @returns Number of data elements written; equals count on success.
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
 * @returns Resized size on success, `0` on failure, or `-1` if the
 *          AppVar/variable cannot be opened.
 * @warning This function does not maintain the data already stored in the
 *          AppVar/variable when shrinking/expanding, and effectively
 *          corrupts the contents.
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
 * either 1 or 2 bytes in length. For example, the token `0x21`
 * corresponds to the string `mean(` in TI-BASIC programs. This allows
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
 * @returns 0 if success, otherwise TI OS Error Code.
 */
uint8_t ti_SetVar(uint8_t type, const char *name, const void *data);

/**
 * Stores an OS variable to another variable.
 *
 * @param[in] type_to Variable type to store data to.
 * @param[in] to Variable name to store data to.
 * @param[in] type_from Variable type to get data from.
 * @param[in] from Variable name to get data from.
 * @returns 0 if success, otherwise TI OS Error Code.
 */
uint8_t ti_StoVar(uint8_t type_to, const char *to, uint8_t type_from, const char *from);

/**
 * Recalls a OS variable.
 *
 * @param[in] type Variable type.
 * @param[in] name Variable name.
 * @param[out] data Address of pointer to variable structure.
 * @returns 0 if success, otherwise TI OS Error Code.
 */
uint8_t ti_RclVar(uint8_t type, const char *name, void **data);

/**
 * Checks to see if there is room in the archive for storing \p num_bytes,
 * without needing to execute a Garbage Collect.
 *
 * @param[in] num_bytes Number of bytes to be stored to the archive.
 * @returns `true` if the bytes can be stored to the archive without triggering a Garbage Collect.
 */
bool ti_ArchiveHasRoom(uint24_t num_bytes);

/**
 * Checks to see if there is room in the archive for storing an AppVar/variable,
 * without needing to execute a Garbage Collect.
 *
 * @param[in] handle AppVar/variable handle.
 * @returns `true` if archiving the variable will trigger a Garbage Collect.
 */
bool ti_ArchiveHasRoomVar(uint8_t handle);

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

/* @cond */

/* Compatibility type macros */
#define TI_PRGM_TYPE            _Pragma("GCC warning \"'TI_PRGM_TYPE' is deprecated, use 'OS_TYPE_PRGM' instead\"") OS_TYPE_PRGM
#define TI_PPRGM_TYPE           _Pragma("GCC warning \"'TI_PPRGM_TYPE' is deprecated, use 'OS_TYPE_PROT_PRGM' instead\"") OS_TYPE_PROT_PRGM
#define TI_TPRGM_TYPE           _Pragma("GCC warning \"'TI_TPRGM_TYPE' is deprecated, use 'OS_TYPE_TMP_PRGM' instead\"") OS_TYPE_TMP_PRGM
#define TI_APPVAR_TYPE          _Pragma("GCC warning \"'TI_APPVAR_TYPE' is deprecated, use 'OS_TYPE_APPVAR' instead\"") OS_TYPE_APPVAR
#define TI_STRING_TYPE          _Pragma("GCC warning \"'TI_STRING_TYPE' is deprecated, use 'OS_TYPE_STR' instead\"") OS_TYPE_STR
#define TI_EQU_TYPE             _Pragma("GCC warning \"'TI_EQU_TYPE' is deprecated, use 'OS_TYPE_EQU' instead\"") OS_TYPE_EQU
#define TI_ANS_TYPE             _Pragma("GCC warning \"'TI_ANS_TYPE' is deprecated, use the expected type instead\"") (0x00)
#define TI_REAL_LIST_TYPE       _Pragma("GCC warning \"'TI_REAL_LIST_TYPE' is deprecated, use 'OS_TYPE_REAL_LIST' instead\"") OS_TYPE_REAL_LIST
#define TI_CPLX_LIST_TYPE       _Pragma("GCC warning \"'TI_CPLX_LIST_TYPE' is deprecated, use 'OS_TYPE_CPLX_LIST' instead\"") OS_TYPE_CPLX_LIST
#define TI_REAL_TYPE            _Pragma("GCC warning \"'TI_REAL_TYPE' is deprecated, use 'OS_TYPE_CPLX_LIST' instead\"") OS_TYPE_REAL
#define TI_CPLX_TYPE            _Pragma("GCC warning \"'TI_CPLX_TYPE' is deprecated, use 'OS_TYPE_CPLX' instead\"") OS_TYPE_CPLX
#define TI_MATRIX_TYPE          _Pragma("GCC warning \"'TI_MATRIX_TYPE' is deprecated, use 'OS_TYPE_CPLX' instead\"") OS_TYPE_MATRIX
#define TI_MAX_SIZE             _Pragma("GCC warning \"'TI_MAX_SIZE' is deprecated, use 'OS_VAR_MAX_SIZE' instead\"") OS_VAR_MAX_SIZE
#define ti_Program              _Pragma("GCC warning \"'ti_Program' is deprecated, use 'OS_TYPE_PRGM' instead\"") OS_TYPE_PRGM
#define ti_ProtectedProgram     _Pragma("GCC warning \"'ti_ProtectedProgram' is deprecated, use 'OS_TYPE_PROT_PRGM' instead\"") OS_TYPE_PROT_PRGM
#define ti_TempProgram          _Pragma("GCC warning \"'ti_TempProgram' is deprecated, use 'OS_TYPE_TMP_PRGM' instead\"") OS_TYPE_TMP_PRGM
#define ti_AppVar               _Pragma("GCC warning \"'ti_AppVar' is deprecated, use 'OS_TYPE_APPVAR' instead\"") OS_TYPE_APPVAR

/* Compatibility variable macros */
#define ti_Ans      _Pragma("GCC warning \"'ti_Ans' is deprecated, use 'OS_VAR_ANS' instead\"") OS_VAR_ANS
#define ti_Str1     _Pragma("GCC warning \"'ti_Str1' is deprecated, use 'OS_VAR_STR1' instead\"") OS_VAR_STR1
#define ti_Str2     _Pragma("GCC warning \"'ti_Str2' is deprecated, use 'OS_VAR_STR2' instead\"") OS_VAR_STR2
#define ti_Str3     _Pragma("GCC warning \"'ti_Str3' is deprecated, use 'OS_VAR_STR3' instead\"") OS_VAR_STR3
#define ti_Str4     _Pragma("GCC warning \"'ti_Str4' is deprecated, use 'OS_VAR_STR4' instead\"") OS_VAR_STR4
#define ti_Str5     _Pragma("GCC warning \"'ti_Str5' is deprecated, use 'OS_VAR_STR5' instead\"") OS_VAR_STR5
#define ti_Str6     _Pragma("GCC warning \"'ti_Str6' is deprecated, use 'OS_VAR_STR6' instead\"") OS_VAR_STR6
#define ti_Str7     _Pragma("GCC warning \"'ti_Str7' is deprecated, use 'OS_VAR_STR7' instead\"") OS_VAR_STR7
#define ti_Str8     _Pragma("GCC warning \"'ti_Str8' is deprecated, use 'OS_VAR_STR8' instead\"") OS_VAR_STR8
#define ti_Str9     _Pragma("GCC warning \"'ti_Str9' is deprecated, use 'OS_VAR_STR9' instead\"") OS_VAR_STR9
#define ti_Str0     _Pragma("GCC warning \"'ti_Str0' is deprecated, use 'OS_VAR_STR0' instead\"") OS_VAR_STR0
#define ti_Y1       _Pragma("GCC warning \"'ti_Y1' is deprecated, use 'OS_VAR_Y1' instead\"") OS_VAR_Y1
#define ti_Y2       _Pragma("GCC warning \"'ti_Y2' is deprecated, use 'OS_VAR_Y2' instead\"") OS_VAR_Y2
#define ti_Y3       _Pragma("GCC warning \"'ti_Y3' is deprecated, use 'OS_VAR_Y3' instead\"") OS_VAR_Y3
#define ti_Y4       _Pragma("GCC warning \"'ti_Y4' is deprecated, use 'OS_VAR_Y4' instead\"") OS_VAR_Y4
#define ti_Y5       _Pragma("GCC warning \"'ti_Y5' is deprecated, use 'OS_VAR_Y5' instead\"") OS_VAR_Y5
#define ti_Y6       _Pragma("GCC warning \"'ti_Y6' is deprecated, use 'OS_VAR_Y6' instead\"") OS_VAR_Y6
#define ti_Y7       _Pragma("GCC warning \"'ti_Y7' is deprecated, use 'OS_VAR_Y7' instead\"") OS_VAR_Y7
#define ti_Y8       _Pragma("GCC warning \"'ti_Y8' is deprecated, use 'OS_VAR_Y8' instead\"") OS_VAR_Y8
#define ti_Y9       _Pragma("GCC warning \"'ti_Y9' is deprecated, use 'OS_VAR_Y9' instead\"") OS_VAR_Y9
#define ti_Y0       _Pragma("GCC warning \"'ti_Y0' is deprecated, use 'OS_VAR_Y0' instead\"") OS_VAR_Y0
#define ti_A        _Pragma("GCC warning \"'ti_A' is deprecated, use 'OS_VAR_A' instead\"") OS_VAR_A
#define ti_B        _Pragma("GCC warning \"'ti_B' is deprecated, use 'OS_VAR_B' instead\"") OS_VAR_B
#define ti_C        _Pragma("GCC warning \"'ti_C' is deprecated, use 'OS_VAR_C' instead\"") OS_VAR_C
#define ti_D        _Pragma("GCC warning \"'ti_D' is deprecated, use 'OS_VAR_D' instead\"") OS_VAR_D
#define ti_E        _Pragma("GCC warning \"'ti_E' is deprecated, use 'OS_VAR_E' instead\"") OS_VAR_E
#define ti_F        _Pragma("GCC warning \"'ti_F' is deprecated, use 'OS_VAR_F' instead\"") OS_VAR_F
#define ti_G        _Pragma("GCC warning \"'ti_G' is deprecated, use 'OS_VAR_G' instead\"") OS_VAR_G
#define ti_H        _Pragma("GCC warning \"'ti_H' is deprecated, use 'OS_VAR_H' instead\"") OS_VAR_H
#define ti_I        _Pragma("GCC warning \"'ti_I' is deprecated, use 'OS_VAR_I' instead\"") OS_VAR_I
#define ti_J        _Pragma("GCC warning \"'ti_J' is deprecated, use 'OS_VAR_J' instead\"") OS_VAR_J
#define ti_K        _Pragma("GCC warning \"'ti_K' is deprecated, use 'OS_VAR_K' instead\"") OS_VAR_K
#define ti_L        _Pragma("GCC warning \"'ti_L' is deprecated, use 'OS_VAR_L' instead\"") OS_VAR_L
#define ti_M        _Pragma("GCC warning \"'ti_M' is deprecated, use 'OS_VAR_M' instead\"") OS_VAR_M
#define ti_N	    _Pragma("GCC warning \"'ti_N' is deprecated, use 'OS_VAR_N' instead\"") OS_VAR_N
#define ti_O        _Pragma("GCC warning \"'ti_O' is deprecated, use 'OS_VAR_O' instead\"") OS_VAR_O
#define ti_P        _Pragma("GCC warning \"'ti_P' is deprecated, use 'OS_VAR_P' instead\"") OS_VAR_P
#define ti_Q        _Pragma("GCC warning \"'ti_Q' is deprecated, use 'OS_VAR_Q' instead\"") OS_VAR_Q
#define ti_R        _Pragma("GCC warning \"'ti_R' is deprecated, use 'OS_VAR_R' instead\"") OS_VAR_R
#define ti_S        _Pragma("GCC warning \"'ti_S' is deprecated, use 'OS_VAR_S' instead\"") OS_VAR_S
#define ti_T        _Pragma("GCC warning \"'ti_T' is deprecated, use 'OS_VAR_T' instead\"") OS_VAR_T
#define ti_U        _Pragma("GCC warning \"'ti_U' is deprecated, use 'OS_VAR_U' instead\"") OS_VAR_U
#define ti_V        _Pragma("GCC warning \"'ti_V' is deprecated, use 'OS_VAR_V' instead\"") OS_VAR_V
#define ti_W        _Pragma("GCC warning \"'ti_W' is deprecated, use 'OS_VAR_W' instead\"") OS_VAR_W
#define ti_X        _Pragma("GCC warning \"'ti_X' is deprecated, use 'OS_VAR_X' instead\"") OS_VAR_X
#define ti_Y        _Pragma("GCC warning \"'ti_Y' is deprecated, use 'OS_VAR_Y' instead\"") OS_VAR_Y
#define ti_Z        _Pragma("GCC warning \"'ti_Z' is deprecated, use 'OS_VAR_Z' instead\"") OS_VAR_Z
#define ti_Theta    _Pragma("GCC warning \"'ti_Theta' is deprecated, use 'OS_VAR_THETA' instead\"") OS_VAR_THETA
#define ti_MatA     _Pragma("GCC warning \"'ti_MatA' is deprecated, use 'OS_VAR_MAT_A' instead\"") OS_VAR_MAT_A
#define ti_MatB     _Pragma("GCC warning \"'ti_MatB' is deprecated, use 'OS_VAR_MAT_B' instead\"") OS_VAR_MAT_B
#define ti_MatC     _Pragma("GCC warning \"'ti_MatC' is deprecated, use 'OS_VAR_MAT_C' instead\"") OS_VAR_MAT_C
#define ti_MatD     _Pragma("GCC warning \"'ti_MatD' is deprecated, use 'OS_VAR_MAT_D' instead\"") OS_VAR_MAT_D
#define ti_MatE     _Pragma("GCC warning \"'ti_MatE' is deprecated, use 'OS_VAR_MAT_E' instead\"") OS_VAR_MAT_E
#define ti_MatF     _Pragma("GCC warning \"'ti_MatF' is deprecated, use 'OS_VAR_MAT_F' instead\"") OS_VAR_MAT_F
#define ti_MatG     _Pragma("GCC warning \"'ti_MatG' is deprecated, use 'OS_VAR_MAT_G' instead\"") OS_VAR_MAT_G
#define ti_MatH     _Pragma("GCC warning \"'ti_MatH' is deprecated, use 'OS_VAR_MAT_H' instead\"") OS_VAR_MAT_H
#define ti_MatI     _Pragma("GCC warning \"'ti_MatI' is deprecated, use 'OS_VAR_MAT_I' instead\"") OS_VAR_MAT_I
#define ti_MatJ     _Pragma("GCC warning \"'ti_MatJ' is deprecated, use 'OS_VAR_MAT_J' instead\"") OS_VAR_MAT_J
#define ti_L1       _Pragma("GCC warning \"'ti_L1' is deprecated, use 'OS_VAR_L1' instead\"") OS_VAR_L1
#define ti_L2       _Pragma("GCC warning \"'ti_L2' is deprecated, use 'OS_VAR_L2' instead\"") OS_VAR_L2
#define ti_L3       _Pragma("GCC warning \"'ti_L3' is deprecated, use 'OS_VAR_L3' instead\"") OS_VAR_L3
#define ti_L4       _Pragma("GCC warning \"'ti_L4' is deprecated, use 'OS_VAR_L4' instead\"") OS_VAR_L4
#define ti_L5       _Pragma("GCC warning \"'ti_L5' is deprecated, use 'OS_VAR_L5' instead\"") OS_VAR_L5
#define ti_L6       _Pragma("GCC warning \"'ti_L6' is deprecated, use 'OS_VAR_L6' instead\"") OS_VAR_L6

/* Compatibility typedefs */
typedef uint8_t ti_var_t;

/* Compatibility functions */
void ti_CloseAll(void) __attribute__((deprecated ("Use ti_Close(handle) for each handle instead")));
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
