; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Division Unsigned
; Input:
;	Operand1: 
;		  EuHL : 32 bits
; 
;	Operand2: 
;		  AuBC : 32 bits
; Output:
;	Result:   EuHL : 32 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__ldivu,__ldvrmu

__ldivu:
	push	ix
	push	iy
	call	__ldvrmu
	ld	a,iyh
	push	ix
	pop	hl
	pop	iy
	pop	ix
	ret

; Input:
;	EuHL = dividend
;	AuBC = divisor
; Output:
;	EuIX = quotient
;	AuHL = remainder
__ldvrmu:
	push	hl
	pop	ix
	ld	iyh,a
	ld	iyl,32
	xor	a,a
	sbc	hl,hl
_loop:
	add	ix,ix		;shift AuHLEuIX left
	rl	e
	adc	hl,hl
	rla
	sbc	hl,bc
	sbc	a,iyh
	jr	nc,_L1
	add	hl,bc
	adc	a,iyh
	jr	_L2
_L1:
	inc	ix
_L2:
	dec	iyl
	jr	nz,_loop
	ret


