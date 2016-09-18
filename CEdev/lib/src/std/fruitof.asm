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
	.def __fruitof
	.assume adl=1

__fruitof	equ 0002BCh
