	.ref __next
	.def _srand
	.assume adl=1

; void srand(unsigned int seed);
	
_srand:
	pop	de
	pop	hl
	push	hl
	push	de
	xor	a,a
	ld	(__next),hl
	ld	(__next+3),a
	ret
