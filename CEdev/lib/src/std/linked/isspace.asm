	.def	_isspace
	.ref	___maptab
	.assume adl=1

; original source
; int isspace(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(WS));
; }

_isspace	equ 0220ACh
