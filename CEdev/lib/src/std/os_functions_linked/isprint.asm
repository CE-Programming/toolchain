	.def	_isprint
	.assume adl=1

; original source
; int isprint(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(UC|LC|DIG|PUN|SP));
; }

_isprint	equ 0220C8h
