	.def _fabs
	.assume adl=1
	
; double fabs(double j);

_fabs:
	pop	bc
	pop	hl
	pop	de
	push	de
	push	hl
	push	bc
	res	7,e
	ret
