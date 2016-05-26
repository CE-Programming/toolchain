;-------------------------------------------------------------------------
; void debugger(void) function
; For use in CEmu, opens the debugger
;-------------------------------------------------------------------------
	.def	_debugger
	.assume adl=1

_debugger:
	ld	a,2
	ld	(0FFFFFFh),a
	ret
