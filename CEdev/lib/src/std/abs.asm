	.def	_abs
	.assume adl=1
	
_abs:
	pop	hl
	pop	de
	push	de
	push	hl
	or	a,a
	sbc	hl,hl
	sbc	hl,de
	ret	p
	ex	de,hl
	ret
