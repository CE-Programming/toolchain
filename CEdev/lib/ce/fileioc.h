/**
 * @file    FILEIOC CE C Library
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

/**
 * Varible and flag definitions
 */
#define ti_Program             (5)
#define ti_ProtectedProgram    (6)
#define ti_AppVar              (21)
#define ti_TempProgram         (22)

#ifndef EOF
#define EOF (-1)
#endif

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
 *  Specifies the type of variable to open
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
 * Returns the number of chuncks read (should be equal to count)
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
 * Resizes the slot to the new size; note that the current file
 * offset is set to the beginning of the file
 */
int ti_Resize(size_t new_size, const ti_var_t slot);

/**
 * Returns zero if the slot is not in the archive
 */
int ti_IsArchived(const ti_var_t slot);

/**
 * Sets the varaible into either the archive or RAM
 * Returns zero if the operation fails if not enough memory or some other error
 * NOTE: This routine also closes the file handle. You must reopen the file afterwords.
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

#endif
