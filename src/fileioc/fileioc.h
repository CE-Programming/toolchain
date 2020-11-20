/**
 * @file
 * @brief fileioc implements OS variable access routines.
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
#include <tice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Varible and flag definitions */
#define TI_PRGM_TYPE            (0x05) /**< Normal unprotect program type.  */
#define TI_PPRGM_TYPE           (0x06) /**< Normal protected program type.  */
#define TI_TPRGM_TYPE           (0x16) /**< Normal temporary program type.  */
#define TI_APPVAR_TYPE          (0x15) /**< AppVar type.  */
#define TI_STRING_TYPE          (0x04) /**< String type.  */
#define TI_EQU_TYPE             (0x03) /**< Equation type.  */
/* @cond */
#define TI_REAL_LIST_TYPE       (0x01)
#define TI_CPLX_LIST_TYPE       (0x0D)
#define TI_REAL_TYPE            (0x00)
#define TI_CPLX_TYPE            (0x0C)
#define TI_MATRIX_TYPE          (0x02)
/* @endcond */

/**
 * Maximum object size in bytes
 */
#define TI_MAX_SIZE             (65505)

/* @cond */
#ifndef EOF
#define EOF (-1)
#endif
/* @endcond */

/**
 * @brief Variable slot type.
 */
typedef uint8_t ti_var_t;

/**
 * Closes all open slots.
 *
 * @warning Call before you use any variable functions
 */
void ti_CloseAll(void);

/**
 * Opens a file.
 *
 * An AppVar is used as default file storage.
 *
 * @param name Name of file to open
 * @param mode
 * "r"  - Opens a file for reading. The file must exist. Keeps file in archive if in archive.                                   <br>
 * "w"  - Creates an empty file for writing. Overwrites file if already exists.                                                 <br>
 * "a"  - Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.  <br>
 * "r+" - Opens a file to update both reading and writing. The file must exist. Moves file from archive to RAM if in archive.   <br>
 * "w+" - Creates an empty file for both reading and writing. Overwrites file if already exists.                                <br>
 * "a+" - Opens a file for reading and appending. Moves file from archive to RAM if in archive. Created if it does not exist.
 * @returns Slot variable
 * @note If there isn't enough memory to create the variable, or a slot isn't open, zero (0) is returned
 */
ti_var_t ti_Open(const char *name, const char *mode);

/**
 * Opens a variable
 *
 * Can open any type of program or appvar variable
 * @param varname Name of variable to open
 * @param mode
 * "r"  - Opens a file for reading. The file must exist. Keeps file in archive if in archive.                                   <br>
 * "w"  - Creates an empty file for writing. Overwrites file if already exists.                                                 <br>
 * "a"  - Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.  <br>
 * "r+" - Opens a file to update both reading and writing. The file must exist. Moves file from archive to RAM if in archive.   <br>
 * "w+" - Creates an empty file for both reading and writing. Overwrites file if already exists.                                <br>
 * "a+" - Opens a file for reading and appending. Moves file from archive to RAM if in archive. Created if it does not exist.
 * @param type Specifies the type of variable to open
 * @returns Slot variable
 * @note If there isn't enough memory to create the variable, or a slot isn't open, zero (0) is returned
 */
ti_var_t ti_OpenVar(const char *varname, const char *mode, uint8_t type);

/**
 * Frees an open variable slot.
 *
 * @returns Zero if closing failed.
 */
int ti_Close(const ti_var_t slot);

/**
 * Returns the name of the file(s) that contains the string as the first part of the variable;
 * which can then be used with ti_Open and other functions.
 *
 * \p seach_pos should be set to NULL to begin a search, and is updated with each call.
 *
 * @code
 *  char *var_name;
 *  uint8_t *search_pos = NULL;
 *  while((var_name = ti_Detect(&search_pos, "my_data")) != NULL) {
 *    ...do something with the name or search_pos...
 *  }
 * @endcode
 *
 * @param curr_search_posistion Current offset in the VAT.
 * @param detection_string String to search for (NULL to search for all).
 * @note If the return value is NULL, there are no more variables to find.
 */
char *ti_Detect(void **curr_search_posistion, const char *detection_string);

/**
 * Returns the name of the file(s) that contains the string as the first part of the variable;
 * which can then be used with ti_OpenVar and other functions.
 *
 * \p seach_pos should be set to NULL to begin a search, and is updated with each call.
 *
 * @code
 *  char *var_name;
 *  uint8_t *search_pos = NULL;
 *  while((var_name = ti_DetectVar(&search_pos, "my_data", TI_PRGM_TYPE)) != NULL) {
 *    ...do something with the name or search_pos...
 *  }
 * @endcode
 *
 * @param curr_search_posistion Current offset in the VAT.
 * @param detection_string String to search for (NULL to search for all).
 * @param var_type Type of variable to detect.
 * @note If the return value is NULL, there are no more variables to find.
 */
char *ti_DetectVar(void **curr_search_posistion, const char *detection_string, uint8_t var_type);

/**
 * Returns the name of the file(s) that contains the string as the first part of the variable;
 * which can then be used with ti_OpenVar and other functions.
 *
 * \p seach_pos should be set to NULL to begin a search, and is updated with each call.
 *
 * @code
 *  char *var_name;
 *  uint8_t *search_pos = NULL;
 *  uint8_t type;
 *  while((var_name = ti_DetectVar(&search_pos, "my_data", &type)) != NULL) {
 *    if (type == TI_PRGM_TYPE || type == TI_PPRGM_TYPE) {
 *     ...do something with the name or search_pos...
 *    }
 *  }
 * @endcode
 *
 * @param curr_search_posistion Current offset in the VAT.
 * @param detection_string String to search for (NULL to search for all).
 * @param var_type Type of variable found.
 * @note If the return value is NULL, there are no more variables to find.
 */
char *ti_DetectAny(void **curr_search_posistion, const char *detection_string, uint8_t *var_type);

/**
 * Writes to the current variable slot.
 *
 * @param data Pointer to data to write.
 * @param size Size (in bytes) of a single data chunk.
 * @param count Number of data chunks to write to the variable slot.
 * @param slot Variable slot to write the data to.
 *
 * @returns The number of chunks written (should be equal to count)
 */
size_t ti_Write(const void *data, size_t size, size_t count, const ti_var_t slot);

/**
 * Reads from the current variable pointer.
 *
 * @param data Pointer to data to read into.
 * @param size Size (in bytes) of a single data chunk.
 * @param count Number of data chunks to read from the variable slot.
 * @param slot Variable slot to read the data from.
 *
 * @returns The number of chunks read (should be equal to count).
 */
size_t ti_Read(void *data, size_t size, size_t count, const ti_var_t slot);

/**
 * Writes a character directly into the slot data pointer, and increments the offset.
 *
 * @param c Character to write.
 * @param slot Variable slot to put the character to.
 * @returns The input c is returned if no error.
 *
 * @returns 'EOF' if current offset is larger than file size, or memory isn't large enough.
 */
int ti_PutC(const char c, const ti_var_t slot);

/**
 * Pulls a character directly from the slot data pointer, and increments the offset.
 *
 * @param slot Variable slot to get the character from.
 * @returns 1 byte character at the current variable offset.
 * @returns 'EOF' if current offset is larger than file size.
 */
int ti_GetC(const ti_var_t slot);

/**
 * Seeks to an offset in the file.
 *
 * @param offset Number of bytes to offest from (can be negative).
 * @param origin
 * SEEK_SET (0) - Seek from beginning of file        <br>
 * SEEK_CUR (1) - Seek from current offset in file   <br>
 * SEEK_END (2) - Seek from end of file
 * @param slot Variable slot seeking in.
 *
 * @returns 'EOF' on seek failure.
 */
int ti_Seek(int offset, unsigned int origin, const ti_var_t slot);

/**
 * Seeks to the start of a slot.
 *
 * Same functionality as <tt>ti_Seek(0, SEEK_SET, slot)</tt>
 *
 * @param slot Variable slot to rewind
 *
 * @returns 'EOF' on rewind failure
 */
int ti_Rewind(const ti_var_t slot);

/**
 * Gets the offset in a slot.
 *
 * @param slot Slot to test.
 * @returns The value of the current slot offset.
 */
uint16_t ti_Tell(const ti_var_t slot);

/**
 * Gets the size of a slot.
 *
 * @param slot Slot to test.
 * @returns The size of the slot variable.
 */
uint16_t ti_GetSize(const ti_var_t slot);

/**
 * Resizes the slot variable.
 *
 * @param slot Slot to resize.
 * @param new_size New size of slot.
 *
 * @returns Resized size on success, 0 on failure, or -1 if the slot cannot be opened.
 *
 * @note The variable offset is set to the beginning of the file.
 */
int ti_Resize(size_t new_size, const ti_var_t slot);

/**
 * Tests if a slot is in the archive.
 *
 * @param slot Slot to test.
 *
 * @returns 0 if the slot is not in the archive.
 */
int ti_IsArchived(const ti_var_t slot);

/**
 * Sends the variable into either the archive or RAM if needed.
 *
 * @warning Archiving a variable can cause a garbage collection cycle.
 * You should use ti_SetGCBehavior in the case of this event.
 *
 * @param archived
 * True - Send to Archive. <br>
 * False - Send to RAM.
 * @param slot Slot to send.
 *
 * @returns 0 if the operation fails from not enough memory.
 */
int ti_SetArchiveStatus(bool archived, const ti_var_t slot);

/**
 * Deletes an AppVar.
 *
 * @param name Name of AppVar to delete.
 *
 * @returns 0 if an error is encountered.
 */
int ti_Delete(const char *name);

/**
 * Deletes a variable given the name and type.
 *
 * @param varname Name of variable to delete.
 * @param type Type of variable to delete.
 *
 * @returns 0 if an error is encountered.
 */
int ti_DeleteVar(const char *varname, const uint8_t type);

/**
 * Gets the string used for displaying a TI token.
 *
 * @param length_of_string Pointer to variable to hold length of resulting string (Can be NULL if you don't care).
 * @param length_of_token Pointer to variable to hold length of the token, used for determining the next read location (Can be NULL if you don't care).
 * @param read_pointer Address of pointer to data to read.
 *
 * @returns A pointer to string used for displaying a TI token.
 * @note read_pointer is updated to the next token, depending on if it is 1 or 2 bytes in length
 */
char *ti_GetTokenString(void **read_pointer, uint8_t *length_of_token, unsigned int *length_of_string);

/**
 * Gets a pointer to the data located at the current posistion in the slot, a
 * good way for fast reading of data.
 *
 * @param slot Slot variable to get pointer of.
 *
 * @returns Pointer to variable data
 */
void *ti_GetDataPtr(const ti_var_t slot);

/**
 * Gets the VAT location of the slot.
 *
 * @param slot Slot variable to get VAT location of.
 * @returns VAT location of slot variable.
 */
void *ti_GetVATPtr(const ti_var_t slot);

/**
 * Gets the variable name of an already opened slot.
 *
 * @param slot Slot variable to get name of.
 * @param name Buffer to store name in, allocate at least 10 bytes.
 */
void ti_GetName(char *name, const ti_var_t slot);

/**
 * Renames an AppVar.
 *
 * @param old_name Old name of AppVar.
 * @param new_name New name of AppVar.
 *
 * @returns 0 if success, 1 if AppVar already exists, 2 any other error occurs.
 * @warning It is potentially hazardous to rename an open AppVar. Close the AppVar before renaming.
 */
uint8_t ti_Rename(const char *old_name, const char *new_name);

/**
 * Renames a variable.
 *
 * @param old_name Old name of variable.
 * @param new_name New name of variable.
 * @param type Type of variable.
 *
 * @returns 0 if success, 1 if variable already exists, 2 any other error occurs.
 * @warning It is potentially hazardous to rename an open variable. Close the variable before renaming.
 */
uint8_t ti_RenameVar(const char *old_name, const char *new_name, const uint8_t type);

/**
 * Stores data or values to an OS variable.
 *
 * @param var_type Type of variable to set.
 * @param name Pointer to name of variable.
 * @param data Pointer to data to set.
 *
 * @returns 0 if success.
 */
uint8_t ti_SetVar(const ti_var_t var_type, const char *name, void *data);

/**
 * Stores an OS variable to another variable.
 *
 * @param var_type_to Type of variable to store to.
 * @param to Pointer to data to store to.
 * @param var_type_from Type of variable to get from.
 * @param from Pointer to data to get from.
 *
 * @returns 0 if success.
 */
uint8_t ti_StoVar(const ti_var_t var_type_to, void *to, const ti_var_t var_type_from, void *from);

/**
 * Recalls a variable.
 *
 * @param var_type Type of variable to recall.
 * @param var_name Pointer to name of variable to recall.
 * @param data_struct Address of pointer to variable structure.
 * @returns 0 if success.
 * @note data_struct is set to the variable's data.
 */
uint8_t ti_RclVar(const uint8_t var_type, const char *var_name, void **data_struct);


/**
 * Checks to see if there is room in the archive for storing \p num_bytes,
 * without needing to execute a Garbage Collect.
 *
 * @param num_bytes Number of bytes to be stored to the archive.
 * @returns true if the bytes can be stored to the archive without a Garbage Collect.
 */
bool ti_ArchiveHasRoom(uint24_t num_bytes);


/**
 * Set routines to run before and after a garbage collect would be triggered.
 *
 * @param before Routine to run before a garbage collect. NULL sets it to do nothing.
 * @param after Routine to run following a garbage collect. NULL sets it to do nothing.
 * @note If your program uses graphx, use gfx_End and gfx_Begin to reset graphics before, and setup graphics after the garbage collect.
 * */
void ti_SetGCBehavior(void (*before)(void), void (*after)(void));


/**
 * Allocates space for a real variable.
 * @returns Pointer to variable.
 */
#define ti_MallocReal() ((real_t*)malloc(sizeof(real_t)))

/**
 * Allocates space for a complex variable.
 * @returns Pointer to variable.
 */
#define ti_MallocCplx() ((cplx_t*)malloc(sizeof(cplx_t)))

/**
 * Allocates space for a string variable.
 * @param len Length of string.
 * @returns Pointer to variable.
 */
#define ti_MallocString(len) ti_AllocString((len), ((void*)malloc))

/**
 * Allocates space for a list variable.
 * @param dim Dimension of list.
 * @returns Pointer to variable.
 */
#define ti_MallocList(dim) ti_AllocList((dim), ((void*)malloc))

/**
 * Allocates space for a matrix variable.
 * @param rows Rows in matrix.
 * @param cols Columns in matrix.
 * @returns Pointer to variable.
 */
#define ti_MallocMatrix(rows, cols) ti_AllocMatrix((rows), (cols), ((void*)malloc))

/**
 * Allocates space for a complex list variable.
 * @param dim Dimension of complex list.
 * @returns Pointer to variable.
 */
#define ti_MallocCplxList(dim) ti_AllocCplxList((dim), ((void*)malloc))

/**
 * Allocates space for an equation variable.
 * @param len Length of equation variable.
 * @returns Pointer to variable.
 */
#define ti_MallocEqu(len) ti_AllocEqu((len), ((void*)malloc))

/* @cond */
string_t *ti_AllocString(unsigned len, void (*malloc_routine)(size_t));
list_t *ti_AllocList(unsigned dim, void (*malloc_routine)(size_t));
matrix_t *ti_AllocMatrix(uint8_t rows, uint8_t cols, void (*malloc_routine)(size_t));
cplx_list_t *ti_AllocCplxList(unsigned dim, void (*malloc_routine)(size_t));
equ_t *ti_AllocEqu(unsigned len, void (*malloc_routine)(size_t));
/* @endcond */

/* @cond */
/* Some more definitions using Ans */
#define TI_ANS_TYPE (0x00)
#define ti_Ans      ("\x72\0")

/* Some string definitions */
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

/* Compatibility defines */
#define ti_Program             _Pragma("GCC warning \"'ti_Program' is deprecated, use 'TI_PRGM_TYPE' instead\"") TI_PRGM_TYPE
#define ti_ProtectedProgram    _Pragma("GCC warning \"'ti_ProtectedProgram' is deprecated, use 'TI_PPRGM_TYPE' instead\"") TI_PPRGM_TYPE
#define ti_TempProgram         _Pragma("GCC warning \"'ti_TempProgram' is deprecated, use 'TI_TPRGM_TYPE' instead\"") TI_TPRGM_TYPE
#define ti_AppVar              _Pragma("GCC warning \"'ti_AppVar' is deprecated, use 'TI_APPVAR_TYPE' instead\"") TI_APPVAR_TYPE
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
