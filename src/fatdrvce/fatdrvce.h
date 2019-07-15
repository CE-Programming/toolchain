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
 * @author Steven "s@rdw.se" Arnow
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 */

#ifndef H_FATDRVCE
#define H_FATDRVCE

#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <usbdrvce.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    usb_device_t dev;    /**< USB device */
    usb_endpoint_t in;   /**< USB bulk in endpoint */
    usb_endpoint_t out;  /**< USB bulk out endpoint */
    usb_endpoint_t ctrl; /**< USB Control endpoint */
    uint8_t interface;   /**< USB Interface index */
    uint8_t maxlun;      /**< Maximum LUNs for MSD */
    uint8_t lun;         /**< Selected LUN for MSD */
    void *buffer;        /**< User supplied buffer address */
} msd_device_t;

typedef struct {
    msd_device_t *msd;  /**< MSD containing FAT filesystem */
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

/**
 * Initialize a USB connected Mass Storage Device. Checks if the device is
 * a valid MSD device. Will perform all necessary MSD initialization.
 * A user-supplied buffer is needed for internal library use. This buffer must
 * be at least 512 bytes in size. It should not be the same buffer used
 * by other devices and/or functions.
 * @param msd MSD device structure.
 * @param dev USB device to initialize as MSD.
 * @param buffer The buffer's address. (must be at least 512 bytes).
 * @return USB_SUCCESS on success, otherwise error if initialization failed.
 */
usb_error_t msd_Init(msd_device_t *msd, usb_device_t dev, void *buffer);

/**
 * Gets the block size from the device.
 * @param msd MSD device structure.
 * @param blockSize Pointer to store block size to.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_GetBlockSize(msd_device_t *msd, uint32_t *blockSize);

/**
 * Gets the sector count of the device.
 * @param msd MSD device structure.
 * @param blockSize Pointer to store block size to.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_GetSectorCount(msd_device_t *msd, uint32_t *sectorCount);

/**
 * Gets the sector size of each sector on the device.
 * @param msd MSD device structure.
 * @param blockSize Pointer to store block size to.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_GetSectorSize(msd_device_t *msd, uint24_t *sectorSize);

/**
 * Reads sectors from a Mass Storage Device.
 * @param msd MSD device structure.
 * @param lba Logical Block Address (LBA) of starting sector to read.
 * @param sectors Number of sectors to read.
 * @param buffer Buffer to read into. Should be at least a sector size.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_ReadSectors(msd_device_t *msd, uint32_t lba, uint24_t sectors,
                            void *data);

/**
 * Writes sectors to a Mass Storage Device.
 * @param msd MSD device structure.
 * @param lba Logical Block Address (LBA) of sector to write.
 * @param sectors Number of sectors to write.
 * @param buffer Buffer to write to MSD. Should be at least one sector size.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_WriteSectors(msd_device_t *msd, uint32_t lba, uint24_t sectors,
                             const void *data);

#ifdef __cplusplus
}
#endif

#endif
