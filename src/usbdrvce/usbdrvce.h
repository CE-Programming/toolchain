/**
 * @file
 * @author Jacob "jacobly" Young
 * @brief USB driver
 */

#ifndef H_USBDRVCE
#define H_USBDRVCE

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum usb_init_flags {
  USB_USE_C_HEAP   = 1 << 1, /**< Use part of the default C heap. @warning Do not use this unless you changed your program's bss/heap to end at 0xD10000! */
  USB_USE_USB_AREA = 1 << 2, /**< Use the memory that TIOS uses for usb. */
  USB_USE_OS_HEAP  = 1 << 3, /**< Use the application heap area. */
  USB_DEFAULT_INIT_FLAGS = USB_USE_USB_AREA | USB_USE_OS_HEAP, /**< Default flags for use with usb_init(). */
} usb_init_flags_t;

typedef enum usb_error {
  USB_SUCCESS,
  USB_IGNORE,
  USB_ERROR_SCHEDULE_FULL,
  USB_ERROR_NO_DEVICE,
  USB_ERROR_NO_MEMORY,
  USB_ERROR_NOT_SUPPORTED,
} usb_error_t;

typedef enum usb_find_flags {
  USB_FIND_INACTIVE = 1 << 0, /**< Only return unactivated devices. */
  USB_FIND_ACTIVE   = 1 << 1, /**< Only return activated devices. */
  USB_FIND_DEVICE   = 1 << 2, /**< Only return non-hubs. */
  USB_FIND_HUB      = 1 << 3, /**< Only return hubs. */
} usb_find_flags_t;

typedef enum usb_speed {
  USB_SPEED_UNKNOWN = -1,
  USB_SPEED_FULL,
  USB_SPEED_LOW,
  USB_SPEED_HIGH,
  USB_SPEED_SUPER,
} usb_speed_t;

typedef enum usb_transfer_type {
  USB_CONTROL_TRANSFER,
  USB_ISOCHRONOUS_TRANSFER,
  USB_BULK_TRANSFER,
  USB_INTERRUPT_TRANSFER,
} usb_transfer_type_t;

typedef enum usb_transfer_status {
  USB_TRANSFER_COMPLETED,      /**< Transfered successfully. @note A receive transfer will complete when the end of a packet is detected, or the buffer is filled, whichever happens first. */
  USB_TRANSFER_STALLED,        /**< Endpoint halt condition detected or control request not supported. */
  USB_TRANSFER_FAILED,         /**< Transfer failed due to timout and/or corruption. */
  USB_TRANSFER_MEMORY_ERROR,   /**< Memory could not be accessed in a timely enough fashion to complete the transfer. */
  USB_TRANSFER_OVERFLOW_ERROR, /**< Device sent more bytes than can be stored in the transfer buffer, and were therefore lost. This can be avoided be making sure receive buffers lengths are always a multiple of the endpoint's maximum packet length. */
  USB_TRANSFER_HOST_ERROR,     /**< The results of the transaction were missed due to host hold-off. This probably indicates a bug in this library. */
  USB_TRANSFER_NO_DEVICE,      /**< The device was disconnected. */
} usb_transfer_status_t;

typedef struct usb_device *usb_device_t; /**< opaque handle representing a connected device */

/**
 * Type of the function to be called when a usb device is connected or disconnected.
 * @param device Handle for the device that was connected or disconnected.
 * @param data Opaque pointer passed to usb_Init().
 * @return Return USB_SUCCESS to initialize the device, USB_IGNORE to ignore a device without erroring, or an error to ignore the device and return from usb_HandleEvents().
 */
typedef usb_error_t (*device_callback_t)(usb_device_t device, void *data);

/**
 * Type of the function to be called when a transfer finishes.
 * @param device The device that was communicated with.
 * @param endpoint Endpoint communicated with, ored with hshb_index << 5.
 * @param status Status of the transfer.
 * @param data Opaque pointer passed to usb_ScheduleTransfer().
 * @param transferred The number of bytes transferred.
 * Only valid if \p status was USB_TRANSFER_COMPLETED.
 * @return Return USB_SUCCESS to free the transfer, USB_IGNORE to restart the transfer or an error to free the transfer and return from usb_HandleEvents().
 */
typedef usb_error_t (*transfer_callback_t)(usb_device_t device, uint8_t endpoint, usb_transfer_status_t status, size_t transferred, void *data);

/**
 * Initializes the usb driver.
 * @param connect_handler Function to be called when a usb device is connected.
 * @param connect_data Opaque pointer to be passed to the \p connect_handler.
 * @param disconnect_handler Function to be called when a usb device is disconnected.
 * @param disconnect_data Opaque pointer to be passed to the \p disconnect_handler.
 * @param flags Which areas of memory to use.
 * @return USB_SUCCESS if initialization succeeded.
 * @note This must be called before any other function, and can be called again
 * to cancel all transfers and close all connections.
 */
usb_error_t usb_Init(device_callback_t connect_handler, void *connect_data, device_callback_t disconnect_handler, void *disconnect_data, usb_init_flags_t flags);

/**
 * Deinitializes the usb driver.
 * @note This must be called before the program exits.
 */
void usb_Cleanup(void);

/**
 * Finds the first device satisfying flags.
 * @param flags What kinds of devices to return.
 * @return The first matching device, or NULL if no matching devices.
 */
usb_device_t usb_FindFirstDevice(usb_find_flags_t flags);

/**
 * Finds the next device after \p from satisfying flags.
 * @param from Device to start the search from.
 * @param flags What kinds of devices to return.
 * @return The first matching device after \p from, or NULL if no matching devices.
 */
usb_device_t usb_FindNextDevice(usb_device_t from, usb_find_flags_t flags);

/**
 * Calls any triggered device or transfer callbacks.
 * @return An error returned by a callback or USB_SUCCESS.
 */
usb_error_t usb_HandleEvents(void);

/**
 * Clears an endpoint's halt/stall condition.
 * @param device The device to communicate with.
 * @param endpoint The endpoint to communicate with.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ClearHalt(usb_device_t device, uint8_t endpoint);

/**
 * Performs a usb reset on a device. This causes an inactive device to become active.
 * @param device The device to communicate with.
 * @param endpoint The endpoint to communicate with.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ResetDevice(usb_device_t device);

/**
 * Gets a device's address.
 * @param device The device to communicate with.
 * @return The usb address of \p device.
 */
uint8_t usb_GetDeviceAddress(usb_device_t device);

/**
 * Gets a device's speed.
 * @param device The device to communicate with.
 * @return The usb speed of \p device, or USB_SPEED_UNKNOWN if unknown.
 */
usb_speed_t usb_GetDeviceSpeed(usb_device_t device);

/**
 * Gets the maximum packet size of an endpoint.
 * @param device The device to communicate with.
 * @param endpoint The endpoint to communicate with.
 * @return The endpoint's wMaxPacketSize or 0 on error.
 */
usb_speed_t usb_GetMaxPacketSize(usb_device_t device, uint8_t endpoint);

/**
 * Determines how large of a buffer would be required to receive the complete configuration descriptor at \p index.
 * @param device The device to communicate with.
 * @param index Which configuration descriptor to query.
 * @param total_length Returns the number of bytes in the complete configuration descriptor.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetConfigurationDescriptorTotalLength(usb_device_t device, uint8_t index, size_t *total_length);

/**
 * Fetches the configuration at \p index.
 * @param device The device to communicate with.
 * @param type Descriptor type to fetch.
 * @param index Descriptor index to fetch.
 * @param descriptor Returns the fetched descriptor.
 * @param length The number of bytes to transfer.
 * The \p descriptor buffer must by at least this large.
 * @param transferred Returns the number of bytes actually received.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetDescriptor(usb_device_t device, uint8_t type, uint8_t index, void *descriptor, size_t length, size_t *transferred);

/**
 * Changes the configuration at \p index, not usually supported.
 * @param device The device to communicate with.
 * @param type Descriptor type to modify.
 * @param index Descriptor index to modify.
 * @param descriptor The new descriptor data.
 * @param length The number of bytes in the new descriptor.
 * The \p descriptor buffer must by at least this large.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetDescriptor(usb_device_t device, uint8_t type, uint8_t index, void *descriptor, size_t length);

/**
 * Gets the currently active configuration of a device.
 * @param device The device to communicate with.
 * @param configuration Returns the current configuration value, or 0 if unconfigured.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetConfiguration(usb_device_t device, uint8_t *configuration);

/**
 * Selects the configuration specified by the \p configuration_descriptor.
 * This must be called before pipes other than the default control pipe can be accessed.
 * @param device The device to communicate with.
 * @param configuration_descriptor A complete configuration descriptor fetched with usb_GetDescriptor().
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetConfiguration(usb_device_t device, void *configuration_descriptor);

/**
 * Selects the configuration specified by the \p configuration_descriptor.
 * This must be called before pipes other than the default control pipe can be accessed.
 * @param device The device to communicate with.
 * @param interface Interface index to query.
 * @param alternate_setting Returns the alternate setting in use.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetInterfaceAltSetting(usb_device_t device, uint8_t interface, uint8_t *alternate_setting);

/**
 * Selects the configuration specified by the \p configuration_descriptor.
 * This must be called before pipes other than the default control pipe can be accessed.
 * @param device The device to communicate with.
 * @param interface Interface index to modify.
 * @param alternate_setting Alternate setting to use.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetInterfaceAltSetting(usb_device_t device, uint8_t interface, uint8_t alternate_setting);

/**
 * Schedules a control transfer and waits for it to complete.
 * @param device The device to communicate with.
 * @param endpoint Address of the control endpoint to communicate with.
 * Bit 7 is ignored.
 * @param bmRequestType The request type field of the setup packet.
 * Bit 7 specifies the direction of the transfer.
 * @param bRequest The request field of the setup packet.
 * @param wValue The value field of the setup packet.
 * @param wIndex The index field of the setup packet.
 * @param buffer Data to transfer that must reside in RAM.
 * @param wLength The length field of the setup packet.
 * The buffer must be at least this large.
 * @param transferred Returns the number of bytes actually transferred.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ControlTransfer(usb_device_t device, uint8_t endpoint, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, void *buffer, uint16_t wLength, size_t *transferred);

/**
 * Schedules a bulk transfer and waits for it to complete.
 * @param device The device to communicate with.
 * @param endpoint Address of the bulk endpoint to communicate with.
 * Bit 7 specifies the direction of the transfer.
 * @param buffer Data to transfer that must reside in RAM.
 * @param length The number of bytes to transfer.
 * The \p buffer must be at least this large.
 * @param transferred Returns the number of bytes actually transferred.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_BulkTransfer(usb_device_t device, uint8_t endpoint, void *buffer, size_t length, size_t *transferred);

/**
 * Schedules an interrupt transfer and waits for it to complete.
 * @param device The device to communicate with.
 * @param endpoint Address of the interrupt endpoint to communicate with.
 * Bit 7 specifies the direction of the transfer.
 * @param buffer Data to transfer that must reside in RAM.
 * @param length The number of bytes to transfer.
 * The \p buffer must be at least this large.
 * @param transferred Returns the number of bytes actually transferred.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_InterruptTransfer(usb_device_t device, uint8_t endpoint, void *buffer, size_t length, size_t *transferred);

/**
 * Schedules an isochronous transfer and waits for it to complete.
 * @param device The device to communicate with.
 * @param endpoint Address of the isochronous endpoint to communicate with.
 * Bit 7 specifies the direction of the transfer.
 * @param buffer Data to transfer that must reside in RAM.
 * @param length The number of bytes to transfer.
 * The \p buffer must be at least this large.
 * @param transferred Returns the number of bytes actually transferred.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_IsochronousTransfer(usb_device_t device, uint8_t endpoint, void *buffer, size_t length, size_t *transferred);

/**
 * Schedules a transfer.
 * @param device The device to communicate with.
 * @param endpoint Address of endpoint to communicate with.
 * Bit 7 is ignored for control transfers, and the direction of other transfers.
 * @param type Type of the endpoint and transfer.
 * @param buffer Data to transfer that must reside in RAM.
 * This buffer must remain valid until the callback is called i.e. it cannot be modified or freed.
 * For control transfers, the setup packet occupies the first 8 bytes of the buffer regardless of the direction of transfer, and should not be included in the setup packet's wLength field, and the \p length parameter is ignored.
 * @param length Number of bytes to transfer.
 * The \p buffer must be at least this large.
 * However, this is ignored for control transfers
 * @param transferred Returns the number of bytes actually transferred.
 * @param handler Function to be called when the transfer finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS if the transfer was scheduled or an error.
 */
usb_error_t usb_ScheduleTransfer(usb_device_t device, uint8_t endpoint, usb_transfer_type_t type, void *buffer, size_t length, transfer_callback_t handler, void *data);

#ifdef __cplusplus
}
#endif

#endif
