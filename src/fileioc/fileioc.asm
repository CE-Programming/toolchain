;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library FILEIOC, 8

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export ti_CloseAll
	export ti_Open
	export ti_OpenVar
	export ti_Close
	export ti_Write
	export ti_Read
	export ti_GetC
	export ti_PutC
	export ti_Delete
	export ti_DeleteVar
	export ti_Seek
	export ti_Resize
	export ti_IsArchived
	export ti_SetArchiveStatus
	export ti_Tell
	export ti_Rewind
	export ti_GetSize
;-------------------------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------------------------
	export ti_GetTokenString
	export ti_GetDataPtr
	export ti_Detect
	export ti_DetectVar
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
	export ti_SetVar
	export ti_StoVar
	export ti_RclVar
	export ti_AllocString
	export ti_AllocList
	export ti_AllocMatrix
	export ti_AllocCplxList
	export ti_AllocEqu
;-------------------------------------------------------------------------------
; v4 functions
;-------------------------------------------------------------------------------
	export ti_DetectAny
	export ti_GetVATPtr
	export ti_GetName
	export ti_Rename
	export ti_RenameVar
;-------------------------------------------------------------------------------
; v5 functions
;-------------------------------------------------------------------------------
	export ti_ArchiveHasRoom
;-------------------------------------------------------------------------------
; v6 functions
;-------------------------------------------------------------------------------
	export ti_SetGCBehavior
;-------------------------------------------------------------------------------
; v7 functions
;-------------------------------------------------------------------------------
; No new functions, but a change was made to slot openness managemnent such that
; it is no longer necessary to call `ti_CloseAll` in initialization. New
; programs omitting this initialization require this change.
;-------------------------------------------------------------------------------
; v8 functions
;-------------------------------------------------------------------------------
	export ti_ArchiveHasRoomVar

;-------------------------------------------------------------------------------
vat_ptr0 := $d0244e
vat_ptr1 := $d0257b
vat_ptr2 := $d0257e
vat_ptr3 := $d02581
vat_ptr4 := $d02584
data_ptr0 := $d0067e
data_ptr1 := $d00681
data_ptr2 := $d01fed
data_ptr3 := $d01ff3
data_ptr4 := $d01ff9
resize_amount := $e30c0c
curr_slot := $e30c11
TI_MAX_SIZE := 65505
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
ti_AllocString:
ti_AllocEqu:
; allocates space for a string/equation
; args:
;  sp + 3 : len of string/equation
;  sp + 6 : pointer to alloc routine
; return:
;  hl -> allocated space
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	iy, (iy + 6)
	push	hl
	inc	hl
	inc	hl
	call	ti._indcall
	pop	de
	ld	(hl), e
	inc	hl
	ld	(hl), d
	dec	hl
	ret

;-------------------------------------------------------------------------------
ti_AllocCplxList:
; allocates space for a complex list
; args:
;  sp + 3 : dim of list
;  sp + 6 : pointer to alloc routine
; return:
;  hl -> allocated space
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	iy, (iy + 6)
	push	hl
	add	hl, hl
	jr	util_alloc_var

;-------------------------------------------------------------------------------
ti_AllocList:
; allocates space for a real list
; args:
;  sp + 3 : dim of list
;  sp + 6 : pointer to alloc routine
; return:
;  hl -> allocated space
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	iy, (iy + 6)
	push	hl
	jr	util_alloc_var

;-------------------------------------------------------------------------------
ti_AllocMatrix:
; allocates space for a matrix
; args:
;  sp + 3 : matrix rows
;  sp + 6 : matrix cols
;  sp + 9 : pointer to alloc routine
; return:
;  hl -> allocated space
	ld	iy, 0
	add	iy, sp
	ld	h, (iy + 3)
	ld	l, (iy + 6)
	ld	iy, (iy + 9)
	push	hl
	mlt	hl
util_alloc_var:
	call	ti.HLTimes9
	inc	hl
	inc	hl
	push	hl
	call	ti._indcall
	pop	de
	pop	de
	add	hl, de
	or	a, a
	sbc	hl, de
	ret	z
	ld	(hl), e
	inc	hl
	ld	(hl), d
	dec	hl
	ret

;-------------------------------------------------------------------------------
ti_CloseAll:
; closes all currently open file handles
; args:
;  n/a
; return:
;  n/a
	ld	hl, variable_offsets + 3 - 1
	push	hl
	pop	de
	inc	de
	ld	bc, 4 * 3
; upper byte of offset = 12
	ld	(hl), c
	ldir
	ret

;-------------------------------------------------------------------------------
ti_Resize:
; resizes an appvar variable
; args:
;  sp + 3 : new size
;  sp + 6 : slot index
; return:
;  hl = new size if no failure
	pop	hl
	pop	de			; de = new size
	pop	bc			; c = slot
	push	bc
	push	de
	push	hl
	call	util_is_slot_open
	jp	nz, util_ret_neg_one
	push	de
	call	util_is_in_ram
	pop	hl
	jp	c, util_ret_null
	ld	de, TI_MAX_SIZE
	or	a,a
	sbc	hl,de
	add	hl,de
	push	af
	push	hl
	call	ti_Rewind.rewind	; rewind file offset
	pop	hl
	pop	af
	jp	nc,util_ret_null	; return if too big
	push	hl
	call	util_get_slot_size
	pop	hl
	or	a,a
	sbc	hl,bc
	ld	(resize_amount), hl
	jr	z, .no_resize
	jr	c, .decrease
.increase:
	call	ti.EnoughMem
	jp	c, util_ret_null
	ex	de, hl
	call	util_insert_mem
	jr	.no_resize
.decrease:
	push	hl
	pop	bc
	or	a, a
	sbc	hl, hl
	sbc	hl, bc
	ld	(resize_amount), hl
	call	util_delete_mem
.no_resize:
	ld	hl, (resize_amount)
	ret

;-------------------------------------------------------------------------------
ti_IsArchived:
; Checks if a variable is archived
; args:
;  sp + 3 : Slot number
; return:
;  0 if not archived
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jr	z, util_is_in_ram
	xor	a, a
	ret
util_is_in_ram:
	call	util_get_vat_ptr
	ld	hl, (hl)
	dec	hl
	dec	hl
	dec	hl
	dec	hl
	dec	hl
	ld	a, (hl)
	or	a, a
	sbc	hl, hl
	cp	a, $d0
	ret	nc
	inc	hl
	ret

;-------------------------------------------------------------------------------
ti_OpenVar:
; opens a variable
; args:
;  sp + 3 : pointer to variable name
;  sp + 6 : open flags
;  sp + 9 : variable Type
; return:
;  slot index if no error
	ld	iy, 0
	add	iy, sp
	ld	a, (iy + 9)
;	jr	ti_Open.start		; emulated by dummifying next instruction
	db	$fe			; ld a,ti.AppVarObj -> cp a,$3e \ dec d
assert ti.AppVarObj = $15

;-------------------------------------------------------------------------------
ti_Open:
; opens an appvar, acting as a file handle
; args:
;  sp + 3 : pointer to appvar name
;  sp + 6 : open flags
; return:
;  a = slot index if no error
	ld	a, ti.AppVarObj
.start:
	ld	(.smc_type), a
	ld	(ti.OP1), a
	ld	iy, ti.flags

	ld	hl, variable_offsets + (5 * 3) - 1
	ld	a, 5
.find_slot:
; slot open (in use): upper byte of offset == 0
; slot closed (free): upper byte of offset > slot
	cp	a, (hl)
	jr	c, .slot
	dec	hl
	dec	hl
	dec	hl
	dec	a
	jr	nz, .find_slot
	ret

.slot:
	ld	(curr_slot), a
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	hl, (ix + 6)
	ld	de, ti.OP1 + 1
	call	ti.Mov8b
	xor	a, a
	ld	(de), a
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 'w'
	ld	iy, ti.flags
	jr	nz, .no_overwite
	call	ti.PushOP1
	call	ti.ChkFindSym
	call	nc, ti.DelVarArc
	call	ti.PopOP1
.no_overwite:
	ld	hl,(ix + 9)
	ld	a,(hl)
	cp	a,'r'
	jr	z,.mode
	cp	a,'a'
	jr	z,.mode
	cp	a,'w'
	jp	nz,util_ret_null_pop_ix
.mode:
	inc	hl
	ld	a,(hl)
	cp	a,'+'
	jr	nz,.no_append
.unarchive_var:
	call	ti.ChkFindSym
	jr	c, .not_found
	call	ti.ChkInRam
	jr	z, .save_ptrs
	or	a, a
	sbc	hl, hl
	ex	de, hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ex	de, hl
	call	ti.EnoughMem
	jp	c, util_ret_null_pop_ix
	call	util_unarchive
	jr	.unarchive_var
.no_append:
	call	ti.ChkFindSym
	jr	c, .not_found
	call	ti.ChkInRam
	jr	z, .save_ptrs
	push	hl
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 'r'
	pop	hl
	jp	nz, util_ret_null_pop_ix
	call	util_skip_archive_header
	jr	.save_ptrs
.not_found:
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 'r'
	jp	z, util_ret_null_pop_ix
	or	a, a
	sbc	hl, hl
	ld	a, 0
.smc_type := $-1
	ld	iy, ti.flags
	call	ti.CreateVar
.save_ptrs:
	push	hl
	call	util_get_vat_ptr
	pop	bc
	ld	(hl), bc
	call	util_get_data_ptr
	ld	(hl), de
	ld	bc, 0
	ld	hl, (ix + 9)
	ld	a, 'a'
	cp	a, (hl)
	call	z, util_get_slot_size
	call	util_set_offset
	pop	ix
	xor	a, a
	sbc	hl, hl
	ld	a, (curr_slot)
	ld	l, a
	ret

;-------------------------------------------------------------------------------
ti_SetArchiveStatus:
; sets the archive status of a slot index
; args:
;  sp + 3 : boolean value
;  sp + 6 : slot index
; return:
;  n/a
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	call	util_is_slot_open
	jp	nz, util_ret_null
	ld	a, e
	push	af
	call	util_get_vat_ptr
	ld	hl, (hl)
	ld	a, (hl)
	ld	(ti.OP1), a
	ld	bc, -6
	add	hl, bc
	ld	b, (hl)
	ld	de, ti.OP1 + 1
	dec	hl
.copy_name:
	ld	a, (hl)
	ld	(de), a
	inc	de
	dec	hl
	djnz	.copy_name
	xor	a, a
	ld	(de), a
	pop	af
	or	a, a
	jr	z, .set_unarchived
.set_archived:
	call	util_archive
	jr	.relocate_var
.set_unarchived:
	call	util_unarchive
.relocate_var:
	call	ti.ChkFindSym
	jp	c, util_ret_neg_one
	call	ti.ChkInRam
	jr	z, .save_ptrs
	call	util_skip_archive_header
.save_ptrs:
	push	hl
	call	util_get_vat_ptr
	pop	bc
	ld	(hl), bc
	call	util_get_data_ptr
	ld	(hl), de
	ret

;-------------------------------------------------------------------------------
ti_Write:
; writes a chunk of data into a slot handle
; args:
;  sp + 3 : pointer to data to write
;  sp + 6 : size of chunks in bytes
;  sp + 9 : number of chunks
;  sp + 12 : slot index
; return:
;  hl = number of chunks written if success
	ld	iy, 0
	add	iy, sp
	ld	c,(iy + 12)
	call	util_is_slot_open
	jr	nz, .ret0
	call	util_is_in_ram
	jr	z, .ret0
	ld	bc, (iy + 6)
	ld	hl, (iy + 9)
	call	ti._smulu
	add	hl, de
	xor	a, a
	sbc	hl, de
	ret	z
	ld	(.smc_copy_size), hl
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
	push	hl
	call	util_get_slot_size	; bc = size of file
	pop	hl			; hl = needed size
	or	a, a
	inc	bc
	sbc	hl, bc
	jr	c, .no_core_needed
	inc	hl
	ld	(resize_amount), hl
	call	util_insert_mem
	or	a, a
	jr	z, .ret0
.no_core_needed:
	call	util_get_data_offset
	ex	de, hl
	ld	hl, (iy + 3)
	ld	bc, 0
.smc_copy_size := $-3
	push	bc
	ldir
	call	util_get_offset
	pop	hl
	add	hl,bc
	ex	de,hl
	call	util_get_offset_ptr
	ld	(hl), de
	ld	hl, (iy + 9)
	ret
.ret0:
	xor	a, a
	sbc	hl, hl
	ret

util_get_data_offset:
	call	util_get_data_ptr
	ld	hl, (hl)
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
	inc	hl
	inc	hl
	ret

;-------------------------------------------------------------------------------
ti_Read:
; reads a chunk of data from a slot handle
; args:
;  sp + 3 : pointer to buffer to read into
;  sp + 6 : size of chunks in bytes
;  sp + 9 : number of chunks
;  sp + 12 : slot index
; return:
;  hl = number of chunks read if success
	ld	iy, 0
	add	iy, sp
	ld	c, (iy + 12)
	call	util_is_slot_open
	jr	nz, .ret0
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	or	a, a
	sbc	hl, bc			; size - offset = bytes left to read
	jr	z, .ret0
	jr	c, .ret0
	ld	bc, (iy + 6)
	call	ti._sdivu			; (size - offset) / chunk_size
	ld	de, (iy + 9)		; number of chunks to read, hl = number of chunks left
	or	a, a
	sbc	hl, de
	add	hl, de			; check if left <= read
	jr	nc, .copy
	ex	de, hl
.copy:
	ex	de, hl
	ld	bc, (iy + 6)
	push	hl
	call	ti._smulu
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	z, .ret0.pop
	push	hl
	call	util_get_data_offset
	ld	de, (iy + 3)
	pop	bc
	push	bc
	ldir
	call	util_get_offset
	pop	hl
	add	hl, bc
	ex	de, hl
	call	util_get_offset_ptr
	ld	(hl), de
	pop	hl
	ret				; return actual chunks read
.ret0.pop:
	pop	hl
.ret0:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_GetC:
; gets a single byte character from a slot, advances the offset
; args:
;  sp + 3 : slot index
; return:
;  a = character read if success
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jr	nz, .ret_neg_one
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	scf
	sbc	hl, bc			; size-offset
	jr	c, .ret_neg_one
	push	bc
	call	util_get_data_ptr
	ld	hl, (hl)
	add	hl, bc
	inc	hl
	inc	hl			; bypass size bytes
	pop	bc
	inc	bc
	ld	a, (hl)
	call	util_set_offset
	or	a, a
	sbc	hl, hl
	ld	l, a
	ret
.ret_neg_one:
	scf
	sbc	hl, hl
	ld	a, l
	ret

;-------------------------------------------------------------------------------
ti_PutC:
; Performs an fputc on an AppVar
; args:
;  sp + 3 : Character to place
;  sp + 6 : Slot number
; return:
;  Character written if no failure
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	ld	a, e
	ld	(char_in), a
	call	util_is_slot_open
	jr	nz, .ret_neg_one
	call	util_is_in_ram
	jr	c, .ret_neg_one
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	or	a, a
	sbc	hl, bc
	jr	c, .ret_neg_one
	jr	nz, .no_increment
.increment:
	push	bc
	inc	hl
	ld	(resize_amount), hl
	call	ti.EnoughMem
	pop	bc
	jr	c, .ret_neg_one
	push	bc
	ex	de, hl
	call	util_insert_mem
	pop	bc
	or	a, a
	jr	z, .ret_neg_one
.no_increment:
	call	util_get_data_ptr
	ld	hl, (hl)
	add	hl, bc
	inc	hl
	inc	hl
	ld	a, 0
char_in := $-1
	ld	(hl), a
	inc	bc
	push	af
	call	util_set_offset
	pop	af
	or	a, a
	sbc	hl, hl
	ld	l, a
	ret
.ret_neg_one:
	scf
	sbc	hl, hl
	ld	a, l
	ret

;-------------------------------------------------------------------------------
ti_Seek:
; seeks to a particular offset in an slot index
; args:
;  sp + 3 : positional offset to seek to
;  sp + 6 : origin position
;  sp + 9 : slot index
; return:
;  hl = -1 if failure
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 3)
	ld	c, (iy + 9)
	call	util_is_slot_open
	jr	nz, .ret_neg_one
	ld	a, (iy + 6)		; origin location
	or	a, a
	jr	z, .seek_set
	dec	a
	jr	z, .seek_curr
	dec	a
	jr	nz, .ret_neg_one
.seek_end:
	push	de
	call	util_get_slot_size
.seek_set_asm:
	pop	hl
	add	hl, bc
	ex	de, hl
.seek_set:
	call	util_get_slot_size
	push	bc
	pop	hl
	or	a, a
	sbc	hl, de
	push	de
	pop	bc
	jr	c, .ret_neg_one
	jp	util_set_offset
.seek_curr:
	push	de
	call	util_get_offset
	jr	.seek_set_asm
.ret_neg_one:
	scf
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_DeleteVar:
; deletes an arbitrary variable
; args:
;  sp + 3 : pointer to variable name
;  sp + 6 : variable type
; return:
;  hl = 0 if failure
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	ld	a, c
;	jr	ti_Delete.start		; emulated by dummifying next instruction:
	db	$fe			; ld a,ti.AppVarObj -> cp a,$3E \ dec d
assert ti.AppVarObj = $15

;-------------------------------------------------------------------------------
ti_Delete:
; deletes an appvar
; args:
;  sp + 3 : pointer to appvar name
; return:
;  hl = 0 if failure
	ld	a,ti.AppVarObj
.start:
	pop	de
	pop	hl
	push	hl
	push	de
	dec	hl
	push	af
	call	ti.Mov9ToOP1
	pop	af
	ld	(ti.OP1), a
	call	ti.ChkFindSym
	jp	c, util_ret_null
	ld	iy, ti.flags
	call	ti.DelVarArc
	scf
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_Rewind:
; Performs an frewind on a variable
; args:
;  sp + 3 : Slot number
; return:
;  hl = -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	util_is_slot_open
	jr	nz, .ret_neg_one
.rewind:
	ld	bc, 0
	call	util_set_offset
	or	a, a
	sbc	hl, hl
	ret
.ret_neg_one:
	scf
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_Tell:
; gets the current offset of an open slot index
; args:
;  sp + 3 : slot index
; return:
;  hl = -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	util_is_slot_open
	jr	nz, .ret_neg_one
	call	util_get_offset
	push	bc
	pop	hl
	ret
.ret_neg_one:
	scf
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_GetSize:
; gets the size of an open slot index
; args:
;  sp + 3 : slot index
; return:
;  hl = -1 if failure
	pop	hl
	pop	bc
	push	bc
	push	hl
	call	util_is_slot_open
	jr	nz, .ret_neg_one
	call	util_get_slot_size
	push	bc
	pop	hl
	ret
.ret_neg_one:
	scf
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_Close:
; closes an open slot index
; args:
;  sp + 3 : slot index
; return:
;  n/a
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jq	nz, util_ret_null
	ld	(hl), 255
	ret

;-------------------------------------------------------------------------------
ti_DetectAny:
; finds any variable that starts with some data
; args:
;  sp + 3 : address of pointer to being search
;  sp + 6 : pointer to null terminated string of data to search for
;  sp + 9 : pointer storage of type of variable found
; return:
;  hl -> name of variable
	ld	a,$ff
	jr	ti_Detect.start_flag

;-------------------------------------------------------------------------------
ti_DetectVar:
; finds a variable that starts with some data
; args:
;  sp + 3 : address of pointer to being search
;  sp + 6 : pointer to null terminated string of data to search for
;  sp + 9 : type of variable to search for
; return:
;  hl -> name of variable
	ld	hl,9
	add	hl,sp
	ld	a,(hl)
;	jr	ti_Detect.start		; emulated by dummifying next instruction:
	db	$fe			; ld a,ti.AppVarObj -> cp a,$3E \ dec d
assert ti.AppVarObj = $15

;-------------------------------------------------------------------------------
ti_Detect:
; finds an appvar that starts with some data
;  sp + 3 : address of pointer to being search
;  sp + 6 : pointer to null terminated string of data to search for
; return:
;  hl -> name of variable
	ld	a,ti.AppVarObj
.start:
	ld	(.smc_type), a
	xor	a,a
.start_flag:
	ld	(.smc_flag), a
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	hl, (ix + 9)
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	nz, .detectall		; if null, then detect everything
	ld	hl, .fdetectall
	ld	(ix + 9), hl
.detectall:
	ld	hl, (ix + 6)
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	z, .fstart
	ld	hl, (hl)
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	nz, .fdetect
.fstart:
	ld	hl, (ti.progPtr)
.fdetect:
	ld	de, (ti.pTemp)
	or	a, a
	sbc	hl, de
	jr	c, .finish
	jr	z, .finish
	add	hl, de
	jr	.fcontinue

.finish:
	xor	a, a
	sbc	hl, hl
	pop	ix
	ret

.fcontinue:
	push	hl
	ld	a, 0
.smc_flag := $-1
	or	a, a
	ld	a, (hl)
	jr	z, .fdetectnormal
	ld	de, (ix + 12)
	ld	(de), a
	jr	.fgoodtype
.fdetectnormal:
	cp	a, ti.AppVarObj
.smc_type := $-1
	jr	nz, .fskip
.fgoodtype:
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	dec	hl
	ld	d, (hl)
	dec	hl
	ld	a, (hl)
	call	ti.SetDEUToA
	ex	de,hl
	cp	a, $d0
	jr	nc, .finram
	ld	de, 9
	add	hl, de			; skip archive vat stuff
	ld	e, (hl)
	add	hl, de
	inc	hl
.finram:
	inc	hl
	inc	hl			; hl -> data
	ld	bc, (ix + 9)
.fcmp:
	ld	a, (bc)
	or	a, a
	jr	z, .ffound
	cp	a, (hl)
	inc	bc
	inc	de
	inc	hl
	jr	z, .fcmp		; check the string in memory
.fskip:
	pop	hl
	call	.fbypassname
	jr	.fdetect

.ffound:
	pop	hl
	call	.fbypassname
	ex	de, hl
	ld	hl, (ix + 6)
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	z, .isnull
	ld	(hl), de
.isnull:
	ld	hl, ti.OP6
	pop	ix
	ret

.fbypassname:				; bypass the name in the vat
	ld	de, ti.OP6
	ld	bc, -6
	add	hl, bc
	ld	b, (hl)
	dec	hl
.loop:
	ld	a, (hl)
	ld	(de), a
	dec	hl
	inc	de
	djnz	.loop
	xor	a, a
	ld	(de), a
	ret

.fdetectall:
	dl	0

;-------------------------------------------------------------------------------
ti_GetTokenString:
; return pointer to next token string
; args:
;  sp + 3 : slot index
; return:
;  hl -> os string to display
	ld	iy, 0
	add	iy, sp
	ld	a, 1
	ld	(.smc_length), a
	ld	hl, (iy + 3)
	ld	hl, (hl)
	push	hl
	ld	a, (hl)
	call	ti.Isa2ByteTok
	ex	de, hl
	jr	nz, .not2byte
	inc	de
	ld	hl, .smc_length
	inc	(hl)
.not2byte:
	inc	de
	ld	hl, (iy + 3)
	ld	(hl), de
	pop	hl
	push	iy
	ld	iy, ti.flags
	call	ti.Get_Tok_Strng
	pop	iy
	ld	hl, (iy + 9)
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	z, .skip
	ld	(hl), bc
.skip:
	ld	hl, (iy + 6)
	add	hl, bc
	or	a, a
	sbc	hl ,bc
	jr	z, .skipstore
	ld	(hl), 1
.smc_length := $-1
.skipstore:
	ld	hl, ti.OP3
	ret

;-------------------------------------------------------------------------------
ti_GetDataPtr:
; return a pointer to the current location in the given variable
; args:
;  sp + 3 : slot index
; return:
;  hl -> current offset data
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jr	nz, .ret_null
	call	util_get_slot_size
	inc	hl
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
	ret
.ret_null:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_GetVATPtr:
; return a pointer to the vat location in the given variable
; args:
;  sp + 3 : slot index
; return:
;  hl -> vat location of variable
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jr	nz, .ret_null
	call	util_get_vat_ptr
	ld	hl, (hl)
	ret
.ret_null:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_GetName:
; gets the variable name of an open slot index
; args:
;  sp + 3 : name buffer
;  sp + 6 : slot index
; return:
;  n/a
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	call	util_is_slot_open
	ret	nz
	call	util_get_vat_ptr
	ld	hl, (hl)
	ld	bc, -6
	add	hl, bc
	ld	b, (hl)			; length of name
	dec	hl
.copy:
	ld	a, (hl)
	ld	(de), a
	inc	de
	dec	hl
	djnz	.copy
	xor	a, a
	ld	(de), a			; terminate the string
	ret

;-------------------------------------------------------------------------------
ti_RenameVar:
; renames a variable with a new name
; args:
;  sp + 3 : old name pointer
;  sp + 6 : new name pointer
;  sp + 9 : variable type
; return:
;  a = 0 if success
;  a = 1 if new file already exists
;  a = 2 if old file does not exist
;  a = 3 if other error
	ld	iy, 0
	add	iy, sp
	ld	a, (iy + 9)
	ld	iy, ti.flags		; probably not needed
;	jr	ti_Rename.start		; emulated by dummifying next instruction
	db	$fe			; ld a,appVarObj -> cp a,$3E \ dec d

;-------------------------------------------------------------------------------
ti_Rename:
; renames an appvar with a new name
; args:
;  sp + 3 : old name pointer
;  sp + 6 : new name pointer
; return:
;  a = 0 if success
;  a = 1 if new file already exists
;  a = 2 if old file does not exist
;  a = 3 if other error
	ld	a,ti.AppVarObj		; file type
.start:
	pop	bc
	pop	hl
	pop	de
	push	de			; de -> new name
	push	hl			; hl -> old name
	push	bc
	push	de			; new
	push	de			; new
	ld	de, ti.OP1
	ld	(de), a
	inc	de
	call	ti.Mov8b
	call	ti.PushOP1		; save old name
	ld	hl, util_archive
	ld	(.smc_archive), hl
	pop	hl			; new name
	ld	de, ti.OP1 + 1
	call	ti.Mov8b
	call	ti.ChkFindSym
	push	af
	call	ti.PopOP1
	pop	af
	jr	nc, .return_1		; check if name already exists
.locate_program:
	call	ti.ChkFindSym		; find old name
	jr	c, .return_2
	call	ti.ChkInRam
	jr	nz, .in_archive
	ld	hl, util_no_op		; no-op routine
	ld	(.smc_archive), hl
	call	ti.PushOP1
	call	util_archive
	call	ti.PopOP1
	jr	.locate_program
.in_archive:
	ex	de, hl
	ld	de, 9
	add	hl, de			; skip vat stuff
	ld	e, (hl)
	add	hl, de
	inc	hl			; size of name
	call	ti.LoadDEInd_s
	pop	bc			; bc -> new name
	push	hl
	push	de
	push	bc
	call	ti.PushOP1		; old name
	pop	hl
	ld	de, ti.OP1 + 1
	call	ti.Mov8b
	call	ti.PushOP1		; new name
	pop	hl
	push	hl
	ld	a, (ti.OP1)
	call	ti.CreateVar
	inc	de
	inc	de
	pop	bc
	pop	hl
	call	ti.ChkBCIs0
	jr	z, .is_zero
	ldir
.is_zero:
	call	ti.PopOP1
	call	0
.smc_archive := $-3
	call	ti.PopOP1
	call	ti.ChkFindSym
	call	ti.DelVarArc
	xor	a, a
	ret
.return_1:
	pop	de			; new name
	ld	a, 1
	ret
.return_2:
	pop	de			; new name
	ld	a, 2
	ret

;-------------------------------------------------------------------------------
ti_SetVar:
; sets an os variable structure value
; args:
;  sp + 3 : type of variable to set
;  sp + 6 : pointer to name of variable
;  sp + 9 : pointer to data to set
; return:
;  a = any error code, 0 if success
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	hl, (ix + 9)		; pointer to data
	ld	a, (ix + 6)
	call	util_set_var_str
	call	ti.ChkFindSym
	call	nc, ti.DelVarArc
	ld	a, (ix + 6)
	ld	hl, (ix + 12)
	and	a, $3f
	call	ti.DataSize
	pop	ix
	push	hl
	ex	de, hl
	dec	hl
	dec	hl
	call	ti.CreateVar
	inc	bc
	inc	bc
	pop	hl
	ldir
	xor	a, a
	ret

;-------------------------------------------------------------------------------
ti_StoVar:
; stores an os variable to a variable data structure
; args:
;  sp + 3 : type of variable to store to
;  sp + 6 : pointer to data to store to
;  sp + 9 : type of variable to get from
;  sp + 12 : pointer to data to get from
; return:
;  a = any error code, 0 if success
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 12)		; pointer to data
	call	util_set_var_str
	ld	a, (iy + 9)
	or	a, a			; if real look up the variable
	jr	z, .iscr
	cp	a, $0c			; if cplx look up the variable
	jr	nz, .notcr
.iscr:
	call	ti.FindSym
	jp	c, .notcr		; fill it with zeros
	and	a, $3f
	ex	de, hl
	call	ti.Mov9OP1OP2
.notcr:
	call	ti.PushOP1
	ld	hl, (iy + 6)		; pointer to var string
	ld	a, (iy + 3)
	call	util_set_var_str
	ld	iy, ti.flags
	ld	hl, util_ret_neg_one_byte
	call	ti.PushErrorHandler
	call	ti.StoOther
	call	ti.PopErrorHandler
	xor	a, a
	ret

;-------------------------------------------------------------------------------
ti_RclVar:
; gets a pointer to a variable data structure
; args:
;  sp + 3 : pointer to variable name string
;  sp + 6 : pointer to data structure pointer
; return:
;  a = type of variable
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)		; pointer to data
	ld	a, (iy + 3)		; var type
	ld	iy,ti.flags
	call	util_set_var_str
	call	ti.FindSym
	jr	c, .ret_neg_one
	push	af
	call	ti.ChkInRam
	pop	bc
	ld	a, b
	jr	nz, .ret_neg_one
	ld	iy, 0
	add	iy, sp
	and	a, $3f
	sub	a, (iy + 3)		; var type
	jr	nz, .ret_neg_one
	ld	hl, (iy + 9)
	ld	(hl), de
	ret
.ret_neg_one:
	ld	a,-1
	ret

;-------------------------------------------------------------------------------
ti_ArchiveHasRoom:
; checks if there is room in the archive without triggering a garbage collect.
; args:
;  sp + 3 : number of bytes to store into the archive
; return:
;  true if there is room, false if not
	pop	de
	pop	bc
	push	bc
	push	de
	cp	a, a			; set z flag
	ld	hl, $FF0000
	add	hl, bc
	call	nc, ti.FindFreeArcSpot
	ld	a, 1
	ret	nz
	xor	a, a
	ret

;-------------------------------------------------------------------------------
ti_ArchiveHasRoomVar:
; checks if there is room in the archive without triggering a garbage collect.
; args:
;  sp + 3 : handle to variable
; return:
;  true if there is room, false if not
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jr	nz,.fail
	call	util_get_vat_ptr
	ld	hl,(hl)
	ld	bc,-6
	add	hl,bc
	ld	c,(hl)			; get var name length
	call	util_get_data_ptr
	ld	de,(hl)
.entry_sym:
	ld	a,c
	ex	de,hl
	ld	hl,(hl)
	ld	bc,12
	add	a,c
	ld	c,a
	add.s	hl,bc
	jr	c,.fail
	ld	c,l
	ld	b,h
	call	ti.FindFreeArcSpot
	ld	a,1
	ret	nz
.fail:
	xor	a,a
	ret

;-------------------------------------------------------------------------------
ti_SetGCBehavior:
;Set routines to run before and after a garbage collect would be triggered.
; args:
;   sp + 3 : pointer to routine to be run before. Set to 0 to use default handler.
;	sp + 6 : pointer to routine to be run after. Set to 0 to use default handler.
; return:
;   None
	pop	de
	pop	bc
	ex	(sp),hl
	push	bc
	push	de
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	nz,.notdefault1
	ld	hl,util_post_gc_default_handler
.notdefault1:
	ld	(util_post_gc_handler),hl
	sbc	hl,hl
	adc	hl,bc
	jr	nz,.notdefault2
	ld	hl,util_pre_gc_default_handler
.notdefault2:
	ld	(util_pre_gc_handler),hl
	ret
util_post_gc_default_handler := util_no_op
util_pre_gc_default_handler := util_no_op

;-------------------------------------------------------------------------------
; internal library routines
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
util_skip_archive_header:
; in:
;  hl -> start of archived vat entry
; out:
;  hl -> actual variable data
	ex	de, hl
	ld	bc, 9
	add	hl, bc
	ld	c, (hl)
	inc	hl
	add	hl, bc
	ex	de, hl
util_no_op:
	ret

;-------------------------------------------------------------------------------
util_set_var_str:
; in:
;  hl -> string
;  a = type
; out:
;  OP1 = variable combo
	ld	de, ti.OP1
	and	a, $3f
	ld	(de), a
	inc	de
	jp	ti.Mov8b

;-------------------------------------------------------------------------------
util_insert_mem:
	call	util_get_data_ptr
	push	hl
	ld	hl, (hl)
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
	inc	hl			; bypass size bytes
	inc	hl
	ex	de, hl
	ld	hl, (resize_amount)
	push	hl
	push	de
	call	ti.EnoughMem
	pop	de
	pop	hl
	jr	nc, .enough_mem
	pop	hl
	xor	a, a
	ret
.enough_mem:
	call	ti.InsertMem
	pop	hl
	ld	hl, (hl)
	push	hl
	ld	de, 0
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ex	de, hl
	ld	bc, (resize_amount)
	add	hl, bc			; increase by 5
	jr	util_save_size
util_delete_mem:
	call	util_get_data_ptr
	push	hl
	ld	hl, (hl)
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
	inc	hl
	inc	hl
	ld	de, (resize_amount)
	call	ti.DelMem
	pop	hl
	ld	hl, (hl)
	push	hl
	ld	de, 0
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ex	de, hl
	ld	bc, (resize_amount)
	or	a, a
	sbc	hl, bc			; decrease amount
util_save_size:
	ex	de, hl
	pop	hl			; pointer to size bytes location
	ld	(hl), e
	inc	hl
	ld	(hl), d			; write new size
util_ret_neg_one_byte:
	ld	a, 255
	ret

util_ret_null_pop_ix:
	pop	ix
util_ret_null:
	xor	a, a
	sbc	hl, hl
	ret
util_ret_neg_one:
	scf
	sbc	hl, hl
	ret

util_is_slot_open:
; in:
;  c = slot
; out:
;  a = 0
;  ubc = slot * 3
;  uhl = pointer to upper byte of slot offset
;  zf = open
;  (curr_slot) = slot
	ld	a, c
	cp	a, 6
	jr	nc, .not_open
	ld	(curr_slot), a
	ld	b, 3
	mlt	bc
	ld	hl, variable_offsets - 1
	add	hl, bc
	ld	a, b
	cp	a, (hl)
	ret
.not_open:
	xor	a, a
	inc	a
	ret

util_get_vat_ptr:
	ld	a, (curr_slot)
	ld	hl, vat_ptr0 		; vat_ptr0 = $d0244e
	dec	a
	ret	z
	inc	h
	ld	l, $7b			; vat_ptr1 = $d0257b
	dec	a
	ret	z
	ld	l, $7e			; vat_ptr2 = $d0257e
	dec	a
	ret	z
	ld	l, $81			; vat_ptr3 = $d02581
	dec	a
	ret	z
	ld	l, $84			; vat_ptr4 = $d02584
	ret
util_get_data_ptr:
	ld	a, (curr_slot)
	ld	hl, data_ptr0		; data_ptr0 = $d0067e
	dec	a
	ret	z
	ld	l, $81			; data_ptr1 = $d00681
	dec	a
	ret	z
	ld	hl, data_ptr2		; data_ptr2 = $d01fed
	dec	a
	ret	z
	ld	l, $f3			; data_ptr3 = $d01ff3
	dec	a
	ret	z
	ld	l, $f9			; data_ptr4 = $d01ff9
	ret
util_get_offset_ptr:
	push	bc
	ld	hl, (curr_slot)
	ld	h, 3
	mlt	hl
	ld	bc, variable_offsets - 3
	add	hl, bc
	pop	bc
	ret
util_get_slot_size:
	call	util_get_data_ptr
	ld	hl, (hl)
	ld	bc, 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ret
util_get_offset:
	call	util_get_offset_ptr
	ld	bc, (hl)
	ret
util_set_offset:
	call	util_get_offset_ptr
	ld	(hl), bc
	ret

util_archive:				; properly handle garbage collects
	ld	iy, ti.flags
	call	ti.ChkFindSym
	call	ti.ChkInRam
	ret	nz
	call	ti.PushOP1
	call	ti_ArchiveHasRoomVar.entry_sym
	jr	z,.handle_gc
	call	ti.Arc_Unarc
	jp	ti.PopOP1
.handle_gc:
	call	util_pre_gc_default_handler
util_pre_gc_handler := $-3
	ld	iy, ti.flags
	call	ti.PopOP1
	call	ti.PushOP1
	call	ti.Arc_Unarc
	call	util_post_gc_default_handler
util_post_gc_handler := $-3
	ld	iy, ti.flags
	jp	ti.PopOP1

util_unarchive:
	ld	iy, ti.flags
	call	ti.PushOP1
	call	ti.ChkFindSym
	call	ti.ChkInRam
	call	nz,ti.Arc_Unarc
	jp	ti.PopOP1

;-------------------------------------------------------------------------------
; Internal library data
;-------------------------------------------------------------------------------

	db	255			; handle edge case of 0 for slot
variable_offsets:
	dl	-1, -1, -1, -1, -1
