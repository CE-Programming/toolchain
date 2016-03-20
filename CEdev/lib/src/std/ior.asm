; (c) Copyright  2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer OR.
; Input:
;	Operand1: 
;		  HL : 24 bit
;
;	Operand2: 
;		  BC : 24 bit
;
; Output:
;	Result:   HL : 24 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__ior

__ior          equ 000168h
