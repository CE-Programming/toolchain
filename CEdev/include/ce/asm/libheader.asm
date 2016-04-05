; Include the launcher in the program

 ifndef USING_SHARED_LIBRARIES
 define USING_SHARED_LIBRARIES
 
 .assume ADL=1
 
 define	.launcher,space=ram
 define	.libs,space=ram

 segment .launcher
 ld hl,__libloadappvar
 call %020320		; _mov9toop1
 ld a,%15		; saves a whole 3 bytes
 ld (%D005F8),a		; op1
 
__findlibload:
 call %02050C		; _chkfindsym
 jp c,__notfound
 call %021F98		; _chkinram
 jp nz,__inarc		; if in ram, archive LibLoad and search again
 call %020628		; _pushop1
 call %021448		; _arc_unarc
 call %0205C4		; _popop1
 jr __findlibload
__inarc:
 ex de,hl
 ld de,9
 add hl,de
 ld e,(hl)
 add hl,de
 inc hl
 inc hl
 inc hl
 ld de,__relocationstart
 jp (hl)		; jump to the loader -- it should take care of everything
__notfound:
 call %020814           ; _clrscrn
 call %020828		; _homeup
 ld hl,__missingappvar
 call %0207C0		; _puts
 call %0207F0		; _newline
 ld hl,__linkaddress
 call %0207C0		; _puts
 call %020D8C		; _getkey
 jp %020814
__relocationstart:	; libraries to be relocated will be placed here for the relocator
 segment .libs
 ;...
 ;...
 ;...
 segment data
__missingappvar:
 db "Need"
__libloadappvar:
 db " LibLoad",0
__linkaddress:
 db "http://tiny.cc/celibs",0
 
 endif