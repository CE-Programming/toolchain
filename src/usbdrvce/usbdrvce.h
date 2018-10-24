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
  USB_USE_C_HEAP         = 1 << 0, /**< Use part of the default C heap.
                                        @warning Do not use this unless you
                                        changed your program's bss/heap to end
                                        at 0xD10000! */
  USB_USE_PERIODIC_LIST  = 1 << 1, /**< Use space normally used for periodic.
                                        @warning This disables support for
                                        interrupt transfers, isochronous
                                        transfers, and hubs! */
  USB_USE_USB_AREA       = 1 << 2, /**< Use the memory that TIOS uses for usb. */
  USB_USE_OS_HEAP        = 1 << 3, /**< Use the application heap area. */
  USB_DEFAULT_INIT_FLAGS = USB_USE_USB_AREA | USB_USE_OS_HEAP,
} usb_init_flags_t;

typedef enum usb_device_event {
  USB_DEVICE_DISCONNECTED,
  USB_DEVICE_CONNECTED,
  USB_DEVICE_DISABLED,
  USB_DEVICE_ENABLED,
  USB_DEVICE_OVERCURRENT_DEACTIVATED,
  USB_DEVICE_OVERCURRENT_ACTIVATED,
  USB_DEVICE_DEFAULT_SETUP,
} usb_device_event_t;

typedef enum usb_error {
  USB_SUCCESS,
  USB_IGNORE,
  USB_ERROR_UNINITIALIZED,
  USB_ERROR_INVALID_PARAM,
  USB_ERROR_SCHEDULE_FULL,
  USB_ERROR_NO_DEVICE,
  USB_ERROR_NO_MEMORY,
  USB_ERROR_NOT_SUPPORTED,
  USB_ERROR_TIMEOUT,
  USB_USER_ERROR = 100,
} usb_error_t;

typedef enum usb_find_flags {
  USB_FIND_DISABLED = 1 << 0, /**< Only return disabled devices. */
  USB_FIND_ENABLED  = 1 << 1, /**< Only return enabled devices. */
  USB_FIND_DEVICE   = 1 << 2, /**< Only return non-hubs. */
  USB_FIND_HUB      = 1 << 3, /**< Only return hubs. */
  USB_FIND_DIRECT   = 1 << 4, /**< Only return devices directly attached to the
                                   specified \p root hub. */
} usb_find_flags_t;

typedef enum usb_speed {
  USB_SPEED_UNKNOWN = -1,
  USB_SPEED_FULL,
  USB_SPEED_LOW,
  USB_SPEED_HIGH,
  USB_SPEED_SUPER,
} usb_speed_t;

typedef enum usb_transfer_type {
  USB_UNUSED_ENDPOINT = -1,
  USB_CONTROL_TRANSFER,
  USB_ISOCHRONOUS_TRANSFER,
  USB_BULK_TRANSFER,
  USB_INTERRUPT_TRANSFER,
} usb_transfer_type_t;

typedef enum usb_transfer_status {
  USB_TRANSFER_COMPLETED,      /**< Transfered successfully. @note A receive
                                    transfer will complete when the end of a
                                    packet is detected, or the buffer is filled,
                                    whichever happens first. */
  USB_TRANSFER_STALLED,        /**< Endpoint halt condition detected or control
                                    request not supported. */
  USB_TRANSFER_FAILED,         /**< Transfer failed due to timout and/or
                                    corruption. */
  USB_TRANSFER_MEMORY_ERROR,   /**< Memory could not be accessed in a timely
                                    enough fashion to complete the transfer.
                                    @note This usually means you changed the cpu
                                    speed or lcd parameters or something. */
  USB_TRANSFER_OVERFLOW_ERROR, /**< Device sent more bytes than can be stored in
                                    the transfer buffer, and were therefore
                                    lost. @note This can be avoided be making
                                    sure receive buffer lengths are always a
                                    multiple of the endpoint's maximum packet
                                    length. */
  USB_TRANSFER_HOST_ERROR,     /**< The results of the transaction were missed
                                    due to host hold-off. @note This usually
                                    indicates a bug in this library. */
  USB_TRANSFER_NO_DEVICE,      /**< The device was disconnected. */
} usb_transfer_status_t;

typedef struct usb_control_setup {
  uint8_t bmRequestType, bRequest;
  uint16_t wValue, wIndex, wLength;
} usb_control_setup_t;

typedef struct usb_device *usb_device_t; /**< opaque handle for a device */

#define USB_RETRY_FOREVER 0xFFFFFFu

#define usb_RootHub ((usb_device_t)0xD13FC0)

/**
 * Type of the function to be called when a usb device event occurs.
 * @param device Handle for the device where the event originated.
 * @param data Opaque pointer passed to usb_Init().
 * @return Return USB_SUCCESS to initialize the device, USB_IGNORE to ignore it
 * without erroring, or an error to ignore the device and to return from
 * usb_ProcessEvents().
 */
typedef usb_error_t (*usb_device_event_callback_t)(usb_device_t device,
                                                   void *data,
                                                   usb_device_event_t event);

/**
 * Type of the function to be called when a transfer finishes.
 * @param device The device that was communicated with.
 * @param endpoint Endpoint communicated with, ored with hshb_index << 5.
 * @param status Status of the transfer.
 * @param data Opaque pointer passed to usb_ScheduleTransfer().
 * @param transferred The number of bytes transferred.
 * Only valid if \p status was USB_TRANSFER_COMPLETED.
 * @return Return USB_SUCCESS to free the transfer, USB_IGNORE to restart it,
 * or an error to free it and to return from usb_ProcessEvents().
 */
typedef usb_error_t (*usb_transfer_callback_t)(usb_device_t device,
                                               uint8_t endpoint,
                                               usb_transfer_status_t status,
                                               size_t transferred, void *data);

/**
 * Initializes the usb driver.
 * @param event_handler Function to be called when a usb event happens.
 * @param event_data Opaque pointer to be passed to the \p event_handler.
 * @param flags Which areas of memory to use.
 * @return USB_SUCCESS if initialization succeeded.
 * @note This must be called before any other function, and can be called again
 * to cancel all transfers and close all connections.
 */
usb_error_t usb_Init(usb_device_event_callback_t event_handler,
                     void *event_data, usb_init_flags_t flags);

/**
 * Uninitializes the usb driver.
 * @note This must be called before the program exits, or TIOS gets angry.
 */
void usb_Cleanup(void);

/**
 * Sets the descriptors to use when connected to a host.  If this is not called
 * before a call to usb_connect_callback_t with (flags & USB_CONNECTED_TO_HOST)
 * returns, or is called with NULL, then the default calculator device
 * descriptors will be used.  In a passed array, the first entry points to a
 * device descriptor, and the rest to each configuration descriptor.  If the
 * first entry is NULL, then that speed is disabled.  The arrays just need
 * to be readable, but the descriptors themselves must be in RAM.
 * @param descriptors An array of pointers to descriptors, pointer to NULL for
 * disabled, or NULL for default.
 */
void usb_SetDeviceDescriptors(void **full_speed_descriptors,
                              void **high_speed_descriptors);

/**
 * Finds the next device connected through \p root after \p from satisfying
 * flags.
 * @param root Hub below which to limit search.
 * @param from Device to start the search from.
 * @param flags What kinds of devices to return.
 * @return The first matching device under \p root and after \p from, or NULL if
 *         no more matching devices.
 */
usb_device_t usb_FindDevice(usb_device_t root, usb_device_t from,
                            usb_find_flags_t flags);

/**
 * Finds the first device satisfying flags.
 * @param flags What kinds of devices to return.
 * @return The first matching device, or NULL if no more matching devices.
 */
#define usb_FindFirstDevice(flags)\
  usb_FindDevice(usb_RootHub, usb_RootHub, flags)

/**
 * Finds the next device after \p from satisfying flags.
 * @param from Device to start the search from.
 * @param flags What kinds of devices to return.
 * @return The first matching device after \p from, or NULL if no matching
 * devices.
 */
#define usb_FindNextDevice(flags, from)\
  usb_FindDevice(usb_RootHub, from, flags)

/**
 * @param device Device to get the hub of.
 * @return The hub that \pdevice is attached to.
 */
usb_device_t usb_DeviceHub(usb_device_t device);

/**
 * Calls any triggered device or transfer callbacks.
 * @return An error returned by a callback or USB_SUCCESS.
 */
usb_error_t usb_ProcessEvents(void);

/**
 * Clears an endpoint's halt/stall condition.
 * @param device The device to communicate with.
 * @param endpoint The endpoint to communicate with.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ClearHalt(usb_device_t device, uint8_t endpoint);

/**
 * Performs a usb reset on a device. This causes a device to become enabled.
 * @param device The device to communicate with.
 * @param endpoint The endpoint to communicate with.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ResetDevice(usb_device_t device);

/**
 * Gets a device's address.
 * @param device The device to communicate with.
 * @return The usb address of \p device, or 0 if disabled.
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
uint16_t usb_GetMaxPacketSize(usb_device_t device, uint8_t endpoint);

/**
 * Gets the transfer type of an endpoint.
 * @param device The device to communicate with.
 * @param endpoint The endpoint to communicate with.
 * @return The endpoint's transfer type or USB_UNUSED_ENDPOINT.
 */
usb_transfer_type_t usb_GetTransferType(usb_device_t device, uint8_t endpoint);

/**
 * Determines how large of a buffer would be required to receive the complete
 * configuration descriptor at \p index.
 * @param device The device to communicate with.
 * @param index Which configuration descriptor to query.
 * @param total_length Returns the number of bytes in the complete configuration
 * descriptor.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetConfigurationDescriptorTotalLength(usb_device_t device,
                                                      uint8_t index,
                                                      size_t *total_length);

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
usb_error_t usb_GetDescriptor(usb_device_t device, uint8_t type, uint8_t index,
                              void *descriptor, size_t length,
                              size_t *transferred);

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
usb_error_t usb_SetDescriptor(usb_device_t device, uint8_t type, uint8_t index,
                              void *descriptor, size_t length);

/**
 * Gets the currently active configuration of a device.
 * @param device The device to communicate with.
 * @param index Returns the current configuration value, or 0 if unconfigured.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetConfiguration(usb_device_t device, uint8_t *index);

/**
 * Selects the configuration specified by the \p configuration_descriptor.
 * This must be called before pipes other than the default control pipe can be
 * accessed.
 * @param device The device to communicate with.
 * @param configuration_descriptor A complete configuration descriptor fetched
 * with usb_GetDescriptor().
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetConfiguration(usb_device_t device,
                                 void *configuration_descriptor);

/**
 * Gets the current alternate setting in use on the specified interface.
 * @param device The device to communicate with.
 * @param interface Interface index to query.
 * @param alternate_setting Returns the alternate setting in use.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetInterfaceAltSetting(usb_device_t device, uint8_t interface,
                                       uint8_t *alternate_setting);

/**
 * Sets the alternate setting in use on the specified interface.
 * @param device The device to communicate with.
 * @param interface Interface index to modify.
 * @param alternate_setting Alternate setting to use.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetInterfaceAltSetting(usb_device_t device, uint8_t interface,
                                       uint8_t alternate_setting);

/**
 * Schedules a transfer to the pipe connected to \p endpoint of \p device, in
 * the direction indicated by \p setup->bmRequestType, using \p buffer as the
 * data buffer, \p setup->wLength as the buffer length, and then waits for it to
 * complete.  If acting as usb host and using a control pipe, \p setup is used
 * as the setup packet, otherwise all fields not mentioned above are ignored.
 * @param device The device to communicate with.
 * @param endpoint Address of the endpoint to communicate with. Bit 7 is
 * ignored.
 * @param setup Indicates the transfer direction and buffer length.  If acting
 * as usb host and using a control pipe, also used as the setup packet to send.
 * @param buffer Data to transfer that must reside in RAM and have room for at
 * least \p setup->wLength bytes.
 * @param retries How many times to retry the transfer before timing out.
 * If retries is USB_RETRY_FOREVER, the transfer never times out.
 * @param transferred Returns the number of bytes actually transferred.
 * If \p transferred is NULL then nothing is returned.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ControlTransfer(usb_device_t device, uint8_t endpoint,
                                usb_control_setup_t *setup, void *buffer,
                                unsigned retries, size_t *transferred);

/**
 * Schedules a control transfer to the default control pipe of \p device, in the
 * direction indicated by \p setup->bmRequestType, using \p buffer as the data
 * buffer, \p setup->wLength as the buffer length, and then waits for it to
 * complete.  If acting as usb host, \p setup is used as the setup packet,
 * otherwise all fields not mentioned above are ignored.
 * @param device The device to communicate with.
 * @param setup Indicates the transfer direction and buffer length.  If acting
 * as usb host, also used as the setup packet to send.
 * @param buffer Data to transfer that must reside in RAM and be at least
 * setup->wLength bytes.
 * @param retries How many times to retry the transfer before timing out.
 * If retries is USB_RETRY_FOREVER, the transfer never times out.
 * @param transferred Returns the number of bytes actually transferred.
 * NULL means don't return anything.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
#define usb_DefaultControlTransfer(device, setup, buffer, retries, transferred)\
  usb_ControlTransfer(device, 0, setup, buffer, retries, transferred)

/**
 * Schedules a transfer to the pipe connected to \p endpoint of \p device, using
 * \p length as the buffer length, and waits for it to complete. If acting as
 * usb host and using a control pipe, uses the beginning of \p buffer as the
 * setup packet to send, its \c bmRequestType for the transfer direction, and
 * the rest of \p buffer as the data buffer.  Otherwise, uses \p endpoint for
 * transfer direction and  the whole \p buffer as the data buffer.
 * @param device The device to communicate with.
 * @param endpoint Address of the endpoint to communicate with. Bit 7 indicates
 * the transfer direction for non-control transfers.
 * @param buffer Data to transfer that must reside in RAM.  When acting as usb
 * host and using a control pipe, starts with a \c usb_control_setup_t.
 * @param length Number of bytes to transfer.  The \p buffer must be at least
 * this large.  However, this is ignored for control transfers when acting as
 * usb host where the \c wLength of the setup packet is used instead.
 * @param retries How many times to retry the transfer before timing out.
 * If retries is USB_RETRY_FOREVER, the transfer never times out.
 * @param transferred Returns the number of bytes actually transferred.
 * NULL means don't return anything.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_Transfer(usb_device_t device, uint8_t endpoint, void *buffer,
                         size_t length, unsigned retries, size_t *transferred);
#define usb_BulkTransfer usb_Transfer
#define usb_InterruptTransfer usb_Transfer
#define usb_IsochronousTransfer usb_Transfer

/**
 * Schedules a transfer to the pipe connected to \p endpoint of \p device, in
 * the direction indicated by \p setup->bmRequestType, using \p buffer as the
 * data buffer, and \p setup->wLength as the buffer length.  If acting as usb
 * host and using a control pipe, \p setup is used as the setup packet,
 * otherwise all fields not mentioned above are ignored.
 * @param device The device to communicate with.
 * @param endpoint Address of endpoint to communicate with.  Bit 7 indicates the
 * transfer direction for non-control transfers.
 * @param setup Indicates the transfer direction and buffer length.  If acting
 * as usb host and using a control pipe, also used as the setup packet to send.
 * @param buffer Data to transfer that must reside in RAM.  This buffer must
 * remain valid until the callback is called i.e. it cannot be modified or
 * freed.
 * @param transferred Returns the number of bytes actually transferred.
 * @param handler Function to be called when the transfer finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS if the transfer was scheduled or an error.
 */
usb_error_t usb_ScheduleControlTransfer(usb_device_t device, uint8_t endpoint,
                                        usb_control_setup_t *setup,
                                        void *buffer,
                                        usb_transfer_callback_t handler,
                                        void *data);

/**
 * Schedules a control transfer to the default control pipe of \p device, in
 * the direction indicated by \p setup->bmRequestType, using \p buffer as the
 * data buffer, and \p setup->wLength as the buffer length.  If acting as usb
 * host, \p setup is used as the setup packet, otherwise all fields not
 * mentioned above are ignored.
 * @param device The device to communicate with.
 * @param setup Indicates the transfer direction and buffer length.  If acting
 * as usb host, also used as the setup packet to send.
 * @param buffer Data to transfer that must reside in RAM.  This buffer must
 * remain valid until the callback is called i.e. it cannot be modified or
 * freed.
 * @param transferred Returns the number of bytes actually transferred.
 * @param handler Function to be called when the transfer finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS if the transfer was scheduled or an error.
 */
#define usb_ScheduleDefaultControlTransfer(device, setup, buffer, handler, data)\
  usb_ScheduleControlTransfer(device, 0, setup, buffer, handler, data)

/**
 * If endpoint is not a control endpoint, schedules a transfer of the endpoint's
 * transfer type.  If the endpoint is a control endpoint, schedules a control
 * transfer interpreting the beginning of buffer as the \c usb_control_setup_t
 * and using the rest of the buffer as the transfer buffer.
 * @param device The device to communicate with.
 * @param endpoint Address of endpoint to communicate with.
 * Bit 7 is ignored for control transfers, and the direction of other transfers.
 * @param type Type of the endpoint and transfer.
 * @param buffer Data to transfer that must reside in RAM.  When acting as usb
 * host and using a control pipe, starts with a \c usb_control_setup_t.  This
 * buffer must remain valid until the callback is called i.e. it cannot be
 * modified or freed.
 * @param length Number of bytes to transfer.  The \p buffer must be at least
 * this large.  However, this is ignored for control transfers when acting as
 * usb host where the \c wLength of the setup packet is used instead.
 * @param transferred Returns the number of bytes actually transferred.
 * @param handler Function to be called when the transfer finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS if the transfer was scheduled or an error.
 */
usb_error_t usb_ScheduleTransfer(usb_device_t device, uint8_t endpoint,
                                 void *buffer, size_t length,
                                 usb_transfer_callback_t handler, void *data);
#define usb_ScheduleBulkTransfer usb_ScheduleTransfer
#define usb_ScheduleInterruptTransfer usb_ScheduleTransfer
#define usb_ScheduleIsochronousTransfer usb_ScheduleTransfer

#ifdef __cplusplus
}
#endif

#endif
