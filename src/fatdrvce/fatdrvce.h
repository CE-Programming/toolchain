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
    usb_device_t dev;   /**< USB device */
    void *buffer;       /**< User supplied buffer address */
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
 * Sets up the buffer used for MSD driver handling. This buffer must
 * be at least 512 bytes in size. It should not be the same buffer used
 * by other devices and/or functions.
 * @param dev MSD device returned by \c msd_Find.
 * @param buffer The buffer's address.
 * @return USB_SUCCESS on success, otherwise error if the device could not be initialized.
 */
usb_error_t msd_SetupDevice(msd_device_t *msd, usb_device_t dev, void *buffer);

/**
 * Checks if the usb device is a valid Mass Storage Device (MSD).
 * @param prev Previous found device, supply NULL to start the search.
 * @return USB_SUCCESS if the device is a Mass Storage Device.
 */
usb_error_t msd_ValidDevice(usb_device_t dev);

/**
 * Directly reads a 512 byte sector from the Mass Storage Device into the
 * buffer specified by msd_SetDataBuffer().
 * @param dev MSD device returned by \c msd_Find.
 * @param lba Logical Block Address (LBA) of sector to read.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_Read(msd_device_t *dev, uint32_t lba, void *buffer);

/**
* Directly writes a 512 byte sector to the Mass Storage Device from the
* buffer specified by msd_SetDataBuffer().
 * @param dev MSD device returned by \c msd_Find.
 * @param lba Logical Block Address (LBA) of sector to write.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_Write(msd_device_t *dev, uint32_t lba, void *buffer);

/**
 * Schedules a read of a 512 byte sector from the Mass Storage Device.
 * @param dev MSD device returned by \c msd_Find.
 * @param lba Logical Block Address (LBA) of sector to read.
 * @param handler Function to be called when the read finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_ScheduleRead(msd_device_t *dev, uint32_t lba, void *buffer,
                             usb_transfer_callback_t handler,
                             usb_transfer_data_t *data);

/**
* Schedules a write of a 512 byte sector to the Mass Storage Device.
 * @param dev MSD device returned by \c msd_Find.
 * @param lba Logical Block Address (LBA) of sector to write.
 * @param handler Function to be called when the write finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS on success.
 */
usb_error_t msd_ScheduleWrite(msd_device_t *dev, uint32_t lba, void *buffer,
                              usb_transfer_callback_t handler,
                              usb_transfer_data_t *data);

#ifdef __cplusplus
}
#endif

#endif
