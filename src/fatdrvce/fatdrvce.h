/**
 * @file
 * @brief USB FAT Filesystem Driver
 *
 * This library can be used to communicate with Mass Storage Devices (MSD) which
 * have partitions formated as FAT32. (FAT16 support is implemented yet untested).
 * It currently only supports drives that have a sector size of 512, which is pretty
 * much every flash drive on the market, except for huge ones.
 * The drive must use MBR partitioning, GUID is not supported yet.
 *
 * WARNING: Currently fatdrvce cannot operate in programs that use os_GetCSC().
 * Please use an alternative such as kb_Scan(), avaiable in the keypadc library.
 *
 * Example program showing initialization and teardown of FAT devices:
 * @code
 *
 * #define MAX_PARTITIONS 10
 *
 * void main(void) {
 *     static fat_partition_t fat_partitions[MAX_PARTITIONS];
 *     static uint8_t buffer[512];
 *     static uint8_t driver_buffer[512];
 *     static jmp_buf msdenv;
 *     usb_error_t evnt;
 *     uint8_t num;
 *
 *     // Set the buffers used by the FAT MSD library
 *     msd_SetDriverBuffer(driver_buffer);
 *     msd_SetDataBuffer(buffer);
 *
 *     // Configure USB error handling, e.g. removal before write is finished
 *     if ((evnt = setjmp(msdenv))) {
 *         // Tell the user there was an error with USB here
 *     }
 *     msd_SetJmpBuf(msdenv);
 *
 *     // Initialize the first attached MSD device
 *     if (msd_Init(10000) != 0) {
 *         // No MSD devices found
 *     }
 *
 *     // Locate available FAT partitions on the MSD device
 *     if ((num = fat_Find(fat_partitions, MAX_PARTITIONS) == 0) {
 *         // No FAT partitions found
 *     }
 *
 *     // Select the first (or other) FAT partition on the MSD
 *     fat_Select(fat_partitions, 0);
 *
 *     // Initialize the selected FAT partition
 *     if (fat_Init() != 0) {
 *         // Failed to initialize FAT partition
 *     }
 *
 *     // Here is where you can perform any other open/read/write operations
 *     // The 'buffer' variable can be used for both reading and writing
 *
 *     // Deinitialize FAT and MSD subsystems
 *     fat_Deinit();
 *     msd_Deinit();
 * }
 * @endcode
 *
 * @author Steven "s@rdw.se" Arnow
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 */

#ifndef H_FATDRVCE
#define H_FATDRVCE

#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t lba;       /**< Logical Block Address (LBA) of FAT partition */
    uint32_t size;      /**< Size of FAT partition */
} fat_partition_t;

typedef struct {
    char filename[13];  /**< Entry filename. */
    uint8_t attrib;     /**< Entry attributes. */
    uint8_t padding[2]; /**< Extra padding (reserved) */
} fat_entry_t;

#define	FAT_O_WRONLY      2               /**< Open Write only mode. */
#define	FAT_O_RDONLY      1               /**< Open Read only mode */
#define	FAT_O_RDWR (O_RDONLY | O_WRONLY)  /**< Open in Read and Write mode. */

#define FAT_RDONLY    (1 << 0)  /**< Entry is Read-Only. */
#define FAT_HIDDEN    (1 << 1)  /**< Entry is Hidden. */
#define FAT_SYSTEM    (1 << 2)  /**< Entry is a System file / directory. */
#define FAT_VOLLABEL  (1 << 3)  /**< Entry is a Volume Label. Only for root directory. */
#define FAT_SUBDIR    (1 << 4)  /**< Entry is a subdirectory (or directory). */
#define FAT_DIR       (1 << 4)  /**< Entry is a directory (or subdirectory). */
#define FAT_ALL       (FAT_DIR | FAT_VOLLABEL | FAT_SYSTEM | FAT_HIDDEN | FAT_RDONLY)

typedef enum msd_config {
    MSD_CONFIG_NONE = 0,              /**< No extra configuration parameters */
    MSD_CONFIG_AUTO_ADVANCE_DATA_BUFFER = 1, /**< Automatically advance data buffer pointer by 512 bytes on each read / write. */
} msd_config_t;

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * Before calling this function, you must use \c fat_Find and \c fat_Select
 * in order to locate the correct FAT partition.
 * @warning When using the FAT library, calls to os_GetCSC() will cause USB not
 * to work. This will probably be fixed in later revisions, but just use the
 * \c keypadc library for now.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Init(void);

/**
 * Deinitializes the FAT filesystem and frees the handles to the device.
 * This function should be called with each corresponding \c fat_Init
 * function call. It should not be called in a device error handler,
 * only in the case of a graceful exit, otherwise an infinite loop may
 * occur.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Deinit(void);

/**
 * Locates any available FAT partitions detected on the mass storage device
 * (MSD), and returns setup pointers for use with \c fat_Select. You must
 * allocate space for \p result before calling this function. In addition, the
 * \c msd_Find and \c msd_Select functions must be called prior to using this
 * function in order to select any attached MSD.
 * @param max The maximum number of FAT partitions that can be found.
 * @param partitions Array of FAT partitions available, returned from function.
 * @param num Array of FAT partitions available, returned from function.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Find(uint8_t max, fat_partition_t *partions, uint8_t *num);

/**
 * Selects which FAT parition the library should use. You can only work with
 * one partition at a time, or use \c fat_Select to switch between available
 * partitions.
 * @param list Array of FAT partitions available, returned from
 * \c fat_Find.
 * @param index Which FAT partition to use, i.e. '0' would select the first
 * partition.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Select(fat_partition_t *list, uint8_t index);

/**
 * Opens a file on the device, given an absolute path. Names must use the 8.3
 * path format. No support for long file names is given. The file must exist,
 * or be created with \c fat_Create.
 * @param path Absolute 8.3 file path name.
 * @param flags \c FAT_O_WRONLY, \c FAT_O_RDONLY, \c FAT_O_RDWR for write only,
 * read only, and read/write respectively.
 * @param fd Returned file descriptor variable.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Open(int8_t *fd, const char *path, int flags);

/**
 * Closes and frees any open file descriptor.
 * @param fd File descriptor.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Close(int8_t fd);

/**
 * Gets the size of a file.
 * @param fd File descriptor.
 * @param value Returned file size in bytes.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_GetFileSize(int8_t fd, uint32_t *value);

/**
 * Sets the file size.
 * @param path Absolute 8.3 formatted file path.
 * @param size New file size.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_SetFileSize(const char *path, uint32_t size);

/**
 * Gets the current offset in a file.
 * @param fd File descriptor.
 * @param offset Returned file offset in bytes.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Tell(int8_t fd, uint32_t *offset);

/**
 * Seeks to an arbitrary sector in the flash file. If the sector is beyond
 * the size of the file, the file allocation is extended. \p pos must be a
 * multiple of 512, or 0. Arbitrary seek positions are not supported.
 * @param fd File descriptor
 * @param pos 512 byte multiple offset in file descriptor.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Seek(int8_t fd, uint32_t pos);

/**
 * Reads the contents of a 512 byte sector of a file into \c fat_SectorBuffer
 * If the current file position results in less than a full 512 byte sector
 * being available, garbage may be read into the excess buffer locations.
 * @param fd File descriptor
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_ReadSector(int8_t fd);

/**
 * Writes the contents of the location pointed to by
 * \c fat_SectorBuffer into the current file position.
 * The file is extended as needed, however the metadata size of the file
 * needs to be updated using \c fat_SetFileSize.
 * @param fd File descriptor
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_WriteSector(int8_t fd);

/**
 * Deletes a file given an absolute path.
 * @param path Absolute 8.3 file path name.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Delete(const char *path);

/**
 * Creates a new file or directory on the device given an absolute path and name.
 * @param path Absolute 8.3 formatted directory path.
 * @param name 8.3 formatted file name.
 * @param attrib FAT style attributes. Can be an combination of \c FAT_RDONLY,
 * \c FAT_HIDDEN, \c FAT_SYSTEM, \c FAT_SUBDIR.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_Create(const char *path, const char *name, uint8_t attrib);

/**
 * Gets the attributes for a file on the device.
 * @param attrib Returned attribute value; 255 if no valid stats, otherwise a
 * bitmask of valid FAT attributes.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_GetAttrib(const char *path, uint8_t *attrib);

/**
 * Sets the attributes for a file on the device
 * @param path Absolute 8.3 formatted file path.
 * @param attrib FAT style attributes. Can be an combination of \c FAT_RDONLY,
 * \c FAT_HIDDEN, \c FAT_SYSTEM, \c FAT_SUBDIR.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_SetAttrib(const char *path, uint8_t attrib);

/**
 * Returns all FAT file / directory entires in a path.
 * @param path Absolute 8.3 formatted root path. Can be NULL for root directory.
 * @param list Storage location for directory entries. Must be pre-allocated.
 * @param directories Only return directories if not 0.
 * @param max Number of allocated \c fat_entry_t available.
 * @param skip Number of entries to skip adding to the list. Useful for memory
 * constraints.
 * @param num Returned number of entries found.
 * @return USB_SUCCESS on success.
 */
usb_error_t fat_DirList(const char *path, uint8_t directories, int skip, int max, fat_entry_t *list, int *num);

/**
 * Sets up the buffer used for FAT driver handling. This buffer must
 * be at least 512 bytes in size. It should not be the same buffer as set by
 * fat_SetDataBuffer(). Other library functions will only use the first 512
 * bytes of the supplied buffer.
 * @param buffer Sets the buffer pointer address.
 * @return None.
 */
void msd_SetDriverBuffer(void *buffer);

/**
 * Locates any attached Mass Storage Devices (MSD).
 * @param ms Number of 32kHz ticks; Timeout before erroring if no devices
 * are found. Recommended values are > 5000.
 * @param list Array of MSD's available, returned from function.
 * @param max The maximum number of MSD's that can be found.
 * @param num Returned number of attached MSD's.
 * @return USB_SUCCESS on success.
 */
usb_device_t msd_Find(usb_device_t prev, unsigned int ticks);

/**
 * Sends a SCSI "TEST_UNIT_READY" packet. This may be needed to periodically
 * ensure that the device is still alive.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_TestUnitReady(void);

/**
 * Directly reads a 512 byte sector from the Mass Storage Device into the
 * buffer specified by msd_SetDataBuffer(). If the option
 * MSD_CONFIG_AUTO_ADVANCE_DATA_BUFFER is set, the buffer address is advanced by
 * 512 bytes.
 * @param sector Logical Block Address (LBA) of sector to read.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_ReadSector(uint32_t sector, void *buffer);

/**
* Directly writes a 512 byte sector to the Mass Storage Device from the
* buffer specified by msd_SetDataBuffer(). If the option
* MSD_CONFIG_AUTO_ADVANCE_DATA_BUFFER is set, the buffer address is advanced by
* 512 bytes.
 * @param sector Logical Block Address (LBA) of sector to write.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_WriteSector(uint32_t sector, void *buffer);

/**
 * Cleans up and deinitializes the current USB device.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_Deinit(usb_device_t dev);

#ifdef __cplusplus
}
#endif

#endif
