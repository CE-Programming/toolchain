// Parts from Matt "MateoConLechuga" Waltz and Jacob "jacobly" Young, in addtion to
// contributors of http://wikiti.brandonw.net/index.php?title=84PCE:OS:Include_File
// Latest as of June 2016

#ifndef TICE_H
#define TICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Creates a random integer value */
#define randInt(min, max)	((unsigned)rand() % ((max) - (min) + 1) + (min))

/* RTC define -- useful for srand() */
#define rtc_Time()	(*(volatile uint32_t*)0xF30044)

/* RTC definitions */
#define RTC_UNFREEZE        (1<<7)
#define RTC_FREEZE          (0<<7)
#define RTC_LOAD            (1<<6)
#define RTC_ENABLE          (1<<0)|RTC_UNFREEZE
#define RTC_DISABLE         (0<<0)

#define rtc_Seconds         (*(volatile uint8_t*)0xF30000)
#define rtc_Minutes         (*(volatile uint8_t*)0xF30004)
#define rtc_Hours           (*(volatile uint8_t*)0xF30008)
#define rtc_Days            (*(volatile uint16_t*)0xF3000C)
#define rtc_AlarmSeconds    (*(uint8_t*)0xF30010)
#define rtc_AlarmMinutes    (*(uint8_t*)0xF30014)
#define rtc_AlarmHours      (*(uint8_t*)0xF30018)
#define rtc_Control         (*(uint8_t*)0xF30020)
#define rtc_LoadSeconds     (*(uint8_t*)0xF30024)
#define rtc_LoadMinutes     (*(uint8_t*)0xF30028)
#define rtc_LoadHours       (*(uint8_t*)0xF3002C)
#define rtc_LoadDays        (*(uint16_t*)0xF30030)
#define rtc_IntStatus       (*(volatile uint8_t*)0xF30034)
#define rtc_IntAcknowledge  (*(volatile uint8_t*)0xF30034)
#define rtc_IsBusy()        (rtc_Control & RTC_LOAD)

/**
 * RTC interrupt masks
 */
#define RTC_ALARM_INT_SOURCE    (1<<5)
#define RTC_DAY_INT_SOURCE      (1<<4)
#define RTC_HR_INT_SOURCE       (1<<3)
#define RTC_MIN_INT_SOURCE      (1<<2)
#define RTC_SEC_INT_SOURCE      (1<<1)

#define RTC_LOAD_INT            (1<<5)
#define RTC_ALARM_INT           (1<<4)
#define RTC_DAY_INT             (1<<3)
#define RTC_HR_INT              (1<<2)
#define RTC_MIN_INT             (1<<1)
#define RTC_SEC_INT             (1<<0)
#define RTC_INT_MASK            (RTC_SEC_INT | RTC_MIN_INT | RTC_HR_INT | RTC_DAY_INT | RTC_ALARM_INT | RTC_LOAD_INT)

/**
 * LCD defines
 */
#define lcd_BacklightLevel	(*(uint8_t*)0xF60024)

/**
 * Resets the RTC back to its original values
 * If enable is true, the RTC will be enabled during this function
 */
void boot_RTCInitialize(bool enable);

/**
 * Returns a pointer to the system stats
 */
void *os_GetSystemStats(void);

/**
 * Sets up the defualt error handlers if an OS routine encounters an error when running
 */
void os_PushErrorHandler(void *routine);
void os_PopErrorHandler(void);

/**
 * OS varaible type definitions
 */
typedef struct { int8_t sign, exp; uint8_t mant[7]; } real_t;
typedef struct { real_t real, imag; } cplx_t;
typedef struct { uint16_t dim; real_t items[1]; } list_t;
typedef struct { uint16_t dim; cplx_t items[1]; } cplx_list_t;
typedef struct { uint8_t cols, rows; real_t items[1]; } matrix_t;
typedef struct { uint16_t len; char data[1]; } string_t;
typedef struct { uint16_t size; uint8_t data[1]; } var_t;

/**
 * Cleans up everything and gets ready to enter back to the OS
 * when you are ready to exit your program
 */
void prgm_CleanUp(void);

/* This is here because Mateo can't spell */
#define pgrm_CleanUp prgm_CleanUp

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
 * os_GetDrawBGColor is only useable in OS 5.2 and above; use at your own risk
 */
void os_SetDrawBGColor(int color);
void os_GetDrawBGColor(int color);

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
void *os_NextSymEntry(void *entry, uint24_t *type, uint24_t *nameLength, const char *name, void **data);

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
 * Copies a real_t
 */
real_t os_RealCopy(const real_t *src);

/**
 * Unary operations used to interact with the OS math functions
 */
real_t os_RealAcosRad(const real_t *arg);
real_t os_RealAsinRad(const real_t *arg);
real_t os_RealAtanRad(const real_t *arg);
real_t os_RealCosRad(const real_t *arg);
real_t os_RealRadToDeg(const real_t *arg);
real_t os_RealExp(const real_t *arg);
real_t os_RealFloor(const real_t *arg);
real_t os_RealFrac(const real_t *arg);
real_t os_RealRoundInt(const real_t *arg);
real_t os_RealLog(const real_t *arg);
real_t os_RealNeg(const real_t *arg);
real_t os_RealDegToRad(const real_t *arg);
real_t os_RealInv(const real_t *arg);
real_t os_RealSinRad(const real_t *arg);
real_t os_RealSqrt(const real_t *arg);
real_t os_RealTanRad(const real_t *arg);
real_t os_RealInt(const real_t *arg);
cplx_t os_CplxSquare(const cplx_t *arg);

/**
 * Binary operations used to interact with the OS math functions
 */
real_t os_RealAdd(const real_t *arg1, const real_t *arg2);
real_t os_RealDiv(const real_t *arg1, const real_t *arg2);
real_t os_RealGcd(const real_t *arg1, const real_t *arg2);
real_t os_RealLcm(const real_t *arg1, const real_t *arg2);
real_t os_RealMax(const real_t *arg1, const real_t *arg2);
real_t os_RealMin(const real_t *arg1, const real_t *arg2);
real_t os_RealMul(const real_t *arg1, const real_t *arg2);
real_t os_RealNcr(const real_t *total, const real_t *num);
real_t os_RealNpr(const real_t *total, const real_t *num);
real_t os_RealPow(const real_t *base, const real_t *exp);
real_t os_RealRandInt(const real_t *min, const real_t *max);
real_t os_RealMod(const real_t *arg1, const real_t *arg2);
real_t os_RealSub(const real_t *arg1, const real_t *arg2);
/**
 * digits must be in the range 0 - 9
 */
real_t os_RealRound(const real_t *arg, char digits);

/**
 * Returns -1, 0, or 1 depending on the comparison
 */
int os_RealCompare(const real_t *arg1, const real_t *arg2);

/**
 * Conversion routines for ti-floats.
 * All saturate on overflow.
 */
int24_t os_RealToInt24(const real_t *arg);
real_t os_Int24ToReal(int24_t arg);
float os_RealToFloat(const real_t *arg);
real_t os_FloatToReal(float arg);

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
real_t os_StrToReal(const char *string, char **end);

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
 * Whole bunch of useful timer functions
 * Use the below defines to send to boot_SetTimersControlRegister
 */
#define TIMER1_ENABLE	1 << 0	// Enables Timer 1
#define TIMER1_DISABLE	0 << 0	// Disables Timer 1
#define TIMER1_32K	1 << 1	// Use the 32K clock for timer 1
#define TIMER1_CPU	0 << 1	// Use the CPU clock rate for timer 1
#define TIMER1_0INT	1 << 2	// Enable an interrupt when 0 is reached for the timer 1
#define TIMER1_NOINT	0 << 2	// Disable interrupts for the timer 1
#define TIMER1_UP	1 << 9	// Timer 1 counts up
#define TIMER1_DOWN	0 << 9	// Timer 1 counts down

#define TIMER2_ENABLE	1 << 3	// Enables Timer 2
#define TIMER2_DISABLE	0 << 3	// Enables Timer 2
#define TIMER2_32K	1 << 4	// Use the 32K clock for timer 2
#define TIMER2_CPU	0 << 4	// Use the CPU clock rate for timer 2
#define TIMER2_0INT	1 << 5	// Enable an interrupt when 0 is reached for the timer 2
#define TIMER2_NOINT	0 << 5	// Disable interrupts for the timer 2
#define TIMER2_UP	1 << 10	// Timer 2 counts up
#define TIMER2_DOWN	0 << 10	// Timer 2 counts down

/* These defines can be used to check the status of the timer */
#define TIMER1_MATCH1	1 << 0	// Timer 1 hit the first match value
#define TIMER1_MATCH2	1 << 1	// Timer 1 hit the second match value
#define TIMER1_RELOADED	1 << 2	// Timer 1 was reloaded (Needs to have TIMER1_0INT enabled)

#define TIMER2_MATCH1	1 << 3	// Timer 2 hit the first match value
#define TIMER2_MATCH2	1 << 4	// Timer 2 hit the second match value
#define TIMER2_RELOADED	1 << 5	// Timer 2 was reloaded (Needs to have TIMER2_0INT enabled)

#define timer_1_Counter		(*(volatile uint32_t *)0xF20000)
#define timer_2_Counter		(*(volatile uint32_t *)0xF20010)
#define timer_1_ReloadValue	(*(uint32_t *)0xF20004)
#define timer_2_ReloadValue	(*(uint32_t *)0xF20014)
#define timer_1_MatchValue_1	(*(uint32_t *)0xF20008) 
#define timer_1_MatchValue_2	(*(uint32_t *)0xF2000C)
#define timer_2_MatchValue_1	(*(uint32_t *)0xF20018)
#define timer_2_MatchValue_2	(*(uint32_t *)0xF2001C)
#define timer_Control		(*(uint32_t *)0xF20030)
#define timer_EnableInt		(*(uint16_t *)0xF20038)
#define timer_IntStatus		(*(volatile uint16_t *)0xF20034)
#define timer_IntAcknowledge	(*(volatile uint16_t *)0xF20034)

/**
 * Returns extended keys as 16-bits
 */
int os_GetKey(void);

/**
 * Performs an OS call to get the keypad scan code
 * Values returned are listed below
 */
int os_GetCSC(void);
typedef uint8_t sk_key_t;
#define sk_Down       0x01
#define sk_Left       0x02
#define sk_Right      0x03
#define sk_Up         0x04
#define sk_Enter      0x09
#define sk_2nd        0x36
#define sk_Clear      0x0F
#define sk_Alpha      0x30
#define sk_Add        0x0A
#define sk_Sub        0x0B
#define sk_Mul        0x0C
#define sk_Div        0x0D
#define sk_Graph      0x31
#define sk_Trace      0x32
#define sk_Zoom       0x33
#define sk_Window     0x34
#define sk_Yequ       0x35
#define sk_Mode       0x37
#define sk_Del        0x38
#define sk_Store      0x2A
#define sk_Ln         0x2B
#define sk_Log        0x2C
#define sk_Square     0x2D
#define sk_Recip      0x2E
#define sk_Math       0x2F
#define sk_0          0x21
#define sk_1          0x22
#define sk_4          0x23
#define sk_7          0x24
#define sk_2          0x1A
#define sk_5          0x1B
#define sk_8          0x1C
#define sk_3          0x12
#define sk_6          0x13
#define sk_9          0x14
#define sk_Comma      0x25
#define sk_Sin        0x26
#define sk_Apps       0x27
#define sk_GraphVar   0x28
#define sk_DecPnt     0x19
#define sk_LParen     0x1D
#define sk_Cos        0x1E
#define sk_Prgm       0x1F
#define sk_Stat       0x20
#define sk_Chs        0x10
#define sk_RParen     0x15
#define sk_Tan        0x16
#define sk_Vars       0x17
#define sk_Power      0x0E

/**
 * Things you shouldn't use unless you know what you are doing
 */
void os_ForceCmdNoChar(void);

/**
 * Sets the calculator into 6MHz mode and 48MHz modes. Note that the ones
 * suffix with I perserve the interrupt vectors
 */
void boot_Set6MHzMode(void);
void boot_Set48MHzMode(void);
void boot_Set6MHzModeI(void);
void boot_Set48MHzModeI(void);

/**
 * Use this function to call assembly functions in the OS and Bootcode
 * i.e. _OS( asm_HomeUp );
 */
void _OS(void *function);

/**
 * Assembly functions ( Don't forget to call from _OS() )
 */
void asm_MoveUp(void);
void asm_MoveDown(void);
void asm_HomeUp(void);
void asm_RunIndicOn(void);
void asm_RunIndicOff(void);
void asm_DisableAPD(void);
void asm_EnableAPD(void);

/**
 * ---- TI-OS Token definitions ----
 */
#define tToDMS		0x01
#define tToDEC		0x02
#define tToAbc		0x03
#define tStore		0x04	// ->
#define tBoxPlot	0x05
#define tLBrack		0x06	// '['
#define tRBrack		0x07	// ']'
#define tLBrace		0x08	// '{'
#define tRBrace		0x09	// '}'
#define tFromRad	0x0A
#define tFromDeg	0x0B
#define tRecip		0x0C
#define tSqr		0x0D
#define tTrnspos	0x0E
#define tCube		0x0F	// '^3'
#define tLParen		0x10	// '('
#define tRParen		0x11	// ')'
#define tRound		0x12	// 'round'
#define tPxTst		0x13	// 'PXL-TEST'
#define tAug		0x14	// 'aug'
#define tRowSwap	0x15	// 'rSwap'
#define tRowPlu		0x16	// 'rAdd'
#define tmRow		0x17	// 'multR'
#define tmRowPlus	0x18	// 'mRAdd'
#define tMax		0x19	// 'max'
#define tMin		0x1A	// 'min'
#define tRToPr		0x1B	// 'R>Pr'
#define tRToPo		0x1C	// 'R>Po'
#define tPToRx		0x1D	// 'P>Rx'
#define tPToRy		0x1E	// 'P>Ry'
#define tMedian		0x1F	// 'MEDIAN'
#define tRandM		0x20	// 'randM'
#define tMean		0x21	// 'MEAN'
#define tRoot		0x22	// 'ROOT'
#define tSeries		0x23	// 'seq'
#define tFnInt		0x24	// 'fnInt'
#define tNDeriv		0x25	// 'fnIr'
#define tEvalF		0x26
#define tFmin		0x27
#define tFmax		0x28
#define tSpace		0x29	// ' '
#define tString		0x2A	// '"'
#define tComma		0x2B	// ','
#define tii		0x2C	// 'i'
#define tFact		0x2D	// '!'
#define tCubicR		0x2E
#define tQuartR		0x2F
#define t0		0x30
#define t1		0x31
#define t2		0x32
#define t3		0x33
#define t4		0x34
#define t5		0x35
#define t6		0x36
#define t7		0x37
#define t8		0x38
#define t9		0x39
#define tDecPt		0x3A	// '.'
#define tee		0x3B	// 'e'
#define tOr		0x3C	// '_or_'
#define tXor		0x3D
#define tColon		0x3E	// ':'
#define tEnter		0x3F
#define tAnd		0x40	// '_and_'
#define tA		0x41
#define tB		0x42
#define tC		0x43
#define tD		0x44
#define tE		0x45
#define tF		0x46
#define tG		0x47
#define tH		0x48
#define tI		0x49
#define tJ		0x4A
#define tK		0x4B
#define tL		0x4C
#define tM		0x4D
#define tN		0x4E
#define tO		0x4F
#define tP		0x50
#define tQ		0x51
#define tR		0x52
#define tS		0x53
#define tT		0x54
#define tU		0x55
#define tV		0x56
#define tW		0x57
#define tX		0x58
#define tY		0x59
#define tZ		0x5A
#define tTheta		0x5B

/**
 * Extended Tokens
 */
#define tExtTok		0xEF
#define tSetDate	0x00
#define tSetTime	0x01
#define tCheckTmr	0x02
#define tSetDtFmt	0x03
#define tSetTmFmt	0x04
#define tTimeCnv	0x05
#define tDayOfWk	0x06
#define tGetDtStr	0x07
#define tGetTmStr	0x08
#define tGetDate	0x09
#define tGetTime	0x0A
#define tStartTmr	0x0B
#define tGtDtFmt	0x0C
#define tGetTmFmt	0x0D
#define tIsClockOn	0x0E
#define tClockOff	0x0F
#define tClockOn	0x10
#define tOpenLib	0x11
#define tExecLib	0x12
#define tInvT		0x13
#define tChiSquaredTest	0x14
#define tLinRegTInt	0x15
#define tManualFit	0x16
#define tZQuadrant	0x17
#define tZFracHalf	0x18
#define tZFracThird	0x19
#define tZFracFourth	0x1A
#define tZFracFifth	0x1B
#define tZFracEighth	0x1C
#define tZFracTenth	0x1D
#define tFracSlash	0x2E
#define tFracMixedNum	0x2F
#define tSwapImProper	0x30
#define tSwapFracDec	0x31
#define tRemainder	0x32
#define tSummationSigma	0x33
#define tLogBase	0x34
#define tRandIntNoRep	0x35
#define tMathPrint	0x36
#define tClassic	0x38
#define tAutoAnswer	0x3B
#define tDecAnswer	0x3C
#define tFracAnswer	0x3D
#define tBlue		0x41
#define tRed		0x42
#define tBlack		0x43
#define tMagenta	0x44
#define tGreen		0x45
#define tOrange		0x46
#define tBrown		0x47
#define tNavy		0x48
#define tLtBlue		0x49
#define tYellow		0x4A
#define tWhite		0x4B
#define tLtGray		0x4C
#define tMedGray	0x4D
#define tGray		0x4E
#define tDarkGray	0x4F
#define tGraphColor	0x65
#define tTextColor	0x67
#define tBackgroundOn	0x5B
#define tBackgroundOff	0x64
#define tThin		0x74
#define tBorderColor	0x6C
#define tAsm84CPrgm	0x68
#define tAsm84CCmp	0x69
#define tAsm84CeCmp	0x7B
#define tAsm84CePrgm	0x7A

#define tVarMat		0x5C
#define tVarLst		0x5D
#define tVarEqu		0x5E
#define tProg		0x5F
#define tVarPict	0x60
#define tVarGDB		0x61
#define tVarOut		0x62
#define tVarSys		0x63

/**
 * Mode settings tokens
 */
#define tRad		0x64	// 'Radian'
#define tDeg		0x65	// 'Degree'
#define tNormF		0x66	// 'Normal'
#define tSci		0x67	// 'Sci'
#define tEng		0x68	// 'Eng'
#define tFloat		0x69	// 'Float'
#define tFix		0x73	// 'Fix_'
#define tSplitOn	0x74
#define tFullScreen	0x75
#define tStndrd		0x76	// 'Func'
#define tParam		0x77	// 'Param'
#define tPolar		0x78	// 'Pol'
#define tSeqG		0x79	// ;79h
#define tAFillOn	0x7A	// 'AUTO FILL ON'
#define tAFillOff	0x7B	// 'AutoFill OFF'
#define tACalcOn	0x7C
#define tACalcOff	0x7D

#define tEQ		0x6A	// '=='
#define tLT		0x6B	// '<'
#define tGT		0x6C	// '>'
#define tLE		0x6D	// LLE
#define tGE		0x6E	// LGE
#define tNE		0x6F	// LNE
#define tAdd		0x70	// '+'
#define tSub		0x71	// '-'
#define tMul		0x82	// '*'
#define tDiv		0x83	// '/'
#define tAns		0x72

#define tBoxIcon	0x7F
#define tCrossIcon	0x80
#define tDotIcon	0x81

#define tTrace		0x84	// 'Trace'
#define tClDrw		0x85	// 'ClDraw'
#define tZoomStd	0x86	// 'ZStd'
#define tZoomtrg	0x87	// 'Ztrg'
#define tZoomBox	0x88	// 'ZBOX'
#define tZoomIn		0x89	// 'ZIn'
#define tZoomOut	0x8A	// 'ZOut'
#define tZoomSqr	0x8B	// 'ZSqr'
#define tZoomInt	0x8C	// 'ZInt'
#define tZoomPrev	0x8D	// 'ZPrev'
#define tZoomDec	0x8E	// 'ZDecm'
#define tZoomStat	0x8F	// 'ZStat
#define tUsrZm		0x90	// 'ZRcl'
#define tPrtScrn	0x91	// 'PrtScrn'
#define tZoomSto	0x92	//  'ZSto'
#define tText		0x93

#define tnPr		0x94	// '_nPr_'
#define tnCr		0x95	// '_nCr_'

// Graph Commands
#define tYOn		0x96	// 'FnOn_'
#define tYOff		0x97	// 'FnOff_'
#define tStPic		0x98	// 'StPic_'
#define tRcPic		0x99	// 'RcPic_'
#define tStoDB		0x9A	// 'StGDB_'
#define tRclDB		0x9B	// 'RcGDB_'
#define tLine		0x9C	// 'Line'
#define tVert		0x9D	// 'Vert_'
#define tPtOn		0x9E	// 'PtOn'
#define tPtOff		0x9F	// 'PtOff'
#define tPtChg		0xA0	// 'PtChg'
#define tPXOn		0xA1
#define tPXOff		0xA2
#define tPXChg		0xA3
#define tShade		0xA4	// 'Shade'
#define tCircle		0xA5	// 'Circle'
#define tHorz		0xA6	// 'HORIZONTAL'
#define tTanLn		0xA7	// 'TanLn'
#define tDrInv		0xA8	// 'DrInv_'
#define tDrawF		0xA9	// 'DrawF_'
#define tVarStrng	0xAA

// Functions with No Argument
#define tRand		0xAB	// 'rand'
#define tPi		0xAC	//  Lpi
#define tGetKey		0xAD	// 'getKy'
#define tAPost		0xAE	// '''
#define tQuest		0xAF	// '?'
#define tChs		0xB0
#define tInt		0xB1
#define tAbs		0xB2
#define tDet		0xB3
#define tIdent		0xB4
#define tDim		0xB5
#define tSum		0xB6
#define tProd		0xB7
#define tNot		0xB8
#define tIPart		0xB9
#define tFPart		0xBA

// New 2 Byte Tokens
#define t2ByteTok	0xBB
#define tSqrt		0xBC
#define tCubRt		0xBD
#define tLn		0xBE
#define tExp		0xBF
#define tLog		0xC0
#define tALog		0xC1
#define tSin		0xC2
#define tASin		0xC3
#define tCos		0xC4
#define tACos		0xC5
#define tTan		0xC6
#define tATan		0xC7
#define tSinH		0xC8
#define tASinH		0xC9
#define tCoshH		0xCA
#define tACosH		0xCB
#define tTanH		0xCC
#define tATanH		0xCD

// Some Programming Commands
#define tIf		0xCE	// 'If_'
#define tThen		0xCF	// 'Then_'
#define tElse		0xD0	// 'Else_'
#define tWhile		0xD1	// 'While_'
#define tRepeat		0xD2	// 'Repeat_'
#define tFor		0xD3	// 'For_'
#define tEnd		0xD4	// 'End'
#define tReturn		0xD5	// 'Return'
#define tLbl		0xD6	// 'Lbl_'
#define tGoto		0xD7	// 'Goto_'
#define tPause		0xD8	// 'Pause_'
#define tStop		0xD9	// 'Stop'
#define tISG		0xDA	// 'IS>'
#define tDSL		0xDB	// 'DS<'
#define tInput		0xDC	// 'Input_'
#define tPrompt		0xDD	// 'Prompt_'
#define tDisp		0xDE	// 'Disp_'
#define tDispG		0xDF	// 'DispG'
#define tOutput		0xE0	// 'Outpt'
#define tClLCD		0xE1	// 'ClLCD'
#define tConst		0xE2	// 'Fill'
#define tSortA		0xE3	// 'sortA_'
#define tSortD		0xE4	// 'sortD_'
#define tDispTab	0xE5	// 'Disp Table
#define tMenu		0xE6	// 'Menu'
#define tSendMBL	0xE7	// 'Send'
#define tGetMBL		0xE8	// 'Get'

// Stat Plot Commands
#define tPlotOn		0xE9	// 'PLOTSON'
#define tPlotOff	0xEA	// 'PLOTSOFF
#define tListName	0xEB	// List Designator
#define tPlot1		0xEC
#define tPlot2		0xED
#define tPlot3		0xEE
#define tUnused01	0xEF	// available?
#define tPower		0xF0	// '^'
#define tXRoot		0xF1	// LsupX,Lroot
#define tOneVar		0xF2	// 'OneVar_'
#define tTwoVar		0xF3
#define tLR		0xF4	// 'LinR(A+BX)'
#define tLRExp		0xF5	// 'ExpR_'
#define tLRLn		0xF6	// 'LnR_'
#define tLRPwr		0xF7	// 'PwrR_'
#define tMedMed		0xF8
#define tQuad		0xF9
#define tClrLst		0xFA	// 'Clear List'
#define tClrTbl		0xFB	// 'Clear Table'
#define tHist		0xFC	// 'Hist_'
#define txyLine		0xFD	// 'xyline_'
#define tScatter	0xFE	// 'Scatter_'
#define tLR1		0xFF	// 'LINR(AX+B)'

// 2nd Half Of Graph Format Tokens
#define tSeq		0x00	// 'SeqG'
#define tSimulG		0x01	// 'SimulG'
#define tPolarG		0x02	// 'PolarGC'
#define tRectG		0x03	// 'RectGC'
#define tCoordOn	0x04	// 'CoordOn'
#define tCoordOff	0x05	// 'CoordOff'
#define tDrawLine	0x06	// 'DrawLine'
#define tDrawDot	0x07	// 'DrawDot'
#define tAxisOn		0x08	// 'AxesOn'
#define tAxisOff	0x09	// 'AxesOff'
#define tGridOn		0x0A	// 'GridOn'
#define tGridOff	0x0B	// 'GridOff'
#define tLblOn		0x0C	// 'LabelOn'
#define tLblOff		0x0D	// 'LabelOff'
#define tWebOn		0x0E	// 'WebOn'
#define tWebOff		0x0F	// 'WebOFF'
#define tuv		0x10	// U vs V
#define tvw		0x11	// V vs W
#define tuw		0x12	// U vs W

// 2nd Half Of User Matrix Tokens
#define tMatA		0x00	// MAT A
#define tMatB		0x01	// MAT B
#define tMatC		0x02	// MAT C
#define tMatD		0x03	// MAT D
#define tMatE		0x04	// MAT E
#define tMatF		0x05	// MAT F
#define tMatG		0x06	// MAT G
#define tMatH		0x07	// MAT H
#define tMatI		0x08	// MAT I
#define tMatJ		0x09	// MAT J

// 2nd Half Of User List Tokens
#define tL1		0x00	// LIST 1
#define tL2		0x01	// LIST 2
#define tL3		0x02	// LIST 3
#define tL4		0x03	// LIST 4
#define tL5		0x04	// LIST 5
#define tL6		0x05	// LIST 6

// 2nd Half Of User Equation Tokens
// Y Equations have bit 4 set
#define tY1		0x10	// Y1
#define tY2		0x11	// Y2
#define tY3		0x12	// Y3
#define tY4		0x13	// Y4
#define tY5		0x14	// Y5
#define tY6		0x15	// Y6
#define tY7		0x16	// Y7
#define tY8		0x17	// Y8
#define tY9		0x18	// Y9
#define tY0		0x19	// Y0

// Param Equations Have Bit 5 Set
#define tX1T		0x20	// X1t
#define tY1T		0x21	// Y1t
#define tX2T		0x22	// X2t
#define tY2T		0x23	// Y2t
#define tX3T		0x24	// X3t
#define tY3T		0x25	// Y3t
#define tX4T		0x26	// X4t
#define tY4T		0x27	// Y4t
#define tX5T		0x28	// X5t
#define tY5T		0x29	// Y5t
#define tX6T		0x2A	// X6t
#define tY6T		0x2B	// Y6t

// Polar Equations Have Bit 6 Set
#define tR1		0x40	// R1
#define tR2		0x41	// R2
#define tR3		0x42	// R3
#define tR4		0x43	// R4
#define tR5		0x44	// R5
#define tR6		0x45	// R6

// Recursion Equations Have Bit 7 Set
#define tun		0x80	// Un
#define tvn		0x81	// Vn
#define twn		0x82	// Wn

// 2nd Half User Picture Tokens
#define tPic1		0x00	// PIC1
#define tPic2		0x01	// PIC2
#define tPic3		0x02	// PIC3
#define tPic4		0x03	// PIC4
#define tPic5		0x04	// PIC5
#define tPic6		0x05	// PIC6
#define tPic7		0x06	// PIC7
#define tPic8		0x07	// PIC8
#define tPic9		0x08	// PIC9
#define tPic0		0x09	// PIC0

// 2nd Half User Graph Database Tokens
#define tGDB1		0x00	// GDB1
#define tGDB2		0x01	// GDB2
#define tGDB3		0x02	// GDB3
#define tGDB4		0x03	// GDB4
#define tGDB5		0x04	// GDB5
#define tGDB6		0x05	// GDB6
#define tGDB7		0x06	// GDB7
#define tGDB8		0x07	// GDB8
#define tGDB9		0x08	// GDB9
#define tGDB0		0x09	// GDB0

// 2nd Half Of String Vars
#define tStr1		0x00
#define tStr2		0x01
#define tStr3		0x02
#define tStr4		0x03
#define tStr5		0x04
#define tStr6		0x05
#define tStr7		0x06
#define tStr8		0x07
#define tStr9		0x08
#define tStr0		0x09

// 2nd Half Of System Output Only Variables
#define tRegEq		0x01	// REGRESSION EQUATION
#define tStatN		0x02	// STATISTICS N
#define tXMean		0x03	// X MEAN
#define tSumX		0x04	// SUM(X)
#define tSumXSqr	0x05	// SUM(X^2)
#define tStdX		0x06	// STANDARD DEV X
#define tStdPX		0x07	// STANDARD DEV POP X
#define tMinX		0x08	// Min X VALUE
#define tMaxX		0x09	// Max X VALUE
#define tMinY		0x0A	// Min Y VALUE
#define tMaxY		0x0B	// Max Y VALUE
#define tYmean		0x0C	// Y MEAN
#define tSumY		0x0D	// SUM(Y)
#define tSumYSqr	0x0E	// SUM(Y^2)
#define tStdY		0x0F	// STANDARD DEV Y
#define tStdPY		0x10	// STANDARD DEV POP Y
#define tSumXY		0x11	// SUM(XY)
#define tCorr		0x12	// CORRELATION
#define tMedX		0x13	// MED(X)
#define tQ1		0x14	// 1ST QUADRANT OF X
#define tQ3		0x15	// 3RD QUADRANT OF X
#define tQuadA		0x16	// 1ST TERM OF QUAD POLY REG/ Y-INT
#define tQuadB		0x17	// 2ND TERM OF QUAD POLY REG/ SLOPE
#define tQuadC		0x18	// 3RD TERM OF QUAD POLY REG
#define tCubeD		0x19	// 4TH TERM OF CUBIC POLY REG
#define tQuartE		0x1A	// 5TH TERM OF QUART POLY REG
#define tMedX1		0x1B	// x1 FOR MED-MED
#define tMedX2		0x1C	// x2 FOR MED-MED
#define tMedX3		0x1D	// x3 FOR MED-MED
#define tMedY1		0x1E	// y1 FOR MED-MED
#define tMedY2		0x1F	// y2 FOR MED-MED
#define tMedY3		0x20	// y3 FOR MED-MED
#define tRecurn		0x21	// RECURSION N
#define tStatP		0x22
#define tStatZ		0x23
#define tStatT		0x24
#define tStatChi	0x25
#define tStatF		0x26
#define tStatDF		0x27
#define tStatPhat	0x28
#define tStatPhat1	0x29
#define tStatPhat2	0x2A
#define tStatMeanX1	0x2B
#define tStatStdX1	0x2C
#define tStatN1		0x2D
#define tStatMeanX2	0x2E
#define tStatStdX2	0x2F
#define tStatN2		0x30
#define tStatStdXP	0x31
#define tStatLower	0x32
#define tStatUpper	0x33
#define tStat_s		0x34
#define tLRSqr		0x35	// r^2
#define tBRSqr		0x36	// R^2

// These next tokens are only used to access the data
// They are display only and the user cannot access them at all
#define tF_DF		0x37	// ANOFAV FACTOR DF
#define tF_SS		0x38	// ANOFAV FACTOR SS
#define tF_MS		0x39	// ANOFAV FACTOR MS
#define tE_DF		0x3A	// ANOFAV ERROR DF
#define tE_SS		0x3B	// ANOFAV ERROR SS
#define tE_MS		0x3C	// ANOFAV ERROR MS

// 2nd Half Of System Input/Output Variables
#define tuXscl		0x00
#define tuYscl		0x01
#define tXscl		0x02
#define tYscl		0x03
#define tRecuru0	0x04	// U 1st Initial condition
#define tRecurv0	0x05	// V 1st Initial condition
#define tun1		0x06	// U(N-1); not used
#define tvn1		0x07	// V(N-1); not used
#define tuRecuru0	0x08
#define tuRecurv0	0x09
#define tXmin		0x0A
#define tXmax		0x0B
#define tYmin		0x0C
#define tYmax		0x0D
#define tTmin		0x0E
#define tTmax		0x0F
#define tThetaMin	0x10
#define tThetaMax	0x11
#define tuXmin		0x12
#define tuXmax		0x13
#define tuYmin		0x14
#define tuYmax		0x15
#define tuThetMin	0x16
#define tuThetMax	0x17
#define tuTmin		0x18
#define tuTmax		0x19
#define tTblMin		0x1A
#define tPlotStart	0x1B
#define tuPlotStart	0x1C
#define tnMax		0x1D
#define tunMax		0x1E
#define tnMin		0x1F
#define tunMin		0x20
#define tTblStep	0x21
#define tTStep		0x22
#define tThetaStep	0x23
#define tuTStep		0x24
#define tuThetStep	0x25
#define tDeltaX		0x26
#define tDeltaY		0x27
#define tXFact		0x28
#define tYFact		0x29
#define tTblInput	0x2A
#define tFinN		0x2B
#define tFinI		0x2C
#define tFinPV		0x2D
#define tFinPMT		0x2E
#define tFinFV		0x2F
#define tFinPY		0x30
#define tFinCY		0x31
#define tRecurw0	0x32	// w0(1)
#define tuRecurw0	0x33
#define tPlotStep	0x34
#define tuPlotStep	0x35
#define tXres		0x36
#define tuXres		0x37
#define tRecuru02	0x38	// u0(2)
#define tuRecuru02	0x39
#define tRecurv02	0x3C	// v0(2)
#define tuRecurv02	0x3D
#define tRecurw02	0x3E	// w0(2)
#define tuRecurw02	0x3F

// 2nd Byte Of t2ByteTok Tokens
#define tFinNPV		0x00
#define tFinIRR		0x01
#define tFinBAL		0x02
#define tFinPRN		0x03
#define tFinINT		0x04
#define tFinToNom	0x05
#define tFinToEff	0x06
#define tFinDBD		0x07
#define tLCM		0x08
#define tGCD		0x09
#define tRandInt	0x0A
#define tRandBin	0x0B
#define tSubStrng	0x0C
#define tStdDev		0x0D
#define tVariance	0x0E
#define tInStrng	0x0F
#define tDNormal	0x10
#define tInvNorm	0x11
#define tDT		0x12
#define tChI		0x13
#define tDF		0x14
#define tBINPDF		0x15
#define tBINCDF		0x16
#define tPOIPDF		0x17
#define tPOICDF		0x18
#define tGEOPDF		0x19
#define tGEOCDF		0x1A
#define tNormalPDF	0x1B
#define tTPDF		0x1C
#define tChiPDF		0x1D
#define tFPDF		0x1E
#define tRandNorm	0x1F
#define tFinFPMT	0x20
#define tFinFI		0x21
#define tFinFPV		0x22
#define tFinFN		0x23
#define tFinFFV		0x24
#define tConj		0x25
#define tReal		0x26
#define tImag		0x27
#define tAngle		0x28
#define tCumSum		0x29
#define tExpr		0x2A
#define tLength		0x2B
#define tDeltaLst	0x2C
#define tRef		0x2D
#define tRRef		0x2E
#define tToRect		0x2F
#define tToPolar	0x30
#define tConste		0x31
#define tSinReg		0x32
#define tLogistic	0x33
#define tLinRegTTest	0x34
#define tShadeNorm	0x35
#define tShadeT		0x36
#define tShadeChi	0x37
#define tShadeF		0x38
#define tMatToLst	0x39
#define tLstToMat	0x3A
#define tZTest		0x3B
#define tTTest		0x3C
#define t2SampZTest	0x3D
#define t1PropZTest	0x3E
#define t2PropZTest	0x3F
#define tChiTest	0x40
#define tZIntVal	0x41
#define t2SampZInt	0x42
#define t1PropZInt	0x43
#define t2PropZInt	0x44
#define tGraphStyle	0x45
#define t2SampTTest	0x46
#define t2SampFTest	0x47
#define tTIntVal	0x48
#define t2SampTInt	0x49
#define tSetupLst	0x4A
#define tFinPMTend	0x4B
#define tFinPMTbeg	0x4C
#define tRealM		0x4D
#define tPolarM		0x4E
#define tRectM		0x4F
#define tExprOn		0x50
#define tExprOff	0x51
#define tClrAllLst	0x52
#define tGetCalc	0x53
#define tDelVar		0x54
#define tEquToStrng	0x55
#define tStrngToequ 	0x56
#define tDelLast	0x57
#define tSelect		0x58
#define tANOVA		0x59
#define tModBox		0x5A
#define tNormProb	0x5B
#define tMGT		0x64	// VERTICAL SPLIT
#define tZFit		0x65	// ZOOM FIT
#define tDiag_on	0x66	// DIANOSTIC DISPLAY ON
#define tDiag_off	0x67	// DIANOSTIC DISPLAY OFF
#define tArchive	0x68	// Archive
#define tUnarchive	0x69	// UnArchive
#define tAsm		0x6A
#define tAsmComp	0x6B	// asm compile
#define tAsmPrgm	0x6C	// Signifies a program is asm
#define tAsmCmp		0x6D	// asm program is compiled
#define tLcapAAcute	0x6E
#define tLcapAGrave	0x6F
#define tLcapACaret	0x70
#define tLcapADier	0x71
#define tLaAcute	0x72
#define tLaGrave	0x73
#define tLaCaret	0x74
#define tLaDier		0x75
#define tLcapEAcute	0x76
#define tLcapEGrave	0x77
#define tLcapECaret	0x78
#define tLcapEDier	0x79
#define tLeAcute	0x7A
#define tLeGrave	0x7B
#define tLeCaret	0x7C
#define tLeDier		0x7D
#define tLcapIGrave	0x7F
#define tLcapICaret	0x80
#define tLcapIDier	0x81
#define tLiAcute	0x82
#define tLiGrave	0x83
#define tLiCaret	0x84
#define tLiDier		0x85
#define tLcapOAcute	0x86
#define tLcapOGrave	0x87
#define tLcapOCaret	0x88
#define tLcapODier	0x89
#define tLoAcute	0x8A
#define tLoGrave	0x8B
#define tLoCaret	0x8C
#define tLoDier		0x8D
#define tLcapUAcute	0x8E
#define tLcapUGrave	0x8F
#define tLcapUCaret	0x90
#define tLcapUDier	0x91
#define tLuAcute	0x92
#define tLuGrave	0x93
#define tLuCaret	0x94
#define tLuDier		0x95
#define tLcapCCed	0x96
#define tLcCed		0x97
#define tLcapNTilde	0x98
#define tLnTilde	0x99
#define tLaccent	0x9A
#define tLgrave		0x9B
#define tLdieresis	0x9C
#define tLquesDown	0x9D
#define tLexclamDown	0x9E
#define tLalpha		0x9F
#define tLbeta		0xA0
#define tLgamma		0xA1
#define tLcapDelta	0xA2
#define tLdelta		0xA3
#define tLepsilon	0xA4
#define tLlambda	0xA5
#define tLmu		0xA6
#define tLpi		0xA7
#define tLrho		0xA8
#define tLcapSigma	0xA9
#define tLphi		0xAB
#define tLcapOmega	0xAC
#define tLphat		0xAD
#define tLchi		0xAE
#define tLstatF		0xAF
#define tLa		0xB0
#define tLb		0xB1
#define tLc		0xB2
#define tLd		0xB3
#define tLsmalle	0xB4
#define tLf		0xB5
#define tLsmallg	0xB6
#define tLh		0xB7
#define tLi		0xB8
#define tLj		0xB9
#define tLk		0xBA
#define tLl		0xBC
#define tLm		0xBD
#define tLsmalln	0xBE
#define tLo		0xBF
#define tLp		0xC0
#define tLq		0xC1
#define tLsmallr	0xC2
#define tLs		0xC3
#define tLsmallt	0xC4
#define tLu		0xC5
#define tLv		0xC6
#define tLw		0xC7
#define tLx		0xC8
#define tLy		0xC9
#define tLz		0xCA
#define tLsigma		0xCB
#define tLtau		0xCC
#define tLcapIAcute	0xCD
#define tGarbageCollect	0xCE

// 2 byte extended tokens (tExtTok) present in OS 5.2 and above
#define tSEQn		0x8F	// 'SEQ(n)'
#define tSEQn1		0x90	// 'SEQ(n+1)'
#define tSEQn2		0x91	// 'SEQ(n+2)'
#define tLEFT		0x92	// 'LEFT'
#define tCENTER		0x93	// 'CENTER'
#define tRIGHT		0x94	// 'RIGHT'
#define tInvBinom	0x95	// 'invBinom('
#define tWait		0x96	// 'Wait_'
#define tToString	0x97	// 'toString('
#define tEval		0x98	// 'eval('

#endif
