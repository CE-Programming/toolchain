	.def	_islower
	.assume adl=1

; original source
; int islower(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(LC));
; }

_islower	equ 0220C4h
