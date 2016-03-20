; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer AND.
; Input:
;	Operand1: 
;		  hl : 24 bit
;
;	Operand2: 
;		  bc : 24 bit
;
; Output:
;	Result:   hl : 24 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__iand
	
__iand         equ 000134h
