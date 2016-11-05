	.def	_isdigit
	.assume adl=1

;int isdigit(int c) {
;	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(DIG));
;}

_isdigit	equ 0220BCh
