/**
 * @file
 * @brief Mass Storage Device (MSD) Driver
 *
 * @author Matt "MateoConLechuga" Waltz
 * @author Jacob "jacobly" Young
 */

#ifndef MSDDRVCE_H
#define MSDDRVCE_H

#include <stdint.h>
#include <stdbool.h>
#include <usbdrvce.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MSD_BLOCK_SIZE 512 /**< Block size in bytes */

/** Mass Storage Driver return codes */
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
/* @cond */
    uint8_t priv[1024]; /**< Internal library use */
/* @endcond */
} msd_t;

typedef struct {
    uint32_t bsize; /**< Size of each block in bytes */
    uint32_t bnum; /**< Number of blocks on MSD */
} msd_info_t;

typedef struct msd_transfer {
    msd_t *msd; /**< Initialized MSD device */
    uint32_t lba; /**< Logical block address */
    void *buffer; /**< Pointer to data location to read/write */
    uint24_t count; /**< Number of blocks to transfer */
    void (*callback)(msd_error_t error, struct msd_transfer *xfer); /**< Called when transfer completes */
    void *userptr; /**< Custom user data for callback (optional) */
/* @cond */
    uint8_t priv[76];
/* @endcond */
} msd_transfer_t;

typedef struct {
    uint32_t first_lba; /**< First Logical Block Address (LBA) of partition */
    uint32_t last_lba; /**< Last Logical Block Address (LBA) of partition */
} msd_partition_t;

/**
 * Initialize a Mass Storage Device.
 * @param msd Uninitilaized MSD device structure.
 * @param usb Initialized USB device structure.
 * @return MSD_SUCCESS on success, otherwise error.
 */
msd_error_t msd_Open(msd_t *msd, usb_device_t usb);

/**
 * Closes and deinitializes a Mass Storage Device. This function should also be
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
 * Asynchronous block read. You must set the following \p xfer elements:
 * \p msd, \p lba, \p buffer, \p count, \p callback. The optional element
 * \p userptr can be used to store user-defined data for access in the callback.
 * The \p xfer argument must remain valid (cannot be free'd or lose scope)
 * until the callback is issued. You can free \p xfer inside the callback as
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
 * until the callback is issued. You can free \p xfer inside the callback as
 * needed.
 * @param xfer Initialized transaction structure.
 * @return MSD_SUCCESS if the transfer has been added to the queue.
 */
msd_error_t msd_WriteAsync(msd_transfer_t *xfer);

/**
 * Synchronous block read.
 * @param msd Initialized MSD structure.
 * @param lba Logical Block Address (LBA) of starting block to read.
 * @param count Number of blocks to read.
 * @param buffer Buffer to read into. Must be at least \p MSD_BLOCK_SIZE * \p count bytes.
 * @return Number of blocks read, on success should equal \p count.
 */
uint24_t msd_Read(msd_t *msd, uint32_t lba, uint24_t count, void *buffer);

/**
 * Synchronous block write.
 * @param msd Iniailized MSD structure.
 * @param lba Logical Block Address (LBA) of starting block to read.
 * @param count Number of blocks to write.
 * @param buffer Buffer to write. Must be at least \p MSD_BLOCK_SIZE * \p count bytes.
 * @return Number of blocks written, on success should equal \p count.
 */
uint24_t msd_Write(msd_t *msd, uint32_t lba, uint24_t count, const void *buffer);

/**
 * Returns a list of partitions detected on the device.
 * You must allocate space for \p partitions before calling this
 * function, as well as passing a valid msd_t returned from msd_Open.
 * @param msd Initialized MSD structure returned from msd_Open.
 * @param partitions Returned array of partitions available.
 * @param max The maximum number of partitions that can be found.
 * @return Number of partitions detected; \p partitions will be filled with
 *         valid partition information up to the number detected.
 * @note Currently MBR (msdos) and GUID (gpt) partition tables are supported.
 */
uint8_t msd_FindPartitions(msd_t *msd, msd_partition_t *partitions, uint8_t max);

#ifdef __cplusplus
}
#endif

#endif
