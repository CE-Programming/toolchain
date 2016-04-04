; (c) Copyright 2001-2008 Zilog Inc.
;-------------------------------------------------------------------------
; CASE branch resolution.
;
; Input:
;	Operand1: 
;		  bc : 24 bit address of CASE TABLE
;
;	Operand2: 
;		  de : 24 bit number of entries in table
;
;	Operand3: 
;		  hl : 24 bit value to match in table
; 
; Output:
;	Result:   hl : 24 bit address of case jp to take
; Registers Used:
; 
; 
; Table Format:
;	[24-bit value][JP label (4-bytes)] 7 bytes total
; 
; 
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__case

__case:
	push	af
	push	iy

	ld		iy,bc	; iy = table address
	ld		bc,hl	; bc = match value
;
;	Loop trough table entries looking for a match
;
_loop:
	ld		hl,(iy)	; Get case value from table
	or		a,a		; Clear carry
	sbc		hl,bc	; Match?
	jr		z,match

;	lea		iy,iy + 7
	lea		iy,iy + 6 ;new case table item length
	dec		de
	push		de
	ex		de,hl
	ld		de,0
	or		a,a		; clear carry
	sbc		hl,de		; Done?
	pop		de
	jr		nz,_loop

	; No match, iy points to default
;	LD		hl,iy	; return pointer to default case JP
	LD		hl,(iy)	; single jump to the case
	jr		done

match:				; iy+3 points to destination
;	lea		hl,iy+3	; return pointer to JP
	ld		hl,(iy+3)	; single jump to the case

done:
	pop		iy
	pop		af
	ret
	
