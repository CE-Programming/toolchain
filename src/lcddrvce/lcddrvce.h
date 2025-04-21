/**
 * @file
 * @author Brendan "calc84maniac" Fletcher
 *
 * This is a library for interfacing with the calculator's LCD panel.
 * It provides the ability to send direct commands over SPI,
 * and convenience functions are provided for common commands.
 */

#ifndef LCDDRVCE_H
#define LCDDRVCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Converts a command name and size into a literal for use with lcd_SendSizedCommandRaw(), lcd_SendSizedCommandBytes(), or lcd_SendSizedCommandWords().
 * The `LCD_CMD_` prefix is automatically taken care of.
 *
 * For example, `LCD_SIZEDCMD(VSCRDEF, 3)` is used to send #LCD_CMD_VSCRDEF with 3 parameters.
 *
 * @param[in] cmd Command name without `LCD_CMD_` prefix
 * @param[in] size Parameters size in bytes or words (max 255)
 */
#define LCD_SIZEDCMD(cmd, size) (LCD_CMD_##cmd | (size) << 8)

/**
 * Converts a 16-bit parameter to big endian.
 * This is only needed when storing 16-bit parameters in a structure for use with lcd_SendCommandRaw() or lcd_SendParamsRaw().
 * Parameters sent using lcd_SendCommandWords() or specific command macros will be converted to big endian automatically.
 */
#define LCD_PARAM16(param) __builtin_bswap16(param)

/**
 * Initializes the LCD driver.
 *
 * The first call to this function will reinitialize the SPI controller
 * to target the LCD and prepare the SPI controller to send data.
 *
 * @note This must be called before any other function. Each call to this
 * function must correspond to a call to lcd_Cleanup().
 */
void lcd_Init(void);

/**
 * Waits for all previously queued commands and parameters to finish sending.
 */
void lcd_Wait(void);

/**
 * Uninitializes the LCD driver.
 *
 * The last call to this function, corresponding to the first call to
 * lcd_Init(), will disable the SPI controller.
 * Implicitly calls lcd_Wait() in case there are commands in progress.
 *
 * @note This will not restore any changed LCD settings.
 * If that is necessary, send commands to change them back to defaults.
 */
void lcd_Cleanup(void);

/**
 * Sends a command, given a pointer to its raw parameters.
 *
 * You can also use the lcd_SendCommandRaw() convenience macro to specify
 * the command and the size of the parameters separately.
 *
 * @param[in] sized_cmd An #LCD_SIZEDCMD literal, specifying parameter data size in bytes
 * @param[in] params Pointer to raw parameter data
 * @return Pointer following raw parameter data
 */
const void *lcd_SendSizedCommandRaw(uint16_t sized_cmd, const void *params);

/**
 * Sends only raw parameters to a previously sent command.
 *
 * Most useful for sending pixel data after lcd_StartPixelWrite() or lcd_ContinuePixelWrite().
 *
 * @param[in] size Size of the raw parameters in bytes
 * @param[in] params Pointer to raw parameter data
 * @return Pointer following the raw parameter data.
 */
const void *lcd_SendParamsRaw(size_t size, const void *params);

/**
 * Sends a command with no parameters.
 */
void lcd_SendCommand(uint8_t cmd);

/**
 * Sends a command with one byte parameter.
 */
void lcd_SendCommand1(uint8_t cmd, uint8_t param);

/**
 * Sends a command with two byte parameters.
 */
void lcd_SendCommand2(uint8_t cmd, uint8_t param1, uint8_t param2);

/**
 * Sends a command with an arbitrary number of byte parameters.
 *
 * You can also use the lcd_SendCommandBytes() convenience macro to specify
 * the command and the number of parameters separately.
 *
 * @param[in] sized_cmd An #LCD_SIZEDCMD literal, specifying number of bytes
 * @param[in] ... One function parameter for each byte parameter
 */
void lcd_SendSizedCommandBytes(uint16_t sized_cmd, ...);

/**
 * Sends a command with an arbitrary number of 16-bit word parameters.
 *
 * The parameters should be passed as their actual values, and are
 * converted to big endian when transferred over SPI.
 *
 * You can also use the lcd_SendCommandWords() convenience macro to specify
 * the command and the number of parameters separately.
 *
 * @param[in] sized_cmd An #LCD_SIZEDCMD literal, specifying number of words
 * @param[in] ... One function parameter for each word parameter
 */
void lcd_SendSizedCommandWords(uint16_t sized_cmd, ...);

/**
 * Sets a gamma profile that provides a uniform perceived change in
 * brightness as the color components change. This fixes a flaw in TI's
 * default gamma profile that makes some darker colors indistinguishable.
 */
void lcd_SetUniformGamma(void);

/**
 * Restores TI's default gamma profile.
 */
void lcd_SetDefaultGamma(void);

/**
 * Sends a command, given a pointer to its raw parameters.
 * 
 * @see lcd_SendSizedCommandRaw
 *
 * @param[in] cmd Command name without `LCD_CMD_` prefix
 * @param[in] size Parameter data size in bytes (maximum 255)
 * @param[in] params Pointer to raw parameter data
 * @return Pointer following raw parameter data
 */
#define lcd_SendCommandRaw(cmd, size, params) lcd_SendSizedCommandRaw(LCD_SIZEDCMD(cmd, size), params)

/**
 * Sends a command with an arbitrary number of byte parameters.
 * 
 * @see lcd_SendSizedCommandBytes
 *
 * @param[in] cmd Command name without `LCD_CMD_` prefix
 * @param[in] size Number of parameters (maximum 255)
 * @param[in] ... One function parameter for each byte parameter
 */
#define lcd_SendCommandBytes(cmd, size, ...) lcd_SendSizedCommandBytes(LCD_SIZEDCMD(cmd, size), __VA_ARGS__)

/**
 * Sends a command with an arbitrary number of 16-bit word parameters.
 *
 * The parameters should be passed as their actual values, and are
 * converted to big endian when transferred over SPI.
 *
 * @see lcd_SendSizedCommandWords
 *
 * @param[in] cmd Command name without `LCD_CMD_` prefix
 * @param[in] size Number of parameters (maximum 255)
 * @param[in] ... One function parameter for each word parameter
 */
#define lcd_SendCommandWords(cmd, size, ...) lcd_SendSizedCommandWords(LCD_SIZEDCMD(cmd, size), __VA_ARGS__)

/**
 * Enables or disables pixel color inversion.
 * @param[in] on Boolean indicating whether to enable inversion
 */
#define lcd_SetInvertedMode(on) lcd_SendCommand((on) ? LCD_CMD_INVON : LCD_CMD_INVOFF)
/**
 * Enables or disables image display.
 * When disabled, displays a blank (white) image, regardless of the contents of LCD RAM.
 * @param[in] on Boolean indicating whether image display should be on
 */
#define lcd_SetDisplayEnable(on) lcd_SendCommand((on) ? LCD_CMD_DISPON : LCD_CMD_DISPOFF)

/**
 * Enables or disables Sleep Mode.
 * @param[in] on Boolean indicating whether to enable sleep mode
 */
#define lcd_SetSleepMode(on) lcd_SendCommand((on) ? LCD_CMD_SLPIN : LCD_CMD_SLPOUT)
/**
 * Enables or disables Partial Mode.
 * This mode restricts image display to only a subset of the scanlines,
 * with the remaining lines showing as white or black.
 * @see lcd_SetPartialArea()
 * @see lcd_SetPartialControl()
 * @param[in] on Boolean indicating whether to enable partial mode
 */
#define lcd_SetPartialMode(on) lcd_SendCommand((on) ? LCD_CMD_PTLON : LCD_CMD_NORON)
/**
 * Enables or disables Idle Mode.
 * When enabled, each color component of every pixel is rounded to 0 or 63,
 * for 8 displayable colors total (Black, White, Red, Green, Blue, Cyan, Magenta, Yellow).
 * @param[in] on Boolean indicating whether to enable idle mode
 */
#define lcd_SetIdleMode(on) lcd_SendCommand((on) ? LCD_CMD_IDMON : LCD_CMD_IDMOFF)
/**
 * Enables or disables screen interlacing.
 * When enabled, the left side of the frame is displayed on even-indexed vertical scanlines,
 * and the right side of the frame is displayed on odd-indexed vertical scanlines.
 * @see lcd_SetGateControl()
 * @param[in] on Boolean indicating whether to enable interlacing
 */
#define lcd_SetInterlacedMode(on) lcd_SetGateControl(LCD_GATECTRL_DEFAULT | ((on) ? LCD_SM : 0))


/**
 * Sets the vertical scroll area definition.
 * @see lcd_SetScrollAddress()
 * @note The sum of all three parameters should be 320.
 * @param[in] TFA Number of lines in top fixed area, between 0 and 320
 * @param[in] VSA Number of lines in vertical scroll area, between 0 and 320
 * @param[in] BFA Number of lines in bottom fixed area, between 0 and 320
 */
#define lcd_SetScrollArea(TFA, VSA, BFA) lcd_SendCommandWords(VSCRDEF, 3, TFA, VSA, BFA)
/**
 * Sets the vertical scroll start address.
 * @see lcd_SetScrollArea()
 * @note In typical usage, this address should be in the range [TFA, 320-BFA) so no lines are repeated.
 * Whenever a displayed line address within the vertical scroll area would be at least 320-BFA,
 * it will have (320-BFA)-TFA subtracted from it to cause wrapping within that range.
 * @param[in] addr The source line to display at the start of the vertical scroll area
 */
#define lcd_SetScrollAddress(addr) lcd_SendCommandWords(VSCSAD, 1, addr)

/**
 * Sets the start and end lines (inclusive) for the displayed area in Partial Mode.
 * @see lcd_SetPartialMode()
 * @note If the start line is greater than the end line, the displayed area wraps around.
 * @param[in] PSL Partial start line, between 0 and 319
 * @param[in] PEL Partial end line, between 0 and 319
 */
#define lcd_SetPartialArea(PSL, PEL) lcd_SendCommandWords(PTLAR, 2, PSL, PEL)
/**
 * Sets Partial Mode settings.
 * Can be used to set the color of lines outside the partial display area, as well as configure interval scan for those lines.
 *
 * ::LCD_PARCTRL_DEFAULT can be used to restore the default settings.
 *
 * @see lcd_SetPartialMode()
 * @param[in] param A bitwise OR of each field from ::lcd_parctrl
 */
#define lcd_SetPartialControl(param) lcd_SendCommand1(LCD_CMD_PARCTRL, param)

/**
 * Sets the RAM access order flags.
 * These flags are useful for changing the order pixels are copied to the LCD RAM,
 * including copying in column-major order by setting ::LCD_MV, which can help avoid screen tearing.
 *
 * ::LCD_MADCTL_DEFAULT can be used to restore the default settings.
 *
 * @note Often, it makes sense to start with ::LCD_MADCTL_DEFAULT and then XOR any flags that need to be changed.
 * @param[in] param A bitwise OR of flags from ::lcd_madctl
 */
#define lcd_SetRamAccessOrder(param) lcd_SendCommand1(LCD_CMD_MADCTL, param)
/**
 * Sets the column address range (inclusive) for copying pixels to the LCD RAM.
 * The valid range depends on whether the configured RAM access order is row major or column major.
 * @see lcd_SetRamAccessOrder()
 * @param[in] XS Column start address, between 0 and 319/239
 * @param[in] XE Column end address, between 0 and 319/239
 */
#define lcd_SetColumnAddress(XS, XE) lcd_SendCommandWords(CASET, 2, XS, XE)
/**
 * Sets the row address range (inclusive) for copying pixels to the LCD RAM.
 * The valid range depends on the configured RAM access order is row major or column major.
 * @see lcd_SetRamAccessOrder()
 * @param[in] YS Row start address, between 0 and 239/319
 * @param[in] YE Row end address, between 0 and 239/319
 */
#define lcd_SetRowAddress(YS, YE) lcd_SendCommandWords(RASET, 2, YS, YE)

/**
 * Starts a pixel write operation, resetting the RAM pointer to the start of the column/row address range.
 * Pixels can be sent as raw parameter data with lcd_SendParamsRaw() until issuing another command.
 * To continue from the next pixel after issuing another command, use lcd_ContinuePixelWrite().
 * @note The RAM interface must first be set to SPI with lcd_SetRamInterface() or lcd_SetRamControl().
 */
#define lcd_StartPixelWrite() lcd_SendCommand(LCD_CMD_RAMWR)
/**
 * Continues a pixel write operation without resetting the RAM pointer.
 * Pixels can be sent as raw parameter data with lcd_SendParamsRaw() until issuing another command.
 * To continue from the next pixel after issuing another command, this command can be used again.
 * @note The RAM interface must first be set to SPI with lcd_SetRamInterface() or lcd_SetRamControl().
 */
#define lcd_ContinuePixelWrite() lcd_SendCommand(LCD_CMD_RAMWRC)
/**
 * Sets the pixel formats for SPI and RGB interfaces.
 * ::LCD_COLMOD_DEFAULT can be used to restore the default settings.
 * @param[in] param A bitwise OR of each field from ::lcd_colmod
 */
#define lcd_SetPixelFormat(param) lcd_SendCommand1(LCD_CMD_COLMOD, param)
/**
 * Sets the RAM interface and display mode settings.
 * ::LCD_RAMCTRL1_DEFAULT can be used to restore the default settings.
 * @param[in] param A bitwise OR of each field from ::lcd_ramctrl1
 */
#define lcd_SetRamInterface(param) lcd_SendCommand1(LCD_CMD_RAMCTRL, param)
/**
 * Sets all RAM control settings.
 * ::LCD_RAMCTRL1_DEFAULT and ::LCD_RAMCTRL2_DEFAULT can be used to restore the default settings.
 * @param[in] param1 A bitwise OR of each field from ::lcd_ramctrl1
 * @param[in] param2 A bitwise OR of each field from ::lcd_ramctrl2
 */
#define lcd_SetRamControl(param1, param2) lcd_SendCommand2(LCD_CMD_RAMCTRL, param1, param2)

/**
 * Sets gate control flags.
 * This overrides any previous setting of lcd_SetInterlacedMode(), and vice versa.
 *
 * ::LCD_GATECTRL_DEFAULT can be used to restore the default setting.
 *
 * @param[in] param A bitwise OR of flags from ::lcd_gatectrl
 */
#define lcd_SetGateControl(param) lcd_SendCommandBytes(GATECTRL, 3, LCD_GC_NL_DEFAULT, LCD_GC_SCN_DEFAULT, param)
/**
 * Sets inverted settings flags.
 * These flags invert the effects of various other settings.
 *
 * ::LCD_LCMCTRL_DEFAULT can be used to restore the default settings.
 *
 * @note Often, it makes sense to start with ::LCD_LCMCTRL_DEFAULT and then XOR any flags that need to be inverted.
 * @param[in] param A bitwise OR of flags from ::lcd_lcmctrl
 */
#define lcd_SetInvertedSettings(param) lcd_SendCommand1(LCD_CMD_LCMCTRL, param)

/**
 * Sets frame rate control settings for Normal Mode.
 * ::LCD_FRCTRL_DEFAULT can be used to restore the default setting.
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] param A bitwise OR of each field from ::lcd_frctrl
 */
#define lcd_SetNormalFrameRateControl(param) lcd_SendCommand1(LCD_CMD_FRCTRL2, param)
/**
 * Sets the frame rate clock divider and disables separate frame rate control.
 * To enable separate frame rate control as well, use lcd_EnableDividedSeparateFrameRateControl().
 *
 * ::LCD_DIV_DEFAULT can be used to restore the default setting.
 *
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] DIV A clock divider constant from ::lcd_frctrl1
 */
#define lcd_SetFrameRateDivider(DIV) lcd_SendCommand1(LCD_CMD_FRCTRL1, DIV | LCD_FRS_DISABLE)
/**
 * Enables and sets separate frame rate control settings for Idle Mode and Partial Mode.
 * Also resets the frame rate divider to the default.
 * To set the frame rate divider as well, use lcd_EnableDividedSeparateFrameRateControl().
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] idle A bitwise OR of each field from ::lcd_frctrl to be used in Idle Mode
 * @param[in] partial A bitwise OR of each field from ::lcd_frctrl to be used in Partial Mode
 */
#define lcd_EnableSeparateFrameRateControl(idle, partial) lcd_EnableDividedIdlePartialFrameRateControl(LCD_DIV_DEFAULT, idle, partial)
/**
 * Enables and sets separate frame rate control settings for Idle Mode and Partial Mode,
 * with an additional clock divider.
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] DIV A clock divider constant from ::lcd_frctrl1.
 * @param[in] idle A bitwise OR of each field from ::lcd_frctrl to be used in Idle Mode
 * @param[in] partial A bitwise OR of each field from ::lcd_frctrl to be used in Partial Mode
 */
#define lcd_EnableDividedSeparateFrameRateControl(DIV, idle, partial) lcd_SendCommandBytes(FRCTRL1, 3, DIV | LCD_FRS_ENABLE, idle, partial)
/**
 * Disables separate frame rate control settings for Idle Mode and Partial Mode.
 * Also resets the frame rate divider to the default. To avoid resetting the divider, use lcd_SetFrameRateDivider() instead.
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 */
#define lcd_DisableSeparateFrameRateControl() lcd_SetFrameRateDivider(LCD_DIV_DEFAULT)

/**
 * Sets porch control settings for Normal Mode.
 * #LCD_BP_DEFAULT and #LCD_FP_DEFAULT can be used to restore the default settings.
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] BPA Number of lines in back porch, between 1 and 127. Used only with ::LCD_DM_MCU or ::LCD_DM_VSYNC
 * @param[in] FPA Number of lines in front porch, between 1 and 127. Used only with ::LCD_DM_MCU
 */
#define lcd_SetNormalPorchControl(BP, FP) lcd_SendCommand2(LCD_CMD_PORCTRL, BPA, FPA)
/**
 * Sets only the back porch control setting for Normal Mode.
 * #LCD_BP_DEFAULT can be used to restore the default setting.
 * @note This setting is most useful when setting ::LCD_DM_VSYNC in lcd_SetRamInterface(),
 * because the front porch setting is not used in that mode.
 * @param[in] BPA Number of lines in back porch, between 1 and 127. Used only with ::LCD_DM_MCU or ::LCD_DM_VSYNC
 */
#define lcd_SetNormalBackPorchControl(BPA) lcd_SendCommand1(LCD_CMD_PORCTRL, BPA)
/**
 * Enables and sets separate porch control for Idle Mode and Partial Mode.
 * Requires specifying porch settings for Normal Mode as well.
 *
 * #LCD_BP_DEFAULT and #LCD_FP_DEFAULT can be used to specify default settings for any mode.
 *
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] BPA Number of lines in Normal Mode back porch, between 1 and 127
 * @param[in] FPA Number of lines in Normal Mode front porch, between 1 and 127
 * @param[in] BPB Number of lines in Idle Mode back porch, a multiple of 4 between 4 and 60
 * @param[in] FPB Number of lines in Idle Mode front porch, a multiple of 4 between 4 and 60
 * @param[in] BPC Number of lines in Partial Mode back porch, a multiple of 4 between 4 and 60
 * @param[in] FPC Number of lines in Partial Mode front porch, a multiple of 4 between 4 and 60
 */
#define lcd_EnableSeparatePorchControl(BPA, FPA, BPB, FPB, BPC, FPC) lcd_SendCommandBytes(PORCTRL, 5, BPA, FPA, LCD_PS_ENABLE, (BPB >> 2) | (FPB << 2), (BPC >> 2) | (FPC << 2))
/**
 * Disables separate porch control for Idle Mode and Partial Mode.
 * Requires specifying porch settings for Normal Mode, which will then apply to all modes.
 *
 * #LCD_BP_DEFAULT and #LCD_FP_DEFAULT can be used to restore the default settings.
 *
 * @note This setting only matters the LCD controller is using internal scan timing,
 * that is, when using a setting other than ::LCD_DM_RGB in lcd_SetRamInterface().
 * @param[in] BPA Number of lines in back porch, between 1 and 127
 * @param[in] FPA Number of lines in front porch, between 1 and 127
 */
#define lcd_DisableSeparatePorchControl(BPA, FPA) lcd_SendCommandBytes(PORCTRL, 3, BPA, FPA, LCD_PS_DISABLE)

/**
 * Enables or disables digital gamma.
 * Digital gamma mappings can be set using lcd_SetDigitalGammaTableRed() and lcd_SetDigitalGammaTableBlue().
 * @param[in] on Boolean indicating whether to enable digital gamma
 */
#define lcd_SetDigitalGamma(on) lcd_SendCommand1(LCD_CMD_DGMEN, (on) ? LCD_DGM_ENABLE : LCD_DGM_DISABLE)
/**
 * Sets the digital gamma mapping table for the Red component.
 * @note With the default BGR settings, this table actually modifies the Blue component's gamma.
 * Also, due to a hardware quirk, the LSB of the input component is forced to 0 before indexing the table.
 * @param[in] table A pointer to a 64-byte table, with the most significant 6 bits of each byte determining the output component value.
 */
#define lcd_SetDigitalGammaTableRed(table) lcd_SendCommandRaw(DGMLUTR, 64, table)
/**
 * Sets the digital gamma mapping table for the Blue component.
 * @note With the default BGR settings, this table actually modifies the Red component's gamma.
 * Also, due to a hardware quirk, the LSB of the input component is forced to 0 before indexing the table.
 * @param[in] table A pointer to a 64-byte table, with the most significant 6 bits of each byte determining the output component value.
 */
#define lcd_SetDigitalGammaTableBlue(table) lcd_SendCommandRaw(DGMLUTB, 64, table)

#define LCD_CMD_NOP         0x00 /**< No operation */
#define LCD_CMD_SWRESET     0x01 /**< Software reset */
//#define LCD_CMD_RDDID       0x04 /**< Read display ID */
//#define LCD_CMD_RDDST       0x09 /**< Read display status */
//#define LCD_CMD_RDDPM       0x0A /**< Read display power mode */
//#define LCD_CMD_RDDMADCTL   0x0B /**< Read display MADCTL */
//#define LCD_CMD_RDDCOLMOD   0x0C /**< Read display pixel format */
//#define LCD_CMD_RDDIM       0x0D /**< Read display image mode */
//#define LCD_CMD_RDDSM       0x0E /**< Read display signal mode */
//#define LCD_CMD_RDDSDR      0x0F /**< Read display self-diagnostic result */
#define LCD_CMD_SLPIN       0x10 /**< Sleep in */
#define LCD_CMD_SLPOUT      0x11 /**< Sleep out */
#define LCD_CMD_PTLON       0x12 /**< Partial display mode on */
#define LCD_CMD_NORON       0x13 /**< Normal display mode on */
#define LCD_CMD_INVOFF      0x20 /**< Display inversion off */
#define LCD_CMD_INVON       0x21 /**< Display inversion on */
#define LCD_CMD_GAMSET      0x26 /**< Gamma set */
/** Parameter values for #LCD_CMD_GAMSET */
typedef enum lcd_gamset {
    LCD_GAM_2_2 = 1, /**< Gamma 2.2 */
    LCD_GAM_1_8 = 2, /**< Gamma 1.8 */
    LCD_GAM_2_5 = 4, /**< Gamma 2.5 */
    LCD_GAM_1_0 = 8  /**< Gamma 1.0 */
} lcd_gamset_t;

#define LCD_CMD_DISPOFF     0x28 /**< Display off */
#define LCD_CMD_DISPON      0x29 /**< Display on */
#define LCD_CMD_CASET       0x2A /**< Column address set */
#define LCD_CMD_RASET       0x2B /**< Row address set */
#define LCD_CMD_RAMWR       0x2C /**< Memory write */
//#define LCD_CMD_RAMRD       0x2E /**< Memory read */
#define LCD_CMD_PTLAR       0x30 /**< Partial area */
#define LCD_CMD_VSCRDEF     0x33 /**< Vertical scrolling definition */
#define LCD_CMD_TEOFF       0x34 /**< Tearing effect line off */
#define LCD_CMD_TEON        0x35 /**< Tearing effect line on */
#define LCD_CMD_MADCTL      0x36 /**< Memory data access control */
/** Parameter flags for #LCD_CMD_MADCTL. @see lcd_SetRamAccessOrder() */
typedef enum lcd_madctl {
    LCD_MH  = 1 << 2, /**< Display data latch order (scan from bottom to top) */
    LCD_BGR = 1 << 3, /**< BGR order (swap red and blue) */
    LCD_ML  = 1 << 4, /**< Line address order (scan from right to left) */
    LCD_MV  = 1 << 5, /**< Page/column order (RAM access is column major) */
    LCD_MX  = 1 << 6, /**< Column address order (RAM access from bottom to top) */
    LCD_MY  = 1 << 7, /**< Page address order (RAM access from right to left) */
    LCD_MADCTL_DEFAULT = LCD_BGR /**< TI-OS default parameters */
} lcd_madctl_t;

#define LCD_CMD_VSCSAD      0x37 /**< Vertical scroll start address of RAM */
#define LCD_CMD_IDMOFF      0x38 /**< Idle mode off */
#define LCD_CMD_IDMON       0x39 /**< Idle mode on */
#define LCD_CMD_COLMOD      0x3A /**< Interface pixel format */
/** Pixel format field values */
typedef enum lcd_pxlfmt {
    LCD_PXLFMT_12BPP = 3, /**< 12 bits per pixel (SPI only) */
    LCD_PXLFMT_16BPP = 5, /**< 16 bits per pixel */
    LCD_PXLFMT_18BPP = 6, /**< 18 bits per pixel */
    LCD_PXLFMT_MASK  = 7  /**< Bitmask for PXLFMT field */
} lcd_pxlfmt_t;
/** Parameter fields for #LCD_CMD_COLMOD. @see lcd_SetPixelFormat() */
typedef enum lcd_colmod {
    LCD_SPI_12BPP = LCD_PXLFMT_12BPP << 0, /**< 12 bits per pixel over SPI interface */
    LCD_SPI_16BPP = LCD_PXLFMT_16BPP << 0, /**< 16 bits per pixel over SPI interface */
    LCD_SPI_18BPP = LCD_PXLFMT_18BPP << 0, /**< 18 bits per pixel over SPI interface */
    LCD_RGB_16BPP = LCD_PXLFMT_16BPP << 4, /**< 16 bits per pixel over RGB interface */
    LCD_RGB_18BPP = LCD_PXLFMT_18BPP << 4, /**< 18 bits per pixel over RGB interface */
    LCD_SPI_MASK  = LCD_PXLFMT_MASK  << 0, /**< Bitmask for SPI field */
    LCD_RGB_MASK  = LCD_PXLFMT_MASK  << 4, /**< Bitmask for RGB field */
    LCD_SPI_DEFAULT = LCD_SPI_18BPP, /**< TI-OS default SPI bits per pixel */
    LCD_RGB_DEFAULT = LCD_RGB_18BPP, /**< TI-OS default RGB bits per pixel */
    LCD_COLMOD_DEFAULT = LCD_SPI_DEFAULT | LCD_RGB_DEFAULT /**< TI-OS default parameters */
} lcd_colmod_t;

#define LCD_CMD_RAMWRC      0x3C /**< Write memory continue */
//#define LCD_CMD_RAMRDC      0x3E /**< Read memory continue */
#define LCD_CMD_STE         0x44 /**< Set tear scanline */
//#define LCD_CMD_GSCAN       0x45 /**< Get scanline */
//#define LCD_CMD_WRDISBV     0x51 /**< Write display brightness */
//#define LCD_CMD_RDDISBV     0x52 /**< Read display brightness */
//#define LCD_CMD_WRCTRLD     0x53 /**< Write CTRL display */
//#define LCD_CMD_RDCTRLD     0x54 /**< Read CTRL value display */
//#define LCD_CMD_WRCACE      0x55 /**< Write content adaptive brightness control and color enhancement */
//#define LCD_CMD_RDCABC      0x56 /**< Read content adaptive brightness control */
//#define LCD_CMD_WRCABCMB    0x5E /**< Write CABC minimum brightness */
//#define LCD_CMD_RDCABCMB    0x5F /**< Read CABC minimum brightness */
//#define LCD_CMD_RDABCSDR    0x68 /**< Read automatic brightness control self-diagnostic result */
#define LCD_CMD_RAMCTRL     0xB0 /**< RAM control */
/** Fields for parameter byte 1 of #LCD_CMD_RAMCTRL. @see lcd_SetRamInterface() */
typedef enum lcd_ramctrl1 {
    LCD_DM_MCU   = 0 << 0, /**< MCU display mode (internal timing) */
    LCD_DM_RGB   = 1 << 0, /**< RGB display mode (RGB interface timing) */
    LCD_DM_VSYNC = 2 << 0, /**< VSYNC display mode (internal timing except for RGB interface VSYNC) */
    LCD_RAM_SPI  = 0 << 4, /**< RAM access over SPI interface */
    LCD_RAM_RGB  = 1 << 4, /**< RAM access over RGB interface */
    LCD_DM_MASK  = 3 << 0, /**< Bitmask for DM field */
    LCD_RAM_MASK = 1 << 4, /**< Bitmask for RAM field */
    LCD_DM_DEFAULT = LCD_DM_RGB, /**< TI-OS default display mode */
    LCD_RAM_DEFAULT = LCD_RAM_RGB, /**< TI-OS default RAM access */
    LCD_RAMCTRL1_DEFAULT = LCD_DM_DEFAULT | LCD_RAM_DEFAULT /**< TI-OS default parameters */
} lcd_ramctrl1_t;
/** Fields for parameter byte 2 of #LCD_CMD_RAMCTRL. @see lcd_SetRamControl() */
typedef enum lcd_ramctrl2 {
    LCD_BUS_18BIT = 0 << 2, /**< 18-bit bus for RGB interface (use this on the CE) */
    LCD_BUS_6BIT  = 1 << 2, /**< 6-bit bus for RGB interface (not used on the CE) */
    LCD_ENDIAN_BIG = 0 << 3, /**< Big endian order for 16-bit pixels sent over SPI */
    LCD_ENDIAN_LITTLE = 1 << 3, /**< Little endian order for 16-bit pixels sent over SPI */
    LCD_EPF_0 = 0 << 4, /**< Expanded pixel format where component LSBs are set to 0 */
    LCD_EPF_1 = 1 << 4, /**< Expanded pixel format where component LSBs are set to 1 */
    LCD_EPF_MSB = 2 << 4, /**< Expanded pixel format where component LSBs are copied from the MSBs */
    LCD_EPF_GREEN = 3 << 4, /**< Expanded pixel format where component LSBs are copied from green LSB */
    LCD_WEMODE_SPI_STOP = 0 << 6, /**< Stop-at-end mode for SPI interface; after writing the last row and column, ignore further pixels */
    LCD_WEMODE_SPI_WRAP = 1 << 6, /**< Wrap-at-end mode for SPI interface; after writing the last row and column, wrap to the start */
    LCD_WEMODE_RGB_WRAP = 0 << 7, /**< Wrap-at-end mode for RGB interface; after writing the last row and column, wrap to the start */
    LCD_WEMODE_RGB_STOP = 1 << 7, /**< Stop-at-end mode for RGB interface; after writing the last row and column, ignore further pixels */
    LCD_BUS_MASK = 1 << 2, /**< Bitmask for BUS field */
    LCD_ENDIAN_MASK = 1 << 3, /**< Bitmask for ENDIAN field */
    LCD_EPF_MASK = 3 << 4, /**< Bitmask for EPF field */
    LCD_WEMODE_SPI_MASK = 1 << 6, /**< Bitmask for WEMODE_SPI field */
    LCD_WEMODE_RGB_MASK = 1 << 7, /**< Bitmask for WEMODE_RGB field */
    LCD_BUS_DEFAULT = LCD_BUS_18BIT, /**< TI-OS default RGB interface bus width */
    LCD_ENDIAN_DEFAULT = LCD_ENDIAN_BIG, /**< TI-OS default endian order for 16-bit pixels sent over SPI */
    LCD_EPF_DEFAULT = LCD_EPF_GREEN, /**< TI-OS default expanded pixel format */
    LCD_WEMODE_SPI_DEFAULT = LCD_WEMODE_SPI_WRAP, /**< TI-OS default wrap-at-end mode for SPI interface */
    LCD_WEMODE_RGB_DEFAULT = LCD_WEMODE_RGB_STOP, /**< TI-OS default wrap-at-end mode for RGB interface */
    LCD_RAMCTRL2_DEFAULT = LCD_BUS_DEFAULT | LCD_ENDIAN_DEFAULT | LCD_EPF_DEFAULT | LCD_WEMODE_SPI_DEFAULT | LCD_WEMODE_RGB_DEFAULT /**< TI-OS default parameters */
} lcd_ramctrl2_t;

#define LCD_CMD_RGBCTRL     0xB1 /**< RGB interface control */
/** Flags and fields for parameter byte 1 of #LCD_CMD_RGBCTRL */
typedef enum lcd_rgbctrl {
    LCD_EPL  = 1 << 0, /**< ENABLE signal polarity for RGB interface (set for low) */
    LCD_DPL  = 1 << 1, /**< DOTCLK signal polarity for RGB interface (set for falling edge) */
    LCD_HSPL = 1 << 2, /**< HSYNC signal polarity for RGB interface (set for high active) */
    LCD_VSPL = 1 << 3, /**< VSYNC signal polarity for RGB interface (set for high active) */
    LCD_RCM_DE = 2 << 5, /**< Set RGB DE (Data Enable) mode */
    LCD_RCM_HV = 3 << 5, /**< Set RGB HV (HSYNC/VSYNC) mode */
    LCD_WO = 1 << 7, /**< Enable direct RGB mode, bypassing RAM */
    LCD_RCM_MASK = 3 << 5, /**< Mask for RCM field */
    LCD_RCM_DEFAULT = 0 << 5, /**< TI-OS default RGB control mode (functionally equivalent to ::LCD_RCM_DE) */
    LCD_RGBCTRL_DEFAULT = LCD_RCM_DEFAULT | LCD_EPL /**< TI-OS default parameters */
} lcd_rgbctrl_t;
#define LCD_VBP_DEFAULT 5 /**< TI-OS default for parameter byte 2 of #LCD_CMD_RGBCTRL (defined as 5) */
#define LCD_HBP_DEFAULT 20 /**< TI-OS default for parameter byte 3 of #LCD_CMD_RGBCTRL (defined as 20) */

#define LCD_CMD_PORCTRL     0xB2 /**< Porch setting */
#define LCD_BP_DEFAULT 12 /**< TI-OS default back porch for #LCD_CMD_PORCTRL parameters (defined as 12) */
#define LCD_FP_DEFAULT 12 /**< TI-OS default front porch for #LCD_CMD_PORCTRL parameters (defined as 12) */
/** Values for parameter byte 3 of #LCD_CMD_PORCTRL. @see lcd_EnableSeparatePorchControl() */
typedef enum lcd_porctrl {
    LCD_PS_DISABLE = 0, /**< Disable separate porch control */
    LCD_PS_ENABLE = 1, /**< Enable separate porch control */
    LCD_PS_DEFAULT = LCD_PS_DISABLE /**< TI-OS default parameter */
} lcd_porctrl_t;

#define LCD_CMD_FRCTRL1     0xB3 /**< Frame rate control 1 (in partial mode/idle colors) */
/** Fields for parameter byte 1 of #LCD_CMD_FRCTRL1. @see lcd_SetFrameRateDivider() */
typedef enum lcd_frctrl1 {
    LCD_DIV_1 = 0 << 0, /**< Divide LCD internal pixel clock rate by 1 (10 MHz) */
    LCD_DIV_2 = 1 << 0, /**< Divide LCD internal pixel clock rate by 2 (5 MHz) */
    LCD_DIV_4 = 2 << 0, /**< Divide LCD internal pixel clock rate by 4 (2.5 MHz) */
    LCD_DIV_8 = 3 << 0, /**< Divide LCD internal pixel clock rate by 8 (1.25 MHz) */
    LCD_FRS_DISABLE = 0 << 4, /**< Disable separate frame rate control for Idle Mode and Partial Mode */
    LCD_FRS_ENABLE = 1 << 4, /**< Enable separate frame rate control for Idle Mode and Partial Mode */
    LCD_DIV_MASK = 3 << 0, /**< Bitmask for DIV field */
    LCD_FRS_MASK = 1 << 4, /**< Bitmask for FRS field */
    LCD_DIV_DEFAULT = LCD_DIV_1, /**< TI-OS default pixel clock divider */
    LCD_FRS_DEFAULT = LCD_FRS_DISABLE, /**< TI-OS default separate frame rate control setting */
    LCD_FRCTRL1_DEFAULT = LCD_DIV_DEFAULT | LCD_FRS_DEFAULT /**< TI-OS default parameters */
} lcd_frctrl1_t;

#define LCD_CMD_PARCTRL     0xB5 /**< Partial control */
/** Parameter fields for #LCD_CMD_PARCTRL. @see lcd_SetPartialControl() */
typedef enum lcd_parctrl {
    LCD_ISC_NONE = 0 << 0, /**< Interval scan mode disabled */
    LCD_ISC_1  = 16 << 0, /**< Non-display area is scanned every frame */
    LCD_ISC_3  = 17 << 0, /**< Non-display area is scanned every 3 frames */
    LCD_ISC_5  = 18 << 0, /**< Non-display area is scanned every 5 frames */
    LCD_ISC_7  = 19 << 0, /**< Non-display area is scanned every 7 frames */
    LCD_ISC_9  = 20 << 0, /**< Non-display area is scanned every 9 frames */
    LCD_ISC_11 = 21 << 0, /**< Non-display area is scanned every 11 frames */
    LCD_ISC_13 = 22 << 0, /**< Non-display area is scanned every 13 frames */
    LCD_ISC_15 = 23 << 0, /**< Non-display area is scanned every 15 frames */
    LCD_ISC_17 = 24 << 0, /**< Non-display area is scanned every 17 frames */
    LCD_ISC_19 = 25 << 0, /**< Non-display area is scanned every 19 frames */
    LCD_ISC_21 = 26 << 0, /**< Non-display area is scanned every 21 frames */
    LCD_ISC_23 = 27 << 0, /**< Non-display area is scanned every 23 frames */
    LCD_ISC_25 = 28 << 0, /**< Non-display area is scanned every 25 frames */
    LCD_ISC_27 = 29 << 0, /**< Non-display area is scanned every 27 frames */
    LCD_ISC_29 = 30 << 0, /**< Non-display area is scanned every 29 frames */
    LCD_ISC_31 = 31 << 0, /**< Non-display area is scanned every 31 frames */
    LCD_NDL_WHITE = 0 << 7, /**< Non-display area is displayed as white */
    LCD_NDL_BLACK = 1 << 7, /**< Non-display area is displayed as black */
    LCD_ISC_MASK = 31 << 0, /**< Bitmask for ISC field */
    LCD_NDL_MASK = 1 << 7, /**< Bitmask for NDL field */
    LCD_ISC_DEFAULT = LCD_ISC_NONE, /**< TI-OS default interval scan cycle setting */
    LCD_NDL_DEFAULT = LCD_NDL_WHITE, /**< TI-OS default non-display level setting */
    LCD_PARCTRL_DEFAULT = LCD_ISC_DEFAULT | LCD_NDL_DEFAULT /**< TI-OS default parameters */
} lcd_parctrl_t;

//#define LCD_CMD_GCTRL       0xB7 /**< Gate control */
#define LCD_CMD_GTADJ       0xB8 /**< Gate on timing adjustment */
#define LCD_CMD_DGMEN       0xBA /**< Digital gamma enable */
/** Parameter values for #LCD_CMD_DGMEN. @see lcd_SetDigitalGamma() */
typedef enum lcd_dgmen {
    LCD_DGM_DISABLE = 0 << 2, /**< Disable digital gamma */
    LCD_DGM_ENABLE = 1 << 2, /**< Enable digital gamma */
    LCD_DGM_DEFAULT = LCD_DGM_DISABLE /**< TI-OS default digital gamma setting */
} lcd_dgmen_t;

//#define LCD_CMD_VCOMS       0xBB /**< VCOM setting */
#define LCD_CMD_POWSAVE     0xBC /**< Power saving mode */
#define LCD_CMD_DLPOFFSAVE  0xBD /**< Display off power save */
#define LCD_CMD_LCMCTRL     0xC0 /**< LCM control */
/** Parameter flags for #LCD_CMD_LCMCTRL. @see lcd_SetInvertedSettings() */
typedef enum lcd_lcmctrl {
    LCD_XGS  = 1 << 0, /**< Set to invert the effect of ::LCD_GS. @see lcd_SetGateControl() */
    LCD_XMV  = 1 << 1, /**< Set to invert the effect of ::LCD_MV. @see lcd_SetRamAccessOrder() */
    LCD_XMH  = 1 << 2, /**< Set to invert the effect of ::LCD_MH. @see lcd_SetRamAccessOrder() */
    LCD_XMX  = 1 << 3, /**< Set to invert the effect of ::LCD_MX. @see lcd_SetRamAccessOrder() */
    LCD_XINV = 1 << 4, /**< Set to invert the effect of ::LCD_CMD_INVOFF and ::LCD_CMD_INVON. @see lcd_SetInvertedMode() */
    LCD_XBGR = 1 << 5, /**< Set to invert the effect of ::LCD_BGR. @see lcd_SetRamAccessOrder() */
    LCD_XMY  = 1 << 6, /**< Set to invert the effect of ::LCD_MY. @see lcd_SetRamAccessOrder() */
    LCD_LCMCTRL_DEFAULT = LCD_XMV | LCD_XBGR /**< TI-OS default parameters */
} lcd_lcmctrl_t;

#define LCD_CMD_IDSET       0xC1 /**< ID code setting */
//#define LCD_CMD_VDVVRHEN    0xC2 /**< VDV and VRH command enable */
//#define LCD_CMD_VRHS        0xC3 /**< VRH set */
//#define LCD_CMD_VDV         0xC4 /**< VDV set */
#define LCD_CMD_VCMOFSET    0xC5 /**< VCOM offset set */
#define LCD_CMD_FRCTRL2     0xC6 /**< Frame rate control in normal mode */
/** Parameter fields for #LCD_CMD_FRCTRL2 and parameter bytes 2 and 3 of #LCD_CMD_FRCTRL1. @see lcd_SetNormalFrameRateControl() */
typedef enum lcd_frctrl {
    LCD_RTN_250 =  0 << 0, /**< 250 pixel clocks per line (119 Hz with default porches). Should not be used or internal RAM reads will fail. */
    LCD_RTN_266 =  1 << 0, /**< 266 pixel clocks per line (111 Hz with default porches) */
    LCD_RTN_282 =  2 << 0, /**< 282 pixel clocks per line (105 Hz with default porches) */
    LCD_RTN_298 =  3 << 0, /**< 282 pixel clocks per line (99 Hz with default porches) */
    LCD_RTN_314 =  4 << 0, /**< 314 pixel clocks per line (94 Hz with default porches) */
    LCD_RTN_330 =  5 << 0, /**< 330 pixel clocks per line (90 Hz with default porches) */
    LCD_RTN_346 =  6 << 0, /**< 346 pixel clocks per line (86 Hz with default porches) */
    LCD_RTN_362 =  7 << 0, /**< 362 pixel clocks per line (82 Hz with default porches) */
    LCD_RTN_378 =  8 << 0, /**< 378 pixel clocks per line (78 Hz with default porches) */
    LCD_RTN_394 =  9 << 0, /**< 394 pixel clocks per line (75 Hz with default porches) */
    LCD_RTN_410 = 10 << 0, /**< 410 pixel clocks per line (72 Hz with default porches) */
    LCD_RTN_426 = 11 << 0, /**< 426 pixel clocks per line (69 Hz with default porches) */
    LCD_RTN_442 = 12 << 0, /**< 442 pixel clocks per line (67 Hz with default porches) */
    LCD_RTN_458 = 13 << 0, /**< 458 pixel clocks per line (64 Hz with default porches) */
    LCD_RTN_474 = 14 << 0, /**< 474 pixel clocks per line (62 Hz with default porches) */
    LCD_RTN_490 = 15 << 0, /**< 490 pixel clocks per line (60 Hz with default porches) */
    LCD_RTN_506 = 16 << 0, /**< 506 pixel clocks per line (58 Hz with default porches) */
    LCD_RTN_522 = 17 << 0, /**< 522 pixel clocks per line (57 Hz with default porches) */
    LCD_RTN_538 = 18 << 0, /**< 538 pixel clocks per line (55 Hz with default porches) */
    LCD_RTN_554 = 19 << 0, /**< 554 pixel clocks per line (53 Hz with default porches) */
    LCD_RTN_570 = 20 << 0, /**< 570 pixel clocks per line (52 Hz with default porches) */
    LCD_RTN_586 = 21 << 0, /**< 586 pixel clocks per line (50 Hz with default porches) */
    LCD_RTN_602 = 22 << 0, /**< 602 pixel clocks per line (49 Hz with default porches) */
    LCD_RTN_618 = 23 << 0, /**< 618 pixel clocks per line (48 Hz with default porches) */
    LCD_RTN_634 = 24 << 0, /**< 634 pixel clocks per line (46 Hz with default porches) */
    LCD_RTN_650 = 25 << 0, /**< 650 pixel clocks per line (45 Hz with default porches) */
    LCD_RTN_666 = 26 << 0, /**< 666 pixel clocks per line (44 Hz with default porches) */
    LCD_RTN_682 = 27 << 0, /**< 682 pixel clocks per line (43 Hz with default porches) */
    LCD_RTN_698 = 28 << 0, /**< 698 pixel clocks per line (42 Hz with default porches) */
    LCD_RTN_714 = 29 << 0, /**< 714 pixel clocks per line (41 Hz with default porches) */
    LCD_RTN_730 = 30 << 0, /**< 730 pixel clocks per line (40 Hz with default porches) */
    LCD_RTN_746 = 31 << 0, /**< 746 pixel clocks per line (39 Hz with default porches) */
    LCD_NL_DOT = 0 << 5, /**< Dot-based polarity inversion */
    LCD_NL_COLUMN = 7 << 5, /**< Column-based polarity inversion */
    LCD_RTN_MASK = 31 << 0, /**< Bitmask for RTN field */
    LCD_NL_MASK = 7 << 5, /**< Bitmask for NL field */
    LCD_RTN_DEFAULT = LCD_RTN_490, /**< TI-OS default pixel clocks per line */
    LCD_NL_DEFAULT = LCD_NL_DOT, /**< TI-OS default polarity inversion mode */
    LCD_FRCTRL_DEFAULT = LCD_RTN_DEFAULT | LCD_NL_DEFAULT /**< TI-OS default parameters */
} lcd_frctrl_t;

//#define LCD_CMD_CABCCTRL    0xC7 /**< CABC control */
//#define LCD_CMD_REGSEL1     0xC8 /**< Register value selection 1 */
//#define LCD_CMD_REGSEL2     0xC9 /**< Register value selection 2 */
//#define LCD_CMD_PWMFRSEL    0xCC /**< PWM frequency selection */
//#define LCD_CMD_PWCTRL1     0xD0 /**< Power control 1 */
//#define LCD_CMD_VAPVANEN    0xD2 /**< Enable VAP/VAN signal output */
//#define LCD_CMD_RDID1       0xDA /**< Read ID1 */
//#define LCD_CMD_RDID2       0xDB /**< Read ID2 */
//#define LCD_CMD_RDID3       0xDC /**< Read ID3 */
//#define LCD_CMD_CMD2EN      0xDF /**< Command 2 enable */
#define LCD_CMD_PVGAMCTRL   0xE0 /**< Positive voltage gamma control */
#define LCD_CMD_NVGAMCTRL   0xE1 /**< Negative voltage gamma control */
#define LCD_CMD_DGMLUTR     0xE2 /**< Digital gamma lookup table for red */
#define LCD_CMD_DGMLUTB     0xE3 /**< Digital gamma lookup table for blue */
#define LCD_CMD_GATECTRL    0xE4 /**< Gate control */
/** Values for parameter byte 1 of #LCD_CMD_GATECTRL */
typedef enum lcd_gatectrl_nl {
    LCD_GC_NL_8   = 0,  /**<   8 physical lines in the display */
    LCD_GC_NL_16  = 1,  /**<  16 physical lines in the display */
    LCD_GC_NL_24  = 2,  /**<  24 physical lines in the display */
    LCD_GC_NL_32  = 3,  /**<  32 physical lines in the display */
    LCD_GC_NL_40  = 4,  /**<  40 physical lines in the display */
    LCD_GC_NL_48  = 5,  /**<  48 physical lines in the display */
    LCD_GC_NL_56  = 6,  /**<  56 physical lines in the display */
    LCD_GC_NL_64  = 7,  /**<  64 physical lines in the display */
    LCD_GC_NL_72  = 8,  /**<  72 physical lines in the display */
    LCD_GC_NL_80  = 9,  /**<  80 physical lines in the display */
    LCD_GC_NL_88  = 10, /**<  88 physical lines in the display */
    LCD_GC_NL_96  = 11, /**<  96 physical lines in the display */
    LCD_GC_NL_104 = 12, /**< 104 physical lines in the display */
    LCD_GC_NL_112 = 13, /**< 112 physical lines in the display */
    LCD_GC_NL_120 = 14, /**< 120 physical lines in the display */
    LCD_GC_NL_128 = 15, /**< 128 physical lines in the display */
    LCD_GC_NL_136 = 16, /**< 136 physical lines in the display */
    LCD_GC_NL_144 = 17, /**< 144 physical lines in the display */
    LCD_GC_NL_152 = 18, /**< 152 physical lines in the display */
    LCD_GC_NL_160 = 19, /**< 160 physical lines in the display */
    LCD_GC_NL_168 = 20, /**< 168 physical lines in the display */
    LCD_GC_NL_176 = 21, /**< 176 physical lines in the display */
    LCD_GC_NL_184 = 22, /**< 184 physical lines in the display */
    LCD_GC_NL_192 = 23, /**< 192 physical lines in the display */
    LCD_GC_NL_200 = 24, /**< 200 physical lines in the display */
    LCD_GC_NL_208 = 25, /**< 208 physical lines in the display */
    LCD_GC_NL_216 = 26, /**< 216 physical lines in the display */
    LCD_GC_NL_224 = 27, /**< 224 physical lines in the display */
    LCD_GC_NL_232 = 28, /**< 232 physical lines in the display */
    LCD_GC_NL_240 = 29, /**< 240 physical lines in the display */
    LCD_GC_NL_248 = 30, /**< 248 physical lines in the display */
    LCD_GC_NL_256 = 31, /**< 256 physical lines in the display */
    LCD_GC_NL_264 = 32, /**< 264 physical lines in the display */
    LCD_GC_NL_272 = 33, /**< 272 physical lines in the display */
    LCD_GC_NL_280 = 34, /**< 280 physical lines in the display */
    LCD_GC_NL_288 = 35, /**< 288 physical lines in the display */
    LCD_GC_NL_296 = 36, /**< 296 physical lines in the display */
    LCD_GC_NL_304 = 37, /**< 304 physical lines in the display */
    LCD_GC_NL_312 = 38, /**< 312 physical lines in the display */
    LCD_GC_NL_320 = 39, /**< 320 physical lines in the display */
    LCD_GC_NL_DEFAULT = LCD_GC_NL_320 /**< TI-OS default parameter */
} lcd_gatectrl_nl_t;
/** Values for parameter byte 2 of #LCD_CMD_GATECTRL */
typedef enum lcd_gatectrl_scn {
    LCD_GC_SCN_0   = 0,  /**< Display starts at gate 0   */
    LCD_GC_SCN_8   = 1,  /**< Display starts at gate 8   */
    LCD_GC_SCN_16  = 2,  /**< Display starts at gate 16  */
    LCD_GC_SCN_24  = 3,  /**< Display starts at gate 24  */
    LCD_GC_SCN_32  = 4,  /**< Display starts at gate 32  */
    LCD_GC_SCN_40  = 5,  /**< Display starts at gate 40  */
    LCD_GC_SCN_48  = 6,  /**< Display starts at gate 48  */
    LCD_GC_SCN_56  = 7,  /**< Display starts at gate 56  */
    LCD_GC_SCN_64  = 8,  /**< Display starts at gate 64  */
    LCD_GC_SCN_72  = 9,  /**< Display starts at gate 72  */
    LCD_GC_SCN_80  = 10, /**< Display starts at gate 80  */
    LCD_GC_SCN_88  = 11, /**< Display starts at gate 88  */
    LCD_GC_SCN_96  = 12, /**< Display starts at gate 96  */
    LCD_GC_SCN_104 = 13, /**< Display starts at gate 104 */
    LCD_GC_SCN_112 = 14, /**< Display starts at gate 112 */
    LCD_GC_SCN_120 = 15, /**< Display starts at gate 120 */
    LCD_GC_SCN_128 = 16, /**< Display starts at gate 128 */
    LCD_GC_SCN_136 = 17, /**< Display starts at gate 136 */
    LCD_GC_SCN_144 = 18, /**< Display starts at gate 144 */
    LCD_GC_SCN_152 = 19, /**< Display starts at gate 152 */
    LCD_GC_SCN_160 = 20, /**< Display starts at gate 160 */
    LCD_GC_SCN_168 = 21, /**< Display starts at gate 168 */
    LCD_GC_SCN_176 = 22, /**< Display starts at gate 176 */
    LCD_GC_SCN_184 = 23, /**< Display starts at gate 184 */
    LCD_GC_SCN_192 = 24, /**< Display starts at gate 192 */
    LCD_GC_SCN_200 = 25, /**< Display starts at gate 200 */
    LCD_GC_SCN_208 = 26, /**< Display starts at gate 208 */
    LCD_GC_SCN_216 = 27, /**< Display starts at gate 216 */
    LCD_GC_SCN_224 = 28, /**< Display starts at gate 224 */
    LCD_GC_SCN_232 = 29, /**< Display starts at gate 232 */
    LCD_GC_SCN_240 = 30, /**< Display starts at gate 240 */
    LCD_GC_SCN_248 = 31, /**< Display starts at gate 248 */
    LCD_GC_SCN_256 = 32, /**< Display starts at gate 256 */
    LCD_GC_SCN_264 = 33, /**< Display starts at gate 264 */
    LCD_GC_SCN_272 = 34, /**< Display starts at gate 272 */
    LCD_GC_SCN_280 = 35, /**< Display starts at gate 280 */
    LCD_GC_SCN_288 = 36, /**< Display starts at gate 288 */
    LCD_GC_SCN_296 = 37, /**< Display starts at gate 296 */
    LCD_GC_SCN_304 = 38, /**< Display starts at gate 304 */
    LCD_GC_SCN_312 = 39, /**< Display starts at gate 312 */
    LCD_GC_SCN_DEFAULT = LCD_GC_SCN_0 /**< TI-OS default parameter */
} lcd_gatectrl_scn_t;
/** Values for parameter byte 3 of #LCD_CMD_GATECTRL. @see lcd_SetGateControl() */
typedef enum lcd_gatectrl {
    LCD_GS = 1 << 0, /**< Gate scan direction (scan from right to left) */
    LCD_SS = 1 << 1, /**< Source scan direction (scan from bottom to top) */
    LCD_SM = 1 << 2, /**< Interlaced scan mode. @see lcd_SetInterlacedMode() */
    LCD_TMG = 1 << 4, /**< Gate mirror selection (local mirror for displays with fewer than 320 lines) */
    LCD_GATECTRL_DEFAULT = LCD_TMG /**< TI-OS default parameters */
} lcd_gatectrl_t;

//#define LCD_CMD_SPI2EN      0xE7 /**< SPI2 enable */
//#define LCD_CMD_PWCTRL2     0xE8 /**< Power control 2 */
#define LCD_CMD_EQCTRL      0xE9 /**< Equalize time control */
//#define LCD_CMD_PROMCTRL    0xEC /**< Program mode control */
//#define LCD_CMD_PROMEN      0xFA /**< Program mode enable */
//#define LCD_CMD_NVMSET      0xFC /**< NVM setting */
//#define LCD_CMD_PROMACT     0xFE /**< Program action */

/* Raw parameter structures */
/* @cond */
typedef struct lcd_gamset_params {
    uint8_t GC : 4;
    uint8_t : 4;
} lcd_gamset_params_t;

typedef struct lcd_ptlar_params {
    uint16_t PSL;
    uint16_t PEL;
} lcd_ptlar_params_t;

typedef struct lcd_vscrdef_params {
    uint16_t TFA;
    uint16_t VSA;
    uint16_t BFA;
} lcd_vscrdef_params_t;

typedef struct lcd_colmod_params {
    uint8_t MCU : 3;
    uint8_t : 1;
    uint8_t RGB : 3;
    uint8_t : 1;
} lcd_colmod_params_t;

typedef struct lcd_madctl_params {
    uint8_t : 2;
    uint8_t MH : 1;
    uint8_t RGB : 1;
    uint8_t ML : 1;
    uint8_t MV : 1;
    uint8_t MX : 1;
    uint8_t MY : 1;
} lcd_madctl_params_t;

typedef struct lcd_vscsad_params {
    uint16_t VSP;
} lcd_vscsad_params_t;

typedef struct lcd_ramctrl_params {
    uint8_t DM : 2; /**< Display mode */
    uint8_t : 2;
    uint8_t RM : 1;
    uint8_t : 3;

    uint8_t MDT : 2;
    uint8_t RIM : 1;
    uint8_t ENDIAN : 1;
    uint8_t EPF : 2;
    uint8_t WEMODE0 : 1;
    uint8_t WEMODE1 : 1;
} lcd_ramctrl_params_t;

typedef struct lcd_rgbctrl_params {
    uint8_t EPL : 1;
    uint8_t DPL : 1;
    uint8_t HSPL : 1;
    uint8_t VSPL : 1;
    uint8_t : 1;
    uint8_t RCM : 2;
    uint8_t WO : 1;

    uint8_t VBP : 7;
    uint8_t : 1;

    uint8_t HBP : 5;
    uint8_t : 3;
} lcd_rgbctrl_params_t;

typedef struct lcd_porctrl_params {
    uint8_t BPA : 7;
    uint8_t : 1;

    uint8_t FPA : 7;
    uint8_t : 1;

    uint8_t PSEN : 1;
    uint8_t : 7;

    uint8_t FPB : 4;
    uint8_t BPB : 4;

    uint8_t FPC : 4;
    uint8_t BPC : 4;
} lcd_porctrl_params_t;

typedef struct lcd_frctrl1_params {
    uint8_t DIV : 2;
    uint8_t : 2;
    uint8_t FRSEN : 1;
    uint8_t : 3;

    uint8_t RTNB : 5;
    uint8_t NLB : 3;

    uint8_t RTNC : 5;
    uint8_t NLC : 3;
} lcd_frctrl1_params_t;

typedef struct lcd_parctrl_params {
    uint8_t ISC : 4;
    uint8_t PTGISC : 1;
    uint8_t : 2;
    uint8_t NDL : 1;
} lcd_parctrl_params_t;

typedef struct lcd_gtadj_params {
    uint8_t PAD_2A;
    uint8_t PAD_2B;

    uint8_t GTA : 6;
    uint8_t : 2;

    uint8_t GOF : 4;
    uint8_t GOFR : 4;
} lcd_gtadj_params_t;

typedef struct lcd_dgmen_params {
    uint8_t : 2;
    uint8_t DGMEN : 1;
    uint8_t : 5;
} lcd_dgmen_params_t;

typedef struct lcd_powsave_params {
    uint8_t IS : 1;
    uint8_t NS : 1;
    uint8_t : 6;
} lcd_powsave_params_t;

typedef struct lcd_dlpoffsave_params {
    uint8_t DOFSAVE : 1;
    uint8_t : 7;
} lcd_dlpoffsave_params_t;

typedef struct lcd_lcmctrl_params {
    uint8_t XGS : 1;
    uint8_t XMV : 1;
    uint8_t XMH : 1;
    uint8_t XMX : 1;
    uint8_t XINV : 1;
    uint8_t XBGR : 1;
    uint8_t XMY : 1;
    uint8_t : 1;
} lcd_lcmctrl_params_t;

typedef struct lcd_vcmofset_params {
    uint8_t VCMOFS : 6;
    uint8_t : 2;
} lcd_vcmofset_params_t;

typedef struct lcd_frctrl2_params {
    uint8_t RTNA : 5;
    uint8_t NLA : 3;
} lcd_frctrl2_params_t;

typedef struct lcd_gamctrl_params {
    uint8_t V0 : 4;
    uint8_t V63 : 4;

    uint8_t V1 : 6;
    uint8_t : 2;

    uint8_t V2 : 6;
    uint8_t : 2;

    uint8_t V4 : 5;
    uint8_t : 3;

    uint8_t V6 : 5;
    uint8_t : 3;

    uint8_t V13 : 4;
    uint8_t J0 : 2;
    uint8_t : 2;

    uint8_t V20 : 7;
    uint8_t : 1;

    uint8_t V27 : 3;
    uint8_t : 1;
    uint8_t V36 : 3;
    uint8_t : 1;

    uint8_t V43 : 7;
    uint8_t : 1;

    uint8_t V50 : 4;
    uint8_t J1 : 2;
    uint8_t : 2;

    uint8_t V57 : 5;
    uint8_t : 3;

    uint8_t V59 : 5;
    uint8_t : 3;

    uint8_t V61 : 6;
    uint8_t : 2;

    uint8_t V62 : 6;
    uint8_t : 2;
} lcd_gamctrl_params_t;

typedef struct lcd_dgmlut_params {
    uint8_t DGMLUT[64];
} lcd_dgmlut_params_t;

typedef struct lcd_gatectrl_params {
    uint8_t NL : 6;
    uint8_t : 2;

    uint8_t SCN : 6;
    uint8_t : 2;

    uint8_t GS : 1;
    uint8_t SS : 1;
    uint8_t SM : 1;
    uint8_t : 1;
    uint8_t TMG : 1;
    uint8_t : 3;
} lcd_gatectrl_params_t;

typedef struct lcd_eqctrl_params {
    uint8_t SEQ : 5;
    uint8_t : 3;

    uint8_t SPRET : 5;
    uint8_t : 3;

    uint8_t GEQ : 4;
    uint8_t : 4;
} lcd_eqctrl_params_t;

/* @endcond */

#ifdef __cplusplus
}
#endif

#endif
