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

static fat_t fat;
uint24_t file_count = 0;
uint24_t dir_count = 0;
fat_error_t scan_fat_files(char* path)
{
    fat_error_t faterr;
    fat_dir_entry_t entry;
    fat_dir_t dir;

    faterr = fat_OpenDir(&fat, path, &dir);
    if (faterr != FAT_SUCCESS)
    {
        printf("error code %d\n", faterr);
        return faterr;
    }

    for (;;)
    {
        faterr = fat_ReadDir(&dir, &entry);
        if (faterr != FAT_SUCCESS)
        {
            printf("error code %d", faterr);
            break;
        }

        /* end of entries */
        if (entry.name[0] == 0)
        {
            break;
        }

        if (entry.attrib & FAT_DIR)
        {
            /* don't show . and .. */
            if (entry.name[0] == '.')
            {
                continue;
            }

            size_t i = strlen(path);
            dir_count++;
            sprintf(&path[i], "/%s", entry.name);
            faterr = scan_fat_files(path);
            if (faterr != FAT_SUCCESS)
            {
                break;
            }

            path[i] = '\0';
        }
        else
        {
            printf("%s/%s\n", &path[1], entry.name);
            file_count++;
        }
    }

    fat_CloseDir(&dir);

    return faterr;
}

int main(void)
{
    static char buffer[212];
    static msd_partition_t partitions[MAX_PARTITIONS];
    static global_t global;
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

    char path[512];

    path[0] = '/';
    path[1] = '\0';

    faterr = scan_fat_files(path);
    if (faterr != FAT_SUCCESS)
    {
        putstr("error scanning tree");
        goto fat_error;
    }

    printf("file count: %u\n", file_count);
    printf("dir count: %u\n", dir_count);

/**
 * Gets the next directory entry.
 * @param dir[in] Initialized directory handle from fat_OpenDir().
 * @param entry[out] Pointer to store entry information.
 * @return Number of entries found.
 */
fat_error_t fat_ReadDir(fat_dir_t *dir, fat_dir_entry_t *entry);

/**
 * Closes an open directory handle.
 * @param dir[in] Directory handle.
 * @return Number of entries found.
 */
fat_error_t fat_CloseDir(fat_dir_t *dir);

    
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
