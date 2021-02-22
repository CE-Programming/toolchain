/**
 * @file
 * @brief USB Serial Driver
 *
 * This library can be used to communicate with USB serial devices.
 *
 * @author commandblockguy
 */

#ifndef H_SRLDRVCE
#define H_SRLDRVCE

#include <stddef.h>
#include <stdint.h>
#include <usbdrvce.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t srl_error_t;
enum srl_error {
    SRL_SUCCESS,
    SRL_IGNORE,
    SRL_ERROR_SYSTEM,
    SRL_ERROR_INVALID_PARAM,
    SRL_ERROR_SCHEDULE_FULL,
    SRL_ERROR_NO_DEVICE,
    SRL_ERROR_NO_MEMORY,
    SRL_ERROR_NOT_SUPPORTED,
    SRL_ERROR_TIMEOUT,
    SRL_ERROR_FAILED,
    SRL_ERROR_INVALID_INTERFACE,
    SRL_USER_ERROR = 100,
};

enum srl_DeviceType {
    SRL_UNKNOWN, /**< Incompatible or non-serial device */
    SRL_HOST,    /**< Calc is acting as a device */
    SRL_CDC,     /**< CDC device */
    SRL_FTDI     /**< FTDI device */
};

typedef uint8_t srl_deviceType_t;

enum srl_SubType_FTDI {
    FTDI_UNKNOWN = 0,
    SIO,
    FT8U232AM,
    FT232BM,
    FT2232C,
    FT232RL,
    FTX,
    FT2232H,
    FT4232H,
    FT232H,
};

typedef uint8_t srl_subType_t;

typedef struct srl_Device {
    usb_device_t dev;       /**< USB device */
    usb_endpoint_t in;      /**< USB bulk in endpoint */
    usb_endpoint_t out;     /**< USB bulk out endpoint */
    srl_deviceType_t type;  /**< Device type */
    srl_subType_t subType;  /**< Device sub-type */
    char *readBuf;          /**< Pointer to the read buffer */
    size_t readBufSize;     /**< Size of the read buffer */
    char *readBufStart;     /**< First byte with data in the read buffer */
    char *readBufEnd;       /**< Last byte with data in the read buffer */
    char *readBufBreak;     /**< Last byte before the buffer "loops" */
    bool readBufActive;     /**< Whether data is being read into the read buffer */
    bool stopRead;          /**< Set when waiting for the read to stop */
    char *writeBuf;         /**< Pointer to the write buffer */
    size_t writeBufSize;    /**< Size of the write buffer */
    char *writeBufStart;    /**< First byte with data in the write buffer */
    char *writeBufEnd;      /**< Last byte with data in the write buffer */
} srl_device_t;

#define SRL_INTERFACE_ANY 0xFF


/**
 * Initializes a serial device and assigns it a buffer.
 * The buffer must be at least 128 bytes long, but a size of 512 bytes is recommended.
 * @param dev USB device to be used as a serial device.
 * @param buf The buffer's address.
 * @param size The size of the buffer
 * @param rate The baud rate to set the device to
 * @param interface The interface number to use, or SRL_INTERFACE_ANY for the first available interface
 * @return USB_SUCCESS on success, otherwise an error.
 */
srl_error_t srl_Init(srl_device_t *srl, usb_device_t dev, void *buf, size_t size, uint8_t interface);

/**
 * Set the baud rate of the device.
 * @param rate Baud rate.
 * @return USB_SUCCESS on success, otherwise an error.
 */
srl_error_t srl_SetRate(srl_device_t *srl, uint24_t rate);

/**
 * Get the number of bytes available in the input buffer.
 */
size_t srl_Available(srl_device_t *srl);

/**
 * Performs a non-blocking read of data.
 * If there are less than length bytes available, all available data will be read.
 * @param buffer Buffer that data is read in to.
 * @param length Maximum amount of data to read.
 * @return The amount of data actually read.
 */
size_t srl_Read(srl_device_t *srl, void *buffer, size_t length);

/**
 * Performs a non-blocking write of data.
 * @param buffer Data to write.
 * @param length Amount of data to write.
 * @return The amount of data actually written.
 */
size_t srl_Write(srl_device_t *srl, const void *buffer, size_t length);

/**
 * Performs a blocking read of data.
 * If there are less than length bytes available, the function will wait until
 * the timeout is exceeded or length bytes become available.
 * @param buffer Buffer that data is read in to.
 * @param length Amount of data to read.
 * @param timeout Timeout in milliseconds, or 0 for no timeout.
 * @return The amount of data read.
 */
size_t srl_Read_Blocking(srl_device_t *srl, void *buffer, size_t length, uint24_t timeout);

/**
 * Performs a blocking write of data.
 * The function will wait until the timeout is exceeded or all data is transmitted.
 * @param buffer Data to write.
 * @param length Amount of data to write.
 * @param timeout Timeout in milliseconds, or 0 for no timeout.
 * @return The amount of data actually written.
 */
size_t srl_Write_Blocking(srl_device_t *srl, const void *buffer, size_t length, uint24_t timeout);

/**
 * Returns a pointer to CDC ACM descriptors, to be used with usb_Init
 */
usb_standard_descriptors_t *srl_GetCDCStandardDescriptors(void);

#ifdef __cplusplus
}
#endif

#endif
