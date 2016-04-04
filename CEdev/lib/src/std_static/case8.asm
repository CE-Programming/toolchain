; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;
; Registers Used:
; 
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__case8

__case8:
	ex		(sp),iy		;store iy and take table address into iy
	push	af
	push	bc
	push	de
	
	lea		iy,iy+2		;table address starts after JP (HL) instruction and 16-bit count
	ld		de,(iy-2)	;count

_loop:
	ld		a,(iy)		;case value (8-bit)
	ld		bc,%0
	ld		c,a
	inc		iy			;case label
	push	hl
	or		a,a
	sbc		hl,bc
	pop		hl
	jr		z, _done
	
	dec.s	de			;decrement count
	ld		b,%0
	ld		c,%0
	ex		de,hl
	or		a,a
	sbc.s	hl,bc
	ex		de,hl
	lea		iy,iy+3
	jr		nz,_loop

_done:	
	ld		hl,(iy)

	pop		de
	pop		bc
	pop		af
	ex		(sp),iy		;restore iy
	ex		(sp),hl		;store jump target as return address on stack
	ret

