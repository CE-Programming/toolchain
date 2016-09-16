	.ref __frameset0
	.def _isnan
	.assume adl=1
	
; int isnan(double n);

_isnan:	
	call	__frameset0
	ld	hl,(ix+6)
	adc	hl,hl
	jr	z,l_1
	ld	hl,(ix+8)
	add	hl,hl
l_1:	inc	h
	ld	hl,0
	jr	nz,l_2
	inc	hl
l_2:	ld	sp,ix
	pop	ix
	ret
