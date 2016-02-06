#pragma asm "segment code"
#pragma asm "xdef _debugger"

void debugger(void) {
	asm("LD	A,1");
	asm("LD	(0FFFF00h),A");
}