	.def	_isgraph
	.assume adl=1
	
; original source
; int isgraph(int c) {
; 	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(UC|LC|DIG|PUN));
; }

_isgraph	equ 0220C0h
