; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Modulus Signed.
; Input:
;	Operand1: 
;		  EHL : 32 bits (dividend)
;
;	Operand2: 
;		  ABC : 32 bits (divisor)
;
; Output:
;	Result:   EHL : 32 bit
; Registers Used:
;	de,af
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lrems
	.ref	__lremu, __lneg
__lrems:
	push	af
	push	bc
	push	de

	bit	7,a
	jr	z,_L1
	push	hl
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
	call	__lremu
	pop	bc
	bit	7,c
	jr	z,_L3
	call	__lneg
_L3:
	pop	bc
	pop	af
	ret

