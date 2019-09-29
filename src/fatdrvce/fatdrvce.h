/**
 * @file
 * @brief USB FAT Filesystem Driver
 *
 * This library can be used to communicate with Mass Storage Devices (MSD) which
 * have partitions formated as FAT32. (FAT16 support is implemented yet untested).
 * It currently only supports drives that have a sector size of 512, which is pretty
 * much every flash drive on the market, except for huge ones.
 * The drive must use MBR partitioning, GUID is not supported.
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
    usb_device_t dev;    /**< USB device */
    usb_endpoint_t in;   /**< USB bulk in endpoint */
    usb_endpoint_t out;  /**< USB bulk out endpoint */
    usb_endpoint_t ctrl; /**< USB Control endpoint */
    uint24_t tag;        /**< MSD Command Block Wrapper incrementing tag */
    uint32_t lba;        /**< Logical Block Address of LUN */
    uint32_t blocksize;  /**< Block size (usually 512) */
    uint8_t interface;   /**< USB Interface index */
    uint8_t maxlun;      /**< Maximum LUNs for MSD */
    void *buffer;        /**< User supplied buffer address */
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
    uint24_t working_pointer;
} fat_t;

typedef struct {
    fat_t *fat;
    uint8_t flags;
    uint32_t entry_sector;
    uint32_t first_cluster;
    uint32_t current_cluster;
    uint32_t file_size;
    uint24_t file_size_sectors;
    uint32_t fpos;           /**< File position by bytes. */
    uint24_t fpossector;     /**< File position by sector count. */
    uint8_t cluster_sector;  /**< Current sector in cluster. */
    uint32_t current_sector; /**< Current sector on msd. */
    uint24_t working_buffer;
    uint24_t entry_pointer;
} fat_file_t;

typedef enum {
    FAT_SUCCESS=0,
    FAT_ERROR_INVALID_PARAM,
    FAT_ERROR_USB_FAILED,
    FAT_ERROR_NOT_SUPPORTED,
    FAT_ERROR_INVALID_CLUSTER,
    FAT_ERROR_EOF,
    FAT_ERROR_EXISTS,
    FAT_ERROR_INVALID_PATH,
    FAT_ERROR_FAILED_ALLOC
} fat_error_t;

typedef enum {
    MSD_SUCCESS=0,
    MSD_ERROR_INVALID_PARAM,
    MSD_ERROR_USB_FAILED,
    MSD_ERROR_NOT_SUPPORTED,
    MSD_ERROR_INVALID_DEVICE
} msd_error_t;

#define FAT_OPEN_WRONLY  2  /**< Open file in write-only mode. */
#define FAT_OPEN_RDONLY  1  /**< Open file in read-only mode. */
#define FAT_OPEN_RDWR    (FAT_OPEN_RDONLY | FAT_OPEN_WRONLY)  /**< Open file for reading and writing. */

#define FAT_RDONLY    (1 << 0)  /**< Entry is read-only. */
#define FAT_HIDDEN    (1 << 1)  /**< Entry is hidden. */
#define FAT_SYSTEM    (1 << 2)  /**< Entry is a system file / directory. */
#define FAT_VOLLABEL  (1 << 3)  /**< Entry is a volume label -- only for root directory. */
#define FAT_DIR       (1 << 4)  /**< Entry is a directory (or subdirectory). */
#define FAT_ALL       (FAT_DIR | FAT_VOLLABEL | FAT_SYSTEM | FAT_HIDDEN | FAT_RDONLY)

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
 * Opens a file for either reading or writing, or both.
 * @param fat Initialized FAT structure type.
 * @param filepath File path to open or write.
 * @param flags Mode of opening, can be a mask of FAT_OPEN_WRONLY,
                FAT_OPEN_RDONLY, and FAT_OPEN_RDWR.
 * @return 0 if the file could not be opened, otherwise pointer
 *         to a file handle for other functions.
 */
fat_file_t *fat_Open(fat_t *fat,
                     const char *filepath,
                     uint8_t flags);

/**
 * Closes an open file handle, freeing it for future use.
 * @param file File handle returned from fat_Open.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_Close(fat_file_t *file);

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
 * Gets the size of the file.
 * @param file File handle returned from fat_Open.
 * @return File size in bytes.
 */
uint32_t fat_FileSize(fat_file_t *file);

/**
 * Gets the offset position in the file.
 * @param file File handle returned from fat_Open.
 * @return File offset in bytes.
 */
uint32_t fat_FilePos(fat_file_t *file);

/**
 * Reads a whole sector (512 bytes) from a file, and advances the file
 * position offset to the next sector.
 * @param file File handle returned from fat_Open.
 * @param data Location to store read sector data, must be at least 512 bytes.
 * @return FAT_SUCCESS on success, otherwise error.
 */
fat_error_t fat_ReadSector(fat_file_t *file,
                           void *data);

/**
 * Initialize a USB connected Mass Storage Device. Checks if the device is
 * a valid MSD device. Will perform all necessary MSD initialization.
 * A user-supplied buffer is needed for internal library use. This buffer must
 * be at least 512 bytes in size. It should not be the same buffer used
 * by other devices and/or functions.
 * @param msd MSD device structure.
 * @param dev USB device to initialize as MSD.
 * @param buffer The buffer's address. (must be at least 512 bytes).
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
 * Reads a single sector from a Mass Storage Device.
 * @param msd MSD device structure.
 * @param lba Logical Block Address (LBA) of starting sector to read.
 * @param sectors Number of sectors to read.
 * @param buffer Buffer to read into. Should be at least a sector size.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_ReadSector(msd_device_t *msd,
                           uint32_t lba,
                           void *data);

/**
 * Writes a single sector of a Mass Storage Device.
 * @param msd MSD device structure.
 * @param lba Logical Block Address (LBA) of sector to write.
 * @param buffer Buffer to write to MSD. Should be at least one sector size.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_WriteSectors(msd_device_t *msd,
                             uint32_t lba,
                             const void *data);

#ifdef __cplusplus
}
#endif

#endif
