; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Division Signed
; Input:
;	Operand1: 
;		  hl : 16 bits x
; 
;	Operand2: 
;		  bc :	 16 bits y
;
; Output:
;	Result:   hl : 16 bits
;
; Registers Used:
;	
;-------------------------------------------------------------------------
	.def __sdivs
	.assume adl=1
	
__sdivs		equ 000208h
