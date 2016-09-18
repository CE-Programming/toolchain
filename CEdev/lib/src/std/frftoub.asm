; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract unsigned char conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   A : 8 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __frftoub
	.assume adl=1

__frftoub	equ 0002A4h
