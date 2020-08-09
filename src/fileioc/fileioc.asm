;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'FILEIOC', 6

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
	call	__indcall
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
	call	_HLTimes9
	inc	hl
	inc	hl
	push	hl
	call	__indcall
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
	ld	a, $40
	ld	(vat_ptr0 + 2), a
	ld	(vat_ptr1 + 2), a
	ld	(vat_ptr2 + 2), a
	ld	(vat_ptr3 + 2), a
	ld	(vat_ptr4 + 2), a
	ret

;-------------------------------------------------------------------------------
ti_Resize:
; resizes an appvar variable
; args:
;  sp + 3 : new size
;  sp + 6 : slot index
; return:
;  hl = new size if no failure
	pop	de
	pop	hl			; hl = new size
	pop	bc			; c = slot
	push	bc
	push	hl
	push	de
	call	util_is_slot_open
	jp	z, util_ret_neg_one
	push	hl
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
	call	_EnoughMem
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
	jp	z, util_ret_null
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
	db	$fe			; ld a,appVarObj -> cp a,$3e \ dec d
assert appVarObj = $15

;-------------------------------------------------------------------------------
ti_Open:
; opens an appvar, acting as a file handle
; args:
;  sp + 3 : pointer to appvar name
;  sp + 6 : open flags
; return:
;  a = slot index if no error
	ld	a, appVarObj
.start:
	ld	(.smc_type), a
	ld	(OP1), a
	ld	iy, flags
	push	ix
	ld	ix, 0
	add	ix, sp
	xor	a, a
	ld	hl, (vat_ptr0)
	inc	a
	add	hl, hl
	jr	nc, .slot
	ld	hl, (vat_ptr1)
	inc	a
	add	hl,hl
	jr	nc, .slot
	ld	hl, (vat_ptr2)
	inc	a
	add	hl, hl
	jr	nc, .slot
	ld	hl, (vat_ptr3)
	inc	a
	add	hl, hl
	jr	nc, .slot
	ld	hl, (vat_ptr4)
	inc	a
	add	hl, hl
	jp	c, util_ret_null_pop_ix
.slot:
	ld	(curr_slot), a
	ld	hl, (ix + 6)
	ld	de, OP1 + 1
	call	_Mov8b
	xor	a, a
	ld	(de), a
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 'w'
	ld	iy, flags
	jr	nz, .no_overwite
	call	_PushOP1
	call	_ChkFindSym
	call	nc, _DelVarArc
	call	_PopOP1
.no_overwite:
	ld	hl, (ix + 9)
	ld	a, (hl)
	cp	a, 'r'
	jr	z, .mode
	cp	a, 'a'
	jr	z, .mode
	cp	a, 'w'
	jp	nz, util_ret_null_pop_ix
.mode:
	inc	hl
	ld	a, (hl)
	cp	a, '+'
	jr	nz, .no_append
.archive_var:
	call	_PushOP1
	call	_ChkFindSym
	call	_ChkInRam
	jr	z, .in_ram
	or	a, a
	sbc	hl, hl
	ex	de, hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ex	de, hl
	call	_EnoughMem
	push	af
	call	_PopOP1
	pop	af
	jp	c, util_ret_null_pop_ix
	call	_PushOP1
	call	_Arc_Unarc
	call	_PopOP1
	jr	.archive_var
.in_ram:
	call	_PopOP1
.no_append:
	call	_ChkFindSym
	jr	c, .not_found
	call	_ChkInRam
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
	ld	iy, flags
	call	_CreateVar
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
	jp	z, util_ret_null
	ld	a, e
	push	af
	call	util_get_vat_ptr
	ld	hl, (hl)
	ld	a, (hl)
	ld	(OP1), a
	ld	bc, -6
	add	hl, bc
	ld	b, (hl)
	ld	de, OP1 + 1
	dec	hl
.copy_name:
	ld	a, (hl)
	ld	(de), a
	inc	de
	dec	hl
	djnz	.copy_name
	xor	a, a
	ld	(de), a
	call	_PushOP1
	ld	iy, flags
	call	_ChkFindSym
	call	_ChkInRam
	push	af
	pop	bc
	pop	af
	or	a, a
	jr	z, .set_not_archived
.set_archived:
	push	bc
	pop	af
	call	z, util_Arc_Unarc
	jr	.relocate_var
.set_not_archived:
	push	bc
	pop	af
	call	nz, _Arc_Unarc
.relocate_var:
	call	_PopOP1
	call	_ChkFindSym
	jp	c, util_ret_neg_one
	call	_ChkInRam
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
	jr	z, .ret0
	call	util_is_in_ram
	jr	z, .ret0
	ld	bc, (iy + 6)
	ld	hl, (iy + 9)
	call	__smulu
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
	jr	z, .ret0
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	or	a, a
	sbc	hl, bc			; size - offset = bytes left to read
	jr	z, .ret0
	jr	c, .ret0
	ld	bc, (iy + 6)
	call	__sdivu			; (size - offset) / chunk_size
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
	call	__smulu
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
	jp	z, util_ret_neg_one
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	scf
	sbc	hl, bc			; size-offset
	jp	c, util_ret_neg_one
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

;-------------------------------------------------------------------------------
ti_PutC:
; Performs an fputc on an AppVar
; args:
;  sp + 3 : Character to place
;  sp + 6 : Slot number
; return:
;  Character written if no failure
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	ld	a, l
	ld	(char_in), a
	call	util_is_slot_open
	jp	z, util_ret_neg_one
	push	hl
	call	util_is_in_ram
	pop	hl
	jp	c, util_ret_neg_one
_PutChar:
	call	util_get_slot_size
	push	bc
	call	util_get_offset
	pop	hl
	or	a, a
	sbc	hl, bc
	jp	c, util_ret_neg_one
	jr	nz, .no_increment
.increment:
	push	bc
	inc	hl
	ld	(resize_amount), hl
	call	_EnoughMem
	pop	bc
	jp	c, util_ret_neg_one
	push	bc
	ex	de, hl
	call	util_insert_mem
	pop	bc
	or	a, a
	jp	z, util_ret_neg_one
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
	jp	z, util_ret_neg_one
	ld	a, (iy + 6)		; origin location
	or	a, a
	jr	z, .seek_set
	dec	a
	jr	z, .seek_curr
	dec	a
	jp	nz, util_ret_neg_one
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
	jp	c, util_ret_neg_one
	jp	util_set_offset
.seek_curr:
	push	de
	call	util_get_offset
	jr	.seek_set_asm

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
	db	$fe			; ld a,appVarObj -> cp a,$3E \ dec d
assert appVarObj = $15

;-------------------------------------------------------------------------------
ti_Delete:
; deletes an appvar
; args:
;  sp + 3 : pointer to appvar name
; return:
;  hl = 0 if failure
	ld	a,appVarObj
.start:
	pop	de
	pop	hl
	push	hl
	push	de
	dec	hl
	push	af
	call	_Mov9ToOP1
	pop	af
	ld	(OP1), a
	call	_ChkFindSym
	jp	c, util_ret_null
	ld	iy, flags
	call	_DelVarArc
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
	jp	z, util_ret_neg_one
.rewind:
	ld	bc, 0
	call	util_set_offset
	or	a, a
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
	jp	z, util_ret_neg_one
	call	util_get_offset
	push	bc
	pop	hl
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
	jp	z, util_ret_neg_one
	call	util_get_slot_size
	push	bc
	pop	hl
	ret

;-------------------------------------------------------------------------------
ti_Close:
; closes an open slot index
; args:
;  sp + 3 : slot index
; return:
;  n/a
	pop	hl
	pop	bc
	push	bc
	push	hl
	ld	a, c
	ld	(curr_slot), a
	call	util_get_vat_ptr
	inc	hl
	inc	hl
	ld	(hl), $40
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
	db	$fe			; ld a,appVarObj -> cp a,$3E \ dec d
assert appVarObj = $15

;-------------------------------------------------------------------------------
ti_Detect:
; finds an appvar that starts with some data
;  sp + 3 : address of pointer to being search
;  sp + 6 : pointer to null terminated string of data to search for
; return:
;  hl -> name of variable
	ld	a,appVarObj
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
	ld	hl, (progPtr)
.fdetect:
	ld	de, (pTemp)
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
	cp	a, appVarObj
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
	call	_SetDEUToA
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
	ld	hl, OP6
	pop	ix
	ret

.fbypassname:				; bypass the name in the vat
	ld	de, OP6
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
	call	_Isa2ByteTok
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
	ld	iy, flags
	call	_Get_Tok_Strng
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
	ld	hl, OP3
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
	jp	z, util_ret_null
	call	util_get_slot_size
	inc	hl
	push	hl
	call	util_get_offset
	pop	hl
	add	hl, bc
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
	jp	z, util_ret_null
	call	util_get_vat_ptr
	ld	hl, (hl)
	ret

;-------------------------------------------------------------------------------
ti_GetName:
; gets the variable name of an open slot index
; args:
;  sp + 3 : name buffer
;  sp + 6 : slot index
; return:
;  n/a
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	push	hl
	call	util_is_slot_open
	pop	de
	ret	z
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
	ld	iy, flags		; probably not needed
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
	ld	a,appVarObj		; file type
.start:
	pop	bc
	pop	hl
	pop	de
	push	de			; de -> new name
	push	hl			; hl -> old name
	push	bc
	push	de			; new
	push	de			; new
	ld	de, OP1
	ld	(de), a
	inc	de
	call	_Mov8b
	call	_PushOP1		; save old name
	ld	hl, util_Arc_Unarc
	ld	(.smc_archive), hl
	pop	hl			; new name
	ld	de, OP1 + 1
	call	_Mov8b
	call	_ChkFindSym
	push	af
	call	_PopOP1
	pop	af
	jr	nc, .return_1		; check if name already exists
.locate_program:
	call	_ChkFindSym		; find old name
	jr	c, .return_2
	call	_ChkInRam
	jr	nz, .in_archive
	ld	hl, util_no_op			; no-op routine instead of assuming $F8 points to a ret instruction lol
	ld	(.smc_archive), hl
	call	_PushOP1
	call	util_Arc_Unarc
	call	_PopOP1
	jr	.locate_program
.in_archive:
	ex	de, hl
	ld	de, 9
	add	hl, de			; skip vat stuff
	ld	e, (hl)
	add	hl, de
	inc	hl			; size of name
	call	_LoadDEInd_s
	pop	bc			; bc -> new name
	push	hl
	push	de
	push	bc
	call	_PushOP1		; old name
	pop	hl
	ld	de, OP1 + 1
	call	_Mov8b
	call	_PushOP1		; new name
	pop	hl
	push	hl
	ld	a, (OP1)
	call	_CreateVar
	inc	de
	inc	de
	pop	bc
	pop	hl
	call	_ChkBCIs0
	jr	z, .is_zero
	ldir
.is_zero:
	call	_PopOP1
	call	util_Arc_Unarc
.smc_archive := $-3
	call	_PopOP1
	call	_ChkFindSym
	call	_DelVarArc
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
	call	_ChkFindSym
	call	nc, _DelVarArc
	ld	a, (ix + 6)
	ld	hl, (ix + 12)
	and	a, $3f
	call	_DataSize
	pop	ix
	push	hl
	ex	de, hl
	dec	hl
	dec	hl
	call	_CreateVar
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
	call	_FindSym
	jp	c, .notcr		; fill it with zeros
	and	a, $3f
	ex	de, hl
	call	_Mov9OP1OP2
.notcr:
	call	_PushOP1
	ld	hl, (iy + 6)		; pointer to var string
	ld	a, (iy + 3)
	call	util_set_var_str
	ld	iy, flags
	ld	hl, util_ret_neg_one_byte
	call	_PushErrorHandler
	call	_StoOther
	call	_PopErrorHandler
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
	ld	iy, flags
	call	util_set_var_str
	call	_FindSym
	jp	c, util_ret_neg_one_byte
	push	af
	call	_ChkInRAM
	pop	bc
	ld	a, b
	jp	nz, util_ret_neg_one_byte
	ld	iy, 0
	add	iy, sp
	and	a, $3f
	cp	a, (iy + 3)		; var type
	jp	nz, util_ret_neg_one_byte
	ld	hl, (iy + 9)
	ld	(hl), de
	ret

;-------------------------------------------------------------------------------
ti_ArchiveHasRoom:
; checks if there is room in the archive before a garbage collect
; args:
;  sp + 3 : number of bytes to store into the archive
; return:
;  true if there is room, false if not
	pop	de
	ex	(sp),hl
	push	de
util_ArchiveHasRoom:
	ld	bc,12
	add	hl,bc
	call	_FindFreeArcSpot
	ld	a,1
	ret	nz
	dec	a
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
	ld	de, OP1 + 1
	call	_Mov8b
	and	a, $3f
	ld	(OP1), a
	ret

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
	call	_EnoughMem
	pop	de
	pop	hl
	jr	c, util_ret_null_byte
	call	_InsertMem
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
	call	_DelMem
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
util_ret_null_byte:
	xor	a, a
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
	ld	a, c
	ld	(curr_slot), a
	push	hl
	call	util_get_vat_ptr
	inc	hl
	inc	hl
	bit	7, (hl)
	pop	hl
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
	dec	l
	ld	h, 3
	mlt	hl
	ld	bc, variable_offsets
	add	hl,bc
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

util_Arc_Unarc: ;properly handle garbage collects :P
	call	_ChkInRAM
	jp	nz,_Arc_Unarc ;if the file is already in archive, we won't trigger a gc
	ex	hl,de
	call	_LoadDEInd_s
	ex	hl,de
	call	util_ArchiveHasRoom
	jp	nz,_Arc_Unarc ;gc will not be triggered
	call	util_pre_gc_default_handler
util_pre_gc_handler:=$-3
	call	_Arc_Unarc
	jp	util_post_gc_default_handler
util_post_gc_handler:=$-3



;-------------------------------------------------------------------------------
; Internal library data
;-------------------------------------------------------------------------------

variable_offsets:
	dl	0, 0, 0, 0, 0
