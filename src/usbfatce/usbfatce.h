/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 * @brief USB FAT driver
 */

#ifndef H_USBFATCE
#define H_USBFATCE

#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int idx;
} msd_t;

typedef struct {
    uint32_t lba;
    uint32_t size;
} fat_partition_t;

typedef struct {
    char filename[13];
    uint8_t attrib;
    uint8_t padding[2];
} fat_entry_t;

#define	O_WRONLY      2
#define	O_RDONLY      1
#define	O_RDWR        (O_RDONLY | O_WRONLY)

#define FAT_RDONLY    (1 << 0)
#define FAT_HIDDEN    (1 << 1)
#define FAT_SYSTEM    (1 << 2)
#define FAT_VOLLABEL  (1 << 3)
#define FAT_SUBDIR    (1 << 4)

extern uint8_t *fat_SectorBuffer;

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * Before calling this function, you must use \c fat_Find and \c fat_Select
 * in order to locate the correct FAT partition.
 * @return true if the FAT filesystem was initialized properly, false upon error.
 */
bool fat_Init(void);

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
 * @param flags O_WRONLY, O_RDONLY, O_RDWR for write only, read only, and
 * read/write respectively.
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
 * @param path Absolute 8.3 formatted root path.
 * @param list Storage location for directory entries. Must be pre-allocated.
 * @param size Number of allocated \c fat_entry_t available.
 * @param skip Number of entries to skip adding to the list. Useful for memory
 * constraints.
 * @return An error returned by a callback or USB_SUCCESS.
 */
int fat_DirList(const char *path, fat_entry_t *list, int size, int skip);

/**
 * Selects the first found attached Mass Storage Device (MSD).
 * This is an alternative to using \c msd_Find and \c msd_Select.
 * @param ms Timeout before erroring if no devices are detected.
 * @return 0 if initialization fails.
 */
uint8_t msd_Init(unsigned int ms);

/**
 * Locates any attached Mass Storage Devices (MSD).
 * @param ms Timeout before erroring if no devices are found.
 * @param result Array of MSD's available, returned from function.
 * @param max The maximum number of MSD's that can be found.
 * @return The number of attached MSD's.
 */
uint8_t msd_Find(unsigned int ms, msd_t *result, uint8_t max);

/**
 * Select an attached Mass Storage Devices (MSD) for use.
 * @param list Array of MSD's available, returned from \c msd_Find.
 * @param index Which attached MSD to use, i.e. '0' would select the first
 * found Mass Storage Device.
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
 * Implements 'setjmp' functionality to return to in the event of an
 * error or a detachment of the usb device.
 * @param func Function pointer to call.
 * @return None.
 */
int msd_SetJmp(jmp_buf env);

/**
 * Cleans up the current USB state.
 * @return None.
 */
void msd_Cleanup(void);

#ifdef __cplusplus
}
#endif

#endif
