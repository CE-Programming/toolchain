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

#define MAX_PARTITIONS 255

enum { USB_RETRY_INIT = USB_USER_ERROR };

struct global
{
    usb_device_t usb;
    msd_t msd;
};

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *global)
{
    switch (event)
    {
        case USB_DEVICE_DISCONNECTED_EVENT:
            puts("usb device disconnected");
            if (global->usb)
                msd_Close(&global->msd);
            global->usb = NULL;
            break;
        case USB_DEVICE_CONNECTED_EVENT:
            puts("usb device connected");
            return usb_ResetDevice(event_data);
        case USB_DEVICE_ENABLED_EVENT:
            puts("usb device enabled");
            global->usb = event_data;
            break;
        case USB_DEVICE_DISABLED_EVENT:
            puts("usb device disabled");
            return USB_RETRY_INIT;
        default:
            break;
    }

    return USB_SUCCESS;
}

int main(void)
{
    static msd_partition_t partitions[MAX_PARTITIONS];
    static global_t global;
    uint8_t num_partitions;
    msd_info_t msdinfo;
    usb_error_t usberr;
    msd_error_t msderr;

    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);

    // usb initialization loop; waits for something to be plugged in
    do
    {
        global.usb = NULL;

        usberr = usb_Init(handleUsbEvent, &global, NULL, USB_DEFAULT_INIT_FLAGS);
        if (usberr != USB_SUCCESS)
        {
            puts("usb init error.");
            goto error;
        }

        while (usberr == USB_SUCCESS)
        {
            if (global.usb != NULL)
                break;

            // break out if a key is pressed
            if (os_GetCSC())
            {
                puts("exiting demo, press a key");
                goto error;
            }

            usberr = usb_WaitForInterrupt();
        }
    } while (usberr == USB_RETRY_INIT);

    if (usberr != USB_SUCCESS)
    {
        puts("usb enable error.");
        goto error;
    }

    // initialize the msd device
    msderr = msd_Open(&global.msd, global.usb);
    if (msderr != MSD_SUCCESS)
    {
        puts("failed opening msd");
        goto error;
    }

    puts("detected drive");

    // get block count and size
    msderr = msd_Info(&global.msd, &msdinfo);
    if (msderr != MSD_SUCCESS)
    {
        puts("error getting msd info");
        msd_Close(&global.msd);
        goto error;
    }

    // print msd sector number and size
    printf("block size: %u bytes\n", (uint24_t)msdinfo.bsize);
    printf("num blocks: %u\n", (uint24_t)msdinfo.bnum);

    num_partitions = msd_FindPartitions(&global.msd, partitions, MAX_PARTITIONS);

    printf("num paritions: %u\n", num_partitions);

    for (uint8_t i = 0; i < num_partitions; ++i)
    {
    	uint32_t first_lba = partitions[i].first_lba;
    	uint32_t last_lba = partitions[i].last_lba;

	printf("%lu - %lu\n", first_lba, last_lba);
    }

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
