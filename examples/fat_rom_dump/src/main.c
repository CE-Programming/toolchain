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

#define ROM_DUMP_SIZE (1024 * 1024 * 4)
#define MAX_PARTITIONS 10
#define ROM_DUMP_FILE "ROMDUMP.ROM"
#define ROM_DUMP_PATH "/"
#define ROM_DUMP_NAME ROM_DUMP_PATH ROM_DUMP_FILE
#define ROM_BUFFER_SIZE (MSD_SECTOR_SIZE * 64)

static uint8_t rombuffer[ROM_BUFFER_SIZE];
void putstr(char *str);

struct global
{
    usb_device_t device;
};

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data)
{

    switch (event)
    {
        case USB_DEVICE_DISCONNECTED_EVENT:
            callback_data->device = NULL;
            putstr("usb device disconnected");
            break;
        case USB_DEVICE_CONNECTED_EVENT:
            usb_ResetDevice(event_data);
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

void main(void)
{
    static uint8_t msd_buffer[MSD_SECTOR_SIZE];
    static fat_partition_t fatpartitions[MAX_PARTITIONS];
    static global_t global;
    static msd_device_t msd;
    static fat_t fat;
    bool msd_inited = false;
    uint8_t numpartitions;
    usb_error_t usberror = USB_ERROR_INVALID_PARAM;
    msd_error_t msderror = MSD_ERROR_INVALID_PARAM;
    fat_error_t faterror = FAT_ERROR_INVALID_PARAM;

    memset(&msd, 0, sizeof msd);
    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);

    usberror = usb_Init(handleUsbEvent, &global, NULL, USB_DEFAULT_INIT_FLAGS);
    if (usberror != USB_SUCCESS)
    {
        return;
    }

    do
    {

        // check for any usb events
        usberror = usb_WaitForInterrupt();
        if (usberror != USB_SUCCESS)
        {
            break;
        }

        // if a device is plugged, initialize it
        if (!msd_inited && global.device)
        {

            // initialize the msd device
            msderror = msd_Init(&msd, global.device, msd_buffer);
            if (msderror == MSD_SUCCESS)
            {
                msd_inited = true;
            }
            break;
        }

    } while (!os_GetCSC());

    // return if msd could not be configured
    if (!msd_inited)
    {
        putstr("invalid drive.");
        usb_Cleanup();
        os_GetKey();
        return;
    }

    // locate partitions
    faterror = fat_Find(&msd, &fatpartitions, &numpartitions, MAX_PARTITIONS);

    // attempt fat init on first fat32 partition
    if (faterror == FAT_SUCCESS && numpartitions > 0)
    {
        // attempt init of first fat partition
        faterror = fat_Init(&fat, &fatpartitions[0]);
    }

    // attempt to create a file
    if (faterror == FAT_SUCCESS)
    {
        fat_file_t *file;
        uintptr_t i;

        putstr("creating dump file...");

        // create the rom dump file, deleting it if it exists first
        fat_Delete(&fat, ROM_DUMP_NAME);
        fat_Create(&fat, ROM_DUMP_PATH, ROM_DUMP_FILE, FAT_FILE);

        // set the size of the rom dump
        fat_SetSize(&fat, ROM_DUMP_NAME, ROM_DUMP_SIZE);

        putstr("writing dump file...");

        // open dump file for writing
        file = fat_Open(&fat, ROM_DUMP_NAME, FAT_O_RDWR);

        // write the rom file, starting at the memory base address
        // dma only works from ram, so copy to a temporary buffer
        for (i = 0; i < ROM_DUMP_SIZE; i += ROM_BUFFER_SIZE)
        {
                memcpy(rombuffer, (const void *)i, ROM_BUFFER_SIZE);
                fat_WriteSectors(file, ROM_BUFFER_SIZE / MSD_SECTOR_SIZE, rombuffer);
        }

        // close the file
        faterror = fat_Close(file);

        // close the filesystem
        fat_Deinit(&fat);
    }

    if( faterror == USB_SUCCESS )
    {
        putstr("dumped rom!");
    }
    else
    {
        putstr("a fatal error occurred.");
    }

    // cleanup and return
    usb_Cleanup();
    os_GetKey();
}

void putstr(char *str) {
    os_PutStrFull(str);
    _OS(asm_NewLine);
}
