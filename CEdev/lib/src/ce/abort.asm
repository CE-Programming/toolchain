; (c) Copyright 2016 Matt Waltz
;-------------------------------------------------------------------------
; void abort(void) function
; For use in CEmu
;-------------------------------------------------------------------------
	.def	_abort
	.ref	_exit
	.assume adl=1

_abort:
	ld	a,1
	ld	(0FFFFFFh),a
	jp	_exit