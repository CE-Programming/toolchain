#pragma asm "segment code"
#pragma asm "xref _exit"
#pragma asm "xdef _abort"

void abort(void) {
	asm("XOR	A,A");
	asm("LD	(0FFFF00h),A");
	asm("JP	_exit");
}