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

#define MAX_PARTITIONS 10
#define MAX_ENTRIES 10
#define FAT_BUFFER_SIZE (MSD_SECTOR_SIZE / sizeof(uint16_t))

void putstr(char *str);

struct global
{
    usb_device_t device;
};

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data) {

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

void main(void) {
    static uint8_t msd_buffer[MSD_SECTOR_SIZE];
    static fat_partition_t fatpartitions[MAX_PARTITIONS];
    static char buffer[212];
    static global_t global;
    static msd_device_t msd;
    static fat_t fat;
    uint32_t sector_size;
    uint32_t sector_num;
    uint8_t numpartitions;
    bool msd_inited = false;
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
                putstr("inited msd");
            }
            else
            {
                putstr("init msd fail");
            }
            break;
        }

    } while (!os_GetCSC());

    // return if msd could not be configured
    if (!msd_inited)
    {
        usb_Cleanup();
        os_GetKey();
        return;
    }

    // get sector size
    msderror = msd_Info(&msd, &sector_num, &sector_size);
    if (msderror == MSD_SUCCESS)
    {
        sprintf(buffer, "sector size: %u", (uint24_t)sector_size);
        putstr(buffer);
        sprintf(buffer, "sector num: %u", (uint24_t)sector_num);
        putstr(buffer);

        // find available fat partitions
        faterror = fat_Find(&msd, fatpartitions, &numpartitions, MAX_PARTITIONS);
    }

    // attempt fat init on first fat32 partition
    if (faterror == FAT_SUCCESS && numpartitions > 0)
    {
        sprintf(buffer, "num fat partition: %u", numpartitions);
        putstr(buffer);

        // attempt init of fat partition
        faterror = fat_Init(&fat, &fatpartitions[0]);
    }

    // attempt to open a file
    if (faterror == FAT_SUCCESS)
    {
        static fat_dir_entry_t entries[MAX_ENTRIES];
        static uint16_t fatbuffer[FAT_BUFFER_SIZE];
        static const char *str = "/FATTEST/DIR1/FILE.TXT";
        fat_file_t *file;
        uint24_t i;
        uint16_t j;
        int24_t count;

        putstr("inited fat filesystem");

        // create some directories and files
        fat_Create(&fat, "/", "FATTEST", FAT_DIR);
        fat_Create(&fat, "/FATTEST", "DIR1", FAT_DIR);
        fat_Create(&fat, "/FATTEST", "DIR2", FAT_DIR);
        fat_Create(&fat, "/FATTEST", "DIR3", FAT_DIR);

        fat_Create(&fat, "/FATTEST/DIR1", "FILE.TXT", FAT_FILE);
        fat_Create(&fat, "/FATTEST/DIR2", "FILE1.TXT", FAT_FILE);
        fat_Create(&fat, "/FATTEST/DIR2", "FILE2.TXT", FAT_FILE);

        // change the size of the first file
        fat_SetSize(&fat, str, 512 * 1024);
        fat_SetSize(&fat, str, 512 * 0);
        fat_SetSize(&fat, str, 512 * 32);

        // change the size of the other files
        fat_SetSize(&fat, "/FATTEST/DIR2/FILE1.TXT", 512 * 2 + 16);
        fat_SetSize(&fat, "/FATTEST/DIR2/FILE2.TXT", 512 * 2 + 32);

        // should not delete, nonempty directory
        fat_Delete(&fat, "/FATTEST/DIR2");

        // should delete, empty directory
        fat_Delete(&fat, "/FATTEST/DIR3");

        // get directory contents (should be 4)
        count = fat_DirList(&fat, "/FATTEST/DIR2", FAT_LIST_ALL,
                            entries, MAX_ENTRIES, 0);
        if (count >= 0)
        {
            sprintf(buffer, "num entries: %d", count);
            putstr(buffer);
        }

        // delete file
        fat_Delete(&fat, "/FATTEST/DIR2/FILE2.TXT");

        // write bytes to file
        file = fat_Open(&fat, str, FAT_O_RDWR);
        for (i = 0; i < 32; ++i)
        {
            uint24_t offset = i * FAT_BUFFER_SIZE;
            for (j = offset; j < offset + FAT_BUFFER_SIZE; ++j)
            {
                fatbuffer[j - offset] = j;
            }
            fat_WriteSectors(file, 1, fatbuffer);
        }

        // read back file, and compare read to written bytes
        fat_SetFilePos(file, 0);
        for (i = 0; i < 32; ++i)
        {
            uint24_t offset = i * FAT_BUFFER_SIZE;
            fat_ReadSectors(file, 1, fatbuffer);
            for (j = offset; j < offset + FAT_BUFFER_SIZE; ++j)
            {
                if (fatbuffer[j - offset] != j)
                {
                    putstr("read does not match!");
                    usb_Cleanup();
                    os_GetKey();
                    abort();
                }
            }
        }

        // verify that this read returns EOF
        faterror = fat_ReadSectors(file, 1, fatbuffer);
        if (faterror == FAT_ERROR_EOF)
        {
            putstr("detected eof.");
        }

        faterror = fat_Close(file);

        // close the filesystem
        fat_Deinit(&fat);
    }

    if( faterror == USB_SUCCESS )
    {
        putstr("success!");
    }

    // cleanup and return
    usb_Cleanup();
    os_GetKey();
}

void putstr(char *str) {
    os_PutStrFull(str);
    _OS(asm_NewLine);
}
