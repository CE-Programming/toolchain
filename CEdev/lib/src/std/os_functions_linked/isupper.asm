	.def	_isupper
	.assume adl=1

; original source
; int isupper(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(UC));
; }

_isupper	equ 0220D0h
