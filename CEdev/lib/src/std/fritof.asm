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
	.def __fritof
	.assume adl=1

__fritof	equ 0002B8h
