/**
 * @file
 * @brief USB FAT Filesystem Driver
 *
 * This library can be used to communicate with Mass Storage Devices (MSD) which
 * have partitions formated as FAT32. It is recommended to make the cluster
 * allocation size at least 4KiB, however 64KiB will provide the best
 * performance.
 *
 * Currently only drives with a logical sector size of 512 bytes are supported,
 * which is the most common sector size available. Larger drives and SSDs may
 * not work.
 *
 * The drive must use MBR partitioning, GUID and others are not supported.
 *
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 */

#ifndef H_FATDRVCE
#define H_FATDRVCE

#include <stdint.h>
#include <stdbool.h>
#include <usbdrvce.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t signature;
    uint32_t tag;
    uint32_t length;
    uint8_t status;
} msd_csw_t;

typedef struct {
    uint8_t length;
    uint8_t opcode;
    uint8_t data[15];
} msd_cbd_t;

typedef struct {
    uint32_t signature;
    uint32_t tag;
    uint32_t length;
    uint8_t dir;
    uint8_t lun;
    msd_cbd_t cbd;
} msd_cbw_t;

typedef struct {
    usb_device_t dev; /**< USB device */
    usb_endpoint_t in; /**< USB bulk in endpoint */
    usb_endpoint_t out; /**< USB bulk out endpoint */
    usb_endpoint_t ctrl; /**< USB Control endpoint */
    uint24_t tag; /**< MSD Command Block Wrapper incrementing tag */
    uint32_t lba; /**< Logical Block Address of LUN */
    uint32_t blocksize; /**< Block size (usually 512) */
    uint8_t interface; /**< USB Interface index */
    uint8_t maxlun; /**< Maximum LUNs for MSD */
    void *buffer; /**< User supplied buffer address */
} msd_device_t;

typedef struct {
    uint32_t lba;       /**< Logical Block Address (LBA) of FAT partition */
    msd_device_t *msd;  /**< MSD containing FAT filesystem */
} fat_partition_t;

typedef struct {
    fat_partition_t *partition; /**< Disk partition used by FAT. */
    uint8_t cluster_size; /**< Size of each cluster in number of sectors. */
    uint32_t clusters; /**< Number of clusters. */
    uint24_t fat_size; /**< Logical number of sectors per file allocation table. Ignores high byte. */
    uint24_t fat_pos; /**< Starting sector of the file allocation table. */
    uint24_t fs_info; /**< Sector where filesystem information is stored. */
    uint32_t fat_base_lba;
    uint32_t root_dir_pos;
    uint32_t data_region;
    uint32_t working_sector;
    uint32_t working_cluster;
    uint32_t working_next_cluster;
    uint32_t working_prev_cluster;
    uint32_t working_size;
    uint24_t working_pointer;
    uint24_t working_entry;
    uint24_t working_next_entry;
    uint24_t working_prev_entry;
} fat_t;

typedef struct {
    fat_t *fat;
    uint8_t flags; /**< Opening flags.  */
    uint32_t entry_sector; /**< Sector where file information is stored. */
    uint32_t first_cluster; /**< First cluster of the file. */
    uint32_t current_cluster; /**< Current cluster derived from offset. */
    uint32_t file_size; /**< Size of file in bytes. */
    uint24_t file_size_sectors; /**< Size of file in sectors */
    uint24_t fpossector; /**< File position by sector count. */
    uint8_t cluster_sector; /**< Current sector in cluster. */
    uint32_t current_sector; /**< Current sector on msd. */
    uint24_t working_buffer; /**< Buffer used by the library. */
    uint24_t entry_pointer; /**< Pointer to buffer index for entry. */
} fat_file_t;

typedef struct {
    char filename[13];
    uint8_t attrib;
    uint32_t size;
} fat_dir_entry_t;

typedef enum {
    FAT_SUCCESS=0,
    FAT_ERROR_INVALID_PARAM,
    FAT_ERROR_USB_FAILED,
    FAT_ERROR_NOT_SUPPORTED,
    FAT_ERROR_INVALID_CLUSTER,
    FAT_ERROR_EOF,
    FAT_ERROR_EXISTS,
    FAT_ERROR_INVALID_PATH,
    FAT_ERROR_FAILED_ALLOC,
    FAT_ERROR_CLUSTER_CHAIN,
    FAT_ERROR_DIRECTORY_NOT_EMPTY,
    FAT_ERROR_NO_VOLUME_LABEL,
    FAT_ERROR_RDONLY,
    FAT_ERROR_WRONLY
} fat_error_t;

typedef enum {
    MSD_SUCCESS=0,
    MSD_ERROR_INVALID_PARAM,
    MSD_ERROR_USB_FAILED,
    MSD_ERROR_NOT_SUPPORTED,
    MSD_ERROR_INVALID_DEVICE
} msd_error_t;

#define FAT_FILE      (0 << 0)  /**< Entry has no attributes. */
#define FAT_RDONLY    (1 << 0)  /**< Entry is read-only. */
#define FAT_HIDDEN    (1 << 1)  /**< Entry is hidden. */
#define FAT_SYSTEM    (1 << 2)  /**< Entry is a system file / directory. */
#define FAT_VOLLABEL  (1 << 3)  /**< Entry is a volume label -- only for root directory. */
#define FAT_DIR       (1 << 4)  /**< Entry is a directory (or subdirectory). */
#define FAT_ARCHIVE   (1 << 5)  /**< Entry is a directory (or subdirectory). */

typedef enum {
    FAT_LIST_FILEONLY, /**< For listing only files. */
    FAT_LIST_DIRONLY, /**< For listing only directories. */
    FAT_LIST_ALL /**< For listing files and directories. */
} fat_list_option_t;

#define FAT_O_RDONLY  (1 << 0) /**< Open file in read-only mode. */
#define FAT_O_WRONLY  (1 << 1) /**< Open file in write-only mode. */
#define FAT_O_RDWR    (FAT_O_RDONLY | FAT_O_WRONLY)  /**< Open file for reading and writing. */

#define MSD_SECTOR_SIZE 512 /**< Size of device sector, library only supports 512 bytes. */

/**
 * Locates any available FAT partitions detected on the mass storage device
 * (MSD). You must allocate space for \p partitions before calling this
 * function, as well as passing a valid msd_device_t from the msd_Init
 * function.
 * @param partitions Array of FAT partitions available, returned from function.
 * @param number The number of FAT partitions found.
 * @param max The maximum number of FAT partitions that can be found.
 * @return USB_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Find(msd_device_t *msd,
                     fat_partition_t *partitions,
                     uint8_t *number,
                     uint8_t max);

/**
 * Initializes the FAT filesystem and allows other FAT functions to be used.
 * Before calling this function, you must use fat_Find in order to
 * locate a valid FAT partition.
 * @param fat Uninitialized FAT structure type.
 * @param partition Available FAT partition returned from fat_Find.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Init(fat_t *fat,
                     fat_partition_t *partition);

/**
 * Deinitialize the FAT filesystem. This is not required to be called, however
 * it will clear the filesystem dirty bit so other OSes don't see the drive as
 * having potential errors. You cannot use the FAT structure after this call,
 * and should call fat_Init if you need to modify the filesystem again.
 * @param fat Initialized FAT structure type.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Deinit(fat_t *fat);

/**
 * Parses a directory and returns a list of files and subdirectories in it.
 * @param fat Initialized FAT structure type.
 * @param dir Directory path to get list from.
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
int24_t fat_DirList(fat_t *fat,
                    const char *path,
                    fat_list_option_t option,
                    fat_dir_entry_t *entries,
                    uint24_t size,
                    uint24_t skip);

/**
 * Returns the volume label of the drive if it exists.
 * @param fat Initialized FAT structure type.
 * @param label Storage for returning label, must be >= 13 bytes.
 * @retuns FAT_SUCCESS on success, FAT_ERROR_NO_VOLUME_LABEL if no label,
 *         otherwise a different error.
 */
fat_error_t fat_GetVolumeLabel(fat_t *fat,
                               char *label);

/**
 * Creates new files or directories in the filesystem.
 * @param fat Initialized FAT structure type.
 * @param path Path in which to create. Does not create subdirectories.
 * @param name Name of new file or directory.
 * @param attrib New entry attributes, can be a mask of FAT_RDONLY,
                 FAT_HIDDEN, FAT_SYSTEM, and FAT_DIR.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Create(fat_t *fat,
                       const char *path,
                       const char *name,
                       uint8_t attrib);

/**
 * Deletes a file or directory and deallocates the spaced used by it on disk.
 * @param fat Initialized FAT structure type.
 * @param path Absolute path to file or directory to delete.
 * @return FAT_SUCCESS on success, otherwise error.
 * @note This will only delete empty directories.
 */
fat_error_t fat_Delete(fat_t *fat,
                       const char *path);

/**
 * Sets the attributes (read only, hidden, etc) of the file.
 * @param fat Initialized FAT structure type.
 * @param path File path.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetAttrib(fat_t *fat,
                          const char *path,
                          uint8_t attrib);

/**
 * Gets the attributes (read only, hidden, etc) of the file.
 * @param fat Initialized FAT structure type.
 * @param path File path.
 * @return File attributes, or 255 if an error.
 */
uint8_t fat_GetAttrib(fat_t *fat,
                      const char *path);

/**
 * Sets the size of the file, allocating or deallocating space as needed.
 * This function should be called before attempting to write in a file that
 * does not have a large enough current file size, (i.e. a newly created file),
 * otherwise writes may always return FAT_ERROR_EOF.
 * @param fat Initialized FAT structure type.
 * @param path File path.
 * @param size New file size.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetSize(fat_t *fat,
                        const char *path,
                        uint32_t size);

/**
 * Gets the size of the file.
 * @param fat Initialized FAT structure type.
 * @param path File path.
 * @return File size in bytes.
 */
uint32_t fat_GetSize(fat_t *fat,
                     const char *path);

/**
 * Opens a file for either reading or writing, or both.
 * @param fat Initialized FAT structure type.
 * @param path File path to open or write.
 * @param flags Mode of opening, can be a mask of FAT_O_WDONLY,
                FAT_O_RDONLY, or just FAT_O_RDWR.
 * @return 0 if the file could not be opened, otherwise pointer
 *         to a file handle for other functions.
 */
fat_file_t *fat_Open(fat_t *fat,
                     const char *path,
                     uint8_t flags);

/**
 * Closes an open file handle, freeing it for future use.
 * @param file File handle returned from fat_Open.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Close(fat_file_t *file);

/**
 * Sets the sector offset position in the file.
 * @param file File handle returned from fat_Open.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_SetFilePos(fat_file_t *file, uint24_t sector);

/**
 * Gets the sector offset position in the file. Multiply return by the sector
 * size (512) to get the byte offet.
 * @param file File handle returned from fat_Open.
 * @return File offset in number of sectors.
 */
uint24_t fat_GetFilePos(fat_file_t *file);

/**
 * Reads multiple sectors (512 bytes each), and advances the file position.
 * @param file File handle returned from fat_Open.
 * @param num Number of sectors to read.
 * @param data Location to store read sector data.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_ReadSectors(fat_file_t *file,
                            uint24_t num,
                            void *data);

/**
 * Writes multiple sectors (512 bytes each), and advances the file position.
 * @param file File handle returned from fat_Open.
 * @param num Number of sectors to write to file.
 * @param data Location of writing sector data.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_WriteSectors(fat_file_t *file,
                             uint24_t num,
                             const void *data);

/**
 * Initialize a USB connected Mass Storage Device. Checks if the device is
 * a valid MSD device. Will perform all necessary MSD initialization.
 * A user-supplied buffer is needed for internal library use. This buffer must
 * be at least 512 bytes in size. It should not be the same buffer used
 * by other devices and/or functions.
 * @param msd MSD device structure.
 * @param dev USB device to initialize as MSD.
 * @param buffer The buffer's address. (must be 512 bytes).
 * @return MSD_SUCCESS on success, otherwise error if initialization failed.
 */
msd_error_t msd_Init(msd_device_t *msd,
                     usb_device_t dev,
                     void *buffer);

/**
 * Gets the sector count of the device.
 * @param msd MSD device structure.
 * @param blockSize Pointer to store block size to.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_GetSectorCount(msd_device_t *msd,
                               uint32_t *sectorCount);

/**
 * Gets the sector size of each sector on the device.
 * @param msd MSD device structure.
 * @param blockSize Pointer to store block size to.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_GetSectorSize(msd_device_t *msd,
                              uint24_t *sectorSize);

/**
 * Reads sectors from a Mass Storage Device.
 * @param msd MSD device structure.
 * @param lba Logical Block Address (LBA) of starting sector to read.
 * @param num Number of sectors to read.
 * @param data Buffer to read into. Should be the size of a sector multiplied by num.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_ReadSectors(msd_device_t *msd,
                            uint32_t lba,
                            uint24_t num,
                            void *data);

/**
 * Writes sectors of a Mass Storage Device.
 * @param msd MSD device structure.
 * @param lba Logical Block Address (LBA) of first sector.
 * @param num Number of sectors to write.
 * @param data Data to write to MSD. Should be the size of a sector multiplied by num.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_WriteSectors(msd_device_t *msd,
                             uint32_t lba,
                             uint24_t num,
                             const void *data);

#ifdef __cplusplus
}
#endif

#endif
