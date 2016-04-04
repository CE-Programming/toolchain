; (c) Copyright 2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract unsigned integer to float conversion.
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
	.def	__fruitof

__fruitof:
	push	de
	ld	de,0h
	or	a,a
	sbc	hl,de
	pop	de
	jr	nz,_L0
	ld	e,0h
	ret
_L0:
	ld	e,7fh
_L1:
	dec	e
	add	hl,hl
	jr	nc,_L1
	push	hl
	ld	hl,2
	add	hl,sp
	sra	e
	rr	(hl)
	pop	hl
	rr	h
	rr	l
	ret

