/**
 * FILEIOC CE C Library
 * @version 2.0
 *
 * @section LICENSE
 *
 * Copyright (c) 2016, Matthew Waltz
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 *
 * This library implements some variable opening and editing routines
 */

#ifndef H_FILEIOC
#define H_FILEIOC

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <tice.h>

/**
 * Varible and flag definitions
 */
#define TI_PRGM_TYPE            (0x05)
#define TI_PPRGM_TYPE           (0x06)
#define TI_TPRGM_TYPE           (0x16)
#define TI_APPVAR_TYPE          (0x15)
#define TI_REAL_TYPE            (0x00)
#define TI_CPLX_TYPE            (0x0C)
#define TI_MATRIX_TYPE          (0x02)
#define TI_STRING_TYPE          (0x04)
#define TI_EQU_TYPE             (0x03)
#define TI_REAL_LIST_TYPE       (0x01)
#define TI_CPLX_LIST_TYPE       (0x0D)

#ifndef EOF
#define EOF (-1)
#endif

/**
 * Some variable types
 */
typedef uint8_t ti_var_t;

/**
 * Closes all open slots
 * Call before you use any varaible functions
 */
void ti_CloseAll(void);

/**
 * Opens a varaible given then name and flags
 * ti_Open opens an AppVar as default file storage
 * ti_OpenVar opens a Program or Protected Program, depending on the type given
 * If there isn't enough memory to create the variable, or a slot isn't open, zero (0) is returned
 * Otherwise it returns the available slot number (1-5)
 * Available modes:
 * "r"  - Opens a file for reading. The file must exist. Keeps file in archive if in archive.                                   (Archive)
 * "w"  - Creates an empty file for writing. Overwrites file if already exists.                                                 (RAM)
 * "a"  - Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.  (RAM)
 * "r+" - Opens a file to update both reading and writing. The file must exist. Moves file from archive to RAM if in archive.   (RAM)
 * "w+" - Creates an empty file for both reading and writing. Overwrites file if already exists.                                (RAM)
 * "a+" - Opens a file for reading and appending. Moves file from archive to RAM if in archive. Created if it does not exist.   (RAM)
 * Unlike the standard implementation of fopen, the "b" (binary) mode is not available because characters are only 8 bits wide on this platform.
 * Type:
 *  Specifies the type of variable to open -- Only useable when it makes sense
 */
ti_var_t ti_Open(const char *varname, const char *mode);
ti_var_t ti_OpenVar(const char *varname, const char *mode, uint8_t type);

/**
 * Frees an open variable slot
 * Returns zero if closing failed
 */
int ti_Close(const ti_var_t slot);

/**
 * Returns the name of the file(s) that contains the string as the first part of the variable
 * This can then be used with ti_Open and other functions
 * seach_pos should be set to NULL to begin a search, and is then updated with each call
 *
 * For example:
 *  uint8_t *search_pos = NULL;
 *  char *var_name;
 *  while((var_name = ti_Detect( &search_pos, "my_data" )) != NULL) {
 *    ...do something with the name or search_pos...
 *  }
 * If the return value is NULL, either the variable wasn't found in the current search span, or there are no more variables to find
 * If detection_string is NULL, return is NULL as well
 */
char *ti_Detect(void **curr_search_posistion, const char *detection_string);
char *ti_DetectVar(void **curr_search_posistion, const char *detection_string, uint8_t var_type);

/**
 * Writes to the current variable pointer given:
 * data:
 *  pointer to data to write
 * size:
 *  size (in bytes) of the data we are writting
 * count:
 *  number of data chunks to write to the variable slot
 * slot:
 *  varaible slot to write the data to
 * Returns the number of chunks written (should be equal to count)
 */
size_t ti_Write(const void *data, size_t size, size_t count, const ti_var_t slot);

/**
 * Reads from the current variable pointer given:
 * data:
 *  pointer to data to read into
 * size:
 *  size (in bytes) of the data we are reading
 * count:
 *  number of data chunks to read from the variable slot
 * slot:
 *  varaible slot to read from
 * Returns the number of chunks read (should be equal to count)
 */
size_t ti_Read(const void *data, size_t size, size_t count, const ti_var_t slot);

/**
 * Puts a character directly into the slot data pointer, and increments the offset
 * Returns 'EOF' if current offset is larger than file size, or memory isn't large enough
 * c is internally converted to an unsigned char
 * c is returned if no error occurs
 * slot:
 *  varaible slot to put the character to
 */
int ti_PutC(const char c, const ti_var_t slot);

/**
 * Pulls a character directly from the slot data pointer, and increments the offset
 * Reads 'EOF' if current offset is larger than file size
 * slot:
 *  varaible slot to get the character from
 */
int ti_GetC(const ti_var_t slot);

/**
 * Seeks to an offset from the origin:
 * SEEK_SET (0) - Seek from beginning of file
 * SEEK_CUR (1) - Seek from current offset in file
 * SEEK_END (2) - Seek from end of file
 * slot:
 *  varaible slot seeking in
 */
int ti_Seek(int offset, unsigned int origin, const ti_var_t slot);

/**
 * Seeks to the start of the given variable
 * Basically an ti_Seek(0, SEEK_SET, slot);
 * slot:
 *  varaible slot seeking in
 */
int ti_Rewind(const ti_var_t slot);

/**
 * Returns the value of the current cursor offset
 */
uint16_t ti_Tell(const ti_var_t slot);

/**
 * Returns the size of the variable in the slot
 */
uint16_t ti_GetSize(const ti_var_t slot);

/**
 * Resizes the file slot
 * The file offset is set to the beginning of the file
 */
int ti_Resize(size_t new_size, const ti_var_t slot);

/**
 * Returns zero if the slot is not in the archive
 */
int ti_IsArchived(const ti_var_t slot);

/**
 * Sets the varaible into either the archive or RAM
 * Returns zero if the operation fails if not enough memory or some other error
 */
int ti_SetArchiveStatus(bool archived, const ti_var_t slot);

/**
 * ti_Delete    - Deletes an AppVar given the name
 * ti_DeleteVar - Deletes a varaible given the name and type
 */
int ti_Delete(const char *varname);
int ti_DeleteVar(const char *varname, uint8_t type);

/**
 * Gets the string used for displaying a TI token
 * read_pointer is updated to the next token, depending on if it is 1 or 2 bytes in length
 * length_of_token gets the length of the token, used for determining the next read location (Can be NULL if you don't care)
 * length_of_string returns the length of the returned string (Can be NULL if you don't care)
 */
char *ti_GetTokenString(void **read_pointer, uint8_t *length_of_token, unsigned *length_of_string);

/**
 * Gets a pointer to the data located at the current posistion in the slot
 * Good way for fast reading of data
 */
void *ti_GetDataPtr(const ti_var_t slot);

/**
 * Sets a varaible
 * Returns 0 if success
 */
uint8_t ti_SetVar(const ti_var_t var_type, const char *name, void *data);

/**
 * Stores a varaible to another variable
 * Returns 0 if success
 */
uint8_t ti_StoVar(const ti_var_t var_type_to, void *to, const ti_var_t var_type_from, void *from);

/**
 * Recalls a varaible
 * Returns 0 if success
 * data is set to the data being pointed to
 */
uint8_t ti_RclVar(const uint8_t var_type, const char *var_name, void **data_struct);

/**
 * Allocates space for a real variable
 */
#define ti_MallocReal() ((real_t*)malloc(sizeof(real_t)))

/**
 * Allocates space for a complex variable
 */
#define ti_MallocCplx() ((cplx_t*)malloc(sizeof(cplx_t)))

/**
 * Allocates space for a string variable
 */
string_t *ti_AllocString(unsigned len, void (*malloc_routine)(size_t));
#define ti_MallocString(len) ti_AllocString(len, (void*)malloc)

/**
 * Allocates space for a list variable
 */
list_t *ti_AllocList(unsigned dim, void (*malloc_routine)(size_t));
#define ti_MallocList(dim) ti_AllocList(dim, (void*)malloc)

/**
 * Allocates space for a matrix variable
 */
matrix_t *ti_AllocMatrix(uint8_t rows, uint8_t cols, void (*malloc_routine)(size_t));
#define ti_MallocMatrix(rows, cols) ti_AllocMatrix(rows, cols, (void*)malloc)

/**
 * Allocates space for a complex list variable
 */
cplx_list_t *ti_AllocCplxList(unsigned dim, void (*malloc_routine)(size_t));
#define ti_MallocCplxList(dim) ti_AllocCplxList(dim, (void*)malloc)

/**
 * Allocates space for an equation variable
 */
equ_t *ti_AllocEqu(unsigned len, void (*malloc_routine)(size_t));
#define ti_MallocEqu(len) ti_AllocEqu(len, (void*)malloc)

/**
 * Some more definitions using Ans
 */
#define TI_ANS_TYPE	0x00
#define ti_Ans		("\x72\0")

/**
 * Some string definitions
 */
#define ti_Str1     ("\xAA\x0\0")
#define ti_Str2     ("\xAA\x1\0")
#define ti_Str3     ("\xAA\x2\0")
#define ti_Str4     ("\xAA\x3\0")
#define ti_Str5     ("\xAA\x4\0")
#define ti_Str6     ("\xAA\x5\0")
#define ti_Str7     ("\xAA\x6\0")
#define ti_Str8     ("\xAA\x7\0")
#define ti_Str0     ("\xAA\x8\0")

/**
 * Some equation definitions
 */
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

/**
 * Some real and complex defines
 */
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

/**
 * Some matrix defines
 */
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

/**
 * Some list defines
 */
#define ti_L1        ("\x5D\x0\0")
#define ti_L2        ("\x5D\x1\0")
#define ti_L3        ("\x5D\x2\0")
#define ti_L4        ("\x5D\x3\0")
#define ti_L5        ("\x5D\x4\0")
#define ti_L6        ("\x5D\x5\0")

/**
 * For compatibility reasons
 */
#define ti_Program             TI_PRGM_TYPE
#define ti_ProtectedProgram    TI_PPRGM_TYPE
#define ti_TempProgram         TI_TPRGM_TYPE
#define ti_AppVar              TI_APPVAR_TYPE

#endif
