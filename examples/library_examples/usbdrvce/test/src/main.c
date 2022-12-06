typedef struct global global_t;
#define usb_callback_data_t global_t

#include <usbdrvce.h>

#include <debug.h>
#include <tice.h>

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct global {
    usb_device_t device;
    usb_endpoint_t in, out;
    uint8_t type;
};

void outchar(char c) {
    if (c == '\n') {
        os_NewLine();
        return;
    }
    if (c < ' ' || c > '~')
        return;
    if (c == '[')
        c = 0xC1;
    os_PutStrFull((char[]){c, '\0'});
}

static void putBlockHex(const void *block, size_t size) {
    const uint8_t *pointer = block;
    while (size--)
        printf("%02X", *pointer++);
}

static usb_error_t handleTestIn(usb_endpoint_t endpoint,
                                usb_transfer_status_t status,
                                size_t transferred, usb_transfer_data_t *data) {
    (void)endpoint;
    (void)data;
    printf("%02X: %u\n", status, transferred);
    return USB_SUCCESS;
}

static usb_error_t handleTestOut(usb_endpoint_t endpoint,
                                 usb_transfer_status_t status,
                                 size_t transferred, usb_transfer_data_t *data) {
    (void)endpoint;
    printf("%02X: %u ", status, transferred);
    putBlockHex((char *)data + transferred - 6, 7);
    printf("\n");
    free(data);
    return USB_SUCCESS;
}

static usb_error_t handleBulkIn(usb_endpoint_t endpoint,
                                usb_transfer_status_t status,
                                size_t transferred, usb_transfer_data_t *data) {
    (void)endpoint;
    (void)data;
    printf("%02X| %u\n", status, transferred);
    return USB_SUCCESS;
}

static usb_error_t handleBulkOut(usb_endpoint_t endpoint,
                                 usb_transfer_status_t status,
                                 size_t transferred, usb_transfer_data_t *data) {
    printf("%02X| %u ", status, transferred);
    putBlockHex((char *)data + transferred - 6, 7);
    printf("\n");
    if (status == USB_TRANSFER_COMPLETED)
        return usb_ScheduleBulkTransfer(endpoint, data, 512, handleBulkOut, data);
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
        "USB_HUB_LOCAL_POWER_GOOD_EVENT",
        "USB_HUB_LOCAL_POWER_LOST_EVENT",
        "USB_DEVICE_RESUMED_EVENT",
        "USB_DEVICE_SUSPENDED_EVENT",
        "USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT",
        "USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT",
        "USB_DEFAULT_SETUP_EVENT",
        "USB_HOST_CONFIGURE_EVENT",
        // Temp debug events:
        "USB_DEVICE_INT",
        "USB_DEVICE_CONTROL_INT",
        "USB_DEVICE_DEVICE_INT",
        "USB_OTG_INT",
        "USB_HOST_INT",
        "USB_CONTROL_ERROR_INT",
        "USB_CONTROL_ABORT_INT",
        "USB_FIFO0_SHORT_PACKET_INT",
        "USB_FIFO1_SHORT_PACKET_INT",
        "USB_FIFO2_SHORT_PACKET_INT",
        "USB_FIFO3_SHORT_PACKET_INT",
        "USB_DEVICE_SUSPEND_INT",
        "USB_DEVICE_RESUME_INT",
        "USB_DEVICE_ISOCHRONOUS_ERROR_INT",
        "USB_DEVICE_ISOCHRONOUS_ABORT_INT",
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
        "USB_HOST_SYSTEM_ERROR_INT",
    };
    usb_error_t error = USB_SUCCESS;
    switch ((unsigned)event) {
        case USB_ROLE_CHANGED_EVENT:
            printf("%s: %02X\n", usb_event_names[event], *(const usb_role_t *)event_data);
            break;
        case USB_DEVICE_DISCONNECTED_EVENT:
            if (callback_data->device == event_data) {
                callback_data->device = NULL;
                callback_data->in = callback_data->out = NULL;
            }
            __attribute__((fallthrough));
        case USB_DEVICE_CONNECTED_EVENT:
        case USB_DEVICE_DISABLED_EVENT:
        case USB_DEVICE_ENABLED_EVENT:
            printf("%s: %06X %06X\n", usb_event_names[event], (unsigned)event_data,
                   (unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            if (event == USB_DEVICE_CONNECTED_EVENT && !(usb_GetRole() & USB_ROLE_DEVICE))
                error = usb_ResetDevice(event_data);
            if (event == USB_DEVICE_ENABLED_EVENT)
                callback_data->device = event_data;
            break;
        case USB_DEFAULT_SETUP_EVENT: {
            static const usb_control_setup_t clear_out_endpoint_halt_setup = {
                .bmRequestType = USB_HOST_TO_DEVICE | USB_STANDARD_REQUEST | USB_RECIPIENT_ENDPOINT,
                .bRequest = USB_CLEAR_FEATURE_REQUEST,
                .wValue = USB_ENDPOINT_HALT_FEATURE,
                .wIndex = 0x02,
                .wLength = 0,
            };
            const usb_control_setup_t *setup = event_data;
            putBlockHex(setup, sizeof(*setup));
            printf("\n");
            usb_device_t host = usb_FindDevice(NULL, NULL, USB_SKIP_HUBS);
            if (!host) {
                error = USB_ERROR_NO_DEVICE;
                break;
            }
            if (!memcmp(setup, &clear_out_endpoint_halt_setup, sizeof(usb_control_setup_t))) {
                usb_endpoint_t out_endpoint = usb_GetDeviceEndpoint(host, 0x02);
                if (!out_endpoint) {
                    error = USB_ERROR_SYSTEM;
                    break;
                }
                void *buffer;
                if (!(buffer = malloc(512))) {
                    error = USB_ERROR_NO_MEMORY;
                    break;
                }
                handleBulkOut(out_endpoint, USB_TRANSFER_COMPLETED, 0, buffer);
            } else if ((setup->bmRequestType & ~USB_DEVICE_TO_HOST) == (USB_VENDOR_REQUEST | USB_RECIPIENT_DEVICE) &&
                !setup->bRequest && !setup->wValue && !setup->wIndex) {
                usb_endpoint_t default_control_endpoint = usb_GetDeviceEndpoint(host, 0);
                if (!default_control_endpoint) {
                    error = USB_ERROR_SYSTEM;
                    break;
                }
                if (setup->bmRequestType & USB_DEVICE_TO_HOST) {
                    error = usb_ScheduleTransfer(default_control_endpoint, "Hello World! Which must be exactly sixty-three characters?!?!1!.Hello World! Which must be exactly sixty-three characters?!?!1!.", 129, handleTestIn, NULL);
                } else {
                    void *buffer;
                    if (!(buffer = malloc(setup->wLength))) {
                        error = USB_ERROR_NO_MEMORY;
                        break;
                    }
                    error = usb_ScheduleControlTransfer(default_control_endpoint, setup, buffer, handleTestOut, buffer);
                }
                if (error == USB_SUCCESS)
                    error = USB_IGNORE;
            }
            break;
        }
        case USB_HOST_CONFIGURE_EVENT: {
            usb_device_t host = usb_FindDevice(NULL, NULL, USB_SKIP_HUBS);
            if (!host) {
                error = USB_ERROR_NO_DEVICE;
                break;
            }
            usb_endpoint_t in_endpoint = usb_GetDeviceEndpoint(host, 0x81);
            usb_endpoint_t out_endpoint = usb_GetDeviceEndpoint(host, 0x02);
            if (!in_endpoint || !out_endpoint) {
                error = USB_ERROR_SYSTEM;
                break;
            }
            printf("%s: %06X %06X\n", usb_event_names[event], (unsigned)event_data,
                   (unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            usb_SetEndpointFlags(in_endpoint, USB_AUTO_TERMINATE);
            error = usb_ScheduleBulkTransfer(in_endpoint,
"000000000000000000000000000000000000000000000000000000000000000\n"
"111111111111111111111111111111111111111111111111111111111111111\n"
"222222222222222222222222222222222222222222222222222222222222222\n"
"333333333333333333333333333333333333333333333333333333333333333\n"
"444444444444444444444444444444444444444444444444444444444444444\n"
"555555555555555555555555555555555555555555555555555555555555555\n"
"666666666666666666666666666666666666666666666666666666666666666\n"
"777777777777777777777777777777777777777777777777777777777777777"
, 64*8, handleBulkIn, NULL);
            if (error != USB_SUCCESS)
                break;
            void *buffer;
            if (!(buffer = malloc(512))) {
                error = USB_ERROR_NO_MEMORY;
                break;
            }
            handleBulkOut(out_endpoint, USB_TRANSFER_COMPLETED, 0, buffer);
            break;
        }
        case USB_DEVICE_INTERRUPT:
        case USB_DEVICE_DEVICE_INTERRUPT:
        case USB_DEVICE_CONTROL_INTERRUPT:
        case USB_DEVICE_WAKEUP_INTERRUPT:
        case USB_HOST_INTERRUPT:
            break;
        case 99:
            printf("debug: %06X\n", (unsigned)event_data);
            break;
        case 98:
            printf("%08" PRIX32 "cycles\n", atomic_load_32(&timer_2_Counter));
            timer_2_Counter = 0;
            break;
        case 97:
            putBlockHex(event_data, 64);
            printf("\n");
            break;
        default:
            printf("%s\n", usb_event_names[event]);
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
        printf("error: %X\n", error);
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
    if ((usb_GetRole() & USB_ROLE_DEVICE) || !global->device)
        return;
    if ((error = usb_GetDescriptor(global->device, USB_DEVICE_DESCRIPTOR,
                                   0, &device, sizeof(device), &length))
        != USB_SUCCESS) goto err;
    if (length < sizeof(device)) goto noerr;
    putBlockHex(&device, sizeof(device));
    printf("\n");
    for (index = 0; !found && index != device.bNumConfigurations; ++index) {
        length = usb_GetConfigurationDescriptorTotalLength(global->device, index);
        if (!(configuration = malloc(length))) goto noerr;
        if ((error = usb_GetDescriptor(global->device, USB_CONFIGURATION_DESCRIPTOR,
                                       index, configuration, length, &length))
            != USB_SUCCESS) goto err;
        printf("%02X: ", index);
        putBlockHex(configuration, length);
        printf("\n");
        found = parseConfigurationDescriptor(global, &device, configuration, length);
        free(configuration); configuration = NULL;
    }
    if (!found) goto noerr;
    printf("%02X %02X %02X\n", global->type, usb_GetEndpointAddress(global->in), usb_GetEndpointAddress(global->out));
    switch (global->type) {
        case 1:
            printf("%X: ", usb_DefaultControlTransfer(global->device, &get_max_lun_setup, buffer, 0, &length));
            if (length <= 1)
                putBlockHex(buffer, length);
            else
                printf("%u", length);
            printf("\n");

            printf("%06X: %u", usb_BulkTransfer(global->out, (uint8_t *)inquiry_cbw, sizeof(inquiry_cbw), 0, &length), length);

            printf("%X: ", usb_BulkTransfer(global->in, buffer, 0x24, 0, &length));
            if (length <= 0x24)
                putBlockHex(buffer, length);
            else
                printf("%u", length);
            printf("\n");

            printf("%X: ", usb_BulkTransfer(global->in, buffer, 0xD, 0, &length));
            if (length <= 0xD)
                putBlockHex(buffer, length);
            else
                printf("%u", length);
            printf("\n");

            break;
        case 2:
            printf("%X: %u\n", usb_BulkTransfer(global->out, (uint8_t *)rdy_pkt_00, sizeof(rdy_pkt_00), 0, &length), length);

            printf("%X: ", usb_BulkTransfer(global->in, buffer, sizeof(buffer), 0, &length));
            if (length <= sizeof(buffer))
                putBlockHex(buffer, length);
            else
                printf("%u", length);
            printf("\n");

            printf("%X: %u\n", usb_BulkTransfer(global->out, (uint8_t *)rdy_pkt_01, sizeof(rdy_pkt_01), 0, &length), length);

            printf("%X: ", usb_BulkTransfer(global->in, buffer, sizeof(buffer), 0, &length));
            if (length <= sizeof(buffer))
                putBlockHex(buffer, length);
            else
                printf("%u", length);
            printf("\n");

            break;
    }
    goto noerr;
 err:
    printf("error: %X\n", error);
 noerr:
    if (configuration) free(configuration);
    memset(global, 0, sizeof(global_t));
}

int main(void) {
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
            printf("%06X: %08" PRIX32 " ", usb_GetFrameNumber(), usb_GetCycleCounter());
            os_SetCursorPos(row, col);
            handleDevice(&global);
        }
    }
    usb_Cleanup();
    printf("error: %X", error);
    os_GetKey();
}
