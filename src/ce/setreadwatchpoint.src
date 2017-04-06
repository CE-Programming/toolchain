;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_SetReadWatchpoint
	.assume	adl=1

;--------------------------------------------------------------------
_SetReadWatchpoint:
; Sets a watchpoint at a particular address
; Arguments
;  DE = Address to set as watchpoint
;   C = Length of watchpoint
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),5
	ret
