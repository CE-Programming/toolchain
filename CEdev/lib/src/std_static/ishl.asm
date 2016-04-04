; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Shift Left
; Input:
;	Operand1: 
;		  BC : 24 bit number of bits to shift
;			Asuume B=0 C=shift count
;	Operand2: 
;		  HL : 24 bit value to be shifted by C
;
; Output:
;	Result:   HL : 24 bit 
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def	__ishl, __ishl_b
	.assume adl=1

__ishl_b:
	push bc
	ld c,a
	call __ishl
	pop bc
	ret

__ishl:
	push	bc
	ld	b,c
	inc	b
	jr	test
loop:
	add	hl,hl
test:
	djnz	loop
	pop	bc
	ret	

