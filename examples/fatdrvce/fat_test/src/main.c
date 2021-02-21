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

struct global
{
    usb_device_t usb;
    msd_device_t msd;
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
            // close the usb device the msd was using
            msd_Close(&global->msd);
            global->usb = NULL;
            putstr("usb device disconnected");
            break;
        case USB_DEVICE_CONNECTED_EVENT:
            putstr("usb device connected");
            return usb_ResetDevice(event_data);
        case USB_DEVICE_ENABLED_EVENT:
            global->usb = event_data;
            putstr("usb device enabled");
            break;
        default:
            break;
    }

    return USB_SUCCESS;
}

int main(void)
{
    static uint8_t msd_buffer[MSD_SECTOR_SIZE];
    static fat_partition_t fatparts[MAX_PARTITIONS];
    static char buffer[212];
    static global_t global;
    static fat_t fat;
    uint32_t sector_size;
    uint32_t sector_num;
    uint8_t numparts;
    bool valid;
    usb_error_t usberr;
    msd_error_t msderr;
    fat_error_t faterr;

    memset(&global, 0, sizeof(global_t));
    valid = false;

    os_SetCursorPos(1, 0);

    usberr = usb_Init(handleUsbEvent, &global, NULL, USB_DEFAULT_INIT_FLAGS);
    if (usberr != USB_SUCCESS)
    {
        putstr("usb init error.");
        os_GetKey();
        return -1;
    }

    do
    {
        // check for any usb events
        usberr = usb_WaitForInterrupt();
        if (usberr != USB_SUCCESS)
        {
            putstr("usb library error.");
            os_GetKey();
            return -1;
        }

        // if a device is plugged in, initialize it
        if (!valid && global.usb != NULL)
        {
            // initialize the msd device
            msderr = msd_Open(&global.msd, global.usb, msd_buffer);
            if (msderr != MSD_SUCCESS)
            {
                putstr("failed opening msd");
                usb_Cleanup();
                os_GetKey();
                return -1;
            }

            putstr("opened msd");
            valid = true;
            break;
        }
    } while (!os_GetCSC());

    // get sector number and size
    msderr = msd_Info(&global.msd, &sector_num, &sector_size);
    if (msderr != MSD_SUCCESS)
    {
        putstr("error getting msd info");
        return -1;
    }

    // print msd sector number and size
    sprintf(buffer, "sector size: %u", (uint24_t)sector_size);
    putstr(buffer);
    sprintf(buffer, "sector num: %u", (uint24_t)sector_num);
    putstr(buffer);

    // find available fat partitions
    faterr = fat_FindPartitions(&global.msd, fatparts, &numparts, MAX_PARTITIONS);
    if (faterr != FAT_SUCCESS)
    {
        putstr("error finding fat partitions");
        return -1;
    }

    // verify there is at least one fat parition
    if (numparts == 0)
    {
        putstr("no fat paritions on device");
        return -1;
    }

    // print number of fat partitions
    sprintf(buffer, "num fat partition: %u", numparts);
    putstr(buffer);

    // attempt fat init on first fat partition
    faterr = fat_OpenPartition(&fat, &fatparts[0]);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not open fat partition");
        return -1;
    }

    os_ClrHome();

    // attempt to create and open/edit a variety of files
    if (faterr == FAT_SUCCESS)
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

        putstr("created files");

        // change the size of the first file
        fat_SetSize(&fat, str, 512 * 1024);
        fat_SetSize(&fat, str, 512 * 0);
        fat_SetSize(&fat, str, 512 * 32);

        // change the size of the other files
        fat_SetSize(&fat, "/FATTEST/DIR2/FILE1.TXT", 512 * 2 + 16);
        fat_SetSize(&fat, "/FATTEST/DIR2/FILE2.TXT", 512 * 2 + 32);

        putstr("set file sizes");

        // should not delete, nonempty directory
        fat_Delete(&fat, "/FATTEST/DIR2");

        // should delete, empty directory
        fat_Delete(&fat, "/FATTEST/DIR3");

        putstr("deleted files");

        // get directory contents (should be 4)
        count = fat_DirList(&fat, "/FATTEST/DIR2", FAT_LIST_ALL,
                            entries, MAX_ENTRIES, 0);
        if (count >= 0)
        {
            sprintf(buffer, "num dir entries: %d", count);
            putstr(buffer);
        }

        // delete file
        fat_Delete(&fat, "/FATTEST/DIR2/FILE2.TXT");

        // write bytes to file
        file = fat_Open(&fat, str, FAT_RDWR);
        for (i = 0; i < 32; ++i)
        {
            uint24_t offset = i * FAT_BUFFER_SIZE;
            for (j = offset; j < offset + FAT_BUFFER_SIZE; ++j)
            {
                fatbuffer[j - offset] = j;
            }
            fat_WriteSectors(file, 1, fatbuffer);
        }

        putstr("wrote file bytes");

        // read back file, and compare read to written bytes
        fat_SetPos(file, 0);
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

        putstr("read back file bytes");

        // check if end of file
        faterr = fat_ReadSectors(file, 1, fatbuffer);
        if (faterr == FAT_ERROR_EOF)
            putstr("detected eof");

        // close the file
        faterr = fat_Close(file);
        if (faterr == USB_SUCCESS)
            putstr("end of test!");

        // close the partition
        fat_ClosePartition(&fat);

        // close the msd device
        msd_Close(&global.msd);
    }

    // cleanup and return
    usb_Cleanup();
    os_GetKey();
}
