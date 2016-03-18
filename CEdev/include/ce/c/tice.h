// Parts from Matt "MateoConLechuga" Waltz and Jacob "jacobly" Young, in addtion to
// contributors of http://wikiti.brandonw.net/index.php?title=84PCE:OS:Include_File
// Latest as of March. 5, 2016

#ifndef TICE_H
#define TICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Defines for MMIO memory areas */

/* RTC defines */
/* There’s a whole slew of bootcode RTC functions, but a lot of them are kind of pointless when you could just use these defines from MMIO */
#define rtc_GetSeconds()        (*((uint8_t*)0xF30000))
#define rtc_GetMinutes()        (*((uint8_t*)0xF30004))
#define rtc_GetHours()          (*((uint8_t*)0xF30008))
#define rtc_GetDays()           (*((uint16_t*)0xF3000C))
#define rtc_GetControl()        (*((uint8_t*)0xF30020))
#define rtc_SetControl(c)       ((*((uint8_t*)0xF30020)) = (uint8_t)(c))
#define rtc_LoadSetTime()       ((*((uint8_t*)0xF30020)) = (*((uint8_t*)0xF30020))|64)
#define rtc_SetSeconds(s)       ((*((uint8_t*)0xF30024)) = (uint8_t)(s))
#define rtc_SetMinutes(m)       ((*((uint8_t*)0xF30028)) = (uint8_t)(m))
#define rtc_SetHours(h)         ((*((uint8_t*)0xF3002C)) = (uint8_t)(h))
#define rtc_SetDays(d)          ((*((uint16_t*)0xF3002C)) = (uint16_t)(d))
#define rtc_Time()              (*(volatile uint32_t*)0xF30044)

/* LCD defines */
#define lcd_GetBacklightLevel()  (*((uint8_t*)0xF60024))
#define lcd_SetBacklightLevel(b) ((*((uint8_t*)0xF60024)) = (uint8_t)(b);

/**
 * OS varaible type definitions
 */
typedef struct { int8_t sign, exp; uint8_t mant[7]; } real_t;
typedef struct { real_t real, imag; } cplx_t;
typedef struct { uint16_t dim; real_t *items; } list_t;
typedef struct { uint16_t dim; cplx_t *items; } cplx_list_t;
typedef struct { uint8_t cols, rows; real_t *items; } matrix_t;
typedef struct { uint16_t size; uint8_t *data; } var_t;

/**
 * Cleans up everything and gets ready to enter back to the OS
 * when you are ready to exit your program
 */
void pgrm_CleanUp(void);

/**
 * A faster implementation of memset
 */
void *memset_fast(void *ptr,int value,size_t num);

/**
 * Returns the Bootcode version major
 */
uint8_t boot_GetBootVerMajor(void);

/**
 * Returns the Bootcode version minor
 */
uint8_t boot_GetBootVerMinor(void);

/**
 * Returns the Harware version
 */
uint8_t boot_GetHardwareVers(void);

/**
 * Turns all of VRAM into 0xFF (white)
 */
void boot_ClearVRAM(void);

/**
 * Checks if the [on] key was pressed
 */
bool boot_CheckOnPressed(void);

/**
 * Returns extended keys as 16-bits
 */
int os_GetKey(void);

/**
 * Performs an OS call to get the keypad scan code
 */
int os_GetCSC(void);

/**
 * Disables the OS cursor
 */
void os_DisableCursor(void);

/**
 * Enables the OS cursor
 */
void os_EnableCursor(void);

/**
 * Set/Get the foreground color used to draw text on the graphscreen
 */
void os_SetDrawFGColor(int color);
int os_GetDrawFGColor(void);

/**
 * Set/Get the backgroundground color used to draw text on the graphscreen
 * os_GetDrawBGColor is broken; use at your own risk
 */
void os_SetDrawBGColor(int color);
void os_GetDrawBGColor_BROKEN(int color);

/**
 * Set/Get the cursor posistion used on the homescreen
 */
void os_SetCursorPos(uint8_t curRow, uint8_t curCol);
void os_GetCursorPos(unsigned int *curRow, unsigned int *curCol);

/**
 * Selects/Gets the font to use when drawing on the graphscreen
 * 0: small font
 * 1: large monospace font
 */
void os_FontSelect(char id);
int os_FontGetID(void);

/**
 * Returns the width of a string in the varaible-width format
 * Second function is used to get the height of the characters
 */
int os_FontGetWidth(const char *string);
int os_FontGetHeight(void);

/**
 * Draws a text using the small font to the screen
 * Returns the end column
 */
int os_FontDrawText(const char *string, uint16_t col, uint8_t row);
int os_FontDrawTransText(const char *string, uint16_t col, uint8_t row);

/**
 * Puts some text at the current homescreen cursor location
 * Returns 1 if string fits on screen, 0 otherwise
 */
int os_PutStrFull(const char *string);

/**
 * Puts some text at the current homescreen cursor location
 * Returns 1 if string fits on line, 0 otherwise
 */
int os_PutStrLine(const char *string);

/**
 * Set/Get a particular flag variable
 */
void os_SetFlagByte(int offset, uint8_t set);
uint8_t os_GetFlagByte(int offset);

/**
 * Returns amount of free ram, free set to start of free ram
 */
size_t os_MemChk(void **free);

/**
 * Throws an OS error
 */
void os_ThrowError(uint8_t error);

/**
 * Returns a pointer to symtable of the OS
 */
void *os_GetSymTablePtr(void);

/**
 * Creates an appvar; and returns a pointer to the structure 
 * Returns NULL if creation failed for some reason, otherwise a pointer to the size bytes
 */
var_t *os_CreateAppVar(const char *name, uint16_t size);

/**
 * Returns next entry or NULL if no more entries, pass os_GetSymTablePtr() as first entry
 */
void *os_NextSymEntry(void *entry, uint24_t *type, uint24_t *nameLength, char *name, void **data);

/**
 * If file exists, returns 1 and sets entry and data, otherwise returns 0.
 * entry and/or data can be NULL if you don't care
 */
int os_ChkFindSym(uint8_t type, const char *name, void **entry, void **data);

/**
 * type is set to the current varaible type in ANS, and a pointer to the data is returned
 * Returns NULL if Ans doesn't exist or type is NULL
 */
void *os_RclAns(uint8_t *type);

/**
 * Copies a real_t type to another location
 * Returns dest
 */
real_t *os_RealCopy(real_t *dest, const real_t *src);

/**
 * Urnary operations used to interact with the OS math functions
 * All return result
 */
real_t *os_RealAcosRad(real_t *result, const real_t *arg);
real_t *os_RealAsinRad(real_t *result, const real_t *arg);
real_t *os_RealAtanRad(real_t *result, const real_t *arg);
real_t *os_RealCosRad(real_t *result, const real_t *arg);
real_t *os_RealRadToDeg(real_t *result, const real_t *arg);
real_t *os_RealExp(real_t *result, const real_t *arg);
real_t *os_RealFloor(real_t *result, const real_t *arg);
real_t *os_RealFrac(real_t *result, const real_t *arg);
real_t *os_RealRoundInt(real_t *result, const real_t *arg);
real_t *os_RealLog(real_t *result, const real_t *arg);
real_t *os_RealNeg(real_t *result, const real_t *arg);
real_t *os_RealDegToRad(real_t *result, const real_t *arg);
real_t *os_RealInv(real_t *result, const real_t *arg);
real_t *os_RealSinRad(real_t *result, const real_t *arg);
real_t *os_RealSqrt(real_t *result, const real_t *arg);
real_t *os_RealTanRad(real_t *result, const real_t *arg);
real_t *os_RealInt(real_t *result, const real_t *arg);
cplx_t *os_CplxSquare(cplx_t *result, const cplx_t *arg);

/**
 * Binary operations used to interact with the OS math functions
 * All return result
 */
real_t *os_RealAdd(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealDiv(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealGcd(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealLcm(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealMax(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealMin(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealMul(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealNcr(real_t *result, const real_t *total, const real_t *num);
real_t *os_RealNpr(real_t *result, const real_t *total, const real_t *num);
real_t *os_RealPow(real_t *result, const real_t *base, const real_t *exp);
real_t *os_RealRandInt(real_t *result, const real_t *min, const real_t *max);
real_t *os_RealMod(real_t *result, const real_t *arg1, const real_t *arg2);
real_t *os_RealSub(real_t *result, const real_t *arg1, const real_t *arg2);
/**
 * digits must be in the range 0 - 9
 */
real_t *os_RealRound(real_t *result, const real_t *arg, char digits);

/**
 * Returns -1, 0, or 1 depending on the comparison
 */
int os_RealCompare(const real_t *arg1, const real_t *arg2);

/** os_RealToStr:
  *  This converts a ti-float to a ti-ascii string.
  *  result: zero terminated string copied to this address
  *  arg: real to convert
  * maxLength: 
  *  <=0: use default max length (14)
  *  >0:  max length of result, minimum of 6
  * mode:
  *  0: Use current mode for everything (digits ignored)
  *  1: Normal mode
  *  2: Sci mode
  *  3: Eng mode
  *  >4: Use current Normal/Sci/Eng mode (digits still used)
  * digits:
  *  -1:  Float mode
  *  0-9: Fix # mode
  *  returns length of result
  */
int os_RealToStr(char *result, const real_t *arg, char maxLength, char mode, char digits);

/** os_StrToReal:
  *  This converts a ti-ascii string to a ti-float.
  *  String format regexp: / *[-\032+]?[0-9]*(\.[0-9]*)?([eE\033][-\032+]?[0-9]*)?/
  *  result: resulting ti-float stored here, on exponent overflow this is +-9.9999999999999e99
  *  string: ti-ascii string to convert
  *  end: if non-null, pointer to end of parsed number is stored here
  *  returns result
  */
real_t *os_StrToReal(real_t *result, const char *string, char **end);

/** 
 * Basically a reimplemented form of printf that prints to some debugging device
 */
void boot_DebugPrintf(const char *string);

/**
 * Turns off the calculator (probably not a good idea to use)
 */
void boot_TurnOff(void);

/**
 * Inserts a new line at the current cursor posistion on the homescreen
 */
void boot_NewLine(void);

/**
 * Prints the boot version at a really silly place on the homescreen
 */
void boot_PrintBootVersion(void);

/**
 * Sets the calculator into 6MHz mode and 48MHz modes. Note that the ones
 * suffix with I perserve the interrupt vectors
 */
void boot_Set6MHzMode(void);
void boot_Set48MHzMode(void);
void boot_Set6MHzModeI(void);
void boot_Set48MHzModeI(void);

/**
 * Returns the current battery status
 */
uint8_t boot_GetBatteryStatus(void);

/**
 * Waits for just a bit
 * Someone should really look at this to see how long it actually is
 */
void boot_WaitShort(void);

/**
 * Checks if the calculator is being powered via USB
 */
bool boot_USBPowered(void);

/**
 * Checks if there is not a USB plug of A type in the USB port
 */
bool boot_NotPlugTypeA(void);

/**
 * Set the time of the calculator
 */
void boot_SetTime(uint8_t seconds, uint8_t minutes, uint8_t hours);

/**
 * High 8 is unsigned offset, low 8 is bits to test
 * os_TestFlagBits will return a 0 or 1
 */
int os_TestFlagBits(uint16_t offset_pattern);
void os_SetFlagBits(int16_t offset_pattern);
void os_ResetFlagBits(int16_t offset_pattern);

/**
 * Whole bunch of possibly useful timer functions
 */
void boot_SetTimersControlRegister(uint16_t value);
uint16_t boot_GetTimersControlRegister(void);
void boot_SetTimersInterruptStatus(uint16_t value);
uint16_t boot_GetTimersInterruptStatus(void);
void boot_SetTimersInterruptMask(uint16_t value);
uint16_t boot_GetTimersInterruptMask(void);
void boot_SetTimer1Counter(uint32_t count);
uint32_t boot_GetTimer1Counter(void);
void boot_SetTimer1ReloadValue(uint32_t value);
uint32_t boot_GetTimer1ReloadValue(void);
void boot_SetTimer1MatchValue1(uint32_t value);
uint32_t boot_GetTimer1MatchValue1(void);
void boot_SetTimer1MatchValue2(uint32_t value);
uint32_t boot_GetTimer1MatchValue2(void);
void boot_SetTimer2Counter(uint32_t count);
uint32_t boot_GetTimer2Counter(void);
void boot_SetTimer2ReloadValue(uint32_t value);
uint32_t boot_GetTimer2ReloadValue(void);
void boot_SetTimer2MatchValue1(uint32_t value);
uint32_t boot_GetTimer2MatchValue1(void);
void boot_SetTimer2MatchValue2(uint32_t value);
uint32_t boot_GetTimer2MatchValue2(void);

/**
 * Things you shouldn't use unless you know what you are doing:
 */
void os_ForceCmdNoChar(void);
/* ============================================ */

/* === OS and Bootcode Funtion Wrapper ======== */
#pragma asm "xref __saveIY"
#define _OS(FUNC) \
    do { \
      asm("	LD	(__saveIY),IY"); \
      asm("	LD	IY, 13631616"); \
      FUNC ; \
      asm("	LD	IY,(__saveIY)"); \
    } while (0)
/* ============================================ */

#endif
