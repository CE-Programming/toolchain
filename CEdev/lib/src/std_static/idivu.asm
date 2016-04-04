; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Integer Division.
; Input:
;	Operand1: 
;		  uHL : 24 bit dividend
;
;	Operand2: 
;		  uBC : 24 bit divisor
;
; Output:
;	Result:   uHL: 24 bit quotient
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__idivu,__idvrmu

__idivu:
	push	af
	push	de
	call	__idvrmu
	ex	de,hl
	pop	de
	pop	af
	ret

; Input:
;	uHL = dividend
;	uBC = divisor
; Output:
;	uDE = quotient
;	uHL = remainder
; Uses:
;	AF, BC
__idvrmu:
	ex de,hl
	ld	a,24		;24 bit counter
	or	a,a
	sbc	hl,hl
loop1:
	ex	de,hl		;shift uHLuDE left
	add	hl,hl
	ex	de,hl
	adc	hl,hl		;carry out not possible
	sbc	hl,bc
	jr	nc,over

	add	hl,bc		;restore dividend
	jr	under
over:
	inc	e		;update quotient
under:
	dec	a
	jr	nz,loop1

	ret

