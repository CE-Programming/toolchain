; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Modulus Unsigned
; Input:
;	Operand1: 
;		  hl : 16 bits
; 
;	Operand2: 
;		  bc : 16 bits
;
; Output:
;	Result:   hl : 16 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__sremu
	.ref	__iremu
__sremu:
	push	bc
	push	hl
	ld	hl,2
	add	hl,sp
	ld	(hl),0
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),0
	pop	hl
	pop	bc
	jp	__iremu

