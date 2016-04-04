; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract unsigned integer conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   HL : 24 bits
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frftoui

__frftoui:
	push	af
	ld	a,e
	add	hl,hl
	rla
	cp	a,67h	;underflow
	jr	c,_L0
	cp	a,96h	;overflow
	jr	c,_L2
_L0:
	or	a,a
	sbc	hl,hl
_L1:
	pop	af
	ret
_L2:
	sub	a,7fh
	jr	z,_L1
	push	bc
	jr	c,_L4
	ld	b,a
_L3:
	add	hl,hl
	djnz	_L3
	jr	_L6
_L4:
	push	hl
	ld	hl,2
	add	hl,sp
	neg
	ld	b,a
	ld	a,(hl)
	pop	hl
_L5:
	rra
	rr	h
	rr	l
	or	a,a
	djnz	_L5
	push	hl
	ld	hl,2
	add	hl,sp
	ld	(hl),a
	pop	hl
_L6:
	pop	bc
	pop	af
	ret


