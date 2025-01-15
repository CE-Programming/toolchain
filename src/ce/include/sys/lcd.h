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
/** LCD Bits per pixel */
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

#define LCD_BGR (0x100)
#define LCD_RGB (0x000)

#define LCD_INDEXED1              (0x21) /**< 1bit indexed color */
#define LCD_INDEXED2              (0x23) /**< 2bit indexed color */
#define LCD_INDEXED4              (0x25) /**< 4bit indexed color */
#define LCD_INDEXED8              (0x27) /**< 8bit indexed color */
#define LCD_COLOR1555             (0x29) /**< 1555 16bit */
#define LCD_COLOR565              (0x2D) /**< 565 16bit */
#define LCD_COLOR444              (0x2F) /**< 444 16bit */
#define LCD_COLOR16               (LCD_COLOR565) /**< TI-OS Default */

#define LCD_BGR1bit               (LCD_INDEXED1  | LCD_BGR) /**< BGR 1bit indexed color */
#define LCD_BGR2bit               (LCD_INDEXED2  | LCD_BGR) /**< BGR 2bit indexed color */
#define LCD_BGR4bit               (LCD_INDEXED4  | LCD_BGR) /**< BGR 4bit indexed color */
#define LCD_BGR8bit               (LCD_INDEXED8  | LCD_BGR) /**< BGR 8bit indexed color */
#define LCD_BGR1555               (LCD_COLOR1555 | LCD_BGR) /**< BGR 1555 16bit */
#define LCD_BGR565                (LCD_COLOR565  | LCD_BGR) /**< BGR 565 16bit */
#define LCD_BGR444                (LCD_COLOR444  | LCD_BGR) /**< BGR 444 16bit */
#define LCD_BGR16bit              (LCD_COLOR16   | LCD_BGR) /**< BGR 565 16bit (TI-OS Default) */

#define LCD_RGB1bit               (LCD_INDEXED1  | LCD_RGB) /**< RGB 1bit indexed color */
#define LCD_RGB2bit               (LCD_INDEXED2  | LCD_RGB) /**< RGB 2bit indexed color */
#define LCD_RGB4bit               (LCD_INDEXED4  | LCD_RGB) /**< RGB 4bit indexed color */
#define LCD_RGB8bit               (LCD_INDEXED8  | LCD_RGB) /**< RGB 8bit indexed color */
#define LCD_RGB1555               (LCD_COLOR1555 | LCD_RGB) /**< RGB 1555 16bit */
#define LCD_RGB565                (LCD_COLOR565  | LCD_RGB) /**< RGB 565 16bit */
#define LCD_RGB444                (LCD_COLOR444  | LCD_RGB) /**< RGB 444 16bit */
#define LCD_RGB16bit              (LCD_COLOR16   | LCD_RGB) /**< RGB 565 16bit */

/**
 * Sets the color order (RGB/BGR) and the bits per pixel on the LCD without
 * modifying other bits.
 */
#define lcd_SetVideoMode(VideoMode) \
do { \
    lcd_Control = (lcd_Control & ~0x10E) | ((VideoMode) & 0x10E); \
} while(0)

/**
 * Resets lcd_Control to TI-OS defaults
 */
#define lcd_ResetVideoMode() \
do { \
    lcd_Control = LCD_BGR16bit; \
} while(0)

#ifdef __cplusplus
}
#endif

#endif
