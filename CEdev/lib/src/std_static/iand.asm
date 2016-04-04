; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer AND.
; Input:
;	Operand1: 
;		  hl : 24 bit
;
;	Operand2: 
;		  bc : 24 bit
;
; Output:
;	Result:   hl : 24 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__iand
__iand:
	push	af
	push	bc
	push	hl
	ld	hl,2
	add	hl,sp
	
	ld a,(hl)
	inc hl
	inc hl
	inc hl
	and a,(hl)
	dec hl
	dec	hl
	dec	hl
	ld (hl),a

	pop	hl
	pop	bc

	ld	a,h
	and	a,b
	ld	h,a

	ld	a,l
	and	a,c
	ld	l,a

	pop	af
	ret	
