; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;	Result:   hl : 24 bit address of case jp to take
; Registers Used:
;
; Data at Return Address:
;	JP   (HL)                   0
;	DW   numCases               1
;	DW24 startValue             3
;	DW24 Lab1                   6
;	DW24 Lab2                   9
;	...
;	DW24 defaultLab             6+3*numCases
; 
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__seqcaseD

__seqcaseD:
	ex		(sp),iy		;store iy and take table address into iy
	push		iy		;store return address
	push		af
	push		bc
	push		de
	
	lea		iy,iy+6		; Address of First Label
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
	pop		iy		;return address
	ex		(sp),iy		;exchange return address with the actual value of IY at entry
	ret