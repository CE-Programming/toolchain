/**
 * @file
 * @author Brendan "calc84maniac" Fletcher
 *
 * This is a library for interfacing with the calculator's LCD panel.
 * It is very low-level, providing the ability to send direct commands over SPI.
 * Convenience functions are provided for common commands.
 */

#ifndef LCDDRVCE_H
#define LCDDRVCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_SIZEDCMD(cmd, size) (LCD_CMD_##cmd | (size) << 8)

#define LCD_PARAM16(param) __builtin_bswap16(param)

/**
 * Initializes the LCD driver.
 * The first call to this function will reinitialize the SPI controller
 * to target the LCD and prepare the SPI controller to send data.
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
 * The last call to this function, corresponding to the first call to
 * lcd_Init(), will disable the SPI controller.
 * Implicitly calls lcd_Wait() in case there are commands in progress.
 * @note This will not restore any changed LCD settings.
 * If that is necessary, send commands to change them back to defaults.
 */
void lcd_Cleanup(void);

/**
 * Sends an LCD command with a pointer to its raw parameters.
 * Use the lcd_SendSizedCommandRaw convenience macro to specify
 * the command and the size of the parameters, in bytes.
 * Returns a pointer following the parameters, to simplify implementing
 * command lists.
 */
const void *lcd_SendCommandRaw(uint16_t sized_cmd, const void *params);

/**
 * Sends only raw parameters to a previously sent command.
 * Most useful for sending pixel data after LCD_CMD_RAMWR or LCD_CMD_RAMWRC.
 * Returns a pointer following the parameters.
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
 * Sends a command with any number of byte parameters.
 * Use the lcd_SendSizedCommandBytes convenience macro to specify
 * the command and the number of parameters.
 */
void lcd_SendCommandBytes(uint16_t sized_cmd, ...);

/**
 * Sends a command with any number of 16-bit word parameters.
 * Use the lcd_SendSizedCommandWords convenience macro to specify
 * the command and the number of parameters.
 * The parameters should be passed as their actual values, and are
 * converted to big endian when transferred over SPI.
 */
void lcd_SendCommandWords(uint16_t sized_cmd, ...);

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

#define lcd_SendSizedCommandRaw(cmd, size, params) lcd_SendRawCommand(LCD_SIZEDCMD(cmd, size), params)
#define lcd_SendSizedCommandBytes(cmd, size, ...) lcd_SendCommandBytes(LCD_SIZEDCMD(cmd, size), __VA_ARGS__)
#define lcd_SendSizedCommandWords(cmd, size, ...) lcd_SendCommandWords(LCD_SIZEDCMD(cmd, size), __VA_ARGS__)

#define lcd_SetSleepMode(on) lcd_SendCommand((on) ? LCD_CMD_SLPIN : LCD_CMD_SLPOUT)
#define lcd_SetPartialMode(on) lcd_SendCommand((on) ? LCD_CMD_PTLON : LCD_CMD_NORON)
#define lcd_SetInvertedMode(on) lcd_SendCommand((on) ? LCD_CMD_INVON : LCD_CMD_INVOFF)
#define lcd_SetIdleMode(on) lcd_SendCommand((on) ? LCD_CMD_IDMON : LCD_CMD_IDMOFF)
#define lcd_SetInterlacedMode(on) lcd_SendSizedCommandBytes(GATECTRL, 3, LCD_GATECTRL_NL_DEFAULT, LCD_GATECTRL_SCN_DEFAULT, LCD_TMG | ((on) ? LCD_SM : 0))

#define lcd_SetColumnAddress(XS, XE) lcd_SendSizedCommandWords(CASET, 2, XS, XE)
#define lcd_SetRowAddress(YS, YE) lcd_SendSizedCommandWords(RASET, 2, YS, YE)

#define lcd_StartPixelWrite() lcd_SendCommand(LCD_CMD_RAMWR)
#define lcd_ContinuePixelWrite() lcd_SendCommand(LCD_CMD_RAMWRC)

#define lcd_SetPartialArea(PSL, PEL) lcd_SendSizedCommandWords(PTLAR, 2, PSL, PEL)
#define lcd_SetScrollArea(TFA, VSA, BFA) lcd_SendSizedCommandWords(VSCRDEF, 3, TFA, VSA, BFA)
#define lcd_SetScrollAddress(addr) lcd_SendSizedCommandWords(VSCSAD, 1, addr)

#define lcd_SetRamAccessOrder(param) lcd_SendCommand1(LCD_CMD_MADCTL, param)
#define lcd_SetPixelFormat(param) lcd_SendCommand1(LCD_CMD_COLMOD, param)

#define lcd_SetRamInterface(param) lcd_SendCommand1(LCD_CMD_RAMCTRL, param)
#define lcd_SetRamControl(param1, param2) lcd_SendCommand2(LCD_CMD_RAMCTRL, param1, param2)

#define lcd_SetNormalPorchControl(BPA, FPA) lcd_SendCommand2(LCD_CMD_PORCTRL, BPA, FPA)
#define lcd_SetNormalFrameRateControl(RTNA) lcd_SendCommand1(LCD_CMD_FRCTRL2, RTNA)

#define lcd_SetDigitalGamma(on) lcd_SendCommand1(LCD_CMD_DGMEN, (on) ? LCD_DGMEN : 0)

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
typedef struct lcd_gamset {
    uint8_t GC : 4;
    uint8_t : 4;
} lcd_gamset_t;
#define LCD_GAM_2_2 1
#define LCD_GAM_1_8 2
#define LCD_GAM_2_5 4
#define LCD_GAM_1_0 8

#define LCD_CMD_DISPOFF     0x28 /**< Display off */
#define LCD_CMD_DISPON      0x29 /**< Display on */
#define LCD_CMD_CASET       0x2A /**< Column address set */
#define LCD_CMD_RASET       0x2B /**< Row address set */
#define LCD_CMD_RAMWR       0x2C /**< Memory write */
//#define LCD_CMD_RAMRD       0x2E /**< Memory read */
#define LCD_CMD_PTLAR       0x30 /**< Partial area */
typedef struct lcd_ptlar {
	uint16_t PSL;
	uint16_t PEL;
} lcd_ptlar_t;
#define LCD_CMD_VSCRDEF     0x33 /**< Vertical scrolling definition */
typedef struct lcd_vscrdef {
	uint16_t TFA;
	uint16_t VSA;
	uint16_t BFA;
} lcd_vscrdef_t;
#define LCD_CMD_TEOFF       0x34 /**< Tearing effect line off */
#define LCD_CMD_TEON        0x35 /**< Tearing effect line on */
#define LCD_CMD_MADCTL      0x36 /**< Memory data access control */
typedef struct lcd_madctl {
    uint8_t : 2;
    uint8_t MH : 1;
    uint8_t RGB : 1;
    uint8_t ML : 1;
    uint8_t MV : 1;
    uint8_t MX : 1;
    uint8_t MY : 1;
} lcd_madctl_t;
#define LCD_MH (1 << 2)
#define LCD_BGR (1 << 3)
#define LCD_ML (1 << 4)
#define LCD_MV (1 << 5)
#define LCD_MX (1 << 6)
#define LCD_MY (1 << 7)
#define LCD_MADCTL_DEFAULT LCD_BGR

#define LCD_CMD_VSCSAD      0x37 /**< Vertical scroll start address of RAM */
typedef struct lcd_vscsad {
	uint16_t VSP;
} lcd_vscsad_t;
#define LCD_CMD_IDMOFF      0x38 /**< Idle mode off */
#define LCD_CMD_IDMON       0x39 /**< Idle mode on */
#define LCD_CMD_COLMOD      0x3A /**< Interface pixel format */
typedef struct lcd_colmod {
    uint8_t MCU : 3;
    uint8_t : 1;
    uint8_t RGB : 3;
    uint8_t : 1;
} lcd_colmod_t;
#define LCD_PXLFMT_12BPP 3
#define LCD_PXLFMT_16BPP 5
#define LCD_PXLFMT_18BPP 6
#define LCD_MCU_12BPP (LCD_PXLFMT_12BPP << 0)
#define LCD_MCU_16BPP (LCD_PXLFMT_16BPP << 0)
#define LCD_MCU_18BPP (LCD_PXLFMT_18BPP << 0)
#define LCD_RGB_16BPP (LCD_PXLFMT_16BPP << 4)
#define LCD_RGB_18BPP (LCD_PXLFMT_18BPP << 4)
#define LCD_COLMOD_DEFAULT (LCD_MCU_18BPP | LCD_RGB_18BPP)

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
typedef struct lcd_ramctrl {
    uint8_t DM : 2;
    uint8_t : 2;
    uint8_t RM : 1;
    uint8_t : 3;

    uint8_t MDT : 2;
    uint8_t RIM : 1;
    uint8_t ENDIAN : 1;
    uint8_t EPF : 2;
    uint8_t WEMODE0 : 1;
	uint8_t WEMODE1 : 1;
} lcd_ramctrl_t;
#define LCD_DM_MCU 0
#define LCD_DM_RGB 1
#define LCD_DM_VSYNC 2
#define LCD_RAM_SPI (0 << 4)
#define LCD_RAM_RGB (1 << 4)
#define LCD_RAMCTRL1_DEFAULT (LCD_DM_RGB | LCD_RAM_RGB)

#define LCD_BUS_18BIT (0 << 2)
#define LCD_BUS_6BIT (1 << 2)
#define LCD_ENDIAN_BIG (0 << 3)
#define LCD_ENDIAN_LITTLE (1 << 3)
#define LCD_EPF_0 (0 << 4)
#define LCD_EPF_1 (1 << 4)
#define LCD_EPF_MSB (2 << 4)
#define LCD_EPF_GREEN (3 << 4)
#define LCD_WEMODE_SPI_STOP (0 << 6)
#define LCD_WEMODE_SPI_WRAP (1 << 6)
#define LCD_WEMODE_RGB_WRAP (0 << 7)
#define LCD_WEMODE_RGB_STOP (1 << 7)
#define LCD_RAMCTRL2_DEFAULT (LCD_BUS_18BIT | LCD_ENDIAN_BIG | LCD_EPF_GREEN | LCD_WEMODE_SPI_WRAP | LCD_WEMODE_RGB_STOP)

#define LCD_CMD_RGBCTRL     0xB1 /**< RGB interface control */
typedef struct lcd_rgbctrl {
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
} lcd_rgbctrl_t;
#define LCD_RGBCTRL_EPL (1 << 0)
#define LCD_RGBCTRL_DPL (1 << 1)
#define LCD_RGBCTRL_HSPL (1 << 2)
#define LCD_RGBCTRL_VSPL (1 << 3)
#define LCD_RGBCTRL_DE (2 << 5)
#define LCD_RGBCTRL_HV (3 << 5)
#define LCD_RGBCTRL_WO (1 << 7)
#define LCD_RGBCTRL_DEFAULT LCD_RGBCTRL_EPL
#define LCD_VBP_DEFAULT 5
#define LCD_HBP_DEFAULT 20

#define LCD_CMD_PORCTRL     0xB2 /**< Porch setting */
typedef struct lcd_porctrl {
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
} lcd_porctrl_t;
#define LCD_BPA_DEFAULT 12
#define LCD_FPA_DEFAULT 12

#define LCD_CMD_FRCTRL1     0xB3 /**< Frame rate control 1 (in partial mode/idle colors) */
typedef struct lcd_frctrl1 {
    uint8_t DIV : 2;
    uint8_t : 2;
    uint8_t FRSEN : 1;
    uint8_t : 3;

    uint8_t RTNB : 5;
    uint8_t NLB : 3;

    uint8_t RTNC : 5;
    uint8_t NLC : 3;
} lcd_frctrl1_t;
#define LCD_FRSEN (1 << 4)

#define LCD_CMD_PARCTRL     0xB5 /**< Partial control */
typedef struct lcd_parctrl {
    uint8_t ISC : 4;
    uint8_t PTGISC : 1;
    uint8_t : 2;
    uint8_t NDL : 1;
} lcd_parctrl_t;
//#define LCD_CMD_GCTRL       0xB7 /**< Gate control */
#define LCD_CMD_GTADJ       0xB8 /**< Gate on timing adjustment */
typedef struct lcd_gtadj {
    uint8_t PAD_2A;
    uint8_t PAD_2B;

    uint8_t GTA : 6;
    uint8_t : 2;

    uint8_t GOF : 4;
    uint8_t GOFR : 4;
} lcd_gtadj_t;
#define LCD_CMD_DGMEN       0xBA /**< Digital gamma enable */
typedef struct lcd_dgmen {
    uint8_t : 2;
    uint8_t DGMEN : 1;
    uint8_t : 5;
} lcd_dgmen_t;
#define LCD_DGMEN (1 << 2)

//#define LCD_CMD_VCOMS       0xBB /**< VCOM setting */
#define LCD_CMD_POWSAVE     0xBC /**< Power saving mode */
typedef struct lcd_powsave {
    uint8_t IS : 1;
    uint8_t NS : 1;
    uint8_t : 6;
} lcd_powsave_t;
#define LCD_CMD_DLPOFFSAVE  0xBD /**< Display off power save */
typedef struct lcd_dlpoffsave {
    uint8_t DOFSAVE : 1;
    uint8_t : 7;
} lcd_dlpoffsave_t;
#define LCD_CMD_LCMCTRL     0xC0 /**< LCM control */
typedef struct lcd_lcmctrl {
    uint8_t XGS : 1;
    uint8_t XMV : 1;
    uint8_t XMH : 1;
    uint8_t XMX : 1;
    uint8_t XINV : 1;
    uint8_t XBGR : 1;
    uint8_t XMY : 1;
    uint8_t : 1;
} lcd_lcmctrl_t;
#define LCD_XGS (1 << 0)
#define LCD_XMV (1 << 1)
#define LCD_XMH (1 << 2)
#define LCD_XMX (1 << 3)
#define LCD_XINV (1 << 4)
#define LCD_XBGR (1 << 5)
#define LCD_XMY (1 << 6)
#define LCD_LCMCTRL_DEFAULT (LCD_XMV | LCD_XBGR)

#define LCD_CMD_IDSET       0xC1 /**< ID code setting */
//#define LCD_CMD_VDVVRHEN    0xC2 /**< VDV and VRH command enable */
//#define LCD_CMD_VRHS        0xC3 /**< VRH set */
//#define LCD_CMD_VDV         0xC4 /**< VDV set */
#define LCD_CMD_VCMOFSET    0xC5 /**< VCOM offset set */
struct lcd_vcmofset {
    uint8_t VCMOFS : 6;
    uint8_t : 2;
} lcd_vcmofset_t;
#define LCD_CMD_FRCTRL2     0xC6 /**< Frame rate control in normal mode */
typedef struct lcd_frctrl2 {
    uint8_t RTNA : 5;
    uint8_t NLA : 3;
} lcd_frctrl2_t;
#define LCD_FRCTRL2_DEFAULT 15

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
typedef struct lcd_gamctrl {
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
} lcd_gamctrl_t;
#define LCD_CMD_DGMLUTR     0xE2 /**< Digital gamma lookup table for red */
#define LCD_CMD_DGMLUTB     0xE3 /**< Digital gamma lookup table for blue */
#define LCD_CMD_GATECTRL    0xE4 /**< Gate control */
typedef struct lcd_gatectrl {
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
} lcd_gatectrl_t;
#define LCD_GATECTRL_NL_DEFAULT 0x27
#define LCD_GATECTRL_SCN_DEFAULT 0x00
#define LCD_GS (1 << 0)
#define LCD_SS (1 << 1)
#define LCD_SM (1 << 2)
#define LCD_TMG (1 << 4)
#define LCD_GATECTRL_DEFAULT LCD_TMG

//#define LCD_CMD_SPI2EN      0xE7 /**< SPI2 enable */
//#define LCD_CMD_PWCTRL2     0xE8 /**< Power control 2 */
#define LCD_CMD_EQCTRL      0xE9 /**< Equalize time control */
typedef struct lcd_eqctrl {
    uint8_t SEQ : 5;
    uint8_t : 3;

    uint8_t SPRET : 5;
    uint8_t : 3;

    uint8_t GEQ : 4;
    uint8_t : 4;
} lcd_eqctrl_t;
//#define LCD_CMD_PROMCTRL    0xEC /**< Program mode control */
//#define LCD_CMD_PROMEN      0xFA /**< Program mode enable */
//#define LCD_CMD_NVMSET      0xFC /**< NVM setting */
//#define LCD_CMD_PROMACT     0xFE /**< Program action */

#ifdef __cplusplus
}
#endif

#endif
