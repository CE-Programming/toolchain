;-------------------------------------------------------------------------------
; fatdrvce: Provides MSD and FAT API functions for the TI84+CE calculators.
; Copyright (C) 2019 MateoConLechuga, jacobly0
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU Lesser General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU Lesser General Public License for more details.
;
; You should have received a copy of the GNU Lesser General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;-------------------------------------------------------------------------------
; Notes:
; The orginal µCFAT source was used as inspiration for some of the implemented
; file i/o function, and hand-optimized for speed. Some parts of this file are
; related to implementations of functions available in µCFAT. The license for
; µCFAT is provided below.
;-------------------------------------------------------------------------------
; Copyright (c) 2015 Steven Arnow <s@rdw.se>
; 'fat.c' - This file is part of µCFAT
;
; This software is provided 'as-is', without any express or implied
; warranty. In no event will the authors be held liable for any damages
; arising from the use of this software.
;
; Permission is granted to anyone to use this software for any purpose,
; including commercial applications, and to alter it and redistribute it
; freely, subject to the following restrictions:
;
; 	1. The origin of this software must not be misrepresented; you must not
; 	claim that you wrote the original software. If you use this software
; 	in a product, an acknowledgment in the product documentation would be
; 	appreciated but is not required.
;
; 	2. Altered source versions must be plainly marked as such, and must not be
; 	misrepresented as being the original software.
;
; 	3. This notice may not be removed or altered from any source
; 	distribution.
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
fat_Find:
; Locates FAT partitions on the MSD
; Arguments:
;  sp + 3  : msd device structure
;  sp + 6  : storage for found partitions
;  sp + 9  : return number of found partitions
;  sp + 12 : maxium number of partitions to find
; Returns:
;  USB_SUCCESS on success
	ld	iy,0
	add	iy,sp
	ld	bc,(iy + 3)			; msd structure
	ld	de,(iy + 6)			; partition pointers
	ld	hl,(iy + 9)			; return number
	ld	a,(iy + 12)			; maximum partitions to locate
	ld	(smc.partitionmsd),bc
	ld	(smc.partitionnumptr),hl
	ld	(smc.partitionptrs),de
	ld	(smc.maxpartitions),a
	xor	a,a
	ld	(hl),a
	sbc	hl,hl
	ld	(scsi.read10.lba + 0),hl
	ld	(scsi.read10.lba + 3),a
	ld	iy,(iy + 3)			; usb device
	call	util_read10			; read zero sector
	ld	hl,USB_ERROR_FAILED
	ret	nz				; check if error
	ld	hl,(tmp.sectorbuffer)
	ld	de,($90 shl 16) or ($58 shl 8) or ($eb shl 0)
	compare_hl_de				; check if in boot sector
	jq	z,util_one_fat			; sometimes this happens if users are dumb
	ld	(smc.errorsp),sp
	call	util_find
	xor	a,a
	sbc	hl,hl				; return USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
fat_Init:
; Initializes a FAT filesystem from a particular LBA
; Arguments:
;  arg0: Uninitialized FAT structure type
;  arg1: Available FAT partition returned from fat_Find
; Returns:
;  USB_SUCCESS on success
	ld	iy,0
	add	iy,sp
	push	ix
	ld	de,(iy + 6)
	ld	iy,(iy + 3)
	ld	(yfatType.partition),de		; store partition pointer
	ld	ix,(yfatType.partition)
	ld	hl,(xfatPartition.lba + 0)
	ld	a,(xfatPartition.lba + 3)	; get fat base lba
	ld	(yfatType.fat_base_lba + 0),hl
	ld	(yfatType.fat_base_lba + 3),a
	or	a,a
	sbc	hl,hl
	call	util_read_fat_sector		; read fat zero sector
	jq	nz,.error
	ld	ix,tmp.sectorbuffer
	ld	a,(ix + 12)
	cp	a,(ix + 16)			; ensure 512 byte sectors and 2 FATs
	jq	nz,.error
	ld	a,(ix + 39)
	or	a,a				; can't support reallllly big drives (BPB_FAT32_FATSz32 high)
	jq	nz,.error
	ld	a,(ix + 66)
	cp	a,$28				; check fat32 signature
	jr	z,.goodsig
	cp	a,$29
	jq	nz,.error
.goodsig:
	xor	a,a
	ld	hl,(ix + 14)
	ex.s	de,hl
	ld	(yfatType.fat_pos),de
	ld	hl,(ix + 36)			; BPB_FAT32_FATSz32
	add	hl,hl				; * num fats
	adc	a,a
	add	hl,de				; data region
	adc	a,a				; get carry if needed
	ld	(yfatType.data_region + 0),hl
	ld	(yfatType.data_region + 3),a
	push	af
	ex	de,hl
	ld	hl,(ix + 44 + 0)
	ld	a,(ix + 44 + 3)			; BPB_FAT32_RootClus
	ld	bc,2
	or	a,a
	sbc	hl,bc
	jr	nc,.nocarry
	dec	a
.nocarry:
	ld	c,(ix + 13)
	ld	(yfatType.cluster_size),c	; sectors per cluster
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
	ld	(yfatType.root_dir_pos + 0),hl
	ld	(yfatType.root_dir_pos + 3),a
	ld	de,(ix + 48)
	ex.s	de,hl
	ld	(yfatType.fs_info),hl
	xor	a,a
	call	util_read_fat_sector
	jq	nz,.error
	call	util_checkmagic
	jq	nz,.error			; uh oh!
	ld	hl,(ix + 0)			; ix should still point to the temp sector...
	ld	bc,$615252			; don't bother comparing $41 byte...
	xor	a,a
	sbc	hl,bc
	jq	nz,.error
	scf
	sbc	hl,hl
	ex	de,hl
	ld	hl,tmp.sectorbuffer + 488	; invalidate free space
	ld	(hl),de
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),e
	ld	hl,(yfatType.fs_info)		; a is always zero (set from above)
	call	util_write_fat_sector
	jq	nz,.error
	or	a,a
	sbc	hl,hl				; return success
	pop	ix
	ret
.error:
	ld	hl,USB_ERROR_FAILED
	pop	ix
	ret

;-------------------------------------------------------------------------------
util_get_spare_file:
; outputs
;  b: index of file (if needed?)
;  hl, iy: pointer to file index
	ld	b,MAX_FAT_FILES
	ld	iy,fatFile4
	ld	de,-sizeof fatFile
.find:
	lea	hl,iy
	bit	BIT_OPEN,(yfatFile.flags)
	ret	z
	add	iy,de
	djnz	.find
	xor	a,a
	sbc	hl,hl				; return null
	ret

;-------------------------------------------------------------------------------
util_cluster_to_sector:
; gets the base sector of the cluster
; inputs
;   auhl = cluster
;   iy -> fat structure
; outputs
;   auhl = sector
	ld	de,-2
	add	hl,de
	adc	a,d
	ld	c,a
	ld	a,(yfatType.cluster_size)
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
	ld	de,(yfatType.data + 0)
	ld	a,(yfatType.data + 3)
	add	hl,de
	adc	a,c
	ret

;-------------------------------------------------------------------------------
util_sector_to_cluster:
; gets sector to base cluster
; inputs
;   auhl = sector
;   iy -> fat structure
; outputs
;   auhl = cluster
	or	a,a
	jr	nz,.notzero
	compare_hl_zero
	ret	z
.notzero:
	ld	bc,(yfatType.data + 0)
	or	a,a
	sbc	hl,bc
	sbc	a,(yfatType.data + 3)
	ld	de,(yfatType.cluster_size - 2)
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

;-------------------------------------------------------------------------------
util_next_cluster:
; moves to next cluster in the chain
; inputs
;   auhl = parent cluster
;   iy -> fat structure
; outputs
;   auhl = next cluster
	add	hl,hl
	adc	a,a		; << 1
	ex	de,hl
	or	a,a
	sbc	hl,hl
	ld	l,e
	add	hl,hl
	push	hl		; hl = cluster_pos
	push	af		; >> 8
	inc	sp
	push	de
	inc	sp
	pop	hl
	inc	sp
	xor	a,a
	ld	de,(yfatType.fat_pos)
	add	hl,de
	adc	a,a		; auhl = cluster_sec
	call	util_read_fat_sector
	pop	de
	jr	nz,.error
	ld	hl,tmp.sectorbuffer
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
util_read_fat_sector:
; inputs
;  auhl: LBA address
;  iy: fat_t structure
; outputs
;  de: read sector
	ld	bc,(yfatType.fat_base_lba + 0)
	ld	e,(yfatType.fat_base_lba + 3)
	add	hl,bc
	adc	a,e			; big endian
	ld	de,scsi.read10.lba
	ld	(de),a
	dec	sp
	push	hl
	inc	sp
	pop	af			; hlu
	inc	de
	ld	(de),a
	ld	a,h
	inc	de
	ld	(de),a
	ld	a,l
	inc	de
	ld	(de),a
	push	iy
	ld	iy,(yfatType.partition)
	ld	iy,(yfatPartition.msd)
	call	util_read10
	pop	iy
	ret

;-------------------------------------------------------------------------------
util_write_fat_sector:
; inputs
;  auhl: lba address
;  iy: fat_t structure
; outputs
	ld	bc,(yfatType.fat_base_lba + 0)
	ld	e,(yfatType.fat_base_lba + 3)
	add	hl,bc
	adc	a,e			; big endian
	ld	de,scsi.write10.lba
	ld	(de),a
	dec	sp
	push	hl
	inc	sp
	pop	af			; hlu
	inc	de
	ld	(de),a
	ld	a,h
	inc	de
	ld	(de),a
	ld	a,l
	inc	de
	ld	(de),a
	push	iy
	ld	iy,(yfatType.partition)
	ld	iy,(yfatPartition.msd)
	call	util_write10
	pop	iy
	ret

;-------------------------------------------------------------------------------
util_read10:
	ld	de,tmp.sectorbuffer
	ld	hl,scsi.read10
	jq	util_scsi_request

;-------------------------------------------------------------------------------
util_write10:
	ld	de,tmp.sectorbuffer
	ld	hl,scsi.write10
	jq	util_scsi_request

;-------------------------------------------------------------------------------
util_find:
	call	util_read10			; read sector
	jr	nz,.error
	call	util_checkmagic
	ret	nz
	ld	hl,-64
	add	hl,sp
	ld	sp,hl
	ex	de,hl
	ld	hl,tmp.sectorbuffer + 446 + 4
	ld	bc,64
	ldir					; copy the current partition table to the stack
	xor	a,a
	sbc	hl,hl
	add	hl,sp
	ld	a,4
.loop:
	push	af
	push	hl
	ld	a,(hl)
	cp	a,$0c				; fat32 partition? (lba)
	call	z,util_fat32_found
	cp	a,$0b				; fat32 partition? (chs)
	call	z,util_fat32_chs_found
	cp	a,$0f				; extended partition? (lba)
	call	z,util_ebr_found
	cp	a,$05				; extended partition? (chs)
	call	z,util_ebr_chs_found
	pop	hl
	ld	bc,16
	add	hl,bc
	pop	af
	dec	a
	jr	nz,.loop
	ld	hl,64
	add	hl,sp
	ld	sp,hl
	ret
.error:
	ld	sp,0
smc.errorsp := $ - 3
	ld	hl,USB_ERROR_FAILED
	ret

;-------------------------------------------------------------------------------
util_one_fat:
	call	util_checkmagic
	ld	hl,0
smc.partitionnumptr := $ - 3
	ld	(hl),0
	ret	nz
	ld	(hl),1
	ld	hl,(smc.partitionptrs)
	ld	de,0
	ld	(hl),de
	inc	hl
	ld	(hl),e				; lba
	inc	hl
	inc	hl
	inc	hl
	ld	bc,0
smc.partitionmsd := $ - 3
	ld	(hl),bc				; msd
	ex	de,hl				; return USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
util_fat32_chs_found:
	jq	util_fat32_found

;-------------------------------------------------------------------------------
util_fat32_found:
	push	af
	ld	bc,(smc.partitionnumptr)
	ld	a,(bc)
	cp	a,0
smc.maxpartitions := $ - 1
	jr	z,.found_max
	ld	bc,4				; hl -> start of lba
	add	hl,bc
	push	hl
	ld	de,0
smc.partitionptrs := $ - 3
	ld	bc,4
	ldir					; copy lba
	ld	(smc.partitionptrs),de
	ex	de,hl
	ld	bc,(smc.partitionmsd)
	ld	(hl),bc
	pop	hl
	ld	de,scsi.read10.lba + 3
	call	util_reverse_copy		; move to next read sector

	ld	hl,(smc.partitionnumptr)
	inc	(hl)
.found_max:
	pop	af
	ret

;-------------------------------------------------------------------------------
util_ebr_chs_found:
	jq	util_ebr_found

;-------------------------------------------------------------------------------
util_ebr_found:
	push	af
	ld	bc,4				; hl -> start of lba
	add	hl,bc
	ld	de,scsi.read10.lba + 3
	call	util_reverse_copy
	call	util_find			; recursively locate fat32 partitions
	pop	af
	ret

;-------------------------------------------------------------------------------
util_reverse_copy:
	ld	b,4
.copy:
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	djnz	.copy
	ret

;-------------------------------------------------------------------------------
util_checkmagic:
	ld	hl,tmp.sectorbuffer + 510	; offset = signature
util_sector_checkmagic:
	ld	a,(hl)
	cp	a,$55
	ret	nz
	inc	hl
	ld	a,(hl)
	cp	a,$aa
	ret

