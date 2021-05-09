/**
 * @file
 * @brief MSD FAT Filesystem Driver
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
 * The drive must use MBR partitioning, GUID and others are not yet supported.
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

typedef struct {
    usb_device_t dev; /**< USB device */
    uint8_t bulkinaddr; /**< USB bulk in endpoint address */
    uint8_t bulkoutaddr; /**< USB bulk out endpoint address */
    uint8_t configindex; /**< USB config descriptor index */
    uint24_t tag; /**< MSD Command Block Wrapper next tag */
    uint32_t lba; /**< Logical Block Address of LUN */
    uint32_t blocksize; /**< Block size */
    uint8_t interface; /**< USB Interface index */
    uint8_t maxlun; /**< Maximum LUNs for MSD */
    void *buffer; /**< Buffer for internal library use */
} msd_device_t;

typedef struct msd_transfer_t {
    msd_device_t *dev; /**< Initialized MSD device */
    uint32_t lba; /**< Logical block address */
    void *buffer; /**< Pointer to data location to read/write */
    uint8_t count; /**< Number of blocks to transfer */
    msd_transfer_t *next; /**< Next MSD transfer */
    void (*callback)(msd_transfer_t *); /**< Called on last MSD transfer */
    void *userptr; /**< Custom user data for callback (optional) */
} msd_transfer_t;

typedef enum {
    MSD_SUCCESS = 0, /**< Operation was successful */
    MSD_ERROR_INVALID_PARAM, /**< An invalid argument was provided */
    MSD_ERROR_USB_FAILED, /**< An error occurred in usbdrvce */
    MSD_ERROR_NOT_SUPPORTED, /**< The operation is not supported */
    MSD_ERROR_INVALID_DEVICE, /**< An invalid usb device was specified */
} msd_error_t;

#define MSD_BLOCK_SIZE 512 /**< Block size of the device in bytes */
#define MSD_USER_BUFFER_SIZE 2048 /**< User buffer size in bytes */

/**
 * Initialize a Mass Storage Device.
 * A unique user buffer is needed for internal library use. This buffer must
 * be at least 2048 bytes in size. It should not be the same buffer used
 * by other devices and/or functions.
 * @param msd Uninitilaized MSD device structure.
 * @param dev Initialized USB device structure.
 * @param buffer Pointer to user buffer. (must be at least 2048 bytes)
 * @return MSD_SUCCESS on success, otherwise error.
 */
msd_error_t msd_Open(msd_device_t *msd, usb_device_t dev, void *buffer);

/**
 * Closes and deinitializes a Mass Storage Device. This function should be
 * called in the \c USB_DEVICE_DISCONNECTED_EVENT in the USB handler callback.
 * @param msd Initialized MSD device structure.
 */
void msd_Close(msd_device_t *msd);

/**
 * Attempts to reset and restore normal working order of the device.
 * @param msd Initialized MSD device structure.
 * @return MSD_SUCCESS on success, otherwise error.
 */
msd_error_t msd_Reset(msd_device_t *msd);

/**
 * Gets the number of and size of each block (sector) on the device.
 * @param msd Initialized MSD device structure.
 * @param num Pointer to store number of sectors to.
 * @param size Pointer to store sector size to.
 * @return MSD_SUCCESS on success.
 */
msd_error_t msd_Info(msd_device_t *msd, uint32_t *num, uint32_t *size);

/**
 * Asynchronous block read.
 * @param transfer Initialized transaction structure.
 * @return MSD_SUCCESS if the transfer has been added to the queue.
 */
msd_error_t msd_ReadAsync(msd_transfer_t *xfer);

/**
 * Asynchronous block write.
 * @param transfer Initialized transaction structure.
 * @return MSD_SUCCESS if the transfer has been added to the queue.
 */
msd_error_t msd_WriteAsync(msd_transfer_t *xfer);

#ifdef __cplusplus
}
#endif

#endif
