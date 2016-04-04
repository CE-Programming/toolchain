; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Division Signed
; Input:
;	Operand1: 
;		  eHL : 32 bits
; 
;	Operand2: 
;		  aBC :	 32 bits
; Output:
;	Result:   eHL : 24 bits
;
; Registers Used:
;	
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__ldivs
	.ref	__ldivu, __lneg
__ldivs:
	push	bc
	push	af
	push	de
	bit	7,a
	jr	z,_L1
	push	hl
	or	a,a		; CR 7885
	sbc	hl,hl
	sbc	hl,bc
	adc	a,0
	neg
	push	hl
	pop	bc
	pop	hl
_L1:
	bit	7,e
	jr	z,_L2
	call	__lneg
_L2:
	call	__ldivu
	pop	bc
	pop	af
	ld	b,a
	xor	a,c
	jp	p,_L3
	call	__lneg
_L3:
	ld	a,b
	pop	bc
	ret

