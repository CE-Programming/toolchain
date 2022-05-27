/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief This has something to do with TI Python.
 */

#ifndef TI_PYTHON_H
#define TI_PYTHON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform an MSD GetMaxLUN request, either through the USB port or with an ARM coprocessor.
 * @param[in,out] value On input the wValue to use in the request (should be zero for usb?), on output the max logical unit number.
 */
void os_MSDGetMaxLUN(uint8_t *value);

/**
 * Perform an MSD mass storage reset request, either through the USB port or with an ARM coprocessor.
 * @param[in] value Affects the wValue of the request, 1 for 0x55AA, 2 for 0xAA55, otherwise 0x0000 (for usb).
 */
void os_MSDReset(uint8_t value);

/**
 * Performs an MSD inquiry, either through the USB port or with an ARM coprocessor.
 * @param[in] lun Logical unit number.
 * @param[out] inquiry Buffer where the response is stored.
 * @return Error code, 0 for success, 5 for failed command, -5 for failed transfer.
 */
int8_t os_MSDInquiry(uint8_t lun, uint8_t *inquiry);

/**
 * Performs an MSD test unit ready command, either through the USB port or with an ARM coprocessor.
 * @param[in] lun Logical unit number.
 * @param[out] status Returns the status of the command.
 */
void os_MSDTestUnitReady(uint8_t lun, uint8_t *status);

/**
 * Performs an MSD read capacity command, either through the USB port or with an ARM coprocessor.
 * @param lun Logical unit number.
 * @param data Returns the returned logical block address and block byte length.
 * @return Error code, 0 for success, 5 for failed command, -5 for failed transfer.
 */
int8_t os_MSDReadCapacity(uint8_t lun, uint32_t data[2]);

/**
 * Performs an MSD read command, either through the USB port or with an ARM coprocessor.
 * @param[in] lun Logical unit number.
 * @param[in] blockCount Number of blocks to read.
 * @param[in] lba Logical block address to start reading from.
 * @param[in] blockSize Block size, obtained from os_MSDReadCapacity().
 * @param[out] buffer Buffer to read data into, should be blockCount * blockSize bytes.
 * @return Error code, 0 for success, 5 for failed command, -5 for failed transfer.
 */
int8_t os_MSDRead(uint8_t lun, uint8_t blockCount, uint32_t lba, uint24_t blockSize, void *buffer);

/**
 * Performs an MSD write command, either through the USB port or with an ARM coprocessor.
 * @param[in] lun Logical unit number.
 * @param[in] blockCount Number of blocks to write.
 * @param[in] lba Logical block address to start writing to.
 * @param[in] blockSize Block size, obtained from os_MSDReadCapacity().
 * @param[in] buffer Buffer of data to write, should be blockCount * blockSize bytes.
 * @return Error code, 0 for success, 5 for failed command, -5 for failed transfer.
 */
int8_t os_MSDWrite(uint8_t lun, uint8_t blockCount, uint32_t lba, uint24_t blockSize, void *buffer);

#ifdef __cplusplus
}
#endif

#endif
