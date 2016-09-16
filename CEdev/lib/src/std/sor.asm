; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short OR.
; Input:
;	Operand1: 
;		  hl : 16 bit
;
;	Operand2: 
;		  bc : 16 bit
;
; Output:
;	Result:   hl : 16 bit
;                 hl OR bc
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.def __sor
	.assume adl=1

__sor		equ 000234h	
