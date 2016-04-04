; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;	Returns to case label
; Data at Return Address:
;	DW   numCases               0
;	DW24 startValue             2
;	DW24 Lab1                   5
;	DW24 Lab2                   8
;	...
;	DW24 defaultLab             5+3*numCases
;
; Registers Used:
; 
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__seqcase

__seqcase:
	ex		(sp),iy		;store iy and take table address into iy
	push		af
	push		bc
	push		de
	
	lea		iy,iy+5		; Address of First Label
	ld		de,0		; clear hi byte
	ld		bc,(iy-5)	; count to de
	ld		e,c
	ld		d,b
	ld		bc,(iy-3)	; start case value
	or		a,a		; clear C
	sbc		hl,bc		; index into table
	jp		M,defaultCase	; br if hl less than first case
	push		hl
	or		a,a		;
	sbc		hl,de		; 
	pop		hl
	jp		M,index		; branch if hl < numCases
defaultCase:
	ld		hl,de		; index to default case
index:
	ld		bc,hl		; hl = 3*hl
	add		hl,hl
	add		hl,bc
	ld		bc,hl
	add		iy,bc		; iy points to case label
	ld		hl,(iy)
	pop		de
	pop		bc
	pop		af
	ex		(sp),iy		;restore iy
	ex		(sp),hl		;store jump target as return address on stack
	ret