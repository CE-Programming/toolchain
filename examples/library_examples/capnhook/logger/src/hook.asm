include '../../../src/capnhook.inc'

_sprintf = $0000BC

public _hook
_hook:
	db	$83 ; Required for this to be recognized as a hook
	push	iy,ix,hl,de,bc,af
	set	0,(iy-flag_continue) ; Don't return a value to TI-OS
	lea	hl,ix+_type_name_buffer-(_hook+1) ; ix contains the address of the first byte of the hook after $83
	push	hl
	lea	hl,ix+.format_string-(_hook+1)
	push	hl
	ld	hl,$FB0000 ; Address of dbgout for the CEmu console
	push	hl
	call	_sprintf
	pop	hl,hl,hl
	pop	af,bc,de,hl,ix,iy
	ret
.format_string:
	db	"%12s: af:%04x bc:%06x de:%06x hl:%06x ix:%06x iy:%06x",$a,0
public _type_name_buffer
_type_name_buffer:
	rb	16
hook_size = $ - _hook

public _hook_size
_hook_size:
	dl	hook_size
