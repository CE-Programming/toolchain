#include "linklib.h"

#include <stdlib.h>
#include <string.h>

#define usb_transfer_data_t size_t
#include <usbdrvce.h>

#define DEFAULT_LANGID 0x0409

#ifndef LINKLIB_KEY
# warning Please add -DLINKLIB_KEY="\"<unique string>\"" to your makefile's CFLAGS
# define LINKLIB_KEY "LinkLib program compiled on " __DATE__ " at " __TIME__
#endif

static struct state {
    uint8_t pending;
    uint8_t allocated;
    link_devices_t devices;
} *state;

static const usb_string_descriptor_t key = {
    .bLength = sizeof(L"" LINKLIB_KEY),
    .bDescriptorType = USB_STRING_DESCRIPTOR,
    .bString = L"" LINKLIB_KEY,
};

static bool check_host_key(usb_device_t device, const usb_control_setup_t *setup) {
    static usb_string_descriptor_t check = { .bString = L"" LINKLIB_KEY };
    size_t transferred;
    return setup->wLength == key.bLength &&
        usb_DefaultControlTransfer(device, setup, &check,
                                   1, &transferred) == USB_SUCCESS &&
        transferred == key.bLength && !memcmp(&check, &key, key.bLength);
}

static bool check_device_key(usb_device_t device) {
    static usb_string_descriptor_t check = { .bString = L"" LINKLIB_KEY };
    size_t transferred;
    return usb_GetStringDescriptor(device, 1, DEFAULT_LANGID, &check,
                                   key.bLength, &transferred) == USB_SUCCESS &&
        transferred == key.bLength && !memcmp(&check, &key, key.bLength);
}

static usb_error_t set_configuration(usb_device_t device, uint8_t index) {
    usb_error_t error = USB_SUCCESS;
    size_t length = usb_GetConfigurationDescriptorTotalLength(device, index), transferred;
    usb_configuration_descriptor_t *descriptor = malloc(length);
    if (error == USB_SUCCESS && !descriptor)
        error = USB_ERROR_NO_MEMORY;
    if (error == USB_SUCCESS)
        error = usb_GetConfigurationDescriptor(device, index, descriptor, length, &transferred);
    if (error == USB_SUCCESS)
        error = usb_SetConfiguration(device, descriptor, transferred);
    free(descriptor);
    return error;
}

static usb_device_t find_device(uint8_t address) {
    usb_device_t device = NULL;
    while ((device = usb_FindDevice(NULL, device, USB_SKIP_HUBS | USB_SKIP_DISABLED)))
        if (usb_GetDeviceAddress(device) == address && usb_GetDeviceData(device))
            return device;
    return NULL;
}

static usb_error_t transfer_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                    size_t transferred, size_t *data) {
    (void)endpoint;
    *data = status == USB_TRANSFER_COMPLETED ? transferred : 0;
    if (state)
        --state->pending;
    return USB_SUCCESS;
}

static bool queue(uint8_t address, bool direction, void *buffer, size_t *length) {
    if (!state) {
        *length = 0;
        return false;
    }
    uint8_t endpoint = (((usb_GetRole() & USB_ROLE_DEVICE) == USB_ROLE_DEVICE) ^ direction
                        ? USB_DEVICE_TO_HOST : USB_HOST_TO_DEVICE) | 1;
    size_t buffer_length = *length;
    *length = LINK_PENDING;
    if (usb_ScheduleBulkTransfer(usb_GetDeviceEndpoint(find_device(address), endpoint),
                                 buffer, buffer_length, &transfer_handler, length)
        != USB_SUCCESS) {
        *length = 0;
        return false;
    }
    ++state->pending;
    return true;
}

static usb_error_t event_handler(usb_event_t event, void *data, void *unused) {
    static const usb_control_setup_t check_setup = {
        .bmRequestType = USB_HOST_TO_DEVICE | USB_VENDOR_REQUEST | USB_RECIPIENT_DEVICE,
        .bRequest = 0xFF,
        .wValue = 0,
        .wIndex = 0,
        .wLength = sizeof(L"" LINKLIB_KEY),
    };
    usb_error_t error = USB_SUCCESS;
    (void)unused;
    if (!state)
        return error;
    switch (event) {
        default:
            break;
        case USB_ROLE_CHANGED_EVENT: {
            usb_role_t *role = data;
            if ((*role & USB_ROLE_DEVICE) == USB_ROLE_HOST)
                state->devices.self = 0;
            break;
        }
        case USB_DEVICE_CONNECTED_EVENT: {
            usb_device_t device = data;
            if ((usb_GetRole() & USB_ROLE_DEVICE) == USB_ROLE_DEVICE)
                break;
            if (error == USB_SUCCESS)
                error = usb_ResetDevice(device);
            break;
        }
        case USB_DEVICE_DISABLED_EVENT: {
            usb_device_t device = data;
            usb_SetDeviceData(device, NULL);
            break;
        }
        case USB_DEVICE_ENABLED_EVENT: {
            size_t transferred;
            usb_device_t device = data;
            if ((usb_GetRole() & USB_ROLE_DEVICE) == USB_ROLE_DEVICE || !check_device_key(device))
                break;
            if (error == USB_SUCCESS)
                error = set_configuration(device, 0);
            if (error == USB_SUCCESS &&
                usb_DefaultControlTransfer(device, &check_setup, (void *)&key, 1, &transferred)
                == USB_SUCCESS && transferred == key.bLength)
                usb_SetDeviceData(device, state);
            break;
        }
        case USB_DEFAULT_SETUP_EVENT: {
            const usb_control_setup_t *setup = data;
            if ((usb_GetRole() & USB_ROLE_DEVICE) == USB_ROLE_HOST)
                break;
            usb_device_t device = usb_FindDevice(NULL, NULL, USB_SKIP_HUBS | USB_SKIP_DISABLED);
            if (error == USB_SUCCESS && setup->bmRequestType ==
                (USB_HOST_TO_DEVICE | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE) &&
                setup->bRequest == USB_SET_ADDRESS_REQUEST &&
                !setup->wIndex && !setup->wLength)
                state->devices.self = setup->wValue;
            else if (error == USB_SUCCESS && !memcmp(setup, &check_setup, sizeof(check_setup)) &&
                     check_host_key(device, setup)) {
                usb_SetDeviceData(device, state);
                error = USB_IGNORE;
            }
            break;
        }
    }
    return error;
}

__attribute__((destructor)) static void link_Cleanup(void) {
    if (state)
        usb_Cleanup();
    free(state);
    state = NULL;
}

__attribute__((constructor)) static void link_Init(void) {
    static const usb_string_descriptor_t *strings[] = { &key };
    static const usb_string_descriptor_t langids = {
        .bLength = sizeof(langids),
        .bDescriptorType = USB_STRING_DESCRIPTOR,
        .bString = {
            [0] = DEFAULT_LANGID,
        },
    };
    static struct {
        usb_configuration_descriptor_t configuration;
        struct {
            usb_interface_descriptor_t interface;
            usb_endpoint_descriptor_t endpoints[2];
        } interface0;
    } configuration1 = {
        .configuration = {
            .bLength = sizeof(configuration1.configuration),
            .bDescriptorType = USB_CONFIGURATION_DESCRIPTOR,
            .wTotalLength = sizeof(configuration1),
            .bNumInterfaces = 1,
            .bConfigurationValue = 1,
            .iConfiguration = 0,
            .bmAttributes = USB_BUS_POWERED | USB_NO_REMOTE_WAKEUP,
            .bMaxPower = 500 / 2,
        },
        .interface0 = {
            .interface = {
                .bLength = sizeof(configuration1.interface0.interface),
                .bDescriptorType = USB_INTERFACE_DESCRIPTOR,
                .bInterfaceNumber = 0,
                .bAlternateSetting = 0,
                .bNumEndpoints = sizeof(configuration1.interface0.endpoints) /
                                 sizeof(*configuration1.interface0.endpoints),
                .bInterfaceClass = USB_VENDOR_SPECIFIC_CLASS,
                .bInterfaceSubClass = 0,
                .bInterfaceProtocol = 0,
                .iInterface = 0,
            },
            .endpoints = {
                [0] = {
                    .bLength = sizeof(configuration1.interface0.endpoints[0]),
                    .bDescriptorType = USB_ENDPOINT_DESCRIPTOR,
                    .bEndpointAddress = USB_HOST_TO_DEVICE | 1,
                    .bmAttributes = USB_BULK_TRANSFER,
                    .wMaxPacketSize = 0x40,
                    .bInterval = 0,
                },
                [1] = {
                    .bLength = sizeof(configuration1.interface0.endpoints[1]),
                    .bDescriptorType = USB_ENDPOINT_DESCRIPTOR,
                    .bEndpointAddress = USB_DEVICE_TO_HOST | 1,
                    .bmAttributes = USB_BULK_TRANSFER,
                    .wMaxPacketSize = 0x40,
                    .bInterval = 0,
                },
            },
        },
    };
    static const usb_configuration_descriptor_t *configurations[] = {
        &configuration1.configuration,
    };
    static const usb_device_descriptor_t device = {
        .bLength = sizeof(device),
        .bDescriptorType = USB_DEVICE_DESCRIPTOR,
        .bcdUSB = 0x0200,
        .bDeviceClass = 0,
        .bDeviceSubClass = 0,
        .bDeviceProtocol = 0,
        .bMaxPacketSize0 = 0x40,
        .idVendor = 0x0451,
        .idProduct = 0xE008,
        .bcdDevice = 0x0220,
        .iManufacturer = 0,
        .iProduct = 0,
        .iSerialNumber = 0,
        .bNumConfigurations = sizeof(configurations) / sizeof(*configurations),
    };
    static const usb_standard_descriptors_t standard = {
        .device = &device,
        .configurations = configurations,
        .langids = &langids,
        .numStrings = sizeof(strings) / sizeof(*strings),
        .strings = strings,
    };

    state = malloc(sizeof(*state) + 1 * sizeof(*state->devices.ids));
    state->pending = 0;
    state->allocated = 1;
    state->devices.self = 0;
    state->devices.count = 0;

    if (!state || usb_Init(&event_handler, NULL, &standard, USB_DEFAULT_INIT_FLAGS) == USB_SUCCESS)
        return;

    free(state);
    state = NULL;
}

bool link_QueueRead(uint8_t device, void *buffer, size_t *length) {
    return queue(device, true, buffer, length);
}

bool link_QueueWrite(uint8_t device, const void *buffer, size_t *length) {
    return queue(device, false, (void *)buffer, length);
}

bool link_Poll(void) {
    if (!state)
        return false;
    if (usb_HandleEvents() == USB_SUCCESS)
        return state->pending;
    link_Cleanup();
    return false;
}

const link_devices_t *link_Devices(void) {
    link_Poll();
    if (!state) {
        static link_devices_t no_devices = {
            .self = 0,
            .count = 0,
            .ids = {},
        };
        return &no_devices;
    }

    usb_device_t device = NULL;
    state->devices.count = 0;
    while ((device = usb_FindDevice(NULL, device, USB_SKIP_HUBS | USB_SKIP_DISABLED))) {
        if (!usb_GetDeviceData(device))
            continue;
        if (state->devices.count == state->allocated) {
            struct state *new_state = realloc(
                    state, sizeof(*state) + (state->devices.count + 1) * sizeof(*state->devices.ids));
            if (!new_state)
                break;
            state = new_state;
        }
        state->devices.ids[state->devices.count++] = usb_GetDeviceAddress(device);
    }

    return &state->devices;
}
