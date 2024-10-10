;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library FATDRVCE, 3

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export fat_Open
	export fat_Close
	export fat_OpenDir
	export fat_ReadDir
	export fat_CloseDir
	export fat_OpenFile
	export fat_CloseFile
	export fat_SetFileSize
	export fat_GetFileSize
	export fat_SetAttrib
	export fat_GetAttrib
	export fat_SetFileBlockOffset
	export fat_GetFileBlockOffset
	export fat_ReadFile
	export fat_WriteFile
	export fat_Create
	export fat_Delete
	export fat_GetVolumeLabel
;-------------------------------------------------------------------------------

include 'macros.inc'

; fat filesystem api

;-------------------------------------------------------------------------------
; fat structures
;-------------------------------------------------------------------------------

virtual at 0
	FAT_SUCCESS rb 1
	FAT_ERROR_INVALID_PARAM rb 1
	FAT_ERROR_INVALID_CLUSTER rb 1
	FAT_ERROR_INVALID_POSITION rb 1
	FAT_ERROR_NOT_FOUND rb 1
	FAT_ERROR_EXISTS rb 1
	FAT_ERROR_INVALID_PATH rb 1
	FAT_ERROR_FAILED_ALLOC rb 1
	FAT_ERROR_CLUSTER_CHAIN rb 1
	FAT_ERROR_DIRECTORY_NOT_EMPTY rb 1
	FAT_ERROR_NO_VOLUME_LABEL rb 1
	FAT_ERROR_RDONLY rb 1
	FAT_ERROR_RW_FAILED rb 1
	FAT_ERROR_INVALID_FILESYSTEM rb 1
	FAT_ERROR_INVALID_SIZE rb 1
	FAT_ERROR_INVALID_MAGIC rb 1
	FAT_ERROR_INVALID_SIGNATURE rb 1
	FAT_ERROR_NO_MORE_ENTRIES rb 1
	FAT_ERROR_INVALID_NAME rb 1
end virtual
virtual at 0
	FAT_LIST_FILEONLY rb 1
	FAT_LIST_DIRONLY rb 1
	FAT_LIST_ALL rb 1
end virtual

struct fatFile
	local size
	label .: size
	fat rl 1
	entry_block rd 1
	first_cluster rd 1
	current_cluster rd 1
	file_size rd 1
	block_count rl 1
	block_index rl 1
	starting_block_index rl 1		; only for read/write
	blocks_per_cluster rb 1			; copied from fat struct
	block_func rl 1				; internally selected
	current_block rd 1
	working_buffer rl 1
	entry_pointer rl 1
	size := $-.
end struct
struct fatDir
	local size
	label .: size
	fat rl 1
	open rb 1
	block_offset rl 1
	blocks_per_cluster rb 1
	cluster_block rb 1
	working_block rd 1
	working_cluster rd 1
	size := $-.
end struct
struct fat
	local size
	label .: size
    	read rl 1
    	write rl 1
	user rl 1
	base_lba rd 1
	blocks_per_cluster rb 1
	clusters rd 1
	fat_size rd 1
	fat_pos rl 1
	fs_info rl 1
	root_dir_pos rd 1
	data_region rd 1
	working_block rd 1
	working_cluster rd 1
	working_next_cluster rd 1
	working_prev_cluster rd 1
	working_size rd 1
	working_pointer rl 1
	working_entry rl 1
	working_next_entry rl 1
	working_prev_entry rl 1
	buffer rb 512
	size := $-.
end struct
struct fatDirEntry
	local size
	label .: size
	name rb 13
	attrib rb 1
	entrysize rd 1
	size := $-.
end struct


repeat 1, size: sizeof fat
	display 'fat size: ', `size, 10
end repeat

repeat 1, size: sizeof fatFile
	display 'fat file size: ', `size, 10
end repeat

repeat 1, size: sizeof fatDir
	display 'fat dir size: ', `size, 10
end repeat

repeat 1, size: sizeof fatDirEntry
	display 'fat dir entry size: ', `size
end repeat

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
fat_Open:
; Initializes a FAT filesystem from a particular LBA
; Arguments:
;  sp + 3 : uninitialized fat struct
;  sp + 6 : read callback
;  sp + 9 : write callback
;  sp + 12 : user data for callbacks
;  sp + 15 : lower 24 bits of base lba
;  sp + 18 : upper 8 bits of base lba
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	hl,(iy + 6)
	ld	(xfat.read),hl
	ld	hl,(iy + 9)
	ld	(xfat.write),hl
	ld	hl,(iy + 12)
	ld	(xfat.user),hl
	ld	a,hl,(iy + 15)
	ld	(xfat.base_lba),a,hl		; configure struct
	lea	iy,ix
	xor	a,a
	sbc	hl,hl
	call	util_read_fat_block		; read fat zero block
	jr	z,.read_zero_block
	ld	hl,FAT_ERROR_RW_FAILED
	pop	ix
	ret
.read_zero_block:
	lea	ix,yfat.buffer
	ld	a,(ix + 12)
	cp	a,(ix + 16)			; ensure 512 byte blocks and 2 FATs
	jr	z,.goodfat
	ld	hl,FAT_ERROR_INVALID_FILESYSTEM
	pop	ix
	ret
.goodfat:
	ld	a,(ix + 39)
	or	a,a				; can't support reallllly big drives (BPB_FAT32_FATSz32 high)
	jr	z,.goodsize
	ld	hl,FAT_ERROR_INVALID_SIZE
	pop	ix
	ret
.goodsize:
	xor	a,a
	ld	b,a
	ld	hl,(ix + 14)
	ex.s	de,hl
	ld	(yfat.fat_pos),de
	ld	hl,(ix + 36)			; BPB_FAT32_FATSz32
	ld	(yfat.fat_size),hl
	add	hl,hl				; * num fats
	adc	a,b
	add	hl,de				; data region
	adc	a,b				; get carry if needed
	ld	(yfat.data_region),a,hl
	push	af
	ex	de,hl
	ld	a,hl,(ix + 44)			; BPB_FAT32_RootClus
	ld	bc,2
	or	a,a
	sbc	hl,bc
	jr	nc,.nocarry
	dec	a
.nocarry:
	ld	c,(ix + 13)
	ld	(yfat.blocks_per_cluster),c
	jr	.enter
.multiply:
	add	hl,hl
	adc	a,a
.enter:
	rr	c
	jr	nc,.multiply
	pop	bc
	add	hl,de				; bude = data region
	adc	a,b				; root directory location
	ld	(yfat.root_dir_pos),a,hl
	ld	de,(ix + 48)
	ex.s	de,hl
	ld	(yfat.fs_info),hl
	xor	a,a
	call	util_read_fat_block
	jr	z,.check_magic
	ld	hl,FAT_ERROR_RW_FAILED
	pop	ix
	ret
.check_magic:
	call	util_checkmagic
	jr	z,.goodmagic
	ld	hl,FAT_ERROR_INVALID_MAGIC
	pop	ix
	ret
.goodmagic:
	ld	hl,(ix + 0)			; ix should still point to the temp block...
	ld	bc,$615252			; don't bother comparing $41 byte...
	xor	a,a
	sbc	hl,bc
	jr	z,.goodsig
	ld	hl,FAT_ERROR_INVALID_SIGNATURE
	pop	ix
	ret
.goodsig:
	scf
	sbc	hl,hl
	ex	de,hl
	lea	hl,yfat.buffer
	ld	bc,488
	add	hl,bc				; invalidate free space
	ld	(hl),de
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),e
	ld	hl,(yfat.fs_info)		; a is zero
	call	util_write_fat_block
	pop	ix
	ld	hl,FAT_ERROR_RW_FAILED
	ret	nz
	xor	a,a
	sbc	hl,hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_Close:
; Deinitialize the FAT partition
; Arguments:
;  sp + 3 : fat struct
; Returns:
;  FAT_SUCCESS on success
	pop	de
	ex	(sp),iy
	push	de
	xor	a,a
	sbc	hl,hl
	call	util_read_fat_block
	ld	hl,FAT_ERROR_RW_FAILED
	ret	nz
	lea	hl,yfat.buffer
	ld	de,$41
	add	hl,de
	res	0,(hl)				; clear dirty bit
	xor	a,a
	sbc	hl,hl
	call	util_write_fat_block
	ld	hl,FAT_ERROR_RW_FAILED
	ret	nz
	xor	a,a
	sbc	hl,hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_OpenDir:
; Opens a directory for reading contents
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : directory path
;  sp + 9 : dir struct
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 9)	; dir struct
	ld	(.fatdir),hl
	ld	de,(iy + 6)	; dir path
	ld	iy,(iy + 3)	; fat struct
	ld	a,(de)
	cp	a,'/'
	jq	nz,.path_error
	inc	de
	ld	a,(de)
	dec	de
	or	a,a
	jq	nz,.notroot
	ld	a,hl,(yfat.root_dir_pos)
	call	util_block_to_cluster
	jq	.gotcluster
.notroot:
	call	util_locate_entry
	jq	z,.path_error
	push	iy
	push	de
	pop	iy
	call	util_get_entry_first_cluster
	pop	iy
.gotcluster:
	compare_auhl_zero
	jr	nz,.findcluster
	ld	hl,FAT_ERROR_INVALID_CLUSTER
	ret
.findcluster:
	ld	(yfat.working_cluster),a,hl
	call	util_cluster_to_block
	ld	(yfat.working_block),a,hl
	call	util_read_fat_block		; read the first block for cache
	jr	z,.success
	ld	hl,FAT_ERROR_RW_FAILED
	ret
.success:
	push	ix
	ld	ix,0
.fatdir := $-3
	ld	(xfatDir.fat),iy
	ld	a,(yfat.blocks_per_cluster)
	ld	(xfatDir.blocks_per_cluster),a
	ld	(xfatDir.cluster_block),a
	ld	a,hl,(yfat.working_cluster)
	ld	(xfatDir.working_cluster),a,hl
	ld	a,hl,(yfat.working_block)
	ld	(xfatDir.working_block),a,hl
	ld	a,$aa
	ld	(xfatDir.open),a		; magic number
	xor	a,a
	sbc	hl,hl				; return success
	ld	(xfatDir.block_offset),hl
	pop	ix
	ret
.path_error:
	ld	hl,FAT_ERROR_INVALID_PATH
	ret

;-------------------------------------------------------------------------------
fat_ReadDir:
; Opens a directory for reading contents
; Arguments:
;  sp + 3 : dir struct
;  sp + 6 : entry struct
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)	; entry struct
	ld	(.entry),hl
	ld	iy,(iy + 3)	; dir struct
	ld	a,(yfatDir.open)
	cp	a,$aa		; check for magic open byte
	jr	z,.open
	ld	hl,FAT_ERROR_NO_MORE_ENTRIES
	cp	a,$bb
	ret	z
	ld	hl,FAT_ERROR_INVALID_PARAM
	ret
.open:

	; for speed, check if the currently cached block is available

	ld	a,(yfatDir.block_offset)
	push	ix
	ld	ix,(yfatDir.fat)
	lea	hl,xfat.working_block
	cp	a,16				; get next cluster if at end
	pop	ix
	jq	z,.next_block
	lea	de,yfatDir.working_block
	ld	b,4
.check_cache:
	ld	a,(de)
	cp	a,(hl)
	jr	nz,.read_block
	inc	hl
	inc	de
	djnz	.check_cache
	jr	.skip_read
.read_block:
	push	iy
	ld	a,hl,(yfatDir.working_block)
	ld	iy,(yfatDir.fat)
	ld	(yfat.working_block),a,hl
	call	util_read_fat_block		; read the block for cache
	pop	iy
	jq	z,.skip_read
	ld	hl,FAT_ERROR_RW_FAILED
	ret
.skip_read:
	ld	de,(yfatDir.block_offset)
	ld	hl,16
	or	a,a
	sbc	hl,de
	ld	b,l				; num entries left in the block
	ex	de,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl				; shift by 32 multiple
	push	ix
	lea	ix,iy
	ld	iy,(yfatDir.fat)
	lea	de,yfat.buffer
	add	hl,de				; pointer to entry
	push	hl
	pop	iy

.findentry:
	ld	a,(iy)
	or	a,a
	jr	nz,.continue
	ld	(xfatDir.open),$bb		; done marker
	ld	hl,(.entry)
	ld	bc,sizeof fatDirEntry
	xor	a,a
	call	ti.MemSet
	xor	a,a
	sbc	hl,hl				; success, zeroed entry at end
	pop	ix
	ret
.continue:
	inc	(xfatDir.block_offset)
	cp	a,$e5
	jr	z,.skip
	cp	a,' '
	jr	z,.skip
	ld	a,(iy + 11)
	tst	a,8
	jr	z,.foundentry
.skip:
	lea	iy,iy + 32
	djnz	.findentry

	lea	iy,ix
	pop	ix

	; handle the next block in the cluster
.next_block:
	ld	a,hl,(yfatDir.working_block)
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	ld	(yfatDir.working_block),a,hl
	xor	a,a
	ld	(yfatDir.block_offset),a
	dec	(yfatDir.cluster_block)
	jp	nz,.read_block

	; find the next cluster if at end of current cluster

	ld	a,hl,(yfatDir.working_cluster)
	push	iy
	ld	iy,(yfatDir.fat)
	call	util_next_cluster
	pop	iy
	compare_auhl_zero
	jr	nz,.foundcluster
	ld	(yfatDir.open),$bb		; done marker
	ld	hl,FAT_ERROR_NO_MORE_ENTRIES
	ret
.foundcluster:
	ld	(yfatDir.working_cluster),a,hl
	push	iy
	ld	iy,(yfatDir.fat)
	call	util_cluster_to_block
	pop	iy
	ld	(yfatDir.working_block),a,hl
	ld	a,(yfatDir.blocks_per_cluster)
	ld	(yfatDir.cluster_block),a
	jp	.read_block

.foundentry:
	pop	hl				; pop ix
	push	hl
	ld	ix,0
.entry := $-3
	lea	de,ix + 0
	lea	hl,iy + 0
	call	util_get_name
	ld	a,(iy + 11)
	ld	(xfatDirEntry.attrib),a
	ld	a,hl,(iy + 28)
	ld	(xfatDirEntry.entrysize),a,hl
	pop	ix
	xor	a,a
	sbc	hl,hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_CloseDir:
; Closes an open directory handle
; Arguments:
;  sp + 3 : dir struct
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	iy,(iy + 3)
	xor	a,a
	ld	(yfatDir.open),a
	sbc	hl,hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_GetVolumeLabel:
; Returns the volume label if it exists
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : volume label (8.3 format) storage
; Returns:
;  FAT_SUCCESS on success, and FAT_ERROR_NO_VOLUME_LABEL
	pop	de,iy
	push	iy,de
	ld	a,hl,(yfat.root_dir_pos)
	call	util_block_to_cluster
.findcluster:
	ld	(yfat.working_cluster),a,hl
	call	util_cluster_to_block
	ld	(yfat.working_block),a,hl
	ld	b,(yfat.blocks_per_cluster)
.findblock:
	ld	(yfat.working_block),a,hl
	push	bc
	call	util_read_fat_block
	jr	z,.rd_success
	pop	bc
	ld	hl,FAT_ERROR_RW_FAILED
	ret
.rd_success:
	lea	hl,yfat.buffer + 11
	ld	b,16
	ld	de,32
.findentry:
	ld	a,(hl)
	and	a,8
	jr	nz,.foundlabel
	add	hl,de
	djnz	.findentry
	ld	a,hl,(yfat.working_block)
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	pop	bc
	djnz	.findblock
	ld	a,hl,(yfat.working_cluster)
	call	util_next_cluster
	compare_auhl_zero
	jq	nz,.findcluster
.notfound:
	ld	hl,FAT_ERROR_NO_VOLUME_LABEL
	ret
.foundlabel:
	pop	bc
	ld	de,-11
	add	hl,de
	pop	bc,iy,de
	push	de,iy,bc
	ld	bc,11
	ldir
	jq	.enterremovetrailingspaces
.removetrailingspaces:
	ld	a,(de)
	cp	a,' '
	jq	nz,.done
.enterremovetrailingspaces:
	xor	a,a
	ld	(de),a
	dec	de
	jq	.removetrailingspaces
.done:
	xor	a,a
	sbc	hl,hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_OpenFile:
; Attempts to open a file for reading and/or writing
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : filename (8.3 format)
;  sp + 9 : flags (currently unused)
;  sp + 12 : fat file struct
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 6)
	push	iy
	ld	iy,(iy + 3)
	call	util_locate_entry
	pop	iy
	jr	nz,.found
	ld	hl,FAT_ERROR_NOT_FOUND
	ret
.found:
	ld	bc,(iy + 3)
	ld	iy,(iy + 12)
	ld	(yfatFile.fat),bc
	ld	(yfatFile.entry_pointer),de
	ld	(yfatFile.entry_block),a,hl
	push	ix
	push	bc
	pop	ix
	ld	a,(xfat.blocks_per_cluster)
	ld	(yfatFile.blocks_per_cluster),a	; for faster access
	pop	ix
.enter:
	push	iy
	ld	iy,(yfatFile.entry_pointer)
	ld	a,(iy + 20 + 1)
	ld	hl,(iy + 20 - 2)
	ld	l,(iy + 26 + 0)
	ld	h,(iy + 26 + 1)			; first cluster
	pop	iy
	ld	(yfatFile.first_cluster),a,hl
	ld	(yfatFile.current_cluster),a,hl
	compare_auhl_zero
	jr	z,.notallocated
	push	iy
	ld	iy,(yfatFile.entry_pointer)	; get file size
	ld	a,hl,(iy + 28)
	pop	iy
.notallocated:
	ld	(yfatFile.file_size),a,hl
	call	util_ceil_byte_size_to_block_size
	ld	(yfatFile.block_count),a,hl
	ld	a,hl,(yfatFile.current_cluster)
	push	iy
	ld	iy,(yfatFile.fat)
	call	util_cluster_to_block
	pop	iy
	ld	(yfatFile.current_block),a,hl
	xor	a,a
	sbc	hl,hl
	ld	(yfatFile.block_index),hl		; return success
	ret

;-------------------------------------------------------------------------------
fat_SetFileSize:
; Sets the size of the file
; Arguments:
;  sp + 3 : fat file struct
;  sp + 6 : size low word
;  sp + 9 : size high byte
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 6)
	push	iy
	ld	iy,(iy + 3)
	ld	a,hl,(yfatFile.entry_block)
	ld	de,(yfatFile.entry_pointer)
	ld	iy,(yfatFile.fat)
	ld	(yfat.working_block),a,hl
	ld	(yfat.working_entry),de
	push	de
	pop	iy
	ld	a,(iy + 20 + 1)			; start at first cluster, and walk the chain
	ld	hl,(iy + 20 - 2)			; until the number of clusters is allocated
	ld	l,(iy + 26 + 0)
	ld	h,(iy + 26 + 1)
	ld	(.currentcluster),a,hl
	pop	iy
	ld	bc,(iy + 6)			; get new file size
	ld	a,(iy + 9)
	push	iy
	ld	iy,(iy + 3)
	ld	iy,(yfatFile.fat)
	push	iy
	ld	iy,(yfat.working_entry)
	ld	e,hl,(iy + 28)
	ld	(iy + 28),a,bc			; otherwise, directly store new size
	pop	iy
	ld	(yfat.working_size),a,bc
	pop	iy				; get current file size
	call	ti._lcmpu
	jq	z,.success			; if same size, just return
	jq	c,.makelarger
.makesmaller:
	call	.writeentry
	compare_hl_zero
	jq	nz,.notzerofile
	push	iy
	ld	iy,(iy + 3)
	ld	iy,(yfatFile.fat)
	ld	a,hl,(.currentcluster)
	call	util_dealloc_cluster_chain	; deallocate all clusters
	pop	iy
	jq	nz,.write_error
	jq	.success
.notzerofile:
	push	hl
	pop	bc
	ld	a,hl,(.currentcluster)
	compare_auhl_zero
	jq	z,.success
	push	iy
	ld	iy,(iy + 3)
	ld	iy,(yfatFile.fat)
	dec	bc
	jq	.entertraverseclusters
.traverseclusters:
	push	bc
	call	util_next_cluster
	compare_auhl_zero
	pop	bc
	jr	nz,.goodchain			; the filesystem is screwed up
	ld	hl,FAT_ERROR_CLUSTER_CHAIN
	ret
.goodchain:
	dec	bc
.entertraverseclusters:
	compare_bc_zero
	jq	nz,.traverseclusters
	call	util_set_new_eoc_cluster	; mark this cluster as unused
	call	util_dealloc_cluster_chain	; deallocate all other clusters
	pop	iy
	jq	nz,.write_error
	jq	.success
.makelarger:
	call	.writeentry			; get number of clusters there needs to be
	compare_hl_zero
	jq	z,.success
.allocateclusters:
	push	hl
	push	iy
	ld	iy,(iy + 3)
	ld	iy,(yfatFile.fat)
	ld	a,hl,(.currentcluster)
	ld	(yfat.working_cluster),a,hl
	call	util_next_cluster
	compare_auhl_zero
	jq	nz,.alreadyallocated
	call	util_alloc_cluster
.alreadyallocated:
	ld	(.currentcluster),a,hl
	compare_auhl_zero
	pop	iy
	pop	hl
	jr	nz,.goodalloc
	ld	hl,FAT_ERROR_FAILED_ALLOC
	ret
.goodalloc:
	dec	hl
	compare_hl_zero
	jq	nz,.allocateclusters
	;jq	.success
.success:
	ld	iy,(iy + 3)
	ld	a,hl,(yfatFile.entry_block)	; read the entry again for open
	push	iy
	ld	iy,(yfatFile.fat)
	call	util_read_fat_block
	pop	iy
	jr	nz,.write_error
	jq	fat_OpenFile.enter			; reopen the file
.writeentry:
	push	iy
	ld	iy,(iy + 3)
	ld	iy,(yfatFile.fat)
	ld	a,hl,(yfat.working_size)
	compare_auhl_zero
	jq	nz,.writenotzero
	push	ix
	ld	ix,(yfat.working_entry)
	xor	a,a
	ld	(ix + 20 + 0),a			; remove first cluster if zero
	ld	(ix + 20 + 1),a
	ld	(ix + 26 + 0),a
	ld	(ix + 26 + 1),a
	pop	ix
.writenotzero:
	ld	a,hl,(yfat.working_block)
	call	util_write_fat_block		; write the new size
	jq	z,.writegood
	pop	iy
.write_error:
	ld	hl,FAT_ERROR_RW_FAILED
	ret
.writegood:
	ld	a,hl,(yfat.working_size)
	call	util_ceil_byte_size_to_blocks_per_cluster
	pop	iy
	ret

.currentcluster:
	dd	0

;-------------------------------------------------------------------------------
fat_GetFileSize:
; Gets the size of the file
; Arguments:
;  sp + 3 : fat file struct
; Returns:
;  File size in bytes
	pop	de
	ex	iy,(sp)
	push	de
	ld	e,hl,(yfatFile.file_size)
	ret

;-------------------------------------------------------------------------------
fat_SetFileBlockOffset:
; Sets the offset block position in the file
; Arguments:
;  sp + 3 : fat file struct
;  sp + 6 : block offset
; Returns:
;  FAT_SUCCESS on success
	pop	bc
	pop	iy
	pop	hl
	push	hl
	push	iy
	push	bc
	ld	de,(yfatFile.block_count)
	or	a,a
	sbc	hl,de
	add	hl,de
	jq	nc,.invalid
	ld	de,(yfatFile.block_index)
	or	a,a
	sbc	hl,de
	ret	z				; if at the same block position, done (return 0)
	add	hl,de				; hl = new block_index, de = current block_index

	; check if block is within current cluster
	; we can optimize by just changing the block position
	ld	(yfatFile.block_index),hl
	ld	a,(yfatFile.blocks_per_cluster)
	dec	a
	cpl
	ld	c,a				; mask for number of blocks
	and	a,l
	ld	l,a
	ld	a,c
	and	a,e
	ld	b,e
	ld	e,a
	or	a,a
	sbc	hl,de				; hl - de = number of cluster blocks to advance by
	jr	c,.restartchain			; requires a previous cluster, restart the chain
	jr	nz,.nextclusters
.withincluster:
	ld	e,b
	ld	hl,(yfatFile.block_index)
	or	a,a
	sbc	hl,de
	ld	a,de,(yfatFile.current_block)	; need to move the current block up or down
	ld	bc,$800000
	add	hl,bc
	sbc	a,c
	add	hl,bc
	add	hl,de
	adc	a,c
	ld	(yfatFile.current_block),a,hl
	xor	a,a
	sbc	hl,hl
	ret					; just changed block position, no need to move clusters (return 0)

.nextclusters:
	ld	a,(yfatFile.blocks_per_cluster)
	dec	a
	and	a,(yfatFile.block_index)
	ld	bc,0
	ld	c,a				; bc = offset of block in last cluster
	add	hl,bc
	jr	.followchain
.restartchain:
	ld	a,hl,(yfatFile.first_cluster)
	ld	(yfatFile.current_cluster),a,hl
	ld	hl,(yfatFile.block_index)
.followchain:
	ld	c,(yfatFile.blocks_per_cluster)
	xor	a,a
	ld	b,24
.divloop:
	add	hl,hl
	rla
	cp	a,c
	jr	c,.divskip
	sub	a,c
	inc	l
.divskip:
	djnz	.divloop
	ld	(.cluster_block),a
	push	hl
	pop	bc
	ld	a,hl,(yfatFile.current_cluster)
	jr	.entergetpos
.getclusterpos:
	push	bc,iy
	ld	iy,(yfatFile.fat)
	call	util_next_cluster
	pop	iy,bc
	compare_hl_zero
	jr	z,.chainfailed
	dec	bc
.entergetpos:
	compare_bc_zero
	jr	nz,.getclusterpos
	ld	(yfatFile.current_cluster),a,hl
	push	iy
	ld	iy,(yfatFile.fat)
	call	util_cluster_to_block
	pop	iy
	ld	de,0
.cluster_block := $-3
	add	hl,de
	adc	a,d
	ld	(yfatFile.current_block),a,hl
.success:
	xor	a,a
	sbc	hl,hl
	ret
.invalid:
	ld	hl,FAT_ERROR_INVALID_POSITION
	ret
.chainfailed:
	ld	hl,FAT_ERROR_CLUSTER_CHAIN
	ret

;-------------------------------------------------------------------------------
fat_GetFileBlockOffset:
; Gets the file's block position
; Arguments:
;  sp + 3 : FAT File structure type
; Returns:
;  Block position in file
	pop	de
	ex	hl,(sp)
	push	de
	compare_hl_zero
	ret	z
	push	hl
	pop	iy
	ld	hl,(yfatFile.block_index)
	ret

;-------------------------------------------------------------------------------
fat_SetAttrib:
; Sets the attributes of the path
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : file path
;  sp + 9 : file attributes flag
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 6)
	push	iy
	ld	iy,(iy + 3)
	call	util_locate_entry
	pop	iy
	jq	z,.invalidpath
	push	hl,af
	ld	a,(iy + 9)
	push	de
	pop	iy
	ld	(iy + 11),a
	pop	af,hl
	call	util_write_fat_block
	ld	hl,FAT_ERROR_RW_FAILED
	ret	nz
	xor	a,a
	sbc	hl,hl
	ret
.invalidpath:
	ld	hl,FAT_ERROR_INVALID_PATH
	ret

;-------------------------------------------------------------------------------
fat_GetAttrib:
; Gets the attributes of the path
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : file path
; Returns:
;  File attribute byte
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 6)
	ld	iy,(iy + 3)
	call	util_locate_entry
	jq	z,.invalidpath
	push	de
	pop	iy
	ld	a,(iy + 11)
	ret
.invalidpath:
	ld	hl,FAT_ERROR_INVALID_PATH
	ret

;-------------------------------------------------------------------------------
fat_CloseFile:
; Closes an open file handle
; Arguments:
;  sp + 3 : fat struct
; Returns:
;  FAT_SUCCESS on success
	xor	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
fat_ReadFile:
; Reads blocks from an open file handle
; Arguments:
;  sp + 3 : FAT File structure type
;  sp + 6 : Number of blocks to read
;  sp + 9 : Buffer to read into
; Returns:
;  FAT_SUCCESS on success
	ld	hl,util_read_fat_multiple_blocks
	ld	(util_fat_read_write.block_func),hl
	jq	util_fat_read_write

;-------------------------------------------------------------------------------
fat_WriteFile:
; Writes a blocks to an open file handle
; Arguments:
;  sp + 3 : FAT File structure type
;  sp + 6 : Number of blocks to write
;  sp + 9 : Buffer to write
; Returns:
;  FAT_SUCCESS on success
	ld	hl,util_write_fat_multiple_blocks
	ld	(util_fat_read_write.block_func),hl
	jq	util_fat_read_write

;-------------------------------------------------------------------------------
util_zerocluster:
; okay, so I just want to rant about this function. ever since msdos 1.25 (!!),
; the zero byte has been the marker for the end of entry chain. *however*, in
; order to support the spec and be "backwards compatible", no one actually
; uses this byte, requiring an entire cluster to be zeroed when a directory is
; created. this is dumb. this is stupid. screw backwards compatibily, anyone
; still using msdos 1.25 now is literally insane or really sad because
; they are supporting some legacy system.
; anyway, this function just writes zeros to an entire cluster.
; inputs:
;   iy: fat structure
;   auhl: cluster to zero
; outputs:
;   a stupid zeroed cluster
	push	hl
	lea	hl,yfat.buffer
	push	hl
	pop	de
	inc	de
	ld	bc,512
	ld	(hl),c
	ldir
	pop	hl
	call	util_cluster_to_block
	ld	b,(yfat.blocks_per_cluster)
.zerome:
	push	bc
	push	af
	push	hl
	call	util_write_fat_block
	pop	hl
	jq	nz,.error
	pop	af
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	pop	bc
	djnz	.zerome
	xor	a,a
	ret
.error:
	pop	hl,hl
	xor	a,a
	inc	a
	ret

;-------------------------------------------------------------------------------
fat_Create:
; Creates a new file or directory entry
; Arguments:
;  sp + 3 : FAT structure type
;  sp + 6 : Path
;  sp + 9 : New name
;  sp + 12 : File attributes
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 9)
	call	util_validate_fat_name
	ld	hl,FAT_ERROR_INVALID_NAME
	ret	z
	ld	hl,-512
	add	hl,sp
	ld	sp,hl				; temporary space for concat
	ex	de,hl
	push	de
	ld	hl,(iy + 6)
	compare_hl_zero
	jq	z,.rootdirpath
	call	ti.StrCopy
.rootdirpath:
	ld	a,'/'
	ld	(de),a
	inc	de
	ld	hl,(iy + 9)
	call	ti.StrCopy
	pop	de
	push	iy
	ld	iy,(iy + 3)
	call	util_locate_entry
	pop	iy
	jq	nz,.alreadyexists
	ld	hl,(iy + 6)
	inc	hl				; todo: check for '/' or '.'?
	ld	a,(hl)
	or	a,a
	jq	nz,.notroot
	push	iy
	ld	iy,(iy + 3)
	push	iy
	call	util_alloc_entry_root
	pop	iy
	ld	(yfat.working_prev_entry),de
	ld	(yfat.working_entry),de
	ld	bc,0
	ld	(yfat.working_prev_cluster),c,bc
	pop	iy
	jq	.createfile
.notroot:
	ld	de,(iy + 6)
	push	iy
	ld	iy,(iy + 3)
	call	util_locate_entry
	pop	iy
	jq	z,.invalidpath
	push	iy
	ld	iy,(iy + 3)
	ld	(yfat.working_prev_entry),de
	ld	(yfat.working_block),a,hl
	push	de
	pop	iy
	ld	a,(iy + 20 + 1)
	ld	hl,(iy + 20 - 2)		; get hlu
	ld	l,(iy + 26 + 0)
	ld	h,(iy + 26 + 1)			; get the entry's cluster
	pop	iy
	push	iy
	ld	iy,(iy + 3)
	ld	(yfat.working_cluster),a,hl
	ld	(yfat.working_prev_cluster),a,hl
	call	util_alloc_entry
	ld	(yfat.working_entry),de
	pop	iy
.createfile:
	compare_auhl_zero
	jq	z,.failedalloc
	push	ix
	push	iy
	ld	de,(iy + 9)
	ld	iy,(iy + 3)
	ld	(yfat.working_block),a,hl
	ld	hl,(yfat.working_entry)
	push	hl
	call	util_get_fat_name
	pop	ix
	pop	iy
	ld	a,(iy + 12)
	ld	(ix + 11),a
	xor	a,a
	sbc	hl,hl
	ld	(ix + 28),a,hl			; set initial size to zero
	ld	(ix + 20),a
	ld	(ix + 21),a
	ld	(ix + 26),a
	ld	(ix + 27),a
	pop	ix
	push	iy
	ld	iy,(iy + 3)
	ld	a,hl,(yfat.working_block)
	call	util_write_fat_block
	pop	iy
	jq	nz,.rw_error
	bit	4,(iy + 12)
	jq	z,.notdirectory
.createdirectory:
	push	iy
	ld	iy,(iy + 3)
	xor	a,a
	sbc	hl,hl
	ld	(yfat.working_cluster),a,hl
	call	util_alloc_entry.enter
	ld	(yfat.working_next_entry),de
	ld	(yfat.working_block),a,hl
	call	util_block_to_cluster
	ld	(yfat.working_cluster),a,hl
	call	util_zerocluster		; zero the damn cluster >:(
	jq	nz,.rw_errorpop
	ld	hl,(yfat.working_next_entry)
	ld	(hl),'.'			; buffer is zero from cluster zeroing
	ld	b,10
.setsingledot:
	inc	hl
	ld	(hl),' '
	djnz	.setsingledot
	inc	hl
	ld	(hl),$10
	push	ix
	ld	ix,(yfat.working_next_entry)
	xor	a,a
	sbc	hl,hl
	ld	(ix + 12),a
	ld	de,(yfat.working_cluster + 2)
	ld	(ix + 20),e
	ld	(ix + 21),d
	ld	de,(yfat.working_cluster + 0)
	ld	(ix + 26),e
	ld	(ix + 27),d
	ld	(ix + 28),hl
	ld	(ix + 31),a
	pop	ix
	ld	a,hl,(yfat.working_block)
	call	util_write_fat_block
	jq	nz,.rw_errorpop
	ld	de,(yfat.working_prev_entry)
	ld	(yfat.working_entry),de
	call	util_alloc_entry
	ld	(yfat.working_next_entry),de
	ld	(yfat.working_block),a,hl
	call	util_read_fat_block
	jq	nz,.rw_errorpop
	ld	a,hl,(yfat.working_block)
	call	util_block_to_cluster
	ld	(yfat.working_cluster),a,hl
	ld	hl,(yfat.working_next_entry)
	ld	(hl),'.'
	inc	hl
	ld	(hl),'.'
	ld	b,9
.setdoubledot:
	inc	hl
	ld	(hl),' '
	djnz	.setdoubledot
	inc	hl
	ld	(hl),$10
	push	ix
	ld	ix,(yfat.working_next_entry)
	xor	a,a
	sbc	hl,hl
	ld	(ix + 12),$00
	ld	de,(yfat.working_prev_cluster + 2)
	ld	(ix + 20),e
	ld	(ix + 21),d
	ld	de,(yfat.working_prev_cluster + 0)
	ld	(ix + 26),e
	ld	(ix + 27),d
	ld	(ix + 28),hl
	ld	(ix + 31),a
	ld	(ix + 32 + 0),a
	ld	(ix + 32 + 11),a		; zero next entry, mark as eoc
	pop	ix
	ld	a,hl,(yfat.working_block)
	call	util_write_fat_block
	jq	nz,.rw_errorpop
	pop	iy
.notdirectory:
	ld	e,FAT_SUCCESS
	jq	.restorestack
.failedalloc:
	ld	e,FAT_ERROR_FAILED_ALLOC
	jq	.restorestack
.alreadyexists:
	ld	e,FAT_ERROR_EXISTS
	jq	.restorestack
.invalidpath:
	ld	e,FAT_ERROR_INVALID_PATH
	jq	.restorestack
.rw_errorpop:
	pop	hl
.rw_error:
	ld	e,FAT_ERROR_RW_FAILED
	jq	.restorestack
.restorestack:
	ld	hl,512
	ld	d,l
	add	hl,sp
	ld	sp,hl
	ex.s	de,hl
	ret

;-------------------------------------------------------------------------------
fat_Delete:
; Deletes a file and deallocates the spaced used by it on disk
; Arguments:
;  sp + 3 : FAT structure type
;  sp + 6 : Path
; Returns:
;  FAT_SUCCESS on success
	ld	iy,0
	add	iy,sp
	push	ix
	call	.enter
	pop	ix
	ret
.enter:
	ld	de,(iy + 6)
	ld	iy,(iy + 3)
	push	iy
	call	util_locate_entry
	pop	iy
	jq	z,.invalidpath
	push	de
	pop	ix
	bit	4,(ix + 11)
	jq	z,.normalfile
.directory:
	push	hl,af
	push	ix
	ld	a,(ix + 20 + 1)
	ld	hl,(ix + 20 - 2)		; get hlu
	ld	l,(ix + 26 + 0)
	ld	h,(ix + 26 + 1)
	call	util_is_directory_empty
	pop	ix
	pop	de,hl
	ld	a,d
	jq	nz,.dirnotempty
	push	ix
	push	hl,af
	call	util_read_fat_block		; reread entry block
	pop	de,hl
	ld	a,d
	pop	ix				; a directory can now be treated as a normal file
	jq	nz,.rw_error
.normalfile:
	ld	(ix + 11),0
	ld	(ix + 0),$e5			; mark entry as deleted
	push	ix
	call	util_write_fat_block
	pop	ix
	jq	nz,.rw_error
	ld	a,(ix + 20 + 1)
	ld	hl,(ix + 20 - 2)		; get hlu
	ld	l,(ix + 26 + 0)
	ld	h,(ix + 26 + 1)
	call	util_dealloc_cluster_chain
	jq	nz,.rw_error
	ret
.invalidpath:
	ld	hl,FAT_ERROR_INVALID_PATH
	ret
.rw_error:
	ld	hl,FAT_ERROR_RW_FAILED
	ret
.dirnotempty:
	ld	hl,FAT_ERROR_DIRECTORY_NOT_EMPTY
	ret

;-------------------------------------------------------------------------------
util_get_entry_first_cluster:
	ld	a,(iy + 20 + 1)
	ld	hl,(iy + 20 - 2)		; get hlu
	ld	l,(iy + 26 + 0)
	ld	h,(iy + 26 + 1)			; get the entry's cluster
	ret

;-------------------------------------------------------------------------------
util_end_of_chain:
; inputs
;   auhl: cluster
; outputs
;   flag c set if end of cluster chain
; perserves
;   hl, af, bc, de
	push	de,hl,af
	ex	de,hl
	and	a,$0f
	ld	hl,8
	add	hl,de
	ex	de,hl
	adc	a,$f0
	pop	de,hl
	ld	a,d
	pop	de
	ret

;-------------------------------------------------------------------------------
util_set_new_eoc_cluster:
; inputs
;   iy: fat structure
;   auhl: cluster entry to mark as end
; outputs:
;   auhl: previous contents of cluster entry
	compare_auhl_zero
	ret	z
	call	util_end_of_chain
	ret	c
	push	af,hl
	call	util_cluster_entry_to_block
	call	util_read_fat_block
	pop	hl,de
	ld	a,d
	jq	nz,.error
	call	util_get_cluster_offset
	ld	a,$ff				; mark new end of chain
	ld	bc,(hl)
	ld	(hl),a
	inc	hl
	ld	(hl),a
	inc	hl
	ld	(hl),a
	inc	hl
	ld	d,(hl)				; dubc = previous cluster
	ld	(hl),$0f			; end of chain marker
	push	bc,de
	pop	af,hl
	ret
.error:
	xor	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat structure
;   auhl: starting cluster to deallocate from
; outputs:
;   yfat.working_cluster: ending cluster
;   yfat.working_block: block with cluster offset
util_dealloc_cluster_chain:
	compare_auhl_zero
	jq	z,.success
	call	util_end_of_chain
	jq	c,.success
	ld	(yfat.working_cluster),a,hl
	call	util_cluster_entry_to_block
	ld	(yfat.working_block),a,hl
	call	util_read_fat_block
	jq	nz,.error
.followchain:
	ld	a,hl,(yfat.working_cluster)
	call	util_get_cluster_offset
	xor	a,a
	ld	bc,(hl)
	ld	(hl),a
	inc	hl
	ld	(hl),a
	inc	hl
	ld	(hl),a
	inc	hl
	ld	d,(hl)				; dubc = previous cluster
	ld	(hl),a				; zero previous cluster
	push	bc,de
	pop	af,hl				; auhl = previous cluster
	ld	(yfat.working_cluster),a,hl
	call	util_end_of_chain		; check if end of chain
	jq	c,.updatepartialchain
	compare_auhl_zero
	jq	z,.updatepartialchain
	call	util_cluster_entry_to_block
	ld	e,a
	ld	a,bc,(yfat.working_block)
	call	ti._lcmpu
	jq	z,.followchain
	jq	.updatepartialchain
.updatepartialchain:
	ld	a,hl,(yfat.working_block)
	call	util_update_fat_table
	ld	a,hl,(yfat.working_cluster)
	jq	z,util_dealloc_cluster_chain
	jq	.error
.error:
	xor	a,a
	inc	a
	ret
.success:
	xor	a,a
	ret

; inputs:
;   iy: fat structure
;   iy + working_cluster: previous cluster
;   iy + working_block: entry block
;   iy + working_entry: entry in block
; outputs:
;   auhl: allocated cluster number
util_alloc_cluster:
	xor	a,a
	sbc	hl,hl
.traversefat:
	push	hl,af
	ld	bc,(yfat.fat_pos)
	add	hl,bc
	adc	a,0
	call	util_read_fat_block
	jq	z,.readfatblock
	pop	af,hl
	jq	.rw_error
.readfatblock:
	push	ix
	lea	ix,yfat.buffer - 4
	ld	b,128
.traverseclusterchain:
	lea	ix,ix + 4
	ld	a,hl,(ix)
	compare_auhl_zero
	jr	z,.unallocatedcluster
	djnz	.traverseclusterchain
	pop	ix
	pop	af,hl
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	jq	.traversefat
	ret
.unallocatedcluster:
	ld	a,128
	sub	a,b
	ld	bc,0
	ld	c,a
	lea	de,ix
	ld	a,$0f
	scf
	sbc	hl,hl
	ld	(ix),a,hl
	pop	ix,af,hl
	push	af,hl
	add	hl,hl				; shift auhl by 7 left
	adc	a,a
	add	hl,hl
	adc	a,a
	add	hl,hl
	adc	a,a
	add	hl,hl
	adc	a,a
	add	hl,hl
	adc	a,a
	add	hl,hl
	adc	a,a
	add	hl,hl
	adc	a,a
	add	hl,bc
	adc	a,b				; new cluster
	ld	(yfat.working_next_cluster),a,hl
	pop	hl,af
	ld	bc,(yfat.fat_pos)
	add	hl,bc
	adc	a,0
	call	util_update_fat_table
	jq	nz,.rw_error
	ld	a,hl,(yfat.working_cluster)
	compare_auhl_zero
	jq	z,.linkentrytofirstcluster
.linkclusterchain:
	push	hl
	call	util_cluster_entry_to_block
	push	hl,af
	call	util_read_fat_block
	pop	de,bc,hl
	jq	nz,.rw_error
	push	bc,de
	call	util_get_cluster_offset
	push	ix
	push	hl
	pop	ix
	ld	a,hl,(yfat.working_next_cluster)
	ld	(ix),a,hl
	pop	ix,af,hl
	call	util_update_fat_table
	jq	nz,.rw_error
	ld	a,hl,(yfat.working_cluster)
	compare_auhl_zero
	jq	nz,.nolinkneeded
.linkentrytofirstcluster:
	ld	a,hl,(yfat.working_block)
	call	util_read_fat_block
	jq	nz,.rw_error
	push	ix
	ld	ix,(yfat.working_entry)
	ld	de,(yfat.working_next_cluster + 0)
	ld	(ix + 26),e
	ld	(ix + 27),d
	ld	de,(yfat.working_next_cluster + 2)
	ld	(ix + 20),e
	ld	(ix + 21),d
	pop	ix
	ld	a,hl,(yfat.working_block)
	call	util_write_fat_block
	jq	nz,.rw_error
.nolinkneeded:
	ld	a,hl,(yfat.working_next_cluster)
	ret
.rw_error:
	xor	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat structure
;   auhl: block to update in FAT
util_update_fat_table:
	push	af,hl
	call	util_write_fat_block
	pop	hl,de
	ld	a,d
	ret	nz
	ld	bc,(yfat.fat_size)
	add	hl,bc
	adc	a,0
	call	util_write_fat_block
	ret	nz
	xor	a,a
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat structure
;   iy + working_cluster: previous cluster
;   iy + working_block: entry block
;   iy + working_entry: entry in block
; outputs:
;   auhl: new entry block
;   de: offset in entry block
util_do_alloc_entry:
	call	util_alloc_cluster
	call	util_cluster_to_block
	ld	b,0
	push	ix
	lea	ix,yfat.buffer
	ld	(ix + 0),$e5
	ld	(ix + 11),b
	ld	(ix + 20),b
	ld	(ix + 21),b
	ld	(ix + 26),b
	ld	(ix + 27),b
	ld	(ix + 28),b
	ld	(ix + 29),b
	ld	(ix + 30),b
	ld	(ix + 31),b
	ld	(ix + 32),b
	pop	ix
	push	af,hl
	call	util_write_fat_block
	pop	hl
	jq	nz,.error
	pop	af
	ret
.error:
	pop	hl
	xor	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat struct
;   iy + working_cluster: first cluster
;   iy + working_block: parent entry block
;   iy + working_entry: parent entry in block
; outputs:
;   auhl: new entry block
;   de: fat.buffer address for entry block
util_alloc_entry:
	ld	a,hl,(yfat.working_cluster)
.enter:
	call	util_cluster_to_block
	compare_auhl_zero
	jr	z,.alloccluster
	ld	b,(yfat.blocks_per_cluster)
.loop:
	push	bc,hl,af
	call	util_read_fat_block
	push	iy
	lea	iy,yfat.buffer - 32
	ld	b,16
.findavailentry:
	lea	iy,iy + 32
	ld	a,(iy + 0)
	cp	a,$e5				; deleted entry, let's use it!
	jr	z,.foundavailentry
	or	a,a
	jr	z,.foundavailentry		; end of list, let's allocate here
	djnz	.findavailentry
	pop	iy,af,hl
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	pop	bc
	djnz	.loop
.movetonextcluster:
	ld	a,hl,(yfat.working_cluster)
	call	util_next_cluster
	compare_auhl_zero
	jr	nz,.nextclusterisvalid
	push	af,hl
.alloccluster:
	ld	a,hl,(yfat.working_cluster)
	call	util_do_alloc_entry
	lea	de,yfat.buffer
	ret
.nextclusterisvalid:
	ld	(yfat.working_cluster),a,hl
	jr	.enter
.foundavailentry:
	lea	de,iy				; pointer to new entry
	pop	iy,af,hl,bc			; auhl = block with entry
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat structure
; outputs:
;   auhl: new entry block
;   de: offset in entry block
util_alloc_entry_root:
	xor	a,a
	sbc	hl,hl
	ld	(yfat.working_block),a,hl
	lea	hl,yfat.buffer
	ld	(yfat.working_entry),hl
	ld	a,hl,(yfat.root_dir_pos)
	call	util_block_to_cluster
	ld	(yfat.working_cluster),a,hl
	jq	util_alloc_entry.enter

;-------------------------------------------------------------------------------
util_get_name:
	ld	a,'.'
	cp	a,(hl)
	jq	z,.special
	push	hl
	ld	b,8
.name8:
	ld	a,(hl)
	cp	a,' '
	jr	z,.next
	ld	(de),a
	inc	hl
	inc	de
	djnz	.name8
.next:
	pop	hl
	ld	bc,8
	add	hl,bc
	ld	a,(hl)
	cp	a,' '
	jq	z,.done			; no extension
	ld	a,'.'
	ld	(de),a
	inc	de
	ld	b,3
.name3:
	ld	a,(hl)
	cp	a,' '
	jr	z,.done
	ld	(de),a
	inc	hl
	inc	de
	djnz	.name3
.done:
	xor	a,a
	ld	(de),a
	ret
.special:
	ld	(de),a
	inc	hl
	inc	de
	cp	a,(hl)
	jq	nz,.done
	ld	(de),a
	inc	de
	jq	.done

;-------------------------------------------------------------------------------
util_get_fat_name:
; convert name to storage name (covers most cases)
; inputs
;   de: name
;   hl: <output> name (11+1 bytes)
	push	de
	ld	b,0
.loop1:
	ld	a,b
	cp	a,8
	jr	nc,.done1
	ld	a,(de)
	cp	a,'.'
	jr	z,.done1
	cp	a,'/'
	jr	z,.done1
	or	a,a
	jr	z,.done1
	call	util_toupper
	ld	(hl),a
	inc	de
	inc	hl
	inc	b
	jr	.loop1
.done1:
	ld	a,b
	cp	a,8
	jr	nc,.elseif
	ld	a,(de)
	or	a,a
	jr	z,.elseif
	cp	a,'/'
	jr	z,.elseif
	ld	a,8
.loop2:
	cp	a,b
	jr	z,.fillremaining
	ld	(hl),' '
	inc	hl
	inc	b
	jr	.loop2
.fillremaining:
	inc	de
.loop3456:
	ld	a,b
	cp	a,11
	jq	nc,.return
	ld	a,(de)
	or	a,a
	jr	z,.other
	cp	a,'/'
	jr	z,.other
	inc	de
.store:
	call	util_toupper
	ld	(hl),a
	inc	hl
	inc	b
	jr	.loop3456
.other:
	ld	a,' '
	jr	.store
.elseif:
	ld	a,b
	cp	a,8
	jr	nz,.spacefill
	ld	a,(de)
	cp	a,'.'
	jr	nz,.spacefill
	jr	.fillremaining
.spacefill:
	ld	a,11
.spacefillloop:
	cp	a,b
	jq	z,.return
	ld	(hl),' '
	inc	hl
	inc	b
	jq	.spacefillloop
.return:
	pop	de
	ret

;-------------------------------------------------------------------------------
util_validate_fat_name:
; ensure none of the following characters: * ? . , ; : / \ | + = < > [ ] " \t
; inputs:
;   hl: pointer to null terminated string
; outputs:
;   z set if invalid name
.loop:
	ld	a,(hl)
	or	a,a
	jr	z,.done
	cp	a,'*'
	ret	z
	cp	a,'?'
	ret	z
	cp	a,','
	ret	z
	cp	a,';'
	ret	z
	cp	a,':'
	ret	z
	cp	a,'/'
	ret	z
	cp	a,'\'
	ret	z
	cp	a,'|'
	ret	z
	cp	a,'+'
	ret	z
	cp	a,'='
	ret	z
	cp	a,'<'
	ret	z
	cp	a,'>'
	ret	z
	cp	a,'['
	ret	z
	cp	a,']'
	ret	z
	cp	a,'"'
	ret	z
	cp	a,'	'
	ret	z
	inc	hl
	jr	.loop
.done:
	inc	a
	ret

;-------------------------------------------------------------------------------
util_toupper:
	cp	a,'a'
	ret	c
	cp	a,'z'+1
	ret	nc
	res	5,a
	ret

;-------------------------------------------------------------------------------
util_get_component_start:
	ld	a,(de)
	or	a,a
	ret	z
	cp	a,'/'
	ret	nz
	inc	de
	jq	util_get_component_start

;-------------------------------------------------------------------------------
util_get_next_component:
	ld	a,(de)
	or	a,a
	ret	z
	cp	a,'/'
	ret	z
	inc	de
	jq	util_get_next_component

;-------------------------------------------------------------------------------
util_is_directory_empty:
; inputs
;   iy: FAT structure
;   auhl: cluster
; outputs
;   z flag set if directory is empty
.enter:
	ld	(yfat.working_cluster),a,hl
	call	util_cluster_to_block
	compare_auhl_zero
	ret	z
	ld	(yfat.working_block),a,hl
	ld	b,(yfat.blocks_per_cluster)
.next_block:
	push	bc
	ld	a,hl,(yfat.working_block)
	call	util_read_fat_block
	jq	nz,.fail
	push	ix
	ld	b,16
	lea	ix,yfat.buffer - 32
.loop:
	lea	ix,ix + 32
	ld	a,(ix + 11)
	cp	a,$0f
	jr	z,.next
	ld	a,(ix + 0)
	or	a,a
	jq	z,.successpop
	cp	a,$e5
	jr	z,.next
	cp	a,'.'
	jr	z,.next
	cp	a,' '
	jr	z,.next
	jq	.failpop
.next:
	djnz	.loop
	ld	a,hl,(yfat.working_block)
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	ld	(yfat.working_block),a,hl
	pop	bc
	djnz	.next_block
	ld	a,hl,(yfat.working_cluster)
	call	util_next_cluster
	jq	.enter
.successpop:
	pop	bc,bc
.success:
	xor	a,a
	ret
.failpop:
	pop	bc,bc
.fail:
	xor	a,a
	inc	a
	ret

;-------------------------------------------------------------------------------
util_locate_entry:
; finds the component entry
; inputs
;   iy: fat structure
;   de: name
; outputs
;   auhl: block of entry
;   de: offset to entry in block
;   z set if not found
	ld	a,hl,(yfat.root_dir_pos)
	ld	(yfat.working_block),a,hl
	ld	(yfat.working_pointer),de
	ld	a,(de)
	cp	a,'/'
	jq	nz,.error
	inc	de
	ld	a,(de)
	or	a,a
	jq	nz,.findcomponent		; root directory
	lea	de,yfat.buffer
	inc	a
	ret
.findcomponent:
	ld	de,(yfat.working_pointer)
	call	util_get_component_start
	jq	z,.error
	ld	hl,.string
	call	util_get_fat_name
	call	util_get_next_component
	ld	(yfat.working_pointer),de
.locateloop:
	ld	a,hl,(yfat.working_block)
	call	util_read_fat_block
	jq	nz,.error
	push	iy
	lea	iy,yfat.buffer - 32
	ld	c,16
.detectname:
	lea	iy,iy + 32
	ld	a,(iy + 11)
	and	a,$0f
	cp	a,$0f				; long file name entry, skip
	jr	z,.skipentry
	ld	a,(iy + 0)
	cp	a,$e5				; deleted entry, skip
	jr	z,.skipentry
	or	a,a
	jq	z,.errorpopiy			; end of list, suitable entry not found
	lea	de,iy
	ld	hl,.string
	ld	b,11
.cmpnames:
	ld	a,(de)
	cp	a,(hl)
	jr	nz,.skipentry
	inc	de
	inc	hl
	djnz	.cmpnames
	lea	de,iy
	pop	iy
	ld	hl,(yfat.working_pointer)
	ld	a,(hl)
	or	a,a				; check if end of component lookup (de)
	jq	z,.foundlastcomponent
	push	iy
	push	de
	pop	iy
	call	util_get_entry_first_cluster
	pop	iy
	call	util_cluster_to_block
	compare_auhl_zero
	jq	z,.error			; this means it is empty... which shouldn't happen!
	ld	(yfat.working_block),a,hl
	jq	.findcomponent			; found the component we were looking for (yay)
.skipentry:
	dec	c
	jr	nz,.detectname
	pop	iy
.movetonextblock:
	ld	a,hl,(yfat.working_block)
	call	util_block_to_cluster
	push	hl,af
	ld	a,hl,(yfat.working_block)
	ld	bc,1				; increment auhl
	add	hl,bc
	add	a,b
	call	util_block_to_cluster
	pop	bc,de
	compare_hl_de
	jr	nz,.movetonextcluster
	cp	a,b
	jr	nz,.movetonextcluster
	ld	a,hl,(yfat.working_block)
	ld	bc,1				; increment auhl
	add	hl,bc
	adc	a,b
	jq	.storeblockandloop
.movetonextcluster:
	ld	a,hl,(yfat.working_block)
	call	util_block_to_cluster
	call	util_next_cluster
	call	util_cluster_to_block
.storeblockandloop:
	ld	(yfat.working_block),a,hl
	compare_auhl_zero
	jq	nz,.locateloop			; make sure we can get the next cluster
.errorpopiy:
	pop	iy
.error:
	xor	a,a
	sbc	hl,hl
	ret
.foundlastcomponent:
	ld	a,hl,(yfat.working_block)
	compare_auhl_zero
	ret
.string:
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0

;-------------------------------------------------------------------------------
util_cluster_to_block:
; gets the base block of the cluster
; inputs
;   auhl = cluster
;   iy -> fat structure
; outputs
;   auhl = block
	ld	de,-2
	add	hl,de
	adc	a,d
	ld	c,a
	ld	a,(yfat.blocks_per_cluster)
	jr	c,.enter
	xor	a,a
	sbc	hl,hl
	ret
.loop:
	add	hl,hl
	rl	c
.enter:
	rrca
	jr	nc,.loop
	ld	a,de,(yfat.data_region)
	add	hl,de
	adc	a,c
	ret

;-------------------------------------------------------------------------------
util_block_to_cluster:
; gets block to base cluster
; inputs
;   auhl = block
;   iy -> fat structure
; outputs
;   auhl = cluster
	compare_auhl_zero
	ret	z
	ld	bc,(yfat.data_region + 0)
	or	a,a
	sbc	hl,bc
	sbc	a,(yfat.data_region + 3)
	ld	de,(yfat.blocks_per_cluster - 2)
	ld	d,0
	ld	e,a
.loop:
	add	hl,hl
	ex	de,hl
	adc	hl,hl
	ex	de,hl
	jr	nc,.loop
	ld	a,d
	push	de
	push	hl
	inc	sp
	pop	hl
	inc	sp
	inc	sp
	ld	bc,2
	add	hl,bc
	adc	a,b
	ret

; inputs:
;   auhl : parent cluster
;   iy : fat struct
; outputs:
;   auhl : next cluster
util_next_cluster:
	ld	de,0
	add	hl,hl
	adc	a,a				; << 1
	ld	e,l				; cluster pos
	push	af				; >> 8
	inc	sp
	push	hl
	inc	sp
	pop	hl
	inc	sp
	xor	a,a
	ld	bc,(yfat.fat_pos)
	add	hl,bc
	adc	a,a
	push	de
	call	util_read_fat_block
	pop	hl
	jr	nz,.error
	add	hl,hl
	lea	de,yfat.buffer
	add	hl,de
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)
	and	a,$0f
	ld	hl,8
	add	hl,de
	ex	de,hl
	ld	e,a
	adc	a,$f0
	jr	nc,.found
	ld	e,a
	ex	de,hl
	ret
.found:
	ld	a,e
	ret
.error:
	xor	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
util_fat_read_write:
; inputs:
;   same as fat_ReadFile / fat_WriteFile
; outputs:
;   same as fat_ReadFile / fat_WriteFile
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	hl,(xfatFile.block_index)
	ld	(xfatFile.starting_block_index),hl
	ld	de,(xfatFile.block_count)
	compare_hl_de
	jq	nc,.return
	ex	de,hl
	or	a,a
	sbc	hl,de
	ld	de,(iy + 6)
	compare_hl_de
	jq	nc,.loop
	ld	(iy + 6),hl			; only read to eof
.loop:
	ld	hl,(iy + 6)			; number of blocks left to transfer
	compare_hl_zero				; no more blocks left, exit
	jq	z,.return

	ld	d,(xfatFile.blocks_per_cluster)
	ld	a,d
	dec	a
	and	a,(xfatFile.block_index)	; mask off the number of blocks remaining in this cluster
	ld	e,a
	ld	a,d
	sub	a,e
	ld	de,0
	ld	e,a
	ex	de,hl				; de = total remaining, hl = remaining in cluster
	compare_hl_de
	jr	nc,.singleclusterread
.multicluster:
	ex	de,hl				; de = number of blocks remaining in cluster
	ld	a,hl,(xfatFile.current_block)
	compare_auhl_zero
	jr	z,.return
	push	de
	call	.do_xfer
	pop	de
	jq	nz,.return
	ld	hl,(iy + 6)
	or	a,a
	sbc	hl,de
	ld	(iy + 6),hl			; subtract remaining from total
	ld	hl,(xfatFile.block_index)
	add	hl,de
	ld	(xfatFile.block_index),hl
	call	.getnextcluster
	jr	.loop
.singleclusterread:
	ld	a,hl,(xfatFile.current_block)
	compare_auhl_zero
	jr	z,.return			; invalid block
	push	de
	call	.do_xfer
	pop	de
	jr	nz,.return
	ld	a,hl,(xfatFile.current_block)
	add	hl,de
	adc	a,d
	ld	(xfatFile.current_block),a,hl
	ld	hl,(xfatFile.block_index)
	add	hl,de
	ld	(xfatFile.block_index),hl
	ld	h,(xfatFile.blocks_per_cluster)
	ld	a,h
	dec	a
	and	a,l
	or	a,a				; if at end of cluster, get the next one
	call	z,.getnextcluster
.return:
	ld	hl,(xfatFile.block_index)
	ld	de,(xfatFile.starting_block_index)
	or	a,a
	sbc	hl,de				; return number of blocks transferred
	pop	ix
	ret
.do_xfer:
	push	de
	pop	bc
	ld	de,(iy + 9)
	push	iy
	ld	iy,(xfatFile.fat)
	call	util_read_fat_multiple_blocks
.block_func := $-3
	pop	iy
	ret
.getnextcluster:
	ld	hl,(xfatFile.block_index)
	ld	de,(xfatFile.block_count)
	or	a,a
	sbc	hl,de
	ret	nc				; don't try to go too far
	ld	a,hl,(xfatFile.current_cluster)
	push	iy
	ld	iy,(xfatFile.fat)
	call	util_next_cluster
	pop	iy
	ld	(xfatFile.current_cluster),a,hl
	push	iy
	ld	iy,(xfatFile.fat)
	call	util_cluster_to_block
	pop	iy
	ld	(xfatFile.current_block),a,hl
	ret

;-------------------------------------------------------------------------------
util_read_fat_block:
; inputs:
;  auhl : lba
;  iy : fat struct
	lea	de,yfat.buffer
.buffer:
	ld	bc,1

;-------------------------------------------------------------------------------
util_read_fat_multiple_blocks:
; inputs:
;  auhl: lba
;  de : data
;  bc : block count
;  iy : fat struct
; outputs:
;   z if success
	push	iy
	push	bc				; store count for checking
	push	de
	push	bc
	ld	bc,(yfat.base_lba)
	add	hl,bc
	adc	a,(yfat.base_lba + 3)
	ld	c,a
	push	bc
	push	hl
	ld	hl,(yfat.user)
	push	hl
	ld	hl,(yfat.read)
	ld	de,.ret
	push	de
	jp	(hl)
.ret:
	pop	bc,bc,bc,bc,bc
	pop	de				; pop count check
	pop	iy
	compare_hl_de
	ret

;-------------------------------------------------------------------------------
util_write_fat_block:
; inputs:
;  auhl : lba
;  iy : fat struct
	lea	de,yfat.buffer
.buffer:
	ld	bc,1

;-------------------------------------------------------------------------------
util_write_fat_multiple_blocks:
; inputs:
;  auhl: lba
;  de : data
;  bc : block count
;  iy : fat struct
	push	iy
	push	bc				; store count for checking
	push	de
	push	bc
	ld	bc,(yfat.base_lba)
	add	hl,bc
	adc	a,(yfat.base_lba + 3)
	ld	c,a
	push	bc
	push	hl
	ld	hl,(yfat.user)
	push	hl
	ld	hl,(yfat.write)
	ld	de,util_read_fat_multiple_blocks.ret
	push	de
	jp	(hl)

; inputs:
;  iy : msd struct
util_checkmagic:
	push	hl,de
	lea	hl,yfat.buffer
	ld	de,510
	add	hl,de
	ld	de,(hl)
	ld	hl,$AA55
	ex.s	de,hl
	compare_hl_de
	pop	de,hl
	ret

;-------------------------------------------------------------------------------
util_get_cluster_offset:
	ld	a,l
	and	a,$7f
	or	a,a
	sbc	hl,hl
	ld	l,a
	add	hl,hl
	add	hl,hl
	lea	de,yfat.buffer
	add	hl,de
	ret

;-------------------------------------------------------------------------------
util_cluster_entry_to_block:
	ld	e,a
	xor	a,a
	ld	bc,128
	call	ti._ldivu
	ld	bc,(yfat.fat_pos)
	add	hl,bc
	adc	a,e
	ret

;-------------------------------------------------------------------------------
util_ceil_byte_size_to_block_size:
	compare_auhl_zero
	ret	z
	ld	e,a
	push	hl,de
	xor	a,a
	ld	bc,512
	push	bc
	call	ti._lremu
	compare_hl_zero
	pop	bc,de,hl
	push	af
	xor	a,a
	call	ti._ldivu
	pop	af
	ret	z
	inc	hl
	ret

;-------------------------------------------------------------------------------
util_ceil_byte_size_to_blocks_per_cluster:
	compare_auhl_zero
	ret	z
	push	af,hl
	xor	a,a
	sbc	hl,hl
	ld	h,(yfat.blocks_per_cluster)
	add	hl,hl
	push	hl
	pop	bc
	pop	hl,de
	ld	e,d
	push	hl,de,bc
	call	ti._lremu
	compare_hl_zero
	pop	bc,de,hl
	push	af
	xor	a,a
	call	ti._ldivu
	pop	af
	ret	z
	inc	hl
	ret
