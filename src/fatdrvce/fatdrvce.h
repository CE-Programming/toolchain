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
 *     static uint8_t sector[512];
 *     static jmp_buf msdenv;
 *     msd_event_t evnt;
 *     uint8_t num;
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
 *     // Set the buffer used by the FAT library
 *     fat_SetBuffer(sector);
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
    uint8_t dummy;
} msd_t;

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

typedef enum msd_event {
    MSD_EVENT_NONE = 0,   /**< No event detected. */
    MSD_EVENT_DETACHED,   /**< The MSD device was unplugged. */
    MSD_EVENT_XFER_ERROR  /**< The MSD device encountered a transfer error. */
} msd_event_t;

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * Before calling this function, you must use \c fat_Find and \c fat_Select
 * in order to locate the correct FAT partition.
 * @warning When using the FAT library, calls to os_GetCSC() will cause USB not
 * to work. This will probably be fixed in later revisions, but just use the
 * \c keypadc library for now.
 * @return 0 on success.
 */
uint8_t fat_Init(void);

/**
 * Deinitializes the FAT filesystem and frees the handles to the device.
 * This function should be called with each corresponding \c fat_Init
 * function call. It should not be called in a device error handler,
 * only in the case of a graceful exit, otherwise an infinite loop may
 * occur.
 * @return None.
 */
void fat_Deinit(void);

/**
 * Locates any available FAT partitions detected on the mass storage device
 * (MSD), and returns setup pointers for use with \c fat_Select. You must
 * allocate space for \p result before calling this function. In addition, the
 * \c msd_Find and \c msd_Select functions must be called prior to using this
 * function in order to select any attached MSD.
 * @param result Array of FAT partitions available, returned from function.
 * @param max The maximum number of FAT partitions that can be found.
 * @return The number of found FAT partitions.
 */
uint8_t fat_Find(fat_partition_t *result, uint8_t max);

/**
 * Selects which FAT parition the library should use. You can only work with
 * one partition at a time, or use \c fat_Select to switch between available
 * partitions.
 * @param list Array of FAT partitions available, returned from
 * \c fat_Find.
 * @param index Which FAT partition to use, i.e. '0' would select the first
 * partition.
 * @return None.
 */
void fat_Select(fat_partition_t *list, uint8_t index);

/**
 * Opens a file on the device, given an absolute path. Names must use the 8.3
 * path format. No support for long file names is given. The file must exist,
 * or be created with \c fat_Create.
 * @param path Absolute 8.3 file path name.
 * @param flags \c FAT_O_WRONLY, \c FAT_O_RDONLY, \c FAT_O_RDWR for write only,
 * read only, and read/write respectively.
 * @return A FAT file descriptor, or a value less than 0 on error.
 */
int8_t fat_Open(const char *path, int flags);

/**
 * Closes and frees any open file descriptor.
 * @param fd File descriptor.
 * @return None.
 */
void fat_Close(int8_t fd);

/**
 * Gets the size of a file.
 * @param fd File descriptor.
 * @return File size in bytes.
 */
uint32_t fat_GetFileSize(int8_t fd);

/**
 * Sets the file size.
 * @param path Absolute 8.3 formatted file path.
 * @param size New file size.
 * @return None.
 */
void fat_SetFileSize(const char *path, uint32_t size);

/**
 * Gets the current offset in a file.
 * @param fd File descriptor.
 * @return File offset in bytes.
 */
uint32_t fat_Tell(int8_t fd);

/**
 * Sets up the buffer used for reading and writing sectors. This buffer must
 * be at least 512 bytes in size.
 * @param buffer Sets the buffer pointer address.
 * @return None.
 */
void fat_SetBuffer(void *buffer);

/**
 * Seeks to an arbitrary sector in the flash file. If the sector is beyond
 * the size of the file, the file allocation is extended. \p pos must be a
 * multiple of 512, or 0. Arbitrary seek positions are not supported.
 * @param fd File descriptor
 * @param pos 512 byte multiple offset in file descriptor.
 * @return false if an error occurs.
 */
bool fat_Seek(int8_t fd, uint32_t pos);

/**
 * Reads the contents of a 512 byte sector of a file into \c fat_SectorBuffer
 * If the current file position results in less than a full 512 byte sector
 * being available, garbage may be read into the excess buffer locations.
 * @param fd File descriptor
 * @return false if an error occurs.
 */
bool fat_ReadSector(int8_t fd);

/**
 * Writes the contents of the location pointed to by
 * \c fat_SectorBuffer into the current file position.
 * The file is extended as needed, however the metadata size of the file
 * needs to be updated using \c fat_SetFileSize.
 * @param fd File descriptor
 * @return false if an error occurs.
 */
bool fat_WriteSector(int8_t fd);

/**
 * Deletes a file given an absolute path.
 * @param path Absolute 8.3 file path name.
 * @return false if an error occurs.
 */
bool fat_Delete(const char *path);

/**
 * Creates a new file or directory on the device given an absolute path and name.
 * @param path Absolute 8.3 formatted directory path.
 * @param name 8.3 formatted file name.
 * @param attrib FAT style attributes. Can be an combination of \c FAT_RDONLY,
 * \c FAT_HIDDEN, \c FAT_SYSTEM, \c FAT_SUBDIR.
 * @return false if an error occurs.
 */
bool fat_Create(char *path, char *name, uint8_t attrib);

/**
 * Gets the attributes for a file on the device.
 * @return Returns 255 if no valid stats, otherwise a bitmask of valid FAT
 * attributes.
 */
uint8_t fat_GetAttrib(const char *path);

/**
 * Sets the attributes for a file on the device
 * @param path Absolute 8.3 formatted file path.
 * @param attrib FAT style attributes. Can be an combination of \c FAT_RDONLY,
 * \c FAT_HIDDEN, \c FAT_SYSTEM, \c FAT_SUBDIR.
 * @return None.
 */
void fat_SetAttrib(const char *path, uint8_t stat);

/**
 * Returns all FAT file / directory entires in a path.
 * @param path Absolute 8.3 formatted root path. Can be NULL for root directory.
 * @param list Storage location for directory entries. Must be pre-allocated.
 * @param directories Only return directories if not 0.
 * @param size Number of allocated \c fat_entry_t available.
 * @param skip Number of entries to skip adding to the list. Useful for memory
 * constraints.
 * @return Number of entries found.
 */
int fat_DirList(const char *path, fat_entry_t *list, uint8_t directories, int size, int skip);

/**
 * Selects the first found attached Mass Storage Device (MSD).
 * This is an alternative to using \c msd_Find and \c msd_Select.
 * Before calling this function, it is important to install an error
 * event handler using the \c msd_SetJmp function.
 * @param ticks Number of 32kHz ticks; timeout before erroring if no devices are detected. (5000 or higher is recommended).
 * @return 0 on success.
 */
uint8_t msd_Init(unsigned int ticks);

/**
 * Locates any attached Mass Storage Devices (MSD).
 * @param ms Number of 32kHz ticks; Timeout before erroring if no devices are found.
 * @param result Array of MSD's available, returned from function.
 * @param max The maximum number of MSD's that can be found.
 * @warning This function is currently unimplemented. Use \c msd_Init for now.
 * @return The number of attached MSD's.
 */
uint8_t msd_Find(unsigned int ticks, msd_t *result, uint8_t max);

/**
 * Select an attached Mass Storage Devices (MSD) for use.
 * @param list Array of MSD's available, returned from \c msd_Find.
 * @param index Which attached MSD to use, i.e. '0' would select the first
 * found Mass Storage Device.
 * @warning This function is currently unimplemented. Use \c msd_Init for now.
 * @return None.
 */
void msd_Select(msd_t *list, uint8_t index);

/**
 * Sends a SCSI "TEST_UNIT_READY" packet to ensure the device does not fall asleep.
 * This function should be called at least every 2 seconds if the device is idle.
 * @return None.
 */
void msd_KeepAlive(void);

/**
 * Directly reads a 512 byte sector from the Mass Storage Device
 * @param buffer Pointer to allocated 512 byte buffer to read into.
 * @param sector Logical Block Address (LBA) of sector to read.
 * @return None.
 */
void msd_ReadSector(uint8_t *buffer, uint32_t sector);

/**
 * Directly writes a 512 byte sector to the Mass Storage Device
 * @param buffer Pointer to allocated 512 byte buffer to write.
 * @param sector Logical Block Address (LBA) of sector to write.
 * @return None.
 */
void msd_WriteSector(uint8_t *buffer, uint32_t sector);

/**
 * Uses a buffer instantiated with \c setjmp as a handle
 * in the event of an error or a detachment of the usb device.
 * @param func Function pointer to call.
 * @return  0 if the first call, otherwise the \c msd_event_t event that
 * occured. You can also trigger this return manually using \c longjmp.
 */
int msd_SetJmpBuf(jmp_buf env);

/**
 * Cleans up and deinitializes the current USB device.
 * @return None.
 */
void msd_Deinit(void);

#ifdef __cplusplus
}
#endif

#endif
