; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Division Unsigned
; Input:
;	Operand1: 
;		  hl : 16 bits
; 
;	Operand2: 
;		  bc : 16 bits
;
; Output:
;	Result:   hl : 16 bits
;
; Registers Used:
;	
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__sdivu
	.ref	__idivu
	
__sdivu        equ 00020Ch

