;-------------------------------------------------------------------------------
.include "library.inc"
;-------------------------------------------------------------------------------

library FILEIOC, 8

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	lib_export ti_CloseAll
	lib_export ti_Open
	lib_export ti_OpenVar
	lib_export ti_Close
	lib_export ti_Write
	lib_export ti_Read
	lib_export ti_GetC
	lib_export ti_PutC
	lib_export ti_Delete
	lib_export ti_DeleteVar
	lib_export ti_Seek
	lib_export ti_Resize
	lib_export ti_IsArchived
	lib_export ti_SetArchiveStatus
	lib_export ti_Tell
	lib_export ti_Rewind
	lib_export ti_GetSize
;-------------------------------------------------------------------------------
; v2 functions
;-------------------------------------------------------------------------------
	lib_export ti_GetTokenString
	lib_export ti_GetDataPtr
	lib_export ti_Detect
	lib_export ti_DetectVar
;-------------------------------------------------------------------------------
; v3 functions
;-------------------------------------------------------------------------------
	lib_export ti_SetVar
	lib_export ti_StoVar
	lib_export ti_RclVar
	lib_export ti_AllocString
	lib_export ti_AllocList
	lib_export ti_AllocMatrix
	lib_export ti_AllocCplxList
	lib_export ti_AllocEqu
;-------------------------------------------------------------------------------
; v4 functions
;-------------------------------------------------------------------------------
	lib_export ti_DetectAny
	lib_export ti_GetVATPtr
	lib_export ti_GetName
	lib_export ti_Rename
	lib_export ti_RenameVar
;-------------------------------------------------------------------------------
; v5 functions
;-------------------------------------------------------------------------------
	lib_export ti_ArchiveHasRoom
;-------------------------------------------------------------------------------
; v6 functions
;-------------------------------------------------------------------------------
	lib_export ti_SetGCBehavior
;-------------------------------------------------------------------------------
; v7 functions
;-------------------------------------------------------------------------------
; No new functions, but a change was made to slot openness managemnent such that
; it is no longer necessary to call `ti_CloseAll` in initialization. New
; programs omitting this initialization require this change.
;-------------------------------------------------------------------------------
; v8 functions
;-------------------------------------------------------------------------------
	lib_export ti_ArchiveHasRoomVar

;-------------------------------------------------------------------------------
.equ vat_ptr0, 0xd0244e
.equ vat_ptr1, 0xd0257b
.equ vat_ptr2, 0xd0257e
.equ vat_ptr3, 0xd02581
.equ vat_ptr4, 0xd02584
.equ data_ptr0, 0xd0067e
.equ data_ptr1, 0xd00681
.equ data_ptr2, 0xd01fed
.equ data_ptr3, 0xd01ff3
.equ data_ptr4, 0xd01ff9
.equ resize_amount, 0xe30c0c
.equ curr_slot, 0xe30c11
.equ TI_MAX_SIZE, 65505
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
	push	hl
	jr	util_alloc_string_equ

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
	ld	iy, 3
	add	iy, sp
	ld	h, (iy + 0)
	ld	l, (iy + 3)
	push	hl
	mlt	hl
util_alloc_var:
	call	ti.HLTimes9
util_alloc_string_equ:
	ld	iy, (iy + 6)
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
	or	a, a
	sbc	hl, de
	add	hl, de
	push	af
	push	hl
	call	ti_Rewind.rewind	; rewind file offset
	pop	hl
	pop	af
	jp	nc, util_ret_null	; return if too big
	push	hl
	call	util_get_slot_size
	pop	hl
	or	a, a
	sbc	hl, bc
	ld	(resize_amount), hl
	jr	z, ti_Resize.no_resize
	jr	c, ti_Resize.decrease
ti_Resize.increase:
	call	ti.EnoughMem
	jp	c, util_ret_null
	ex	de, hl
	call	util_insert_mem
	jr	ti_Resize.no_resize
ti_Resize.decrease:
	push	hl
	pop	bc
	or	a, a
	sbc	hl, hl
	sbc	hl, bc
	ld	(resize_amount), hl
	call	util_delete_mem
ti_Resize.no_resize:
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
	cp	a, 0xd0
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
	ld	hl, 9
	add	hl, sp
	ld	a, (hl)			; (sp + 9)
;	jr	ti_Open.start		; emulated by dummifying next instruction
	.db	0xfe			; ld a, ti.AppVarObj -> cp a, $3e \ dec d
assert (ti.AppVarObj == 0x15)

;-------------------------------------------------------------------------------
ti_Open:
; opens an appvar, acting as a file handle
; args:
;  sp + 3 : pointer to appvar name
;  sp + 6 : open flags
; return:
;  a = slot index if no error
	ld	a, ti.AppVarObj
ti_Open.start:
	ld	(ti_Open.smc_type), a
	ld	(ti.OP1), a
	ld	iy, ti.flags

	ld	hl, variable_offsets + (5 * 3) - 1
	ld	a, 5
ti_Open.find_slot:
; slot open (in use): upper byte of offset == 0
; slot closed (free): upper byte of offset > slot
	cp	a, (hl)
	jr	c, ti_Open.slot
	dec	hl
	dec	hl
	dec	hl
	dec	a
	jr	nz, ti_Open.find_slot
	ret

ti_Open.slot:
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
	cp	a, 0x77
	ld	iy, ti.flags
	jr	nz, ti_Open.no_overwite
	call	ti.PushOP1
	call	ti.ChkFindSym
	call	nc, ti.DelVarArc
	call	ti.PopOP1
ti_Open.no_overwite:
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 0x72
	jr	z, ti_Open.mode
	cp	a, 0x61
	jr	z, ti_Open.mode
	cp	a, 0x77
	jr	nz, ti_Open.ret_null_pop_ix
ti_Open.mode:
	inc	hl
	ld	a, (hl)
	cp	a, 0x2b
	jr	nz, ti_Open.no_append
ti_Open.unarchive_var:
	call	ti.ChkFindSym
	jr	c, ti_Open.not_found
	call	ti.ChkInRam
	jr	z, ti_Open.save_ptrs
	ex	de, hl
	inc.s	de			; clear UDE
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ex	de, hl
	call	ti.EnoughMem
	jr	c, ti_Open.ret_null_pop_ix
	call	util_unarchive
	jr	ti_Open.unarchive_var

ti_Open.ret_null_pop_ix:
	pop	ix
	xor	a, a
	sbc	hl, hl
	ret

ti_Open.no_append:
	call	ti.ChkFindSym
	jr	c, ti_Open.not_found
	call	ti.ChkInRam
	jr	z, ti_Open.save_ptrs
	push	hl
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 0x72
	pop	hl
	jr	nz, ti_Open.ret_null_pop_ix
	call	util_skip_archive_header
	jr	ti_Open.save_ptrs
ti_Open.not_found:
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 0x72
	jr	z, ti_Open.ret_null_pop_ix
	or	a, a
	sbc	hl, hl
	ld	a, 0
.equ ti_Open.smc_type, .-1
	ld	iy, ti.flags
	call	ti.CreateVar
ti_Open.save_ptrs:
	push	hl
	call	util_get_vat_ptr
	pop	bc
	ld	(hl), bc
	call	util_get_data_ptr
	ld	(hl), de
	ld	bc, 0
	ld	hl, (ix + 9)
	ld	a, 0x61
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
;  hl = 0 if failure
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
ti_SetArchiveStatus.copy_name:
	ld	a, (hl)
	ld	(de), a
	inc	de
	dec	hl
	djnz	ti_SetArchiveStatus.copy_name
	xor	a, a
	ld	(de), a
	pop	af
	or	a, a
	jr	z, ti_SetArchiveStatus.set_unarchived
ti_SetArchiveStatus.set_archived:
	call	util_archive
	jr	ti_SetArchiveStatus.relocate_var
ti_SetArchiveStatus.set_unarchived:
	call	util_unarchive
ti_SetArchiveStatus.relocate_var:
	call	ti.ChkFindSym
	jp	c, util_ret_neg_one
	call	ti.ChkInRam
	; jr	z, .save_ptrs
	call	nz, util_skip_archive_header
ti_SetArchiveStatus.save_ptrs:
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
	ld	c, (iy + 12)
	call	util_is_slot_open
	jr	nz, ti_Write.ret0
	call	util_is_in_ram
	jr	z, ti_Write.ret0
	ld	bc, (iy + 6)
	ld	hl, (iy + 9)
	call	ti._smulu
	add	hl, de
	xor	a, a
	sbc	hl, de
	ret	z
	ld	(ti_Write.smc_copy_size), hl
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
	jr	c, ti_Write.no_core_needed
	inc	hl
	ld	(resize_amount), hl
	call	util_insert_mem
	or	a, a
	jr	z, ti_Write.ret0
ti_Write.no_core_needed:
	call	util_get_data_offset
	ex	de, hl
	ld	hl, (iy + 3)
	ld	bc, 0
.equ ti_Write.smc_copy_size, .-3
	push	bc
	ldir
	call	util_get_offset
	pop	hl
	add	hl, bc
	ex	de, hl
	call	util_get_offset_ptr
	ld	(hl), de
	ld	hl, (iy + 9)
	ret
ti_Write.ret0:
util_ret_null:
	xor	a, a
	sbc	hl, hl
	ret

util_get_data_offset:
; output:
;  HL = data_ptr + offset + 2
;  BC = offset
; destroyed:
;  A
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
	jr	nz, ti_Read.ret0
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	xor	a, a
	sbc	hl, bc			; size - offset = bytes left to read
	ret	z			; jr z, .ret0
	jr	c, ti_Read.ret0
	ld	bc, (iy + 6)
	call	ti._sdivu			; (size - offset) / chunk_size
	ld	de, (iy + 9)		; number of chunks to read, hl = number of chunks left
	or	a, a
	sbc	hl, de
	add	hl, de			; check if left <= read
	jr	c, ti_Read.no_copy
	ex	de, hl
ti_Read.no_copy:
	ld	bc, (iy + 6)
	push	hl
	call	ti._smulu
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	z, ti_Read.ret0.pop
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
ti_Read.ret0.pop:
	pop	hl
ti_Read.ret0:
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
	jr	nz, ti_GetC.ret_neg_one
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	scf
	sbc	hl, bc			; size-offset
	jr	c, ti_GetC.ret_neg_one
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
ti_GetC.ret_neg_one:
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
	jr	nz, ti_PutC.ret_neg_one
	call	util_is_in_ram
	jr	c, ti_PutC.ret_neg_one
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	or	a, a
	sbc	hl, bc
	jr	c, ti_PutC.ret_neg_one
	jr	nz, ti_PutC.no_increment
ti_PutC.increment:
	push	bc
	inc	hl
	ld	(resize_amount), hl
	call	ti.EnoughMem
	pop	bc
	jr	c, ti_PutC.ret_neg_one
	push	bc
	ex	de, hl
	call	util_insert_mem
	pop	bc
	or	a, a
	jr	z, ti_PutC.ret_neg_one
ti_PutC.no_increment:
	call	util_get_data_ptr
	ld	hl, (hl)
	add	hl, bc
	inc	hl
	inc	hl
	ld	a, 0
.equ char_in, .-1
	ld	(hl), a
	inc	bc
	push	af
	call	util_set_offset
	pop	af
	or	a, a
	sbc	hl, hl
	ld	l, a
	ret
ti_PutC.ret_neg_one:
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
	jr	nz, ti_Seek.ret_neg_one
	ld	a, (iy + 6)		; origin location
	or	a, a
	jr	z, ti_Seek.seek_set
	dec	a
	jr	z, ti_Seek.seek_curr
	dec	a
	jr	nz, ti_Seek.ret_neg_one
ti_Seek.seek_end:
	push	de
	call	util_get_slot_size
ti_Seek.seek_set_asm:
	pop	hl
	add	hl, bc
	ex	de, hl
ti_Seek.seek_set:
	call	util_get_slot_size
	push	bc
	pop	hl
	or	a, a
	sbc	hl, de
	push	de
	pop	bc
	jr	c, ti_Seek.ret_neg_one
	; jp	util_set_offset
ti_Seek.util_set_offset:
; input:
;  BC = offset
; output:
;  HL = offset_ptr
	call	util_get_offset_ptr
	ld	(hl), bc
	ret

ti_Seek.seek_curr:
	push	de
	call	util_get_offset
	jr	ti_Seek.seek_set_asm
ti_Seek.ret_neg_one:
	scf
	sbc	hl, hl
	ret

.equ util_set_offset, ti_Seek.util_set_offset

;-------------------------------------------------------------------------------
ti_DeleteVar:
; deletes an arbitrary variable
; args:
;  sp + 3 : pointer to variable name
;  sp + 6 : variable type
; return:
;  hl = 0 if failure
	ld	hl, 6
	add	hl, sp
	ld	a, (hl)
;	jr	ti_Delete.start		; emulated by dummifying next instruction:
	.db	0xfe			; ld a, ti.AppVarObj -> cp a, $3E \ dec d
assert (ti.AppVarObj == 0x15)

;-------------------------------------------------------------------------------
ti_Delete:
; deletes an appvar
; args:
;  sp + 3 : pointer to appvar name
; return:
;  hl = 0 if failure
	ld	a, ti.AppVarObj
ti_Delete.start:
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
util_ret_neg_one:
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
	jr	nz, ti_Rewind.ret_neg_one
ti_Rewind.rewind:
	ld	bc, 0
	call	util_set_offset
	or	a, a
	sbc	hl, hl
	ret
ti_Rewind.ret_neg_one:
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
	jr	nz, ti_Tell.ret_neg_one
	call	util_get_offset
	push	bc
	pop	hl
	ret
ti_Tell.ret_neg_one:
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
	jr	nz, ti_GetSize.ret_neg_one
	call	util_get_slot_size
	push	bc
	pop	hl
	ret
ti_GetSize.ret_neg_one:
	scf
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
ti_Close:
; closes an open slot index
; args:
;  sp + 3 : slot index
; return:
;  hl = 0 if failure
	pop	de
	pop	bc
	push	bc
	push	de
	call	util_is_slot_open
	jp	nz, util_ret_null
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
	ld	a, 0xff
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
	ld	hl, 9
	add	hl, sp
	ld	a, (hl)			; (sp + 9)
;	jr	ti_Detect.start		; emulated by dummifying next instruction:
	.db	0xfe			; ld a, ti.AppVarObj -> cp a, $3E \ dec d
assert (ti.AppVarObj == 0x15)

;-------------------------------------------------------------------------------
ti_Detect:
; finds an appvar that starts with some data
;  sp + 3 : address of pointer to being search
;  sp + 6 : pointer to null terminated string of data to search for
; return:
;  hl -> name of variable
	ld	a, ti.AppVarObj
ti_Detect.start:
	ld	(ti_Detect.smc_type), a
	xor	a, a
ti_Detect.start_flag:
	ld	(ti_Detect.smc_flag), a
	push	ix
	ld	ix, 0
	lea	bc, ix + 0
	add	ix, sp
	ld	hl, (ix + 9)
	adc	hl, bc
	jr	nz, ti_Detect.detectall		; if null, then detect everything
	ld	hl, ti_Detect.fdetectall
	ld	(ix + 9), hl
ti_Detect.detectall:
	ld	hl, (ix + 6)
	adc	hl, bc
	jr	z, ti_Detect.fstart
	ld	hl, (hl)
	adc	hl, bc
	jr	nz, ti_Detect.fdetect
ti_Detect.fstart:
	ld	hl, (ti.progPtr)
ti_Detect.fdetect:
	ld	de, (ti.pTemp)
	or	a, a
	sbc	hl, de
	jr	c, ti_Detect.finish
	jr	z, ti_Detect.finish
	add	hl, de
ti_Detect.fcontinue:
	push	hl
	ld	a, 0
.equ ti_Detect.smc_flag, .-1
	or	a, a
	ld	a, (hl)
	jr	z, ti_Detect.fdetectnormal
	ld	de, (ix + 12)
	ld	(de), a
	jr	ti_Detect.fgoodtype

ti_Detect.finish:
	xor	a, a
	sbc	hl, hl
	pop	ix
	ret

ti_Detect.fdetectnormal:
	cp	a, ti.AppVarObj
.equ ti_Detect.smc_type, .-1
	jr	nz, ti_Detect.fskip
ti_Detect.fgoodtype:
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	dec	hl
	ld	d, (hl)
	dec	hl
	ld	a, (hl)
	call	ti.SetDEUToA
	ex	de, hl
	cp	a, 0xd0
	jr	nc, ti_Detect.finram
	ld	de, 9
	add	hl, de			; skip archive vat stuff
	ld	e, (hl)
	add	hl, de
	inc	hl
ti_Detect.finram:
	inc	hl
	inc	hl			; hl -> data
	ld	bc, (ix + 9)
ti_Detect.fcmp:
	ld	a, (bc)
	or	a, a
	jr	z, ti_Detect.ffound
	cp	a, (hl)
	inc	bc
	inc	de
	inc	hl
	jr	z, ti_Detect.fcmp	; check the string in memory
ti_Detect.fskip:
	pop	hl
	call	ti_Detect.fbypassname
	jr	ti_Detect.fdetect

ti_Detect.ffound:
	pop	hl
	call	ti_Detect.fbypassname
	ex	de, hl
	ld	hl, (ix + 6)
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	z, ti_Detect.isnull
	ld	(hl), de
ti_Detect.isnull:
	ld	hl, ti.OP6
	pop	ix
	ret

ti_Detect.fbypassname:				; bypass the name in the vat
	ld	de, ti.OP6
	ld	bc, -6
	add	hl, bc
	ld	b, (hl)
	dec	hl
ti_Detect.loop:
	ld	a, (hl)
	ld	(de), a
	dec	hl
	inc	de
	djnz	ti_Detect.loop
	xor	a, a
	ld	(de), a
	ret

ti_Detect.fdetectall:
	.d24	0

;-------------------------------------------------------------------------------
ti_GetTokenString:
; return pointer to next token string
; args:
;  sp + 3 : pointer to token string
;  sp + 6 : pointer token length
;  sp + 9 : pointer to string length
; return:
;  hl -> os string to display
	ld	iy, 0
	add	iy, sp
	ld	a, 1
	ld	(ti_GetTokenString.smc_length), a
	ld	hl, (iy + 3)
	ld	hl, (hl)
	push	hl
	ld	a, (hl)
	call	ti.Isa2ByteTok
	ex	de, hl
	jr	nz, ti_GetTokenString.not2byte
	inc	de
	ld	hl, ti_GetTokenString.smc_length
	inc	(hl)
ti_GetTokenString.not2byte:
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
	jr	z, ti_GetTokenString.skip
	ld	(hl), bc
ti_GetTokenString.skip:
	ld	hl, (iy + 6)
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	z, ti_GetTokenString.skipstore
	ld	(hl), 1
.equ ti_GetTokenString.smc_length, .-1
ti_GetTokenString.skipstore:
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
	jr	nz, ti_GetDataPtr.ret_null
	call	util_get_slot_size
	inc	hl
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
	ret
ti_GetDataPtr.ret_null:
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
	jr	nz, ti_GetVATPtr.ret_null
	call	util_get_vat_ptr
	ld	hl, (hl)
	ret
ti_GetVATPtr.ret_null:
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
ti_GetName.copy:
	ld	a, (hl)
	ld	(de), a
	inc	de
	dec	hl
	djnz	ti_GetName.copy
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
	ld	hl, 9
	add	hl, sp
	ld	a, (hl)			; (sp + 9)
	ld	iy, ti.flags		; probably not needed
;	jr	ti_Rename.start		; emulated by dummifying next instruction
	.db	0xfe			; ld a, appVarObj -> cp a, $3E \ dec d

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
	ld	a, ti.AppVarObj		; file type
ti_Rename.start:
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
	ld	(ti_Rename.smc_archive), hl
	pop	hl			; new name
	ld	de, ti.OP1 + 1
	call	ti.Mov8b
	call	ti.ChkFindSym
	push	af
	call	ti.PopOP1
	pop	af
	jr	nc, ti_Rename.return_1		; check if name already exists
ti_Rename.locate_program:
	call	ti.ChkFindSym		; find old name
	jr	c, ti_Rename.return_2
	call	ti.ChkInRam
	jr	nz, ti_Rename.in_archive
	ld	hl, util_no_op		; no-op routine
	ld	(ti_Rename.smc_archive), hl
	call	ti.PushOP1
	call	util_archive
	call	ti.PopOP1
	jr	ti_Rename.locate_program
ti_Rename.in_archive:
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
	jr	z, ti_Rename.is_zero
	ldir
ti_Rename.is_zero:
	call	ti.PopOP1
	call	0
.equ ti_Rename.smc_archive, .-3
	call	ti.PopOP1
	call	ti.ChkFindSym
	call	ti.DelVarArc
	xor	a, a
	ret
ti_Rename.return_1:
	pop	de			; new name
	ld	a, 1
	ret
ti_Rename.return_2:
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
	and	a, 0x3f
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
	jr	z, ti_StoVar.iscr
	cp	a, 0x0c			; if cplx look up the variable
	jr	nz, ti_StoVar.notcr
ti_StoVar.iscr:
	call	ti.FindSym
	jr	c, ti_StoVar.notcr	; fill it with zeros
	and	a, 0x3f
	ex	de, hl
	call	ti.Mov9OP1OP2
ti_StoVar.notcr:
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
;  sp + 3 : variable type
;  sp + 6 : pointer to variable name string
;  sp + 9 : pointer to data structure pointer
; return:
;  a = type of variable
	ld	hl, 3
	add	hl, sp
	ld	a, (hl)			; (sp + 3) var type
	inc	hl
	inc	hl
	inc	hl
	ld	hl, (hl)		; (sp + 6) pointer to data
	ld	iy, ti.flags
	call	util_set_var_str
	call	ti.FindSym
	jr	c, ti_RclVar.ret_neg_one
	push	af
	call	ti.ChkInRam
	pop	bc
	ld	a, b
	jr	nz, ti_RclVar.ret_neg_one
	ld	iy, 0
	add	iy, sp
	and	a, 0x3f
	sub	a, (iy + 3)		; var type
	jr	nz, ti_RclVar.ret_neg_one
	ld	hl, (iy + 9)
	ld	(hl), de
	ret
ti_RclVar.ret_neg_one:
	ld	a, -1
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
	ld	hl, 0xFF0000
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
	jr	nz, ti_ArchiveHasRoomVar.fail
	call	util_get_vat_ptr
	ld	hl, (hl)
	ld	bc, -6
	add	hl, bc
	ld	c, (hl)			; get var name length
	call	util_get_data_ptr
	ld	de, (hl)
ti_ArchiveHasRoomVar.entry_sym:
	ld	a, c
	ex	de, hl
	ld	hl, (hl)
	ld	bc, 12
	add	a, c
	ld	c, a
	add.s	hl, bc
	jr	c, ti_ArchiveHasRoomVar.fail
	ld	c, l
	ld	b, h
	call	ti.FindFreeArcSpot
	ld	a, 1
	ret	nz
ti_ArchiveHasRoomVar.fail:
	xor	a, a
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
	ex	(sp), hl
	push	bc
	push	de
	add	hl, de
	or	a, a
	sbc	hl, de
	jr	nz, ti_SetGCBehavior.notdefault1
	ld	hl, util_post_gc_default_handler
ti_SetGCBehavior.notdefault1:
	ld	(util_post_gc_handler), hl
	sbc	hl, hl
	adc	hl, bc
	jr	nz, ti_SetGCBehavior.notdefault2
	ld	hl, util_pre_gc_default_handler
ti_SetGCBehavior.notdefault2:
	ld	(util_pre_gc_handler), hl
	ret
.equ util_post_gc_default_handler, util_no_op
.equ util_pre_gc_default_handler, util_no_op

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
	and	a, 0x3f
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
	jr	nc, util_insert_mem.enough_mem
	pop	hl
	xor	a, a
	ret
util_insert_mem.enough_mem:
	call	ti.InsertMem
	pop	hl
	ld	hl, (hl)
	push	hl
	inc.s	de			; clear UDE
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
	inc.s	de			; clear UDE
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
	jr	nc, util_is_slot_open.not_open
	ld	(curr_slot), a
	ld	b, 3
	mlt	bc
	ld	hl, variable_offsets - 1
	add	hl, bc
	ld	a, b
	cp	a, (hl)
	ret
util_is_slot_open.not_open:
	xor	a, a
	inc	a
	ret

util_get_vat_ptr:
; output:
;  HL = vat_ptr
; destroyed:
;  A
	ld	a, (curr_slot)
	ld	hl, vat_ptr0		; vat_ptr0 = $d0244e
	dec	a
	ret	z
	inc	h
	ld	l, 0x7b			; vat_ptr1 = $d0257b
	dec	a
	ret	z
	ld	l, 0x7e			; vat_ptr2 = $d0257e
	dec	a
	ret	z
	ld	l, 0x81			; vat_ptr3 = $d02581
	dec	a
	ret	z
	ld	l, 0x84			; vat_ptr4 = $d02584
	ret

util_get_data_ptr:
; output:
;  HL = data_ptr
; destroyed:
;  A
	ld	a, (curr_slot)
	ld	hl, data_ptr0		; data_ptr0 = $d0067e
	dec	a
	ret	z
	ld	l, 0x81			; data_ptr1 = $d00681
	dec	a
	ret	z
	ld	hl, data_ptr2		; data_ptr2 = $d01fed
	dec	a
	ret	z
	ld	l, 0xf3			; data_ptr3 = $d01ff3
	dec	a
	ret	z
	ld	l, 0xf9			; data_ptr4 = $d01ff9
	ret

util_get_offset_ptr:
; output:
;  HL = offset_ptr
	push	bc
	ld	hl, (curr_slot)
	ld	h, 3
	mlt	hl
	ld	bc, variable_offsets - 3
	add	hl, bc
	pop	bc
	ret

util_get_slot_size:
; output:
;  HL = data_ptr + 1
;  BC = slot_size
;  UBC = 0
; destroyed:
;  A
	call	util_get_data_ptr
	ld	hl, (hl)
	inc.s	bc			; clear UBC
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ret

util_get_offset:
; output:
;  HL = offset_ptr
;  BC = offset
	call	util_get_offset_ptr
	ld	bc, (hl)
	ret

util_archive:				; properly handle garbage collects
	ld	iy, ti.flags
	call	ti.ChkFindSym
	call	ti.ChkInRam
	ret	nz
	call	ti.PushOP1
	call	ti_ArchiveHasRoomVar.entry_sym
	jr	z, util_archive.handle_gc
	call	ti.Arc_Unarc
	jp	ti.PopOP1
util_archive.handle_gc:
	call	util_pre_gc_default_handler
.equ util_pre_gc_handler, .-3
	ld	iy, ti.flags
	call	ti.PopOP1
	call	ti.PushOP1
	call	ti.Arc_Unarc
	call	util_post_gc_default_handler
.equ util_post_gc_handler, .-3
	ld	iy, ti.flags
	jp	ti.PopOP1

util_unarchive:
	ld	iy, ti.flags
	call	ti.PushOP1
	call	ti.ChkFindSym
	call	ti.ChkInRam
	call	nz, ti.Arc_Unarc
	jp	ti.PopOP1

;-------------------------------------------------------------------------------
; Internal library data
;-------------------------------------------------------------------------------

	.db	255			; handle edge case of 0 for slot
variable_offsets:
	.d24	-1, -1, -1, -1, -1
