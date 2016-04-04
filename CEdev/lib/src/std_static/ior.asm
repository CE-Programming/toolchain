; (c) Copyright  2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer OR.
; Input:
;	Operand1: 
;		  HL : 24 bit
;
;	Operand2: 
;		  BC : 24 bit
;
; Output:
;	Result:   HL : 24 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__ior

__ior:
	push	af
	push	bc
	push	hl
	ld	hl,2
	add	hl,sp
	
	ld a,(hl)
	inc hl
	inc hl
	inc hl
	or a,(hl)
	dec hl
	dec	hl
	dec	hl
	ld (hl),a

	pop	hl
	pop	bc

	ld	a,h
	or	a,b
	ld	h,a

	ld	a,l
	or	a,c
	ld	l,a

	pop	af
	ret	
