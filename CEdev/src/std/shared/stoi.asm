; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Short to Integer Conversion
; Input:
;	Operand1: 
;                 BC : 16 bit number to convert
;                      
; Output:
;       Result:   HL : 24 bit 
; Registers Used:
;	a
;-------------------------------------------------------------------------
        .def __stoi
	.assume adl=1

__stoi		equ 000260h
