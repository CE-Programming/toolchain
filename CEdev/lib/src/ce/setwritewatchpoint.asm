;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_SetWriteWatchpoint
	.assume	adl=1

;--------------------------------------------------------------------
_SetWriteWatchpoint:
; Sets a write watchpoint at a particular address
; Arguments
;  DE = Address to set as watchpoint
;   C = length of watchpoint
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),6
	ret
