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

typedef enum usb_event {
  /// \p event_data Pointer to the new usb_role_t state.
  USB_ROLE_CHANGED_EVENT,
  /// \p event_data The usb_device_t that was disconnected.
  USB_DEVICE_DISCONNECTED_EVENT,
  /// \p event_data The usb_device_t that was connected.
  USB_DEVICE_CONNECTED_EVENT,
  /// \p event_data The usb_device_t that was disabled.
  USB_DEVICE_DISABLED_EVENT,
  /// \p event_data The usb_device_t that was enabled.
  USB_DEVICE_ENABLED_EVENT,
  /// \p event_data The usb_device_t that deactivated overcurrent condition.
  USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT,
  /// \p event_data The usb_device_t that activated overcurrent condition.
  USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT,
  /// This event triggers when a host sends a control setup packet.  Standard
  /// requests are handled internally and do not trigger an event.  Return
  /// USB_SUCCESS if you recognized the request and scheduled a corresponding
  /// transfer, otherwise return USB_IGNORE to stall.
  /// \p event_data The usb_control_setup_t * that was sent by the host.
  USB_DEFAULT_SETUP_EVENT,
  // Temp debug events:
  USB_DEVICE_INTERRUPT,
  USB_DEVICE_CONTROL_INTERRUPT,
  USB_DEVICE_FIFO_INTERRUPT,
  USB_DEVICE_DEVICE_INTERRUPT,
  USB_OTG_INTERRUPT,
  USB_HOST_INTERRUPT,
  USB_CONTROL_INPUT_INTERRUPT,
  USB_CONTROL_OUTPUT_INTERRUPT,
  USB_CONTROL_END_INTERRUPT,
  USB_CONTROL_ERROR_INTERRUPT,
  USB_CONTROL_ABORT_INTERRUPT,
  USB_FIFO0_INPUT_INTERRUPT,
  USB_FIFO0_OUTPUT_INTERRUPT,
  USB_FIFO0_SHORT_PACKET_INTERRUPT,
  USB_FIFO1_INPUT_INTERRUPT,
  USB_FIFO1_OUTPUT_INTERRUPT,
  USB_FIFO1_SHORT_PACKET_INTERRUPT,
  USB_FIFO2_INPUT_INTERRUPT,
  USB_FIFO2_OUTPUT_INTERRUPT,
  USB_FIFO2_SHORT_PACKET_INTERRUPT,
  USB_FIFO3_INPUT_INTERRUPT,
  USB_FIFO3_OUTPUT_INTERRUPT,
  USB_FIFO3_SHORT_PACKET_INTERRUPT,
  USB_DEVICE_RESET_INTERRUPT,
  USB_DEVICE_SUSPEND_INTERRUPT,
  USB_DEVICE_RESUME_INTERRUPT,
  USB_DEVICE_ISOCHRONOUS_ERROR_INTERRUPT,
  USB_DEVICE_ISOCHRONOUS_ABORT_INTERRUPT,
  USB_DEVICE_ZERO_LENGTH_PACKET_TRANSMIT_INTERRUPT,
  USB_DEVICE_ZERO_LENGTH_PACKET_RECEIVE_INTERRUPT,
  USB_DEVICE_DMA_FINISH_INTERRUPT,
  USB_DEVICE_DMA_ERROR_INTERRUPT,
  USB_DEVICE_IDLE_INTERRUPT,
  USB_DEVICE_WAKEUP_INTERRUPT,
  USB_B_SRP_COMPLETE_INTERRUPT,
  USB_A_SRP_DETECT_INTERRUPT,
  USB_A_VBUS_ERROR_INTERRUPT,
  USB_B_SESSION_END_INTERRUPT,
  USB_OVERCURRENT_INTERRUPT,
  USB_B_PLUG_REMOVED_INTERRUPT,
  USB_A_PLUG_REMOVED_INTERRUPT,
  USB_INTERRUPT,
  USB_HOST_ERROR_INTERRUPT,
  USB_HOST_PORT_CONNECT_STATUS_CHANGE_INTERRUPT,
  USB_HOST_PORT_ENABLE_DISABLE_CHANGE_INTERRUPT,
  USB_HOST_PORT_OVERCURRENT_CHANGE_INTERRUPT,
  USB_HOST_PORT_FORCE_PORT_RESUME_INTERRUPT,
  USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT,
  USB_HOST_SYSTEM_ERROR_INTERRUPT,
  USB_HOST_ASYNC_ADVANCE_INTERRUPT,
} usb_event_t;

typedef enum usb_error {
  USB_SUCCESS,
  USB_IGNORE,
  USB_ERROR_SYSTEM,
  USB_ERROR_INVALID_PARAM,
  USB_ERROR_SCHEDULE_FULL,
  USB_ERROR_NO_DEVICE,
  USB_ERROR_NO_MEMORY,
  USB_ERROR_NOT_SUPPORTED,
  USB_ERROR_TIMEOUT,
  USB_ERROR_FAILED,
  USB_USER_ERROR = 100,
} usb_error_t;

typedef enum usb_transfer_status {
  USB_TRANSFER_COMPLETED,    /**< Transfered successfully. @note A receive    */
                             /**  transfer will complete when the end of a    */
                             /**  packet is detected, or the buffer is        */
                             /**  filled, whichever happens first.            */
  USB_TRANSFER_ERROR,        /**< Transfer failed due to timout and/or        */
                             /**  corruption.                                 */
  USB_TRANSFER_TIMED_OUT,    /**< Max retry attempts exceeded.                */
  USB_TRANSFER_STALL,        /**< Endpoint halt condition detected or control */
                             /**  request not supported.                      */
  USB_TRANSFER_NO_DEVICE,    /**< The device was disconnected.                */
  USB_TRANSFER_OVERFLOW,     /**< Device sent more bytes than can be stored   */
                             /**  in the transfer buffer, and were therefore  */
                             /**  lost. @note This can be avoided by ensuring */
                             /**  that receive buffer lengths are always a    */
                             /**  multiple of the endpoint's maximum packet   */
                             /**  length.                                     */
  USB_TRANSFER_MEMORY_ERROR, /**< Memory could not be accessed in a timely    */
                             /**  enough fashion to complete the transfer.    */
                             /**  @note This probably means that non-default  */
                             /**  cpu speed or lcd parameters are in use.     */
  USB_TRANSFER_HOST_ERROR,   /**< The results of the transaction were         */
                             /**  missed due to host hold-off. @note This     */
                             /**  probably indicates a bug in this library.   */
} usb_transfer_status_t;

typedef enum usb_find_flag {
  USB_SKIP_NONE     = 0,      /**< Return all devices                         */
  USB_SKIP_DISABLED = 1 << 0, /**< Don't return disabled devices.             */
  USB_SKIP_ENABLED  = 1 << 1, /**< Don't return enabled devices.              */
  USB_SKIP_DEVICES  = 1 << 2, /**< Don't return non-hubs.                     */
  USB_SKIP_HUBS     = 1 << 3, /**< Don't return hubs.                         */
  USB_SKIP_ATTACHED = 1 << 4, /**< Only return devices directly attached to   */
                              /**  any of the hubs through which \c from is   */
                              /**  connected.  This skips recursing over      */
                              /**  devices attached to other hubs.            */
} usb_find_flag_t;

typedef enum usb_endpoint_flag {
  USB_MANUAL_TERMINATE = 0 << 0, /**< For transfers that are a multiple of    */
                                 /**  the endpoint's maximum packet length,   */
                                 /**  don't automatically terminate outgoing  */
                                 /**  ones with a zero-length packet and      */
                                 /**  don't require incoming ones to be       */
                                 /**  terminated with a zero-length packet.   */
                                 /**  @note This allows you to send or        */
                                 /**  receive partial transfers in multiples  */
                                 /**  of the endpoint's maximum packet        */
                                 /**  length, but requires that transfers     */
                                 /**  which are a multiple of the endpoint's  */
                                 /**  maximum packet length to be manually    */
                                 /**  terminated with an explicit zero-length */
                                 /**  transfer.                               */
  USB_AUTO_TERMINATE   = 1 << 0, /**< For transfers that are a multiple of    */
                                 /**  the endpoint's maximum packet length,   */
                                 /**  automatically terminate outgoing ones   */
                                 /**  with a zero-length packet and require   */
                                 /**  incoming ones to be terminated with a   */
                                 /**  zero-length packet or fail with         */
                                 /**  USB_TRANSFER_OVERFLOW.                  */
} usb_endpoint_flag_t;

typedef enum usb_role {
  USB_ROLE_HOST   = 0 << 4, /**< Acting as usb host.   */
  USB_ROLE_DEVICE = 1 << 4, /**< Acting as usb device. */
  USB_ROLE_A      = 0 << 5, /**< Plug A plugged in.    */
  USB_ROLE_B      = 1 << 5, /**< Plug B plugged in.    */
} usb_role_t;

typedef enum usb_speed {
  USB_SPEED_UNKNOWN = -1,
  USB_SPEED_FULL, /**<  12 Mb/s */
  USB_SPEED_LOW,  /**< 1.5 Mb/s */
} usb_speed_t;

typedef enum usb_transfer_direction {
  USB_HOST_TO_DEVICE = 0 << 7,
  USB_DEVICE_TO_HOST = 1 << 7,
} usb_transfer_direction_t;

typedef enum usb_request_type {
  USB_STANDARD_REQUEST = 0 << 5,
  USB_CLASS_REQUEST    = 1 << 5,
  USB_VENDOR_REQUEST   = 2 << 5,
} usb_request_type_t;

typedef enum usb_recipient {
  USB_RECIPIENT_DEVICE,
  USB_RECIPIENT_INTERFACE,
  USB_RECIPIENT_ENDPOINT,
  USB_RECIPIENT_OTHER,
} usb_recipient_t;

typedef enum usb_request {
  USB_GET_STATUS,
  USB_CLEAR_FEATURE,
  USB_SET_FEATURE = 3,
  USB_SET_ADDRESS = 5,
  USB_GET_DESCRIPTOR,
  USB_SET_DESCRIPTOR,
  USB_GET_CONFIGURATION,
  USB_SET_CONFIGURATION,
  USB_GET_INTERFACE,
  USB_SET_INTERFACE,
  USB_SYNC_FRAME,
} usb_request_t;

typedef enum usb_descriptor_type {
  USB_DEVICE_DESCRIPTOR = 1,
  USB_CONFIGURATION_DESCRIPTOR,
  USB_STRING_DESCRIPTOR,
  USB_INTERFACE_DESCRIPTOR,
  USB_ENDPOINT_DESCRIPTOR,
} usb_descriptor_type_t;

typedef enum usb_class {
  USB_INTERFACE_SPECIFIC_CLASS,
  USB_AUDIO_CLASS,
  USB_COMM_CLASS,
  USB_HID_CLASS,
  USB_PHYSICAL_CLASS = 5,
  USB_IMAGE_CLASS,
  USB_PRINTER_CLASS,
  USB_STORAGE_CLASS,
  USB_HUB_CLASS,
  USB_CDC_DATA_CLASS,
  USB_SMART_CARD_CLASS,
  USB_CONTENT_SECURITY_CLASS,
  USB_VIDEO_CLASS,
  USB_PERSONAL_HEALTCARE_CLASS,
  USB_AUDIO_VIDEO_CLASS,
  USB_BILLBOARD_CLASS,
  USB_TYPE_C_BRIDGE_CLASS,
  USB_DIAGNOSTIC_DEVICE_CLASS = 0xDC,
  USB_WIRELESS_CONTROLLER_CLASS = 0xE0,
  USB_MISCELLANEOUS_CLASS = 0xEF,
  USB_APPLICATION_SPECIFIC_CLASS = 0xFE,
  USB_VENDOR_SPECIFIC_CLASS = 0xFF,
} usb_class_t;

typedef enum usb_configuration_attributes {
  USB_NO_REMOTE_WAKEUP         = 0 << 5,
  USB_REMOTE_WAKEUP            = 1 << 5,
  USB_BUS_POWERED              = 0 << 6,
  USB_SELF_POWERED             = 1 << 6,
  USB_CONFIGURATION_ATTRIBUTES = 1 << 7,
} usb_configuration_attributes_t;

typedef enum usb_usage_type {
  USB_DATA_ENDPOINT                   = 0 << 4,
  USB_FEEDBACK_ENDPOINT               = 1 << 4,
  USB_IMPLICIT_FEEDBACK_DATA_ENDPOINT = 2 << 4,
} usb_usage_type_t;

typedef enum usb_synchronization_type {
  USB_NO_SYNCHRONIZATION = 0 << 2,
  USB_ASYNCHRONOUS       = 1 << 2,
  USB_ADAPTIVE           = 2 << 2,
  USB_SYNCHRONOUS        = 3 << 2,
} usb_synchronization_type_t;

typedef enum usb_transfer_type {
  USB_CONTROL_TRANSFER,
  USB_ISOCHRONOUS_TRANSFER,
  USB_BULK_TRANSFER,
  USB_INTERRUPT_TRANSFER,
} usb_transfer_type_t;

typedef struct usb_control_setup {
  uint8_t  bmRequestType;       /**< direction, type, and recipient           */
  uint8_t  bRequest;            /**< usb_request_t                            */
  uint16_t wValue;              /**< request specific                         */
  uint16_t wIndex;              /**< request specific                         */
  uint16_t wLength;             /**< transfer length                          */
} usb_control_setup_t;

typedef struct usb_descriptor {
  uint8_t  bLength;             /**< The length of this descriptor.           */
  uint8_t  bDescriptorType;     /**< A usb_descriptor_type_t.                 */
  uint8_t  data[1];             /**< The rest of the descriptor               */
} usb_descriptor_t;

typedef struct usb_device_descriptor {
  uint8_t  bLength;             /**< 18                                       */
  uint8_t  bDescriptorType;     /**< USB_DEVICE_DESCRIPTOR                    */
  uint16_t bcdUSB;              /**< usb specification version                */
  uint8_t  bDeviceClass;        /**< usb_class_t                              */
  uint8_t  bDeviceSubClass;     /**< usb class specific                       */
  uint8_t  bDeviceProtocol;     /**< usb class specific                       */
  uint8_t  bMaxPacketSize0;     /**< 8, 16, 32, or 64                         */
  uint16_t idVendor;            /**< usb assigned vendor id                   */
  uint16_t idProduct;           /**< usb assigned product id                  */
  uint16_t bcdDevice;           /**< device version                           */
  uint8_t  iManufacturer;       /**< index of manufacturer string descriptor  */
  uint8_t  iProduct;            /**< index of product string descriptor       */
  uint8_t  iSerialNumber;       /**< index of serial number string descriptor */
  uint8_t  bNumConfigurations;  /**< how many valid configuration indices     */
} usb_device_descriptor_t;

typedef struct usb_device_qualifier_descriptor {
  uint8_t  bLength;             /**< 10                                       */
  uint8_t  bDescriptorType;     /**< USB_DEVICE_QUALIFIER_DESCRIPTOR          */
  uint16_t bcdUSB;              /**< usb specification version                */
  uint8_t  bDeviceClass;        /**< usb_class_t                              */
  uint8_t  bDeviceSubClass;     /**< usb class specific                       */
  uint8_t  bDeviceProtocol;     /**< usb class specific                       */
  uint8_t  bMaxPacketSize0;     /**< 8, 16, 32, or 64                         */
  uint8_t  bNumConfigurations;  /**< how many valid configuration indices     */
  uint8_t  bReserved;           /**< must be 0                                */
} usb_device_qualifier_descriptor_t;

typedef struct usb_configuration_descriptor {
  uint8_t  bLength;             /**< 9                                        */
  uint8_t  bDescriptorType;     /**< USB_CONFIGURATION_DESCRIPTOR             */
  uint16_t wTotalLength;        /**< total length of combined descriptors     */
  uint8_t  bNumInterfaces;      /**< how many interface descriptors follow    */
  uint8_t  bConfigurationValue; /**< value used to select this configuration  */
  uint8_t  iConfiguration;      /**< index of description string descriptor   */
  uint8_t  bmAttributes;        /**< usb_configuration_attributes_t           */
  uint8_t  bMaxPower;           /**< units of 2mA                             */
} usb_configuration_descriptor_t;
typedef struct usb_configuration_descriptor usb_other_speed_configuration_t;

typedef struct usb_interface_descriptor {
  uint8_t  bLength;             /**< 9                                        */
  uint8_t  bDescriptorType;     /**< USB_INTERFACE_DESCRIPTOR                 */
  uint8_t  bInterfaceNumber;    /**< zero-based interface index               */
  uint8_t  bAlternateSetting;   /**< value used to select this alt setting    */
  uint8_t  bNumEndpoints;       /**< how many endpoint descriptors follow     */
  uint8_t  bInterfaceClass;     /**< usb_class_t                              */
  uint8_t  bInterfaceSubClass;  /**< usb class specific                       */
  uint8_t  bInterfaceProtocol;  /**< usb class specific                       */
  uint8_t  iInterface;          /**< index of description string descriptor   */
} usb_interface_descriptor_t;

typedef struct usb_endpoint_descriptor {
  uint8_t  bLength;             /**< 7                                        */
  uint8_t  bDescriptorType;     /**< USB_ENDPOINT_DESCRIPTOR                  */
  uint8_t  bEndpointAddress;    /**< endpoint direction and number            */
  uint8_t  bmAttributes;        /**< usb_usage_type_t |                       */
                                /**  usb_synchronization_type_t |             */
                                /**  usb_transfer_type_t                      */
  uint16_t wMaxPacketSize;      /**  transfer type specific                   */
  uint8_t  bInterval;           /**  transfer type specific                   */
} usb_endpoint_descriptor_t;

typedef struct usb_string_descriptor {
  uint8_t  bLength;             /**< byte length, not character length        */
  uint8_t  bDescriptorType;     /**< USB_STRING_DESCRIPTOR                    */
  wchar_t  bString[1];          /**< UTF-16 string, no null termination       */
} usb_string_descriptor_t;

typedef struct usb_standard_descriptors {
  /// Pointer to device descriptor which must be in RAM
  usb_device_descriptor_t *device;
  /// Pointer to array of device->bNumConfigurations pointers to complete
  /// configuration descriptors. Each one should point to
  /// \c{(*configurations)[i]->wTotalLength} bytes of RAM.
  usb_configuration_descriptor_t **configurations;
  /// Pointer to array of langids, formatted like a string descriptor, with each
  /// wchar_t containing a langid, and which must be in RAM.
  usb_string_descriptor_t *langids;
  /// Number of strings per langid.
  uint8_t numStrings;
  /// Pointer to array of \c{numStrings * (langids->bLength / 2 - 1)} pointers
  /// to string descriptors, each of which must be in RAM, starting with
  /// numStrings pointers for the first langid, then for the next langid, etc.
  usb_string_descriptor_t **strings;
} usb_standard_descriptors_t;

typedef struct usb_device   *usb_device_t;   /**< opaque  device  handle */
typedef struct usb_endpoint *usb_endpoint_t; /**< opaque endpoint handle */

#define USB_RETRY_FOREVER 0xFFFFFFu

#define usb_RootHub() ((usb_device_t)0xD13FC0u) /**< Root hub device */

/**
 * A pointer to \c usb_callback_data_t is passed to the \c usb_event_callback_t.
 * The default is void *, but this can be changed by doing:
 * \code
 * #define usb_callback_data_t struct my_usb_callback_data
 * #include <usbdrvce.h>
 * \endcode
 */
#ifndef usb_callback_data_t
#define usb_callback_data_t void
#endif
/**
 * A pointer to \c usb_device_data_t can be associated with devices.
 * The default is void *, but this can be changed by doing:
 * \code
 * #define usb_device_data_t struct my_usb_device_data
 * #include <usbdrvce.h>
 * \endcode
 */
#ifndef usb_device_data_t
#define usb_device_data_t void
#endif
/**
 * A pointer to \c usb_endpoint_data_t can be associated with endpoints.
 * The default is void *, but this can be changed by doing:
 * \code
 * #define usb_endpoint_data_t struct my_usb_endpoint_data
 * #include <usbdrvce.h>
 * \endcode
 */
#ifndef usb_endpoint_data_t
#define usb_endpoint_data_t void
#endif
/**
 * A pointer to \c usb_transfer_data_t is passed to \c usb_transfer_callback_t.
 * The default is void *, but this can be changed by doing:
 * \code
 * #define usb_transfer_data_t struct my_usb_transfer_data
 * #include <usbdrvce.h>
 * \endcode
 */
#ifndef usb_transfer_data_t
#define usb_transfer_data_t void
#endif

/**
 * Type of the function to be called when a usb device event occurs.
 * @param event_data Event specific data.
 * @param callback_data Opaque pointer passed to usb_Init().  By default is of
 * type void *, but that can be changed by doing:
 * \code
 * #define usb_device_callback_data_t struct mystruct
 * #include <usbdrvce.h>
 * \endcode
 * @return Return USB_SUCCESS to initialize the device, USB_IGNORE to ignore it
 * without erroring, or an error to ignore the device and to return from
 * usb_ProcessEvents().
 */
typedef usb_error_t (*usb_event_callback_t)(usb_event_t event, void *event_data,
                                            usb_callback_data_t *callback_data);

/**
 * Type of the function to be called when a transfer finishes.
 * @param endpoint The transfer endpoint.
 * @param status Status of the transfer.
 * @param data Opaque pointer passed to usb_Schedule*Transfer().  By default is
 * of type void *, but that can be changed by doing:
 * \code
 * #define usb_transfer_callback_data_t struct mystruct
 * #include <usbdrvce.h>
 * \endcode
 * @param data Opaque pointer passed to usb_ScheduleTransfer().
 * @param transferred The number of bytes transferred.
 * Only valid if \p status was USB_TRANSFER_COMPLETED.
 * @return Return USB_SUCCESS to free the transfer, USB_IGNORE to restart it,
 * or an error to free it and to return from usb_ProcessEvents().
 */
typedef usb_error_t (*usb_transfer_callback_t)(usb_endpoint_t endpoint,
                                               usb_transfer_status_t status,
                                               size_t transferred,
                                               usb_transfer_data_t *data);

/**
 * Initializes the usb driver.
 * @param handler Function to be called when a usb event happens.
 * @param data Opaque pointer to be passed to \p handler.
 * @param device_descriptors A pointer to the device descriptors to use, or
 * NULL to use the calculator's defaults.
 * @param flags Which areas of memory to use.
 * @return USB_SUCCESS if initialization succeeded.
 * @note This must be called before any other function, and can be called again
 * to cancel all transfers and disable all devices.
 */
usb_error_t usb_Init(usb_event_callback_t handler, usb_callback_data_t *data,
                     const usb_standard_descriptors_t *device_descriptors,
                     usb_init_flags_t flags);

/**
 * Uninitializes the usb driver.
 * @note This must be called before the program exits, or TIOS gets angry.
 */
void usb_Cleanup(void);

/**
 * Calls any device or transfer callbacks that have triggered.
 * @return An error returned by a callback or USB_SUCCESS.
 */
usb_error_t usb_HandleEvents(void);

/**
 * Waits for any device or transfer events to occur, then calls their associated
 * callbacks.
 * @return An error returned by a callback or USB_SUCCESS.
 */
usb_error_t usb_WaitForEvents(void);

/**
 * Waits for any interrupt or usb event to occur, then calls any device or
 * transfer callbacks that may have triggered.
 * @return An error returned by a callback or USB_SUCCESS.
 */
usb_error_t usb_WaitForInterrupt(void);

/**
 * Gets the hub that \p device is attached to, or NULL if \p device is the root
 * hub.
 * @param device Device to get the hub of.
 * @return The hub device or NULL.
 */
usb_device_t usb_GetDeviceHub(usb_device_t device);

/**
 * Sets the user data associated with \p device.
 * @param device Device to set the user data of.
 */
void usb_SetDeviceData(usb_device_t device, usb_device_data_t *data);

/**
 * Gets the user data associated with \p device.
 * @param device Device to get the user data of.
 * @return The user data last set with \c usb_SetDeviceData.
 */
usb_device_data_t *usb_GetDeviceData(usb_device_t device);

/**
 * Finds the next device connected through \p root after \p from satisfying
 * \p flags, or \c NULL if no more matching devices.
 *
 * To enumerate all devices, excluding all hubs:
 * \code
 * usb_device_t device = NULL;
 * while ((device = usb_FindDevice(NULL, device, USB_SKIP_HUBS))) {
 *   handle(device);
 * }
 * \endcode
 *
 * To enumerate all hubs and devices, including the root hub:
 * \code
 * usb_device_t device = NULL;
 * while ((device = usb_FindDevice(NULL, device, USB_SKIP_NONE))) {
 *   handle(device);
 * }
 * \endcode
 *
 * To enumerate all hubs and devices except the root hub:
 * \code
 * usb_device_t device = NULL; // same as using usb_RootHub()
 * while ((device = usb_FindDevice(usb_RootHub(), device, USB_SKIP_NONE))) {
 *   handle(device);
 * }
 * \endcode
 *
 * To enumerate all devices below a specific hub:
 * \code
 * usb_device_t device = NULL; // same as using hub
 * while ((device = usb_FindDevice(hub, device, USB_SKIP_NONE))) {
 *   handle(device);
 * }
 * \endcode
 *
 * To enumerate all disabled hubs directly attached to a specific hub:
 * \code
 * usb_device_t device = NULL; // must not use hub or else USB_SKIP_ATTACHED
 *                             // will skip all devices attached to hub!
 * while ((device = usb_FindDevice(hub, device, USB_SKIP_ENABLED |
 *                                 USB_SKIP_DEVICES | USB_SKIP_ATTACHED))) {
 *   handle(device);
 * }
 * \endcode
 * @param root Hub below which to limit search, or \c NULL to search all
 * devices including the root hub.
 * @param from Device to start the search from, or \c NULL to start from
 * \p root and include devices attached to root even with \c USB_SKIP_ATTACHED.
 * @param flags What kinds of devices to return.
 * @return The next device connected through \p root after \p from satisfying
 * \p flags or \c NULL if none.
 */
usb_device_t usb_FindDevice(usb_device_t root, usb_device_t from,
                            usb_find_flag_t flags);

/**
 * Performs a usb reset on a device. This triggers a device enabled event when
 * the reset finishes.
 * @param device The device to reset.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ResetDevice(usb_device_t device);

/**
 * Forces a device to disconnect. This triggers a device disabled event when the
 * disconnect finishes.
 * @param device The device to disconnect.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_DisconnectDevice(usb_device_t device);

/**
 * Gets the usb address of a \p device, or 0 if disabled.
 * @param device The device to communicate with.
 * @return The usb address or 0.
 */
uint8_t usb_GetDeviceAddress(usb_device_t device);

/**
 * Gets the speed of a \device, or USB_SPEED_UNKNOWN if unknown.
 * @param device The device to communicate with.
 * @return The \c usb_speed_t.
 */
usb_speed_t usb_GetDeviceSpeed(usb_device_t device);

/**
 * Determines how large of a buffer would be required to receive the complete
 * configuration descriptor at \p index.
 * @note Blocks while the configuration descriptor is fetched.
 * @param device The device to communicate with.
 * @param index Which configuration descriptor to query.
 * @return The total length in bytes of the combined configuration descriptor or
 * 0 on error.
 */
size_t usb_GetConfigurationDescriptorTotalLength(usb_device_t device,
                                                 uint8_t index);

/**
 * Gets the descriptor of a \p device of \p type at \p index.
 * @note Blocks while the descriptor is fetched.
 * @param device The device to communicate with.
 * @param type The \c usb_descriptor_type_t to fetch.
 * @param index Descriptor index to fetch.
 * @param descriptor Returns the fetched descriptor.
 * @param length The maximum number of bytes to receive.
 * The \p descriptor buffer must be at least this large.
 * @param transferred Returns the number of bytes actually received.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetDescriptor(usb_device_t device, usb_descriptor_type_t type,
                              uint8_t index, usb_descriptor_t *descriptor,
                              size_t length, size_t *transferred);

/**
 * Changes the descriptor at \p index.
 * @note Blocks while the descriptor is changed.
 * @note Devices do not usually support this.
 * @param device The device to communicate with.
 * @param type The \c usb_descriptor_type_t to change.
 * @param index The descriptor index to change.
 * @param descriptor The new descriptor.
 * @param length The number of bytes in the new descriptor.
 * The \p descriptor buffer must be this large.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetDescriptor(usb_device_t device, usb_descriptor_type_t type,
                              uint8_t index, const usb_descriptor_t *descriptor,
                              size_t length);

/**
 * Gets the string descriptor at \p index and \p langid.
 * @note Blocks while the descriptor is fetched.
 * @param device The device to communicate with.
 * @param index Descriptor index to fetch.
 * @param langid Language ID to fetch.
 * @param descriptor Returns the fetched descriptor.
 * @param length The number of bytes to transfer.
 * The \p descriptor buffer must be at least this large.
 * @param transferred Returns the number of bytes actually received.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetStringDescriptor(usb_device_t device, uint8_t index,
                                    uint16_t langid,
                                    usb_string_descriptor_t *descriptor,
                                    size_t length, size_t *transferred);

/**
 * Sets the string descriptor at \p index and \p langid.
 * @note Blocks while the descriptor is changed.
 * @note Devices do not usually support this.
 * @param device The device to communicate with.
 * @param index Descriptor index to change.
 * @param langid Language ID to change.
 * @param descriptor The new descriptor.
 * @param length The number of bytes to transfer.
 * The \p descriptor buffer must be this large.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetStringDescriptor(usb_device_t device, uint8_t index,
                                    uint16_t langid,
                                    const usb_string_descriptor_t *descriptor,
                                    size_t length);

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
 * @param descriptor A complete combined configuration descriptor fetched with
 * usb_GetDescriptor().
 * @param length The total length of the configuration descriptor.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t
usb_SetConfiguration(usb_device_t device,
                     const usb_configuration_descriptor_t *descriptor,
                     size_t length);

/**
 * Gets the current alternate setting in use on the specified interface.
 * @param device The device to communicate with.
 * @param interface Interface index to query.
 * @param alternate_setting Returns the alternate setting in use.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_GetInterface(usb_device_t device, uint8_t interface,
                             uint8_t *alternate_setting);

/**
 * Sets the alternate setting in use on the specified interface.
 * @param device The device to communicate with.
 * @param interface_descriptor The interface descriptor describing the interface
 * to select within a configuration descriptor.
 * @param length The remaining length of the configuration descriptor after
 * the beginning of the \p interface_descriptor.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_SetInterface(usb_device_t device,
                             const usb_interface_descriptor_t *descriptor,
                             size_t length);

/**
 * Gets the endpoint of a \p device with a given \p address, or NULL if that
 * address is unused.
 * @param device Device to get the user data of.
 * @param address Address of the endpoint to get.
 * @return The specified endpoint or NULL.
 */
usb_endpoint_t usb_GetDeviceEndpoint(usb_device_t device, uint8_t address);

/**
 * Gets the device that \p endpoint is connected to.
 * @param endpoint Endpoint to get the device of.
 * @return The device for an \p endpoint.
 */
usb_device_t usb_GetEndpointDevice(usb_endpoint_t endpoint);

/**
 * Sets the user data associated with \p endpoint.
 * @param endpoint Endpoint to set the user data of.
 */
void usb_SetEndpointData(usb_endpoint_t endpoint, usb_endpoint_data_t *data);

/**
 * Gets the user data associated with \p endpoint.
 * @param device Endpoint to get the user data of.
 * @return The user data last set with \c usb_SetEndpointData.
 */
usb_endpoint_data_t *usb_GetEndpointData(usb_endpoint_t endpoint);

/**
 * Gets the maximum packet size of an endpoint.
 * @param endpoint The endpoint to get the maximum packet size of..
 * @return The wMaxPacketSize for an \p endpoint.
 */
uint16_t usb_GetEndpointMaxPacketSize(usb_endpoint_t endpoint);

/**
 * Gets the transfer type of an endpoint.
 * @param endpoint The endpoint to get the transfer type of.
 * @return The usb_transfer_type for an endpoint.
 */
usb_transfer_type_t usb_GetEndpointTransferType(usb_endpoint_t endpoint);

/**
 * Sets the flags for an endpoint.
 * @param endpoint The endpoint to set the flags of.
 * @param flags The \c usb_endpoint_flag_t to set.
 */
void usb_SetEndpointFlags(usb_endpoint_t endpoint, usb_endpoint_flag_t flags);

/**
 * Gets the flags for an endpoint.
 * @param endpoint The endpoint to get the flags of.
 * @return The flags last set with \c usb_SetEndpointFlags.
 */
usb_endpoint_flag_t usb_GetEndpointFlags(usb_endpoint_t endpoint);

/**
 * Clears an endpoint's halt condition, indicated by transfers to that endpoint
 * stalling.  This function blocks until the halt condition is cleared.
 * @param endpoint The endpoint to clear the halt condition of.
 * @return USB_SUCCESS if the transfer succeeded or an error.
 */
usb_error_t usb_ClearEndpointHalt(usb_endpoint_t endpoint);

/**
 * Returns the current 11-bit frame number, as last broadcast by the current
 * host, multiplied by 8.  This value ranges from 0x0000 to 0x3FF8, increases by
 * 8 every 1 ms, is truncated to 14 bits, and is synchronized with the host usb
 * clock.
 * @warning The bottom 3 bits are usually 0, but this is not guaranteed because
 * random mmio writes could affect those bits.
 * @note If the hardware supported full speed usb, the lower 3 bits would be the
 * microframe number.
 * @return usb_frame_number << 3
 */
unsigned usb_GetFrameNumber(void);

/**
 * Schedules a transfer to the pipe connected to \p endpoint, in the direction
 * indicated by \p setup->bmRequestType, using \p buffer as the data buffer,
 * \p setup->wLength as the buffer length, and then waits for it to complete.
 * If acting as usb host and using a control pipe, \p setup is used as the setup
 * packet, otherwise all fields not mentioned above are ignored.
 * @param endpoint The endpoint to communicate with, which also specifies the
 * direction for non-control transfers.
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
usb_error_t
usb_ControlTransfer(usb_endpoint_t endpoint, const usb_control_setup_t *setup,
                    void *buffer, unsigned retries, size_t *transferred);

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
#define usb_DefaultControlTransfer(/*usb_device_t */device,                    \
                                   /*const usb_control_setup_t **/setup,       \
                                   /*void **/buffer, /*unsigned */retries,     \
                                   /*size_t **/transferred)/*;*/               \
  usb_ControlTransfer(usb_GetDeviceEndpoint(device, 0), setup, buffer,         \
                      retries, transferred)

/**
 * Schedules a transfer to the pipe connected to \p endpoint, using \p length as
 * the buffer length, and waits for it to complete. If acting as usb host and
 * using a control pipe, uses the beginning of \p buffer as the setup packet to
 * send, its \c bmRequestType for the transfer direction, and the rest of
 * \p buffer as the data buffer.  Otherwise, uses \p endpoint for transfer
 * direction and  the whole \p buffer as the data buffer.
 * @param endpoint The endpoint to communicate with, which also specifies the
 * direction for non-control transfers.
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
usb_error_t usb_Transfer(usb_endpoint_t endpoint, void *buffer, size_t length,
                         unsigned retries, size_t *transferred);
#define usb_BulkTransfer usb_Transfer
#define usb_InterruptTransfer usb_Transfer
#define usb_IsochronousTransfer usb_Transfer

/**
 * Schedules a transfer to the pipe connected to \p endpoint, in the direction
 * indicated by \p setup->bmRequestType, using \p buffer as the data buffer, and
 * \p setup->wLength as the buffer length.  If acting as usb host and using a
 * control pipe, \p setup is used as the setup packet, otherwise all fields not
 * mentioned above are ignored.
 * @param endpoint The endpoint to communicate with, which also specifies the
 * direction for non-control transfers.
 * @param setup Indicates the transfer direction and buffer length.  If acting
 * as usb host and using a control pipe, also used as the setup packet to send.
 * @param buffer Data to transfer that must reside in RAM.  This buffer must
 * remain valid until the callback is called i.e. it cannot be modified or
 * freed.
 * @param handler Function to be called when the transfer finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @param transfer Returns a handle to the transfer.
 * @return USB_SUCCESS if the transfer was scheduled or an error.
 */
usb_error_t
usb_ScheduleControlTransfer(usb_endpoint_t endpoint,
                            const usb_control_setup_t *setup, void *buffer,
                            usb_transfer_callback_t handler,
                            usb_transfer_data_t *data);

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
 * @param handler Function to be called when the transfer finishes.
 * @param data Opaque pointer to be passed to the \p handler.
 * @return USB_SUCCESS if the transfer was scheduled or an error.
 */
#define /*usb_error_t */                                                       \
usb_ScheduleDefaultControlTransfer(/*usb_device_t */device,                    \
                                   /*const usb_control_setup_t **/setup,       \
                                   /*void **/buffer,                           \
                                   /*usb_transfer_callback_t */handler,        \
                                   /*usb_transfer_data_t **/data)/*;*/         \
  usb_ScheduleControlTransfer(usb_GetDeviceEndpoint(device, 0), setup, buffer, \
                              handler, data)

/**
 * If endpoint is not a control endpoint, schedules a transfer of the endpoint's
 * transfer type.  If the endpoint is a control endpoint, schedules a control
 * transfer interpreting the beginning of buffer as the \c usb_control_setup_t
 * and using the rest of the buffer as the transfer buffer.
 * @param endpoint The endpoint to communicate with, which also specifies the
 * direction for non-control transfers.
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
usb_error_t
usb_ScheduleTransfer(usb_endpoint_t endpoint, void *buffer, size_t length,
                     usb_transfer_callback_t handler,
                     usb_transfer_data_t *data);
#define usb_ScheduleBulkTransfer usb_ScheduleTransfer
#define usb_ScheduleInterruptTransfer usb_ScheduleTransfer
#define usb_ScheduleIsochronousTransfer usb_ScheduleTransfer

#ifdef __cplusplus
}
#endif

#endif
