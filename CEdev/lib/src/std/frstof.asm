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
	
__frstof       equ 0002C0h

