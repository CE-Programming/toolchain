;=========================================================================
; Copyright (C) 2015-2018 Matt Waltz
; Version 3.0
;
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 3 of the License, or (at your option) any later version.
; See the file COPYING included with this distribution for more
; information.
;=========================================================================
; Performs dynamic relocation for shared libraries and interdependencies
; inputs: de->start of library relocation table
;         hl->start of LibLoad
; output: once relocation of program and library dependencies is complete,
;         jumps to start of program block after relocation block and begins execution
; note:   updated size is added to the copy in ram of the program for libraries
; notes:  all code is location independent; no need to relocate to absolute address.
;         keeping in archive is safe.
;         uses some saferam areas (see below)
;=========================================================================

; includes
include '../include/library.inc'

define VERSION_MAJOR       3
define VERSION_MINOR       0

; global equates
arclibrarylocations        = pixelShadow2   ; place to store locations of archived libraries
dependencyqueuelocation    = cmdPixelShadow ; queue for keeping track of which libraries still need to be resolved

eSP                        = pixelShadow    ; save sp for errors
totallibsize               = pixelShadow+3  ; total size of the library appvar (not used)
extractedsize              = pixelShadow+6  ; holds extracted size of the library
arclocation                = pixelShadow+9  ; pointer to place to begin extraction from the archive
ramlocation                = pixelShadow+12 ; pointer to place to extract in usermem
endarclibrarylocations     = pixelShadow+15 ; pointer to end of archived library locations in arclibrarylocations
enddependencyqueue         = pixelShadow+18 ; pointer to end of dependency stack
nextlibptr                 = pixelShadow+21 ; pointer to save location of next lib place that needs to be relocated
jumptblptr                 = pixelShadow+24 ; pointer to start of function table for each library in the program
vectortblptr               = pixelShadow+27 ; pointer to start of archived function vector table
relocationtblptr           = pixelShadow+30 ; pointer to start of relocation table
endrelocationtbl           = pixelShadow+33 ; pointer to end of relocation table
prgmstart                  = pixelShadow+36 ; pointer to start of actual program when dealing with dependencies
appvarstartptr             = pixelShadow+39 ; pointer to start of library appvar in archive
libnameptr                 = pixelShadow+42 ; pointer to name of library to extract

; macro definitions
define lib_byte            $C0		; library signifier byte
define jp_byte             $C3		; byte for 'jp' opcode
define libmagic1           $C0		; library magic byte 1
define libmagic2           $C1		; library magic byte 2
define libmagic1alt        $BF		; alternate library magic byte 1
define libmagic2alt        $FE		; alternate library magic byte 2
define asmflag             $22		; flag storage

define prevextracted       0
define foundprgmstart      1
define keeplibinarc        2

macro relocate? name, address*
	name.source? := $
	name.destination? := address
	org name.destination?
	macro end?.relocate?
		name.length? := $ - name.destination?
		org name.source? + name.length?
		purge end?.relocate?
	end macro
end macro

; The alternate magic bytes were added to allow LibLoad to present itself as a
; library (initially just for the version check, but LibLoad could expose
; functions in the future as well). For compatibility, the LibLoad invocation
; process starts execution from the start of this header, so it needs to be
; harmless when executed. With these magic bytes, the header is decoded as:
;	cp	a,a
;	cp	a,VERSION_MAJOR*10+VERSION_MINOR
library 'LibLoad', VERSION_MAJOR*10+VERSION_MINOR, <libmagic1alt,libmagic2alt>

; We *are* the relocator, so we can't use relocations here. Set origin to 0
; (shifted by library stuff before this) and perform any relocations manually.
disable_relocations
	ld	iy,flags		; make sure iy is correct
	push	de
	push	hl

	ld	bc,69000
	ld	hl,pixelShadow
	call	_MemClear		; initialize to wipe out past runs

	ld	hl,arclibrarylocations
	ld	(endarclibrarylocations),hl
	ld	hl,dependencyqueuelocation
	ld	(enddependencyqueue),hl
	pop	hl			; restore the pointer to LibLoad

	ld	de,_libloadstart.source
	add	hl,de
	ld	de,_libloadstart.destination
	ld	bc,_libloadstart.length
	ldir				; relocate the actual LibLoad

	res	foundprgmstart,(iy+asmflag)

	jp	_libloadstart.destination ; jump to execution block

relocate _libloadstart, plotSScreen
	pop	hl			; hl->start of library jump table

	ld	(eSP),sp		; save the stack pointer if we hit an error

	ld	a,(hl)			; hl->maybe $C0 -- If the program is including libs
	cp	a,lib_byte		; is there a library we have to extract?
	jr	z,_startrelocating	; if not, just run it from wherever de was pointing
	jp	(hl)			; return to execution if there are no libs
_startrelocating:
	push	hl
	call	_PushOP1		; save program name
	pop	hl
_extractlib:				; hl->NULL terminated libray name string -> $C0,"LIBNAME",0
	ld	(hl),appVarObj		; change $C0 byte to mark as extracted
	push	hl
	call	_Mov9ToOP1		; move name of library to op1
	pop	hl
	inc	hl
	res	prevextracted,(iy+asmflag)
	ld	(libnameptr),hl

_isextracted:				; check if the current library has already been extracted
	ld	de,arclibrarylocations	; de->place to start search, hl->name to search for
_checkextractedloop:
	push	hl
	push	de
_searchextractedtbl:
	ld	a,(de)			; compare characters
	cp	a,(hl)
	jr	nz,_nomatch		; do they match?
	inc	hl
	inc	de
	or	a,a			; means we've reached the end of the string
	jr	z,_match
	jr	_searchextractedtbl
_nomatch:
	pop	de
	ld	hl,(endarclibrarylocations)
	call	_CpHLDE			; have we reached the end of the table?
	push	af
	ex	de,hl
	ld	de,15			; size of search entry (9=name, 3=ram ptr, 3=arc vec ptr)
	add	hl,de
	ex	de,hl			; check and see if we have reached the end of the extraction table
	pop	af
	pop	hl
	jr	z,_notextracted		; hasn't been extracted yet
	jr	_checkextractedloop
_match:
	set	prevextracted,(iy+asmflag) ; set the flag that this library was previously extracted, so we don't resolve absolutes
	pop	hl
	ld	de,9
	add	hl,de
	pop	de
_donesearch:				; hl->location of library in ram, hl+3->location of library vector table in archive

	ld	de,(hl)			; de=location of library vector table in archive
	ld	(vectortblptr),de
	inc	hl
	inc	hl
	inc	hl
	ld	de,(hl)			; de=location of library in ram
	ld	(ramlocation),de
	ld	hl,(libnameptr)		; restore pointer to library name
	call	_movetostrngend		; move to end of library name
	inc	hl			; bypass version byte
	ld	(jumptblptr),hl
	jp	_resloveentrypoints	; need to resolve the entry points & enqueue dependencies
_notextracted:
	ld	hl,(libnameptr)
	ld	de,(endarclibrarylocations)
	call	_Mov8b			; copy the string. it shouldn't be bigger than this
	xor	a
	ld	(de),a
	inc	de
	ld	(endarclibrarylocations),de ; now we are looking after the null byte

	ld	hl,(libnameptr)
	call	_movetostrngend
	push	hl			; save the location in the program we are on
_findbinary:
	call	_ChkFindSym
	jr	nc,_foundlibrary	; throw an error if the library doesn't exist
	jp	_missingerror		; jump to the lib missing handler
_foundlibrary:
	call	_chkinram
	jr	nz,_libinarc		; if the library is found in ram, archive the library and search again
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	_findbinary
_libinarc:
	ex	de,hl
	ld	de,9
	add	hl,de
	ld	e,(hl)
	add	hl,de
	inc	hl			; hl->size bytes
	call	_LoadDEInd_s		; de=total size of library
	push	de
	pop	bc			; bc=total size of library
;	ld	(totallibsize),bc
	ld	(appvarstartptr),hl	; hl->start of appvar in archived memory

assert libmagic1 = libmagic1alt+1
	ld	a,(hl)			; magic byte check 1
	sub	a,libmagic1alt+2
	add	a,2
	jr	nc,_libmagicerrornz
	inc	hl
	ld	a,(hl)			; magic byte check 2
	cp	a,libmagic2
	jr	z,_libexists
	cp	a,libmagic2alt
_libmagicerrornz:
	jp	nz,_versionerror	; throw an error if the library doesn't match the magic numbers

_libexists:
	inc	hl			; hl->version byte in library
	push	hl			; save location of version byte
	dec	bc
	dec	bc			; for the two magic bytes
	add	hl,bc			; hl->end of library
	ld	bc,-3
	add	hl,bc
	ld	de,(hl)			; de=size of library code
	ld	(extractedsize),de
	add	hl,bc
	ld	de,(hl)			; de->offset to start of dependency table
	ld	(endrelocationtbl),hl	; hl->end of relocation table
	ld	hl,(appvarstartptr)
	add	hl,de			; hl->start of dependencies -- need to store each dependency onto the queue.
	ld	(arclocation),hl	; hl->start of library extraction location
	pop	de			; de->version byte of library
	ld	a,(de)			; a=version of library
	pop	hl			; hl->version of library in the program
	cp	a,(hl)			; check if library version in program is greater than library version on-calc
	jp	c,_versionerror		; c flag set if on-calc lib version is less than the one used in the program

_goodversion:
	inc	hl			; hl->start of program function jump table
	inc	de			; de->start of archived function vector table
	ld	(vectortblptr),de	; save the pointer to the archived vector table
	ld	(jumptblptr),hl		; save the pointer to the function jump table
	ld	hl,(endarclibrarylocations)
	ld	(hl),de
	inc	hl
	inc	hl
	inc	hl
	ld	(endarclibrarylocations),hl

	ld	hl,usermem		; this is where programs are extracted to
	ld	de,(asm_prgm_size)
	add	hl,de			; hl->end of program+libaries
	ex	de,hl			; de->location to extract to

	ld	(ramlocation),de	; save this pointer

	res	keeplibinarc,(iy+asmflag)
	ld	hl,(arclocation)	; hl->start of library code in archive
	ld	de,(extractedsize)
	add	hl,de			; hl->start of library relocation table
	ld	(relocationtblptr),hl	; store this
	ld	de,(endrelocationtbl)
	call	_CpHLDE			; check and see if they match -- if so, this library is going to remain in the archive
	jr	nz,_needtoextractlib
	ld	hl,(arclocation)
	ld	(ramlocation),hl	; okay, not a ram location, but it's use is still the same
	set	keeplibinarc,(iy+asmflag)
_needtoextractlib:

	ld	de,(ramlocation)
	ld	hl,(endarclibrarylocations)
	ld	(hl),de
	inc	hl
	inc	hl
	inc	hl
	ld	(endarclibrarylocations),hl

	bit	keeplibinarc,(iy+asmflag)
	jr	nz,_resloveentrypoints	; only need to resolve entry points if in the archive

	ld	hl,(extractedsize)
	push	hl
	push	de
	push	bc
	call	_EnoughMem		; hl=size of library
	pop	bc
	pop	de
	pop	hl
	jp	c,_errmemory		; throw a memory error -- need more ram!
	call	_InsertMem		; insert memory for the relocated library (de)

	ld	hl,(extractedsize)	; extracted size = dependency jumps + library code
	ld	de,(asm_prgm_size)
	add	hl,de
	ld	(asm_prgm_size),hl	; store new size of program+libraries

	ld	hl,(arclocation)	; hl->start of library code
	ld	de,(ramlocation)	; de->insertion place
	ld	bc,(extractedsize)	; bc=extracted library size
	ldir				; copy in the library to ram
_resloveentrypoints:
	ld	hl,(ramlocation)
	call	_enqueuealldependencies	; get all the dependency pointers that reside in the ram lib
	ld	hl,(jumptblptr)		; hl->start of function jump table
_resloveentrypointsloop:
	ld	a,(hl)
	cp	a,jp_byte		; jp byte ($C3)
	jr	nz,_doneresloveentrypoints
	inc	hl			; bypass jp byte ($C3)
	push	hl
	ld	hl,(hl)			; offset in vector table (0,3,6, etc.)
	ld	bc,3
	call	__idivs			; originally the offset was just added because vectors were stored in three bytes, now it is just 2 to save space
	add	hl,hl			; (offset/3) * 2
	ld	de,(vectortblptr)	; hl->start of vector table
	add	hl,de			; hl->correct vector entry
	call	_loaddeind_s		; de=offest in lib for function
	ld	hl,(ramlocation)
	add	hl,de			; hl->function in ram
	ex	de,hl			; de->function in ram
	pop	hl			; restore jump offset
	ld	(hl),de			; de=resolved address
	inc	hl
	inc	hl
	inc	hl			; move to next jump
	jr	_resloveentrypointsloop
_doneresloveentrypoints:		; finished resolving entry points
	ld	(nextlibptr),hl		; hl->next library in program (if there is one)

	bit	prevextracted,(iy+asmflag) ; have we already resolved the absolute addresses for the library?
	jr	nz,_donerelocateabsolutes

	bit	keeplibinarc,(iy+asmflag) ; we don't need to store anything if we are here
	jr	nz,_donerelocateabsolutes ; really, this is just a precautionary check -- should work fine without this

_relocateabsolutes:
	ld	hl,(relocationtblptr)	; restore this
_relocateabsolutesloop:
	ld	de,(endrelocationtbl)
	call	_CpHLDE			; have we reached the end of the relocation table
	jr	z,_donerelocateabsolutes
	push	hl			; save pointer to relocation table current
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a			; hl->offset in ram library to relocate
	call	_SetHLUTo0
	ld	de,(ramlocation)
	add	hl,de			; hl->location in library to relocate
	push	hl
	ld	hl,(hl)			; hl=offset we are relocating
	ld	de,(ramlocation)
	add	hl,de			; hl=new address
	ex	de,hl			; de=new address
	pop	hl
	ld	(hl),de			; resolved absolute address
	pop	hl
	inc	hl
	inc	hl			; move to next relocation vector
	jr	_relocateabsolutesloop
_donerelocateabsolutes:

	bit	foundprgmstart,(iy+asmflag) ; have we found the start of the program?
	jr	nz,_nosetstart

	ld	hl,(nextlibptr)
	ld	a,(hl)			; hl->maybe lib_byte -- If the program is using more libraries
	cp	a,lib_byte
	jp	z,_extractlib		; extract the next library

_checkifdependencies:			; the first time we hit this, we have all the dependencies placed onto the queue that the libraries use.
	bit	foundprgmstart,(iy+asmflag)
	jr	nz,_nosetstart
	ld	(prgmstart),hl
	set	foundprgmstart,(iy+asmflag)
_nosetstart:
	ld	hl,(enddependencyqueue)
	ld	de,dependencyqueuelocation
	call	_CpHLDE			; make sure we are done parsing the dependency queue
					; now we need to parse the libraries like they are programs. this will be fun.
	jr	z,_runpgrm
	dec	hl
	dec	hl
	dec	hl			; hl->dependency $C0,"LIBNAME",0,VERSION,JUMP_TABLE
	ld	(enddependencyqueue),hl	; store pointer to next dependency
	ld	hl,(hl)			; valid pointer to $C0 (lib_byte)
	jp	_extractlib		; extract current dependency if needed, or resolve entry points

_runpgrm:
	call	_PopOP1			; restore program name
	ld	hl,(prgmstart)
	jp	(hl)			; passed all the checks; let's start execution! :)

_enqueuealldependencies:
	bit	keeplibinarc,(iy+asmflag) ; we don't need to store anything if we are here
	ret	nz			; really, this is just a precautionary check -- should work fine without
_enqueuealldependenciesloop:
	ld	a,(hl)
	cp	a,lib_byte		; is there a dependency?
	jr	nz,_checkextracteddependent

	ex	de,hl
	ld	hl,(enddependencyqueue)
	ld	(hl),de			; save pointer to start of this dependency -- one at a time
	inc	hl
	inc	hl
	inc	hl			; move to next pointer
	ld	(enddependencyqueue),hl	; save next pointer
	ex	de,hl

_skipdependencystore:
	call	_movetostrngend
	inc	hl			; move to start of dependency jump table
_movetonextjump:
	ld	a,(hl)
	cp	a,jp_byte
	jr	nz,_enqueuealldependenciesloop

	inc	hl
	inc	hl
	inc	hl
	inc	hl			; jp address
	jr	_movetonextjump
_checkextracteddependent:
	cp	a,appVarObj
	jr	z,_skipdependencystore	; keep going
	ret

_movetostrngend:
	ld	bc,0
	ld	a,c
	cpir
	ret

_versionerror:
	ld	hl,_versionlibstr
	jr	_throwerror
_missingerror:				; can't find a dependent lib
	ld	hl,_missinglibstr
_throwerror:				; draw the error message onscreen
	ld	a,lcdBpp16
	ld	(mpLcdCtrl),a
	ld	sp,(eSP)
	push	hl
	call	_DrawStatusBar
	call	_ClrScrn		; clean up the screen a bit
	call	_HomeUp			; if we encounter an error
	pop	hl
	set	textInverse,(iy+textFlags)
	ld	a,2
	ld	(curcol),a
	call	_PutS
	res	textInverse,(iy+textFlags)
	call	_NewLine
	call	_NewLine		; make it look pretty
	ld	hl,_libnamestr
	call	_PutS
	ld	hl,OP1+1
	call	_PutS
	call	_NewLine
	call	_NewLine
	ld	hl,_downloadstr
	call	_PutS
	push	hl
	call	_NewLine
	pop	hl
	call	_PutS
_waitkeyloop:
	call	_GetCSC
	cp	a,skEnter
	jr	z,_exitwaitloop
	cp	a,skClear
	jr	z,_exitwaitloop
	jr	_waitkeyloop
_exitwaitloop:
	call	_ClrScrn
	call	_HomeUp			; stop execution of the program
	jp	_PopOP1			; restore program name

_versionlibstr:				; strings for LibLoad Errors
	db	"ERROR: Library Version",0
_missinglibstr:
	db	"ERROR: Missing Library",0
_libnamestr:
	db	"Library Name: ",0
_downloadstr:
	db	"Download here: ",0
_urlstr:
	db	"https://tiny.cc/clibs",0

end relocate
enable_relocations
