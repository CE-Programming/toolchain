	.def	_iscntrl
	.assume adl=1

;int iscntrl(int c) {
;	if( (unsigned char)c & (unsigned char)0x80 )
;		return (0);
;	return(__maptab[c] & (unsigned char)(CTL));
;}

_iscntrl	equ 0220B8h
