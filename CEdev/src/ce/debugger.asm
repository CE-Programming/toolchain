;-------------------------------------------------------------------------
; void debugger(void) function
; For use in CEmu, opens the debugger
;-------------------------------------------------------------------------
	.def	_Debugger
	.assume adl=1

_Debugger:
	scf
	sbc	hl,hl
	ld	(hl),2
	ret
