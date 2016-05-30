;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_RemoveWatchpoint
	.assume	adl=1

;--------------------------------------------------------------------
_RemoveWatchpoint:
; Removes a watchpoint at a particular address
; Arguments
;  DE = Address to remove
	pop	hl
	pop	de
	push	de
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),8
	ret
