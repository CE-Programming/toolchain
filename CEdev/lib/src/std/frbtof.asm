; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract unsigned char to float conversion.
;
; Input:
;	Operand1: 
;		  A : 8 bits
;
; Output:
;	Result:   eHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __frbtof
	.assume adl=1

__frbtof	equ 00029Ch
