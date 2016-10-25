	.def _atexit
	.ref ___atexit
	.ref ___atexit_registered
	.assume adl=1

;-------------------------------------------------------------------------------
_atexit:
	pop	hl
	pop	de
	push	de
	push	hl
	ld	a,(___atexit_registered)
	cp	a,32                     ; check if at maximum
	jr	nz,_add
	scf
	sbc	hl,hl
	ret
_add:	ld	l,a
	ld	h,3
	mlt	hl
	ld	bc,___atexit
	add	hl,bc
	ld	(hl),de
	inc	a
	ld	(___atexit_registered),a
	or	a,a
	sbc	hl,hl
	ret
