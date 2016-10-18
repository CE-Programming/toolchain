	.def _exit
	.def _atexit
	.ref __exit
	.assume adl=1

;-------------------------------------------------------------------------------
	segment bss
___atexit:
	ds	96
	segment data
___atexit_registered:
	db	0
_already_in_atexit:
	db	0
;-------------------------------------------------------------------------------

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

;-------------------------------------------------------------------------------
_exit:
	pop	de
	pop	hl
	push	hl
	push	de
	ld	de,_already_in_atexit
	ld	a,(de)
	or	a,a
	ret	nz             ; check to see if some idiot called exit()
	inc	a
	ld	(de),a
	push	hl

_lexit:	ld	hl,___atexit_registered
	ld	a,(hl)
	or	a,a
	jr	z,_end
	dec	a
	ld	(hl),a
	ld	l,a
	ld	h,3
	mlt	hl
	ld	bc,___atexit
	add	hl,bc
	ld	iy,(hl)
	call	00015Ch               ; __indcall
	jr	_lexit

_end:	pop	hl
	ret
