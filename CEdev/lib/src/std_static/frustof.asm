; (c) Copyright 2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract unsigned short to float conversion.
;
; Input:
;	Operand1: 
;		  HL : 16 bits
;
; Output:
;	Result:   eHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frustof
	.ref	__fruitof
__frustof:
	push	hl
	dec	sp
	pop	hl
	inc sp
	ld	l,0h
	jp	__fruitof

