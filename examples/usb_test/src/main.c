typedef struct global global_t;
#define usb_callback_data_t global_t

#include <usbdrvce.h>

#include <debug.h>
#include <tice.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct global {
    usb_device_t device;
    usb_endpoint_t in, out;
    uint8_t type;
};

static void putChar(char c) {
    static char str[2];
    str[0] = c;
    os_PutStrFull(str);
}
static void putNibHex(unsigned char x) {
    x &= 0xF;
    putChar(x < 10 ? '0' + x : 'A' + x - 10);
}
static void putByteHex(unsigned char x) {
    putNibHex(x >> 4);
    putNibHex(x >> 0);
}
static void putShortHex(unsigned short x) {
    putByteHex(x >> 8);
    putByteHex(x >> 0);
}
static void putIntHex(unsigned x) {
    putByteHex(x >> 16);
    putShortHex(x >> 0);
}
static void putLongHex(unsigned long x) {
    putByteHex(x >> 24);
    putIntHex(x);
}
static void putBlockHex(void *block, size_t size) {
    while (size--)
        putByteHex(*(*(unsigned char **)&block)++);
}

static usb_error_t handleTestIn(usb_endpoint_t endpoint,
                                usb_transfer_status_t status,
                                size_t transferred, usb_transfer_data_t *data) {
    putByteHex(status);
    putChar(':');
    putIntHex(transferred);
    _OS(asm_NewLine);
    return USB_SUCCESS;
}

static usb_error_t handleTestOut(usb_endpoint_t endpoint,
                                 usb_transfer_status_t status,
                                 size_t transferred, usb_transfer_data_t *data) {
    putByteHex(status);
    putChar(':');
    putIntHex(transferred);
    putChar(':');
    putBlockHex((char *)data + transferred - 6, 7);
    _OS(asm_NewLine);
    free(data);
    return USB_SUCCESS;
}

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data) {
    static const char *usb_event_names[] = {
        "USB_ROLE_CHANGED_EVENT",
        "USB_DEVICE_DISCONNECTED_EVENT",
        "USB_DEVICE_CONNECTED_EVENT",
        "USB_DEVICE_DISABLED_EVENT",
        "USB_DEVICE_ENABLED_EVENT",
        "USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT",
        "USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT",
        "USB_DEFAULT_SETUP_EVENT",
        // Temp debug events:
        "USB_DEVICE_INT",
        "USB_DEVICE_CONTROL_INT",
        "USB_DEVICE_FIFO_INT",
        "USB_DEVICE_DEVICE_INT",
        "USB_OTG_INT",
        "USB_HOST_INT",
        "USB_CONTROL_END_INT",
        "USB_CONTROL_ERROR_INT",
        "USB_CONTROL_ABORT_INT",
        "USB_FIFO0_INPUT_INT",
        "USB_FIFO0_OUTPUT_INT",
        "USB_FIFO0_SHORT_PACKET_INT",
        "USB_FIFO1_INPUT_INT",
        "USB_FIFO1_OUTPUT_INT",
        "USB_FIFO1_SHORT_PACKET_INT",
        "USB_FIFO2_INPUT_INT",
        "USB_FIFO2_OUTPUT_INT",
        "USB_FIFO2_SHORT_PACKET_INT",
        "USB_FIFO3_INPUT_INT",
        "USB_FIFO3_OUTPUT_INT",
        "USB_FIFO3_SHORT_PACKET_INT",
        "USB_DEVICE_SUSPEND_INT",
        "USB_DEVICE_RESUME_INT",
        "USB_DEVICE_ISOCHRONOUS_ERROR_INT",
        "USB_DEVICE_ISOCHRONOUS_ABORT_INT",
        "USB_DEVICE_ZERO_LENGTH_PACKET_TRANSMIT_INT",
        "USB_DEVICE_ZERO_LENGTH_PACKET_RECEIVE_INT",
        "USB_DEVICE_DMA_FINISH_INT",
        "USB_DEVICE_DMA_ERROR_INT",
        "USB_DEVICE_IDLE_INT",
        "USB_DEVICE_WAKEUP_INT",
        "USB_B_SRP_COMPLETE_INT",
        "USB_A_SRP_DETECT_INT",
        "USB_A_VBUS_ERROR_INT",
        "USB_B_SESSION_END_INT",
        "USB_OVERCURRENT_INT",
        "USB_HOST_PORT_CONNECT_STATUS_CHANGE_INT",
        "USB_HOST_PORT_ENABLE_DISABLE_CHANGE_INT",
        "USB_HOST_PORT_OVERCURRENT_CHANGE_INT",
        "USB_HOST_PORT_FORCE_PORT_RESUME_INT",
        "USB_HOST_FRAME_LIST_ROLLOVER_INT",
        "USB_HOST_SYSTEM_ERROR_INT",
    };
    usb_error_t error = USB_SUCCESS;
    unsigned char i;
    switch (event) {
        case USB_ROLE_CHANGED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putNibHex(*(usb_role_t *)event_data >> 4);
            _OS(asm_NewLine);
            break;
        case USB_DEVICE_DISCONNECTED_EVENT:
            if (callback_data->device == event_data) {
                callback_data->device = NULL;
                callback_data->in = callback_data->out = NULL;
            }
        case USB_DEVICE_CONNECTED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putIntHex((unsigned)event_data);
            putIntHex((unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            _OS(asm_NewLine);
            break;
        case USB_DEVICE_DISABLED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            _OS(asm_NewLine);
            break;
        case USB_DEVICE_ENABLED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putIntHex((unsigned)event_data);
            putIntHex((unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            callback_data->device = event_data;
            _OS(asm_NewLine);
            break;
        case USB_DEFAULT_SETUP_EVENT: {
            const usb_control_setup_t *setup = event_data;
            for (i = 0; i < 8; i++)
                putByteHex(((unsigned char *)setup)[i]);
            _OS(asm_NewLine);
            if ((setup->bmRequestType & ~USB_DEVICE_TO_HOST) == USB_VENDOR_REQUEST | USB_RECIPIENT_DEVICE &&
                !setup->bRequest && !setup->wValue && !setup->wIndex) {
                usb_device_t host;
                usb_endpoint_t control;
                host = usb_FindDevice(NULL, NULL, USB_SKIP_HUBS);
                if (!host) {
                    error = USB_ERROR_NO_DEVICE;
                    break;
                }
                control = usb_GetDeviceEndpoint(host, 0);
                if (!control) {
                    error = USB_ERROR_SYSTEM;
                    break;
                }
                if (setup->bmRequestType & USB_DEVICE_TO_HOST) {
                    error = usb_ScheduleTransfer(control, "Hello World! Which must be exactly sixty-three characters?!?!1!.Hello World! Which must be exactly sixty-three characters?!?!1!.", 129, handleTestIn, NULL);
                } else {
                    char *buffer = malloc(setup->wLength);
                    if (!buffer) {
                        error = USB_ERROR_NO_MEMORY;
                        break;
                    }
                    error = usb_ScheduleControlTransfer(control, setup, buffer, handleTestOut, buffer);
                }
                if (error == USB_SUCCESS)
                    error = USB_IGNORE;
            }
            break;
        }
        case USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT: {
            static unsigned counter;
            unsigned row, col;
            os_GetCursorPos(&row, &col);
            os_SetCursorPos(0, 8);
            putIntHex(++counter);
            os_SetCursorPos(row, col);
            break;
        }
        case USB_DEVICE_INTERRUPT:
        case USB_DEVICE_DEVICE_INTERRUPT:
        case USB_DEVICE_CONTROL_INTERRUPT:
        case USB_DEVICE_WAKEUP_INTERRUPT:
        case USB_HOST_INTERRUPT:
            break;
        case 100:
            putIntHex((unsigned)event_data);
            _OS(asm_NewLine);
            break;
        case 101:
            putLongHex(atomic_load_32(&timer_2_Counter));
            os_PutStrFull(" cycles");
            _OS(asm_NewLine);
            timer_2_Counter = 0;
        case 102:
            for (i = 0; i < 64; i++)
                putByteHex(((unsigned char *)event_data)[i]);
            _OS(asm_NewLine);
            break;
        default:
            os_PutStrFull(usb_event_names[event]);
            _OS(asm_NewLine);
            break;
    }
    return error;
}

static bool parseConfigurationDescriptor(global_t *const global,
                                         const usb_device_descriptor_t *const device,
                                         usb_configuration_descriptor_t *const configuration,
                                         const size_t length) {
    uint8_t *current = (uint8_t *)configuration;
    size_t remaining = length;
    usb_error_t error;
    uint8_t in = 0, out = 0;
    while (remaining && (!in || !out)) {
        usb_descriptor_t *descriptor = (usb_descriptor_t *)current;
        if (remaining < 2 || remaining < descriptor->bLength) return false;
        switch (descriptor->bDescriptorType) {
            case USB_INTERFACE_DESCRIPTOR: {
                usb_interface_descriptor_t *interface = (usb_interface_descriptor_t *)descriptor;
                if (device->idVendor == 0x451 && device->idProduct == 0xE008)
                    global->type = 2;
                else if (interface->bInterfaceClass == 0x08 &&
                         interface->bInterfaceSubClass == 0x06 &&
                         interface->bInterfaceProtocol == 0x50)
                    global->type = 1;
                else
                    global->type = 0;
                in = out = 0;
                break;
            }
            case USB_ENDPOINT_DESCRIPTOR: {
                usb_endpoint_descriptor_t *endpoint = (usb_endpoint_descriptor_t *)descriptor;
                if (global->type && endpoint->bmAttributes == USB_BULK_TRANSFER) {
                    uint8_t *addr = endpoint->bEndpointAddress & USB_DEVICE_TO_HOST ? &in : &out;
                    if (!*addr) *addr = endpoint->bEndpointAddress;
                }
                break;
            }
        }
        current += descriptor->bLength;
        remaining -= descriptor->bLength;
    }
    if (!in || !out) return false;
    if ((error = usb_SetConfiguration(global->device, configuration, length)) != USB_SUCCESS) {
        putIntHex(error);
        _OS(asm_NewLine);
        return false;
    }
    global->in = usb_GetDeviceEndpoint(global->device, in);
    global->out = usb_GetDeviceEndpoint(global->device, out);
    return true;
}

static void handleDevice(global_t *global) {
#define USB_GET_MAX_LUN 0xFE
    static const usb_control_setup_t get_max_lun_setup = { USB_DEVICE_TO_HOST | USB_CLASS_REQUEST | USB_RECIPIENT_INTERFACE, USB_GET_MAX_LUN, 0, 0, 1 };
    static const uint8_t inquiry_cbw[] = { 'U','S','B','C', 1,0,0,0, 0x24,0,0,0, USB_DEVICE_TO_HOST,0,6, 0x12, 0, 0, 0,0x24, 0, 0,0,0,0,0,0,0,0,0,0 };
    static const uint8_t rdy_pkt_00[] = { 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 0x00 };
    static const uint8_t rdy_pkt_01[] = { 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0xd0 };
    static uint8_t buffer[64];
    usb_error_t error;
    usb_device_descriptor_t device;
    size_t length;
    uint8_t index;
    bool found = false;
    usb_configuration_descriptor_t *configuration = NULL;
    if (!global->device)
        return;
    if ((error = usb_GetDescriptor(global->device, USB_DEVICE_DESCRIPTOR,
                                   0, &device, sizeof(device), &length))
        != USB_SUCCESS) goto err;
    if (length < sizeof(device)) goto noerr;
    putBlockHex(&device, sizeof(device));
    _OS(asm_NewLine);
    for (index = 0; !found && index != device.bNumConfigurations; ++index) {
        length = usb_GetConfigurationDescriptorTotalLength(global->device, index);
        if (!(configuration = malloc(length))) goto noerr;
        if ((error = usb_GetDescriptor(global->device, USB_CONFIGURATION_DESCRIPTOR,
                                       index, configuration, length, &length))
            != USB_SUCCESS) goto err;
        putByteHex(index);
        putChar(':');
        putBlockHex(configuration, length);
        _OS(asm_NewLine);
        found = parseConfigurationDescriptor(global, &device, configuration, length);
        free(configuration); configuration = NULL;
    }
    if (!found) goto noerr;
    putByteHex(global->type);
    putByteHex(usb_GetEndpointAddress(global->in));
    putByteHex(usb_GetEndpointAddress(global->out));
    _OS(asm_NewLine);
    switch (global->type) {
        case 1:
            putIntHex(usb_DefaultControlTransfer(global->device, &get_max_lun_setup, buffer, 0, &length));
            putChar(':');
            if (length <= 1)
                putBlockHex(buffer, length);
            else
                putIntHex(length);
            _OS(asm_NewLine);

            putIntHex(usb_BulkTransfer(global->out, inquiry_cbw, sizeof(inquiry_cbw), 0, &length));
            putChar(':');
            putIntHex(length);
            _OS(asm_NewLine);

            putIntHex(usb_BulkTransfer(global->in, buffer, 0x24, 0, &length));
            putChar(':');
            if (length <= 0x24)
                putBlockHex(buffer, length);
            else
                putIntHex(length);
            _OS(asm_NewLine);

            putIntHex(usb_BulkTransfer(global->in, buffer, 0xD, 0, &length));
            putChar(':');
            if (length <= 0xD)
                putBlockHex(buffer, length);
            else
                putIntHex(length);
            _OS(asm_NewLine);

            break;
        case 2:
            putIntHex(usb_BulkTransfer(global->out, rdy_pkt_00, sizeof(rdy_pkt_00), 0, &length));
            putChar(':');
            putIntHex(length);
            _OS(asm_NewLine);

            length = 0;
            putIntHex(usb_BulkTransfer(global->in, buffer, sizeof(buffer), 0, &length));
            putChar(':');
            if (length <= sizeof(buffer))
                putBlockHex(buffer, length);
            else
                putIntHex(length);
            _OS(asm_NewLine);

            putIntHex(usb_BulkTransfer(global->out, rdy_pkt_01, sizeof(rdy_pkt_01), 0, &length));
            putChar(':');
            putIntHex(length);
            _OS(asm_NewLine);

            length = 0;
            putIntHex(usb_BulkTransfer(global->in, buffer, sizeof(buffer), 0, &length));
            putChar(':');
            if (length <= sizeof(buffer))
                putBlockHex(buffer, length);
            else
                putIntHex(length);
            _OS(asm_NewLine);

            break;
    }
    goto noerr;
 err:
    putIntHex(error);
    _OS(asm_NewLine);
 noerr:
    if (configuration) free(configuration);
    memset(global, 0, sizeof(global_t));
 }

void main(void) {
    global_t global;
    usb_error_t error;
    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);
    if ((error = usb_Init(handleUsbEvent, &global, NULL,
                          USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS) {
        while ((error = usb_WaitForInterrupt()) == USB_SUCCESS && !os_GetCSC()) {
            unsigned row, col;
            os_GetCursorPos(&row, &col);
            os_SetCursorPos(0, 0);
            putIntHex(usb_GetFrameNumber());
            os_SetCursorPos(row, col);
            handleDevice(&global);
        }
    }
    usb_Cleanup();
    putIntHex(error);
    os_GetKey();
}
