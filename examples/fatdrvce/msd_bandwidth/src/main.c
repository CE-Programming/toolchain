typedef struct global global_t;
#define usb_callback_data_t global_t

#include <usbdrvce.h>
#include <fatdrvce.h>
#include <tice.h>

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECTORS_PER_ACCESS 16
#define NUM_ACCESSES 64
#define MAX_ENTRIES 10

enum { USB_RETRY_INIT = USB_USER_ERROR };

struct global
{
    usb_device_t usb;
    msd_t msd;
};

static void putstr(char *str)
{
    os_PutStrFull(str);
    os_NewLine();
}

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *global)
{
    switch (event)
    {
        case USB_DEVICE_DISCONNECTED_EVENT:
            putstr("usb device disconnected");
            if (global->usb)
                msd_Close(&global->msd);
            global->usb = NULL;
            break;
        case USB_DEVICE_CONNECTED_EVENT:
            putstr("usb device connected");
            return usb_ResetDevice(event_data);
        case USB_DEVICE_ENABLED_EVENT:
            putstr("usb device enabled");
            global->usb = event_data;
            break;
        case USB_DEVICE_DISABLED_EVENT:
            putstr("usb device disabled");
            return USB_RETRY_INIT;
        default:
            break;
    }

    return USB_SUCCESS;
}

void read_callback(msd_error_t error, struct msd_transfer_t *xfer)
{
    if (error != MSD_SUCCESS)
    {
        putstr("error completing read");
    }

    *(uint8_t*)xfer->userptr = 1;
}

int main(void)
{
    static uint8_t msd_buffer[MSD_BLOCK_SIZE * NUM_SECTORS_PER_ACCESS];
    static char buffer[200];
    static global_t global;
    static uint8_t done;
    uint32_t sector_size;
    uint32_t sector_num;
    float elapsed;
    float bps;
    usb_error_t usberr;
    msd_error_t msderr;
    msd_transfer_t xfer;
    int i;

    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);

    // usb initialization loop; waits for something to be plugged in
    do
    {
        global.usb = NULL;

        usberr = usb_Init(handleUsbEvent, &global, NULL, USB_DEFAULT_INIT_FLAGS);
        if (usberr != USB_SUCCESS)
        {
            putstr("usb init error.");
            goto error;
        }

        while (usberr == USB_SUCCESS)
        {
            if (global.usb != NULL)
                break;

            // break out if a key is pressed
            if (os_GetCSC())
            {
                putstr("exiting demo, press a key");
                goto error;
            }

            usberr = usb_WaitForInterrupt();
        }
    } while (usberr == USB_RETRY_INIT);

    if (usberr != USB_SUCCESS)
    {
        putstr("usb enable error.");
        goto error;
    }

    // initialize the msd device
    msderr = msd_Open(&global.msd, global.usb);
    if (msderr != MSD_SUCCESS)
    {
        putstr("failed opening msd");
        goto error;
    }

    putstr("detected drive");

    // get sector number and size
    msderr = msd_Info(&global.msd, &sector_num, &sector_size);
    if (msderr != MSD_SUCCESS)
    {
        putstr("error getting msd info");
        msd_Close(&global.msd);
        goto error;
    }

    // print msd sector number and size
    sprintf(buffer, "sector size: %u", (uint24_t)sector_size);
    putstr(buffer);
    sprintf(buffer, "num sectors: %u", (uint24_t)sector_num);
    putstr(buffer);

    memset(msd_buffer, 0xAA, sizeof msd_buffer);

    // attempt a read
    done = 0;
    xfer.msd = &global.msd;
    xfer.lba = 0;
    xfer.buffer = msd_buffer;
    xfer.count = 1;
    xfer.callback = read_callback;
    xfer.userptr = &done;

    msderr = msd_ReadAsync(&xfer);
    if (msderr != MSD_SUCCESS)
    {
        putstr("error issuing read");
        msd_Close(&global.msd);
        goto error;
    }

    do
    {
        usberr = usb_HandleEvents();
    } while (done == 0 && usberr == USB_SUCCESS);

    putstr("sector read success");

    // close the msd device
    msd_Close(&global.msd);

    // cleanup and return
    usb_Cleanup();
    os_GetKey();
    return 0;

error:
    usb_Cleanup();
    os_GetKey();
    return -1;
}
