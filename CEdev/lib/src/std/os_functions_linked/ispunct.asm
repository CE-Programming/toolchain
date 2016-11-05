	.def	_ispunct
	.assume adl=1

; original source
; int ispunct(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(PUN));
; }

_ispunct	equ 0220CCh
