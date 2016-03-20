; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Division Unsigned
; Input:
;	Operand1: 
;		  EuHL : 32 bits
; 
;	Operand2: 
;		  AuBC : 32 bits
; Output:
;	Result:   EuHL : 32 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__ldivu,__ldvrmu

__ldivu        equ 0001B8h

; Input:
;	EuHL = dividend
;	AuBC = divisor
; Output:
;	EuIX = quotient
;	AuHL = remainder
__ldvrmu       equ 0001BCh


