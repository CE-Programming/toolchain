/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young\n
 * prime17569
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
#define lcd_CrsrImageLen32       256
#define lcd_CrsrImageLen64       1024
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
#define lcd_CrsrClip             (*(volatile uint16_t*)0xE30C14)
#define lcd_CrsrClipX            (*(volatile uint8_t*)0xE30C14)
#define lcd_CrsrClipY            (*(volatile uint8_t*)0xE30C15)
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

/** Sets up the hardware cursor. */
#define lcd_CrsrSetup() \
do { \
  lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(LCD_WIDTH - 1) << 16; \
  lcd_CrsrConfig = 0; \
  lcd_CrsrPalette0 = 0x00000000; \
  lcd_CrsrPalette1 = 0x00FFFFFF; \
  lcd_CrsrXY = 0; \
  lcd_CrsrClip = 0; \
} while (0)

/**
 * Hardware cursor sizes.
 */
typedef enum {
  LCD_CURSOR_SIZE_SMALL = 0, /**< Small size, 32x32, 256 bytes of packed 2bpp image data. */
  LCD_CURSOR_SIZE_LARGE = 1, /**< Large size, 64x64, 1024 bytes of packed 2bpp image data. */
} lcd_cursor_size_t;

/**
 * Sets cursor size.
 * 
 * @param[in] size The cursor size.
 * @see lcd_cursor_size_t
 */
#define lcd_CrsrSetSize(size) \
do { \
  lcd_CrsrConfig = ((lcd_CrsrConfig >> 1) << 1) | (size & 1); \
} while (0)

/** 
 * Gets cursor size.
 * 
 * @returns The cursor size.
 * @see lcd_cursor_size_t
 */
#define lcd_CrsrGetSize() ((lcd_cursor_size_t)(lcd_CrsrConfig & 1))

/** 
 * Sets a small cursor image at the specified index.
 * 
 * @param[in] data A pointer to 256 bytes of packed 2bpp image data.
 * @param[in] index The cursor image index to copy the data to (0-3).
 * 
 * @see lcd_CrsrSetImageIndex
 * @see lcd_cursor_size_t
 * 
 * @note
 * To use convimg to create the required data, add `bpp: 2`
 * to the converts section in convimg.yaml corresponding
 * to your image(s).
 */
#define lcd_CrsrSetImageSmall(data, index) \
do { \
  memcpy(lcd_CrsrImage + ((index & 0b11) * 0x100), data, lcd_CrsrImageLen32); \
} while (0)

/** 
 * Sets a large cursor image.
 * 
 * @param[in] data A pointer to 1024 bytes of packed 2bpp image data.
 * 
 * @see lcd_cursor_size_t
 * 
 * @note
 * To use convimg to create the required data, add `bpp: 2`
 * to the converts section in convimg.yaml corresponding
 * to your image(s).
 */
#define lcd_CrsrSetImageLarge(data) \
do { \
  memcpy(lcd_CrsrImage, data, lcd_CrsrImageLen64); \
} while (0)

/** 
 * Sets the position of the cursor on screen.
 * 
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
#define lcd_CrsrSetPosition(x, y) \
do { \
  lcd_CrsrX = x; \
  lcd_CrsrY = y; \
} while (0)

/** 
 * Sets the cursor clip position.
 * 
 * The cursor clip is the distance from the top-left edge of the cursor image
 * to the first displayed pixel in the cursor image.
 * 
 * @param[in] x X coordinate.
 * @param[in] y Y coordinate.
 */
#define lcd_CrsrSetClipPosition(x, y) \
do { \
  lcd_CrsrClipX = x; \
  lcd_CrsrClipY = y; \
} while (0)

/** Shows the cursor. */
#define lcd_CrsrShow() \
do { \
  lcd_CrsrCtrl |= 1; \
} while (0)

/**
 * Sets the cursor image index (0-3).
 * The cursor is capable of holding up to four small (32x32) images at once,
 * each occupying a quarter of the cursor RAM.
 * This function lets you choose which image you want to display.
 * 
 * @param[in] index The index of the cursor image to display (0-3).
 * 
 * @note
 * There is no effect if the cursor size is set to large (64x64),
 * since the cursor RAM can only hold one 64x64 image.
 */
#define lcd_CrsrSetImageIndex(index) \
do { \
  lcd_CrsrCtrl = (lcd_CrsrCtrl & ~(0b11 << 4)) | ((index & 0b11) << 4); \
} while (0)

/** Hides the cursor. */
#define lcd_CrsrHide() \
do { \
  lcd_CrsrCtrl &= ~(1); \
} while (0)

#define lcd_CrsrCleanup() \
do { \
  lcd_CrsrHide(); \
  lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(LCD_HEIGHT - 1) << 16; \
} while (0)

#ifdef __cplusplus
}
#endif

#endif
