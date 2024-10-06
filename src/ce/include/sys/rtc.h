/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief CE Real-Time Clock define file
 */

#ifndef SYS_RTC_H
#define SYS_RTC_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Bootcode functions
 */

/**
 * Sets the calculator's date
 *
 * Performs checks to ensure date is within range
 * @param[in] day Day to set
 * @param[in] month Month to set
 * @param[in] year Year to set
 */
void boot_SetDate(uint8_t day, uint8_t month, uint16_t year);

/**
 * Gets the calculator's date
 *
 * @param[out] day Pointer to variable to store day
 * @param[out] month Pointer to variable to store month
 * @param[out] year Pointer to variable to store year
 */
void boot_GetDate(uint8_t *day, uint8_t *month, uint16_t *year);

/**
 * Sets the calculator's time
 *
 * Performs checks to ensure time is within range.
 * @warning This function doesn't wait until the previous full RTC load
 *          operation is completed before attempting to start a new one.
 *          This may lead to issues, for example if you call boot_SetDate()
 *          before this function.
 *          To mitigate this, use boot_SetDate() (which doesn't have this bug),
 *          after boot_SetTime() or validate rtc_IsBusy() is false before
 *          calling boot_SetTime().
 * @param[in] seconds Seconds to set
 * @param[in] minutes Minutes to set
 * @param[in] hours Hours to set
 */
void boot_SetTime(uint8_t seconds, uint8_t minutes, uint8_t hours);

/**
 * Gets the calculator's time
 *
 * @note You can read \c rtc_Seconds, \c rtc_Minutes , and \c rtc_Hours directly, but you should double check
 * that \c rtc_Seconds didn't change while reading \c rtc_Minutes and \c rtc_Hours .
 *
 * @param[out] seconds Pointer to variable to store seconds
 * @param[out] minutes Pointer to variable to store minutes
 * @param[out] hours Pointer to variable to store hours
 */
void boot_GetTime(uint8_t *seconds, uint8_t *minutes, uint8_t *hours);

/**
 * Checks if past noon
 *
 * @returns True if past noon
 */
bool boot_IsAfterNoon(void);

/*
 * OS/bootcode variables
 * Currently removed because they're pointless to have in the C API.
#define os_TmpYears          (*(real_t*)0xD02B01)
#define os_TmpMonths         (*(real_t*)0xD02B0A)
#define os_TmpDays           (*(real_t*)0xD02B13)
#define os_TmpHours          (*(real_t*)0xD02B1C)
#define os_TmpMinutes        (*(real_t*)0xD02B25)
*/

/*
 * Direct access to hardware registers
 */

/* @cond */
#define RTC_ALARM_INT_SOURCE    (1<<5)
#define RTC_DAY_INT_SOURCE      (1<<4)
#define RTC_HR_INT_SOURCE       (1<<3)
#define RTC_MIN_INT_SOURCE      (1<<2)
#define RTC_SEC_INT_SOURCE      (1<<1)

#define RTC_UNFREEZE            (1<<7)
#define RTC_FREEZE              (0<<7)
#define RTC_LOAD                (1<<6)
#define RTC_ENABLE              ((1<<0)|RTC_UNFREEZE)
#define RTC_DISABLE             (0<<0)

#define rtc_Control             (*(volatile uint8_t*)0xF30020)
#define rtc_LoadSeconds         (*(volatile uint8_t*)0xF30024)
#define rtc_LoadMinutes         (*(volatile uint8_t*)0xF30028)
#define rtc_LoadHours           (*(volatile uint8_t*)0xF3002C)
#define rtc_LoadDays            (*(volatile uint16_t*)0xF30030)
#define rtc_IntStatus           (*(volatile uint8_t*)0xF30034)
#define rtc_IntAcknowledge      (*(volatile uint8_t*)0xF30034)
/* @endcond */

/**
 * Enables the Real-Time-Clock (RTC).
 *
 * @param int Interrupt mask to enable specific RTC interrupts.
 */
#define rtc_Enable(int) \
do { \
    rtc_Control |= RTC_ENABLE | (int << 1); \
} while (0)

/**
 * Sets the Real-Time-Clock (RTC) with new values.
 *
 * @param sec Second value to load.
 * @param min Minute value to load.
 * @param hr Hour value to load.
 * @param day Day value to load.
 *
 * @note
 * The set values do not take effect until the next RTC second.
 * Verify the values have been loaded by waiting for rtc_IsBusy() to be false.
 * The RTC will also need to be enabled.
 */
#define rtc_Set(sec, min, hr, day) \
do { \
    rtc_Seconds = sec; \
    rtc_Minutes = min; \
    rtc_Hours = hr; \
    rtc_Days = day; \
    rtc_Control |= RTC_LOAD; \
} while (0)

/**
 * Sets the Real-Time-Clock (RTC) alarm with new values.
 *
 * @param sec Second alarm value.
 * @param min Minute alarm value.
 * @param hr Hour alarm value.
 */
#define rtc_SetAlarm(sec, min, hr) \
do { \
    rtc_AlarmSeconds = sec; \
    rtc_AlarmMinutes = min; \
    rtc_AlarmHours = hr; \
} while (0)

/**
 * Disables the Real-Time-Clock (RTC).
 */
#define rtc_Disable() \
do { \
    rtc_Control &= ~RTC_ENABLE; \
} while (0)

/**
 * Checks if the RTC is busy setting newly loaded values.
 */
#define rtc_IsBusy() ((rtc_Control) & RTC_LOAD)

/**
 * Acknowledges an RTC interrupt.
 * This should be used to clear the condition that is causing the interrupt.
 *
 * @param mask RTC interrupt mask.
 */
#define rtc_AckInterrupt(mask) (rtc_IntAcknowledge = (mask))

/**
 * Checks if a RTC interrupt condition has occurred.
 *
 * @param mask RTC interrupt mask.
 */
#define rtc_ChkInterrupt(mask) (rtc_IntStatus & (mask))

/**
 * Gets a combination of the RTC time; useful for seeding random numbers
 * via srand().
 */
#define rtc_Time()              (*(volatile uint32_t*)0xF30044)

#define rtc_Seconds             (*(volatile uint8_t*)0xF30000)    /**< RTC seconds */
#define rtc_Minutes             (*(volatile uint8_t*)0xF30004)    /**< RTC minutes */
#define rtc_Hours               (*(volatile uint8_t*)0xF30008)    /**< RTC hours */
#define rtc_Days                (*(volatile uint16_t*)0xF3000C)   /**< RTC days */
#define rtc_AlarmSeconds        (*(volatile uint8_t*)0xF30010)    /**< RTC alarm seconds */
#define rtc_AlarmMinutes        (*(volatile uint8_t*)0xF30014)    /**< RTC alarm minutes */
#define rtc_AlarmHours          (*(volatile uint8_t*)0xF30018)    /**< RTC alarm hours */

#define RTC_LOAD_INT             (1<<5)  /**< RTC load operation complete */
#define RTC_ALARM_INT            (1<<4)  /**< RTC alarm interrupt */
#define RTC_DAY_INT              (1<<3)  /**< RTC interrupt on day change */
#define RTC_HR_INT               (1<<2)  /**< RTC interrupt on hour change */
#define RTC_MIN_INT              (1<<1)  /**< RTC interrupt on minute change */
#define RTC_SEC_INT              (1<<0)  /**< RTC interrupt on second change */
#define RTC_INT_MASK             (RTC_SEC_INT | RTC_MIN_INT | RTC_HR_INT | RTC_DAY_INT | RTC_ALARM_INT | RTC_LOAD_INT) /**< RTC mask for all interrupts */

#ifdef __cplusplus
}
#endif

#endif
