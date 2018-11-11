debugAbort:
	call	debugNewLine
	call	debugStr
	db	'Abort called at ',0
	ld	b,6
	or	a,a
	sbc	hl,hl
	add	hl,sp
	jr	.enter
.loop:
	inc	hl
	inc	hl
	inc	hl
	call	debugStr
	db	'<-',0
.enter:
	ld	de,(hl)
	call	debugHexUDE
	djnz	.loop
	call	_os_GetKey
	call	usbCleanup
	jr	$

debugHexBlockBC:
	ex	(sp),hl
	push	de
	push	bc
	push	af
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
.loop:
	call	debugHex_DE_
	inc	de
	dec	bc
	ld	a,c
	or	a,b
	jr	nz,.loop
	pop	af
	pop	bc
	pop	de
	ex	(sp),hl
	ret
debugHexBlockHL:
	ex	de,hl
	ex	(sp),hl
	push	de
	push	bc
	ld	b,(hl)
	inc	hl
.loop:
	call	debugHex_DE_
	inc	de
	djnz	.loop
	pop	bc
	pop	de
	ex	(sp),hl
	ex	de,hl
	ret
debugHexBlock:
	ex	(sp),hl
	push	de
	push	bc
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	b,(hl)
	inc	hl
.loop:
	call	debugHex_DE_
	inc	de
	djnz	.loop
	pop	bc
	pop	de
	ex	(sp),hl
	ret
debugHexBCU:
	push	af
	dec	sp
	push	bc
	jr	debugUpper
debugHexDEU:
	push	af
	dec	sp
	push	de
	jr	debugUpper
debugHexHLU:
	push	af
	dec	sp
	push	hl
debugUpper:
	inc	sp
	pop	af
	jr	debugHexA.enter
debugHexB:
	push	af
	ld	a,b
	jr	debugHexA.enter
debugHexD:
	push	af
	ld	a,d
	jr	debugHexA.enter
debugHexH:
	push	af
	ld	a,h
	jr	debugHexA.enter
debugHexUBC:
	call	debugHexBCU
debugHexBC:
	call	debugHexB
debugHexC:
	push	af
	ld	a,c
	jr	debugHexA.enter
debugHexUDE:
	call	debugHexDEU
debugHexDE:
	call	debugHexD
debugHexE:
	push	af
	ld	a,e
	jr	debugHexA.enter
debugHexUHL:
	call	debugHexHLU
debugHexHL:
	call	debugHexH
debugHexL:
	push	af
	ld	a,l
	jr	debugHexA.enter
debugHex_BC_:
	push	af
	ld	a,(bc)
	jr	debugHexA.enter
debugHex_DE_:
	push	af
	ld	a,(de)
	jr	debugHexA.enter
debugHex_HL_:
	push	af
	ld	a,(hl)
	jr	debugHexA.enter
debugHexA:
	push	af
.enter:
	push	iy
	ld	iy,flags
	push	af
	rrca
	rrca
	rrca
	rrca
	call	.nibble
	pop	af
	call	.nibble
	pop	iy
	pop	af
	ret
.nibble:
	or	a,$F0
	daa
	add	a,$A0
	adc	a,$40
	jp	_PutC

debugDecHL:
	push	af
	push	de
	push	hl
	push	iy
	ld	iy,flags
	call	_DispHL_s
	pop	iy
	pop	hl
	pop	de
	pop	af
	ret
debugDecUHL:
	push	af
	push	de
	push	hl
	push	iy
	ld	iy,flags
	call	_DispHL
	pop	iy
	pop	hl
	pop	de
	pop	af
	ret

debugCharA:
	push	de
	push	bc
	push	af
	push	hl
	push	iy
	ld	iy,flags
	call	_PutC
	pop	iy
	pop	hl
	pop	af
	pop	bc
	pop	de
	ret

debugChar:
	ex	(sp), hl
	push	af
	push	iy
	ld	iy,flags
	ld	a,(hl)
	inc	hl
	call	_PutC
	pop	iy
	pop	af
	ex	(sp), hl
	ret

debugStr:
	ex	(sp),hl
	push	bc
	push	af
	push	de
	push	iy
	ld	iy,flags
	push	ix
	call	_PutS
	pop	ix
	pop	iy
	pop	de
	pop	af
	pop	bc
	ex	(sp),hl
	ret

debugNewLine:
	push	hl
	push	af
	push	de
	push	bc
	push	iy
	push	ix
	ld	iy,flags
	call	_NewLine
	pop	ix
	pop	iy
	pop	bc
	pop	de
	pop	af
	pop	hl
	ret
