/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief CE hardware timers define file
 */

#ifndef SYS_TIMERS_H
#define SYS_TIMERS_H

#include <stdint.h>
#include <sys/util.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
/* @endcond */

/**
 * Suspends execution of the calling thread for (at least) @p msec milliseconds.
 *
 * @param[in] msec number of milliseconds
 * @see sleep
 * @see usleep
 */
void delay(uint16_t msec);

/**
 * Suspends execution of the calling thread for (at least) @p msec milliseconds.
 *
 * @param[in] msec number of milliseconds
 * @see sleep
 * @see usleep
 */
void msleep(uint16_t msec);

/**
 * Sleeps until the number of real-time seconds specified in @p seconds have
 * elapsed or until a signal arrives which is not ignored.
 *
 * @note
 * Currently, signals do not exist, so this will never be interrupted.
 *
 * @param[in] seconds number of seconds
 * @return zero if the requested time has elapsed, or the number of seconds left
 *         to sleep, if the call was interrupted by a signal handler
 * @see delay
 * @see usleep
 */
unsigned int sleep(unsigned int seconds);

/**
 * Suspends execution of the calling thread for (at least) @p ticks clock ticks.
 *
 * @param[in] ticks number of clock ticks
 * @see CLOCKS_PER_SEC
 * @see delay
 * @see usleep
 */
void ticksleep(unsigned long ticks);

/**
 * An unsigned integer type capable of holding integers in the range
 * [0,1000000].
 *
 * @see usleep
 */
typedef unsigned int useconds_t;

/**
 * Suspends execution of the calling thread for (at least) @p usec microseconds.
 *
 * The sleep may be lengthened slightly by any system activity or by the time
 * spent processing the call or by the granularity of system timers.
 *
 * @note
 * Currently, no errors are possible.
 *
 * @param[in] usec number of microseconds
 * @return 0 on success, or -1 on error, with \c errno set to indicate the error
 * @see delay
 * @see sleep
 * @see useconds_t
 */
int usleep(useconds_t usec);

/**
 * Waits for ~10 ms. In most cases it is better to use the delay() function.
 */
void boot_WaitShort(void);

/* @cond */
#define timer_Enable(n, rate, int, dir) (timer_Control = timer_Control & ~(0x7 << 3 * ((n) - 1) | 1 << ((n) + 8)) | (1 | (rate) << 1 | (int) << 2) << 3 * ((n) - 1) | (dir) << ((n) + 8))
#define timer_Disable(n) (timer_Control &= ~(1 << 3 * ((n) - 1)))
#define timer_Get(n) atomic_load_32(TIMER_COUNT_ADDR(n))
#define timer_GetSafe(n, dir) \
    ((dir) == TIMER_UP ? \
        atomic_load_increasing_32(TIMER_COUNT_ADDR(n)) : \
        atomic_load_decreasing_32(TIMER_COUNT_ADDR(n)))
#define timer_Set(n, value) *TIMER_COUNT_ADDR(n) = (uint32_t)(value)
#define timer_GetReload(n) *TIMER_RELOAD_ADDR(n)
#define timer_SetReload(n, value) *TIMER_RELOAD_ADDR(n) = (uint32_t)(value)
#define timer_GetMatch(n, m) *TIMER_MATCH_ADDR(n, m)
#define timer_SetMatch(n, m, value) *TIMER_MATCH_ADDR(n, m) = (uint32_t)(value)
#define timer_AckInterrupt(n, mask) (timer_IntAcknowledge = (mask) << 3 * ((n) - 1))
#define timer_ChkInterrupt(n, mask) ((timer_IntStatus >> 3 * ((n) - 1)) & (mask))
#define TIMER_32K                1
#define TIMER_CPU                0
#define TIMER_0INT               1
#define TIMER_NOINT              0
#define TIMER_UP                 1
#define TIMER_DOWN               0
#define TIMER_MATCH(i)           (1<<((i) - 1))
#define TIMER_RELOADED           (1<<2)
#define TIMER1_ENABLE            (1<<0)
#define TIMER1_DISABLE           (0<<0)
#define TIMER1_32K               (1<<1)
#define TIMER1_CPU               (0<<1)
#define TIMER1_0INT              (1<<2)
#define TIMER1_NOINT             (0<<2)
#define TIMER1_UP                (1<<9)
#define TIMER1_DOWN              (0<<9)
#define TIMER2_ENABLE            (1<<3)
#define TIMER2_DISABLE           (0<<3)
#define TIMER2_32K               (1<<4)
#define TIMER2_CPU               (0<<4)
#define TIMER2_0INT              (1<<5)
#define TIMER2_NOINT             (0<<5)
#define TIMER2_UP                (1<<10)
#define TIMER2_DOWN              (0<<10)
#define TIMER3_ENABLE            (1<<6)
#define TIMER3_DISABLE           (0<<6)
#define TIMER3_32K               (1<<7)
#define TIMER3_CPU               (0<<7)
#define TIMER3_0INT              (1<<8)
#define TIMER3_NOINT             (0<<8)
#define TIMER3_UP                (1<<11)
#define TIMER3_DOWN              (0<<11)
#define TIMER1_MATCH1            (1<<0)
#define TIMER1_MATCH2            (1<<1)
#define TIMER1_RELOADED          (1<<2)
#define TIMER2_MATCH1            (1<<3)
#define TIMER2_MATCH2            (1<<4)
#define TIMER2_RELOADED          (1<<5)
#define TIMER3_MATCH1            (1<<6)
#define TIMER3_MATCH2            (1<<7)
#define TIMER3_RELOADED          (1<<8)
#define timer_1_Counter          (*(volatile uint32_t*)0xF20000)
#define timer_1_ReloadValue      (*(volatile uint32_t*)0xF20004)
#define timer_1_MatchValue_1     (*(volatile uint32_t*)0xF20008)
#define timer_1_MatchValue_2     (*(volatile uint32_t*)0xF2000C)
#define timer_2_Counter          (*(volatile uint32_t*)0xF20010)
#define timer_2_ReloadValue      (*(volatile uint32_t*)0xF20014)
#define timer_2_MatchValue_1     (*(volatile uint32_t*)0xF20018)
#define timer_2_MatchValue_2     (*(volatile uint32_t*)0xF2001C)
#define timer_3_Counter          (*(volatile uint32_t*)0xF20020)
#define timer_3_ReloadValue      (*(volatile uint32_t*)0xF20024)
#define timer_3_MatchValue_1     (*(volatile uint32_t*)0xF20028)
#define timer_3_MatchValue_2     (*(volatile uint32_t*)0xF2002C)
#define timer_Control            (*(volatile uint16_t*)0xF20030)
#define timer_IntStatus          (*(volatile uint16_t*)0xF20034)
#define timer_IntAcknowledge     (*(volatile uint16_t*)0xF20034)
#define timer_EnableInt          (*(volatile uint16_t*)0xF20038)
#define TIMER_COUNT_ADDR(n)      (volatile uint32_t*)(0xF20000 + (16 * ((n) - 1)))
#define TIMER_RELOAD_ADDR(n)     (volatile uint32_t*)(0xF20004 + (16 * ((n) - 1)))
#define TIMER_MATCH_ADDR(n, m)   (volatile uint32_t*)(0xF20008 + (16 * ((n) - 1)) + (4 * ((m) - 1)))
#define timer_GetLow(n) (_Pragma("GCC warning \"'timer_GetLow' is deprecated, use 'clock'\""))
/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
