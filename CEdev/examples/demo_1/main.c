/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ti84pce.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other available headers */
// stdarg.h, setjmp.h, ctype.h, float.h, iso646.h, limits.h, errno.h, assert.h, debug.h

/* definitions */
#define darkred    (0xC0C0)
#define lightgreen (0x6F6F)
#define vram       ((uint16_t*)0xD40000)
#define lcdsize    (320*240*2)

/* Put your function prototypes here */
void fillscrn(uint16_t color);
void cleanUp(void);

/* Put all your code here */
void main(void) {
    
    fillscrn(darkred);
    
    /* Don't use GetKey in your programs */
    _OS( GetKey() );
    
    fillscrn(purple);
    
    /* Don't use GetKey in your programs */
    _OS( GetKey() );
    
    cleanUp();
}

/* Other functions */
void fillscrn(uint16_t color) {
    memset(vram, color, lcdsize);
}

void cleanUp(void) {
    /* Clear/invalidate some RAM areas */
    /* Restore the home screen nicely */
    _OS( asm("CALL _DelRes");
         asm("CALL _ClrTxtShd");
         asm("CALL _ClrScrn");
         asm("CALL _HomeUp");
         asm("CALL _DrawStatusBar");
    );
    asm("SET  graphDraw,(iy+graphFlags)");
}