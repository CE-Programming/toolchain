; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract integer to float conversion.
;
; Input:
;	Operand1: 
;		  HL : 24 bits
;
; Output:
;	Result:   eHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__fritof
	.ref	__fruitof

__fritof:
	push	de
	ex	de,hl
	ld	hl,800000h
	or	a,a
	sbc	hl,de
	jr	c,_L0
	ex	de,hl
_L0:
	jr	nz,_L1
	pop	de
	ld	e,%bf
	ret
_L1:
	add	hl,hl
	call	__fruitof
	ex	de,hl
	add	hl,hl
	ex	de,hl
	rr	e
	ex	(sp),hl
	ex	de,hl
	ld	e,l
	pop	hl
	ret

