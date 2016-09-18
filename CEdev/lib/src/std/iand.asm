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
	.def __iand
	.assume adl=1
	
__iand		equ 000134h
