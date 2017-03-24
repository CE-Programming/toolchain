	.ref __frameset0
	.ref _strtod
	.def _atof
	.assume adl=1

; double atof(char *str);

_atof:
	pop	hl
	pop	bc
	push	bc
	push	hl
	or	a,a
	sbc	hl,hl
	push	hl
	push	bc
	call	_strtod
	pop	bc
	pop	hl
	ret
