#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fatdrvce.h>

#define MAX_PARTITIONS 10

static uint8_t sector[512];
static jmp_buf msdenv;

/* Function prototypes */
void putString(const char *str);
void fatDemo(void);

void send_char(char n)
{
    char str[2];
    str[0] = n;
    str[1] = 0;
    os_PutStrFull(str);
}

/* Main Function */
void main(void) {
    os_ClrHome();

    fatDemo();

    while (!os_GetCSC());
}

void fatDemo(void) {
    int8_t fd;
    uint8_t num;
    msd_event_t evnt;
    unsigned int i;
    fat_partition_t fat_partitions[MAX_PARTITIONS];
    char buf[128];

    putString("insert drive...");

    /* Set up error handling */
    if ((evnt = msd_SetJmp(msdenv)) != 0) {
        sprintf(buf, "event: %u", evnt);
        putString(buf);
        return;
    }

    /* Initialize first detected mass storage device */
    if (msd_Init(5000) != 0) {
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

    if (fat_Init() != 0) {
        putString("fat error.");
        return;
    }

    putString("initialized fat.");

    for (;;) {
        msd_ReadSector(sector, 0);
    }

    msd_Cleanup();
}

/* Draw text on the homescreen */
void putString(const char *str) {
    os_PutStrFull(str);
    os_NewLine();
}

