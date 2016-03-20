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

__fruitof      equ 0002BCh

