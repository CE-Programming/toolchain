	.assume	adl=1

	.section	.rodata._free_string
	.local	_free_string
_free_string:
	.asciz	"called free"

	.section	.text._free
	.global	_free
	.type	_free, @function
_free:
	ld	hl, _free_string
	push	hl
	call	_puts
	pop	hl
.L.wait_loop:
	call	_os_GetCSC
	or	a, a
	jr	z, .L.wait_loop
	ret

	.extern	_puts
	.extern	_os_GetCSC
