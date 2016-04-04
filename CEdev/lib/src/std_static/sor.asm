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
	.assume adl=1
	.def	__sor

__sor:
	push	af	
	
	ld	a,l
	or	a,c
	ld	l,a

	ld	a,h
	or	a,b
	ld	h,a

	pop	af
	ret	
