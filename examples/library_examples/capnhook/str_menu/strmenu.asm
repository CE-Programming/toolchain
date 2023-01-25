include '../../include/ez80.inc'
include '../../include/tiformat.inc'
include '../../include/ti84pceg.inc'
include '../../include/include_library.inc'

include '../../src/capnhook.inc'

format ti executable 'STRMENU'

; LibLoad launcher: https://github.com/CE-Programming/libload/blob/master/setup/setup.md
__libloadlauncher:
	ld	hl,__libloadappvar
	call	_Mov9ToOP1
	ld	a,21
	ld	(OP1),a
__findlibload:
	call	_ChkFindSym
	jp	c,__notfound
	call	_ChkInRam
	jp	nz,__inarc
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	__findlibload
__inarc:
	ex	de,hl
	ld	de,9
	add 	hl,de
	ld	e,(hl)
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	de,__relocationstart
	jp	(hl)
__notfound:
	call	_ClrScrn
	call	_HomeUp
	ld	hl,__missingappvar
	call	_PutS
	call	_NewLine
	jp	_GetKey
__relocationstart:
	include_library '../../src/capnhook.lib'

	ld	bc,description
	push	bc
	ld	bc,75 ; Priority - hooks with a lower value are called first
	push	bc
	ld	bc,HOOK_TYPE_MENU
	push	bc
	ld	bc,menu_hook.size ; Hook size
	push	bc
	ld	bc,menu_hook
	push	bc
	ld	bc,$000300 ; Globally unique ID - see https://github.com/commandblockguy/capnhook/wiki/Hook-ID-Registry
	push	bc
	call	hook_Install
	pop	bc,bc,bc,bc,bc,bc

	call	hook_Sync ; Apply changes and activate hooks

	ld	iy,flags ; Preserve flags so that the OS doesn't get crashy

	ret

menu_hook:
	; Menu hook - https://wikiti.brandonw.net/index.php?title=83Plus:Hooks:9BC0
	db	$83 ; Magic byte used to determine whether the hook is still valid

.start: ; ix is set to this address when the hook is called
	or	a,a ; when a = 0: return menu table in hl
	jr	nz,.ignore ; don't care about other events

	ld	a,(menuCurrent) ; Check if the currently open menu is vars
	cp	a,mVars
	jr	nz,.ignore

	; ix contains the address of the first byte of the hook after the magic byte
	; Return the address of .menu_data in hl
	lea	hl,ix+(.menu_data - menu_hook.start)
	or	a,a ; Reset the zero flag

	; Indicate to capnhook to return a value to the OS
	res	0,(iy-flag_continue)
	ret

.ignore:
	; Indicate to capnhook to move on to the next hook rather than returning a value to the OS
	; Always do this unless you want to return a value.
	set	0,(iy-flag_continue)
	ret
.menu_data:
	; This was copied from the default value for the vars menu, except for the new "STRING" column
	db	$04 ; Number of headers
	db	$07,$04,$0f,$03 ; Number of choices for each header
	; String table entry for each header (see https://wikiti.brandonw.net/index.php?title=83Plus:Hooks:9BCC#Condition_7)
	db	$5a,$5d,$6e,$52
	; List of two-byte keycodes for each header
	; There don't appear to be equates for most of these keycodes?
	; "VARS":
	db	$82,$3f
	db	$82,$40
	db	$82,$41
	db	$82,$42
	db	$82,$44
	db	$82,$45
	db	$82,$43
	; "Y-VARS":
	db	$82,$46
	db	$82,$47
	db	$82,$48
	db	$82,$49
	; "COLORS":
	db	$fb,$db
	db	$fb,$dc
	db	$fb,$dd
	db	$fb,$de
	db	$fb,$df
	db	$fb,$e0
	db	$fb,$e1
	db	$fb,$e2
	db	$fb,$e3
	db	$fb,$e4
	db	$fb,$e5
	db	$fb,$e6
	db	$fb,$e7
	db	$fb,$e8
	db	$fb,$e9
	; "STRING":
	db	kExtendEcho2,kInStrng
	db	kExtendEcho2,kLength
	db	kExtendEcho2,kSubStrng
.size = $ - menu_hook

description: ; A human-readable description of the hook
	db	"vars menu string ops",0

; Strings for the LibLoad launcher
__missingappvar:
	db	"Need"
__libloadappvar:
	db	" LibLoad",0
