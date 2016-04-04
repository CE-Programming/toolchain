; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract short to float conversion.
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
	.def	__frstof
	.ref	__fritof
__frstof:
	push	hl
	dec	sp
	pop	hl
	inc sp
	ld	l,0h
	jp	__fritof

