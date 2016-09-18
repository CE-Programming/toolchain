; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Byte Shift Right Signed
; Input:
;	Operand1: 
;                 A : 8 bit number to shift
;	Operand2: 
;                 B : 8 bit shift count
;
; Output:
;       Result:   A : 8 bit 
; Registers Used:
;       flags
;-------------------------------------------------------------------------
        .def __bshrs
	.assume adl=1

__bshrs:
        ld	a,b
        inc	b
        jr      test

loop:
        sra     a
test:
       	djnz	loop

	ld	b,a
	ret
