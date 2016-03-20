; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short NOT.
; Input:
;	Operand1: 
;		  hl : 16 bit
;
; Output:
;	Result:   hl : 16 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	 
	.def	__snot
__snot:
	push	af
	;; 
	;; low 8 bits
	;; 
	ld	a,l
	cpl
	ld	l,a
	;; 
	;; high 8 bits
	;; 
	ld	a,h
	cpl
	ld	h,a

	pop	af
	ret	

 
