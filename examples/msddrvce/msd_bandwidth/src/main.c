typedef struct global global_t;
#define usb_callback_data_t global_t

#include <usbdrvce.h>
#include <msddrvce.h>
#include <tice.h>

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_COUNT  16
#define NUM_TIMES    64
#define MAX_ENTRIES  10

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

int main(void)
{
    static uint8_t msd_buffer[MSD_BLOCK_SIZE * BLOCK_COUNT];
    static char buffer[212];
    static global_t global;
    float elapsed;
    float bps;
    uint24_t count;
    msd_info_t msdinfo;
    usb_error_t usberr;
    msd_error_t msderr;
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

    // get block count and size
    msderr = msd_Info(&global.msd, &msdinfo);
    if (msderr != MSD_SUCCESS)
    {
        putstr("error getting msd info");
        msd_Close(&global.msd);
        goto error;
    }

    // print msd sector number and size
    sprintf(buffer, "block size: %u bytes", (uint24_t)msdinfo.bsize);
    putstr(buffer);
    sprintf(buffer, "num blocks: %u", (uint24_t)msdinfo.bnum);
    putstr(buffer);
    putstr("executing speed test");
    putstr("please wait...");

    timer_Disable(1);
    timer_Set(1, 0);
    timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_UP);

    for (i = 0; i < NUM_TIMES; ++i)
    {
        count = msd_Write(&global.msd, i, BLOCK_COUNT, msd_buffer);
        if (count != BLOCK_COUNT)
        {
            putstr("error writing to msd");
            msd_Close(&global.msd);
            goto error;
        }
    }

    elapsed = (float)timer_GetSafe(1, TIMER_UP) / 32768.0;
    bps = (MSD_BLOCK_SIZE * BLOCK_COUNT * NUM_TIMES) / elapsed;

    sprintf(buffer, "write bytes/sec: %u", (unsigned int)bps);
    putstr(buffer);

    timer_Disable(1);
    timer_Set(1, 0);
    timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_UP);

    for (i = 0; i < NUM_TIMES; ++i)
    {
        count = msd_Read(&global.msd, i, BLOCK_COUNT, msd_buffer);
        if (count != BLOCK_COUNT)
        {
            putstr("error reading from msd");
            msd_Close(&global.msd);
            goto error;
        }
    }

    elapsed = (float)timer_GetSafe(1, TIMER_UP) / 32768.0;
    bps = (MSD_BLOCK_SIZE * BLOCK_COUNT * NUM_TIMES) / elapsed;

    sprintf(buffer, "read bytes/sec: %u", (unsigned int)bps);
    putstr(buffer);

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
