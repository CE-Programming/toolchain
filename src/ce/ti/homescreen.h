/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS homescreen functions
 * 
 * If you want to print to the homescreen instead of using GraphX, this is the file.
 */

#ifndef _TI_HOMESCREEN_H
#define _TI_HOMESCREEN_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <ti/ui.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

/*
 * Bootcode functions
 */

/**
 * Inserts a new line at the current cursor posistion on the homescreen
 * Does not scroll.
 */
void boot_NewLine(void);

/*
 * OS Routines
 */

/**
 * Resets the OS homescreen; accounts for split screen.
 */
#define os_ClrHome() \
do { \
    os_ClrLCD(); \
    os_HomeUp(); \
    os_DrawStatusBar(); \
} while (0)

/**
 * Resets the OS homescreen fully; ignores split screen mode.
 */
#define os_ClrHomeFull() \
do { \
    os_ClrLCDFull(); \
    os_HomeUp(); \
    os_DrawStatusBar(); \
} while (0)

/**
 * Inserts a new line at the current cursor posistion on the homescreen.
 * Does scroll.
 */
tiflags void os_NewLine(void);

/**
 * Disables the OS cursor
 */
void os_DisableCursor(void);

/**
 * Enables the OS cursor
 */
void os_EnableCursor(void);

/**
 * Set the cursor posistion used on the homescreen
 *
 * @param curRow The row aligned offset
 * @param curCol The column aligned offset
 */
void os_SetCursorPos(uint8_t curRow, uint8_t curCol);

/**
 * Gets the cursor posistion used on the homescreen
 *
 * @param curRow Pointer to store the row aligned offset
 * @param curCol Pointer to store the column aligned offset
 */
void os_GetCursorPos(unsigned int *curRow, unsigned int *curCol);

/**
 * Puts some text at the current homescreen cursor location
 *
 * @param string Text to put on homescreen
 * @returns 1 if string fits on screen, 0 otherwise
 */
uint24_t os_PutStrFull(const char *string);

/**
 * Puts some text at the current homescreen cursor location
 *
 * @param string Text to put on homescreen
 * @returns 1 if string fits on line, 0 otherwise
 */
uint24_t os_PutStrLine(const char *string);

/**
 * Routine to scroll homescreen up
 */
tiflags void os_MoveUp(void);

/**
 * Routine to scroll homescreen down
 */
tiflags void os_MoveDown(void);

/**
 * Routine to move row and column posistion to (0,0)
 */
tiflags void os_HomeUp(void);

/**
 * Routine to clear the homescreen lcd
 */
tiflags void os_ClrLCDFull(void);

/**
 * Routine to clear the homescreen lcd.
 * Accounts for split screen
 */
tiflags void os_ClrLCD(void);

/**
 * Invalidate and clear text shadow area
 */
tiflags void os_ClrTxtShd(void);

/**
 * Disable text buffering on the homescreen. C programs use this area by default for the BSS / Heap.
 */
void os_DisableHomeTextBuffer(void);

/**
 * Enables text buffering on the homescreen. C programs use this area by default for the BSS / Heap.
 */
void os_EnableHomeTextBuffer(void);

/**
 * Custom implementation input routine for use in conjunction with the TIOS.
 * It is HIGHLY recommended you implement your own routine, this routine has
 * some quirks. It is good enough for getting basic input however.
 *
 * @param string Input prompt string to be displayed to the user
 * @param buf Storage location to store input string
 * @param bufsize Available storage size for input string. -1 for null termination.
 * @returns None
 */
void os_GetStringInput(char *string, char *buf, size_t bufsize);

#define os_TextFlags         (*(uint8_t*)0xD00080)

#define os_TextShadow        ((uint8_t*)0xD006C0)   /**< Text buffer, 260 bytes. */
#define os_PromptRow         (*(uint8_t*)0xD00800)
#define os_PromptCol         (*(uint8_t*)0xD00801)
#define os_PromptIns         (*(uint8_t*)0xD00802)
#define os_PromptShift       (*(uint8_t*)0xD00803)
#define os_PromptRet         (*(uint8_t*)0xD00804)
#define os_PromptValid       (*(uint8_t*)0xD00807)

#define os_CurRow            (*(uint8_t*)0xD00595)
#define os_CurCol            (*(uint8_t*)0xD00596)

#define os_CmdShadow         ((uint8_t*)0xD0232D)

#define os_TextFGColor       (*(uint16_t*)0xD02688)        /**< Large font foreground color */
#define os_TextBGColor       (*(uint16_t*)0xD0268A)        /**< Large font background color */

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
