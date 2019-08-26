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
	sbc	hl,hl		; return USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
fat_Init:
; Initializes a FAT filesystem from a particular LBA
; Arguments:
;  arg0: Non-zero for transparent mode, zero for opaque
; Returns:
;  Nothing
	ret

;-------------------------------------------------------------------------------
util_read10:
	ld	de,tmp.sectorbuffer
	ld	hl,scsi.read10
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
	cp	a,$0b				; fat32 partition?
	call	z,util_fat32_found
	cp	a,$0c				; fat32 partition?
	call	z,util_fat32_found
	cp	a,$0f				; extended partition?
	call	z,util_ebr_found
	cp	a,$05				; extended partition? (chs)
	call	z,util_ebr_found
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
	ld	bc,0
smc.partitionmsd := $ - 3
	ld	(hl),bc		; msd
	ld	de,0
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),de
	inc	hl
	ld	(hl),e		; lba
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),de
	inc	hl
	ld	(hl),e		; size (todo: fixme)
	xor	a,a
	sbc	hl,hl		; return USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
util_fat32_found:
	push	af
	ld	bc,(smc.partitionnumptr)
	ld	a,(bc)
	cp	a,0
smc.maxpartitions := $ - 1
	jr	z,.found_max
	ld	bc,4				; hl -> end of lba
	add	hl,bc
	push	hl
	ld	de,0
smc.partitionptrs := $ - 3
	ex	de,hl
	ld	bc,(smc.partitionmsd)
	ld	(hl),bc
	inc	hl
	inc	hl
	inc	hl
	ex	de,hl				; store msd structure ptr
	ld	bc,8
	ldir					; copy lba and size
	ld	(smc.partitionptrs),de
	pop	hl
	ld	de,scsi.read10.lba + 3
	call	util_reverse_copy		; move to next read sector

	ld	hl,(smc.partitionnumptr)
	inc	(hl)
.found_max:
	pop	af
	ret

;-------------------------------------------------------------------------------
util_ebr_found:
	push	af
	ld	bc,4				; hl -> end of lba
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


