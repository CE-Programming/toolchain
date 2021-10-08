typedef struct global global_t;
#define usb_callback_data_t global_t
#define fat_callback_data_t msd_t

#include <usbdrvce.h>
#include <msddrvce.h>
#include <fatdrvce.h>
#include <tice.h>

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ROM_DUMP_SIZE (1024 * 1024 * 4)
#define ROM_DUMP_FILE "ROMDUMP.ROM"
#define ROM_DUMP_PATH "/"
#define ROM_DUMP_NAME ROM_DUMP_PATH ROM_DUMP_FILE
#define ROM_BUFFER_SIZE (MSD_BLOCK_SIZE * 4)

struct global
{
    usb_device_t usb;
    msd_t msd;
};

enum { USB_RETRY_INIT = USB_USER_ERROR };

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
            global->usb = event_data;
            putstr("usb device enabled");
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
    static uint8_t rombuffer[ROM_BUFFER_SIZE];
    static char buffer[212];
    static msd_partition_t partitions[4];
    static global_t global;
    static fat_t fat;
    uint8_t count;
    msd_info_t msdinfo;
    usb_error_t usberr;
    msd_error_t msderr;
    fat_error_t faterr;
    fat_file_t file;
    uintptr_t i;

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

    putstr("opened msd");

    // get block count and size
    msderr = msd_Info(&global.msd, &msdinfo);
    if (msderr != MSD_SUCCESS)
    {
        putstr("error getting msd info");
        msd_Close(&global.msd);
        goto msd_error;
    }

    // print msd sector number and size
    sprintf(buffer, "block size: %u bytes", (uint24_t)msdinfo.bsize);
    putstr(buffer);
    sprintf(buffer, "num blocks: %u", (uint24_t)msdinfo.bnum);
    putstr(buffer);

    // locate the first fat partition available
    count = msd_FindPartitions(&global.msd, partitions, 4);
    if (count < 1)
    {
        putstr("no paritions found");
        goto msd_error;
    }

    // attempt to open the first fat partition
    // it is not required to use a MSD to access a FAT filesystem if the
    // appropriate callbacks are configured.
    fat.read = &msd_Read;
    fat.write = &msd_Write;
    fat.usr = &global.msd;
    fat.lba = partitions[0].lba;
    fat.count = partitions[0].count;
    faterr = fat_Init(&fat);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not open partition");
        goto msd_error;
    }

    putstr("opened fat partition");
    putstr("creating dump file...");

    // create the rom dump file, deleting it if it exists first
    fat_Delete(&fat, ROM_DUMP_NAME);
    faterr = fat_Create(&fat, ROM_DUMP_PATH, ROM_DUMP_FILE, FAT_FILE);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not create file");
        goto fat_error;
    }

    putstr("writing dump file...");

    // open dump file for writing
    faterr = fat_Open(&file, &fat, ROM_DUMP_NAME);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not open file");
        goto fat_error;
    }

    // set the size of the rom dump
    faterr = fat_SetSize(&file, 4096);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not set file size");
        goto fat_error;
    }

    // write the rom file, starting at the memory base address
    // dma only works from ram, so copy to a temporary buffer
    for (i = 0; i < ROM_DUMP_SIZE; i += ROM_BUFFER_SIZE)
    {
        memcpy(rombuffer, (const void *)i, ROM_BUFFER_SIZE);
    }

    // close the file
    faterr = fat_Close(&file);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not close file");
        goto fat_error;
    }

    putstr("dumped rom!");

fat_error:
    // close the filesystem
    fat_Deinit(&fat);

msd_error:
    // close the msd device
    msd_Close(&global.msd);

    // cleanup and return
error:
    usb_Cleanup();
    while (!os_GetCSC());

    return 0;
}
