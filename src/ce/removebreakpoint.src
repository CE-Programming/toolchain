;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_RemoveBreakpoint
	.assume	adl=1

;--------------------------------------------------------------------
_RemoveBreakpoint:
; Removes a breakpoint at a particular address
; Arguments
;  DE = Address to remove
	pop	hl
	pop	de
	push	de
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),4
	ret
