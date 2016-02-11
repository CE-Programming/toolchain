// Parts from Matt "MateoConLechuga" Waltz and
// contributors of http://wikiti.brandonw.net/index.php?title=84PCE:OS:Include_File
// Latest as of Oct. 18, 2015

#ifndef TICE_H
#define TICE_H

#include <stdbool.h>
#include <stdint.h>

#pragma asm "include "./asm/tice.asm""
#pragma asm "include "./asm/cstartup.asm""
#pragma asm "xref __saveIY"

/* === Function Prototypes ==================== */
uint8_t GetBootVerMajor(void);  // Returns Major Boot Version
uint8_t GetHardwareVers(void);  // Retuns Hardware Version
uint8_t GetBootVerMinor(void);  // Returns Minor Boot Version
void ClearVRAM(void);           // Sets all bytes of VRAM to 0FFh
bool GetOnInterrupt(void);      // Retuns onInterrupt
void RunIndicOn(void);          // Turns on Run Indicator
void RunIndicOff(void);         // Turns of Run Indicator
void DisableAPD(void);          // Disables APD
void EnableAPD(void);           // Enables APD
uint8_t GetKey(void);           // Returns values of _GetKey
int GetCSC(void);               // Returns values of _GetCSC
int GetDrawFGColor(void);       // 565 color
void SetDrawFGColor(int color); // 565 color
void SetDrawBGColor(int color); // 565 color
/* ============================================ */

/* === ROM Funtion Wrapper ==================== */
#define _OS(FUNC) \
    do { \
      asm("	LD	(__saveIY),IY"); \
      asm("	LD	IY, 13631616"); \
      FUNC ; \
      asm("	LD	IY,(__saveIY)"); \
    } while (0)
/* ============================================ */

#endif

	















