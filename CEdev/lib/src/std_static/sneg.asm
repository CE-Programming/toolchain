; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short NEG.
; Input:
;	Operand1: 
;		  hl : 16 bit
;
; Output:
;	Result:   hl : 16 bit
; Registers Used:
;	None
;-------------------------------------------------------------------------
	.assume adl=1
	 
	.def	__sneg
__sneg:
	push	ix
	ld	ix,0
	add	ix,sp
	push	af
	push	hl
	ld	a,(ix-5)
	bit	7,a
	jr	z,_hlpos
	ld	a,FFH
	jr	_callit
_hlpos:
	ld	a,0
_callit:	
	ld	(ix-4),a
	pop	hl
	push	de
	ld	de,0
	ex	de,hl
	or	a,a
	sbc	hl,de
	pop	de
	pop	af
	pop 	ix
	ret	


 
