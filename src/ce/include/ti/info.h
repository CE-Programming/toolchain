/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE information
 */

#ifndef TI_INFO_H
#define TI_INFO_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Bootcode functions
 */

/**
 * @returns Bootcode version major
 */
uint8_t boot_GetBootMajorVer(void);

/**
 * @returns Bootcode version minor
 */
uint8_t boot_GetBootMinorVer(void);

/**
 * @returns Hardware version
 */
uint8_t boot_GetHardwareVer(void);

/*
 * OS Routines
 */

typedef struct system_info {
    size_t size;                 /**< number of valid bytes after this field */
    uint8_t hardwareVersion;     /**< 7 on both CE,  8 on 82AEP              */
    uint8_t hardwareType;        /**< 0 on TI84+CE,  1 on TI83PCE/82AEP      */
    uint8_t hardwareType2;       /**< 9 on TI84+CE, 12 on TI83PCE/82AEP      */
    uint8_t osMajorVersion;      /**< e.g.  5 on OS 5.4.0.0034               */
    uint8_t osMinorVersion;      /**< e.g.  4 on OS 5.4.0.0034               */
    uint8_t osRevisionVersion;   /**< e.g.  0 on OS 5.4.0.0034               */
    unsigned osBuildVersion;     /**< e.g. 34 on OS 5.4.0.0034               */
    uint8_t bootMajorVersion;    /**< e.g.  5 on boot 5.3.6.0017             */
    uint8_t bootMinorVersion;    /**< e.g.  3 on boot 5.3.6.0017             */
    uint8_t bootRevisionVersion; /**< e.g.  6 on boot 5.3.6.0017             */
    unsigned bootBuildVersion;   /**< e.g. 17 on boot 5.3.6.0017             */
    uint8_t unknown[10];         /**< 400100f0000010300000 on CE             */
    uint8_t calcid[8];           /**< From certificate                       */
    char ti[2];                  /**< First part of device name, "TI"        */
    uint16_t language;           /**< EN: 0x109, FR: 0x10C, ...              */
} system_info_t;

/**
 * Gets the system info
 *
 * @returns A pointer to system_info_t
 */
const system_info_t *os_GetSystemInfo(void);

#ifdef __cplusplus
}
#endif

#endif
