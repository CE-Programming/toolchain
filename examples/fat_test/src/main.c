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
    usb_device_t device;
};

static uint8_t msd_buffer[512];

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data) {

    switch (event) {
        case USB_DEVICE_DISCONNECTED_EVENT:
            callback_data->device = NULL;
            os_PutStrFull("usb device disconnected");
            _OS(asm_NewLine);
            break;
        case USB_DEVICE_ENABLED_EVENT:
            callback_data->device = event_data;
            os_PutStrFull("usb device enabled");
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
    msd_device_t msd;
    bool msd_inited = false;
    uint24_t sectorsize;
    static char buffer[212];

    memset(&msd, 0, sizeof msd);
    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);

    error = usb_Init(handleUsbEvent, &global, NULL, USB_DEFAULT_INIT_FLAGS);
    if (error != USB_SUCCESS) {
        return;
    }

    do {

        // check for any usb events
        error = usb_WaitForInterrupt();
        if (error != USB_SUCCESS) {
            break;
        }

        // if a device is plugged, initialize it
        if (!msd_inited && global.device) {

            // initialize the msd device
            error = msd_Init(&msd, global.device, msd_buffer);
            if (error == USB_SUCCESS) {
                os_PutStrFull("inited msd");
                _OS(asm_NewLine);
                msd_inited = true;
                break;
            } else {
                sprintf(buffer, "init msd fail: %u", error);
                os_PutStrFull(buffer);
                _OS(asm_NewLine);
                break;
            }
        }

    } while (!os_GetCSC());

    // return if msd could not be configured
    if (!msd_inited) {
        usb_Cleanup();
        os_GetKey();
        return;
    }

    // print the sector size
    error = msd_GetSectorSize(&msd, &sectorsize);
    if( error == USB_SUCCESS )
    {
        sprintf(buffer, "sectorsize: %u", sectorsize);
        os_PutStrFull(buffer);
        _OS(asm_NewLine);
    }

    // cleanup and return
    usb_Cleanup();
    os_GetKey();
}
