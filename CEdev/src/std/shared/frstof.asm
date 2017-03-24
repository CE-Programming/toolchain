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
	.def __frstof
	.assume adl=1
	
__frstof	equ 0002C0h
