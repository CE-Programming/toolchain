#ifndef LINKLIB_H
#define LINKLIB_H

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LINK_PENDING SIZE_MAX

typedef struct link_devices {
    uint8_t self, count, ids[];
} link_devices_t;

const link_devices_t *link_Devices(void);

bool link_QueueRead(uint8_t id, void *buffer, size_t *length);

bool link_QueueWrite(uint8_t id, const void *buffer, size_t *length);

bool link_Poll(void);

#ifdef __cplusplus
}
#endif

#endif
