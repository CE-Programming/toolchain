	.ref __frameset0
	.def _isinf
	.assume adl=1
	
; int isinf(double n);

_isinf:
	call	__frameset0
	ld	hl,(ix+6)
	adc	hl,hl
	jr	nz,l_1
	ld	hl,(ix+8)
	add	hl,hl
	inc	h
l_1:	ld	hl,0
	jr	nz,l_2
	inc	hl
l_2:	ld	sp,ix
	pop	ix
	ret
