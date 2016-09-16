; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Integer Division.
; Input:
;	Operand1: 
;		  uHL : 24 bit dividend
;
;	Operand2: 
;		  uBC : 24 bit divisor
;
; Output:
;	Result:   uHL: 24 bit quotient
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __idivu,__idvrmu
	.assume adl=1

__idivu		equ 000140h
__idvrmu	equ 000144h
