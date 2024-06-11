/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief CE PL111 LCD controller define file
 */

#ifndef SYS_LCD_H
#define SYS_LCD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Base address of memory-mapped RAM for the LCD */
#define lcd_Ram                  ((void*)0xD40000)
/* @cond */
#define lcd_Timing0              (*(volatile uint32_t*)0xE30000)
#define lcd_Timing1              (*(volatile uint32_t*)0xE30004)
#define lcd_Timing2              (*(volatile uint32_t*)0xE30008)
#define lcd_Timing3              (*(volatile uint24_t*)0xE3000C)
#define lcd_UpBase               (*(volatile uint24_t*)0xE30010)
#define lcd_UpBaseFull           (*(volatile uint32_t*)0xE30010)
#define lcd_LpBase               (*(volatile uint24_t*)0xE30014)
#define lcd_LpBaseFull           (*(volatile uint32_t*)0xE30014)
/* @endcond */
/** LCD Control register */
#define lcd_Control              (*(volatile uint24_t*)0xE30018)
/* @cond */
/** LCD RGB/BGR and Bits per pixel */
#define lcd_VideoMode            (*(volatile uint16_t*)0xE30018)
#define LCD_RGB1bit               (0x821) /**< RGB 1bit indexed color */
#define LCD_RGB2bit               (0x823) /**< RGB 2bit indexed color */
#define LCD_RGB4bit               (0x825) /**< RGB 4bit indexed color */
#define LCD_RGB8bit               (0x827) /**< RGB 8bit indexed color */
#define LCD_RGB1555               (0x829) /**< RGB 1555 16bit */
#define LCD_RGB565                (0x82D) /**< RGB 565 16bit */
#define LCD_RGB444                (0x82F) /**< RGB 444 16bit */
#define LCD_RGB16bit              (LCD_RGB565) /**< TI-OS Default */
#define LCD_BGR1bit               (0x921) /**< BGR 1bit indexed color */
#define LCD_BGR2bit               (0x923) /**< BGR 2bit indexed color */
#define LCD_BGR4bit               (0x925) /**< BGR 4bit indexed color */
#define LCD_BGR8bit               (0x927) /**< BGR 8bit indexed color */
#define LCD_BGR1555               (0x929) /**< BGR 1555 16bit */
#define LCD_BGR565                (0x92D) /**< BGR 565 16bit */
#define LCD_BGR444                (0x92F) /**< BGR 444 16bit */
#define LCD_BGR16bit              (LCD_BGR565) /**< TI-OS Default */
/** LCD Bits per pixel */
#define lcd_VideoBPP             (*(volatile uint8_t*)0xE30018)
#define LCD_INDEXED1              (0x21) /**< 1bit indexed color */
#define LCD_INDEXED2              (0x23) /**< 2bit indexed color */
#define LCD_INDEXED4              (0x25) /**< 4bit indexed color */
#define LCD_INDEXED8              (0x27) /**< 8bit indexed color */
#define LCD_COLOR1555             (0x29) /**< 1555 16bit */
#define LCD_COLOR565              (0x2D) /**< 565 16bit */
#define LCD_COLOR444              (0x2F) /**< 444 16bit */
#define LCD_COLOR16               (LCD_COLOR565) /**< TI-OS Default */
#define lcd_EnableInt            (*(volatile uint8_t*)0xE3001C)
#define lcd_IntStatus            (*(volatile uint8_t*)0xE30020)
#define lcd_IntStatusMasked      (*(volatile uint8_t*)0xE30024)
#define lcd_IntAcknowledge       (*(volatile uint8_t*)0xE30028)
#define lcd_UpBaseCurr           (*(volatile uint24_t*)0xE3002C)
#define lcd_UpBaseCurrFull       (*(volatile uint32_t*)0xE3002C)
#define lcd_LpBaseCurr           (*(volatile uint24_t*)0xE30030)
#define lcd_LpBaseCurrFull       (*(volatile uint32_t*)0xE30030)
/* @endcond */
/** LCD palette registers, 512 bytes */
#define lcd_Palette              ((uint16_t*)0xE30200)
/* @cond */
#define lcd_CrsrImageLen32      (256)
#define lcd_CrsrImageLen64      (1024)
#define lcd_CrsrImage            ((uint8_t*)0xE30800)
#define lcd_CrsrCtrl             (*(volatile uint8_t*)0xE30C00)
#define lcd_CrsrConfig           (*(volatile uint8_t*)0xE30C04)
#define lcd_CrsrPalette0         (*(volatile uint24_t*)0xE30C08)
#define lcd_CrsrPalette1         (*(volatile uint24_t*)0xE30C0C)
#define lcd_CrsrXY               (*(volatile uint24_t*)0xE30C10)
#define lcd_CrsrXYFull           (*(volatile uint32_t*)0xE30C10)
#define lcd_CrsrX                (*(volatile uint16_t*)0xE30C10)
#define lcd_CrsrY                (*(volatile uint8_t*)0xE30C12)
#define lcd_CrsrYFull            (*(volatile uint16_t*)0xE30C12)
#define lcd_CrsrClip             (*(volatile uint16_t*)0xE30C04)
#define lcd_CrsrClipX            (*(volatile uint8_t*)0xE30C04)
#define lcd_CrsrClipY            (*(volatile uint8_t*)0xE30C05)
#define lcd_CrsrEnableInt        (*(volatile uint8_t*)0xE30C20)
#define lcd_CrsrIntAcknowledge   (*(volatile uint8_t*)0xE30C24)
#define lcd_CrsrIntStatus        (*(volatile uint8_t*)0xE30C28)
#define lcd_CrsrIntStatusMasked  (*(volatile uint8_t*)0xE30C2C)
/* @endcond */
/** Current backlight level of the LCD. 0 is brightest, 255 is darkest. */
#define lcd_BacklightLevel       (*(volatile uint8_t*)0xF60024)

/** Width of LCD in pixels */
#define LCD_WIDTH               (320)
/** Height of LCD in pixels */
#define LCD_HEIGHT              (240)
/** Total size of VRAM in bytes */
#define LCD_SIZE                (LCD_WIDTH*LCD_HEIGHT*2)

#ifdef __cplusplus
}
#endif

#endif
