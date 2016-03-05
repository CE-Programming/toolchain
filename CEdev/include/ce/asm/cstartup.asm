; Parts from Matt "MateoConLechuga" Waltz and
; contributors of http://wikiti.brandonw.net/index.php?title=84PCE:OS:Include_File
; Latest as of 11 February 2016
	ifndef STARTUP_MODULE
	define STARTUP_MODULE
;-------------------------------------------------------------------------------
; Standard CE startup module definitions and references
;-------------------------------------------------------------------------------
	xref	__low_bss
	xref	__len_code
	xref	__low_code
	
	xref	_main
	
	xdef	_errno
	xdef	_init
	xdef	_exit
	xdef	__exit
	xdef	__saveIY
	xdef	__saveSP
	xdef	__c_startup
	xdef	_c_int0
	
	.assume	ADL = 1
 
	define	.header,space=ram
	define	.icon,space=ram
	define	.launcher,space=ram
	define	.libs,space=ram
	define	.startup,space=ram

;-------------------------------------------------------------------------------
; Standard CE startup module code
;-------------------------------------------------------------------------------
	segment .header
	db	%EF
	db	%7B
_init:
	db	%00	; Magic byte recognition for C programs
	
	ifdef	ICON
	xref	__program_description_end
	jp	__program_description_end
	endif
	
	segment .launcher
	segment .libs
	
;-------------------------------------------------------------------------------
	segment .startup
__c_startup:
_c_int0:
	call	%020848		; _RunIndicOff
	ld	hl,__low_bss
	ld	bc,%10DE2	; Maximum size of BSS+Heap
	call	%0210DC		; _MemClear

	di
	ld	(__saveSP),sp
	call	_main
__exit:
_exit:
	ld	sp,(__saveSP)
	ld	iy,%D00080	; Restore IY for OS
	ret
;-------------------------------------------------------------------------------
	segment	data
__saveSP:
	db	0,0,0
__saveIY:
	db	0,0,0
_errno:
	db	0,0,0
;-------------------------------------------------------------------------------
	segment	code
;-------------------------------------------------------------------------------
; End Standard Startup Module
;-------------------------------------------------------------------------------
	endif
