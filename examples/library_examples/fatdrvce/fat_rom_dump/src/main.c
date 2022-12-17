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

#define ROM_FILE_FILE "ROMDUMP.ROM"
#define ROM_FILE_PATH "/"
#define ROM_FILE_FILE_PATH ROM_FILE_PATH ROM_FILE_FILE
#define ROM_BUFFER_SIZE (MSD_BLOCK_SIZE * 4)
#define ROM_BUFFER_NUM_BLOCKS (ROM_BUFFER_SIZE / MSD_BLOCK_SIZE)

//#define ROM_FILE_SIZE ROM_BUFFER_SIZE
#define ROM_FILE_SIZE (1024 * 1024 * 4)

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
    static msd_partition_t partitions[MAX_PARTITIONS];
    static global_t global;
    static fat_t fat;
    uint8_t num_partitions;
    msd_info_t msdinfo;
    usb_error_t usberr;
    msd_error_t msderr;
    fat_error_t faterr;
    fat_file_t file;

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

    putstr("press enter to dump rom!");
    while (!os_GetCSC());

    os_ClrHome();

    putstr("allocating rom file");
    putstr(" - please wait...");

    // create the rom file, deleting it if it exists first
    fat_Delete(&fat, ROM_FILE_FILE_PATH);
    faterr = fat_Create(&fat, ROM_FILE_PATH, ROM_FILE_FILE, 0);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not create file!");
        goto fat_error;
    }

    // open rom file for writing
    faterr = fat_OpenFile(&fat, ROM_FILE_FILE_PATH, 0, &file);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not open file!");
        goto fat_error;
    }

    // set the size of the rom file
    faterr = fat_SetFileSize(&file, ROM_FILE_SIZE);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not set file size!");
        goto fat_error;
    }

    putstr("writing rom file");
    putstr(" - please wait...");

    // write the rom file, starting at the memory base address
    // dma only works from ram, so copy to a temporary buffer
    for (uintptr_t i = 0; i < ROM_FILE_SIZE; i += ROM_BUFFER_SIZE)
    {
        uint24_t count;

        memcpy(rombuffer, (const void *)i, ROM_BUFFER_SIZE);
        count = fat_WriteFile(&file, ROM_BUFFER_NUM_BLOCKS, rombuffer);
        if (count != ROM_BUFFER_NUM_BLOCKS)
        {
            putstr("error writing!");
            goto fat_error;
        }
    }

    putstr("validate rom file");
    putstr(" - please wait...");

    // rewind the file back to the beginning
    fat_SetFileBlockOffset(&file, 0);

    // verify the rom file, starting at the memory base address
    // dma only works from ram, so copy to a temporary buffer
    for (uintptr_t i = 0; i < ROM_FILE_SIZE; i += ROM_BUFFER_SIZE)
    {
        uint24_t count;

        count = fat_ReadFile(&file, ROM_BUFFER_NUM_BLOCKS, rombuffer);
        if (count != ROM_BUFFER_NUM_BLOCKS)
        {
            putstr("error reading!");
            goto fat_error;
        }

        if (memcmp(rombuffer, (const void *)i, ROM_BUFFER_SIZE) != 0)
        {
            putstr("validation error!");
            goto fat_error;
        }
    }

    // close the file
    faterr = fat_CloseFile(&file);
    if (faterr != FAT_SUCCESS)
    {
        putstr("could not close file!");
        goto fat_error;
    }

    putstr("dumped rom!");
    putstr("filename: " ROM_FILE_FILE_PATH);

fat_error:
    // close the filesystem
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
