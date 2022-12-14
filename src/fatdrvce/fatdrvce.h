/**
 * @file
 * @brief FAT Filesystem Driver
 *
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 */

#ifndef FATDRVCE_H
#define FATDRVCE_H

#include <stdint.h>
#include <stdbool.h>
#include <usbdrvce.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FAT_BLOCK_SIZE 512 /**< Block size in bytes */

/**
 * A pointer to \c fat_callback_usr_t is passed to the user provided callback
 * functions for reading and writing.
 * The default is void *, but this can be changed by doing:
 * \code
 * #define fat_callback_usr_t struct my_fat_callback_data
 * #include <fatdrvce.h>
 * \endcode
 */
#ifndef fat_callback_usr_t
#define fat_callback_usr_t void
#endif

/** FAT Driver return codes */
typedef enum {
    FAT_SUCCESS = 0, /**< Operation was successful */
    FAT_ERROR_INVALID_PARAM, /**< An invalid argument was provided */
    FAT_ERROR_NOT_SUPPORTED, /**< The operation is not supported */
    FAT_ERROR_INVALID_CLUSTER, /**< An invalid FAT cluster was accessed */
    FAT_ERROR_INVALID_POSITION, /**< An invalid position in the file */
    FAT_ERROR_NOT_FOUND, /**< The partition, file, or entry does not exist */
    FAT_ERROR_EXISTS, /**< The file or entry already exists */
    FAT_ERROR_INVALID_PATH, /**< An invalid path was provided */
    FAT_ERROR_FAILED_ALLOC, /**< Allocation of a cluster or file failed */
    FAT_ERROR_CLUSTER_CHAIN, /**< The cluster chain was corrupted */
    FAT_ERROR_DIRECTORY_NOT_EMPTY, /**< The directory is not empty */
    FAT_ERROR_NO_VOLUME_LABEL, /**< No volume label found for partition */
    FAT_ERROR_RDONLY, /**< The file or entry is read-only */
    FAT_ERROR_RW_FAILED, /**< The callback read failed to read/write */
    FAT_ERROR_INVALID_FILESYSTEM, /**< A non-FAT filesystem detected */
    FAT_ERROR_NO_MORE_ENTRIES, /**< No more entries in the directory */
} fat_error_t;

/**
 * Callback for reading logical blocks
 * @param usr[in] User defined data pointer.
 * @param lba[in] Local block address (LBA) to read.
 * @param count[in] Number of logical blocks to read.
 * @param buffer[in] Buffer to store read data into.
 * @returns Number of logical blocks read.
 */
typedef uint24_t (*fat_read_callback_t)(fat_callback_usr_t *usr,
                                        uint32_t lba,
                                        uint24_t count,
                                        void *buffer);

/**
 * Callback for writing logical blocks
 * @param usr[in] User defined data pointer.
 * @param lba[in] Local block address (LBA) to write.
 * @param count[in] Number of logical blocks to write.
 * @param buffer[in] Buffer to fetch write data from.
 * @returns Number of logical blocks writen.
 */
typedef uint24_t (*fat_write_callback_t)(fat_callback_usr_t *usr,
                                         uint32_t lba,
                                         uint24_t count,
                                         const void *buffer);

/** FAT structure */
typedef struct {
/* @cond */
    uint8_t priv[768];
/* @endcond */
} fat_t;

/** FAT file structure */
typedef struct {
/* @cond */
    uint8_t priv[64];
/* @endcond */
} fat_file_t;

/** FAT directory structure */
typedef struct {
/* @cond */
    uint8_t priv[32];
/* @endcond */
} fat_dir_t;

/** FAT directory entry structure */
typedef struct {
    char name[13]; /**< Name in 8.3 format */
    uint8_t attrib; /**< File attributes @see fat_file_attrib */
    uint32_t size; /**< Size of file in bytes */
} fat_dir_entry_t;

enum fat_file_attrib
{
    FAT_FILE      = (0 << 0),  /**< Entry has no attributes */
    FAT_RDONLY    = (1 << 0),  /**< Entry is read-only */
    FAT_HIDDEN    = (1 << 1),  /**< Entry is hidden */
    FAT_SYSTEM    = (1 << 2),  /**< Entry is a system file / directory */
    FAT_VOLLABEL  = (1 << 3),  /**< Entry is a volume label */
    FAT_DIR       = (1 << 4),  /**< Entry is a directory (or subdirectory) */
    FAT_ARCHIVE   = (1 << 5),  /**< Entry is a directory (or subdirectory) */
};

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * This function will attempt to read and verify that a valid FAT filesystem is
 * being accessed.
 * @param fat[out] Uninitialized FAT structure type.
 * @param read[in] Callback for reading logical blocks.
 * @param write[in] Callback for writing logical blocks.
 * @param usr[in] Pointer to user-provided data structure that is passed to the
 *                relevant read/write callback functions. This can be used to
 *                store context information with different storage mechanisms.
 * @param base_lba[in] LBA added to every FAT access for ease of use.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Open(fat_t *fat,
                     fat_read_callback_t read,
                     fat_write_callback_t write,
                     fat_callback_usr_t *usr,
                     const uint32_t base_lba);

/**
 * Closes the FAT filesystem. This is not required to be called, however
 * it will clear the filesystem dirty bit so other OSes don't see the filesystem
 * with potential errors. You cannot use the FAT structure after this call,
 * and should call fat_Open() if you need to modify the filesystem again.
 * @param fat[in] Initialized FAT structure type.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Close(fat_t *fat);

/**
 * Opens a directory for reading contents.
 * @param fat[in] Initialized FAT structure.
 * @param path[in] Directory path to get list from.
 * @param dir[out] Pointer to store opaque directory handle.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_OpenDir(fat_t *fat, const char *path, fat_dir_t *dir);

/**
 * Gets the next directory entry.
 * @param dir[in] Initialized directory handle from fat_OpenDir().
 * @param entry[out] Pointer to store entry information.
 * @return Number of entries found.
 */
fat_error_t fat_ReadDir(fat_dir_t *dir, fat_dir_entry_t *entry);

/**
 * Closes an open directory handle.
 * @param dir[in] Directory handle.
 * @return Number of entries found.
 */
fat_error_t fat_CloseDir(fat_dir_t *dir);

/**
 * Returns the volume label of the drive if it exists.
 * @param fat[in] Initialized FAT structure type.
 * @param label[out] Storage for returning label, must be >= 13 bytes.
 * @returns FAT_SUCCESS on success, FAT_ERROR_NO_VOLUME_LABEL if no label,
 *          otherwise a different error.
 */
fat_error_t fat_GetVolumeLabel(fat_t *fat, char *label);

/**
 * Creates new files or directories in the filesystem.
 * @param fat[in] Initialized FAT structure.
 * @param path[in] Path in which to create. Does not create subdirectories.
 * @param name[in] Name of new file or directory.
 * @param attrib[in] New entry attributes, can be a mask of FAT_RDONLY,
                     FAT_HIDDEN, FAT_SYSTEM, and FAT_DIR.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Create(fat_t *fat, const char *path, const char *name, uint8_t attrib);

/**
 * Deletes a file or directory and deallocates the spaced used by it on disk.
 * @param fat[in] Initialized FAT structure.
 * @param filepath[in] Absolute path to file or directory to delete.
 * @return FAT_SUCCESS on success, otherwise error.
 * @note Directories must be empty in order to be deleted.
 * @warning Do not use this function on open files. The file must be closed
 *          before attempting to delete it.
 */
fat_error_t fat_Delete(fat_t *fat, const char *filepath);

/**
 * Sets the attributes (read only, hidden, etc) of the file.
 * @param fat[in] Initialized FAT structure.
 * @param filepath[in] Absolute file path.
 * @param attrib[in] FAT attributes to set file to. @see fat_file_attrib
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetAttrib(fat_t *fat, const char *filepath, uint8_t attrib);

/**
 * Gets the attributes (read only, hidden, etc) of the file.
 * @param fat[in] Initialized FAT structure.
 * @param filepath[in] Absolute file path.
 * @return File attributes, or 255 if an error.
 */
uint8_t fat_GetAttrib(fat_t *fat, const char *filepath);

/**
 * Opens a file for either reading or writing, or both.
 * @param fat[in] Initialized FAT structure.
 * @param filepath[in] Absolute file path.
 * @param file[out] Uninitialized structure to store working file information.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_OpenFile(fat_t *fat, const char *filepath, fat_file_t *file);

/**
 * Sets the size of the file, allocating or deallocating space as needed.
 * This function should be called before attempting to read/write in a file that
 * does not have a large enough current file size, (i.e. a newly created file).
 * @param file[in] FAT file structure.
 * @param size[in] New file size.
 * @return FAT_SUCCESS on success, otherwise error.
 * @note This function resets the block position to 0, regardless size change.
 */
fat_error_t fat_SetFileSize(fat_file_t *file, uint32_t size);

/**
 * Gets the size of a file.
 * @param file[in] FAT file structure.
 * @return File size in bytes.
 */
uint32_t fat_GetFileSize(fat_file_t *file);

/**
 * Sets the block offset position in the file.
 * @param file[in] File handle returned from fat_OpenFile().
 * @param block[in] Block offset into file.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetFileBlockOffset(fat_file_t *file, uint24_t block);

/**
 * Gets the sector offset position in the file.
 * @param file[in] File handle returned from fat_OpenFile().
 * @return File block offset.
 */
uint24_t fat_GetFileBlockOffset(fat_file_t *file);

/**
 * Read from a file. Advances file block offset position.
 * @param file[in] File handle returned from fat_OpenFile().
 * @param count[in] Number of blocks to read.
 * @param buffer[out] Data read from FAT file.
 * @return Returns number of blocks read, should equal \p count if success.
 */
uint24_t fat_ReadFile(fat_file_t *file, uint24_t count, void *buffer);

/**
 * Write to a file. Advances file block offset position. Does not extend file
 * size if at last block in file, fat_SetFileSize() must be used instead.
 * @param file[in] File handle returned from fat_OpenFile().
 * @param count[in] Number of blocks to write to file.
 * @param buffer[in] Data to write to FAT file.
 * @return Returns number of blocks written, should equal \p count if success.
 */
uint24_t fat_WriteFile(fat_file_t *file, uint24_t count, const void *buffer);

/**
 * Closes an open file handle.
 * @param file[in] File handle returned from fat_OpenFile().
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_CloseFile(fat_file_t *file);

#ifdef __cplusplus
}
#endif

#endif
