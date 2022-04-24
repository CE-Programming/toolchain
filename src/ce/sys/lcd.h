/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief CE PL111 LCD controller define file
 */

#ifndef _CELCD_H
#define _CELCD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define lcd_Ram                  ((volatile uint16_t*)0xD40000) /**< Base address of memory-mapped RAM for the LCD */
/* @cond */
#define lcd_Timing0              (*(volatile uint32_t*)0xE30000)
#define lcd_Timing1              (*(volatile uint32_t*)0xE30004)
#define lcd_Timing2              (*(volatile uint32_t*)0xE30008)
#define lcd_Timing3              (*(volatile uint24_t*)0xE3000C)
#define lcd_UpBase               (*(volatile uint32_t*)0xE30010)
#define lcd_LpBase               (*(volatile uint32_t*)0xE30014)
/* @endcond */
#define lcd_Control              (*(volatile uint24_t*)0xE30018) /**< LCD Control register */
/* @cond */
#define lcd_EnableInt            (*(volatile uint8_t*)0xE3001C)
#define lcd_IntStatus            (*(volatile uint8_t*)0xE30020)
#define lcd_IntStatusMasked      (*(volatile uint8_t*)0xE30024)
#define lcd_IntAcknowledge       (*(volatile uint8_t*)0xE30028)
#define lcd_UpBaseCurr           (*(volatile uint32_t*)0xE3002C)
#define lcd_LpBaseCurr           (*(volatile uint32_t*)0xE30030)
/* @endcond */
#define lcd_Palette              ((volatile uint16_t*)0xE30200) /**< LCD palette registers, 512 bytes */
/* @cond */
#define lcd_CrsrCtrl             (*(volatile uint8_t*)0xE30C00)
#define lcd_CrsrConfig           (*(volatile uint8_t*)0xE30C04)
#define lcd_CrsrPalette0         (*(volatile uint24_t*)0xE30C08)
#define lcd_CrsrPalette1         (*(volatile uint24_t*)0xE30C0C)
#define lcd_CrsrXY               (*(volatile uint32_t*)0xE30C10)
#define lcd_CrsrX                (*(volatile uint16_t*)0xE30C10)
#define lcd_CrsrY                (*(volatile uint16_t*)0xE30C12)
#define lcd_CrsrClip             (*(volatile uint16_t*)0xE30C04)
#define lcd_CrsrClipX            (*(volatile uint8_t*)0xE30C04)
#define lcd_CrsrClipY            (*(volatile uint8_t*)0xE30C05)
#define lcd_CrsrEnableInt        (*(volatile uint8_t*)0xE30C20)
#define lcd_CrsrIntAcknowledge   (*(volatile uint8_t*)0xE30C24)
#define lcd_CrsrIntStatus        (*(volatile uint8_t*)0xE30C28)
#define lcd_CrsrIntStatusMasked  (*(volatile uint8_t*)0xE30C2C)
/* @endcond */
#define lcd_BacklightLevel       (*(volatile uint8_t*)0xF60024) /**< Current backlight level of the LCD. 0 is bright. 255 is dark. */

#define LCD_WIDTH               (320)  /**< Width of LCD in pixels */
#define LCD_HEIGHT              (240) /**< Height of LCD in pixels */
#define LCD_SIZE                (LCD_WIDTH*LCD_HEIGHT*2) /**< Total size of VRAM in bytes */

#ifdef __cplusplus
}
#endif

#endif