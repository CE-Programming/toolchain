	.def	_isxdigit
	.assume adl=1

; original source
; int isxdigit(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(DIG|HEX));
; }

_isxdigit	equ 0220D4h
