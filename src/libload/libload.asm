;=========================================================================
; Copyright (C) 2015-2025 Matt "MateoConLechuga" Waltz
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
; uses:   cursorImage
; note:   updated size is added to the copy in ram of the program for libraries
; notes:  all code is location independent; no need to relocate to absolute address.
;         keeping in archive is safe.
;=========================================================================

; includes
include '../include/library.inc'

define VERSION_MAJOR       4
define VERSION_MINOR       1

buf := ti.cursorImage

arc_lib_locs      := buf + 000	; place to store locations of archived libraries
dep_queue_ptr     := buf + 450	; queue for keeping track of which libraries still need to be resolved
error_sp          := buf + 850	; save sp for errors
total_lib_size    := buf + 853	; total size of the library appvar (not used)
loaded_size       := buf + 856	; holds extracted size of the library
arclocation       := buf + 859	; pointer to place to begin extraction from the archive
ramlocation       := buf + 862	; pointer to place to extract in usermem
end_arc_lib_locs  := buf + 865	; pointer to end of archived library locations in arc_lib_locs
end_dep_queue     := buf + 868	; pointer to end of dependency stack
next_lib_ptr      := buf + 871	; pointer to save location of next lib place that needs to be relocated
jump_tbl_ptr      := buf + 874	; pointer to start of function table for each library in the program
vector_tbl_ptr    := buf + 877	; pointer to start of archived function vector table
reloc_tbl_ptr     := buf + 880	; pointer to start of relocation table
end_reloc_tbl     := buf + 883	; pointer to end of relocation table
prgm_start        := buf + 886	; pointer to start of actual program when dealing with dependencies
appvar_ptr        := buf + 889	; pointer to start of library appvar in archive
lib_name_ptr      := buf + 892	; pointer to name of library to extract
show_msgs         := buf + 895  ; show error messages or just exit with error
flag_save         := buf + 896  ; save/restore modified iy flag
ix_save           := buf + 897  ; save/restore modified ix register

REQ_LIB_MARKER    := $C0	; required library signifier byte
OPT_LIB_MARKER    := $C1	; optional library signifier byte
JP_OPCODE         := $C3	; byte for 'jp' opcode
LIB_MAGIC_1       := $C0	; library magic byte 1
LIB_MAGIC_2       := $C1	; library magic byte 2
LIB_MAGIC_1_ALT   := $BF	; alternate library magic byte 1
LIB_MAGIC_2_ALT   := $FE	; alternate library magic byte 2

LIB_FLAGS         := $22	; flag storage
loaded            := 0
keep_in_arc       := 1
optional          := 2
is_dep            := 3

macro move_string_to_end
	ld	bc, 0
	ld	a, c
	cpir
end macro

; The alternate magic bytes were added to allow LibLoad to present itself as a
; library (initially just for the version check, but LibLoad could expose
; functions in the future as well). For compatibility, the LibLoad invocation
; process starts execution from the start of this header, so it needs to be
; harmless when executed. With these magic bytes, the header is decoded as:
;	cp	a, a
;	cp	a, VERSION_MAJOR*10+VERSION_MINOR

library LibLoad, VERSION_MAJOR*10+VERSION_MINOR, <LIB_MAGIC_1_ALT, LIB_MAGIC_2_ALT>

disable_relocations

	ld	iy, ti.flags
	push	de			; de->start of library jump table
	push	hl

	push	bc
	ld	bc, 1020
	ld	hl, buf
	call	ti.MemClear
	pop	bc

	ld	a, (iy + LIB_FLAGS)
	ld	(flag_save), a
	ld	(ix_save), ix		; save IX since older ICE programs don't

	ld	hl, $AA55AA
	xor	a, a
	sbc	hl, bc
	jr	z, .no_show_msgs
; .show_msgs:
	inc	a
.no_show_msgs:
	ld	hl, show_msgs		; disable or enable error printing
	ld	(hl), a

	pop	hl
	ld	de,helpers.source
	add	hl,de
	ld	de,helpers.destination
	ld	bc,helpers.length
	ldir
	ld	hl, arc_lib_locs
	ld	(end_arc_lib_locs), hl
	ld	hl, dep_queue_ptr
	ld	(end_dep_queue), hl
	pop	hl			; hl->start of library jump table

	ld	(error_sp), sp

	res	is_dep, (iy + LIB_FLAGS)
	res	optional, (iy + LIB_FLAGS)
	ld	a, (hl)
	cp	a, REQ_LIB_MARKER
	jr	z, start
	set	optional, (iy + LIB_FLAGS)
	cp	a, OPT_LIB_MARKER
	jr	z, start
	ld	a, (flag_save)
	ld	(iy + LIB_FLAGS), a	; restore flag bits
	ld	ix, (ix_save)		; restore IX register
	jp	(hl)			; return to execution if there are no libs

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

relocate helpers, buf + 900
if 0
call_relative:
	pop	ix
	pea	ix + 3
	push	de
	ld	de, (ix)
	add	ix, de
	pop	de
	jp	(ix)
end if
jump_relative:
	pop	ix
	push	de
	ld	de, (ix)
	add	ix, de
	pop	de
	jp	(ix)
ld_relative:
	pop	hl
	ld	de, (hl)
	inc	hl
	inc	hl
	inc	hl
	push	hl
	add	hl, de			; add hl, relative - 3
	ret
end relocate

macro rcall? name
	call	call_relative
	dl	name - $
end macro

macro rjump? name
	call	jump_relative
	dl	name - $
end macro

macro rload? name
	call	ld_relative
	dl	name - $ - 3
end macro

start:
	push	hl
	call	ti.PushOP1		; save calling program name
	pop	hl
load_lib:				; hl->NULL terminated libray name string ($CX, 'LIBNAME', 0)
	ld	(hl), ti.AppVarObj	; change $CX byte to mark as loaded
	push	hl
	call	ti.Mov9ToOP1
	pop	hl
	inc	hl
	res	loaded, (iy + LIB_FLAGS)
	ld	(lib_name_ptr), hl

check_already_loaded:
	ld	de, arc_lib_locs
.loop:					; de->place to start search,  hl->name to search for
	push	hl
	push	de
.seach_tbl:
	ld	a, (de)			; compare characters
	cp	a, (hl)
	jr	nz, .no_match		; do they match?
	inc	hl
	inc	de
	or	a, a			; means we've reached the end of the string
	jr	nz, .seach_tbl

.match:					; mark as previously loaded (don't resolve absolutes again)
	set	loaded, (iy + LIB_FLAGS)
	pop	hl
	ld	de, 9
	add	hl, de
	pop	de
.done:					; hl->location of library in ram, hl+3->location of library vector table in archive
	ld	de, (hl)		; de=location of library vector table in archive
	ld	(vector_tbl_ptr), de
	inc	hl
	inc	hl
	inc	hl
	ld	de, (hl)		; de=location of library in ram
	ld	(ramlocation), de
	ld	hl, (lib_name_ptr)	; restore pointer to library name
	move_string_to_end		; move to end of library name
	inc	hl			; bypass version byte
	ld	(jump_tbl_ptr), hl
	rjump	resolve_entry_points	; need to resolve the entry points & enqueue dependencies

.no_match:
	pop	de
	ld	hl, (end_arc_lib_locs)
	or	a, a
	sbc	hl, de			; have we reached the end of the table?

	ld	hl, 15			; size of search entry (9=name, 3=ram ptr, 3=arc vec ptr)
	add	hl, de
	ex	de, hl			; end of the extraction table?
	pop	hl
	jr	nz, .loop

.not_loaded:
	ld	hl, (lib_name_ptr)
	move_string_to_end
	push	hl			; save the location in the program we are on
findlib:
	call	ti.ChkFindSym
	jr	nc, .foundlib		; throw an error if the library doesn't exist
	bit	optional,(iy + LIB_FLAGS)
	; if optional, zeroize marker and move on
	jr	nz, optional_lib_clear_pop_hl
.missing:
	rjump	error_missing		; jump to the lib missing handler

.foundlib:
	call	ti.ChkInRam
	jr	nz, .archived		; if the library is found in ram, archive the library and search again
	call	ti.PushOP1
	call	ti.Arc_Unarc
	call	ti.PopOP1
	jr	findlib

.archived:
	ex	de, hl
	ld	de, 9
	add	hl, de
	ld	e, (hl)
	add	hl, de
	inc	hl			; hl->size bytes
	call	ti.LoadDEInd_s		; de=total size of library
	push	de
	pop	bc			; bc=total size of library
;	ld	(total_lib_size), bc
	ld	(appvar_ptr), hl	; hl->start of appvar in archived memory

assert LIB_MAGIC_1 = LIB_MAGIC_1_ALT+1
	ld	a, (hl)			; magic byte check 1
	sub	a, LIB_MAGIC_1_ALT+2
	add	a, 2
	jr	nc, .magic_error
	inc	hl
	ld	a, (hl)			; magic byte check 2
	cp	a, LIB_MAGIC_2
	jr	z, lib_exists
	cp	a, LIB_MAGIC_2_ALT
.magic_error:
	jr	z, lib_exists
	bit	optional,(iy + LIB_FLAGS)
	jr	z, invalid_error
optional_lib_clear_pop_hl:
	pop	hl			; get version byte pointer
optional_lib_clear:
	push	hl
	ld	hl, (lib_name_ptr)
	dec	hl			; library marker type byte
	ld	de, 0
	ld	(hl), e			; mark optional library as not found
	pop	hl
	inc	hl			; skip version byte
	ld	a, JP_OPCODE
.loop:
	cp	a, (hl)			; jp byte ($C3)
	jr	nz, .done
	inc	hl
	ld	(hl), de		; make the vector zero
	inc	hl
	inc	hl
	inc	hl			; move to next jump
	jr	.loop

.done:
	rjump	check_for_lib_marker

invalid_error:
	rjump	error_invalid		; throw an error if the library doesn't match the magic numbers

lib_exists:
	inc	hl			; hl->version byte in library
	push	hl			; save location of version byte
	dec	bc
	dec	bc			; for the two magic bytes
	add	hl, bc			; hl->end of library
	ld	bc, -3
	add	hl, bc
	ld	de, (hl)		; de=size of library code
	ld	(loaded_size), de
	add	hl, bc
	ld	de, (hl)		; de->offset to start of dependency table
	ld	(end_reloc_tbl), hl	; hl->end of relocation table
	ld	hl, (appvar_ptr)
	add	hl, de			; hl->start of dependencies -- need to store each dependency onto the queue.
	ld	(arclocation), hl	; hl->start of library loaded location
	pop	de			; de->version byte of library
	ld	a, (de)			; a=version of library
	pop	hl			; hl->version of library in the program
	cp	a, (hl)			; check if library version in program is greater than library version on-calc
	jr	nc, good_version
	bit	optional,(iy + LIB_FLAGS)
	jr	nz, optional_lib_clear
.version_error:
	rjump	error_version		; c flag set if on-calc lib version is less than the one used in the program

good_version:
	push	hl
	push	de
	ld	hl, (lib_name_ptr)	; store the library name as being loaded
	ld	de, (end_arc_lib_locs)
	call	ti.Mov8b		; copy the string. it shouldn't be bigger than this
	xor	a, a
	ld	(de), a
	inc	de
	ld	(end_arc_lib_locs), de
	pop	de
	pop	hl
	inc	hl			; hl->start of program function jump table
	inc	de			; de->start of archived function vector table
	ld	(vector_tbl_ptr), de	; save the pointer to the archived vector table
	ld	(jump_tbl_ptr), hl	; save the pointer to the function jump table
	ld	hl, (end_arc_lib_locs)
	ld	(hl), de
	inc	hl
	inc	hl
	inc	hl
	ld	(end_arc_lib_locs), hl

	ld	hl, ti.userMem		; this is where programs are loaded to
	ld	de, (ti.asm_prgm_size)
	add	hl, de			; hl->end of program+libaries
	ex	de, hl			; de->location to load to

	ld	(ramlocation), de	; save this pointer

	res	keep_in_arc, (iy + LIB_FLAGS)
	ld	hl, (arclocation)	; hl->start of library code in archive
	ld	de, (loaded_size)
	add	hl, de			; hl->start of library relocation table
	ld	(reloc_tbl_ptr), hl	; store this
	ld	de, (end_reloc_tbl)
	or	a, a
	sbc	hl, de			; check and see if they match -- if so, this library is going to remain in the archive
	jr	nz, need_to_load_lib
	ld	hl, (arclocation)
	ld	(ramlocation), hl	; okay, not a ram location, but it's use is still the same
	set	keep_in_arc, (iy + LIB_FLAGS)

need_to_load_lib:
	ld	de, (ramlocation)
	ld	hl, (end_arc_lib_locs)
	ld	(hl), de
	inc	hl
	inc	hl
	inc	hl
	ld	(end_arc_lib_locs), hl

	bit	keep_in_arc, (iy + LIB_FLAGS)
	jr	nz, resolve_entry_points

.not_in_arc:
	ld	hl, (loaded_size)
	push	hl
	push	de
	push	bc
	call	ti.EnoughMem		; hl=size of library
	pop	bc
	pop	de
	pop	hl
	jr	nc,.enough_mem
	call	ti.PopOP1		; pop program name
	jp	ti.ErrMemory		; throw a memory error -- need more ram!

.enough_mem:
	call	ti.InsertMem		; insert memory for the relocated library (de)

	ld	hl, (loaded_size)	; loaded size = dependency jumps + library code
	ld	de, (ti.asm_prgm_size)
	add	hl, de
	ld	(ti.asm_prgm_size), hl	; store new size of program+libraries

	ld	hl, (arclocation)	; hl->start of library code
	ld	de, (ramlocation)	; de->insertion place
	ld	bc, (loaded_size)	; bc=loaded library size
	ldir				; copy in the library to ram

resolve_entry_points:
	ld	hl, (ramlocation)

	; get all the dependency pointers that reside in the ram lib
enqueue_all_deps:			; we don't need to store anything if we are here
	bit	keep_in_arc, (iy + LIB_FLAGS)
	jr	nz, .finish		; really,  this is just a precautionary check -- should work fine without
.loop:
	res	optional, (iy + LIB_FLAGS)
	ld	a, (hl)
	cp	a, REQ_LIB_MARKER	; is there a dependency?
	jr	nz, .check
	ex	de, hl
	ld	hl, (end_dep_queue)
	ld	(hl), de		; save pointer to start of this dependency -- one at a time
	inc	hl
	inc	hl
	inc	hl			; move to next pointer
	ld	(end_dep_queue), hl	; save next pointer
	ex	de, hl
.skip:
	move_string_to_end
	inc	hl			; move to start of dependency jump table
	ld	a, JP_OPCODE
.next:
	cp	a, (hl)			; jp byte ($C3)
	jr	nz, .loop
	inc	hl
	inc	hl
	inc	hl
	inc	hl			; jp address
	jr	.next

.check:
	cp	a, ti.AppVarObj
	jr	z, .skip		; keep going
.finish:

resolve_entry_points_enqueued:
	ld	hl, (jump_tbl_ptr)	; hl->start of function jump table
	ld	bc, 3
	ld	a, JP_OPCODE
.loop:
	cp	a, (hl)			; jp byte ($C3)
	jr	nz, .done
	inc	hl			; bypass jp byte ($C3)
	push	hl
	ld	hl, (hl)		; offset in vector table (0, 3, 6, etc.)
	call	ti._idivu		; originally the offset was just added because vectors were stored in three bytes,  now it is just 2 to save space
	add	hl, hl			; (offset/3) * 2
	ld	de, (vector_tbl_ptr)	; hl->start of vector table
	add	hl, de			; hl->correct vector entry
	call	ti.LoadDEInd_s		; de=offest in lib for function
	ld	hl, (ramlocation)
	add	hl, de			; hl->function in ram
	ex	de, hl			; de->function in ram
	pop	hl			; restore jump offset
	ld	(hl), de		; de=resolved address
	add	hl, bc			; move to next jump
	jr	.loop

.done:					; finished resolving entry points
					; now relocate absolutes in library
relocate_absolutes:
	ld	(next_lib_ptr), hl	; hl->next library in program (if there is one)
	bit	loaded, (iy + LIB_FLAGS)
	jr	nz, .done
	bit	keep_in_arc, (iy + LIB_FLAGS)
	jr	nz, .done
	ld	hl, (reloc_tbl_ptr)	; restore this
.loop:
	ld	de, (end_reloc_tbl)
	or	a, a
	sbc	hl, de			; have we reached the end of the relocation table
	jr	z, .done
	add	hl, de			; restore hl
	ld	e, (hl)
	inc	hl
	push	hl			; save pointer to relocation table current
	ld	d, (hl)
	ex.s	de, hl			; hl->offset in ram library to relocate
	; UHL = 0

	ld	de, (ramlocation)
	add	hl, de			; hl->location in library to relocate
	push	hl
	ld	hl, (hl)		; hl=offset we are relocating
	; ld	de, (ramlocation)
	add	hl, de			; hl=new address
	ex	de, hl			; de=new address
	pop	hl
	ld	(hl), de		; resolved absolute address
	pop	hl
	inc	hl			; move to next relocation vector
	jr	.loop

.done:					; have we found the start of the program?
	bit	is_dep, (iy + LIB_FLAGS)
	jr	nz, load_next_dep	; if loading dependencies, don't check markers
	ld	hl, (next_lib_ptr)
check_for_lib_marker:
	res	optional, (iy + LIB_FLAGS)
	ld	a, (hl)			; hl->maybe REQ_LIB_MARKER -- If the program is using more libraries
	cp	a, REQ_LIB_MARKER
	jr	z, goto_load_lib
	set	optional, (iy + LIB_FLAGS)
	cp	a, OPT_LIB_MARKER
	jr	nz, check_has_deps
goto_load_lib:
	rjump	load_lib		; load the next library

check_has_deps:				; the first time we hit this,  we have all the dependencies placed onto the queue that the libraries use.
	res	optional, (iy + LIB_FLAGS)
	bit	is_dep, (iy + LIB_FLAGS)
	jr	nz, load_next_dep
	ld	(prgm_start), hl	; save program start
	set	is_dep, (iy + LIB_FLAGS)
load_next_dep:
	ld	hl, (end_dep_queue)
	ld	de, dep_queue_ptr
	or	a, a
	sbc	hl, de			; make sure we are done parsing the dependency queue
	add	hl, de
					; now we need to parse the libraries like they are programs. this will be fun.
	jr	z, .exit
	dec	hl
	dec	hl
	dec	hl			; hl->dependency ($C0, "LIBNAME", 0, VERSION, JUMP_TABLE)
	ld	(end_dep_queue), hl
	ld	hl, (hl)		; valid pointer to $C0 (REQ_LIB_MARKER)
	rjump	load_lib		; load current dependency if needed,  or resolve entry points

.exit:
	call	ti.PopOP1		; restore program name
	ld	hl, (prgm_start)
	ld	ix, (ix_save)		; restore IX register
	ld	a, (flag_save)
	ld	(iy + LIB_FLAGS), a	; restore flag bits
	ld	a, 1
	jp	(hl)			; passed all the checks; let's start execution! :)

error_invalid:
	rload	str_error_invalid
	jr	throw_error

error_version:
	rload	str_error_version
	jr	throw_error

error_missing:
	rload	str_error_missing
throw_error:				; draw the error message onscreen
	ld	sp, (error_sp)
	ld	a, (show_msgs)
	or	a, a
	jr	z, .return
.show_msgs:
	ld	a, ti.lcdBpp16
	ld	(ti.mpLcdCtrl), a
	push	hl
	call	ti.DrawStatusBar
	call	ti.ClrScrn		; clean up the screen a bit
	call	ti.HomeUp		; if we encounter an error
	pop	hl
	set	ti.textInverse, (iy + ti.textFlags)
	ld	a, 2
	ld	(ti.curCol), a
	call	ti.PutS
	res	ti.textInverse, (iy + ti.textFlags)
	call	ti.NewLine
	call	ti.NewLine		; make it look pretty
	rload	str_lib_name
	call	ti.PutS
	ld	hl, ti.OP1+1+8
	ld	(hl), 0
	ld	hl, ti.OP1+1
	call	ti.PutS
	call	ti.NewLine
	call	ti.NewLine
	rload	str_download
	call	ti.PutS
	push	hl
	call	ti.NewLine
	pop	hl
	call	ti.PutS
.wait_key:
	call	ti.GetCSC
	cp	a,ti.skEnter
	jr	z,.exit
	cp	a,ti.skClear
	jr	nz,.wait_key
.exit:
	call	ti.ClrScrn
	call	ti.HomeUp
.return:
	call	ti.PopOP1
	ld	a, (flag_save)
	ld	(iy + LIB_FLAGS), a	; restore flag bits
	ld	ix, (ix_save)		; restore IX register
	xor	a, a			; return with zero in a
	ret

str_error_version:
	db	"ERROR: Library Version", 0
str_error_missing:
	db	"ERROR: Missing Library", 0
str_error_invalid:
	db	"ERROR: Invalid Library", 0
str_lib_name:
	db	"Library Name: ", 0
str_download:
	db	"Download here: ", 0
	db	"https://tiny.cc/clibs", 0
