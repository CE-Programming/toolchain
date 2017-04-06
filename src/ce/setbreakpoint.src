;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_SetBreakpoint
	.assume	adl=1

;--------------------------------------------------------------------
_SetBreakpoint:
; Sets a breakpoint at a particular address
; Arguments
;  DE = Address to set as breakpoint
	pop	hl
	pop	de
	push	de
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),3
	ret
