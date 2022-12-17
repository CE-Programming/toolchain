typedef struct global global_t;
#define usb_callback_data_t global_t
#define fat_callback_usr_t msd_t

#include <usbdrvce.h>
#include <msddrvce.h>
#include <fatdrvce.h>
#include <tice.h>

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTITIONS 32
#define FAT_BUFFER_SIZE (FAT_BLOCK_SIZE / sizeof(uint16_t))

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
    static msd_partition_t partitions[MAX_PARTITIONS];
    static char buffer[212];
    static global_t global;
    static fat_t fat;
    uint8_t num_partitions;
    msd_info_t msdinfo;
    usb_error_t usberr;
    msd_error_t msderr;
    fat_error_t faterr;

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
            goto usb_error;
        }

        while (usberr == USB_SUCCESS)
        {
            if (global.usb != NULL)
                break;

            // break out if a key is pressed
            if (os_GetCSC())
            {
                putstr("exiting demo, press a key");
                goto usb_error;
            }

            usberr = usb_WaitForInterrupt();
        }
    } while (usberr == USB_RETRY_INIT);
   
    if (usberr != USB_SUCCESS)
    {
        putstr("usb enable error.");
        goto usb_error;
    }

    // initialize the msd device
    msderr = msd_Open(&global.msd, global.usb);
    if (msderr != MSD_SUCCESS)
    {
        putstr("failed opening msd");
        goto usb_error;
    }

    putstr("opened msd");

    // get block count and size
    msderr = msd_Info(&global.msd, &msdinfo);
    if (msderr != MSD_SUCCESS)
    {
        putstr("error getting msd info");
        goto msd_error;
    }

    // print msd sector number and size
    sprintf(buffer, "block size: %u bytes", (uint24_t)msdinfo.bsize);
    putstr(buffer);
    sprintf(buffer, "num blocks: %u", (uint24_t)msdinfo.bnum);
    putstr(buffer);

    // locate the first fat partition available
    num_partitions = msd_FindPartitions(&global.msd, partitions, MAX_PARTITIONS);
    if (num_partitions < 1)
    {
        putstr("no paritions found");
        goto msd_error;
    }

    // attempt to open the first found fat partition
    // it is not required to use a MSD to access a FAT filesystem if the
    // appropriate callbacks are configured.
    for (uint8_t p = 0;;)
    {
        uint32_t base_lba = partitions[p].first_lba;
        fat_callback_usr_t *usr = &global.msd;
        fat_read_callback_t read = &msd_Read;
        fat_write_callback_t write = &msd_Write;

        faterr = fat_Open(&fat, read, write, usr, base_lba);
        if (faterr == FAT_SUCCESS)
        {
            sprintf(buffer, "opened fat partition %u", p - 1);
            putstr(buffer);
            break;
        }

        p++;
        if (p >= num_partitions)
        {
            putstr("no suitable patitions");
            goto msd_error;
        }
    }

    os_ClrHome();

    // attempt to create and open/edit a variety of files
    {
        static fat_dir_entry_t entry;
        static uint16_t fatbuffer[FAT_BUFFER_SIZE];
        static const char *str = "/FATTEST/DIR1/FILE.TXT";
        static fat_file_t file;
        static fat_dir_t dir;
        uint24_t count;

        putstr("inited fat filesystem");

        // create some directories and files
        fat_Create(&fat, "/", "FATTEST", FAT_DIR);
        fat_Create(&fat, "/FATTEST", "DIR1", FAT_DIR);
        fat_Create(&fat, "/FATTEST", "DIR2", FAT_DIR);
        fat_Create(&fat, "/FATTEST", "DIR3", FAT_DIR);

        fat_Create(&fat, "/FATTEST/DIR1", "FILE.TXT", 0);
        fat_Create(&fat, "/FATTEST/DIR2", "FILE1.TXT", 0);
        fat_Create(&fat, "/FATTEST/DIR2", "FILE2.TXT", 0);

        putstr("created files");

        // change the file size to test cluster allocation
        faterr = fat_OpenFile(&fat, str, 0, &file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not open file");
            goto fat_error;
        }

        faterr = fat_SetFileSize(&file, 512 * 1024);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not set file size");
            goto fat_error;
        }

        faterr = fat_SetFileSize(&file, 0);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not set file size");
            goto fat_error;
        }

        faterr = fat_SetFileSize(&file, 512 * 32);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not set file size");
            goto fat_error;
        }

        faterr = fat_CloseFile(&file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("file close error");
            goto fat_error;
        }

        // change the size of the other files
        faterr = fat_OpenFile(&fat, "/FATTEST/DIR2/FILE1.TXT", 0, &file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not open file");
            goto fat_error;
        }

        faterr = fat_SetFileSize(&file, 512 * 2 + 16);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not set file size");
            goto fat_error;
        }

        faterr = fat_CloseFile(&file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("file close error");
            goto fat_error;
        }

        faterr = fat_OpenFile(&fat, "/FATTEST/DIR2/FILE2.TXT", 0, &file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not open file");
            goto fat_error;
        }

        fat_SetFileSize(&file, 512 * 2 + 32);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not set file size");
            goto fat_error;
        }

        faterr = fat_CloseFile(&file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("file close error");
            goto fat_error;
        }

        putstr("set file sizes");

        // should not delete, nonempty directory
        fat_Delete(&fat, "/FATTEST/DIR2");

        // should delete, empty directory
        fat_Delete(&fat, "/FATTEST/DIR3");

        putstr("deleted files");

        // get directory contents
        faterr = fat_OpenDir(&fat, "/FATTEST/DIR2", &dir);
        if (faterr != FAT_SUCCESS)
        {
            putstr("file dir open error");
            goto fat_error;
        }

        count = 0;

        for (;;)
        {
            faterr = fat_ReadDir(&dir, &entry);
            if (faterr != FAT_SUCCESS)
            {
                putstr("file dir read error");
                goto fat_error;
            }

            if (entry.name[0] == 0)
            {
                break;
            }

            count++;
        }

        sprintf(buffer, "num dir entries: %d", count);
        putstr(buffer);

        fat_CloseDir(&dir);

        // delete file
        fat_Delete(&fat, "/FATTEST/DIR2/FILE2.TXT");

        // write bytes to file
        faterr = fat_OpenFile(&fat, str, 0, &file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not open file");
            goto fat_error;
        }

        for (uint8_t i = 0; i < 32; ++i)
        {
            uint24_t offset;

            offset = i * FAT_BUFFER_SIZE;
            for (uint24_t j = offset; j < offset + FAT_BUFFER_SIZE; ++j)
            {
                fatbuffer[j - offset] = j;
            }

            count = fat_WriteFile(&file, 1, fatbuffer);
            if (count != 1)
            {
                putstr("write error");
                goto fat_error;
            }
        }

        putstr("wrote file bytes");

        // read back file, and compare read to written bytes
        faterr = fat_SetFileBlockOffset(&file, 0);
        if (faterr != FAT_SUCCESS)
        {
            putstr("could not set position");
            goto fat_error;
        }

        for (uint8_t i = 0; i < 32; ++i)
        {
            uint24_t offset;

            offset = i * FAT_BUFFER_SIZE;

            count = fat_ReadFile(&file, 1, fatbuffer);
            if (count != 1)
            {
                putstr("read error");
                goto fat_error;
            }

            for (uint24_t j = offset; j < offset + FAT_BUFFER_SIZE; ++j)
            {
                if (fatbuffer[j - offset] != j)
                {
                    putstr("read does not match!");
                    goto fat_error;
                }
            }
        }

        putstr("read back file bytes");

        // check if end of file -- should return 0
        count = fat_ReadFile(&file, 1, fatbuffer);
        if (count != 0)
        {
            putstr("file read error");
            goto fat_error;
        }

        // close the fat file
        faterr = fat_CloseFile(&file);
        if (faterr != FAT_SUCCESS)
        {
            putstr("file close error");
            goto fat_error;
        }

         putstr("end of test!");
    }


fat_error:
    // release the filesystem
    fat_Close(&fat);

msd_error:
    // close the msd device
    msd_Close(&global.msd);

usb_error:
    // cleanup usb
    usb_Cleanup();

    while (!os_GetCSC());

    return 0;
}
