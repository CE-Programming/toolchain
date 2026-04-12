	.assume	adl=1

	.section	.text

	.global	_on_exit_func
	.type	_on_exit_func, @function

; void on_exit_func(int, void*)
_on_exit_func:
	ld	hl, 6
	add	hl, sp
	ld	hl, (hl)
	ld	bc, _fesetexceptflag
	; test that C fesetexceptflag and C++ fesetexceptflag have the same address
	or	a, a
	sbc	hl, bc
	add	hl, bc
	ret	z
	ld	hl, _on_exit_func_error_str
	push	hl
	call	_puts
	pop	hl
.L.wait_loop:
	call	_os_GetCSC
	or	a, a
	jr	z, .L.wait_loop
	ret

	.section	.rodata._on_exit_func_error_str

	.local	_on_exit_func_error_str
_on_exit_func_error_str:
	.asciz	"error:\nstd::fesetexceptflag\naddress mismatch"

	.extern	_fesetexceptflag
	.extern	_puts
	.extern	_os_GetCSC
