	.ref __frameset0
	.ref __lcmpzero
	.ref __setflag
	.ref __lneg
	.def _labs
	.assume adl=1

; long labs(long j);

_labs:
	call	__frameset0
	ld	hl,(ix+6)
	ld	e,(ix+9)
	push	hl
	push	de
	call	__lcmpzero
	call	__setflag
	pop	de
	pop	hl
	jp	p,l_1
	call	__lneg
l_1:	ld	sp,ix
	pop	ix
	ret
