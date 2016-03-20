; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Multiplication Signed/Unsigned.
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1: 
;		  uHL : 24 bits
;
;	Operand2: 
;		  uBC : 24 bits
;
; Output:
;	Result:   uHL : 24 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__imulu,__imuls,__imul_b
	
__imul_b       equ 000150h
__imuls        equ 000154h
__imulu        equ 000158h

