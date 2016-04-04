; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Shift Right Signed
; Input:
;	Operand1: 
;                 AuBC : 32 bit value to be shifted by L
; 
;	Operand2: 
;                 L   : number of bits to shift
;
; Output:
;	Result:   AuBC : 32 bit 
; Registers Used:
;	flags
;-------------------------------------------------------------------------
	.def	__lshrs
	.assume adl=1

__lshrs:
    push    hl

	push	af		; save A

	dec		sp
	push	bc
	inc		sp
	pop		af		; a = uBC
	ld	h,b
	ld	b,l
	ld	l,c			; HL = BC
	ld	c,	a		; c = uBC

	pop	af			; restore A

	inc	b			; b = count
	jr	test

loop:
        sra	a
        rr	c
        rr	h
        rr	l

test:
        djnz    loop

	push	hl
	ld		hl,	2
	add		hl,	sp
	ld		(hl), c
	pop		bc

    pop     hl
	ret

