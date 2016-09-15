; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Multiplication Signed/Unsigned.
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1: 
;		  EuHL : 32 bits
;
;	Operand2: 
;		  AuBC : 32 bits
;
; Output:
;	Result:   EuHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lmulu,__lmuls

__lmuls        equ 0001C8h
__lmulu        equ 0001CCh

