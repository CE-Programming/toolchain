; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Short to Integer Conversion
; Input:
;	Operand1: 
;                 BC : 16 bit number to convert
;                      
; Output:
;       Result:   HL : 24 bit 
; Registers Used:
;	a
;-------------------------------------------------------------------------
        .def __stoiu
	.assume adl=1

__stoiu		equ 000264h
