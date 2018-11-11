;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'FATDRVCE', 0

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export fat_Init
	export fat_Find
	export fat_Select
	export fat_Open
	export fat_Close
	export fat_GetFileSize
	export fat_SetFileSize
	export fat_Tell
	export fat_SetBuffer
	export fat_Delete
	export fat_Create
	export fat_GetAttrib
	export fat_SetAttrib
	export fat_DirList
	export msd_Init
	export msd_Find
	export msd_Select
	export msd_KeepAlive
	export msd_ReadSector
	export msd_WriteSector
	export msd_SetJmp
	export msd_Cleanup
;-------------------------------------------------------------------------------

include 'debug.inc'
include 'host.inc'
include 'msd.inc'

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
; (2) Notes:
; The orginal µCFAT source was used to create many of the fat functions here,
; hand-optimized for speed in some areas. Some parts of this file are direct
; algorithmic implementations of the functions available in µCFAT. µCFAT is a 
; pretty awesome library, just throwing that out there too.
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
fat_Init:
	jp	_init_fat

;-------------------------------------------------------------------------------
fat_Find:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)			; fat_partition_t
	ld	a, (iy + 6)			; maximum
msd_mbr_parse:
	ld	(fat32_ptrs), hl
	ld	(fat32_max), a
	xor	a, a
	ld	(fat32_num), a
	sbc	hl, hl
	ld	(scsiRead10Lba), hl
	ld	(scsiRead10Lba + 3), a
	call	scsiRequestDefaultRead		; read sector
	ld	hl, (xferDataPtrDefault)
	ld	de, ($90 shl 16) or ($58 shl 8) or ($eb shl 0)
	or	a, a
	sbc	hl, de
   	add	hl, de				; check if boot sector
	jq	z, fat32_only			; this should only happen on the first one
	call	find_fat32
	ld	a, 0
fat32_num := $ - 1
	ret

;-------------------------------------------------------------------------------
fat_Select:
	ld	iy, 0
	add	iy, sp
	ld	e, (iy + 6)
	ld	d, 8
	mlt	de
	ld	hl, (iy + 3)
	add	hl, de
	ld	de, fat.partitionlba
	ld	bc, 4
	ldir
;	ld	hl, fat.partitionlba
;	call	debugHexBlockHL
;	db	4
;	call    debugNewLine
	ret

;-------------------------------------------------------------------------------
fat_Open:
	ret

;-------------------------------------------------------------------------------
fat_Close:
	pop	de
	pop	hl
	push	hl
	push	de
	call	fatfindfd
	ld	(hl),-1			; fat_fd[i].key = -1;
	ret

;-------------------------------------------------------------------------------
fat_GetFileSize:
	pop	de
	pop	hl
	push	hl
	push	de
	call	fatfindfd
	ld	hl,(iy + 18)
	ld	e,(iy + 21)		; return fat_fd[i].file_size;
	ret

;-------------------------------------------------------------------------------
fat_SetFileSize:
	ret

;-------------------------------------------------------------------------------
fat_Tell:
	pop	de
	pop	hl
	push	hl
	push	de
	call	fatfindfd
	ld	hl,(iy + 14)
	ld	e,(iy + 17)		; return fat_fd[i].fpos;
	ret

;-------------------------------------------------------------------------------
fat_SetBuffer:
	pop	de
	ex	(sp),hl			; hl -> buffer
	push	de
	ld	(fat.sectorbuffer),hl
	ret

;-------------------------------------------------------------------------------
fat_Delete:
	ret

;-------------------------------------------------------------------------------
fat_Create:
	ret

;-------------------------------------------------------------------------------
fat_GetAttrib:
	ret

;-------------------------------------------------------------------------------
fat_SetAttrib:
	ret

;-------------------------------------------------------------------------------
fat_DirList:
	ret

;-------------------------------------------------------------------------------
msd_Init:
	push	ix
	push	iy
	call	msdInit			; attempt to initialize mass storage device
	jr	nc,.fail
	xor	a,a
.ret:
	pop	iy
	pop	ix
	ret
.fail:
	call	usbCleanup
	xor	a,a
	inc	a
	jr	.ret

;-------------------------------------------------------------------------------
msd_Find:
	ret

;-------------------------------------------------------------------------------
msd_Select:
	ret

;-------------------------------------------------------------------------------
msd_KeepAlive:
	ld	hl,scsiTestUnitReady
	jp	scsiDefaultRequest

;-------------------------------------------------------------------------------
msd_ReadSector:
	call	__frameset0
	ld	a,(ix+9)
	ld	(scsiRead10Lba + 3),a
	ld	a,(ix+10)
	ld	(scsiRead10Lba + 2),a
	ld	a,(ix+11)
	ld	(scsiRead10Lba + 1),a
	ld	a,(ix+12)
	ld	(scsiRead10Lba + 0),a
	ld	de,(ix+6)
	call	scsiRequestRead
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_WriteSector:
	call	__frameset0
	ld	a,(ix+9)
	ld	(scsiWrite10Lba + 3),a
	ld	a,(ix+10)
	ld	(scsiWrite10Lba + 2),a
	ld	a,(ix+11)
	ld	(scsiWrite10Lba + 1),a
	ld	a,(ix+12)
	ld	(scsiWrite10Lba + 0),a
	ld	de,(ix+6)
	call	scsiRequestWrite
	ld	sp,ix
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_SetJmp:
	ret

;-------------------------------------------------------------------------------
msd_Cleanup:
	push	ix
	push	iy
	call	usbCleanup
	pop	iy
	pop	ix
	ret

;-------------------------------------------------------------------------------
msd_Detached:
	call	usbCleanup		; restore setjmp buffer to return to
	ret

;-------------------------------------------------------------------------------
_cluster_to_sector:
	pop	de
	pop	hl
	dec	sp
	pop	af
	dec	sp
	dec	sp
	push	hl
	push	de
	ld	de,-2
	add	hl,de
	adc	a,d
	ld	c,a
	ld	a,(_fat_state + 1)
	jr	c,enter
	sbc	hl,hl
	ld	e,l
	ret
loop:
	add	hl,hl
	rl	c
enter:
	rrca
	jr	nc,loop
	ld	de,(_fat_state + 20)
	ld	a,(_fat_state + 20 + 3)
	add	hl,de
	adc	a,c
	ld	e,a
	ret

;-------------------------------------------------------------------------------
_fname_to_fatname:
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 3)		; de = name
	ld	hl,(iy + 6)		; hl = fname
	ld	b,0			; for (i = 0; i < 8 && name[i] != '.' && name[i]; i++)
.loop1:
	ld	a,b
	cp	a,8
	jr	nc,.done1
	ld	a,(de)
	cp	a,46			; '.'
	jr	z,.done1
	ld	a,(de)
	or	a,a
	jr	z,.done1
	ld	(hl),a
	inc	de			; i++
	inc	hl
	inc	b
	jr	.loop1
.done1:
	ld	a,b			; if (i < 8 && name[i])
	cp	a,8
	jr	nc,.elseif
	ld	a,(de)
	or	a,a
	jr	z,.elseif

	ld	a,8			; for (j = i; j < 8; j++)
.loop2:
	cp	a,b
	jr	z,.fillremaining
	ld	(hl),32			; fname[j] = ' ';
	inc	hl
	inc	b
	jr	.loop2
.fillremaining:
	inc	de			; i++;

.loop3456:				; for (; j < 11 && name[i]; j++, i++)
	ld	a,b
	cp	a,11
	ret	nc
	ld	a,(de)
	or	a,a
	jr	z,.other
	inc	de
.store:
	ld	(hl),a			; fname[j] = name[i];
	inc	hl
	inc	b
	jr	.loop3456
.other:
	ld	a,32			; ' '
	jr	.store

.elseif:
	ld	a,b			; else if (i == 8 && name[i] == '.')
	cp	a,8
	jr	nz,.spacefill
	ld	a,(de)
	cp	a,46			; '.'
	jr	nz,.spacefill
	jr	.fillremaining

.spacefill:
	ld	a,11
.spacefillloop:				; for (; j < 11; j++)
	cp	a,b
	ret	z
	ld	(hl),32			; fname[j] = ' '
	inc	hl
	inc	b
	jr	.spacefillloop

_next_cluster:
	ld	hl,3
	add	hl,sp
	ld	a,(_fat_state + 24)
	or	a,a
	ld	a,(hl)
	inc	hl
	ld	hl,(hl)
	jr	z,.fat16.1
	add	a,a
	adc	hl,hl
.fat16.1:
	ex	de,hl
	sbc	hl,hl
	ld	l,a
	add	hl,hl
	push	hl
	ld	hl,(_fat_state + 12)
	add	hl,de
	ld	a,(_fat_state + 12 + 3)
	ld	e,a
	call	fat.readsector
	pop	de
	ld	hl,(fat.sectorbuffer)
	add	hl,de
	ld	a,(_fat_state + 24)
	or	a,a
	jr	z,.fat16.2
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)
	and	$0F
	ld	hl,8
	add	hl,de
	ex	de,hl
	ld	e,a
	adc	a,$F0
	ret	nc
	ld	e,a
	ex	de,hl
	ld	e,a
	ret

.fat16.2:
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	hl,$FF0008
	add	hl,de
	ex	de,hl
	ld	e,a
	ret	nc
	ex	de,hl
	ld	e,a
	ret

;-------------------------------------------------------------------------------
_end_of_chain_mark:
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	ld	de,8
	ld	a,(_fat_state + 24)
	or	a,a
	jr	nz,.fat32
	add.s	hl,de
	sbc	a,a
	ret
.fat32:
	add	hl,de
	ld	a,c
	adc	a,$f0
	sbc	a,a
	ret

;-------------------------------------------------------------------------------
fatfindfd:
	ld	a,l
	or	a,a
	jp	p,.valid
.ret0:
	pop	de			; pop return
	xor	a,a
	sbc	hl,hl			; if (fd < 0) return 0;
	ld	e,0
	ret
.valid:
	ld	b,3			; for (i = 0; i < max_fd_open; i++)
	ld	hl,_fat_fd
	ld	de,23
.find:
	cp	a,(hl)			; if (fat_fd[i].key == fd)
	jr	z,.found
	add	hl,de
	djnz	.find
	jr	.ret0
.found:
	push	hl
	pop	iy
	ret

;-------------------------------------------------------------------------------
; euhl = sector lba
fat.readsector:
	ld	bc,scsiRead10Lba
	call	add_fat.partitionlba
	ld	de,(fat.sectorbuffer)
	jp	scsiRequestRead

;-------------------------------------------------------------------------------
; euhl = sector lba
fat.writesector:
	ld	bc,scsiWrite10Lba
	call	add_fat.partitionlba
	ld	de,(fat.sectorbuffer)
	jp	scsiRequestWrite

;-------------------------------------------------------------------------------
_fat_ReadSector:
	ld	iy, 0
	add	iy, sp
	ld	de, (iy + 3)
	push	de
	ld	hl, (iy + 6)
	ld	e, (iy + 9)
	ld	bc, scsiRead10Lba
	call	add_fat.partitionlba
;	call	debugStr
;	db	'rd ', 0
;	ld	hl, scsiRead10Lba
;	call	debugHexBlockHL
;	db	4
;	call    debugNewLine
	pop	de
	call	scsiRequestRead
	xor	a, a
	ret

;-------------------------------------------------------------------------------
_fat_WriteSector:
	ld	iy, 0
	add	iy, sp
	ld	de,(iy + 3)
	push	de
	ld	hl, (iy + 6)
	ld	e, (iy + 9)
	ld	bc, scsiWrite10Lba
	call	add_fat.partitionlba
;	call	debugStr
;	db	'wr ', 0
;	ld	hl, scsiWrite10Lba
;	call	debugHexBlockHL
;	db	4
;	call    debugNewLine
	pop	de
	call	scsiRequestWrite
	xor	a, a
	ret

;-------------------------------------------------------------------------------
add_fat.partitionlba:
	push	bc
	ld	bc, (fat.partitionlba)
	ld	a, (fat.partitionlba + 3)
	add	hl, bc			; __ladd
	adc	a, e			; big endian
	pop	de
	ld	(de), a
	dec	sp
	push	hl
	inc	sp
	pop	af			; hlu
	inc	de
	ld	(de), a
	ld	a,h
	inc	de
	ld	(de), a
	ld	a,l
	inc	de
	ld	(de), a
	ret

;-------------------------------------------------------------------------------
find_fat32:
	call	scsiRequestDefaultRead		; read sector
	call	check_sector_magic
	ret	nz
	ld	hl, -64
	add	hl, sp
	ld	sp, hl
	ex	de, hl
	ld	hl, xferDataPtrDefault + 446 + 4
	ld	bc, 64
	ldir					; copy the current partition table to the stack
	xor	a, a
	sbc	hl, hl
	add	hl, sp
	ld	a, 4
.loop:
	push	af
	push	hl
	ld	a, (hl)
;	call	debugHexA
	cp	a, $0b				; fat32 partition?
	call	z, fat32_found
	cp	a, $0c				; fat32 partition?
	call	z, fat32_found
	cp	a, $0f				; extended partition?
	call	z, ebr_found
	cp	a, $05				; extended partition? (chs)
	call	z, ebr_found
	pop	hl
	ld	bc, 16
	add	hl, bc

;	push	hl
;	call	debugStr
;	db	'next loop', 0
;	call	debugNewLine
;	ld	a, 200
;	call	_DelayTenTimesAms
;	pop	hl

	pop	af
	dec	a
	jr	nz, .loop
;	call	debugStr
;	db	'exited loop.', 0
;	call	debugNewLine
	ld	hl, 64
	add	hl, sp
	ld	sp, hl
	ret

;-------------------------------------------------------------------------------
fat32_only:
	call	check_sector_magic
	ld	a, 0
	ret	nz
	inc	a
	ld	(fat32_num), a
	ld	hl, (fat32_ptrs)
	push	hl
	pop	de
	ld	(hl), 0
	ld	bc, 7
	inc	de
	ldir
	ret

;-------------------------------------------------------------------------------
fat32_found:
	push	af
;	call	debugStr
;	db	'found fat', 0
;	call	debugNewLine
	ld	a, (fat32_num)
	cp	a, 0
fat32_max := $ - 1
	jr	z, .found_max
	ld	bc, 4				; hl -> end of lba
	add	hl, bc
	push	hl
	ld	c, 8
	ld	de, 0
fat32_ptrs := $ - 3
	ldir
	ld	(fat32_ptrs), de
	pop	hl
	ld	de, scsiRead10Lba + 3
	call	reverse_copy
;	call	scsiRequestDefaultRead		; read sector
;	ld	hl,xferDataPtrDefault
;	call	debugHexBlockHL
;	db	16
;	call	debugNewLine

.found_max:
	ld	hl, fat32_num
	inc	(hl)
	pop	af
	ret

;-------------------------------------------------------------------------------
ebr_found:
	push	af
;	call	debugStr
;	db	'found ebr', 0
;	call	debugNewLine
	ld	bc, 4				; hl -> end of lba
	add	hl, bc
	ld	de, scsiRead10Lba + 3
	call	reverse_copy
	call	find_fat32			; recursively locate fat32 partitions
	pop	af
	ret

;-------------------------------------------------------------------------------
reverse_copy:
	ld	b, 4
.loop:
	ld	a, (hl)
	ld	(de), a
	inc	hl
	dec	de
	djnz	.loop
	ret

;-------------------------------------------------------------------------------
check_sector_magic:
	ld	hl, xferDataPtrDefault + 510	; offset = signature
test_sector:
	ld	a, (hl)
	cp	a, $55
	ret	nz
	inc	hl
	ld	a, (hl)
	cp	a, $aa
	ret

fat.partitionlba:
	db	0,0,0,0
fat.sectorbuffer:
	db	0,0,0

_fat_state:
	db	0 dup 25
_fat_fd:
	db	0 dup 92
_fat_key:
	db	0

include 'fat.zds'

