typedef struct global global_t;
#define usb_callback_data_t global_t

#include <usbdrvce.h>
#include <fatdrvce.h>

#include <debug.h>
#include <tice.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct global {
    bool valid_msd;
    msd_device_t msd;
    uint8_t buffer[512];
};

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data) {

    switch (event) {
        case USB_DEVICE_DISCONNECTED_EVENT:
            os_PutStrFull("USB_DEVICE_DISCONNECTED_EVENT");
            _OS(asm_NewLine);
            break;
        case USB_DEVICE_ENABLED_EVENT:
            os_PutStrFull("USB_DEVICE_ENABLED_EVENT");

            // check if mass storage device and configure if it is
            //if ((msd_IsMSD(event_data) == USB_SUCCESS)) {
            //    msd_SetupDevice(&global.msd, event_data, global.buffer);
            //}

            _OS(asm_NewLine);
            break;
        default:
            break;
    }

    return USB_SUCCESS;
}

void main(void) {
    global_t global;
    usb_error_t error;

    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);

    error = usb_Init(handleUsbEvent, NULL, NULL, USB_DEFAULT_INIT_FLAGS);
    if (error != USB_SUCCESS) {
        return;
    }

    while ((error = usb_WaitForInterrupt()) == USB_SUCCESS && !os_GetCSC()) {
        //handleDevice(&global);
    }

    usb_Cleanup();
}
