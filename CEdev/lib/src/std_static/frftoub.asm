; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract unsigned char conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   A : 8 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frftoub

__frftoub:
	push	hl
	ld	a,e
	add	hl,hl
	rla
	cp	a,77h	;underflow
	jr	c,_L0
	cp	a,96h	;overflow
	jr	c,_L1
_L0:
	xor	a,a
	pop	hl
	ret
_L1:
	sub	a,7fh
	jr	nz,_L2
_L7:
	push	hl
	ld	hl,1
	add	hl,sp
	rl	(hl)
	inc	hl
	ld	a,(hl)
	adc	a,0h
	inc	hl
	ld	sp,hl
	pop	hl
	ret
_L2:
	push	bc
	jr	c,_L4
	ld	b,a
_L3:
	add	hl,hl
	djnz	_L3
	pop	bc
	jr	_L7
_L4:
	ld	hl,5
	add	hl,sp
	neg
	ld	b,a
	ld	a,(hl)
	or	a,a
	rla
	scf
	jr	_L6
_L5:
	or	a,a
_L6:
	rra
	djnz	_L5
	adc	a,0h
	pop	bc
	pop	hl
	ret
