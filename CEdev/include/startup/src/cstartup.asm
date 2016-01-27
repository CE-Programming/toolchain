; Parts from Matt "MateoConLechuga" Waltz and
; contributors of http://wikiti.brandonw.net/index.php?title=84PCE:OS:Include_File
; Latest as of Oct. 18, 2015

.include "tice.asm"

;=============================================================================
; Standard CE startup module
;=============================================================================
 xref __low_bss
 xdef __saveIY
 xref _main
 
 .assume ADL = 1
 
 define .header,space=ram
 define .icon,space=ram
 define .launcher,space=ram
 define .libs,space=ram
 define .startup,space=ram

 segment .header
 db %EF
 db %7B
 db %00			; Magic byte recognition for C programs - who starts their program with a nop?
_crt0:
 segment .startup
 di			; disable interrupts
 call _RunIndicOff	; turn off run indicator
 ld hl, __low_bss
 ld bc, %10DE2 		; Maximum size of BSS+Heap
 call _MemClear

 ld (__saveSP),sp
 call _main		;Save SP and call main
__exit:
 ld sp,(__saveSP)
 ld iy,%D00080		; Restore IY for OS
 ret
 
 segment data
__saveSP:
 db 0,0,0
__saveIY:
 db 0,0,0
 segment bss
_errno:
 ds 3
 
 segment code
;=============================================================================
; End Standard Startup Module
;=============================================================================