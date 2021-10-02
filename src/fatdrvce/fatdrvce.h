/**
 * @file
 * @brief MSD FAT Filesystem Driver
 *
 * This library can be used to communicate with Mass Storage Devices (MSD) which
 * have partitions formated as FAT32. It is recommended to make the cluster
 * allocation size at least 4KiB, however 64KiB will provide the best
 * performance.
 *
 * Currently only drives with a logical block size of 512 bytes are supported,
 * which is the most common block size available. Larger drives and SSDs may
 * not work.
 *
 * The drive must use MBR partitioning, GPT and others are not yet supported.
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

/* MSD structures */

#define MSD_BLOCK_SIZE 512 /**< Block size in bytes */

typedef enum {
    MSD_SUCCESS = 0, /**< Operation was successful */
    MSD_ERROR_INVALID_PARAM, /**< An invalid argument was provided */
    MSD_ERROR_USB_FAILED, /**< An error occurred in usbdrvce */
    MSD_ERROR_SCSI_FAILED, /**< An error occurred in scsi transfer */
    MSD_ERROR_SCSI_CHECK_CONDITION, /**< SCSI command failed */
    MSD_ERROR_NOT_SUPPORTED, /**< The operation is not supported */
    MSD_ERROR_INVALID_DEVICE, /**< An invalid usb device was specified */
    MSD_ERROR_TIMEOUT, /**< The transfer timed out */
} msd_error_t;

typedef struct {
    uint8_t private[1024]; /**< Internal library use */
} msd_t;

typedef struct {
    uint32_t bsize; /**< Size of each block in bytes */
    uint32_t bnum; /**< Number of blocks on MSD */
} msd_info_t;

typedef struct msd_transfer_t {
    msd_t *msd; /**< Initialized MSD device */
    uint32_t lba; /**< Logical block address */
    void *buffer; /**< Pointer to data location to read/write */
    uint24_t count; /**< Number of blocks to transfer */
    void (*callback)(msd_error_t error, struct msd_transfer_t *xfer); /**< Called when transfer completes */
    void *userptr; /**< Custom user data for callback (optional) */
    void *next; /**< Internal library use */
    uint8_t stall; /**< Internal library use */
    uint8_t cbw[31+1]; /**< Internal library use */
    uint8_t csw[13+19]; /**< Internal library use */
} msd_transfer_t;

/* FAT structures */

typedef enum {
    FAT_SUCCESS = 0, /**< Operation was successful */
    FAT_ERROR_INVALID_PARAM, /**< An invalid argument was provided */
    FAT_ERROR_MSD_FAILED, /**< An error occurred in a MSD request */
    FAT_ERROR_NOT_SUPPORTED, /**< The operation is not supported */
    FAT_ERROR_INVALID_CLUSTER, /**< An invalid FAT cluster was accessed */
    FAT_ERROR_EOF, /**< End-of-file was encountered */
    FAT_ERROR_NOT_FOUND, /**< The partition, file, or entry does not exist */
    FAT_ERROR_EXISTS, /**< The file or entry already exists */
    FAT_ERROR_INVALID_PATH, /**< An invalid path was provided */
    FAT_ERROR_FAILED_ALLOC, /**< Allocation of a cluster or file failed */
    FAT_ERROR_CLUSTER_CHAIN, /**< The cluster chain was corrupted */
    FAT_ERROR_DIRECTORY_NOT_EMPTY, /**< The directory is not empty */
    FAT_ERROR_NO_VOLUME_LABEL, /**< No volume label found for partition */
    FAT_ERROR_RDONLY, /**< The file or entry is read-only */
    FAT_ERROR_WRONLY /**< The file or entry is write-only */
} fat_error_t;

typedef enum {
    FAT_LIST_FILEONLY, /**< For listing only files. */
    FAT_LIST_DIRONLY, /**< For listing only directories. */
    FAT_LIST_ALL /**< For listing files and directories. */
} fat_list_option_t;

typedef struct {
    uint8_t private[1024]; /**< Internal library use */
} fat_t;

typedef struct {
    uint8_t private[64]; /**< Internal library use */
} fat_file_t;

typedef struct {
    uint32_t lba; /**< Logical Block Address (LBA) of FAT partition */
    msd_t *msd; /**< MSD containing FAT filesystem */
} fat_partition_t;

typedef struct {
    char filename[13]; /**< Name of file in 8.3 format. */
    uint8_t attrib; /**< File attributes */
    uint32_t size; /**< Size of file in bytes */
} fat_dir_entry_t;

typedef struct fat_transfer_t {
    fat_file_t *file; /**< Pointer to open file */
    uint24_t count; /**< Number of blocks to transfer */
    void *buffer; /**< Pointer to data location to read/write */
    void (*callback)(fat_error_t error, struct fat_transfer_t *xfer); /**< Called when transfer completes */
    void *userptr; /**< Custom user data for callback (optional) */
    void *next; /**< Internal library use */
    msd_transfer_t xfer; /**< Internal library use */
} fat_transfer_t;

#define FAT_FILE      (0 << 0)  /**< Entry has no attributes. */
#define FAT_RDONLY    (1 << 0)  /**< Entry is read-only. */
#define FAT_HIDDEN    (1 << 1)  /**< Entry is hidden. */
#define FAT_SYSTEM    (1 << 2)  /**< Entry is a system file / directory. */
#define FAT_VOLLABEL  (1 << 3)  /**< Entry is a volume label -- only for root directory. */
#define FAT_DIR       (1 << 4)  /**< Entry is a directory (or subdirectory). */
#define FAT_ARCHIVE   (1 << 5)  /**< Entry is a directory (or subdirectory). */

/**
 * Locates any available FAT partitions detected on the mass storage device
 * (MSD). You must allocate space for \p partitions before calling this
 * function, as well as passing a valid msd_t returned from msd_Open.
 * @param msd Initialized MSD structure returned from msd_Open.
 * @param partitions Returned array of FAT partitions available.
 * @param number Returned number of FAT partitions found.
 * @param max The maximum number of FAT partitions that can be found.
 * @return USB_SUCCESS on success, otherwise error.
 */
fat_error_t fat_FindPartitions(msd_t *msd, fat_partition_t *partitions,
                               uint8_t *number, uint8_t max);

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * Before calling this function, you must use fat_Find in order to
 * locate a valid FAT partition.
 * @param fat Uninitialized FAT structure type.
 * @param partition Available FAT partition returned from fat_Find.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_OpenPartition(fat_t *fat, fat_partition_t *partition);

/**
 * Deinitialize the FAT filesystem. This is not required to be called, however
 * it will clear the filesystem dirty bit so other OSes don't see the drive as
 * having potential errors. You cannot use the FAT structure after this call,
 * and should call fat_OpenPartition if you need to modify the filesystem again.
 * @param fat Initialized FAT structure type.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_ClosePartition(fat_t *fat);

/**
 * Parses a directory and returns a list of files and subdirectories in it.
 * @param fat Initialized FAT structure.
 * @param path Directory path to get list from.
 * @param option Listing option for files to find (e.g. FAT_LIST_FILEONLY)
 * @param entries Location to store found entries.
 * @param size Number of avaiable entries to store to in the entries argument.
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
fat_error_t fat_Create(fat_t *fat, const char *path,
                       const char *name, uint8_t attrib);

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
 * Synchronous read for multiple blocks. Advances file block offset position.
 * @param file File handle returned from fat_Open.
 * @param count Number of blocks to read.
 * @param buffer Data read from FAT file.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Read(fat_file_t *file, uint24_t count, void *buffer);

/**
 * Synchronous write for multiple blocks. Advances file block offset position.
 * @param file File handle returned from fat_Open.
 * @param count Number of blocks to write to file.
 * @param buffer Data to write to FAT file.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Write(fat_file_t *file, uint24_t count, const void *buffer);

/**
 * Asynchronous read for multiple blocks. Advances file block offset position.
 * You must set the following \p xfer elements:
 * \p file, \p count, \p buffer, and \p callback. The optional element
 * \p userptr  can be used to store user-defined data for access in the
 * callback. The \p xfer argument must remain valid (cannot be free'd or
 * lose scope) until the callback is issued. You can free \xfer inside the
 * callback as needed.
 * @param xfer Initialized FAT file transfer.
 * @return FAT_SUCCESS if the transfer was queued, otherwise error.
 */
fat_error_t fat_ReadAsync(fat_transfer_t *xfer);

/**
 * Asynchronous write for multiple blocks. Advances file block offset position.
 * You must set the following \p xfer elements:
 * \p file, \p count, \p buffer, and \p callback. The optional element
 * \p userptr  can be used to store user-defined data for access in the
 * callback. The \p xfer argument must remain valid (cannot be free'd or
 * lose scope) until the callback is issued. You can free \xfer inside the
 * callback as needed.
 * @param xfer Initialized FAT file transfer.
 * @return FAT_SUCCESS if the transfer was queued, otherwise error.
 */
fat_error_t fat_WriteAsync(fat_transfer_t *xfer);

/**
 * Closes an open file handle.
 * @param file File handle returned from fat_Open.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Close(fat_file_t *file);

/**
 * Initialize a Mass Storage Device.
 * @param msd Uninitilaized MSD device structure.
 * @param usb Initialized USB device structure.
 * @return MSD_SUCCESS on success, otherwise error.
 */
msd_error_t msd_Open(msd_t *msd, usb_device_t usb);

/**
 * Closes and deinitializes a Mass Storage Device. This function should be
 * called in the \c USB_DEVICE_DISCONNECTED_EVENT in the USB handler callback.
 * @param msd Initialized MSD device structure.
 */
void msd_Close(msd_t *msd);

/**
 * Attempts to reset and restore normal working order of the device.
 * @param msd Initialized MSD device structure.
 * @return MSD_SUCCESS on success, otherwise error.
 */
msd_error_t msd_Reset(msd_t *msd);

/**
 * Gets the number of and size of each logical block on the device.
 * @param msd Initialized MSD device structure.
 * @param info Pointer to store MSD information to.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_Info(msd_t *msd, msd_info_t *info);

/**
 * Synchronous block read.
 * @param msd Iniailized MSD structure.
 * @param lba Logical Block Address (LBA) of starting block to read.
 * @param num Number of blocks to read.
 * @param data Buffer to read into. Must be at least block size * count bytes.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_Read(msd_t *msd, uint32_t lba,
                     uint24_t count, void *buffer);

/**
 * Synchronous block write.
 * @param msd Iniailized MSD structure.
 * @param lba Logical Block Address (LBA) of starting block to read.
 * @param num Number of blocks to read.
 * @param data Buffer to read into. Must be at least block size * count bytes.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_Write(msd_t *msd, uint32_t lba,
                      uint24_t count, const void *buffer);

/**
 * Asynchronous block read. You must set the following \p xfer elements:
 * \p msd, \p lba, \p buffer, \p count, \p callback. The optional element
 * \p userptr can be used to store user-defined data for access in the callback.
 * The \p xfer argument must remain valid (cannot be free'd or lose scope)
 * until the callback is issued. You can free \xfer inside the callback as
 * needed.
 * @param xfer Initialized transaction structure.
 * @return MSD_SUCCESS if the transfer has been added to the queue.
 */
msd_error_t msd_ReadAsync(msd_transfer_t *xfer);

/**
 * Asynchronous block write. You must set the following \p xfer elements:
 * \p msd, \p lba, \p buffer, \p count, \p callback. The optional element
 * \p userptr can be used to store user-defined data for access in the callback.
 * The \p xfer argument must remain valid (cannot be free'd or lose scope)
 * until the callback is issued. You can free \xfer inside the callback as
 * needed.
 * @param xfer Initialized transaction structure.
 * @return MSD_SUCCESS if the transfer has been added to the queue.
 */
msd_error_t msd_WriteAsync(msd_transfer_t *xfer);

#ifdef __cplusplus
}
#endif

#endif
