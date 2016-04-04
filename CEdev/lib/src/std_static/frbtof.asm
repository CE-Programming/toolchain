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
	.def	__frbtof
	.ref	__frubtof

__frbtof:
	or	a,a
	rla
	jr	nc,_L1
	jr	nz,_L0
	rra	
	ld	hl,%800000
	ld	e,%bf
	ret
_L0:
	neg
_L1:
	push	af
	call	__frubtof
	pop	af
	ret nc
	rra
	rl	e
	scf
	rr	e
	ret

