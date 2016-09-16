; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Integer Modulus
; Input:
;	Operand1: 
;		  uHL : 24 bits (dividend x)
; 
;	Operand2: 
;		  uBC :	 24 bits (divisor y)
;
; Output:
;	Result:   uHL : 24 bits (remainder)
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __iremu
	.assume adl=1

__iremu		equ 000170h

