; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Shift Right Signed
; Input:
;	Operand1: 
;		  BC : 24 bit number of bits to shift
;			Assume B=0 C=shift count
;	Operand2: 
;		  HL : 24 bit value to be shifted by C
;
; Output:
;	Result:   HL : 24 bit 
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def	__ishrs, __ishrs_b
	.assume adl=1

__ishrs_b:
	push bc
	ld c,a
	call __ishrs
	pop bc
	ret
	
__ishrs:
	push	af
	push	bc

	dec	sp
	push	hl
	inc	sp
	pop	af

	ld	b,c
	inc	b
	jr	test

loop:
	sra	a
	rr	h
	rr	l
test:
	djnz	loop

	push	hl
	ld	hl,2
	add	hl,sp
	ld	(hl),a
	pop	hl

	pop	bc
	pop	af
	ret


