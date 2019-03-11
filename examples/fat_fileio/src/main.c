#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fatdrvce.h>
#include <keypadc.h>

#define MAX_PARTITIONS 10
#define MAX_ENTRIES 10

static uint8_t sector[512];
static jmp_buf msdenv;

/* Function prototypes */
void putString(const char *str);
void fatDemo(void);

const char *wrtest = "WRTEST.TXT";
const char *dirtest = "DIRTEST";
#define WR_SIZE 4096

/* Main Function */
void main(void) {
    os_ClrHome();

    fatDemo();

    while (!os_GetCSC());
}

static fat_entry_t fat_entries[MAX_ENTRIES];

static void resetScreen(void) {
    asm(" call $20808");
    os_SetCursorPos(0, 0);
}

void fatDemo(void) {
    int8_t fd;
    uint8_t num, entries;
    msd_event_t evnt;
    unsigned int i;
    static fat_partition_t fat_partitions[MAX_PARTITIONS];
    char buf[128];

    resetScreen();
    putString("insert drive...");

    /* Set up error handling */
    if ((evnt = setjmp(msdenv)) != 0) {
        sprintf(buf, "event: %u", evnt);
        putString(buf);
        return;
    }
    msd_SetJmpBuf(msdenv);

    /* Initialize first detected mass storage device */
    if (msd_Init(7000) != 0) {
        putString("drive init failed.");
        return;
    }

    putString("locating filesystem");

    /* Set the buffer used by the FAT library */
    fat_SetBuffer(sector);

    /* Find any avaliable FAT filesystems on the device */
    num = fat_Find(fat_partitions, MAX_PARTITIONS);
    if (num == 0) {
        putString("no fat partitions.");
        return;
    }

    /* log number of partitions */
    sprintf(buf, "total fat partitions: %u", num);
    putString(buf);

    /* Just use the first detected partition */
    fat_Select(fat_partitions, 0);

    putString("using fat partition 1.");

    if ((num = fat_Init()) != 0) {
        sprintf(buf, "fat error: %u", num);
        putString(buf);
        return;
    }

    putString("initialized fat.");
    putString("press any key.");

    while (!kb_AnyKey());
    resetScreen();

    putString("creating file...");
    fat_Create(0, wrtest, 0);
    putString("success.");
    putString("creating dir...");
    fat_Create(0, dirtest, FAT_DIR);
    putString("success.");

    fd = fat_Open(wrtest, FAT_O_WRONLY);
    if (fd >= 0) {
        unsigned int i;

        putString("writing file...");

        for (i = 0; i < WR_SIZE; i += 512) {
            fat_WriteSector(fd);
        }

        fat_Close(fd);
        fat_SetFileSize(wrtest, WR_SIZE);
    } else {
        sprintf(buf, "wr err: %d", fd);
        putString(buf);
    }

    fd = fat_Open(wrtest, FAT_O_RDONLY);
    if (fd >= 0) {
        sprintf(buf, "size: %u", (unsigned int)fat_GetFileSize(fd));
        putString(buf);
        sprintf(buf, "tell: %u", (unsigned int)fat_Tell(fd));
        putString(buf);
        fat_Close(fd);
    } else {
        sprintf(buf, "wr o err: %d", fd);
        putString(buf);
    }

    fat_SetAttrib(dirtest, FAT_DIR | FAT_HIDDEN);
    sprintf(buf, "wr attrib: %u", (unsigned int)fat_GetAttrib(wrtest));
    putString(buf);
    sprintf(buf, "dir attrib: %u", (unsigned int)fat_GetAttrib(dirtest));
    putString(buf);

    while (!kb_AnyKey());
    resetScreen();

    entries = fat_DirList(NULL, fat_entries, 0, MAX_ENTRIES, 0);

    sprintf(buf, "num: %u", entries);
    putString(buf);
    for (num = 0; num < entries && num < 6; num++) {
        sprintf(buf, "%s", fat_entries[num].filename);
        putString(buf);
    }

    fat_Deinit();
    msd_Deinit();
}

/* Draw text on the homescreen */
void putString(const char *str) {
    os_PutStrFull(str);
    os_NewLine();
}

