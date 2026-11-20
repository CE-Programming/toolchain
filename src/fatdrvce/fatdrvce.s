;-------------------------------------------------------------------------------
.include "library.inc"
;-------------------------------------------------------------------------------

library FATDRVCE, 3

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	lib_export fat_Open
	lib_export fat_Close
	lib_export fat_OpenDir
	lib_export fat_ReadDir
	lib_export fat_CloseDir
	lib_export fat_OpenFile
	lib_export fat_CloseFile
	lib_export fat_SetFileSize
	lib_export fat_GetFileSize
	lib_export fat_SetAttrib
	lib_export fat_GetAttrib
	lib_export fat_SetFileBlockOffset
	lib_export fat_GetFileBlockOffset
	lib_export fat_ReadFile
	lib_export fat_WriteFile
	lib_export fat_Create
	lib_export fat_Delete
	lib_export fat_GetVolumeLabel
;-------------------------------------------------------------------------------

.include "compare.inc"

; fat filesystem api

;-------------------------------------------------------------------------------
; fat structures
;-------------------------------------------------------------------------------

.struct 0
FAT_SUCCESS:	.space 1
FAT_ERROR_INVALID_PARAM:	.space 1
FAT_ERROR_INVALID_CLUSTER:	.space 1
FAT_ERROR_INVALID_POSITION:	.space 1
FAT_ERROR_NOT_FOUND:	.space 1
FAT_ERROR_EXISTS:	.space 1
FAT_ERROR_INVALID_PATH:	.space 1
FAT_ERROR_FAILED_ALLOC:	.space 1
FAT_ERROR_CLUSTER_CHAIN:	.space 1
FAT_ERROR_DIRECTORY_NOT_EMPTY:	.space 1
FAT_ERROR_NO_VOLUME_LABEL:	.space 1
FAT_ERROR_RDONLY:	.space 1
FAT_ERROR_RW_FAILED:	.space 1
FAT_ERROR_INVALID_FILESYSTEM:	.space 1
FAT_ERROR_INVALID_SIZE:	.space 1
FAT_ERROR_INVALID_MAGIC:	.space 1
FAT_ERROR_INVALID_SIGNATURE:	.space 1
FAT_ERROR_NO_MORE_ENTRIES:	.space 1
FAT_ERROR_INVALID_NAME:	.space 1
.text
.struct 0
FAT_LIST_FILEONLY:	.space 1
FAT_LIST_DIRONLY:	.space 1
FAT_LIST_ALL:	.space 1
.text

.struct 0
fatFile:
fatFile.fat:	.space 3
fatFile.entry_block:	.space 4
fatFile.first_cluster:	.space 4
fatFile.current_cluster:	.space 4
fatFile.file_size:	.space 4
fatFile.block_count:	.space 3
fatFile.block_index:	.space 3
fatFile.starting_block_index:	.space 3	; only for read/write
fatFile.blocks_per_cluster:	.space 1	; copied from fat struct
fatFile.block_func:	.space 3	; internally selected
fatFile.current_block:	.space 4
fatFile.working_buffer:	.space 3
fatFile.entry_pointer:	.space 3
.equ fatFile_size, . - fatFile

.struct 0
fatDir:
fatDir.fat:	.space 3
fatDir.open:	.space 1
fatDir.block_offset:	.space 3
fatDir.blocks_per_cluster:	.space 1
fatDir.cluster_block:	.space 1
fatDir.working_block:	.space 4
fatDir.working_cluster:	.space 4
.equ fatDir_size, . - fatDir

.struct 0
fat:
fat.read:	.space 3
fat.write:	.space 3
fat.user:	.space 3
fat.base_lba:	.space 4
fat.blocks_per_cluster:	.space 1
fat.clusters:	.space 4
fat.fat_size:	.space 4
fat.fat_pos:	.space 3
fat.fs_info:	.space 3
fat.root_dir_pos:	.space 4
fat.data_region:	.space 4
fat.working_block:	.space 4
fat.working_cluster:	.space 4
fat.working_next_cluster:	.space 4
fat.working_prev_cluster:	.space 4
fat.working_size:	.space 4
fat.working_pointer:	.space 3
fat.working_entry:	.space 3
fat.working_next_entry:	.space 3
fat.working_prev_entry:	.space 3
fat.buffer:	.space 512
.equ fat_size, . - fat

.struct 0
fatDirEntry:
fatDirEntry.name:	.space 13
fatDirEntry.attrib:	.space 1
fatDirEntry.entrysize:	.space 4
.equ fatDirEntry_size, . - fatDirEntry

.text

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
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy + 3)
	ld	hl, (iy + 6)
	ld	(ix + fat.read), hl
	ld	hl, (iy + 9)
	ld	(ix + fat.write), hl
	ld	hl, (iy + 12)
	ld	(ix + fat.user), hl
	ld	hl, (iy + 15)
	ld	a, (iy + 15 + 3)
	ld	(ix + fat.base_lba), hl		; configure struct
	ld	(ix + fat.base_lba + 3), a
	lea	iy, ix+0
	xor	a, a
	sbc	hl, hl
	call	util_read_fat_block		; read fat zero block
	jr	z, fat_Open.read_zero_block
	ld	hl, FAT_ERROR_RW_FAILED
	pop	ix
	ret
fat_Open.read_zero_block:
	lea	ix, iy + fat.buffer
	ld	a, (ix + 12)
	cp	a, (ix + 16)			; ensure 512 byte blocks and 2 FATs
	jr	z, fat_Open.goodfat
	ld	hl, FAT_ERROR_INVALID_FILESYSTEM
	pop	ix
	ret
fat_Open.goodfat:
	ld	a, (ix + 39)
	or	a, a				; can't support reallllly big drives (BPB_FAT32_FATSz32 high)
	jr	z, fat_Open.goodsize
	ld	hl, FAT_ERROR_INVALID_SIZE
	pop	ix
	ret
fat_Open.goodsize:
	xor	a, a
	ld	b, a
	ld	hl, (ix + 14)
	ex.s	de, hl
	ld	(iy + fat.fat_pos), de
	ld	hl, (ix + 36)			; BPB_FAT32_FATSz32
	ld	(iy + fat.fat_size), hl
	add	hl, hl				; * num fats
	adc	a, b
	add	hl, de				; data region
	adc	a, b				; get carry if needed
	ld	(iy + fat.data_region), hl
	ld	(iy + fat.data_region + 3), a
	push	af
	ex	de, hl
	ld	hl, (ix + 44)			; BPB_FAT32_RootClus
	ld	a, (ix + 44 + 3)
	ld	bc, 2
	or	a, a
	sbc	hl, bc
	jr	nc, fat_Open.nocarry
	dec	a
fat_Open.nocarry:
	ld	c, (ix + 13)
	ld	(iy + fat.blocks_per_cluster), c
	jr	fat_Open.enter
fat_Open.multiply:
	add	hl, hl
	adc	a, a
fat_Open.enter:
	rr	c
	jr	nc, fat_Open.multiply
	pop	bc
	add	hl, de				; bude = data region
	adc	a, b				; root directory location
	ld	(iy + fat.root_dir_pos), hl
	ld	(iy + fat.root_dir_pos + 3), a
	ld	de, (ix + 48)
	ex.s	de, hl
	ld	(iy + fat.fs_info), hl
	xor	a, a
	call	util_read_fat_block
	jr	z, fat_Open.check_magic
	ld	hl, FAT_ERROR_RW_FAILED
	pop	ix
	ret
fat_Open.check_magic:
	call	util_checkmagic
	jr	z, fat_Open.goodmagic
	ld	hl, FAT_ERROR_INVALID_MAGIC
	pop	ix
	ret
fat_Open.goodmagic:
	ld	hl, (ix + 0)			; ix should still point to the temp block...
	ld	bc, 0x615252			; don't bother comparing $41 byte...
	xor	a, a
	sbc	hl, bc
	jr	z, fat_Open.goodsig
	ld	hl, FAT_ERROR_INVALID_SIGNATURE
	pop	ix
	ret
fat_Open.goodsig:
	scf
	sbc	hl, hl
	ex	de, hl
	lea	hl, iy + fat.buffer
	ld	bc, 488
	add	hl, bc				; invalidate free space
	ld	(hl), de
	inc	hl
	inc	hl
	inc	hl
	ld	(hl), e
	ld	hl, (iy + fat.fs_info)		; a is zero
	call	util_write_fat_block
	pop	ix
	ld	hl, FAT_ERROR_RW_FAILED
	ret	nz
	xor	a, a
	sbc	hl, hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_Close:
; Deinitialize the FAT partition
; Arguments:
;  sp + 3 : fat struct
; Returns:
;  FAT_SUCCESS on success
	pop	de
	ex	(sp), iy
	push	de
	xor	a, a
	sbc	hl, hl
	call	util_read_fat_block
	ld	hl, FAT_ERROR_RW_FAILED
	ret	nz
	lea	hl, iy + fat.buffer
	ld	de, 0x41
	add	hl, de
	res	0, (hl)				; clear dirty bit
	xor	a, a
	sbc	hl, hl
	call	util_write_fat_block
	ld	hl, FAT_ERROR_RW_FAILED
	ret	nz
	xor	a, a
	sbc	hl, hl				; return success
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
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 9)	; dir struct
	ld	(fat_OpenDir.fatdir), hl
	ld	de, (iy + 6)	; dir path
	ld	iy, (iy + 3)	; fat struct
	ld	a, (de)
	cp	a, 0x2f
	jp	nz, fat_OpenDir.path_error
	inc	de
	ld	a, (de)
	dec	de
	or	a, a
	jr	nz, fat_OpenDir.notroot
	ld	hl, (iy + fat.root_dir_pos)
	ld	a, (iy + fat.root_dir_pos + 3)
	call	util_block_to_cluster
	jr	fat_OpenDir.gotcluster
fat_OpenDir.notroot:
	call	util_locate_entry
	jr	z, fat_OpenDir.path_error
	push	iy
	push	de
	pop	iy
	call	util_get_entry_first_cluster
	pop	iy
fat_OpenDir.gotcluster:
	compare_auhl_zero
	jr	nz, fat_OpenDir.findcluster
	ld	hl, FAT_ERROR_INVALID_CLUSTER
	ret
fat_OpenDir.findcluster:
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_cluster_to_block
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	call	util_read_fat_block		; read the first block for cache
	jr	z, fat_OpenDir.success
	ld	hl, FAT_ERROR_RW_FAILED
	ret
fat_OpenDir.success:
	push	ix
	ld	ix, 0
.equ fat_OpenDir.fatdir, .-3
	ld	(ix + fatDir.fat), iy
	ld	a, (iy + fat.blocks_per_cluster)
	ld	(ix + fatDir.blocks_per_cluster), a
	ld	(ix + fatDir.cluster_block), a
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	ld	(ix + fatDir.working_cluster), hl
	ld	(ix + fatDir.working_cluster + 3), a
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	ld	(ix + fatDir.working_block), hl
	ld	(ix + fatDir.working_block + 3), a
	ld	a, 0xaa
	ld	(ix + fatDir.open), a		; magic number
	xor	a, a
	sbc	hl, hl				; return success
	ld	(ix + fatDir.block_offset), hl
	pop	ix
	ret
fat_OpenDir.path_error:
	ld	hl, FAT_ERROR_INVALID_PATH
	ret

;-------------------------------------------------------------------------------
fat_ReadDir:
; Opens a directory for reading contents
; Arguments:
;  sp + 3 : dir struct
;  sp + 6 : entry struct
; Returns:
;  FAT_SUCCESS on success
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)	; entry struct
	ld	(fat_ReadDir.entry), hl
	ld	iy, (iy + 3)	; dir struct
	ld	a, (iy + fatDir.open)
	cp	a, 0xaa		; check for magic open byte
	jr	z, fat_ReadDir.open
	ld	hl, FAT_ERROR_NO_MORE_ENTRIES
	cp	a, 0xbb
	ret	z
	ld	hl, FAT_ERROR_INVALID_PARAM
	ret
fat_ReadDir.open:

	; for speed, check if the currently cached block is available

	ld	a, (iy + fatDir.block_offset)
	push	ix
	ld	ix, (iy + fatDir.fat)
	lea	hl, ix + fat.working_block
	cp	a, 16				; get next cluster if at end
	pop	ix
	jp	z, fat_ReadDir.next_block
	lea	de, iy + fatDir.working_block
	ld	b, 4
fat_ReadDir.check_cache:
	ld	a, (de)
	cp	a, (hl)
	jr	nz, fat_ReadDir.read_block
	inc	hl
	inc	de
	djnz	fat_ReadDir.check_cache
	jr	fat_ReadDir.skip_read
fat_ReadDir.read_block:
	push	iy
	ld	hl, (iy + fatDir.working_block)
	ld	a, (iy + fatDir.working_block + 3)
	ld	iy, (iy + fatDir.fat)
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	call	util_read_fat_block		; read the block for cache
	pop	iy
	jr	z, fat_ReadDir.skip_read
	ld	hl, FAT_ERROR_RW_FAILED
	ret
fat_ReadDir.skip_read:
	ld	de, (iy + fatDir.block_offset)
	ld	hl, 16
	or	a, a
	sbc	hl, de
	ld	b, l				; num entries left in the block
	ex	de, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl				; shift by 32 multiple
	push	ix
	lea	ix, iy+0
	ld	iy, (iy + fatDir.fat)
	lea	de, iy + fat.buffer
	add	hl, de				; pointer to entry
	push	hl
	pop	iy

fat_ReadDir.findentry:
	ld	a, (iy)
	or	a, a
	jr	nz, fat_ReadDir.continue
	ld	(ix + fatDir.open), 0xbb		; done marker
	ld	hl, (fat_ReadDir.entry)
	ld	bc, fatDirEntry_size
	xor	a, a
	call	ti.MemSet
	xor	a, a
	sbc	hl, hl				; success, zeroed entry at end
	pop	ix
	ret
fat_ReadDir.continue:
	inc	(ix + fatDir.block_offset)
	cp	a, 0xe5
	jr	z, fat_ReadDir.skip
	cp	a, 0x20
	jr	z, fat_ReadDir.skip
	ld	a, (iy + 11)
	tst	a, 8
	jr	z, fat_ReadDir.foundentry
fat_ReadDir.skip:
	lea	iy, iy + 32
	djnz	fat_ReadDir.findentry

	lea	iy, ix+0
	pop	ix

	; handle the next block in the cluster
fat_ReadDir.next_block:
	ld	hl, (iy + fatDir.working_block)
	ld	a, (iy + fatDir.working_block + 3)
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	ld	(iy + fatDir.working_block), hl
	ld	(iy + fatDir.working_block + 3), a
	xor	a, a
	ld	(iy + fatDir.block_offset), a
	dec	(iy + fatDir.cluster_block)
	jp	nz, fat_ReadDir.read_block

	; find the next cluster if at end of current cluster

	ld	hl, (iy + fatDir.working_cluster)
	ld	a, (iy + fatDir.working_cluster + 3)
	push	iy
	ld	iy, (iy + fatDir.fat)
	call	util_next_cluster
	pop	iy
	compare_auhl_zero
	jr	nz, fat_ReadDir.foundcluster
	ld	(iy + fatDir.open), 0xbb		; done marker
	ld	hl, FAT_ERROR_NO_MORE_ENTRIES
	ret
fat_ReadDir.foundcluster:
	ld	(iy + fatDir.working_cluster), hl
	ld	(iy + fatDir.working_cluster + 3), a
	push	iy
	ld	iy, (iy + fatDir.fat)
	call	util_cluster_to_block
	pop	iy
	ld	(iy + fatDir.working_block), hl
	ld	(iy + fatDir.working_block + 3), a
	ld	a, (iy + fatDir.blocks_per_cluster)
	ld	(iy + fatDir.cluster_block), a
	jp	fat_ReadDir.read_block

fat_ReadDir.foundentry:
	pop	hl				; pop ix
	push	hl
	ld	ix, 0
.equ fat_ReadDir.entry, .-3
	lea	de, ix + 0
	lea	hl, iy + 0
	call	util_get_name
	ld	a, (iy + 11)
	ld	(ix + fatDirEntry.attrib), a
	ld	hl, (iy + 28)
	ld	a, (iy + 28 + 3)
	ld	(ix + fatDirEntry.entrysize), hl
	ld	(ix + fatDirEntry.entrysize + 3), a
	pop	ix
	xor	a, a
	sbc	hl, hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_CloseDir:
; Closes an open directory handle
; Arguments:
;  sp + 3 : dir struct
; Returns:
;  FAT_SUCCESS on success
	ld	iy, 0
	add	iy, sp
	ld	iy, (iy + 3)
	xor	a, a
	ld	(iy + fatDir.open), a
	sbc	hl, hl				; return success
	ret

;-------------------------------------------------------------------------------
fat_GetVolumeLabel:
; Returns the volume label if it exists
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : volume label (8.3 format) storage
; Returns:
;  FAT_SUCCESS on success, and FAT_ERROR_NO_VOLUME_LABEL
	pop	de
	pop	iy
	push	iy
	push	de
	ld	hl, (iy + fat.root_dir_pos)
	ld	a, (iy + fat.root_dir_pos + 3)
	call	util_block_to_cluster
fat_GetVolumeLabel.findcluster:
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_cluster_to_block
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	ld	b, (iy + fat.blocks_per_cluster)
fat_GetVolumeLabel.findblock:
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	push	bc
	call	util_read_fat_block
	jr	z, fat_GetVolumeLabel.rd_success
	pop	bc
	ld	hl, FAT_ERROR_RW_FAILED
	ret
fat_GetVolumeLabel.rd_success:
	lea	hl, iy + fat.buffer + 11
	ld	b, 16
	ld	de, 32
fat_GetVolumeLabel.findentry:
	ld	a, (hl)
	and	a, 8
	jr	nz, fat_GetVolumeLabel.foundlabel
	add	hl, de
	djnz	fat_GetVolumeLabel.findentry
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	pop	bc
	djnz	fat_GetVolumeLabel.findblock
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	call	util_next_cluster
	compare_auhl_zero
	jr	nz, fat_GetVolumeLabel.findcluster
fat_GetVolumeLabel.notfound:
	ld	hl, FAT_ERROR_NO_VOLUME_LABEL
	ret
fat_GetVolumeLabel.foundlabel:
	pop	bc
	ld	de, -11
	add	hl, de
	pop	bc
	pop	iy
	pop	de
	push	de
	push	iy
	push	bc
	ld	bc, 11
	ldir
	jr	fat_GetVolumeLabel.enterremovetrailingspaces
fat_GetVolumeLabel.removetrailingspaces:
	ld	a, (de)
	cp	a, 0x20
	jr	nz, fat_GetVolumeLabel.done
fat_GetVolumeLabel.enterremovetrailingspaces:
	xor	a, a
	ld	(de), a
	dec	de
	jr	fat_GetVolumeLabel.removetrailingspaces
fat_GetVolumeLabel.done:
	xor	a, a
	sbc	hl, hl				; return success
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
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 6)
	push	iy
	ld	iy, (iy + 3)
	call	util_locate_entry
	pop	iy
	jr	nz, fat_OpenFile.found
	ld	hl, FAT_ERROR_NOT_FOUND
	ret
fat_OpenFile.found:
	ld	bc, (iy + 3)
	ld	iy, (iy + 12)
	ld	(iy + fatFile.fat), bc
	ld	(iy + fatFile.entry_pointer), de
	ld	(iy + fatFile.entry_block), hl
	ld	(iy + fatFile.entry_block + 3), a
	push	ix
	push	bc
	pop	ix
	ld	a, (ix + fat.blocks_per_cluster)
	ld	(iy + fatFile.blocks_per_cluster), a	; for faster access
	pop	ix
fat_OpenFile.enter:
	push	iy
	ld	iy, (iy + fatFile.entry_pointer)
	ld	a, (iy + 20 + 1)
	ld	hl, (iy + 20 - 2)
	ld	l, (iy + 26 + 0)
	ld	h, (iy + 26 + 1)			; first cluster
	pop	iy
	ld	(iy + fatFile.first_cluster), hl
	ld	(iy + fatFile.first_cluster + 3), a
	ld	(iy + fatFile.current_cluster), hl
	ld	(iy + fatFile.current_cluster + 3), a
	compare_auhl_zero
	jr	z, fat_OpenFile.notallocated
	push	iy
	ld	iy, (iy + fatFile.entry_pointer)	; get file size
	ld	hl, (iy + 28)
	ld	a, (iy + 28 + 3)
	pop	iy
fat_OpenFile.notallocated:
	ld	(iy + fatFile.file_size), hl
	ld	(iy + fatFile.file_size + 3), a
	call	util_ceil_byte_size_to_block_size
	ld	(iy + fatFile.block_count), hl
	ld	(iy + fatFile.block_count + 3), a
	ld	hl, (iy + fatFile.current_cluster)
	ld	a, (iy + fatFile.current_cluster + 3)
	push	iy
	ld	iy, (iy + fatFile.fat)
	call	util_cluster_to_block
	pop	iy
	ld	(iy + fatFile.current_block), hl
	ld	(iy + fatFile.current_block + 3), a
	xor	a, a
	sbc	hl, hl
	ld	(iy + fatFile.block_index), hl		; return success
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
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 6)
	push	iy
	ld	iy, (iy + 3)
	ld	hl, (iy + fatFile.entry_block)
	ld	a, (iy + fatFile.entry_block + 3)
	ld	de, (iy + fatFile.entry_pointer)
	ld	iy, (iy + fatFile.fat)
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	ld	(iy + fat.working_entry), de
	push	de
	pop	iy
	ld	a, (iy + 20 + 1)			; start at first cluster, and walk the chain
	ld	hl, (iy + 20 - 2)			; until the number of clusters is allocated
	ld	l, (iy + 26 + 0)
	ld	h, (iy + 26 + 1)
	ld	(fat_SetFileSize.currentcluster), hl
	ld	(fat_SetFileSize.currentcluster + 3), a
	pop	iy
	ld	bc, (iy + 6)			; get new file size
	ld	a, (iy + 9)
	push	iy
	ld	iy, (iy + 3)
	ld	iy, (iy + fatFile.fat)
	push	iy
	ld	iy, (iy + fat.working_entry)
	ld	hl, (iy + 28)
	ld	e, (iy + 28 + 3)
	ld	(iy + 28), bc			; otherwise, directly store new size
	ld	(iy + 28 + 3), a
	pop	iy
	ld	(iy + fat.working_size), bc
	ld	(iy + fat.working_size + 3), a
	pop	iy				; get current file size
	call	ti._lcmpu
	jp	z, fat_SetFileSize.success			; if same size, just return
	jr	c, fat_SetFileSize.makelarger
fat_SetFileSize.makesmaller:
	call	fat_SetFileSize.writeentry
	compare_hl_zero
	jr	nz, fat_SetFileSize.notzerofile
	push	iy
	ld	iy, (iy + 3)
	ld	iy, (iy + fatFile.fat)
	ld	hl, (fat_SetFileSize.currentcluster)
	ld	a, (fat_SetFileSize.currentcluster + 3)
	call	util_dealloc_cluster_chain	; deallocate all clusters
	pop	iy
	jp	nz, fat_SetFileSize.write_error
	jp	fat_SetFileSize.success
fat_SetFileSize.notzerofile:
	push	hl
	pop	bc
	ld	hl, (fat_SetFileSize.currentcluster)
	ld	a, (fat_SetFileSize.currentcluster + 3)
	compare_auhl_zero
	jp	z, fat_SetFileSize.success
	push	iy
	ld	iy, (iy + 3)
	ld	iy, (iy + fatFile.fat)
	dec	bc
	jr	fat_SetFileSize.entertraverseclusters
fat_SetFileSize.traverseclusters:
	push	bc
	call	util_next_cluster
	compare_auhl_zero
	pop	bc
	jr	nz, fat_SetFileSize.goodchain			; the filesystem is screwed up
	ld	hl, FAT_ERROR_CLUSTER_CHAIN
	ret
fat_SetFileSize.goodchain:
	dec	bc
fat_SetFileSize.entertraverseclusters:
	compare_bc_zero
	jr	nz, fat_SetFileSize.traverseclusters
	call	util_set_new_eoc_cluster	; mark this cluster as unused
	call	util_dealloc_cluster_chain	; deallocate all other clusters
	pop	iy
	jp	nz, fat_SetFileSize.write_error
	jr	fat_SetFileSize.success
fat_SetFileSize.makelarger:
	call	fat_SetFileSize.writeentry			; get number of clusters there needs to be
	compare_hl_zero
	jr	z, fat_SetFileSize.success
fat_SetFileSize.allocateclusters:
	push	hl
	push	iy
	ld	iy, (iy + 3)
	ld	iy, (iy + fatFile.fat)
	ld	hl, (fat_SetFileSize.currentcluster)
	ld	a, (fat_SetFileSize.currentcluster + 3)
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_next_cluster
	compare_auhl_zero
	jr	nz, fat_SetFileSize.alreadyallocated
	call	util_alloc_cluster
fat_SetFileSize.alreadyallocated:
	ld	(fat_SetFileSize.currentcluster), hl
	ld	(fat_SetFileSize.currentcluster + 3), a
	compare_auhl_zero
	pop	iy
	pop	hl
	jr	nz, fat_SetFileSize.goodalloc
	ld	hl, FAT_ERROR_FAILED_ALLOC
	ret
fat_SetFileSize.goodalloc:
	dec	hl
	compare_hl_zero
	jr	nz, fat_SetFileSize.allocateclusters
	;jq	.success
fat_SetFileSize.success:
	ld	iy, (iy + 3)
	ld	hl, (iy + fatFile.entry_block)	; read the entry again for open
	ld	a, (iy + fatFile.entry_block + 3)
	push	iy
	ld	iy, (iy + fatFile.fat)
	call	util_read_fat_block
	pop	iy
	jr	nz, fat_SetFileSize.write_error
	jp	fat_OpenFile.enter			; reopen the file
fat_SetFileSize.writeentry:
	push	iy
	ld	iy, (iy + 3)
	ld	iy, (iy + fatFile.fat)
	ld	hl, (iy + fat.working_size)
	ld	a, (iy + fat.working_size + 3)
	compare_auhl_zero
	jr	nz, fat_SetFileSize.writenotzero
	push	ix
	ld	ix, (iy + fat.working_entry)
	xor	a, a
	ld	(ix + 20 + 0), a			; remove first cluster if zero
	ld	(ix + 20 + 1), a
	ld	(ix + 26 + 0), a
	ld	(ix + 26 + 1), a
	pop	ix
fat_SetFileSize.writenotzero:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_write_fat_block		; write the new size
	jr	z, fat_SetFileSize.writegood
	pop	iy
fat_SetFileSize.write_error:
	ld	hl, FAT_ERROR_RW_FAILED
	ret
fat_SetFileSize.writegood:
	ld	hl, (iy + fat.working_size)
	ld	a, (iy + fat.working_size + 3)
	call	util_ceil_byte_size_to_cluster_size
	pop	iy
	ret

fat_SetFileSize.currentcluster:
	.d32	0

;-------------------------------------------------------------------------------
fat_GetFileSize:
; Gets the size of the file
; Arguments:
;  sp + 3 : fat file struct
; Returns:
;  File size in bytes
	pop	de
	ex	(sp), iy
	push	de
	ld	hl, (iy + fatFile.file_size)
	ld	e, (iy + fatFile.file_size + 3)
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
	ld	de, (iy + fatFile.block_count)
	or	a, a
	sbc	hl, de
	add	hl, de
	jp	nc, fat_SetFileBlockOffset.invalid
	ld	de, (iy + fatFile.block_index)
	xor	a, a
	sbc	hl, de
	ret	z				; if at the same block position, done (return 0)
	add	hl, de				; hl = new block_index, de = current block_index

	; check if block is within current cluster
	; we can optimize by just changing the block position
	ld	(iy + fatFile.block_index), hl
	sub	a, (iy + fatFile.blocks_per_cluster)
	ld	c, a				; mask for number of blocks
	and	a, l
	ld	l, a
	ld	a, c
	and	a, e
	ld	b, e
	ld	e, a
	or	a, a
	sbc	hl, de				; hl - de = number of cluster blocks to advance by
	jr	c, fat_SetFileBlockOffset.restartchain			; requires a previous cluster, restart the chain
	jr	nz, fat_SetFileBlockOffset.nextclusters
fat_SetFileBlockOffset.withincluster:
	ld	e, b
	ld	hl, (iy + fatFile.block_index)
	or	a, a
	sbc	hl, de
	ld	de, (iy + fatFile.current_block)	; need to move the current block up or down
	ld	a, (iy + fatFile.current_block + 3)
	ld	bc, 0x800000
	add	hl, bc
	sbc	a, c
	add	hl, bc
	add	hl, de
	adc	a, c
	ld	(iy + fatFile.current_block), hl
	ld	(iy + fatFile.current_block + 3), a
	xor	a, a
	sbc	hl, hl
	ret					; just changed block position, no need to move clusters (return 0)

fat_SetFileBlockOffset.nextclusters:
	ld	a, (iy + fatFile.blocks_per_cluster)
	dec	a
	and	a, (iy + fatFile.block_index)
	ld	bc, 0
	ld	c, a				; bc = offset of block in last cluster
	add	hl, bc
	jr	fat_SetFileBlockOffset.followchain
fat_SetFileBlockOffset.restartchain:
	ld	hl, (iy + fatFile.first_cluster)
	ld	a, (iy + fatFile.first_cluster + 3)
	ld	(iy + fatFile.current_cluster), hl
	ld	(iy + fatFile.current_cluster + 3), a
	ld	hl, (iy + fatFile.block_index)
fat_SetFileBlockOffset.followchain:
	ld	c, (iy + fatFile.blocks_per_cluster)
	ld	a, c
	dec	a
	and	a, l
	ld	(fat_SetFileBlockOffset.cluster_block), a
	ld	a, c
fat_SetFileBlockOffset.divloop:
	add	hl, hl
	rla
	jr	nc, fat_SetFileBlockOffset.divloop
	push	af
	inc	sp
	push	hl
	inc	sp
	pop	bc
	inc	sp
	ld	hl, (iy + fatFile.current_cluster)
	ld	a, (iy + fatFile.current_cluster + 3)
	jr	fat_SetFileBlockOffset.entergetpos
fat_SetFileBlockOffset.getclusterpos:
	push	bc
	push	iy
	ld	iy, (iy + fatFile.fat)
	call	util_next_cluster
	pop	iy
	pop	bc
	compare_hl_zero
	jr	z, fat_SetFileBlockOffset.chainfailed
	dec	bc
fat_SetFileBlockOffset.entergetpos:
	compare_bc_zero
	jr	nz, fat_SetFileBlockOffset.getclusterpos
	ld	(iy + fatFile.current_cluster), hl
	ld	(iy + fatFile.current_cluster + 3), a
	push	iy
	ld	iy, (iy + fatFile.fat)
	call	util_cluster_to_block
	pop	iy
	ld	de, 0
.equ fat_SetFileBlockOffset.cluster_block, .-3
	add	hl, de
	adc	a, d
	ld	(iy + fatFile.current_block), hl
	ld	(iy + fatFile.current_block + 3), a
fat_SetFileBlockOffset.success:
	xor	a, a
	sbc	hl, hl
	ret
fat_SetFileBlockOffset.invalid:
	ld	hl, FAT_ERROR_INVALID_POSITION
	ret
fat_SetFileBlockOffset.chainfailed:
	ld	hl, FAT_ERROR_CLUSTER_CHAIN
	ret

;-------------------------------------------------------------------------------
fat_GetFileBlockOffset:
; Gets the file's block position
; Arguments:
;  sp + 3 : FAT File structure type
; Returns:
;  Block position in file
	pop	de
	ex	(sp), hl
	push	de
	compare_hl_zero
	ret	z
	push	hl
	pop	iy
	ld	hl, (iy + fatFile.block_index)
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
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 6)
	push	iy
	ld	iy, (iy + 3)
	call	util_locate_entry
	pop	iy
	jr	z, fat_SetAttrib.invalidpath
	push	hl
	push	af
	ld	a, (iy + 9)
	push	de
	pop	iy
	ld	(iy + 11), a
	pop	af
	pop	hl
	call	util_write_fat_block
	ld	hl, FAT_ERROR_RW_FAILED
	ret	nz
	xor	a, a
	sbc	hl, hl
	ret
fat_SetAttrib.invalidpath:
	ld	hl, FAT_ERROR_INVALID_PATH
	ret

;-------------------------------------------------------------------------------
fat_GetAttrib:
; Gets the attributes of the path
; Arguments:
;  sp + 3 : fat struct
;  sp + 6 : file path
; Returns:
;  File attribute byte
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 6)
	ld	iy, (iy + 3)
	call	util_locate_entry
	jr	z, fat_GetAttrib.invalidpath
	push	de
	pop	iy
	ld	a, (iy + 11)
	ret
fat_GetAttrib.invalidpath:
	ld	hl, FAT_ERROR_INVALID_PATH
	ret

;-------------------------------------------------------------------------------
fat_CloseFile:
; Closes an open file handle
; Arguments:
;  sp + 3 : fat struct
; Returns:
;  FAT_SUCCESS on success
	xor	a, a
	sbc	hl, hl
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
	ld	hl, util_read_fat_multiple_blocks
	ld	(util_fat_read_write.block_func), hl
	jp	util_fat_read_write

;-------------------------------------------------------------------------------
fat_WriteFile:
; Writes a blocks to an open file handle
; Arguments:
;  sp + 3 : FAT File structure type
;  sp + 6 : Number of blocks to write
;  sp + 9 : Buffer to write
; Returns:
;  FAT_SUCCESS on success
	ld	hl, util_write_fat_multiple_blocks
	ld	(util_fat_read_write.block_func), hl
	jp	util_fat_read_write

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
	lea	hl, iy + fat.buffer
	push	hl
	pop	de
	inc	de
	ld	bc, 512
	ld	(hl), c
	ldir
	pop	hl
	call	util_cluster_to_block
	ld	b, (iy + fat.blocks_per_cluster)
util_zerocluster.zerome:
	push	bc
	push	af
	push	hl
	call	util_write_fat_block
	pop	hl
	jr	nz, util_zerocluster.error
	pop	af
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	pop	bc
	djnz	util_zerocluster.zerome
	xor	a, a
	ret
util_zerocluster.error:
	pop	hl
	pop	hl
	xor	a, a
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
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 9)
	call	util_validate_fat_name
	ld	hl, FAT_ERROR_INVALID_NAME
	ret	z
	ld	hl, -512
	add	hl, sp
	ld	sp, hl				; temporary space for concat
	ex	de, hl
	push	de
	ld	hl, (iy + 6)
	compare_hl_zero
	jr	z, fat_Create.rootdirpath
	call	ti.StrCopy
fat_Create.rootdirpath:
	ld	a, 0x2f
	ld	(de), a
	inc	de
	ld	hl, (iy + 9)
	call	ti.StrCopy
	pop	de
	push	iy
	ld	iy, (iy + 3)
	call	util_locate_entry
	pop	iy
	jp	nz, fat_Create.alreadyexists
	ld	hl, (iy + 6)
	inc	hl				; todo: check for '/' or '.'?
	ld	a, (hl)
	or	a, a
	jr	nz, fat_Create.notroot
	push	iy
	ld	iy, (iy + 3)
	push	iy
	call	util_alloc_entry_root
	pop	iy
	ld	(iy + fat.working_prev_entry), de
	ld	(iy + fat.working_entry), de
	ld	bc, 0
	ld	(iy + fat.working_prev_cluster), bc
	ld	(iy + fat.working_prev_cluster + 3), c
	pop	iy
	jr	fat_Create.createfile
fat_Create.notroot:
	ld	de, (iy + 6)
	push	iy
	ld	iy, (iy + 3)
	call	util_locate_entry
	pop	iy
	jp	z, fat_Create.invalidpath
	push	iy
	ld	iy, (iy + 3)
	ld	(iy + fat.working_prev_entry), de
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	push	de
	pop	iy
	ld	a, (iy + 20 + 1)
	ld	hl, (iy + 20 - 2)		; get hlu
	ld	l, (iy + 26 + 0)
	ld	h, (iy + 26 + 1)			; get the entry's cluster
	pop	iy
	push	iy
	ld	iy, (iy + 3)
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	ld	(iy + fat.working_prev_cluster), hl
	ld	(iy + fat.working_prev_cluster + 3), a
	call	util_alloc_entry
	ld	(iy + fat.working_entry), de
	pop	iy
fat_Create.createfile:
	compare_auhl_zero
	jp	z, fat_Create.failedalloc
	push	ix
	push	iy
	ld	de, (iy + 9)
	ld	iy, (iy + 3)
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	ld	hl, (iy + fat.working_entry)
	push	hl
	call	util_get_fat_name
	pop	ix
	pop	iy
	ld	a, (iy + 12)
	ld	(ix + 11), a
	xor	a, a
	sbc	hl, hl
	ld	(ix + 28), hl			; set initial size to zero
	ld	(ix + 28 + 3), a
	ld	(ix + 20), a
	ld	(ix + 21), a
	ld	(ix + 26), a
	ld	(ix + 27), a
	pop	ix
	push	iy
	ld	iy, (iy + 3)
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_write_fat_block
	pop	iy
	jp	nz, fat_Create.rw_error
	bit	4, (iy + 12)
	jp	z, fat_Create.notdirectory
fat_Create.createdirectory:
	push	iy
	ld	iy, (iy + 3)
	xor	a, a
	sbc	hl, hl
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_alloc_entry.enter
	ld	(iy + fat.working_next_entry), de
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	call	util_block_to_cluster
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_zerocluster		; zero the damn cluster >:(
	jp	nz, fat_Create.rw_errorpop
	ld	hl, (iy + fat.working_next_entry)
	ld	(hl), 0x2e			; buffer is zero from cluster zeroing
	ld	b, 10
fat_Create.setsingledot:
	inc	hl
	ld	(hl), 0x20
	djnz	fat_Create.setsingledot
	inc	hl
	ld	(hl), 0x10
	push	ix
	ld	ix, (iy + fat.working_next_entry)
	xor	a, a
	sbc	hl, hl
	ld	(ix + 12), a
	ld	de, (iy + fat.working_cluster + 2)
	ld	(ix + 20), e
	ld	(ix + 21), d
	ld	de, (iy + fat.working_cluster + 0)
	ld	(ix + 26), e
	ld	(ix + 27), d
	ld	(ix + 28), hl
	ld	(ix + 31), a
	pop	ix
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_write_fat_block
	jp	nz, fat_Create.rw_errorpop
	ld	de, (iy + fat.working_prev_entry)
	ld	(iy + fat.working_entry), de
	call	util_alloc_entry
	ld	(iy + fat.working_next_entry), de
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	call	util_read_fat_block
	jr	nz, fat_Create.rw_errorpop
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_block_to_cluster
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	ld	hl, (iy + fat.working_next_entry)
	ld	(hl), 0x2e
	inc	hl
	ld	(hl), 0x2e
	ld	b, 9
fat_Create.setdoubledot:
	inc	hl
	ld	(hl), 0x20
	djnz	fat_Create.setdoubledot
	inc	hl
	ld	(hl), 0x10
	push	ix
	ld	ix, (iy + fat.working_next_entry)
	xor	a, a
	sbc	hl, hl
	ld	(ix + 12), 0x00
	ld	de, (iy + fat.working_prev_cluster + 2)
	ld	(ix + 20), e
	ld	(ix + 21), d
	ld	de, (iy + fat.working_prev_cluster + 0)
	ld	(ix + 26), e
	ld	(ix + 27), d
	ld	(ix + 28), hl
	ld	(ix + 31), a
	ld	(ix + 32 + 0), a
	ld	(ix + 32 + 11), a		; zero next entry, mark as eoc
	pop	ix
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_write_fat_block
	jr	nz, fat_Create.rw_errorpop
	pop	iy
fat_Create.notdirectory:
	ld	e, FAT_SUCCESS
	jr	fat_Create.restorestack
fat_Create.failedalloc:
	ld	e, FAT_ERROR_FAILED_ALLOC
	jr	fat_Create.restorestack
fat_Create.alreadyexists:
	ld	e, FAT_ERROR_EXISTS
	jr	fat_Create.restorestack
fat_Create.invalidpath:
	ld	e, FAT_ERROR_INVALID_PATH
	jr	fat_Create.restorestack
fat_Create.rw_errorpop:
	pop	hl
fat_Create.rw_error:
	ld	e, FAT_ERROR_RW_FAILED
fat_Create.restorestack:
	ld	hl, 512
	ld	d, l
	add	hl, sp
	ld	sp, hl
	ex.s	de, hl
	ret

;-------------------------------------------------------------------------------
fat_Delete:
; Deletes a file and deallocates the spaced used by it on disk
; Arguments:
;  sp + 3 : FAT structure type
;  sp + 6 : Path
; Returns:
;  FAT_SUCCESS on success
	ld	iy, 0
	add	iy, sp
	push	ix
	call	fat_Delete.enter
	pop	ix
	ret
fat_Delete.enter:
	ld	de, (iy + 6)
	ld	iy, (iy + 3)
	push	iy
	call	util_locate_entry
	pop	iy
	jr	z, fat_Delete.invalidpath
	push	de
	pop	ix
	bit	4, (ix + 11)
	jr	z, fat_Delete.normalfile
fat_Delete.directory:
	push	hl
	push	af
	push	ix
	ld	a, (ix + 20 + 1)
	ld	hl, (ix + 20 - 2)		; get hlu
	ld	l, (ix + 26 + 0)
	ld	h, (ix + 26 + 1)
	call	util_is_directory_empty
	pop	ix
	pop	de
	pop	hl
	ld	a, d
	jr	nz, fat_Delete.dirnotempty
	push	ix
	push	hl
	push	af
	call	util_read_fat_block		; reread entry block
	pop	de
	pop	hl
	ld	a, d
	pop	ix				; a directory can now be treated as a normal file
	jr	nz, fat_Delete.rw_error
fat_Delete.normalfile:
	ld	(ix + 11), 0
	ld	(ix + 0), 0xe5			; mark entry as deleted
	push	ix
	call	util_write_fat_block
	pop	ix
	jr	nz, fat_Delete.rw_error
	ld	a, (ix + 20 + 1)
	ld	hl, (ix + 20 - 2)		; get hlu
	ld	l, (ix + 26 + 0)
	ld	h, (ix + 26 + 1)
	call	util_dealloc_cluster_chain
	jr	nz, fat_Delete.rw_error
	ret
fat_Delete.invalidpath:
	ld	hl, FAT_ERROR_INVALID_PATH
	ret
fat_Delete.rw_error:
	ld	hl, FAT_ERROR_RW_FAILED
	ret
fat_Delete.dirnotempty:
	ld	hl, FAT_ERROR_DIRECTORY_NOT_EMPTY
	ret

;-------------------------------------------------------------------------------
util_get_entry_first_cluster:
	ld	a, (iy + 20 + 1)
	ld	hl, (iy + 20 - 2)		; get hlu
	ld	l, (iy + 26 + 0)
	ld	h, (iy + 26 + 1)			; get the entry's cluster
	ret

;-------------------------------------------------------------------------------
util_end_of_chain:
; inputs
;   auhl: cluster
; outputs
;   flag c set if end of cluster chain
; perserves
;   hl, af, bc, de
	push	de
	push	hl
	push	af
	ex	de, hl
	and	a, 0x0f
	ld	hl, 8
	add	hl, de
	ex	de, hl
	adc	a, 0xf0
	pop	de
	pop	hl
	ld	a, d
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
	push	af
	push	hl
	call	util_cluster_entry_to_block
	call	util_read_fat_block
	pop	hl
	pop	de
	ld	a, d
	jr	nz, util_set_new_eoc_cluster.error
	call	util_get_cluster_offset
	ld	a, 0xff				; mark new end of chain
	ld	bc, (hl)
	ld	(hl), a
	inc	hl
	ld	(hl), a
	inc	hl
	ld	(hl), a
	inc	hl
	ld	d, (hl)				; dubc = previous cluster
	ld	(hl), 0x0f			; end of chain marker
	push	bc
	push	de
	pop	af
	pop	hl
	ret
util_set_new_eoc_cluster.error:
	xor	a, a
	sbc	hl, hl
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
	jr	z, util_dealloc_cluster_chain.success
	call	util_end_of_chain
	jr	c, util_dealloc_cluster_chain.success
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_cluster_entry_to_block
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	call	util_read_fat_block
	jr	nz, util_dealloc_cluster_chain.error
util_dealloc_cluster_chain.followchain:
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	call	util_get_cluster_offset
	xor	a, a
	ld	bc, (hl)
	ld	(hl), a
	inc	hl
	ld	(hl), a
	inc	hl
	ld	(hl), a
	inc	hl
	ld	d, (hl)				; dubc = previous cluster
	ld	(hl), a				; zero previous cluster
	push	bc
	push	de
	pop	af				; auhl = previous cluster
	pop	hl
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_end_of_chain		; check if end of chain
	jr	c, util_dealloc_cluster_chain.updatepartialchain
	compare_auhl_zero
	jr	z, util_dealloc_cluster_chain.updatepartialchain
	call	util_cluster_entry_to_block
	ld	e, a
	ld	bc, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	ti._lcmpu
	jr	z, util_dealloc_cluster_chain.followchain
util_dealloc_cluster_chain.updatepartialchain:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_update_fat_table
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	jr	z, util_dealloc_cluster_chain
util_dealloc_cluster_chain.error:
	xor	a, a
	inc	a
	ret
util_dealloc_cluster_chain.success:
	xor	a, a
	ret

; inputs:
;   iy: fat structure
;   iy + working_cluster: previous cluster
;   iy + working_block: entry block
;   iy + working_entry: entry in block
; outputs:
;   auhl: allocated cluster number
util_alloc_cluster:
	xor	a, a
	sbc	hl, hl
util_alloc_cluster.traversefat:
	push	hl
	push	af
	ld	bc, (iy + fat.fat_pos)
	add	hl, bc
	adc	a, 0
	call	util_read_fat_block
	jr	z, util_alloc_cluster.readfatblock
	pop	af
	pop	hl
	jp	util_alloc_cluster.rw_error
util_alloc_cluster.readfatblock:
	push	ix
	lea	ix, iy + fat.buffer - 4
	ld	b, 128
util_alloc_cluster.traverseclusterchain:
	lea	ix, ix + 4
	ld	hl, (ix)
	ld	a, (ix + 3)
	compare_auhl_zero
	jr	z, util_alloc_cluster.unallocatedcluster
	djnz	util_alloc_cluster.traverseclusterchain
	pop	ix
	pop	af
	pop	hl
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	jr	util_alloc_cluster.traversefat
	ret
util_alloc_cluster.unallocatedcluster:
	ld	a, 128
	sub	a, b
	ld	bc, 0
	ld	c, a
	lea	de, ix+0
	ld	a, 0x0f
	scf
	sbc	hl, hl
	ld	(ix), hl
	ld	(ix + 3), a
	pop	ix
	pop	af
	pop	hl
	push	af
	push	hl
	add	hl, hl				; shift auhl by 7 left
	adc	a, a
	add	hl, hl
	adc	a, a
	add	hl, hl
	adc	a, a
	add	hl, hl
	adc	a, a
	add	hl, hl
	adc	a, a
	add	hl, hl
	adc	a, a
	add	hl, hl
	adc	a, a
	add	hl, bc
	adc	a, b				; new cluster
	ld	(iy + fat.working_next_cluster), hl
	ld	(iy + fat.working_next_cluster + 3), a
	pop	hl
	pop	af
	ld	bc, (iy + fat.fat_pos)
	add	hl, bc
	adc	a, 0
	call	util_update_fat_table
	jp	nz, util_alloc_cluster.rw_error
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	compare_auhl_zero
	jr	z, util_alloc_cluster.linkentrytofirstcluster
util_alloc_cluster.linkclusterchain:
	push	hl
	call	util_cluster_entry_to_block
	push	hl
	push	af
	call	util_read_fat_block
	pop	de
	pop	bc
	pop	hl
	jr	nz, util_alloc_cluster.rw_error
	push	bc
	push	de
	call	util_get_cluster_offset
	push	ix
	push	hl
	pop	ix
	ld	hl, (iy + fat.working_next_cluster)
	ld	a, (iy + fat.working_next_cluster + 3)
	ld	(ix), hl
	ld	(ix + 3), a
	pop	ix
	pop	af
	pop	hl
	call	util_update_fat_table
	jr	nz, util_alloc_cluster.rw_error
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	compare_auhl_zero
	jr	nz, util_alloc_cluster.nolinkneeded
util_alloc_cluster.linkentrytofirstcluster:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_read_fat_block
	jr	nz, util_alloc_cluster.rw_error
	push	ix
	ld	ix, (iy + fat.working_entry)
	ld	de, (iy + fat.working_next_cluster + 0)
	ld	(ix + 26), e
	ld	(ix + 27), d
	ld	de, (iy + fat.working_next_cluster + 2)
	ld	(ix + 20), e
	ld	(ix + 21), d
	pop	ix
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_write_fat_block
	jr	nz, util_alloc_cluster.rw_error
util_alloc_cluster.nolinkneeded:
	ld	hl, (iy + fat.working_next_cluster)
	ld	a, (iy + fat.working_next_cluster + 3)
	ret
util_alloc_cluster.rw_error:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat structure
;   auhl: block to update in FAT
util_update_fat_table:
	push	af
	push	hl
	call	util_write_fat_block
	pop	hl
	pop	de
	ld	a, d
	ret	nz
	ld	bc, (iy + fat.fat_size)
	add	hl, bc
	adc	a, 0
	call	util_write_fat_block
	ret	nz
	xor	a, a
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
	ld	b, 0
	push	ix
	lea	ix, iy + fat.buffer
	ld	(ix + 0), 0xe5
	ld	(ix + 11), b
	ld	(ix + 20), b
	ld	(ix + 21), b
	ld	(ix + 26), b
	ld	(ix + 27), b
	ld	(ix + 28), b
	ld	(ix + 29), b
	ld	(ix + 30), b
	ld	(ix + 31), b
	ld	(ix + 32), b
	pop	ix
	push	af
	push	hl
	call	util_write_fat_block
	pop	hl
	jr	nz, util_do_alloc_entry.error
	pop	af
	ret
util_do_alloc_entry.error:
	pop	hl
	xor	a, a
	sbc	hl, hl
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
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
util_alloc_entry.enter:
	call	util_cluster_to_block
	compare_auhl_zero
	jr	z, util_alloc_entry.alloccluster
	ld	b, (iy + fat.blocks_per_cluster)
util_alloc_entry.loop:
	push	bc
	push	hl
	push	af
	call	util_read_fat_block
	push	iy
	lea	iy, iy + fat.buffer - 32
	ld	b, 16
util_alloc_entry.findavailentry:
	lea	iy, iy + 32
	ld	a, (iy + 0)
	cp	a, 0xe5				; deleted entry, let's use it!
	jr	z, util_alloc_entry.foundavailentry
	or	a, a
	jr	z, util_alloc_entry.foundavailentry		; end of list, let's allocate here
	djnz	util_alloc_entry.findavailentry
	pop	iy
	pop	af
	pop	hl
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	pop	bc
	djnz	util_alloc_entry.loop
util_alloc_entry.movetonextcluster:
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	call	util_next_cluster
	compare_auhl_zero
	jr	nz, util_alloc_entry.nextclusterisvalid
	push	af
	push	hl
util_alloc_entry.alloccluster:
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	call	util_do_alloc_entry
	lea	de, iy + fat.buffer
	ret
util_alloc_entry.nextclusterisvalid:
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	jr	util_alloc_entry.enter
util_alloc_entry.foundavailentry:
	lea	de, iy+0				; pointer to new entry
	pop	iy			; auhl = block with entry
	pop	af
	pop	hl
	pop	bc
	ret

;-------------------------------------------------------------------------------
; inputs:
;   iy: fat structure
; outputs:
;   auhl: new entry block
;   de: offset in entry block
util_alloc_entry_root:
	xor	a, a
	sbc	hl, hl
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	lea	hl, iy + fat.buffer
	ld	(iy + fat.working_entry), hl
	ld	hl, (iy + fat.root_dir_pos)
	ld	a, (iy + fat.root_dir_pos + 3)
	call	util_block_to_cluster
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	jp	util_alloc_entry.enter

;-------------------------------------------------------------------------------
util_get_name:
	ld	a, 0x2e
	cp	a, (hl)
	jr	z, util_get_name.special
	push	hl
	ld	b, 8
util_get_name.name8:
	ld	a, (hl)
	cp	a, 0x20
	jr	z, util_get_name.next
	ld	(de), a
	inc	hl
	inc	de
	djnz	util_get_name.name8
util_get_name.next:
	pop	hl
	ld	bc, 8
	add	hl, bc
	ld	a, (hl)
	cp	a, 0x20
	jr	z, util_get_name.done			; no extension
	ld	a, 0x2e
	ld	(de), a
	inc	de
	ld	b, 3
util_get_name.name3:
	ld	a, (hl)
	cp	a, 0x20
	jr	z, util_get_name.done
	ld	(de), a
	inc	hl
	inc	de
	djnz	util_get_name.name3
util_get_name.done:
	xor	a, a
	ld	(de), a
	ret
util_get_name.special:
	ld	(de), a
	inc	hl
	inc	de
	cp	a, (hl)
	jr	nz, util_get_name.done
	ld	(de), a
	inc	de
	jr	util_get_name.done

;-------------------------------------------------------------------------------
util_get_fat_name:
; convert name to storage name (covers most cases)
; inputs
;   de: name
;   hl: <output> name (11+1 bytes)
	push	de
	ld	b, 0
util_get_fat_name.loop1:
	ld	a, b
	cp	a, 8
	jr	nc, util_get_fat_name.done1
	ld	a, (de)
	cp	a, 0x2e
	jr	z, util_get_fat_name.done1
	cp	a, 0x2f
	jr	z, util_get_fat_name.done1
	or	a, a
	jr	z, util_get_fat_name.done1
	call	util_toupper
	ld	(hl), a
	inc	de
	inc	hl
	inc	b
	jr	util_get_fat_name.loop1
util_get_fat_name.done1:
	ld	a, b
	cp	a, 8
	jr	nc, util_get_fat_name.elseif
	ld	a, (de)
	or	a, a
	jr	z, util_get_fat_name.elseif
	cp	a, 0x2f
	jr	z, util_get_fat_name.elseif
	ld	a, 8
util_get_fat_name.loop2:
	cp	a, b
	jr	z, util_get_fat_name.fillremaining
	ld	(hl), 0x20
	inc	hl
	inc	b
	jr	util_get_fat_name.loop2
util_get_fat_name.fillremaining:
	inc	de
util_get_fat_name.loop3456:
	ld	a, b
	cp	a, 11
	jr	nc, util_get_fat_name.return
	ld	a, (de)
	or	a, a
	jr	z, util_get_fat_name.other
	cp	a, 0x2f
	jr	z, util_get_fat_name.other
	inc	de
util_get_fat_name.store:
	call	util_toupper
	ld	(hl), a
	inc	hl
	inc	b
	jr	util_get_fat_name.loop3456
util_get_fat_name.other:
	ld	a, 0x20
	jr	util_get_fat_name.store
util_get_fat_name.elseif:
	ld	a, b
	cp	a, 8
	jr	nz, util_get_fat_name.spacefill
	ld	a, (de)
	cp	a, 0x2e
	jr	nz, util_get_fat_name.spacefill
	jr	util_get_fat_name.fillremaining
util_get_fat_name.spacefill:
	ld	a, 11
util_get_fat_name.spacefillloop:
	cp	a, b
	jr	z, util_get_fat_name.return
	ld	(hl), 0x20
	inc	hl
	inc	b
	jr	util_get_fat_name.spacefillloop
util_get_fat_name.return:
	pop	de
	ret

;-------------------------------------------------------------------------------
util_validate_fat_name:
; ensure none of the following characters: * ? . , ; : / \ | + = < > [ ] " \t
; inputs:
;   hl: pointer to null terminated string
; outputs:
;   z set if invalid name
util_validate_fat_name.loop:
	ld	a, (hl)
	or	a, a
	jr	z, util_validate_fat_name.done
	cp	a, 0x2a
	ret	z
	cp	a, 0x3f
	ret	z
	cp	a, 0x2c
	ret	z
	cp	a, 0x3b
	ret	z
	cp	a, 0x3a
	ret	z
	cp	a, 0x2f
	ret	z
	cp	a, 0x5c
	ret	z
	cp	a, 0x7c
	ret	z
	cp	a, 0x2b
	ret	z
	cp	a, 0x3d
	ret	z
	cp	a, 0x3c
	ret	z
	cp	a, 0x3e
	ret	z
	cp	a, 0x5b
	ret	z
	cp	a, 0x5d
	ret	z
	cp	a, 0x22
	ret	z
	cp	a, 0x09
	ret	z
	inc	hl
	jr	util_validate_fat_name.loop
util_validate_fat_name.done:
	inc	a
	ret

;-------------------------------------------------------------------------------
util_toupper:
	cp	a, 0x61
	ret	c
	cp	a, 0x7a+1
	ret	nc
	res	5, a
	ret

;-------------------------------------------------------------------------------
util_get_component_start:
	ld	a, (de)
	or	a, a
	ret	z
	cp	a, 0x2f
	ret	nz
	inc	de
	jr	util_get_component_start

;-------------------------------------------------------------------------------
util_get_next_component:
	ld	a, (de)
	or	a, a
	ret	z
	cp	a, 0x2f
	ret	z
	inc	de
	jr	util_get_next_component

;-------------------------------------------------------------------------------
util_is_directory_empty:
; inputs
;   iy: FAT structure
;   auhl: cluster
; outputs
;   z flag set if directory is empty
util_is_directory_empty.enter:
	ld	(iy + fat.working_cluster), hl
	ld	(iy + fat.working_cluster + 3), a
	call	util_cluster_to_block
	compare_auhl_zero
	ret	z
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	ld	b, (iy + fat.blocks_per_cluster)
util_is_directory_empty.next_block:
	push	bc
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_read_fat_block
	jr	nz, util_is_directory_empty.fail
	push	ix
	ld	b, 16
	lea	ix, iy + fat.buffer - 32
util_is_directory_empty.loop:
	lea	ix, ix + 32
	ld	a, (ix + 11)
	cp	a, 0x0f
	jr	z, util_is_directory_empty.next
	ld	a, (ix + 0)
	or	a, a
	jr	z, util_is_directory_empty.successpop
	cp	a, 0xe5
	jr	z, util_is_directory_empty.next
	cp	a, 0x2e
	jr	z, util_is_directory_empty.next
	cp	a, 0x20
	jr	z, util_is_directory_empty.next
	jr	util_is_directory_empty.failpop
util_is_directory_empty.next:
	djnz	util_is_directory_empty.loop
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	pop	bc
	djnz	util_is_directory_empty.next_block
	ld	hl, (iy + fat.working_cluster)
	ld	a, (iy + fat.working_cluster + 3)
	call	util_next_cluster
	jr	util_is_directory_empty.enter
util_is_directory_empty.successpop:
	pop	bc
	pop	bc
util_is_directory_empty.success:
	xor	a, a
	ret
util_is_directory_empty.failpop:
	pop	bc
	pop	bc
util_is_directory_empty.fail:
	xor	a, a
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
	ld	hl, (iy + fat.root_dir_pos)
	ld	a, (iy + fat.root_dir_pos + 3)
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	ld	(iy + fat.working_pointer), de
	ld	a, (de)
	cp	a, 0x2f
	jp	nz, util_locate_entry.error
	inc	de
	ld	a, (de)
	or	a, a
	jr	nz, util_locate_entry.findcomponent		; root directory
	lea	de, iy + fat.buffer
	inc	a
	ret
util_locate_entry.findcomponent:
	ld	de, (iy + fat.working_pointer)
	call	util_get_component_start
	jp	z, util_locate_entry.error
	ld	hl, util_locate_entry.string
	call	util_get_fat_name
	call	util_get_next_component
	ld	(iy + fat.working_pointer), de
util_locate_entry.locateloop:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_read_fat_block
	jp	nz, util_locate_entry.error
	push	iy
	lea	iy, iy + fat.buffer - 32
	ld	c, 16
util_locate_entry.detectname:
	lea	iy, iy + 32
	ld	a, (iy + 11)
	and	a, 0x0f
	cp	a, 0x0f				; long file name entry, skip
	jr	z, util_locate_entry.skipentry
	ld	a, (iy + 0)
	cp	a, 0xe5				; deleted entry, skip
	jr	z, util_locate_entry.skipentry
	or	a, a
	jp	z, util_locate_entry.errorpopiy			; end of list, suitable entry not found
	lea	de, iy+0
	ld	hl, util_locate_entry.string
	ld	b, 11
util_locate_entry.cmpnames:
	ld	a, (de)
	cp	a, (hl)
	jr	nz, util_locate_entry.skipentry
	inc	de
	inc	hl
	djnz	util_locate_entry.cmpnames
	lea	de, iy+0
	pop	iy
	ld	hl, (iy + fat.working_pointer)
	ld	a, (hl)
	or	a, a				; check if end of component lookup (de)
	jp	z, util_locate_entry.foundlastcomponent
	push	iy
	push	de
	pop	iy
	call	util_get_entry_first_cluster
	pop	iy
	call	util_cluster_to_block
	compare_auhl_zero
	jr	z, util_locate_entry.error			; this means it is empty... which shouldn't happen!
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	jp	util_locate_entry.findcomponent			; found the component we were looking for (yay)
util_locate_entry.skipentry:
	dec	c
	jr	nz, util_locate_entry.detectname
	pop	iy
util_locate_entry.movetonextblock:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_block_to_cluster
	push	hl
	push	af
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	ld	bc, 1				; increment auhl
	add	hl, bc
	add	a, b
	call	util_block_to_cluster
	pop	bc
	pop	de
	compare_hl_de
	jr	nz, util_locate_entry.movetonextcluster
	cp	a, b
	jr	nz, util_locate_entry.movetonextcluster
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	ld	bc, 1				; increment auhl
	add	hl, bc
	adc	a, b
	jr	util_locate_entry.storeblockandloop
util_locate_entry.movetonextcluster:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	call	util_block_to_cluster
	call	util_next_cluster
	call	util_cluster_to_block
util_locate_entry.storeblockandloop:
	ld	(iy + fat.working_block), hl
	ld	(iy + fat.working_block + 3), a
	compare_auhl_zero
	jp	nz, util_locate_entry.locateloop			; make sure we can get the next cluster
util_locate_entry.errorpopiy:
	pop	iy
util_locate_entry.error:
	xor	a, a
	sbc	hl, hl
	ret
util_locate_entry.foundlastcomponent:
	ld	hl, (iy + fat.working_block)
	ld	a, (iy + fat.working_block + 3)
	compare_auhl_zero
	ret
util_locate_entry.string:
	.db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0

;-------------------------------------------------------------------------------
util_cluster_to_block:
; gets the base block of the cluster
; inputs
;   auhl = cluster
;   iy -> fat structure
; outputs
;   auhl = block
	ld	de, -2
	add	hl, de
	adc	a, d
	ld	c, a
	ld	a, (iy + fat.blocks_per_cluster)
	jr	c, util_cluster_to_block.enter
	xor	a, a
	sbc	hl, hl
	ret
util_cluster_to_block.loop:
	add	hl, hl
	rl	c
util_cluster_to_block.enter:
	rrca
	jr	nc, util_cluster_to_block.loop
	ld	de, (iy + fat.data_region)
	ld	a, (iy + fat.data_region + 3)
	add	hl, de
	adc	a, c
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
	ld	bc, (iy + fat.data_region + 0)
	or	a, a
	sbc	hl, bc
	sbc	a, (iy + fat.data_region + 3)
	; AC:UHL = A:UHL << (8 - log2(blocks_per_cluster))
	ld	c, a
	ld	a, (iy + fat.blocks_per_cluster)
util_block_to_cluster.loop:
	add	hl, hl
	rl	c
	rla
	jr	nc, util_block_to_cluster.loop
	; A:UHL = (AC:UHL >> 8) + 2
	push	bc
	push	hl
	inc	sp
	pop	hl
	inc	sp
	inc	sp
	ld	bc, 2
	add	hl, bc
	adc	a, b
	ret

; inputs:
;   auhl : parent cluster
;   iy : fat struct
; outputs:
;   auhl : next cluster
util_next_cluster:
	ld	de, 0
	add	hl, hl
	adc	a, a				; << 1
	ld	e, l				; cluster pos
	push	af				; >> 8
	inc	sp
	push	hl
	inc	sp
	pop	hl
	inc	sp
	xor	a, a
	ld	bc, (iy + fat.fat_pos)
	add	hl, bc
	adc	a, a
	push	de
	call	util_read_fat_block
	pop	hl
	jr	nz, util_next_cluster.error
	add	hl, hl
	lea	de, iy + fat.buffer
	add	hl, de
	ld	de, (hl)
	inc	hl
	inc	hl
	inc	hl
	ld	a, (hl)
	and	a, 0x0f
	ld	hl, 8
	add	hl, de
	ex	de, hl
	ld	e, a
	adc	a, 0xf0
	jr	nc, util_next_cluster.found
	ld	e, a
	ex	de, hl
	ret
util_next_cluster.found:
	ld	a, e
	ret
util_next_cluster.error:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
util_fat_read_write:
; inputs:
;   same as fat_ReadFile / fat_WriteFile
; outputs:
;   same as fat_ReadFile / fat_WriteFile
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy + 3)
	ld	hl, (ix + fatFile.block_index)
	ld	(ix + fatFile.starting_block_index), hl
	ld	de, (ix + fatFile.block_count)
	compare_hl_de
	jp	nc, util_fat_read_write.return
	ex	de, hl
	or	a, a
	sbc	hl, de
	ld	de, (iy + 6)
	compare_hl_de
	jr	nc, util_fat_read_write.loop
	ld	(iy + 6), hl			; only read to eof
util_fat_read_write.loop:
	ld	hl, (iy + 6)			; number of blocks left to transfer
	compare_hl_zero				; no more blocks left, exit
	jr	z, util_fat_read_write.return

	ex	de, hl				; de = total remaining
	xor	a, a
	sub	a, (ix + fatFile.blocks_per_cluster)	; mask for number of blocks
	or	a, (ix + fatFile.block_index)	; mask the negative number of blocks remaining in this cluster
	cpl
	inc	a
	sbc	hl, hl
	ld	l, a				; hl = remaining in cluster
	compare_hl_de
	jr	nc, util_fat_read_write.singleclusterread
util_fat_read_write.multicluster:
	ex	de, hl				; de = number of blocks remaining in cluster
	ld	hl, (ix + fatFile.current_block)
	ld	a, (ix + fatFile.current_block + 3)
	compare_auhl_zero
	jr	z, util_fat_read_write.return
	push	de
	call	util_fat_read_write.do_xfer
	pop	de
	jr	nz, util_fat_read_write.return
	ld	hl, (iy + 6)
	or	a, a
	sbc	hl, de
	ld	(iy + 6), hl			; subtract remaining from total
	ld	hl, (ix + fatFile.block_index)
	add	hl, de
	ld	(ix + fatFile.block_index), hl
	call	util_fat_read_write.getnextcluster
	jr	util_fat_read_write.loop
util_fat_read_write.singleclusterread:
	ld	hl, (ix + fatFile.current_block)
	ld	a, (ix + fatFile.current_block + 3)
	compare_auhl_zero
	jr	z, util_fat_read_write.return			; invalid block
	push	de
	call	util_fat_read_write.do_xfer
	pop	de
	jr	nz, util_fat_read_write.return
	ld	hl, (ix + fatFile.current_block)
	ld	a, (ix + fatFile.current_block + 3)
	add	hl, de
	adc	a, d
	ld	(ix + fatFile.current_block), hl
	ld	(ix + fatFile.current_block + 3), a
	ld	hl, (ix + fatFile.block_index)
	add	hl, de
	ld	(ix + fatFile.block_index), hl
	ld	a, (ix + fatFile.blocks_per_cluster)
	dec	a
	and	a, l				; if at end of cluster, get the next one
	call	z, util_fat_read_write.getnextcluster
util_fat_read_write.return:
	ld	hl, (ix + fatFile.block_index)
	ld	de, (ix + fatFile.starting_block_index)
	or	a, a
	sbc	hl, de				; return number of blocks transferred
	pop	ix
	ret
util_fat_read_write.do_xfer:
	push	de
	pop	bc
	ld	de, (iy + 9)
	push	bc
	push	iy
	ld	iy, (ix + fatFile.fat)
	call	util_read_fat_multiple_blocks
.equ util_fat_read_write.block_func, .-3
	pop	iy
	pop	hl
	ld	h, l
	ld	l, 0
	add	hl, hl				; mutiply by 512
	ld	bc, (iy + 9)
	add	hl, bc
	ld	(iy + 9), hl
	ret
util_fat_read_write.getnextcluster:
	ld	hl, (ix + fatFile.block_index)
	ld	de, (ix + fatFile.block_count)
	or	a, a
	sbc	hl, de
	ret	nc				; don't try to go too far
	ld	hl, (ix + fatFile.current_cluster)
	ld	a, (ix + fatFile.current_cluster + 3)
	push	iy
	ld	iy, (ix + fatFile.fat)
	call	util_next_cluster
	pop	iy
	ld	(ix + fatFile.current_cluster), hl
	ld	(ix + fatFile.current_cluster + 3), a
	push	iy
	ld	iy, (ix + fatFile.fat)
	call	util_cluster_to_block
	pop	iy
	ld	(ix + fatFile.current_block), hl
	ld	(ix + fatFile.current_block + 3), a
	ret

;-------------------------------------------------------------------------------
util_read_fat_block:
; inputs:
;  auhl : lba
;  iy : fat struct
	lea	de, iy + fat.buffer
util_read_fat_block.buffer:
	ld	bc, 1

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
	ld	bc, (iy + fat.base_lba)
	add	hl, bc
	adc	a, (iy + fat.base_lba + 3)
	ld	c, a
	push	bc
	push	hl
	ld	hl, (iy + fat.user)
	push	hl
	ld	hl, (iy + fat.read)
	ld	de, util_read_fat_multiple_blocks.ret
	push	de
	jp	(hl)
util_read_fat_multiple_blocks.ret:
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	de				; pop count check
	pop	iy
	compare_hl_de
	ret

;-------------------------------------------------------------------------------
util_write_fat_block:
; inputs:
;  auhl : lba
;  iy : fat struct
	lea	de, iy + fat.buffer
util_write_fat_block.buffer:
	ld	bc, 1

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
	ld	bc, (iy + fat.base_lba)
	add	hl, bc
	adc	a, (iy + fat.base_lba + 3)
	ld	c, a
	push	bc
	push	hl
	ld	hl, (iy + fat.user)
	push	hl
	ld	hl, (iy + fat.write)
	ld	de, util_read_fat_multiple_blocks.ret
	push	de
	jp	(hl)

; inputs:
;  iy : msd struct
util_checkmagic:
	push	hl
	push	de
	lea	hl, iy + fat.buffer
	ld	de, 510
	add	hl, de
	ld	de, (hl)
	ld	hl, 0xAA55
	ex.s	de, hl
	compare_hl_de
	pop	de
	pop	hl
	ret

;-------------------------------------------------------------------------------
util_get_cluster_offset:
	ld	a, l
	and	a, 0x7f
	or	a, a
	sbc	hl, hl
	ld	l, a
	add	hl, hl
	add	hl, hl
	lea	de, iy + fat.buffer
	add	hl, de
	ret

;-------------------------------------------------------------------------------
util_cluster_entry_to_block:
	; input:
	; - A:UHL
	; output:
	; - A:UHL = floor(A:UHL / 128) + (yfat.fat_pos)
	; destroys:
	; - BC, flags

	; shift A:UHL left by 1 and shift the 33-bit result right by 8
	add	hl, hl
	rla
	push	af
	inc	sp
	push	hl
	inc	sp
	pop	hl
	inc	sp
	ccf
	sbc	a, a
	; the increment to set A to 0 or 1 is deferred until the adc below
	ld	bc, (iy + fat.fat_pos)
	add	hl, bc
	adc	a, 1
	ret

;-------------------------------------------------------------------------------
util_ceil_byte_size_to_block_size:
	; input:
	; - A:UHL
	; output:
	; - A:UHL = ceil(A:UHL / 512)
	; - A = 0
	; destroys:
	; - C, flags

	; UHL = A:UHL >> 9
	ld	c, l
	srl	a
	push	af
	inc	sp
	push	hl
	inc	sp
	pop	hl
	inc	sp
	rr	h
	rr	l
	; round up if any shifted-out bits were non-zero
	sbc	a, a
	or	a, c
	ret	z
	inc	hl
	xor	a, a
	ret

;-------------------------------------------------------------------------------
util_ceil_byte_size_to_cluster_size:
	; input:
	; - A:UHL
	; - IY = fat struct
	; output:
	; - UHL = ceil(A:UHL / (512 * blocks_per_cluster))
	; destroys:
	; - A, BC, flags

	; BC:UHL = A:UHL << (7 - log2(blocks_per_cluster))
	ld	b, (iy + fat.blocks_per_cluster)
	or	a, a
	jr	util_ceil_byte_size_to_cluster_size.enter
util_ceil_byte_size_to_cluster_size.loop:
	add	hl, hl
	rla
util_ceil_byte_size_to_cluster_size.enter:
	rl	b
	jr	nc, util_ceil_byte_size_to_cluster_size.loop
	ld	c, a
	; check if HL != 0
	ld	a, h
	or	a, l
	; UHL = BC:UHL >> 16
	push	bc
	push	hl
	inc	sp
	inc	sp
	pop	hl
	inc	sp
	; round up if any shifted-out bits were non-zero
	ret	z
	inc	hl
	ret
