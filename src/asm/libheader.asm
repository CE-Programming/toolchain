; Created by Matt "MateoConLechuga" Waltz

 ifndef USING_SHARED_LIBRARIES
 define USING_SHARED_LIBRARIES
 
	.assume	ADL=1
 
	define	.launcher,space=ram
	define	.libs,space=ram
	segment	.launcher

__findlibload:
	ld	hl,__libloadappvar
	call	%020320		; _mov9toop1
	ld	a,%15		; saves a whole 3 bytes
	ld	(%D005F8),a	; op1

	call	%02050C		; _chkfindsym
	jr	c,__notfound
	call	%021F98		; _chkinram
	jr	nz,__inarc	; if in ram, archive LibLoad and search again
	call	%021448		; _arc_unarc
	jr	__findlibload
__inarc:
	ex	de,hl
	ld	de,9
	add	hl,de
	ld	e,(hl)
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	de,__relocationstart
	jp	(hl)		; jump to the loader -- it should take care of everything
__notfound:
	call	%020814		; _clrscrn
	call	%020828		; _homeup
	ld	hl,__missingappvar
	call	%0207C0		; _puts
	call 	%0207F0		; _newline
	ld	hl,__webaddress
	call	%0207C0		; _puts
	jp	%020D8C		; _getkey
__relocationstart:		; libraries to be relocated will be placed here for the relocator
	segment	.libs
	;...
	;...
	;...
	segment	data
__missingappvar:
	db	"Need"
__libloadappvar:
	db	" LibLoad",0
__webaddress:
	db	"http://tiny.cc/clibs",0

 endif