; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short AND.
; Input:
;	Operand1: 
;		  hl : 16 bit
;
;	Operand2: 
;		  bc : 16 bit
;
; Output:
;	Result:   hl : 16 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.def __sand
	.assume adl=1
	
__sand		equ 000200h
