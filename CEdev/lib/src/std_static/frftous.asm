; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract unsigned short conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   HL : 16 bits
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frftous

__frftous:
	push	af
	ld	a,e
	add	hl,hl
	rla
	dec	sp
	push	hl
	inc	sp
	pop	hl
	cp	a,6Fh	;underflow
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
	neg
	ld	b,a
_L5:
	rr	h
	rr	l
	or	a,a
	djnz	_L5
_L6:
	pop	bc
	pop	af
	ret
