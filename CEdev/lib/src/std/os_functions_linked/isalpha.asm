	.def	_isalpha
	.assume adl=1
	
; original source
; int isalnum(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(UC|LC));

_isalpha	equ 0220B4h
