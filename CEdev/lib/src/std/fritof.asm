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

__fritof       equ 0002B8h

