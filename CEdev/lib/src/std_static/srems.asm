; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Modulus Signed
; Input:
;	Operand1: 
;		  hl : 16 bits
; 
;	Operand2: 
;		  bc :	 16 bits
;
; Output:
;	Result:   hl : 16 bits
;
; Registers Used:
;	
;-------------------------------------------------------------------------
	.assume adl=1
	.ref	__irems
	.def	__srems

__srems:
	push	af
	push	bc
	push	hl
	sla	h
	sbc	a,a
	ld	hl,2
	add	hl,sp
	ld	(hl),a
	inc	hl
	inc	hl
	inc	hl
	sla	b
	sbc	a,a
	ld	(hl),a
	pop	hl
	pop	bc
	pop	af
	jp	__irems

