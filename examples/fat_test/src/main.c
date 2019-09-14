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

#define MAX_PARTITIONS 10

void putstr(char *str);

struct global {
    usb_device_t device;
};

static uint8_t msd_buffer[512];
static uint8_t read_buffer[512];
static fat_partition_t fatpartitions[MAX_PARTITIONS];

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data) {

    switch (event) {
        case USB_DEVICE_DISCONNECTED_EVENT:
            callback_data->device = NULL;
            putstr("usb device disconnected");
            break;
        case USB_DEVICE_ENABLED_EVENT:
            callback_data->device = event_data;
            putstr("usb device enabled");
            break;
        default:
            break;
    }

    return USB_SUCCESS;
}

void main(void) {
    static global_t global;
    usb_error_t error;
    static msd_device_t msd;
    static fat_t fat;
    bool msd_inited = false;
    uint24_t sectorsize;
    uint8_t numpartitions;
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
                putstr("inited msd");
                msd_inited = true;
                break;
            } else {
                sprintf(buffer, "init msd fail: %u", error);
                putstr(buffer);
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

    // get sector size
    error = msd_GetSectorSize(&msd, &sectorsize);

    if( error == USB_SUCCESS )
    {
        sprintf(buffer, "sectorsize: %u", sectorsize);
        putstr(buffer);

        // find available fat partitions
dbg_Debugger();
        error = fat_Find(&msd, &fatpartitions, &numpartitions, MAX_PARTITIONS);
    }

    // attempt fat init on first fat32 partition
    if( error == USB_SUCCESS && numpartitions > 0 )
    {
        sprintf(buffer, "num fat partition: %u", numpartitions);
        putstr(buffer);

        // attempt init of fat partition
dbg_Debugger();
        error = fat_Init(&fat, &fatpartitions[0]);
    }

    if( error == USB_SUCCESS )
    {
        putstr("inited fat filesystem");
    }


    // cleanup and return
    usb_Cleanup();
    os_GetKey();
}

void putstr(char *str) {
    os_PutStrFull(str);
    _OS(asm_NewLine);
}

