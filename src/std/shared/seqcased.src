; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;	Result:   hl : 24 bit address of case jp to take
; Registers Used:
;
; Data at Return Address:
;	JP   (HL)                   0
;	DW   numCases               1
;	DW24 startValue             3
;	DW24 Lab1                   6
;	DW24 Lab2                   9
;	...
;	DW24 defaultLab             6+3*numCases
; 
;-------------------------------------------------------------------------
	.def __seqcaseD
	.assume adl=1

__seqcaseD	equ 000214h
