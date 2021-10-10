/**
 * @file
 * @brief FAT Filesystem Driver
 *
 * This library can be used to interface with a FAT32 block-based filesystem.
 *
 * Only FAT filesystems with a logical block size of 512 bytes are supported.
 * For best performance, the cluster allocation size should be set to the
 * maxium allowed.
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
 * A pointer to \c fat_callback_data_t is passed to the user-provided callback
 * functions.
 * The default is void *, but this can be changed by doing:
 * \code
 * #define fat_callback_data_t struct my_fat_callback_data
 * #include <fatdrvce.h>
 * \endcode
 */
#ifndef fat_callback_data_t
#define fat_callback_data_t void
#endif

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
    FAT_ERROR_INVALID_FILESYSTEM, /**< Attempted to initialize a non-FAT filesystem */
} fat_error_t;

typedef enum {
    FAT_LIST_FILEONLY, /**< For listing only files */
    FAT_LIST_DIRONLY, /**< For listing only directories */
    FAT_LIST_ALL /**< For listing files and directories */
} fat_list_option_t;

typedef struct {
    uint24_t (*read)(fat_callback_data_t *usr, uint32_t lba, uint24_t count, void *buffer);
    uint24_t (*write)(fat_callback_data_t *usr, uint32_t lba, uint24_t count, const void *buffer);
    fat_callback_data_t *usr;
    uint32_t first_lba;
    uint32_t last_lba;
    uint8_t priv[1024]; /**< Internal library use */
} fat_t;

typedef struct {
    uint8_t priv[64]; /**< Internal library use */
} fat_file_t;

typedef struct {
    char filename[13]; /**< Name of file in 8.3 format */
    uint8_t attrib; /**< File attributes */
    uint32_t size; /**< Size of file in bytes */
} fat_dir_entry_t;

#define FAT_FILE      (0 << 0)  /**< Entry has no attributes */
#define FAT_RDONLY    (1 << 0)  /**< Entry is read-only */
#define FAT_HIDDEN    (1 << 1)  /**< Entry is hidden */
#define FAT_SYSTEM    (1 << 2)  /**< Entry is a system file / directory */
#define FAT_VOLLABEL  (1 << 3)  /**< Entry is a volume label -- only for root directory */
#define FAT_DIR       (1 << 4)  /**< Entry is a directory (or subdirectory) */
#define FAT_ARCHIVE   (1 << 5)  /**< Entry is a directory (or subdirectory) */

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * This function will read and verify that a valid FAT filesystem is being
 * accessed.
 * @param fat FAT structure type.
 * Before calling this function, the following elements must be set:
 *     \p read: Callback for reading logical blocks.
 *     \p write: Callback for writing logical blocks.
 *     \p lba: First Logical Block Address (LBA) in the filesystem.
 *     \p count: Number of logical blocks in the filesystem.
 *     \p usr: Pointer to user-provided data structure that is passed to the
 *       relevant read/write callback functions. This can be used to store
 *       context information when working with different storage mechanisms.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Init(fat_t *fat);

/**
 * Deinitialize the FAT filesystem. This is not required to be called, however
 * it will clear the filesystem dirty bit so other OSes don't see the filesystem
 * with potential errors. You cannot use the FAT structure after this call,
 * and should call fat_Init if you need to modify the filesystem again.
 * @param fat Initialized FAT structure type.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Deinit(fat_t *fat);

/**
 * Parses a directory and returns a list of files and subdirectories in it.
 * @param fat Initialized FAT structure.
 * @param path Directory path to get list from.
 * @param option Listing option for files to find (e.g. FAT_LIST_FILEONLY)
 * @param entries Location to store found entries.
 * @param size Number of available entries to store to in the entries argument.
 *             Must be greater than or equal to 1.
 * @param skip If this function has previously been called, use this function to
 *        start parsing after this many entries.
 *
 * @code
 *  #define MAX_ENTRIES 10
 *
 *  fat_dir_entry_t entries[MAX_ENTRIES];
 *  int24_t count = fat_DirList("/DIR", FAT_LIST_ALL, entries, MAX_ENTRIES, 0);
 * @endcode
 *
 * @return Number of entries found, or -1 if an error occurred.
 */
int24_t fat_DirList(fat_t *fat, const char *path,
                    fat_list_option_t option, fat_dir_entry_t *entries,
                    uint24_t size, uint24_t skip);

/**
 * Returns the volume label of the drive if it exists.
 * @param fat Initialized FAT structure type.
 * @param label Storage for returning label, must be >= 13 bytes.
 * @returns FAT_SUCCESS on success, FAT_ERROR_NO_VOLUME_LABEL if no label,
 *          otherwise a different error.
 */
fat_error_t fat_GetVolumeLabel(fat_t *fat, char *label);

/**
 * Creates new files or directories in the filesystem.
 * @param fat Initialized FAT structure.
 * @param path Path in which to create. Does not create subdirectories.
 * @param name Name of new file or directory.
 * @param attrib New entry attributes, can be a mask of FAT_RDONLY,
                 FAT_HIDDEN, FAT_SYSTEM, and FAT_DIR.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Create(fat_t *fat, const char *path, const char *name, uint8_t attrib);

/**
 * Deletes a file or directory and deallocates the spaced used by it on disk.
 * @param fat Initialized FAT structure.
 * @param filepath Absolute path to file or directory to delete.
 * @return FAT_SUCCESS on success, otherwise error.
 * @note Directories must be empty in order to be deleted.
 * @warning Do not use this function on open files. The file must be closed
 *          before attempting to delete it.
 */
fat_error_t fat_Delete(fat_t *fat, const char *filepath);

/**
 * Sets the attributes (read only, hidden, etc) of the file.
 * @param fat Initialized FAT structure.
 * @param filepath Absolute file path.
 * @param attrib FAT attributes to set file to.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetAttrib(fat_t *fat, const char *filepath, uint8_t attrib);

/**
 * Gets the attributes (read only, hidden, etc) of the file.
 * @param fat Initialized FAT structure.
 * @param filepath Absolute file path.
 * @return File attributes, or 255 if an error.
 */
uint8_t fat_GetAttrib(fat_t *fat, const char *filepath);

/**
 * Sets the size of the file, allocating or deallocating space as needed.
 * This function should be called before attempting to write in a file that
 * does not have a large enough current file size, (i.e. a newly created file),
 * otherwise writes may always return FAT_ERROR_EOF.
 * @param file FAT file structure.
 * @param size New file size.
 * @return FAT_SUCCESS on success, otherwise error.
 * @note This function sets the file offset back to the first block, regardless
 *       of the change in size.
 */
fat_error_t fat_SetSize(fat_file_t *file, uint32_t size);

/**
 * Gets the size of a file.
 * @param fat Initialized FAT structure.
 * @param filepath Absolute file path.
 * @return File size in bytes.
 */
uint32_t fat_GetSize(fat_t *fat, const char *filepath);

/**
 * Opens a file for either reading or writing, or both.
 * @param file Uninitialized structure to store working file information.
 * @param fat Initialized FAT structure.
 * @param filepath Absolute file path.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Open(fat_file_t *file, fat_t *fat, const char *filepath);

/**
 * Sets the block offset position in the file.
 * @param file File handle returned from fat_Open.
 * @param block Block offset into file.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetPos(fat_file_t *file, uint24_t block);

/**
 * Synchronous read for multiple blocks. Advances file block offset position.
 * @param file File handle returned from fat_Open.
 * @param count Number of blocks to read.
 * @param buffer Data read from FAT file.
 * @return Returns number of blocks read, should equal \p count if success.
 */
fat_error_t fat_Read(fat_file_t *file, uint24_t count, void *buffer);

/**
 * Synchronous write for multiple blocks. Advances file block offset position.
 * @param file File handle returned from fat_Open.
 * @param count Number of blocks to write to file.
 * @param buffer Data to write to FAT file.
 * @return FAT_SUCCESS on success, otherwise error.
 * @return Returns number of blocks written, should equal \p count if success.
 */
fat_error_t fat_Write(fat_file_t *file, uint24_t count, const void *buffer);

/**
 * Closes an open file handle.
 * @param file File handle returned from fat_Open.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Close(fat_file_t *file);

#ifdef __cplusplus
}
#endif

#endif
