typedef struct global global_t;
#define usb_callback_data_t global_t

#include <usbdrvce.h>
#include <fatdrvce.h>
#include <tice.h>
#include <debug.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTITIONS 10
#define FAT_BUFFER_SIZE (MSD_SECTOR_SIZE / sizeof(uint24_t))

void putstr(char *str);

struct global {
    usb_device_t device;
};

static uint8_t msd_buffer[MSD_SECTOR_SIZE];
static fat_partition_t fatpartitions[MAX_PARTITIONS];

static usb_error_t handleUsbEvent(usb_event_t event, void *event_data,
                                  usb_callback_data_t *callback_data) {

    switch (event) {
        case USB_DEVICE_DISCONNECTED_EVENT:
            callback_data->device = NULL;
            putstr("usb device disconnected");
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
    static global_t global;
    usb_error_t error;
    static msd_device_t msd;
    static fat_t fat;
    bool msd_inited = false;
    uint24_t sectorsize;
    uint8_t numpartitions;
    static char buffer[212];

    memset(&msd, 0, sizeof msd);
    memset(&global, 0, sizeof(global_t));
    os_SetCursorPos(1, 0);

    error = usb_Init(handleUsbEvent, &global, NULL, USB_DEFAULT_INIT_FLAGS);
    if (error != USB_SUCCESS) {
        return;
    }

    do {

        // check for any usb events
        error = usb_WaitForInterrupt();
        if (error != USB_SUCCESS) {
            break;
        }

        // if a device is plugged, initialize it
        if (!msd_inited && global.device) {

            // initialize the msd device
            error = msd_Init(&msd, global.device, msd_buffer);
            if (error == USB_SUCCESS) {
                putstr("inited msd");
                msd_inited = true;
                break;
            } else {
                sprintf(buffer, "init msd fail: %u", error);
                putstr(buffer);
                break;
            }
        }

    } while (!os_GetCSC());

    // return if msd could not be configured
    if (!msd_inited) {
        usb_Cleanup();
        os_GetKey();
        return;
    }

    // get sector size
    error = msd_GetSectorSize(&msd, &sectorsize);

    if (error == USB_SUCCESS) {
        sprintf(buffer, "sectorsize: %u", sectorsize);
        putstr(buffer);

        // find available fat partitions
        error = fat_Find(&msd, &fatpartitions, &numpartitions, MAX_PARTITIONS);
    }

    // attempt fat init on first fat32 partition
    if (error == USB_SUCCESS && numpartitions > 0) {
        sprintf(buffer, "num fat partition: %u", numpartitions);
        putstr(buffer);

        // attempt init of fat partition
        error = fat_Init(&fat, &fatpartitions[0]);
    }

    // attempt to open a file
    if (error == USB_SUCCESS) {
        static uint24_t fatbuffer[FAT_BUFFER_SIZE];
        static const char *str = "/FATTEST/DIR1/FILE.TXT";
        fat_file_t *file;
        uint24_t i, j, k;

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
        fat_SetSize(&fat, str, 512 * 64);
        fat_SetSize(&fat, str, 512 * 0);
        fat_SetSize(&fat, str, 512 * 10);

        // change the size of the other files
        fat_SetSize(&fat, "/FATTEST/DIR2/FILE1.TXT", 512 * 2 + 16);
        fat_SetSize(&fat, "/FATTEST/DIR2/FILE2.TXT", 512 * 2 + 32);

        // should not delete, nonempty directory
        fat_Delete(&fat, "/FATTEST/DIR2");

        // should delete, empty directory
        fat_Delete(&fat, "/FATTEST/DIR3");

        // delete file
        fat_Delete(&fat, "/FATTEST/DIR2/FILE2.TXT");

        // write bytes to file
        file = fat_Open(&fat, "/FATTEST/DIR1/FILE.TXT", FAT_RDWR);
        for (i = 0; i < 10; ++i)
        {
            for (j = i * FAT_BUFFER_SIZE; j < (i + 1) * FAT_BUFFER_SIZE; ++j)
            {
                fatbuffer[j] = j;
            }
            fat_WriteSector(file, fatbuffer);
        }

        // read back file, and compare read to written bytes
        fat_SetFilePos(file, 0);
        for (i = 0; i < 10; ++i)
        {
            fat_ReadSector(file, fatbuffer);
            for (j = i * FAT_BUFFER_SIZE; j < (i + 1) * FAT_BUFFER_SIZE; ++j)
            {
                if (fatbuffer[j] != j)
                {
                    putstr("read does not match!");
                    usb_Cleanup();
                    os_GetKey();
                    abort();
                }
            }
        }
        fat_Close(file);
    }

    if( error == USB_SUCCESS )
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

