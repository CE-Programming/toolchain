; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract unsigned char to float conversion.
;
; Input:
;	Operand1: 
;		  A : 8 bits
;
; Output:
;	Result:   eHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frubtof

__frubtof:
	or	a,a
	jr	nz,_L0
	sbc	hl,hl
	ld	e,a
	ret
_L0:
	ld	l,a
	ld	e,7fh
_L1:
	dec	e
	add	a,a
	jr	nc,_L1
	sra	e
	rra
	push	af
	dec	sp
	ld	a,l
	pop	hl
	inc	sp
	sbc.s	hl,hl
	ret

