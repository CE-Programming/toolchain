; (c) Copyright 2001-2008 Zilog Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand1: 
;		  bc : 24 bit address of CASE TABLE
;
;	Operand2: 
;		  de : 24 bit number of entries in table
;
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;	Result:   hl : 24 bit address of case jp to take
; Registers Used:
; 
; 
; Table Format:
;	[24-bit value][JP label (4-bytes)] 7 bytes total
; 
;-------------------------------------------------------------------------
	.def __case
	.assume adl=1

__case		equ 000110h 
